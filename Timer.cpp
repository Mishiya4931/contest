#include "Timer.h"
#include"Texture.h"
#include"Sprite.h"
#include"Defines.h"
#define INIT_TIMER (60)
#define TIMER_SPRITE_SPRIT_X (5.0f)
#define TIMER_SPRITE_SPRIT_Y (2.0f)
Timer::Timer():m_nTimeCnt(INIT_TIMER)
{
	m_pTexture = new Texture();
	m_pTexture->Create("Assets/texture/number.png");
}

Timer::~Timer()
{
}

void Timer::Update()
{
	static int cnt = 0;
	if(cnt>60){//��b(60�t���[��)�Ɉ��^�C�}�[�����炷

		if(m_nTimeCnt>0)m_nTimeCnt--;
		cnt = 0;
	}
	cnt++;
}

void Timer::Draw()
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
	//=======�^�C�}�[1�̈�====
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(700.0f, 100.0f, 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	int one = m_nTimeCnt % 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (one % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / TIMER_SPRITE_SPRIT_Y * (one / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / TIMER_SPRITE_SPRIT_Y });
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
	//=======�^�C�}�[10�̈�==========

	T = DirectX::XMMatrixTranslation(590.0f, 100.0f, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]
	mWorld = S * T;// �g�k����]���ړ�
	mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
	DirectX::XMStoreFloat4x4(&world, mWorld);
	Sprite::SetWorld(world);
	Sprite::SetSize({ 160.0f, 160.0f }); //�@�T�C�Y
	Sprite::SetOffset({ 0.0f, 0.0f });// ���W
	int ten = m_nTimeCnt / 10;
	Sprite::SetUVPos({ 1.0f / TIMER_SPRITE_SPRIT_X * (ten % static_cast<int>(TIMER_SPRITE_SPRIT_X)),1.0f / 2.0f * (ten / static_cast<int>(TIMER_SPRITE_SPRIT_X)) });
	Sprite::SetUVScale({ 1.0f / TIMER_SPRITE_SPRIT_X,1.0f / 2.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Sprite::Draw();
	// 3D�\���̐ݒ� 
	SetRenderTargets(1, &pRTV, pDSV);
	Sprite::SetUVPos({0.0f, 0.0f});
	Sprite::SetUVScale({1.0f,1.0f});
}
