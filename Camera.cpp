#include "Camera.h"
#include"Defines.h"
#define PAI (3.141592f)
#define ANGLE(a) PAI/180.0f*a
using namespace DirectX;
Camera::Camera() : m_pos(0.0f,0.0f,METER(-5.0f)), m_look(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f)
, m_fovy(ANGLE(60.0f)), m_aspect(16.0f / 9.0f)
, m_near(CMETER(30.0f)), m_far(METER(1000.0f)) 
{

}
Camera::~Camera()
{
}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix(bool transpose)
{

		DirectX::XMFLOAT4X4 mat;
		XMVECTOR eye = XMLoadFloat3(&m_pos);
		XMVECTOR target = XMLoadFloat3(&m_look);

		// forward = �����Ă�����i�����x�N�g���j
		XMVECTOR forward = XMVector3Normalize(XMVectorSubtract(target, eye));


		// ���S�ȉ�up�iforward�ƕ��s�ɂȂ�Ȃ������Ȏ���I�ԁI�j
		XMVECTOR baseUp = fabs(XMVectorGetY(forward)) > 0.99f
			? XMVectorSet(0, 0, 1, 0) // Y���ɋ߂�������Z���g��
			: XMVectorSet(0, 1, 0, 0); // �ʏ��Y��

		// right�i�������j���v�Z�iforward��baseUp�̊O�ρj
		XMVECTOR right = XMVector3Normalize(XMVector3Cross(baseUp, forward));

		// new up = forward��right�̊O�ρi�����j
		XMVECTOR newUp = XMVector3Cross(forward, right);

		// �ŏI�r���[�s�������ō��I�I
		XMMATRIX view = XMMatrixLookAtLH(eye, target, newUp);

		if (transpose) {
			view = DirectX::XMMatrixTranspose(view);
		}
		DirectX::XMStoreFloat4x4(&mat, view);
		return mat;
	
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);

	if (transpose) {
		proj = DirectX::XMMatrixTranspose(proj);
	}
	DirectX::XMStoreFloat4x4(&mat, proj);
	return mat;
}