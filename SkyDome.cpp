#include "SkyDome.h"
#include "ModelCache.h"
#include "Model.h"
#include "ShaderList.h"

SkyDome::SkyDome():m_Scale{ 1.0f,1.0f,1.0f },m_pCamera(nullptr)
{

	m_pModel = ModelCache::GetInstance()->GetCache("SkyDome");
}

SkyDome::~SkyDome()
{
}
void SkyDome::Update()
{

}
void SkyDome::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D�\���ɂȂ�
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S =
		DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.z)); // ��]
	DirectX::XMMATRIX mat = S * R * T;
	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(mat));
	////���_�V�F�[�_�[�ɓn���ϊ��s����쐬
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();

	// �V�F�[�_�[�ւ̕ϊ��s���ݒ�
	ShaderList::SetWVP(wvp);

	//// ���f���Ɏg�p���钸�_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[��ݒ�
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));



	for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
		//���f���̃��b�V�����擾
		const Model::Mesh* mesh = m_pModel->GetMesh(i);
		//���b�V���Ɋ��蓖�Ă��Ă���}�e���A���擾
		Model::Material material = *m_pModel->GetMaterial(mesh->materialID);
		//�V�F�[�_�[�փ}�e���A����ݒ�
		material.ambient = { 0.8f,0.8f,0.8f,1.0f };
		ShaderList::SetMaterial(material);
		//���f���̕`��
		m_pModel->Draw(i);
	}
}