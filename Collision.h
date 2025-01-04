#pragma once
#include <DirectXMath.h>
class Collision
{

	public:
		//--- �����蔻��̌��� 
		struct Result {
			bool     isHit;  // �����������ǂ��� 
			DirectX::XMFLOAT3  point;  // �q�b�g�ʒu 
		};
		//--- �����蔻��̌`�� 
		struct Box {  // �l�p 
			DirectX::XMFLOAT3  center;  // ���S���W 
			DirectX::XMFLOAT3  size;  // �T�C�Y 
		};
		struct Sphere { // �� 
			DirectX::XMFLOAT3  center;  // ���S���W 
			float     radius;  // ���a 
		};
public:
	// �l�p���m�̓����蔻�� 
	static Result Hit(Box a, Box b);
	static Result Hit(Sphere a, Sphere b);
};

