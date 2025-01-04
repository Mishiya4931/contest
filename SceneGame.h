#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include"Model.h"
#include"Camera.h"
#include"CameraDebug.h"
#include"Player.h"
class SceneGame
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
};

#endif // __SCENE_GAME_H__