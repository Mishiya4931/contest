#include "Player.h"
#include"Defines.h"
#include"GaugeUI.h"
#include"ShaderList.h"
#include"ModelCache.h"
//=============�萔��`=========================
#define MOVE_SPEED_BASE (0.07f)//�X�s�[�h�̃x�[�X
#define MOVE_SPEED_NORMAl (0.0f)//�ʏ�̃X�s�[�h
#define MOVE_SPEED_DASH (0.05f)//�_�b�V���̃X�s�[�h
#define MOVE_SPEED_SLOW (-0.06f)//�������̃X�s�[�h
#define ROTATION_SPEED_BASE (0.9f)//��]�̃X�s�[�h�x�[�X
#define DASH_TIME (60)//�_�b�V�����鎞��
#define DASH_INTERVAL (120)//�_�b�V�����ł���܂ł̎���
#define GAUGE_UI_CORRECT (0.0054f)
#define COLLISION_CORRECT (0.001f)
#define PLAYER_UI_SPRITE_SPRIT_X (5.0f)
#define PLAYER_UI_SPRITE_SPRIT_Y (2.0f)
#define PLAYER_UI_SPRITE_POS_X (80.0f)
#define PLAYER_UI_SPRITE_POS_Y (80.0f)
//============�O���|�o����`====================

enum ePlayerState {//�v���C���[�̏��
    NORMAL,//�ʏ�
    DASH,//�_�b�V��
    SLOW//����
};
ePlayerState g_eState;
Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_power(0.0f),
    m_fDashSpeed(0.0f),
    m_nDashIntervalCnt(0),
    m_bDashFlag(false),
    m_pGaugeUI(nullptr),
    m_nGaugeUICnt(DASH_TIME + DASH_INTERVAL),
    m_nItemCnt(0), m_pModel(nullptr)
{
    m_pTexture = new Texture();
    m_pBackTexture = new Texture();
    m_pTexture->Create("Assets/texture/number.png");
    m_pBackTexture->Create("Assets/texture/CloudUI.png");
    m_pModel = ModelCache::GetInstance()->GetCache("Player");
    m_pModelEquip = ModelCache::GetInstance()->GetCache("PlayerEquip");
    m_pos = { 0.0f,0.5f,0.0f };
    m_pGaugeUI = new GaugeUI();
    m_box = {
    DirectX::XMFLOAT3(0.0f,0.5f,0.0f),
    DirectX::XMFLOAT3(1.0f,1.0f,1.0f)
    };
    m_pDashSe = LoadSound("Assets/sound/Dash.mp3");
}

Player::~Player()
{
    m_pspeaker = nullptr;
    SAFE_DELETE(m_pGaugeUI);
    SAFE_DELETE(m_pTexture);
    SAFE_DELETE(m_pBackTexture);
}
//�X�V����
void Player::Update()
{
    //�J�������ݒ肳��Ă��Ȃ��ꍇ�͏������Ȃ�
    if (!m_pCamera) { return; }
    UpdateMove();

    m_box.center = m_pos;
    OnCollisionWall();

}
//�`�揈��
void Player::Draw()
{
    DrawUI();
    RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
    DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
    SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D�\���ɂȂ�
    DirectX::XMFLOAT4X4 wvp[3];
    DirectX::XMMATRIX T =
        DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    DirectX::XMMATRIX S =
        DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // ��]
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(mat));
    wvp[1] = m_pCamera->GetViewMatrix();
    wvp[2] = m_pCamera->GetProjectionMatrix();

    // �V�F�[�_�[�ւ̕ϊ��s���ݒ�
    ShaderList::SetWVP(wvp);

    //// ���f���Ɏg�p���钸�_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[��ݒ�
    m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
    m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

    // �����̃��b�V���ō\������Ă���ꍇ�A���镔���͋����I�ȕ\���A���镔���͔�����I�ȕ\����
    // ������ꍇ������B�O��̕\���͓����}�e���A���ňꊇ�\�����Ă������߁A���b�V�����ƂɃ}�e���A����
    // �؂�ւ���B

    for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
        //���f���̃��b�V�����擾
        Model::Mesh mesh = *m_pModel->GetMesh(i);
        //���b�V���Ɋ��蓖�Ă��Ă���}�e���A���擾
        Model::Material material = *m_pModel->GetMaterial(mesh.materialID);
        //�V�F�[�_�[�փ}�e���A����ݒ�
        material.ambient = { 0.6,0.6,0.6,1.0f };
        ShaderList::SetMaterial(material);
        //���f���̕`��
        m_pModel->Draw(i);
    }
    
    T =
       DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    S =
       DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
    R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
       DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
       DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // ��]
    mat = S * R * T;
    DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(mat));
    wvp[1] = m_pCamera->GetViewMatrix();
    wvp[2] = m_pCamera->GetProjectionMatrix();

    // �V�F�[�_�[�ւ̕ϊ��s���ݒ�
    ShaderList::SetWVP(wvp);

    //// ���f���Ɏg�p���钸�_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[��ݒ�
    m_pModelEquip->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
    m_pModelEquip->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

    // �����̃��b�V���ō\������Ă���ꍇ�A���镔���͋����I�ȕ\���A���镔���͔�����I�ȕ\����
    // ������ꍇ������B�O��̕\���͓����}�e���A���ňꊇ�\�����Ă������߁A���b�V�����ƂɃ}�e���A����
    // �؂�ւ���B

    for (int i = 0; i < m_pModelEquip->GetMeshNum(); ++i) {
        //���f���̃��b�V�����擾
        Model::Mesh mesh = *m_pModelEquip->GetMesh(i);
        //���b�V���Ɋ��蓖�Ă��Ă���}�e���A���擾
        Model::Material material = *m_pModelEquip->GetMaterial(mesh.materialID);
        //�V�F�[�_�[�փ}�e���A����ݒ�
        material.ambient = { 0.6,0.6,0.6,1.0f };
        ShaderList::SetMaterial(material);
        //���f���̕`��
        m_pModelEquip->Draw(i);
    }
}

