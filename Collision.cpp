#include "Collision.h"
#include<iostream>
Collision::Result Collision::Hit(Info a, Info b)
{
    Result out = {};
    if (a.type == b.type) {
        switch (a.type) {
        case eBox:  out = Hit(a.box, b.box);   break;
		case eSphere: out = Hit(a.sphere, b.sphere); break;
        }
	}
	else
	{
		if (a.type == ePlane)
		{
			if (b.type == eRay);
			else {
				out = Hit(a.plane, b.line);
			}
		}
	}
    return out;
}

Collision::Result Collision::Hit(Box a, Box b)
{
    Result out = {};
    // VECTOR型に変換 
    DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
    DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
    DirectX::XMVECTOR vSizeA = DirectX::XMLoadFloat3(&a.size);
    DirectX::XMVECTOR vSizeB = DirectX::XMLoadFloat3(&b.size);
    // ボックスの半分のサイズを取得 
    vSizeA = DirectX::XMVectorScale(vSizeA, 0.5f);
    vSizeB = DirectX::XMVectorScale(vSizeB, 0.5f);
    // ボックスの各軸の最大値、最小値を取得 
    DirectX::XMVECTOR vMaxA = DirectX::XMVectorAdd(vPosA, vSizeA);
    DirectX::XMVECTOR vMinA = DirectX::XMVectorSubtract(vPosA, vSizeA);
    DirectX::XMVECTOR vMaxB = DirectX::XMVectorAdd(vPosB, vSizeB);
    DirectX::XMVECTOR vMinB = DirectX::XMVectorSubtract(vPosB, vSizeB);
    DirectX::XMFLOAT3 maxA, minA, maxB, minB;
    DirectX::XMStoreFloat3(&maxA, vMaxA);
    DirectX::XMStoreFloat3(&minA, vMinA);
    DirectX::XMStoreFloat3(&maxB, vMaxB);
    DirectX::XMStoreFloat3(&minB, vMinB);

    // ボックスの面同士の関係から当たり判定を行う 

  // ボックスの面同士の関係から当たり判定を行う 
    out.isHit = false;
    if (maxA.x >= minB.x && minA.x <= maxB.x) {
        if (maxA.y >= minB.y && minA.y <= maxB.y) {
            if (maxA.z >= minB.z && minA.z <= maxB.z) {
                out.isHit = true;


                    // 各軸のめり込み量を計算 
                out.normal.x = std::min(maxA.x - minB.x, maxB.x - minA.x);
                out.normal.y = std::min(maxA.y - minB.y, maxB.y - minA.y) * 0.5f;
                out.normal.z = std::min(maxA.z - minB.z, maxB.z - minA.z);
                // めり込みが少ない面を当たった面とみなし、面の法線を計算する 
                if (out.normal.x < out.normal.y) {
                    if (out.normal.x < out.normal.z)
                        out.normal = DirectX::XMFLOAT3(
                            a.center.x >= b.center.x ? 1.0 : -1.0f, 0.0f, 0.0f);
                    else
                        out.normal = DirectX::XMFLOAT3(0.0f, 0.0f,
                            a.center.z >= b.center.z ? 1.0 : -1.0f);
                }
                else {
                    if (out.normal.y < out.normal.z)
                        out.normal = DirectX::XMFLOAT3(0.0f,
                            a.center.y >= b.center.y ? 1.0 : -1.0f, 0.0f);
                    else
                        out.normal = DirectX::XMFLOAT3(0.0f, 0.0f,
                            a.center.z >= b.center.z ? 1.0 : -1.0f);
                }
            }
        }
    }
    return out;
}


Collision::Result Collision::Hit(Sphere a, Sphere b)
{
    Result out = {};
    // 計算に必要なデータを計算 
    DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
    DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
    DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vPosA, vPosB);
    DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vDist);
    float length;
    DirectX::XMStoreFloat(&length, vLen);

    out.isHit = (a.radius+b.radius>=length);
    return out;
}

Collision::Result Collision::Hit(Plane plane, Ray ray, float lenght)
{
	// 計算用の型に変換 
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&ray.origin);
	DirectX::XMVECTOR vRay = DirectX::XMLoadFloat3(&ray.dir);
	// ベクトルの長さを計算 
	vRay = DirectX::XMVector3Normalize(vRay);
	vRay = DirectX::XMVectorScale(vRay, lenght);
	// 計算結果を元に線分の情報を作成 
	Line line = {};
	line.start = ray.origin;
	DirectX::XMStoreFloat3(&line.end, DirectX::XMVectorAdd(vPos, vRay));
	// 平面と直線の当たり判定を実行 
	return Hit(plane, line);
}

