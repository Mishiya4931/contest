#pragma once
#include"Camera.h"
class CameraResult:public Camera
{
public:
	CameraResult();
	~CameraResult();
	void Update()final;
private:
	float m_radXZ;
	float m_radY;
	float m_radius;
};

