#include "Scene.h"

Scene::Scene() : m_pFade(nullptr), m_next(-1),ChangeFlag(false)
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
	if (m_pFade) {
		if(m_pFade->IsFinish() && m_pFade->IsFadeOut())ChangeFlag=false;
		return m_pFade->IsFinish() && m_pFade->IsFadeOut();
	}
	return false;
}

void Scene::SetNext(int next)
{
	if (!ChangeFlag) 
	{
		ChangeFlag = true;
		m_next = next;
		// 切り替え先が発生した際にフェードも実行 
		if (m_pFade)
			m_pFade->Start(false);
	}
}
