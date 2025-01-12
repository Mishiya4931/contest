#include "Score.h"
#include"Texture.h"
#include"Sprite.h"
#include"Defines.h"
Score* Score::Instanse;
#define SCORE_SPRITE_SPRIT_X (5.0f)
#define SCORE_SPRITE_SPRIT_Y (2.0f)
#define SCORE_SPRITE_POS_X (740.0f)
#define SCORE_SPRITE_POS_Y (380.0f)
Score::Score():m_pTexture(nullptr)
{
	m_nScore = 0;
	Instanse = nullptr;
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
}

Score::~Score()
{
	SAFE_DELETE(m_pTexture);
}

void Score::Init()
{
	if (Instanse != nullptr)
	{
		return;
	}
	Instanse = new Score();

}

void Score::Uninit()
{
	if (Instanse != nullptr)
	{
		delete Instanse;
		Instanse = nullptr;
	}
}

void Score::Update()
{
}

void Score::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();// �f�B�X�v���C���̎擾
	DepthStencil* pDSV = GetDefaultDSV(); // �[�x�o�b�t�@�̎擾
	// 2D�\���̐ݒ� 
	SetRenderTargets(1, &pRTV, nullptr);
	// �X�v���C�g�̕\���ɕK�v�ȍs����v�Z 
	DirectX::XMFLOAT4X4 world, view, proj;
	DirectX::XMMATRIX mView =
		DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		);
	DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, CMETER(30.0f), METER(2.0f));
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(mView));
	DirectX::XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(mProj));
	Sprite::SetView(view);
	Sprite::SetProjection(proj);

	//��̈�
	int one = m_nScore % 10;
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X, SCORE_SPRITE_POS_Y, 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (one % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (one / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();

	//�\�̈�
	int ten = m_nScore / 10;
	T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X-110.0f, SCORE_SPRITE_POS_Y, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (ten % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (ten / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();	

	//�S�̈�
	int tho = m_nScore / 100;
	T = DirectX::XMMatrixTranslation(SCORE_SPRITE_POS_X-220.0f, SCORE_SPRITE_POS_Y, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	Sprite::SetUVPos({ 1.0f / SCORE_SPRITE_SPRIT_X * (tho % static_cast<int>(SCORE_SPRITE_SPRIT_X)),1.0f / SCORE_SPRITE_SPRIT_Y * (tho / static_cast<int>(SCORE_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / SCORE_SPRITE_SPRIT_X,1.0f / SCORE_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
}
