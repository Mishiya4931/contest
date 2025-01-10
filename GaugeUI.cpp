#include "GaugeUI.h"
#include"Defines.h"
GaugeUI::GaugeUI() : m_pFrameTex(nullptr), m_pGaugeTex(nullptr), m_rate(0.1f)
{
	
		// 枠部分のテクスチャを読み込み 
		m_pFrameTex = new Texture();
		if (FAILED(m_pFrameTex->Create("Assets/texture/UIFrame.png"))) {
			MessageBox(NULL, "Texture load failed.¥nUI.cpp", "Error", MB_OK);
		}
		// ゲージ
		m_pGaugeTex = new Texture();
		if (FAILED(m_pGaugeTex->Create("Assets/texture/UIGauge.png"))) {
			MessageBox(NULL, "Texture load failed.¥nUI.cpp", "Error", MB_OK);
		}

}

GaugeUI::~GaugeUI()
{
	if (m_pFrameTex) {
		delete m_pFrameTex;
		m_pFrameTex = nullptr;
	}
	if (m_pGaugeTex) {
		delete m_pGaugeTex;
		m_pGaugeTex = nullptr;
	}
}

void GaugeUI::Update()
{
}

void GaugeUI::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();// ディスプレイ情報の取得
	DepthStencil* pDSV = GetDefaultDSV(); // 深度バッファの取得
	// 2D表示の設定 
	SetRenderTargets(1, &pRTV, nullptr);
	// スプライトの表示に必要な行列を計算 
	DirectX::XMFLOAT4X4 world, view, proj;
	DirectX::XMMATRIX mView =
		DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		);
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT) ,0.0f, CMETER(30.0f), METER(2.0f));
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(mProj));

	Sprite::SetView(view);
	Sprite::SetProjection(proj);

	// フレームとゲージの描画 
	DirectX::XMFLOAT2 pos = { SCREEN_WIDTH/2,600.0f };
	DirectX::XMFLOAT2 size[] = {
	 {210.0f, 40.0f}, {200.0f, 30.0f}  // フレームを大きめに設定 
	};
	Texture* pTex[] = { m_pFrameTex, m_pGaugeTex };
	for (int i = 0; i < 2; ++i) {
		DirectX::XMMATRIX T =
			DirectX::XMMatrixTranslation(pos.x - size[i].x * 0.5f, pos.y, 0.0f);
		DirectX::XMMATRIX S;
		if (i == 0) // フレームは倍率を変更せずに表示 
			S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
		else   // ゲージは横方向をm_rateに応じて拡縮 
			S = DirectX::XMMatrixScaling(m_rate, -0.75f, 1.0f);
		DirectX::XMMATRIX mWorld = S * T;
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));

		Sprite::SetWorld(world);       // スプライトのワールド行列を設定 
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f});
		Sprite::SetSize(size[i]);      // スプライトのサイズを設定 
		Sprite::SetOffset({ size[i].x * 0.5f, 0.0f }); // スプライトの原点を変更 
		Sprite::SetTexture(pTex[i]);      // テクスチャを設定 
		Sprite::Draw();
	}
	// 3D表示の設定 
	SetRenderTargets(1, &pRTV, pDSV);
}
