#include "Score.h"
#include"Texture.h"
#include"Sprite.h"
#include"Defines.h"
#include<random>
Score* Score::Instanse;
bool Score::m_bResultFlg;
bool Score::m_bSoundFlag;
bool Score::m_bDrumSoundFlag;
int Score::cnt;
#define SCORE_SPRITE_SPRIT_X (5.0f)
#define SCORE_SPRITE_SPRIT_Y (2.0f)
#define SCORE_SPRITE_POS_X (740.0f)
#define SCORE_SPRITE_POS_Y (380.0f)
Score::Score():m_pTexture(nullptr)
{
	m_nScore = 0;
	cnt = 0;
	Instanse = nullptr;
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
	m_pScoreTexture = new Texture();
	m_pScoreTexture->Create("Assets/texture/ScoreTexture.png");
	m_pScore1 = new Texture();
	m_pScore1->Create("Assets/texture/Score1.png");
	m_pScore2 = new Texture();
	m_pScore2->Create("Assets/texture/Score2.png");
	m_pScore3 = new Texture();
	m_pScore3->Create("Assets/texture/Score3.png");
	m_bResultFlg = false;
	m_pDrumrollSe = LoadSound("Assets/sound/Drum.mp3", false);
	m_pAnnounceSe = LoadSound("Assets/sound/announce.mp3",false);
	m_pExcellAnnounceSe = LoadSound("Assets/sound/Excellannounce.mp3", false);
	m_pSosoSe = LoadSound("Assets/sound/Soso.mp3", false);
	m_pExcellentSe = LoadSound("Assets/sound/Excellent.mp3", false);
}

Score::~Score()
{
	m_pExcellentSEspeaker = nullptr;
	m_pAnnounceSEspeaker = nullptr;
	m_pSEspeaker = nullptr;
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pScoreTexture);
	SAFE_DELETE(m_pScore1);
	SAFE_DELETE(m_pScore2);
	SAFE_DELETE(m_pScore3);
}

void Score::Init()
{
	if (Instanse != nullptr)
	{
		return;
	}
	Instanse = new Score();

}

void Score::Uninit()
{
	if (Instanse != nullptr)
	{
		delete Instanse;
		Instanse = nullptr;
	}
}

void Score::Reset()
{
	m_bSoundFlag = false;
	m_bDrumSoundFlag = true;
	m_bResultFlg = false;
	cnt = 0;
}

void Score::Update()
{
	if (m_bDrumSoundFlag)
	{
		m_pSEspeaker = PlaySound(m_pDrumrollSe);
		m_bDrumSoundFlag = false;
	}
	if (cnt > 120)
	{
		m_pSEspeaker->Stop(0);
		m_bResultFlg = true;
	}
	cnt++;
}

void Score::Draw()
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
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(640.0f, 150.0f, 0.0f);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		DirectX::XMMATRIX mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 1080.0f, 320.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 0.0f,0.0f });
		Sprite::SetUVScale({ 1.0f,1.0f });
		Sprite::SetTexture(m_pScoreTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();





	if (m_bResultFlg) {
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X - 100.0f, SCORE_SPRITE_POS_Y + 200.0f, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 500.0f, 320.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 0.0f,0.0f });
		Sprite::SetUVScale({ 1.0f,1.0f });
		
			if (m_nScore > 30)
			{
				if (!m_bSoundFlag) {
					m_pAnnounceSEspeaker = PlaySound(m_pAnnounceSe);
					m_pExcellentSEspeaker = PlaySound(m_pSosoSe);
					m_bSoundFlag = true;
				}
				Sprite::SetTexture(m_pScore3);
			}
			else if (m_nScore > 15)
			{
				if (!m_bSoundFlag) {
					m_pAnnounceSEspeaker = PlaySound(m_pAnnounceSe);
					m_pExcellentSEspeaker = PlaySound(m_pExcellentSe);
					m_bSoundFlag = true;
				}
				Sprite::SetTexture(m_pScore2);
			}
			else if (m_nScore >= 0)
			{
				if (!m_bSoundFlag) {
					m_pAnnounceSEspeaker = PlaySound(m_pExcellAnnounceSe);
					m_pExcellentSEspeaker = PlaySound(m_pExcellentSe);
					m_bSoundFlag = true;
				}
				Sprite::SetTexture(m_pScore1);
			}
			

		
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();


		int nScoreCorrect = 40 - m_nScore;


		//一の位
		int one = nScoreCorrect % 10;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (one % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (one / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();

		//十の位
		int ten = nScoreCorrect / 10;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X - 110.0f, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (ten % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (ten / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();

		//百の位
		int tho = nScoreCorrect / 100;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X - 220.0f, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (tho % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (tho / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();
	}
	else
	{
		std::random_device Rd;//メルセンツイスタ関数
		std::mt19937 Gen(Rd());
		std::uniform_int_distribution<int> Dist(0, 100);
		//一の位
		int rnd = Dist(Gen);
		int one = rnd % 10;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (one % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (one / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();

		//十の位
		int ten = rnd / 10;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X - 110.0f, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (ten % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (ten / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();

		//百の位
		int tho = rnd / 100;
		T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X - 220.0f, SCORE_SPRITE_POS_Y, 0.0f);
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y上下反転
		mWorld = S * T;// 拡縮→回転→移動
		mWorld = DirectX::XMMatrixTranspose(mWorld);// 転置
		DirectX::XMStoreFloat4x4(&world, mWorld);
		Sprite::SetWorld(world);
		Sprite::SetSize({ 160.0f, 160.0f }); //　サイズ
		Sprite::SetOffset({ 0.0f, 0.0f });// 座標
		Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (tho % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (tho / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
		Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Sprite::Draw();



	}
}