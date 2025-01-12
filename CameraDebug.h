#pragma once
#include "Camera.h" 
#include "Input.h" 
#include"Player.h"

class CameraDebug:public Camera
{
public:
	CameraDebug();
	~CameraDebug();
	void Update()final;
	void SetPlayer(Player* Inplayer) { m_pPlayer = Inplayer; }
private:
	Player* m_pPlayer;
	float m_radXZ;
	float m_radY;
	float m_radius; //  
};