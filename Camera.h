#pragma once
#include<DirectXMath.h>
class Camera
{
public:
	//  �R���X�g���N�^
	Camera();

	//  �f�X�g���N�^
	virtual ~Camera();
	//  �X�V�����i�p����̃N���X�ŕK�������j
	virtual void Update() = 0;
	//  �r���[�s��̎擾�i�f�t�H���g�ł͓]�u�ς݂̍s����v�Z����j
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);
	//�v���W�F�N�V�����s��̎擾�i�f�t�H���g�ł͓]�u�ς݂̍s����v�Z����j
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);
	//  ���W�̎擾
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	//  �����_�̎擾
	DirectX::XMFLOAT3 GetLook() { return m_look; }

protected:
	DirectX::XMFLOAT3 m_pos;  //  ���W
	DirectX::XMFLOAT3 m_look;  //  �����X
	DirectX::XMFLOAT3 m_up;  //  ����x�N�g��
	float m_fovy;  //  
	float m_aspect; // �A�X�y�N�g��
	float m_near;  //  �j�A�N���b�v
	float m_far;  //  �t�@�[�N���b�v
};
