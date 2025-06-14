#pragma once
#include <DirectXMath.h>
class Collision
{

	public:
		//--- 当たり判定形状の種類 
		enum Type {
			eNone,
			eBox,
			eSphere,
			ePlane,
			eRay,
			eLine,
			ePoint,
			eTriangle
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
		struct Point  // 点 
		{
			DirectX::XMFLOAT3 pos;  // 座標 
		};
		struct Triangle // 三角形
		{
			DirectX::XMFLOAT3 point[3]; // 各頂点 
		};
		//--- 当たり判定の形状 
		struct Plane { // 平面 
			DirectX::XMFLOAT3 pos;   // 平面上の１点 
			DirectX::XMFLOAT3 normal;  // 平面の法線 
		};
		struct Ray { // レイ(無限の直線) 
			DirectX::XMFLOAT3 origin;  // 始点 
			DirectX::XMFLOAT3 dir;  // レイの向き 
		};
		struct Line { // 線分 
			DirectX::XMFLOAT3 start;  // 線分の始点 
			DirectX::XMFLOAT3 end;  // 線分の終点 
		};
		//--- 当たり判定の統合情報 
		struct Info {
			Type type;
			union {
				Box box;
				Sphere sphere;
				Plane plane;
				Ray ray;
				Line line;
				Triangle triangle;
			};
		};
		//--- 当たり判定の結果 
		struct Result {
			bool     isHit;  // 当たったかどうか 
			DirectX::XMFLOAT3  point;  // ヒット位置 
			DirectX::XMFLOAT3  normal;  // ヒット平面 
			Info     other;  // 当たり判定オブジェクト
		};

public:
	// 四角同士の当たり判定 
	 // Info型での当たり判定 
	static Result Hit(Info a, Info b);
	static Result Hit(Box a, Box b);
	static Result Hit(Sphere a, Sphere b);
	static Result Hit(Plane plane, Ray ray, float lenght);
	static Result Hit(Plane plane, Line line);
	static Result Hit(Point point, Triangle triangle);
};

