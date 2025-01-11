#pragma once
#include "GameObject.h"
class Goal :public GameObject
{
public: 
	Goal();
	Goal(DirectX::XMFLOAT3 InitPos);
	~Goal();
	void Update();
	void Draw();
private:

};

