#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "ShaderList.h" 
#include"EffectM.h"
#include"DirectX.h"
#include"Player.h"
#include"StageObjectManager.h"
#include"GaugeUI.h"
#define PAI (3.141592f)
#define ANGLE(a) PAI/180.0f*a
EffectM* g_pEffekseerM;
SceneGame::SceneGame():
	m_pCamera(nullptr),
	m_pModel(nullptr),
	m_pPlayer(nullptr),
	m_pStageObjectManager(nullptr)
{
	//g_pEffekseerM = new EffectM();
	//g_pEffekseerM->LoadEffect(u"Assets/sakura.efk");//ファイルの読み込みEFK_CHAR*はchar16_t型なので、""前にuをつけて型指定
	//m_pModel = new Model();
	//if (!m_pModel->Load("Assets/riceblock.fbx", 1.0f)) {
	//	MessageBox(NULL, "読み込んだファイル名", "Error", MB_OK);     
	//}
	m_pStageObjectManager = new StageObjectManager();
	m_pCamera = new CameraDebug();
	m_pPlayer = new Player();
	m_pStageObjectManager->SetPlayer(m_pPlayer);
	m_pCamera->SetPlayer(m_pPlayer);
	m_pPlayer->SetCamera(m_pCamera);
	m_pPlayer->SetWall(m_pStageObjectManager->GetWall());
	//g_pEffekseerM->SetCamera(m_pCamera);//カメラ情報を渡す

}

SceneGame::~SceneGame()
{
if (m_pCamera) {
	delete m_pCamera;
	m_pCamera = nullptr;
	}
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (g_pEffekseerM)
	{
		delete g_pEffekseerM;
		g_pEffekseerM = nullptr;
	}
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pStageObjectManager);
}

void SceneGame::Update()
{
	m_pStageObjectManager->Update();
	m_pCamera->Update();
	//g_pEffekseerM->Update();
	m_pPlayer->Update();

	if (IsKeyTrigger('P'))SetNext(0);//デバッグ
}

void SceneGame::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D表示になる
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());
	//
	////g_pEffekseerM->Draw();
	////********************ボックス回転**********************
	////static float rad = 0.0f;
	////DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(ANGLE(rad));//X軸回転行列;
	////DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(ANGLE(rad));//Y軸回転行列;
	////DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(ANGLE(rad));//Z軸回転行列;
	////DirectX::XMMATRIX mat = Rx * Ry * Rz; // それぞれの行列を掛け合わせて格納 
	////mat = DirectX::XMMatrixTranspose(mat);
	////DirectX::XMFLOAT4X4 fMat; // 行列の格納先 
	////DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	////Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	////rad += 1.0f;//回転角の更新(速度はお任せ);
	////Geometory::DrawBox();
	//// ****************************************************
	////********************ボックス配置********************** 
	////--- １つ目の地面 
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(-2.0f,-2.0f,0.0f);   // 天面がグリッドよりも下に来るように移動 
	//DirectX::XMMATRIX S = DirectX::XMMatrixScaling(5.0f,0.1,10.0f); // 地面となるように、前後左右に広く、上下に狭くする 

	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//					  DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//					  DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転
	//DirectX::XMMATRIX mat = S * R * T;//それぞれの行列を掛け合わせて格納;
	//mat = DirectX::XMMatrixTranspose(mat);//CPUからGPUに行列を送る前に実行する処理;
	//DirectX::XMFLOAT4X4 fMat; // 行列の格納先 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	//Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	//Geometory::DrawBox();

	////--- 2つ目の地面 
	//T = DirectX::XMMatrixTranslation(2.0f, 2.5f, 8.0f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転

 //   mat = S * R *T;//それぞれの行列を掛け合わせて格納;
	//mat = DirectX::XMMatrixTranspose(mat);//CPUからGPUに行列を送る前に実行する処理;
 //   fMat; // 行列の格納先 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	//Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	//Geometory::DrawBox();
	////--- 3つ目の地面 
	//T = DirectX::XMMatrixTranslation(0.0f, 1.0f, 4.1f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(-30.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転

 //   mat = S * R *T;//それぞれの行列を掛け合わせて格納;
	//mat = DirectX::XMMatrixTranspose(mat);//CPUからGPUに行列を送る前に実行する処理;
 //   fMat; // 行列の格納先 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	//Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	//Geometory::DrawBox();
	////--- 4つ目の地面 
	//T = DirectX::XMMatrixTranslation(4.0f, 2.0f, 15.0f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(-30.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転

 //   mat = S * R *T;//それぞれの行列を掛け合わせて格納;
	//mat = DirectX::XMMatrixTranspose(mat);//CPUからGPUに行列を送る前に実行する処理;
 //   fMat; // 行列の格納先 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	//Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	//Geometory::DrawBox();
	////*****************************************************
	//T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//S = DirectX::XMMatrixScaling(1.0f, 1.0, 1.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転
	//mat = S * R * T;//それぞれの行列を掛け合わせて格納;
	//mat = DirectX::XMMatrixTranspose(mat);//CPUからGPUに行列を送る前に実行する処理;
	//fMat; // 行列の格納先 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//MatをfMatに格納する処理;
	//Geometory::SetWorld(fMat); // ボックスに変換行列を設定 
	////===================================
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);



	


	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f,1.0f);


	DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // 回転
	DirectX::XMMATRIX mat = S * R * T;//それぞれの行列を掛け合わせて格納;
	//CPUからGPUに行列を送る前に実行する処理;

	////頂点シェーダーに渡す変換行列を作成
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world, view, proj;
	world = mat;
	//計算用のデータから読み取り用のデータに変換 
	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	//DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	//DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();

	// シェーダーへの変換行列を設定
	ShaderList::SetWVP(wvp); 
	m_pStageObjectManager->Draw();
	m_pPlayer->Draw();
	//// モデルに使用する頂点シェーダー、ピクセルシェーダーを設定
	//m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));

	// 複数のメッシュで構成されている場合、ある部分は金属的な表現、ある部分は非金属的な表現と
	// 分ける場合がある。前回の表示は同じマテリアルで一括表示していたため、メッシュごとにマテリアルを
	// 切り替える。

	//  
	//  



	//for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
	//	  //モデルのメッシュを取得
	//	Model::Mesh mesh = *m_pModel->GetMesh(i);
	//	  //メッシュに割り当てられているマテリアル取得
	//	Model::Material material = *m_pModel->GetMaterial(mesh.materialID);
	//	  //シェーダーへマテリアルを設定
	//	material.ambient = { 0.6,0.6,0.6,1.0f };
	//	ShaderList::SetMaterial(material);
	//	  //モデルの描画
	//	m_pModel->Draw(i);
	//}
	//g_pEffekseerM->Draw();
}