void Player::UpdateMove()
{

    if (IsKeyPress('A'))
    {
        m_Rotation.z += -ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('D'))
    {
        m_Rotation.z += ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('W'))
    {
        m_Rotation.x += -ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('S'))
    {
        m_Rotation.x += ROTATION_SPEED_BASE;
    }
    //�L�����N�^�[�̏�ԕύX(��{��NORMAL���)
    g_eState = NORMAL;
    if (IsKeyTrigger(VK_SHIFT))//�_�b�V���t���O�𗧂Ă�
    {
        if (!m_bDashFlag) {
            m_pspeaker = PlaySound(m_pDashSe);
            m_pspeaker->SetVolume(1.0f);
            m_bDashFlag = true;
            m_nGaugeUICnt = 0;
        }
        
    }
    if (m_bDashFlag)//�_�b�V���t���O�������Ă�����
    {
        
        m_nDashIntervalCnt++;
        m_nGaugeUICnt++;
        if (m_nDashIntervalCnt < DASH_TIME)//DASH_TIME�̎��ԕ�DASH��ԂɂȂ�X�s�[�h���オ��
        {
            g_eState = DASH;
        }
        else if(DASH_TIME < m_nDashIntervalCnt && m_nDashIntervalCnt <DASH_TIME + DASH_INTERVAL)//���Ԃ��o�߂�����NORMAL��Ԃ�
        {
            g_eState = NORMAL;
        }
        else if (DASH_TIME + DASH_INTERVAL < m_nDashIntervalCnt)//DASH_INTERVAL���_�b�V�����g���Ȃ�����
        {
            m_nDashIntervalCnt = 0;//�_�b�V���t���O�����낵�ăJ�E���^���[����
            m_bDashFlag = false;
        }
    }
    if (IsKeyPress(VK_SPACE))//����
    {
        g_eState = SLOW;
    }
    switch (g_eState)//�v���C���[�̏�Ԃɂ���Ĉړ��X�s�[�h��ς���
    {
    case NORMAL:
        m_fDashSpeed = MOVE_SPEED_NORMAl;//�m�[�}����0.0f
        break;
    case DASH:
        m_fDashSpeed = MOVE_SPEED_DASH;
        break;
    case SLOW:
        m_fDashSpeed = MOVE_SPEED_SLOW;
        break;
    default:
        break;
    }
    m_pGaugeUI->SetGauge(static_cast<float>(m_nGaugeUICnt) * GAUGE_UI_CORRECT);
    m_pGaugeUI->Update();
    //�ړ��֘A�̍X�V
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // �s��� z������(row[2]) �� forward �ɂȂ�
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] �� (x, y, z, w)
    // �ړ���+
    bool HitWallFlag = false;
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, MOVE_SPEED_BASE + m_fDashSpeed);
    if (HitWallFlag)moveVec = DirectX::XMVectorScale(forward, 0.0f);
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    // �ʒu���X�V
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);
}

