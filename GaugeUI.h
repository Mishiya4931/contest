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
	// �Q�[�W�ʂ̐ݒ� 
	void SetGauge(float rate) {
		m_rate = rate;
	}
private:
	Texture* m_pFrameTex;// �t���[���̃e�N�X�`�� 
	Texture* m_pGaugeTex;// �Q�[�W�̃e�N�X�`�� 
	float m_rate;// �Q�[�W�� 

};



