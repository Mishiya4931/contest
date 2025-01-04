#include "Player.h"
#include"Defines.h"
enum eGolfBallShotStep {
	SHOT_WAIT,  //  ����ł̂�҂�
	SHOT_KEEP,  //  �L�[���͊J�n
	SHOT_RELEASE, //  �L�[���͂���߂��i����łj
};

Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_isStop(false),
    m_shotStep(SHOT_WAIT),
    m_power(0.0f),
    m_box({
        DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
        DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
        })
{
}

Player::~Player()
{
}
//�X�V����
void Player::Update()
{
    //�J�������ݒ肳��Ă��Ȃ��ꍇ�͏������Ȃ�
    if (!m_pCamera) { return; }
    if (IsKeyPress('A'))
    {
        m_Rotation.z -= 0.9f;
    }
    if (IsKeyPress('D'))
    {
        m_Rotation.z += 0.9f;
    }
     if (IsKeyPress('W'))
    {
        m_Rotation.x -= 0.9f;
    }
    if (IsKeyPress('S'))
    {
        m_Rotation.x += 0.9f;
    }
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // �s��� z������(row[2]) �� forward �ɂȂ�
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] �� (x, y, z, w)
    // �ړ���
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, 0.01f);

    // �ʒu���X�V
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);

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
    // �ړ����� 
    m_pos.x += m_move.x;
    m_pos.y += m_move.y;
    m_pos.z += m_move.z;

    // ��������(��C��R) 
    m_move.x *= 0.99f;
    m_move.y *= 0.99f;
    m_move.z *= 0.99f;

    //  �d��
    m_move.y -= MSEC(GRAVITY);

    //  �n�ʐڐG����
    if (m_pos.y < 0.0f) {
        // �ڐG���̌������� 
        m_move.x *= 0.95f;
        m_move.y *= 0.5f;
        m_move.z *= 0.95f;

        //  �o�E���h����
        m_move.y = -m_move.y; // Y�̈ړ������𔽓] 
        if (m_move.y < CMETER(5.0f)) { //  �o�E���h��������������
            m_move.y = 0.0f;
            m_pos.y = 0.0f;
        }
        else {
            //  �n�ʂɂ߂荞��ł���̂ŁA�o�E���h�����ꍇ�̈ʒu�ɕύX
            m_pos.y = -m_pos.y;
        }
    }
   //  ��~����
    float speed;
    DirectX::XMVECTOR vMove = DirectX::XMLoadFloat3(&m_move);
    DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vMove);
    DirectX::XMStoreFloat(&speed, vLen);  // speed��vLen���i�[ 
    if (speed < CMSEC(30.0f)) { // 1�b�Ԃ�30cm���炢�i�ރX�s�[�h�ł���Β�~ 
        m_isStop= true;
        m_shotStep = SHOT_WAIT;
    }
}
