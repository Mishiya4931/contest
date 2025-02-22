#include "Minimap.h"
/// @brief �R���X�g���N�^
Minimap::Minimap() : m_pRenderTarget(nullptr) {
    //�쐬���鏑�����ݐ�̑傫��
    float width = 512;
    float height = 512;

    // �����_�[�^�[�Q�b�g���쐬
    m_pRenderTarget = new RenderTarget();
    m_pRenderTarget->Create(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
    
    // �[�x�X�e���V�����쐬
    m_pDepthStencil = new DepthStencil();
    m_pDepthStencil->Create(width, height, false);
}
/// @brief �f�X�g���N�^
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
/// @brief �~�j�}�b�v��`��
void Minimap::Draw() {
    DirectX::XMFLOAT4X4 world, view, proj;

    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(490.0f, 210.0f, 0.0f);
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);// Y�㉺���]

    DirectX::XMMATRIX mWorld = S * T;// �g�k����]���ړ�
    mWorld = DirectX::XMMatrixTranspose(mWorld);// �]�u
    DirectX::XMStoreFloat4x4(&world, mWorld);

    //��ʂ̎�O�Ɉ����ăJ������ݒu
    DirectX::XMMATRIX mView = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),//�J�����̈ʒu
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), //�J�����̒����_
        DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)//�J������Up�x�N�g��
    );

    //2D�Ɍ�����s���ݒ�B���_�̈ʒu���ǂ��ɂ��邩
    //�l���Ȃ���A�e�������w��
    DirectX::XMMATRIX mProj = DirectX::XMMatrixOrthographicOffCenterLH(
        -640.0f, 640.0f, -360.0f, 360.0f, 0.5f, 100.0f
    );
    mView = DirectX::XMMatrixTranspose(mView);
    mProj = DirectX::XMMatrixTranspose(mProj);
    DirectX::XMStoreFloat4x4(&view, mView);
    DirectX::XMStoreFloat4x4(&proj, mProj);
    Sprite::SetView(view);
    Sprite::SetProjection(proj);
    //��ʒ��������_�Ƃ��āA�E�゠����ɕ\��
    //��ʕ�(1280,720)�Ƃ���Ɖ�ʏ�Ɖ�ʉE�͂��ꂼ��(640,360)�ƂȂ�B��ʃT�C�Y��200��
    //��ʒ[����50�����ĕ\���������̂�

    //�X�v���C�g�Ɋe�����ݒ肵�ĕ\��
    Sprite::SetWorld(world);
    // �~�j�}�b�v�̃T�C�Y�ƐF��ݒ�
    Sprite::SetSize({ 200.0f, 200.0f }); // ��ʃT�C�Y
    Sprite::SetColor({ 1, 1, 1, 1 });
    Sprite::SetUVPos({0.0f,0.0f});
    Sprite::SetUVScale({1.0f,1.0f});
    Sprite::SetTexture(m_pRenderTarget);
    Sprite::Draw();
}
/// @brief �~�j�}�b�v�̍쐬�J�n
void Minimap::BeginRender() {
    // �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V�����N���A
    m_pRenderTarget->Clear();
    m_pDepthStencil->Clear();

    // �~�j�}�b�v�̃����_�[�^�[�Q�b�g��ݒ�
    SetRenderTargets(1, &m_pRenderTarget, m_pDepthStencil);
}
/// @brief �~�j�}�b�v�̍쐬�I��
void Minimap::EndRender() {
        // �f�t�H���g�̃����_�[�^�[�Q�b�g�ɖ߂�
        RenderTarget* pDefRTV = GetDefaultRTV();
        DepthStencil* pDefDSV = GetDefaultDSV();
        SetRenderTargets(1, &pDefRTV, pDefDSV);
    }

