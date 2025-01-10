#pragma once
#include<vector>
class Player;
class TrashObject;
class Wall;
class StageObjectManager
{
public:
	StageObjectManager();
	~StageObjectManager();
	void Update();
	void Draw();
	void SetPlayer(Player* Inplayer) { m_pPlayer = Inplayer; }
	std::vector <Wall*> GetWall(){ return m_WallObjects; }
private:
	std::vector<TrashObject*> m_StageObjects;
	std::vector <Wall*> m_WallObjects;
	Player* m_pPlayer;
};

