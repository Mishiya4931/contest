#pragma once
#include "GameObject.h"
#include"CameraDebug.h"
class Model;
class SkyDome:public GameObject
{
public:
   SkyDome();
    ~SkyDome();
    void Update();
    void Draw();
private:
    Model* m_pModel;
public:
	void SetCamera(CameraDebug* InCamera) { m_pCamera = InCamera; }
	void SetPosition(DirectX::XMFLOAT3 InPos) { m_pos = InPos; }
private:
	CameraDebug* m_pCamera;
	DirectX::XMFLOAT3 m_Scale;
};

