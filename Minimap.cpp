#include "Minimap.h"

Minimap::Minimap() : m_pRenderTarget(nullptr) {
    float width = 512;
    float height = 512;

    // �����_�[�^�[�Q�b�g���쐬
    m_pRenderTarget = new RenderTarget();
    m_pRenderTarget->Create(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);

    // �[�x�X�e���V�����쐬
    m_pDepthStencil = new DepthStencil();
    m_pDepthStencil->Create(width, height, false);
}

Minimap::~Minimap() {
    if (m_pDepthStencil) {
        delete m_pDepthStencil;
        m_pDepthStencil = nullptr;
    }
    if (m_pRenderTarget) {
        delete m_pRenderTarget;
        m_pRenderTarget = nullptr;
    }
}

void Minimap::Draw() {
    DirectX::XMFLOAT4X4 world, view, proj;
    DirectX::XMMATRIX mView = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(0.0f, 0.0f, -0.3f, 0.0f),
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
        DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
    );
    DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
        0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f
    );
    mView = DirectX::XMMatrixTranspose(mView);
    mProj = DirectX::XMMatrixTranspose(mProj);
    DirectX::XMStoreFloat4x4(&view, mView);
    DirectX::XMStoreFloat4x4(&proj, mProj);
    Sprite::SetView(view);
    Sprite::SetProjection(proj);
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f);
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, -1.0f, 1.0f);// Y�㉺���]

    DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
    mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
    DirectX::XMStoreFloat4x4(&world, mWorld);
    Sprite::SetWorld(world);
    // �~�j�}�b�v�̃T�C�Y�ƐF��ݒ�
    Sprite::SetSize({ 600.0f, 600.0f }); // ��ʃT�C�Y
    Sprite::SetColor({ 1, 0, 0, 1 });
    Sprite::SetTexture(m_pRenderTarget);
    Sprite::Draw();
}

void Minimap::BeginRender() {
    // �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V�����N���A
    m_pRenderTarget->Clear();
    m_pDepthStencil->Clear();

    // �~�j�}�b�v�̃����_�[�^�[�Q�b�g��ݒ�
    SetRenderTargets(1, &m_pRenderTarget, m_pDepthStencil);
}

void Minimap::EndRender() {
        // �f�t�H���g�̃����_�[�^�[�Q�b�g�ɖ߂�
        RenderTarget* pDefRTV = GetDefaultRTV();
        DepthStencil* pDefDSV = GetDefaultDSV();
        SetRenderTargets(1, &pDefRTV, pDefDSV);
    }

