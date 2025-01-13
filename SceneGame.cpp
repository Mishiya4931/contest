#include "SceneGame.h"
#include "Geometory.h"
#include "Defines.h"
#include "ShaderList.h" 
#include"EffectM.h"
#include"DirectX.h"
#include"Player.h"
#include"StageObjectManager.h"
#include"GaugeUI.h"
#include"timer.h"
#include"Score.h"
#include"CameraDebug.h"
#define PAI (3.141592f)
#define ANGLE(a) PAI/180.0f*a
#define TIMER_SPRITE_SPRIT_X (5.0f)
#define TIMER_SPRITE_SPRIT_Y (2.0f)

EffectM* g_pEffekseerM;
Timer* g_pTimer;
SceneGame::SceneGame() :
	m_pCamera(nullptr),
	m_pModel(nullptr),
	m_pPlayer(nullptr),
	m_pStageObjectManager(nullptr),
	StartFlag(false),
	Framecnt(0),
	StartTimer(3)
{
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
	m_pStageObjectManager = new StageObjectManager();
	m_pCamera = new CameraDebug();
	m_pPlayer = new Player();
	m_pStageObjectManager->SetPlayer(m_pPlayer);
	m_pStageObjectManager->SetCamera(m_pCamera);
	m_pCamera->SetPlayer(m_pPlayer);
	m_pPlayer->SetCamera(m_pCamera);
	m_pPlayer->SetWall(m_pStageObjectManager->GetWall());
	g_pTimer = new Timer();

	m_pBgm = LoadSound("Assets/sound/MainBgm.mp3",true);
	m_pspeaker = PlaySound(m_pBgm);
	m_pspeaker->SetVolume(0.5f);
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
	SAFE_DELETE(g_pTimer);
	SAFE_DELETE(m_pTexture);
	m_pspeaker->Stop(0);
}

void SceneGame::Update()
{


		m_pCamera->Update();
	if (StartFlag)
	{
		m_pStageObjectManager->Update();
		//g_pEffekseerM->Update();
		m_pPlayer->Update();
		g_pTimer->Update();
		if (g_pTimer->GetTime() < 1) {
			Score::GetInstanse()->SetScore(m_pStageObjectManager->GetStageObjectCnt());
			SetNext(2);
		}//�f�o�b�O
	}
	else
	{
		if (Framecnt > 60)
		{
			StartTimer--;
			Framecnt = 0;
		}
		if (StartTimer < 1)
		{
			StartFlag = true;
		}
		Framecnt++;
	}
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pStageObjectManager->Draw();


	RenderTarget* pRTV = GetDefaultRTV();// �f�B�X�v���C���̎擾
	DepthStencil* pDSV = GetDefaultDSV(); // �[�x�o�b�t�@�̎擾
	// 2D�\���̐ݒ� 
	SetRenderTargets(1, &pRTV, nullptr);
	// �X�v���C�g�̕\���ɕK�v�ȍs����v�Z 
	DirectX::XMFLOAT4X4 world4x4, view4x4, proj4x4;
	DirectX::XMMATRIX mView =
		DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		);
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, CMETER(30.0f), METER(2.0f));
	DirectX::XMStoreFloat4x4(&view4x4, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj4x4, DirectX::XMMatrixTranspose(mProj));
	Sprite::SetView(view4x4);
	Sprite::SetProjection(proj4x4);
	//=======�^�C�}�[1�̈�====
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world4x4, mWorld);
	Sprite::SetWorld(world4x4);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	int one = StartTimer % 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (one % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / TIMER_SPRITE_SPRIT_Y * (one / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / TIMER_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	if (!StartFlag) {
		Sprite::Draw();
	}









	pRTV = GetDefaultRTV(); // RenderTargetView 
	pDSV = GetDefaultDSV(); // DepthStencilView 
	SetRenderTargets(1, &pRTV, pDSV);  // 3 null 2D�\���ɂȂ�
	Geometory::SetView(m_pCamera->GetViewMatrix());
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix());
	
	T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, 1.0f,1.0f);
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
	//// ���f���Ɏg�p���钸�_�V�F�[�_�[�A�s�N�Z���V�F�[�_�[��ݒ�
	//m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	//m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_TOON));

	// �����̃��b�V���ō\������Ă���ꍇ�A���镔���͋����I�ȕ\���A���镔���͔�����I�ȕ\����
	// ������ꍇ������B�O��̕\���͓����}�e���A���ňꊇ�\�����Ă������߁A���b�V�����ƂɃ}�e���A����
	// �؂�ւ���B
	g_pTimer->Draw();
}
