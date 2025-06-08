#pragma once
#include"Collision.h"
#include"GameObject.h"

enum WallType
{
	WALL_UP = 0,
	WALL_DOWN,
	WALL_LEFT,
	WALL_RIGHT,
	WALL_FRONT,
	WALL_BACK
};
#define WALL_POSITION (10.5f)
#define WALL_NUM (6)
class Wall : public GameObject
{
public:
	Wall();
	Wall(DirectX::XMFLOAT3 InitPos, DirectX::XMFLOAT3 InitRotation, DirectX::XMFLOAT3 InitSize,int No);
	~Wall();
	void Update();
	void Draw();
	int GetNo() { return m_nNo; }
private:
	int m_nNo;
};

