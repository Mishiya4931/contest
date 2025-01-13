#include "Timer.h"
#include"Texture.h"
#include"Sprite.h"
#include"Defines.h"
#define INIT_TIMER (60)
#define TIMER_SPRITE_SPRIT_X (5.0f)
#define TIMER_SPRITE_SPRIT_Y (2.0f)
Timer::Timer():m_nTimeCnt(INIT_TIMER)
{
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
}

Timer::~Timer()
{
}

void Timer::Update()
{
	static int cnt = 0;
	if(cnt>60){//一秒(60フレーム)に一回タイマーを減らす

		if(m_nTimeCnt>0)m_nTimeCnt--;
		cnt = 0;
	}
	cnt++;
}

void Timer::Draw()
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
		0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, CMETER(30.0f), METER(2.0f));
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(mProj));
	Sprite::SetView(view);
	Sprite::SetProjection(proj);
	//=======タイマー1の位====
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(700.0f, 100.0f, 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
	DirectX::XMMATRIX mWorld = S * T;// 拡縮→回転→移動
	mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
	Sprite::SetOffset({ 0.0f, 0.0f });// 座標
	int one = m_nTimeCnt % 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (one % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / TIMER_SPRITE_SPRIT_Y * (one / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / TIMER_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
	//=======タイマー10の位==========

	T = DirectX::XMMatrixTranslation(590.0f, 100.0f, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
	mWorld = S * T;// 拡縮→回転→移動
	mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
	Sprite::SetOffset({ 0.0f, 0.0f });// 座標
	int ten = m_nTimeCnt / 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (ten % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / 2.0f * (ten / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / 2.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
	// 3D表示の設定 
	SetRenderTargets(1, &pRTV, pDSV);
	Sprite::SetUVPos({0.0f, 0.0f});
	Sprite::SetUVScale({1.0f,1.0f});
}
