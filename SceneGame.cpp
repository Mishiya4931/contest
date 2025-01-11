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
	//g_pEffekseerM->LoadEffect(u"Assets/sakura.efk");//�t�@�C���̓ǂݍ���EFK_CHAR*��char16_t�^�Ȃ̂ŁA""�O��u�����Č^�w��
	//m_pModel = new Model();
	//if (!m_pModel->Load("Assets/riceblock.fbx", 1.0f)) {
	//	MessageBox(NULL, "�ǂݍ��񂾃t�@�C����", "Error", MB_OK);     
	//}
	m_pStageObjectManager = new StageObjectManager();
	m_pCamera = new CameraDebug();
	m_pPlayer = new Player();
	m_pStageObjectManager->SetPlayer(m_pPlayer);
	m_pCamera->SetPlayer(m_pPlayer);
	m_pPlayer->SetCamera(m_pCamera);
	m_pPlayer->SetWall(m_pStageObjectManager->GetWall());
	//g_pEffekseerM->SetCamera(m_pCamera);//�J��������n��

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

	if (IsKeyTrigger('P'))SetNext(0);//�f�o�b�O
}

void SceneGame::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV(); // RenderTargetView 
	DepthStencil* pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D�\���ɂȂ�
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());
	//
	////g_pEffekseerM->Draw();
	////********************�{�b�N�X��]**********************
	////static float rad = 0.0f;
	////DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(ANGLE(rad));//X����]�s��;
	////DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(ANGLE(rad));//Y����]�s��;
	////DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(ANGLE(rad));//Z����]�s��;
	////DirectX::XMMATRIX mat = Rx * Ry * Rz; // ���ꂼ��̍s����|�����킹�Ċi�[ 
	////mat = DirectX::XMMatrixTranspose(mat);
	////DirectX::XMFLOAT4X4 fMat; // �s��̊i�[�� 
	////DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	////Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	////rad += 1.0f;//��]�p�̍X�V(���x�͂��C��);
	////Geometory::DrawBox();
	//// ****************************************************
	////********************�{�b�N�X�z�u********************** 
	////--- �P�ڂ̒n�� 
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(-2.0f,-2.0f,0.0f);   // �V�ʂ��O���b�h�������ɗ���悤�Ɉړ� 
	//DirectX::XMMATRIX S = DirectX::XMMatrixScaling(5.0f,0.1,10.0f); // �n�ʂƂȂ�悤�ɁA�O�㍶�E�ɍL���A�㉺�ɋ������� 

	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//					  DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//					  DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]
	//DirectX::XMMATRIX mat = S * R * T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//mat = DirectX::XMMatrixTranspose(mat);//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;
	//DirectX::XMFLOAT4X4 fMat; // �s��̊i�[�� 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	//Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	//Geometory::DrawBox();

	////--- 2�ڂ̒n�� 
	//T = DirectX::XMMatrixTranslation(2.0f, 2.5f, 8.0f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]

 //   mat = S * R *T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//mat = DirectX::XMMatrixTranspose(mat);//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;
 //   fMat; // �s��̊i�[�� 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	//Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	//Geometory::DrawBox();
	////--- 3�ڂ̒n�� 
	//T = DirectX::XMMatrixTranslation(0.0f, 1.0f, 4.1f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(-30.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]

 //   mat = S * R *T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//mat = DirectX::XMMatrixTranspose(mat);//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;
 //   fMat; // �s��̊i�[�� 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	//Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	//Geometory::DrawBox();
	////--- 4�ڂ̒n�� 
	//T = DirectX::XMMatrixTranslation(4.0f, 2.0f, 15.0f);  
	//S = DirectX::XMMatrixScaling(5.0f, 0.1, 5.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(-30.0f)) *
	//    DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]

 //   mat = S * R *T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//mat = DirectX::XMMatrixTranspose(mat);//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;
 //   fMat; // �s��̊i�[�� 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	//Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	//Geometory::DrawBox();
	////*****************************************************
	//T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//S = DirectX::XMMatrixScaling(1.0f, 1.0, 1.0f);
	//R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
	//	DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]
	//mat = S * R * T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//mat = DirectX::XMMatrixTranspose(mat);//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;
	//fMat; // �s��̊i�[�� 
	//DirectX::XMStoreFloat4x4(&fMat, mat);//Mat��fMat�Ɋi�[���鏈��;
	//Geometory::SetWorld(fMat); // �{�b�N�X�ɕϊ��s���ݒ� 
	////===================================
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);



	


	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f,1.0f);


	DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationY(ANGLE(0.0f)) *
		DirectX::XMMatrixRotationZ(ANGLE(0.0f)); // ��]
	DirectX::XMMATRIX mat = S * R * T;//���ꂼ��̍s����|�����킹�Ċi�[;
	//CPU����GPU�ɍs��𑗂�O�Ɏ��s���鏈��;

	////���_�V�F�[�_�[�ɓn���ϊ��s����쐬
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world, view, proj;
	world = mat;
	//�v�Z�p�̃f�[�^����ǂݎ��p�̃f�[�^�ɕϊ� 
	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	//DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	//DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));
	wvp[1] = m_pCamera->GetViewMatrix();
	wvp[2] = m_pCamera->GetProjectionMatrix();

	// �V�F�[�_�[�ւ̕ϊ��s���ݒ�
	ShaderList::SetWVP(wvp); 
	m_pStageObjectManager->Draw();
	m_pPlayer->Draw();
	//// ���f���Ɏg�p���钸�_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[��ݒ�
	//m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));

	// �����̃��b�V���ō\������Ă���ꍇ�A���镔���͋����I�ȕ\���A���镔���͔�����I�ȕ\����
	// ������ꍇ������B�O��̕\���͓����}�e���A���ňꊇ�\�����Ă������߁A���b�V�����ƂɃ}�e���A����
	// �؂�ւ���B

	//  
	//  



	//for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {
	//	  //���f���̃��b�V�����擾
	//	Model::Mesh mesh = *m_pModel->GetMesh(i);
	//	  //���b�V���Ɋ��蓖�Ă��Ă���}�e���A���擾
	//	Model::Material material = *m_pModel->GetMaterial(mesh.materialID);
	//	  //�V�F�[�_�[�փ}�e���A����ݒ�
	//	material.ambient = { 0.6,0.6,0.6,1.0f };
	//	ShaderList::SetMaterial(material);
	//	  //���f���̕`��
	//	m_pModel->Draw(i);
	//}
	//g_pEffekseerM->Draw();
}
