#pragma once
#include "Scene.h"
#include "Texture.h"
#include"Sprite.h"
class SceneTitle :public Scene
{
public:
	SceneTitle();
	~SceneTitle();

	// �X�V���� 
	void Update() final;

	// �`�揈�� 
	void Draw() final;

private:
	Texture* m_pLogo; // �^�C�g����ʂɕ\������摜 
};

