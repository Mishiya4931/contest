#include "Collision.h"

Collision::Result Collision::Hit(Box a, Box b)
{
    Result out = {};
    // VECTOR�^�ɕϊ� 
    DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
    DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
    DirectX::XMVECTOR vSizeA = DirectX::XMLoadFloat3(&a.size);
    DirectX::XMVECTOR vSizeB = DirectX::XMLoadFloat3(&b.size);
    // �{�b�N�X�̔����̃T�C�Y���擾 
    vSizeA = DirectX::XMVectorScale(vSizeA, 0.5f);
    vSizeB = DirectX::XMVectorScale(vSizeB, 0.5f);
    // �{�b�N�X�̊e���̍ő�l�A�ŏ��l���擾 
    DirectX::XMVECTOR vMaxA = DirectX::XMVectorAdd(vPosA, vSizeA);
    DirectX::XMVECTOR vMinA = DirectX::XMVectorSubtract(vPosA, vSizeA);
    DirectX::XMVECTOR vMaxB = DirectX::XMVectorAdd(vPosB, vSizeB);
    DirectX::XMVECTOR vMinB = DirectX::XMVectorSubtract(vPosB, vSizeB);
    DirectX::XMFLOAT3 maxA, minA, maxB, minB;
    DirectX::XMStoreFloat3(&maxA, vMaxA);
    DirectX::XMStoreFloat3(&minA, vMinA);
    DirectX::XMStoreFloat3(&maxB, vMaxB);
    DirectX::XMStoreFloat3(&minB, vMinB);

    // �{�b�N�X�̖ʓ��m�̊֌W���瓖���蔻����s�� 
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
    // �v�Z�ɕK�v�ȃf�[�^���v�Z 
    DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
    DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
    DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vPosA, vPosB);
    DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vDist);
    float length;
    DirectX::XMStoreFloat(&length, vLen);

    out.isHit = (a.radius+b.radius>=length);
    return out;
}
