#pragma once
#include "GameObject.h"
#include"Model.h"
#include"CameraDebug.h"
#include"Sound.h"
class Player;
class Goal :public GameObject
{
public: 
	Goal();
	Goal(DirectX::XMFLOAT3 InitPos);
	~Goal();
	void Update();
	void Draw();
	void SetPlayer(Player* InPlayer) { m_pPlayer = InPlayer; }
	void SetCamera(CameraDebug* InCamera) { m_pCamera = InCamera; }
private:
	Player* m_pPlayer;
	Model* m_pModel;
	CameraDebug* m_pCamera;
	int ObjectNum;
	DirectX::XMFLOAT3 Scale;
	IXAudio2SourceVoice* m_pspeaker;
	XAUDIO2_BUFFER* m_pSetSe;

};

