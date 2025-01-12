#pragma once
#include "GameObject.h"
#include"CameraDebug.h"
class Model;
class TrashObject :public GameObject
{
public:
	TrashObject();
	TrashObject(DirectX::XMFLOAT3 InitPos,int InitRotation);
	~TrashObject();
	void Update()override;
	void Draw()override;
	void SetCamera(CameraDebug* InCamera) { m_pCamera = InCamera; }
private:
	Model* m_pModel;
	CameraDebug* m_pCamera;
	int m_nRotationFlag;
	int m_nRotationcnt;
};

