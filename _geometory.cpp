#include "Geometory.h"

void Geometory::MakeBox()
{
	Vertex vtx[] = {
			// -Z�� 
			{{-0.5f, 0.5f, -0.5f},{0.0f, 0.0f}},
			{{ 0.5f, 0.5f, -0.5f},{1.0f, 0.0f}},
			{{-0.5f,-0.5f, -0.5f},{0.0f, 1.0f}},
			{{ 0.5f,-0.5f, -0.5f},{1.0f, 1.0f}},
			// +Z��
			{{ 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{ 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
			{{-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
			// +X��
			{{ 0.5f, 0.5f,-0.5f}, {0.0f, 0.0f}},
			{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{ 0.5f,-0.5f,-0.5f}, {0.0f, 1.0f}},
			{{ 0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
			// -X��
			{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{-0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}},
			{{-0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
			{{-0.5f,-0.5f,-0.5f}, {1.0f, 1.0f}},
			// +Y��
			{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{-0.5f, 0.5f,-0.5f}, {0.0f, 1.0f}},
			{{ 0.5f, 0.5f,-0.5f}, {1.0f, 1.0f}},
			// -Y��
			{{-0.5f,-0.5f, -0.5f}, {0.0f, 0.0f}},
			{{ 0.5f,-0.5f, -0.5f}, {1.0f, 0.0f}},
			{{-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f}},
			{{ 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f}},
		}; //--- ���_�̍쐬
	int idx[] = {
		 0, 1, 2,  1, 3, 2, // -Z�� 
		 4, 5, 6,  5, 7, 6, // +Z�� 
		 8, 9,10,  9,11,10, // +X�� 
		12,13,14, 13,15,14, // -X�� 
		16,17,18, 17,19,18, // +Y�� 
		20,21,22, 21,23,22 //  -Y�� 
	};
	
	MeshBuffer::Description desc = {};
	desc.pVtx= vtx;
	desc.vtxCount = sizeof(vtx)/sizeof(vtx[0]);
	desc.vtxSize = sizeof(Vertex);
	desc.pIdx = idx;
	desc.idxCount = sizeof(idx)/sizeof(idx[0]);
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pBox = new MeshBuffer();
	m_pBox->Create(desc);
	// �o�b�t�@�̍쐬
}

void Geometory::MakeCylinder()
{
	//--- ���_�̍쐬
	// �V�ʁA���

	// ����

	//--- �C���f�b�N�X�̍쐬
	// �V�ʁA���

	// ����


	//--- �o�b�t�@�̍쐬
}

void Geometory::MakeSphere()
{
	//--- ���_�̍쐬

	//--- �C���f�b�N�X�̍쐬

	// �o�b�t�@�̍쐬
}