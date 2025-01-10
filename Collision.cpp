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

  // �{�b�N�X�̖ʓ��m�̊֌W���瓖���蔻����s�� 
    out.isHit = false;
    if (maxA.x >= minB.x && minA.x <= maxB.x) {
        if (maxA.y >= minB.y && minA.y <= maxB.y) {
            if (maxA.z >= minB.z && minA.z <= maxB.z) {
                out.isHit = true;


                    // �e���̂߂荞�ݗʂ��v�Z 
                out.normal.x = std::min(maxA.x - minB.x, maxB.x - minA.x);
                out.normal.y = std::min(maxA.y - minB.y, maxB.y - minA.y) * 0.5f;
                out.normal.z = std::min(maxA.z - minB.z, maxB.z - minA.z);
                // �߂荞�݂����Ȃ��ʂ𓖂������ʂƂ݂Ȃ��A�ʂ̖@�����v�Z���� 
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

Collision::Result Collision::Hit(Plane plane, Ray ray, float lenght)
{
	// �v�Z�p�̌^�ɕϊ� 
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&ray.origin);
	DirectX::XMVECTOR vRay = DirectX::XMLoadFloat3(&ray.dir);
	// �x�N�g���̒������v�Z 
	vRay = DirectX::XMVector3Normalize(vRay);
	vRay = DirectX::XMVectorScale(vRay, lenght);
	// �v�Z���ʂ����ɐ����̏����쐬 
	Line line = {};
	line.start = ray.origin;
	DirectX::XMStoreFloat3(&line.end, DirectX::XMVectorAdd(vPos, vRay));
	// ���ʂƒ����̓����蔻������s 
	return Hit(plane, line);
}

Collision::Result Collision::Hit(Plane plane, Line line)
{
	Result out = {};
	// �v�Z�ɕK�v�ȃp�����[�^���` 
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&plane.normal);
	DirectX::XMVECTOR vLineStart = DirectX::XMLoadFloat3(&line.start);
	DirectX::XMVECTOR vLineEnd = DirectX::XMLoadFloat3(&line.end);
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);//���K��

	// ���ʂ̈�_��������̎n�_�ƏI�_�Ɍ������x�N�g�����v�Z 
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vLineStart, vPlanePos);
	DirectX::XMVECTOR vToEnd = DirectX::XMVectorSubtract(vLineEnd, vPlanePos);
	DirectX::XMVECTOR vDotStart = DirectX::XMVector3Dot(vToStart, vPlaneN);//�����̎n�_�Ɍ������x�N�g���ƕ��ʂ̃x�N�g���̓���;
	DirectX::XMVECTOR vDotEnd = DirectX::XMVector3Dot(vToEnd, vPlaneN);//�����̏I�_�Ɍ������x�N�g���ƕ��ʂ̃x�N�g���̓���;

	// �e���ς��畽�ʂ��ђʂ��Ă��邩���� 
	float dotStart, dotEnd;
	DirectX::XMStoreFloat(&dotStart, vDotStart);
	DirectX::XMStoreFloat(&dotEnd, vDotEnd);

	if ((dotStart > 0.0f) && (dotEnd < 0.0f))
	{
		// �e���ς̒l���Βl�ɕϊ����āA�Փˈʒu�܂ł̃x�N�g�����v�Z 
		dotStart = fabsf(dotStart);
		dotEnd = fabsf(dotEnd);
		float rate = dotStart / (dotStart + dotEnd); // �Փ˖ʂ܂ł̋����̊������v�Z 
		DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vLineEnd, vLineStart);
		vDist = DirectX::XMVectorScale(vDist, rate); // �����̃x�N�g�����Փ˖ʂ܂ł̒����ɕϊ� 
		vDist = DirectX::XMVectorAdd(vLineStart, vDist); // �n�_����x�N�g�����ړ� 

		// ���ʂƂ̓����蔻��̌��ʂ��i�[ 
		out.isHit = true;
		out.normal = plane.normal;
		DirectX::XMStoreFloat3(&out.point, vDist);
	}
	return out;
}

Collision::Result Collision::Hit(Point point, Triangle triangle)
{
	Result out = {};
	// �v�Z�p�̌^�ɕϊ� 
	DirectX::XMVECTOR vTriPoint[3] = {
	 DirectX::XMLoadFloat3(&triangle.point[0]),
	 DirectX::XMLoadFloat3(&triangle.point[1]),
	 DirectX::XMLoadFloat3(&triangle.point[2]),
	};
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point.pos);

	// �O�p�`�̒��_����ʂ̒��_�Ɍ������x�N�g���ƁA�_�Ɍ������x�N�g�����v�Z 
	DirectX::XMVECTOR vEdge[3];
	DirectX::XMVECTOR vToPoint[3];
	for (int i = 0; i < 3; ++i) {
		// �ӂ̃x�N�g�� 
		vEdge[i] = DirectX::XMVectorSubtract(vTriPoint[(i + 1) % 3], vTriPoint[i]);
		vEdge[i] = DirectX::XMVector3Normalize(vEdge[i]);
		// �_�Ɍ������x�N�g�� 
		vToPoint[i] = DirectX::XMVectorSubtract(vPoint, vTriPoint[i]);
		vToPoint[i] = DirectX::XMVector3Normalize(vToPoint[i]);
	}

	// �O�p�`�̖@�����v�Z 
	DirectX::XMVECTOR vNormal;
	vNormal = DirectX::XMVector3Cross(vEdge[2], vEdge[0]);//�O�ς��g�p���āA2�̕ӂ̃x�N�g������O�p�`�̖@�����v�Z
	vNormal = DirectX::XMVector3Normalize(vNormal);

	// �_���O�p�`�̖ʏ�ɑ��݂��邩���� 
	float dot[3];
	DirectX::XMStoreFloat(&dot[0], DirectX::XMVector3Dot(vNormal, vToPoint[0]));
	if (fabsf(dot[0]) > FLT_EPSILON)// FLT_EPSILON �� 0�i�ق�0�Afloat�^�̌v�Z�덷�̒l�j
	{
		// �ʂ̖@���Ɠ_�Ɍ������x�N�g���������ɂȂ��ĂȂ���Ε��ʏ�ɂȂ� 
		return out;
	}

	// �e�x�N�g���̊O�ς��v�Z 
	DirectX::XMVECTOR vCross[3];
	for (int i = 0; i < 3; ++i) {
		vCross[i] = DirectX::XMVector3Cross(vEdge[i], vToPoint[i]);//�e�ӂ̃x�N�g���Ɠ_�Ɍ������x�N�g������O�ς��v�Z
	}

	// �O�ς̃x�N�g���Ɩʂ̃x�N�g�������������������Ă��邩�v�Z 
	for (int i = 0; i < 3; ++i) {
		DirectX::XMStoreFloat(&dot[i], DirectX::XMVector3Dot(vNormal, vCross[i]));
	}

	// �����蔻��̌��ʂ��i�[ 
	if ((dot[0] >= 0.0f) && (dot[1] >= 0.0f) && (dot[2] >= 0.0f)) {
		out.isHit = true;
		out.point = point.pos;
		DirectX::XMStoreFloat3(&out.normal, vNormal);
	}

	return out;
}

