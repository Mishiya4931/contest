#pragma once
#include "Texture.h" 
#include "Sprite.h" 
class GaugeUI
{
public:
	GaugeUI();
	~GaugeUI();
	void Update();
	void Draw();
	// ゲージ量の設定 
	void SetGauge(float rate) {
		m_rate = rate;
	}
private:
	Texture* m_pFrameTex;// フレームのテクスチャ 
	Texture* m_pGaugeTex;// ゲージのテクスチャ 
	float m_rate;// ゲージ量 

};



