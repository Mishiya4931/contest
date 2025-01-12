#include "SceneTitle.h"
#include"Input.h"
#include"Defines.h"
#include"Score.h"
SceneTitle::SceneTitle() : m_pLogo(nullptr)
{
	m_pLogo = new Texture();
	m_pTitle = new Texture();
	m_pEnter = new Texture();

	Score::Reset();
	if (FAILED(m_pTitle->Create("Assets/texture/Title.png")))
		MessageBox(NULL, "Load failed SceneTitle.", "Error", MB_OK);
if (FAILED(m_pLogo->Create("Assets/texture/TitleLogo.png")))
		MessageBox(NULL, "Load failed SceneTitle.", "Error", MB_OK);
if (FAILED(m_pEnter->Create("Assets/texture/PressEnter.png")))
		MessageBox(NULL, "Load failed SceneTitle.", "Error", MB_OK);
}

SceneTitle::~SceneTitle()
{
	if (m_pLogo) {
		delete m_pLogo;
		m_pLogo = nullptr;
	}	
	if (m_pTitle) {
		delete m_pTitle;
		m_pTitle = nullptr;
	}	
	if (m_pEnter) {
		delete m_pEnter;
		m_pEnter = nullptr;
	}
}

void SceneTitle::Update()
{
	if (IsKeyTrigger(VK_RETURN))SetNext(1); // 切り替え先のシーンを設定（１はゲーム 
}

void SceneTitle::Draw()
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f);
	DirectX::XMMATRIX S;
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
	DirectX::XMMATRIX mWorld = S * T;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));

	Sprite::SetWorld(world);       // スプライトのワールド行列を設定 
	Sprite::SetUVPos({0.0f,0.0f});
	Sprite::SetUVScale({ 1.0f,1.0f });
	// フェードの表示設定 
	Sprite::SetVP();
	Sprite::SetTexture(m_pTitle);
	Sprite::SetSize({ SCREEN_WIDTH,SCREEN_HEIGHT});
	Sprite::SetOffset({ 0.0f, 0.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();	
	T =
		DirectX::XMMatrixTranslation(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f);
	S;
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
	mWorld = S * T;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));

	Sprite::SetWorld(world);       // スプライトのワールド行列を設定 
	// フェードの表示設定 
	Sprite::SetVP();
	Sprite::SetTexture(m_pLogo);
	Sprite::SetSize({1280.0f,320.0f});
	Sprite::SetOffset({ 0.0f, 0.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
	T =
		DirectX::XMMatrixTranslation(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+200.0f, 0.0f);
	S;
		S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
	mWorld = S * T;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));

	Sprite::SetWorld(world);       // スプライトのワールド行列を設定 
	// フェードの表示設定 
	Sprite::SetVP();
	Sprite::SetTexture(m_pEnter);
	Sprite::SetSize({1080.0f,140.0f});
	Sprite::SetOffset({ 0.0f, 0.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
}
