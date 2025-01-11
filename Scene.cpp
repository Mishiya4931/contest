#include "Scene.h"

Scene::Scene() : m_pFade(nullptr), m_next(-1)
{

}

Scene::~Scene()
{
	m_pFade = nullptr;
}

void Scene::RootUpdate()
{
	Update();
	if (m_pFade)
		m_pFade->Update();
}

void Scene::RootDraw()
{
	Draw();
	if (m_pFade)
		m_pFade->Draw();
}

bool Scene::ChangeScene()
{
	if (m_pFade)
		return m_pFade->IsFinish() && m_pFade->IsFadeOut();
	return false;
}

void Scene::SetNext(int next)
{
	m_next = next;
	// �؂�ւ��悪���������ۂɃt�F�[�h�����s 
	if (m_pFade)
		m_pFade->Start(false);
}
