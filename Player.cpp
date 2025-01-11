#include "Player.h"
#include"Defines.h"
#include"GaugeUI.h"

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

//============�O���|�o����`====================
//enum eGolfBallShotStep {
//	SHOT_WAIT,  //  ����ł̂�҂�
//	SHOT_KEEP,  //  �L�[���͊J�n
//	SHOT_RELEASE, //  �L�[���͂���߂��i����łj
//};

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
    m_nGaugeUICnt(DASH_TIME+DASH_INTERVAL),
    m_nItemCnt(0)
{
    m_pos = { 0.0f,0.5f,0.0f };
    m_pGaugeUI = new GaugeUI();
    m_box = {
    DirectX::XMFLOAT3(0.0f,0.5f,0.0f),
    DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
        
}

Player::~Player()
{
    SAFE_DELETE(m_pGaugeUI);
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
    m_pGaugeUI->Draw();
    DirectX::XMFLOAT4X4 world;
    DirectX::XMMATRIX T = 
        DirectX::XMMatrixTranslation(m_pos.x,m_pos.y,m_pos.z);
    DirectX::XMMATRIX S = 
        DirectX::XMMatrixScaling(0.4f,0.4f,0.4f);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // ��]
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat));
    Geometory::SetWorld(world);

    Geometory::DrawBox();
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
