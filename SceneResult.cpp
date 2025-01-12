#include "SceneResult.h"
#include"Score.h"
#include"Input.h"
#include"CameraResult.h"
SceneResult::SceneResult():m_pCamera(nullptr)
{
	m_pCamera = new CameraResult();
}

SceneResult::~SceneResult()
{
	delete m_pCamera;
	m_pCamera = nullptr;
}

void SceneResult::Update()
{
	if (IsKeyTrigger(VK_RETURN))
	{
		SetNext(0);
	}
	Score::GetInstanse()->Update();
}

void SceneResult::Draw()
{
	Score::GetInstanse()->Draw();
}
