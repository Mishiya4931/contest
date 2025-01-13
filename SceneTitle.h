#pragma once
#include "Scene.h"
#include "Texture.h"
#include"Sprite.h"
#include"Sound.h"
class SceneTitle :public Scene
{
public:
	SceneTitle();
	~SceneTitle();

	// �X�V���� 
	void Update() final;

	// �`�揈�� 
	void Draw() final;

private:
	Texture* m_pTitle; // �^�C�g����ʂɕ\������摜 
	Texture* m_pLogo; // �^�C�g����ʂɕ\������摜 
	Texture* m_pEnter; // �^�C�g����ʂɕ\������摜 
	IXAudio2SourceVoice* m_pspeaker;
	IXAudio2SourceVoice* m_pspeaker2;
	XAUDIO2_BUFFER* m_pBgm;
	XAUDIO2_BUFFER* m_pSe;
};

