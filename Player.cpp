#include "Player.h"
#include"Defines.h"


//=============�萔��`=========================
#define MOVE_SPEED_BASE (0.07f)//�X�s�[�h�̃x�[�X
#define MOVE_SPEED_NORMAl (0.0f)//�ʏ�̃X�s�[�h
#define MOVE_SPEED_DASH (0.05f)//�_�b�V���̃X�s�[�h
#define MOVE_SPEED_SLOW (-0.04f)//�������̃X�s�[�h
#define ROTATION_SPEED_BASE (0.9f)//��]�̃X�s�[�h�x�[�X
#define DASH_TIME (30)//�_�b�V�����鎞��
#define DASH_INTERVAL (120)//�_�b�V�����ł���܂ł̎���
//============�O���|�o����`====================
enum eGolfBallShotStep {
	SHOT_WAIT,  //  ����ł̂�҂�
	SHOT_KEEP,  //  �L�[���͊J�n
	SHOT_RELEASE, //  �L�[���͂���߂��i����łj
};
enum ePlayerState {//�v���C���[�̏��
    NORMAL,//�ʏ�
    DASH,//�_�b�V��
    SLOW//����
};
ePlayerState g_eState;
Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_isStop(false),
    m_shotStep(SHOT_WAIT),
    m_power(0.0f),
    m_fDashSpeed(0.0f),
    m_bDashFlag(false),
    m_nDashIntervalCnt(0)
{
    m_box = {
    DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
    DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
        
}

Player::~Player()
{
}
//�X�V����
void Player::Update()
{
    //�J�������ݒ肳��Ă��Ȃ��ꍇ�͏������Ȃ�
    if (!m_pCamera) { return; }
    UpdateMove();

    m_box.center = m_pos;
}
//�`�揈��
void Player::Draw()
{
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
void Player::OnCollision()
{
    if (m_move.x > 0.0f)m_move.x = -m_move.x;
    if (m_move.z > 0.0f)m_move.z = -m_move.z;
}
//����ł���
void Player::UpdateShot()
{
    switch (m_shotStep) {
        //���̑ł��͂���  
    case SHOT_WAIT:
        if (IsKeyTrigger('Z')) {
            m_power = 0.0f;
            m_shotStep = SHOT_KEEP;
        }
        break;
        //�L�[���͌p���� 
    case SHOT_KEEP:
        m_power += 0.1f;  //  
        if (IsKeyRelease('Z')) {
            m_shotStep = SHOT_RELEASE;
        }
        break;
        // ����ł� 
    case SHOT_RELEASE:
    {
        //  �ł��o���v�Z
        DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();
        DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
        DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
        DirectX::XMVECTOR vec = DirectX::XMVectorSubtract(vPos,vCamPos);
        vec = DirectX::XMVector3Normalize(vec);
        vec = DirectX::XMVectorScale(vec,m_power);
        DirectX::XMStoreFloat3(&m_move, vec);

        //  �ł��o����̏���ݒ�
        m_isStop = false;   //  �ړ����Ă���
        m_shotStep = SHOT_WAIT;  //  �܂��Ăёł�
        break;
    }
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
    if (IsKeyTrigger(VK_SHIFT))//����
    {
        m_bDashFlag = true;
        
    }
    if (IsKeyPress(VK_SPACE))//����
    {
        g_eState = SLOW;
    }
    if (m_bDashFlag)//�_�b�V���t���O�������Ă�����
    {
        
        m_nDashIntervalCnt++;
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


    //�ړ��֘A�̍X�V
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // �s��� z������(row[2]) �� forward �ɂȂ�
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] �� (x, y, z, w)
    // �ړ���+
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, MOVE_SPEED_BASE + m_fDashSpeed);

    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    // �ʒu���X�V
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);
}
