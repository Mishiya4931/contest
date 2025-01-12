#pragma once
#include"Scene.h"
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
};

