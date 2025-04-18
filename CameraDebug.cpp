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

//  �v���C���[�ʒu
	m_look = m_pPlayer->GetPos();
	XMFLOAT3 playerPos = m_pPlayer->GetPos();
	XMVECTOR vPlayerPos = XMLoadFloat3(&playerPos);

	float yaw = XMConvertToRadians(m_pPlayer->GetRotation().z);
	float pitch = XMConvertToRadians(m_pPlayer->GetRotation().x);

	
	// �N�H�[�^�j�I������
	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(pitch, yaw, 0.0f);
	// ��]�s��ɕϊ�
	XMMATRIX rot = XMMatrixRotationQuaternion(quat);

	//�J�����̈ʒu(�v���C���[�̌��)��offsetBase�Ɋi�[
	XMVECTOR offsetBase = XMVectorSet(0.0f, 1.0f, -m_radius, 0.0f);//x,y,z

	//offsetBase ����]�����s���offsetrotated�Ɋi�[
	XMVECTOR offsetRotated = XMVector3TransformCoord(offsetBase, rot);

	// �ŏI�I�ȃJ�������W = �v���C���[���W + ��]��I�t�Z�b�g
	XMVECTOR vCamPos = XMVectorAdd(vPlayerPos, offsetRotated);
	XMStoreFloat3(&m_pos, vCamPos);




	if (m_radius < 0.1f) m_radius = 0.1f;//0�̓G���[
	//m_pos.x = cos(DirectX::XMConvertToRadians(m_radY)) * sin(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.x;
	//m_pos.y = sin(DirectX::XMConvertToRadians(m_radY)) * m_radius + m_look.y;
	//m_pos.z = cos(DirectX::XMConvertToRadians(m_radY)) * cos(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.z;

}
DirectX::XMFLOAT4X4 CameraDebug::GetViewMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;

	//�v���C���[�̊p�x�i�N�H�[�^�j�I����]�p�j
	float pitch = XMConvertToRadians(m_pPlayer->GetRotation().x);
	float yaw = XMConvertToRadians(m_pPlayer->GetRotation().z);
	float roll = XMConvertToRadians(m_pPlayer->GetRotation().y);

	//�N�H�[�^�j�I���쐬
	XMVECTOR quat = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	XMMATRIX rot = XMMatrixRotationQuaternion(quat);

	//�J�����ʒu�E�����_�i���v���C���[�j
	XMVECTOR vEye = XMLoadFloat3(&m_pos);
	XMVECTOR vTarget = XMLoadFloat3(&m_look);

	//�����iforward�j�� up ����]�s�񂩂璼�ڎ��o��
	XMVECTOR forward = XMVector3Normalize(XMVectorSubtract(vTarget, vEye));
	XMVECTOR up = rot.r[1]; // �N�H�[�^�j�I���R����Y��
	
	XMMATRIX view = XMMatrixLookToLH(vEye, forward, up);

	if (transpose) {
		view = XMMatrixTranspose(view);
	}
	XMStoreFloat4x4(&mat, view);
	return mat;
}