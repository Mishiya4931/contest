#pragma once
#include "Scene.h"
#include "Texture.h"
#include"Sprite.h"
class SceneTitle :public Scene
{
public:
	SceneTitle();
	~SceneTitle();

	// 更新処理 
	void Update() final;

	// 描画処理 
	void Draw() final;

private:
	Texture* m_pLogo; // タイトル画面に表示する画像 
};

