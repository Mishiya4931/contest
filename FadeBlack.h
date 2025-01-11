#pragma once
#include "Fade.h"
#include"Texture.h"
#include"Sprite.h"
class FadeBlack :public Fade
{
public:
	FadeBlack();
	~FadeBlack() final;

	// �t�F�[�h�C���E�t�F�[�h�A�E�g���ɓ��������Ŏ��� 
	void DrawFadeIn(float alpha) final { DrawFade(alpha); }
	void DrawFadeOut(float alpha) final { DrawFade(alpha); }

	// ���ʃt�F�[�h���� 
	void DrawFade(float alpha);

private:
	Texture* m_pTexture; // �t�F�[�h���ɕ\������摜 
};
