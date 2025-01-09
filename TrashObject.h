#pragma once
#include "GameObject.h"
class TrashObject :public GameObject
{
public:
	TrashObject();
	TrashObject(DirectX::XMFLOAT3 InitPos);
	~TrashObject();
	void Update()override;
	void Draw()override;
private:
};

