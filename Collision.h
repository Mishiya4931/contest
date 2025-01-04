#pragma once
#include <DirectXMath.h>
class Collision
{

	public:
		//--- 当たり判定の結果 
		struct Result {
			bool     isHit;  // 当たったかどうか 
			DirectX::XMFLOAT3  point;  // ヒット位置 
		};
		//--- 当たり判定の形状 
		struct Box {  // 四角 
			DirectX::XMFLOAT3  center;  // 中心座標 
			DirectX::XMFLOAT3  size;  // サイズ 
		};
		struct Sphere { // 球 
			DirectX::XMFLOAT3  center;  // 中心座標 
			float     radius;  // 半径 
		};
public:
	// 四角同士の当たり判定 
	static Result Hit(Box a, Box b);
	static Result Hit(Sphere a, Sphere b);
};

