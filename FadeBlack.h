#pragma once
#include "Fade.h"
#include"Texture.h"
#include"Sprite.h"
class FadeBlack :public Fade
{
public:
	FadeBlack();
	~FadeBlack() final;

	// フェードイン・フェードアウト共に同じ処理で実装 
	void DrawFadeIn(float alpha) final { DrawFade(alpha); }
	void DrawFadeOut(float alpha) final { DrawFade(alpha); }

	// 共通フェード処理 
	void DrawFade(float alpha);

private:
	Texture* m_pTexture; // フェード中に表示する画像 
};
