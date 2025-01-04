#include "Collision.h"

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
    out.isHit = false;
    if (maxA.x >= minB.x && minA.x <= maxB.x) {
        if (maxA.y >= minB.y && minA.y <= maxB.y)
        {
            if (maxA.z >= minB.z && minA.z <= maxB.z)
            {
                out.isHit = true;
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