Collision::Result Collision::Hit(Plane plane, Line line)
{
	Result out = {};
	// 計算に必要なパラメータを定義 
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&plane.normal);
	DirectX::XMVECTOR vLineStart = DirectX::XMLoadFloat3(&line.start);
	DirectX::XMVECTOR vLineEnd = DirectX::XMLoadFloat3(&line.end);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);//正規化

	// 平面の一点から線分の始点と終点に向かうベクトルを計算 
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vLineStart, vPlanePos);
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorSubtract(vLineEnd, vPlanePos);
	DirectX::XMVECTOR vDotStart = DirectX::XMVector3Dot(vToStart, vPlaneN);//線分の始点に向かうベクトルと平面のベクトルの内積;
	DirectX::XMVECTOR vDotEnd = DirectX::XMVector3Dot(vToEnd, vPlaneN);//線分の終点に向かうベクトルと平面のベクトルの内積;

	// 各内積から平面を貫通しているか判定 
	float dotStart, dotEnd;
	DirectX::XMStoreFloat(&dotStart, vDotStart);
	DirectX::XMStoreFloat(&dotEnd, vDotEnd);

	if ((dotStart > 0.0f) && (dotEnd < 0.0f))
	{
		// 各内積の値を絶対値に変換して、衝突位置までのベクトルを計算 
		dotStart = fabsf(dotStart);
		dotEnd = fabsf(dotEnd);
		float rate = dotStart / (dotStart + dotEnd); // 衝突面までの距離の割合を計算 
		DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vLineEnd, vLineStart);
		vDist = DirectX::XMVectorScale(vDist, rate); // 線分のベクトルを衝突面までの長さに変換 
		vDist = DirectX::XMVectorAdd(vLineStart, vDist); // 始点からベクトル分移動 

		// 平面との当たり判定の結果を格納 
		out.isHit = true;
		out.normal = plane.normal;
		DirectX::XMStoreFloat3(&out.point, vDist);
	}
	return out;
}

Collision::Result Collision::Hit(Point point, Triangle triangle)
{
	Result out = {};
	// 計算用の型に変換 
	DirectX::XMVECTOR vTriPoint[3] = {
	 DirectX::XMLoadFloat3(&triangle.point[0]),
	 DirectX::XMLoadFloat3(&triangle.point[1]),
	 DirectX::XMLoadFloat3(&triangle.point[2]),
	};
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point.pos);

	// 三角形の頂点から別の頂点に向かうベクトルと、点に向かうベクトルを計算 
	DirectX::XMVECTOR vEdge[3];
	DirectX::XMVECTOR vToPoint[3];
	for (int i = 0; i < 3; ++i) {
		// 辺のベクトル 
		vEdge[i] = DirectX::XMVectorSubtract(vTriPoint[(i + 1) % 3], vTriPoint[i]);
		vEdge[i] = DirectX::XMVector3Normalize(vEdge[i]);
		// 点に向かうベクトル 
		vToPoint[i] = DirectX::XMVectorSubtract(vPoint, vTriPoint[i]);
		vToPoint[i] = DirectX::XMVector3Normalize(vToPoint[i]);
	}

	// 三角形の法線を計算 
	DirectX::XMVECTOR vNormal;
	vNormal = DirectX::XMVector3Cross(vEdge[2], vEdge[0]);//外積を使用して、2つの辺のベクトルから三角形の法線を計算
	vNormal = DirectX::XMVector3Normalize(vNormal);

	// 点が三角形の面上に存在するか判定 
	float dot[3];
	DirectX::XMStoreFloat(&dot[0], DirectX::XMVector3Dot(vNormal, vToPoint[0]));
	if (fabsf(dot[0]) > FLT_EPSILON)// FLT_EPSILON ≠ 0（ほぼ0、float型の計算誤差の値）
	{
		// 面の法線と点に向かうベクトルが垂直になってなければ平面上にない 
		return out;
	}

	// 各ベクトルの外積を計算 
	DirectX::XMVECTOR vCross[3];
	for (int i = 0; i < 3; ++i) {
		vCross[i] = DirectX::XMVector3Cross(vEdge[i], vToPoint[i]);//各辺のベクトルと点に向かうベクトルから外積を計算
	}

	// 外積のベクトルと面のベクトルが同じ方向を向いているか計算 
	for (int i = 0; i < 3; ++i) {
		DirectX::XMStoreFloat(&dot[i], DirectX::XMVector3Dot(vNormal, vCross[i]));
	}

	// 当たり判定の結果を格納 
	if ((dot[0] >= 0.0f) && (dot[1] >= 0.0f) && (dot[2] >= 0.0f)) {
		out.isHit = true;
		out.point = point.pos;
		DirectX::XMStoreFloat3(&out.normal, vNormal);
	}

	return out;
}

