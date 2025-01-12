#pragma once
#include"Fade.h"
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// �V�[�����Ōp����̍X�V�����ƃt�F�[�h�̏������Ăяo�����߂̍X�V�֐� 
	void RootUpdate();

	// �V�[�����Ōp����̍X�V�����ƃt�F�[�h�̏������Ăяo�����߂̕`��֐� 
	void RootDraw();

	// �p����̃N���X�Ŏ�������X�V�����ƕ`�揈�� 
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �V�[���Ŏ��s����t�F�[�h�N���X��ݒ� 
	void SetFade(Fade* fade) { m_pFade = fade; }

	// ��{�N���X�ł́A�t�F�[�h�A�E�g�̏I�������m���ăV�[���̐؂�ւ���L���ɂ��� 
	virtual bool ChangeScene();

	// ���̐؂�ւ���V�[�����擾 
	int NextScene() { return m_next; }

	// �؂�ւ���̃V�[����ݒ� 
	void SetNext(int next);

protected:
	Fade* m_pFade; // �t�F�[�h�����N���X 
	int  m_next;  // �؂�ւ���̃V�[�� 
	bool ChangeFlag;
};

