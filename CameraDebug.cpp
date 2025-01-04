#include "CameraDebug.h"
using namespace DirectX;
CameraDebug::CameraDebug() : m_radXZ(0.0f), m_radY(15.0f), m_radius(4.0f)
{
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	//�����_�̈ړ� 
	//if (IsKeyPress(VK_UP)) { m_look.z += 1.0f; }
	//if (IsKeyPress(VK_DOWN)) { m_look.z += -1.0f; }
	//if (IsKeyPress(VK_LEFT)) { m_look.x += -1.0f; }
	//if (IsKeyPress(VK_RIGHT)) { m_look.x += 1.0f; }
	//if (IsKeyPress(VK_SHIFT)) { m_look.y += 1.0f; }
	//if (IsKeyPress(VK_CONTROL)) { m_look.y += -1.0f; }
	m_look = m_pPlayer->GetPos();

	//if (IsKeyPress('A')) { m_radXZ += 1.0f; }
	//if (IsKeyPress('D')) { m_radXZ += -1.0f; }
	//if (IsKeyPress('W')) { m_radY += -1.0f; }
	//if (IsKeyPress('S')) { m_radY += 1.0f; }
	//if (IsKeyPress('Q')) { m_radius += -1.0f; }
	//if (IsKeyPress('E')) { m_radius += 1.0f; }
//  �v���C���[�ʒu
	XMFLOAT3 playerPos = m_pPlayer->GetPos();
	XMVECTOR vPlayerPos = XMLoadFloat3(&playerPos);

	float yaw = XMConvertToRadians(m_pPlayer->GetRotation().z);
	float pitch = XMConvertToRadians(m_pPlayer->GetRotation().x);
	//��]�s��(Roll,Pitch,Yaw)
	XMMATRIX rot = XMMatrixRotationRollPitchYaw(
		pitch,  // �㉺����
		yaw,    // ���E����
		0.0f
	);

	//�J�����̈ʒu(�v���C���[�̌��)
	XMVECTOR offsetBase = XMVectorSet(0.0f, 1.0f, -m_radius, 0.0f);//x,y,z

	//offsetBase ����]
	XMVECTOR offsetRotated = XMVector3TransformCoord(offsetBase, rot);

	// �ŏI�I�ȃJ�������W = �v���C���[���W + ��]��I�t�Z�b�g
	XMVECTOR vCamPos = XMVectorAdd(vPlayerPos, offsetRotated);
	XMStoreFloat3(&m_pos, vCamPos);




	if (m_radius < 0.1f) m_radius = 0.1f;//0�̓G���[
	//m_pos.x = cos(DirectX::XMConvertToRadians(m_radY)) * sin(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.x;
	//m_pos.y = sin(DirectX::XMConvertToRadians(m_radY)) * m_radius + m_look.y;
	//m_pos.z = cos(DirectX::XMConvertToRadians(m_radY)) * cos(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.z;

}
