#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include"Model.h"
#include"Camera.h"
#include"CameraDebug.h"
#include"Player.h"
#include"Scene.h"
#include"Texture.h"
class StageObjectManager;

class SceneGame :public Scene 
{
public:
	SceneGame();
	~SceneGame();
	void Update();
	void Draw();

private:
	Model* m_pModel;
	CameraDebug* m_pCamera;
	Player* m_pPlayer;
	StageObjectManager* m_pStageObjectManager;
	Texture* m_pTexture;
	int StartTimer;
	int Framecnt;
	bool StartFlag;
};

#endif // __SCENE_GAME_H__