#include "Goal.h"
#include"Geometory.h"
#include"Player.h"
#include"Collision.h"
#include"ShaderList.h"
#include"ModelCache.h"
#define GOAL_SCALE (1.5f)
Goal::Goal()
{
}

Goal::Goal(DirectX::XMFLOAT3 InitPos):m_pPlayer(nullptr),m_pModel(nullptr),m_pCamera(nullptr),ObjectNum(0)
{
	m_pModel=ModelCache::GetInstance()->GetCache("Cloud");
	m_pos = InitPos;
	Scale = { GOAL_SCALE-0.2f,GOAL_SCALE-0.2f,GOAL_SCALE-0.2f };
	m_box = { InitPos,Scale };
	m_pSetSe = LoadSound("Assets/sound/Set.mp3");
}

Goal::~Goal()
{
	m_pspeaker = nullptr;
}

void Goal::Update()
{
    if (Collision::Hit(m_box, m_pPlayer->GetCollision()).isHit)
    {
        if (m_pPlayer->GetItemNum() > 0)
        {
			m_pspeaker = PlaySound(m_pSetSe);
			m_pspeaker->SetVolume(1.0f);
			ObjectNum += m_pPlayer->GetItemNum();
            m_pPlayer->SetItemNum(m_pPlayer->GetItemNum() - m_pPlayer->GetItemNum());
        }
    }
	m_box = { m_pos,Scale };
	if (30>ObjectNum&&ObjectNum > 20)
	{
		Scale = { GOAL_SCALE-0.1f,GOAL_SCALE-0.1f,GOAL_SCALE-0.1f };
		m_box = { m_pos,Scale };
	}
	else if (40 > ObjectNum && ObjectNum > 30)
	{
		Scale = { GOAL_SCALE,GOAL_SCALE,GOAL_SCALE };
		m_box = { m_pos,Scale };
	}
	else if (ObjectNum > 40)
	{
		Scale = { GOAL_SCALE+0.1f,GOAL_SCALE+0.1f,GOAL_SCALE+0.1f };
		m_box = { m_pos,Scale };
	}
	
}

void Goal::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D�\���ɂȂ�
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S =
		DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.z)); // ��]
	DirectX::XMMATRIX mat = S * R * T;
	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(mat));
	////���_�V�F�[�_�[�ɓn���ϊ��s����쐬
	DirectX::XMMATRIX world, view, proj;
	//DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	//DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));
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
		material.diffuse.x = 1.0f;
		material.diffuse.y = 1.0f;
		material.diffuse.z = 5.0f;
		ShaderList::SetMaterial(material);
		//���f���̕`��
		m_pModel->Draw(i);
	}
}
