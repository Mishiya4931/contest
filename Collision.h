#pragma once
#include <DirectXMath.h>
class Collision
{

	public:
		//--- �����蔻��`��̎�� 
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
		//--- �����蔻��̌`�� 
		struct Box {  // �l�p 
			DirectX::XMFLOAT3  center;  // ���S���W 
			DirectX::XMFLOAT3  size;  // �T�C�Y 
		};
		struct Sphere { // �� 
			DirectX::XMFLOAT3  center;  // ���S���W 
			float     radius;  // ���a 
		};
		struct Point  // �_ 
		{
			DirectX::XMFLOAT3 pos;  // ���W 
		};
		struct Triangle // �O�p�`
		{
			DirectX::XMFLOAT3 point[3]; // �e���_ 
		};
		//--- �����蔻��̌`�� 
		struct Plane { // ���� 
			DirectX::XMFLOAT3 pos;   // ���ʏ�̂P�_ 
			DirectX::XMFLOAT3 normal;  // ���ʂ̖@�� 
		};
		struct Ray { // ���C(�����̒���) 
			DirectX::XMFLOAT3 origin;  // �n�_ 
			DirectX::XMFLOAT3 dir;  // ���C�̌��� 
		};
		struct Line { // ���� 
			DirectX::XMFLOAT3 start;  // �����̎n�_ 
			DirectX::XMFLOAT3 end;  // �����̏I�_ 
		};
		//--- �����蔻��̓������ 
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
		//--- �����蔻��̌��� 
		struct Result {
			bool     isHit;  // �����������ǂ��� 
			DirectX::XMFLOAT3  point;  // �q�b�g�ʒu 
			DirectX::XMFLOAT3  normal;  // �q�b�g���� 
			Info     other;  // �����蔻��I�u�W�F�N�g
		};

public:
	// �l�p���m�̓����蔻�� 
	 // Info�^�ł̓����蔻�� 
	static Result Hit(Info a, Info b);
	static Result Hit(Box a, Box b);
	static Result Hit(Sphere a, Sphere b);
	static Result Hit(Plane plane, Ray ray, float lenght);
	static Result Hit(Plane plane, Line line);
	static Result Hit(Point point, Triangle triangle);
};

