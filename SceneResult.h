#pragma once
#include"Scene.h"
#include"Texture.h"
#include"Sound.h"
class CameraResult;
class SceneResult:public Scene
{
public:
	SceneResult();
	~SceneResult();
	void Update();
	void Draw();
private:
	CameraResult* m_pCamera;
	Texture* m_pTexture;
	IXAudio2SourceVoice* m_pspeaker;
	IXAudio2SourceVoice* m_pSEspeaker;
	XAUDIO2_BUFFER* m_pBgm;
	XAUDIO2_BUFFER* m_pSe;
	XAUDIO2_BUFFER* m_pDrumrollSe;
	XAUDIO2_BUFFER* m_pAnnounceSe;
	XAUDIO2_BUFFER* m_pExcellAnnounceSe;
	XAUDIO2_BUFFER* m_pExcellentSe;
	XAUDIO2_BUFFER* m_pSosoSe;
};

