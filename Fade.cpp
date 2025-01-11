#include "Fade.h"

Fade::Fade():m_isFadeIn(false), m_time(0.0f), m_maxTime(0.0f)
{

}

void Fade::Update()
{
	if (m_time > 0.0f) {  // 毎フレーム判定 
		m_time -= 1.0f / 60.0f;
		if (m_time < 0.0f)  // フェードが終了すると呼び出されなくなるので、少しだけ効率がよい 
			m_time = 0.0f;
	}
}

void Fade::Draw()
{
	if (IsFadeIn())
		DrawFadeIn(GetAlpha());
	else
		DrawFadeOut(GetAlpha());
}

void Fade::Start(bool isIn)
{
	m_isFadeIn = isIn;
	m_time = m_maxTime;
}

void Fade::SetFade(float time, bool isIn)
{
	m_isFadeIn = isIn;
	m_time = time;
	m_maxTime = time;
}