void Player::DrawUI()
{
    RenderTarget* pRTV = GetDefaultRTV();// �f�B�X�v���C���̎擾
    DepthStencil* pDSV = GetDefaultDSV(); // �[�x�o�b�t�@�̎擾
    // 2D�\���̐ݒ� 
    SetRenderTargets(1, &pRTV, nullptr);
    // �X�v���C�g�̕\���ɕK�v�ȍs����v�Z 
    DirectX::XMFLOAT4X4 world, view, proj;
    DirectX::XMMATRIX mView =
        DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
            DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
            DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
        );
    DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
        0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, CMETER(30.0f), METER(2.0f));
    DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(mView));
    DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(mProj));
    Sprite::SetView(view);
    Sprite::SetProjection(proj);
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(PLAYER_UI_SPRITE_POS_X, PLAYER_UI_SPRITE_POS_Y, 0.0f);
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.2f, -1.2f, 1.0f);// Y�㉺���]
    DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
    mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
    DirectX::XMStoreFloat4x4(&world, mWorld);
    Sprite::SetWorld(world);
    Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
    Sprite::SetOffset({ 0.0f, 0.0f });// ���W
    Sprite::SetUVPos({0.0f,0.0f});
    Sprite::SetUVScale({ 1.0f,1.0f});
    Sprite::SetTexture(m_pBackTexture);
    Sprite::SetColor({ 1.0f, 1.0f/ (static_cast<float>(m_nItemCnt+1.0f)*0.6f), 1.0f / (static_cast<float>(m_nItemCnt + 1.0f) * 0.6f), 1.0f });
    Sprite::Draw();  

    //��̈�
    int one = m_nItemCnt % 10;
    T = DirectX::XMMatrixTranslation(PLAYER_UI_SPRITE_POS_X-5.0f, PLAYER_UI_SPRITE_POS_Y+12.0f, 0.0f);
    S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
    mWorld = S * T;// �g�k����]���ړ�
    mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
    DirectX::XMStoreFloat4x4(&world, mWorld);
    Sprite::SetWorld(world);
    Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
    Sprite::SetOffset({ 0.0f, 0.0f });// ���W
    Sprite::SetUVPos({ 1.0f / PLAYER_UI_SPRITE_SPRIT_X * (one % static_cast<int>(PLAYER_UI_SPRITE_SPRIT_X)),1.0f / PLAYER_UI_SPRITE_SPRIT_Y * (one / static_cast<int>(PLAYER_UI_SPRITE_SPRIT_X)) });
    Sprite::SetUVScale({ 1.0f / PLAYER_UI_SPRITE_SPRIT_X,1.0f / PLAYER_UI_SPRITE_SPRIT_Y });
    Sprite::SetTexture(m_pTexture);
    Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
    Sprite::Draw();
}

void Player::OnCollisionWall()
{

    for (auto& itr : m_pWall)
    {
        Collision::Result result = Collision::Hit(GetCollision(), itr->GetCollision());
        if (result.isHit)
        {
            switch (itr->GetNo())
            {
            case WALL_INNER:
                m_pos.z = itr->GetCollision().center.z + (GetCollision().size.z + itr->GetCollision().size.z + COLLISION_CORRECT) * 0.5f * result.normal.z;
                break;
            case WALL_UP:
                m_pos.y = itr->GetCollision().center.y + (GetCollision().size.y + itr->GetCollision().size.y + COLLISION_CORRECT) * 0.5f * result.normal.y;
                break;
            case WALL_LEFT:
                m_pos.x = itr->GetCollision().center.x + (GetCollision().size.x + itr->GetCollision().size.x + COLLISION_CORRECT) * 0.5f * result.normal.x;
                break;
            case WALL_RIGHT:
                m_pos.x = itr->GetCollision().center.x + (GetCollision().size.x + itr->GetCollision().size.x + COLLISION_CORRECT) * 0.5f* result.normal.x;
                break;
            case WALL_BACK:
                m_pos.z = itr->GetCollision().center.z + (GetCollision().size.z + itr->GetCollision().size.z + COLLISION_CORRECT) * 0.5f * result.normal.z;
                break;
            case WALL_DOWN:
                m_pos.y = itr->GetCollision().center.y + (GetCollision().size.y + itr->GetCollision().size.y + COLLISION_CORRECT) * 0.5f * result.normal.y;
                break;
            default:
                break;
            }
        }
    }
}
