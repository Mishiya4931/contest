#include "SceneTitle.h"
#include"Input.h"
#include"Defines.h"
SceneTitle::SceneTitle() : m_pLogo(nullptr)
{
	m_pLogo = new Texture();
	if (FAILED(m_pLogo->Create("Assets/texture/TitleScene.jpg")))
		MessageBox(NULL, "Load failed SceneTitle.", "Error", MB_OK);
}

SceneTitle::~SceneTitle()
{
	if (m_pLogo) {
		delete m_pLogo;
		m_pLogo = nullptr;
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
	// フェードの表示設定 
	Sprite::SetVP();
	Sprite::SetTexture(m_pLogo);
	Sprite::SetSize({ SCREEN_WIDTH,SCREEN_HEIGHT});
	Sprite::SetOffset({ 0.0f, 0.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
}
