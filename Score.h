#pragma once
#include"Sound.h"
class Texture;
class Score
{
private:
	Score();
	~Score();
public:
	static void Init();
	static void Uninit();
	static void Reset();
	static Score* GetInstanse() {
		return Instanse;
	}
	void Update();
	void Draw();
	void SetScore(int InScore) { m_nScore = InScore; }
	int GetScore() { return m_nScore; }
private:
	static int cnt;
	static bool m_bResultFlg;
	static Score* Instanse;
	int m_nScore;
	Texture* m_pTexture;
	Texture* m_pScoreTexture;
	Texture* m_pScore1;
	Texture* m_pScore2;
	Texture* m_pScore3;
	IXAudio2SourceVoice* m_pSEspeaker;
	IXAudio2SourceVoice* m_pAnnounceSEspeaker;
	IXAudio2SourceVoice* m_pExcellentSEspeaker;
	XAUDIO2_BUFFER* m_pDrumrollSe;
	XAUDIO2_BUFFER* m_pAnnounceSe;
	XAUDIO2_BUFFER* m_pExcellAnnounceSe;
	XAUDIO2_BUFFER* m_pExcellentSe;
	XAUDIO2_BUFFER* m_pSosoSe;
	static bool m_bSoundFlag;
	static bool m_bDrumSoundFlag;
};

