#pragma once
#include<vector>
class Player;
class TrashObject;
class StageObjectManager
{
public:
	StageObjectManager();
	~StageObjectManager();
	void Update();
	void Draw();
	void SetPlayer(Player* Inplayer) { m_pPlayer = Inplayer; }
private:
	std::vector<TrashObject*> m_StageObjects;
	Player* m_pPlayer;
};

