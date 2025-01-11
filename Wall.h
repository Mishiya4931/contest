#pragma once
#include"Collision.h"
#include"GameObject.h"

#define WALL_INNER (0)
#define WALL_UP    (1)
#define WALL_LEFT  (2)
#define WALL_RIGHT (3)
#define WALL_BACK  (4)
#define WALL_DOWN  (5)
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

