#pragma once
#include<DirectXMath.h>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update();
	virtual void Draw();
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	DirectX::XMFLOAT3 GetRotation() { return m_Rotation; }
protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_Rotation;
};

