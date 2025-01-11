#include "FadeBlack.h"
#include "Defines.h"
FadeBlack::FadeBlack() : m_pTexture(nullptr)
{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/texture/Fade.png")))
		MessageBox(NULL, "Load failed FadeBlack.", "Error", MB_OK);
}

FadeBlack::~FadeBlack()
{
	if (m_pTexture) {
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void FadeBlack::DrawFade(float alpha)
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f);
	DirectX::XMMATRIX S;
	S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);
	DirectX::XMMATRIX mWorld = S * T;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mWorld));
	// フェードの表示設定 
	Sprite::SetWorld(world);
	Sprite::SetVP();
	Sprite::SetTexture(m_pTexture);
	Sprite::SetSize({SCREEN_WIDTH,SCREEN_HEIGHT});
	Sprite::SetOffset({ 0.0f, 0.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, alpha }); // 引数のアルファを元に透明度を設定 
	Sprite::Draw();
}
