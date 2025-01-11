#pragma once
class Fade
{
public:
	Fade();
	virtual ~Fade() {}

	// �X�V���� 
	void Update();

	// �`�揈�� 
	void Draw();

	// �t�F�[�h�̍ăX�^�[�g 
	void Start(bool isIn);

	// �t�F�[�h�̏����ݒ� 
	void SetFade(float time, bool isIn);

	// �t�F�[�h�I������ 
	bool IsFinish() { return m_time <= 0.0f; }

	// �t�F�[�h�C������ 
	bool IsFadeIn() { return m_isFadeIn; }

	// �t�F�[�h�A�E�g���� 
	bool IsFadeOut() { return !m_isFadeIn; }
	float GetRate() {
		if (m_maxTime == 0.0f) { return 0.0f; } // 0���Z��� 
		return m_time / m_maxTime;
	}

	// �t�F�[�h�̓����x���擾 
	float GetAlpha() {
		float alpha = GetRate();
		if (IsFadeOut()) // �t�F�[�h�A�E�g�̎������J�n���_��0�A�I�����_��1�iRate�Ƌt�̊֌W 
			alpha = 1.0f - alpha;
		return alpha;
	}

protected:
	virtual void DrawFadeIn(float alpha) {}
	virtual void DrawFadeOut(float alpha) {}
private:
	bool m_isFadeIn; // �t�F�[�h�C���t���O 
	float m_time;   // ���݂̃t�F�[�h�̌o�ߎ��� 
	float m_maxTime;  // �t�F�[�h�̍ő厞��
};


