#include "TrashObject.h"
#include"Geometory.h"
#include"ModelCache.h"
#include"Model.h"
#include"ShaderList.h"
TrashObject::TrashObject()
{

}

TrashObject::TrashObject(DirectX::XMFLOAT3 InitPos, int InitRotation) :
	GameObject(InitPos), m_pModel(nullptr), m_nRotationcnt(0),
	m_nRotationFlag(InitRotation), m_bDeleteFlag(false), m_bDeletePrepareFlag(false)
{
	m_pModel = ModelCache::GetInstance()->GetCache("Cloud");
    m_box = {
DirectX::XMFLOAT3(m_pos),
DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
	m_Scale = { 1.0f,1.0f,1.0f };
}

TrashObject::~TrashObject()
{
}

void TrashObject::Update()
{
	if (m_nRotationFlag % 2)
	{
		m_Rotation.y += 1.0f;
	}
	else{
		m_Rotation.y -= 1.0f;
	}
	
	if (m_Rotation.y> 360.0f)
	{
		m_Rotation.y = m_Rotation.y - 360.0f;
	}
	if (m_nRotationcnt < 0)
	{
		m_Rotation.y = m_Rotation.y + 360.0f;
	}
	if (m_bDeletePrepareFlag)
	{
		m_Scale.x += -0.1f;
		m_Scale.y += -0.1f;
		m_Scale.z += -0.1f;
		if (m_Scale.x < 0.0f)m_Scale.x = 0.0f;
		if (m_Scale.y < 0.0f)m_Scale.y = 0.0f;
		if (m_Scale.z < 0.0f) { 
			m_Scale.z = 0.0f; 
			m_bDeleteFlag = true;
		}
	}
}

void TrashObject::Draw()
{
    RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
    DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
    SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D表示になる
    DirectX::XMFLOAT4X4 wvp[3];
    DirectX::XMMATRIX T =
        DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    DirectX::XMMATRIX S =
        DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.y)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.z)); // 回転
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(mat));
	////頂点シェーダーに渡す変換行列を作成
	DirectX::XMMATRIX world, view, proj;
	//DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	//DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();

	// シェーダーへの変換行列を設定
	ShaderList::SetWVP(wvp);

	//// モデルに使用する頂点シェーダー、ピクセルシェーダーを設定
	m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));



	for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
		//モデルのメッシュを取得
		const Model::Mesh* mesh = m_pModel->GetMesh(i);
		//メッシュに割り当てられているマテリアル取得
		Model::Material material = *m_pModel->GetMaterial(mesh->materialID);
		//シェーダーへマテリアルを設定
		material.ambient = { 0.8f,0.8f,0.8f,1.0f };
		ShaderList::SetMaterial(material);
		//モデルの描画
		m_pModel->Draw(i);
	}
}
