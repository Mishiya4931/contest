#include "Geometory.h"

void Geometory::MakeBox()
{
	Vertex vtx[] = {
			// -Z面 
			{{-0.5f, 0.5f, -0.5f},{0.0f, 0.0f}},
			{{ 0.5f, 0.5f, -0.5f},{1.0f, 0.0f}},
			{{-0.5f,-0.5f, -0.5f},{0.0f, 1.0f}},
			{{ 0.5f,-0.5f, -0.5f},{1.0f, 1.0f}},
			// +Z面
			{{ 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{ 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
			{{-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
			// +X面
			{{ 0.5f, 0.5f,-0.5f}, {0.0f, 0.0f}},
			{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{ 0.5f,-0.5f,-0.5f}, {0.0f, 1.0f}},
			{{ 0.5f,-0.5f, 0.5f}, {1.0f, 1.0f}},
			// -X面
			{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{-0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}},
			{{-0.5f,-0.5f, 0.5f}, {0.0f, 1.0f}},
			{{-0.5f,-0.5f,-0.5f}, {1.0f, 1.0f}},
			// +Y面
			{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
			{{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
			{{-0.5f, 0.5f,-0.5f}, {0.0f, 1.0f}},
			{{ 0.5f, 0.5f,-0.5f}, {1.0f, 1.0f}},
			// -Y面
			{{-0.5f,-0.5f, -0.5f}, {0.0f, 0.0f}},
			{{ 0.5f,-0.5f, -0.5f}, {1.0f, 0.0f}},
			{{-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f}},
			{{ 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f}},
		}; //--- 頂点の作成
	int idx[] = {
		 0, 1, 2,  1, 3, 2, // -Z面 
		 4, 5, 6,  5, 7, 6, // +Z面 
		 8, 9,10,  9,11,10, // +X面 
		12,13,14, 13,15,14, // -X面 
		16,17,18, 17,19,18, // +Y面 
		20,21,22, 21,23,22 //  -Y面 
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
	// バッファの作成
}

void Geometory::MakeCylinder()
{
	//--- 頂点の作成
	// 天面、底面

	// 側面

	//--- インデックスの作成
	// 天面、底面

	// 側面


	//--- バッファの作成
}

void Geometory::MakeSphere()
{
	//--- 頂点の作成

	//--- インデックスの作成

	// バッファの作成
}