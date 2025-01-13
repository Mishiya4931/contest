#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "ShaderList.h" 
#include"EffectM.h"
#include"DirectX.h"
#include"Player.h"
#include"StageObjectManager.h"
#include"GaugeUI.h"
#include"timer.h"
#include"Score.h"
#include"CameraDebug.h"
#define PAI (3.141592f)
#define ANGLE(a) PAI/180.0f*a
#define TIMER_SPRITE_SPRIT_X (5.0f)
#define TIMER_SPRITE_SPRIT_Y (2.0f)

EffectM* g_pEffekseerM;
Timer* g_pTimer;
SceneGame::SceneGame() :
	m_pCamera(nullptr),
	m_pModel(nullptr),
	m_pPlayer(nullptr),
	m_pStageObjectManager(nullptr),
	StartFlag(false),
	Framecnt(0),
	StartTimer(3)
{
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
	m_pStageObjectManager = new StageObjectManager();
	m_pCamera = new CameraDebug();
	m_pPlayer = new Player();
	m_pStageObjectManager->SetPlayer(m_pPlayer);
	m_pStageObjectManager->SetCamera(m_pCamera);
	m_pCamera->SetPlayer(m_pPlayer);
	m_pPlayer->SetCamera(m_pCamera);
	m_pPlayer->SetWall(m_pStageObjectManager->GetWall());
	g_pTimer = new Timer();

	m_pBgm = LoadSound("Assets/sound/MainBgm.mp3",true);
	m_pspeaker = PlaySound(m_pBgm);
	m_pspeaker->SetVolume(0.5f);
}

SceneGame::~SceneGame()
{
if (m_pCamera) {
	delete m_pCamera;
	m_pCamera = nullptr;
	}
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (g_pEffekseerM)
	{
		delete g_pEffekseerM;
		g_pEffekseerM = nullptr;
	}
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pStageObjectManager);
	SAFE_DELETE(g_pTimer);
	SAFE_DELETE(m_pTexture);
	m_pspeaker->Stop(0);
}

void SceneGame::Update()
{


		m_pCamera->Update();
	if (StartFlag)
	{
		m_pStageObjectManager->Update();
		//g_pEffekseerM->Update();
		m_pPlayer->Update();
		g_pTimer->Update();
		if (g_pTimer->GetTime() < 1) {
			Score::GetInstanse()->SetScore(m_pStageObjectManager->GetStageObjectCnt());
			SetNext(2);
		}//デバッグ
	}
	else
	{
		if (Framecnt > 60)
		{
			StartTimer--;
			Framecnt = 0;
		}
		if (StartTimer < 1)
		{
			StartFlag = true;
		}
		Framecnt++;
	}
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pStageObjectManager->Draw();


	RenderTarget* pRTV = GetDefaultRTV();// ディスプレイ情報の取得
	DepthStencil* pDSV = GetDefaultDSV(); // 深度バッファの取得
	// 2D表示の設定 
	SetRenderTargets(1, &pRTV, nullptr);
	// スプライトの表示に必要な行列を計算 
	DirectX::XMFLOAT4X4 world4x4, view4x4, proj4x4;
	DirectX::XMMATRIX mView =
		DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		);
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, CMETER(30.0f), METER(2.0f));
	DirectX::XMStoreFloat4x4(&view4x4, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj4x4, DirectX::XMMatrixTranspose(mProj));
	Sprite::SetView(view4x4);
	Sprite::SetProjection(proj4x4);
	//=======タイマー1の位====
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
	DirectX::XMMATRIX mWorld = S * T;// 拡縮→回転→移動
	mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
	DirectX::XMStoreFloat4x4(&world4x4, mWorld);
	Sprite::SetWorld(world4x4);
	Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
	Sprite::SetOffset({ 0.0f, 0.0f });// 座標
	int one = StartTimer % 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (one % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / TIMER_SPRITE_SPRIT_Y * (one / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / TIMER_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	if (!StartFlag) {
		Sprite::Draw();
	}









	pRTV = GetDefaultRTV(); // RenderTargetView 
	pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D表示になる
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());
	
	T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, 1.0f,1.0f);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転
	DirectX::XMMATRIX mat = S * R * T;//それぞれの行列を掛け合わせて格納;
	//CPUからGPUに行列を送る前に実行する処理;

	////頂点シェーダーに渡す変換行列を作成
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world, view, proj;
	world = mat;
	//計算用のデータから読み取り用のデータに変換 
	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	//DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	//DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();
	// シェーダーへの変換行列を設定
	ShaderList::SetWVP(wvp); 
	//// モデルに使用する頂点シェーダー、ピクセルシェーダーを設定
	//m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));

	// 複数のメッシュで構成されている場合、ある部分は金属的な表現、ある部分は非金属的な表現と
	// 分ける場合がある。前回の表示は同じマテリアルで一括表示していたため、メッシュごとにマテリアルを
	// 切り替える。
	g_pTimer->Draw();
}
