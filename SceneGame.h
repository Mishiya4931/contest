#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include"Model.h"
#include"Camera.h"
#include"CameraDebug.h"
#include"Player.h"
#include"Scene.h"
#include"Texture.h"
#include"Sound.h"
#include"Minimap.h"
#include"CameraMinimap.h"
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
	Camera* m_pCamera[2];
	CameraDebug* m_pDebugCamera;
	Player* m_pPlayer;
	StageObjectManager* m_pStageObjectManager;
	Texture* m_pTexture;
	int StartTimer;
	int Framecnt;
	bool StartFlag;
	IXAudio2SourceVoice* m_pspeaker;
	XAUDIO2_BUFFER* m_pBgm;
	Minimap* m_pMinimap;
	CameraMinimap* pCamMinimap;
};

#endif // __SCENE_GAME_H__