#include "EffectM.h"

#include"iostream"
/// @brief 初期化処理
EffectM::EffectM()
{
    g_EffekseerManager = Effekseer::Manager::Create(2000);
    g_EffekseerRenderer = EffekseerRendererDX11::Renderer::Create(GetDevice(),GetContext(), 2000);

    // Effekseerにレンダラーを登録
    g_EffekseerManager->SetSpriteRenderer(g_EffekseerRenderer->CreateSpriteRenderer());
    g_EffekseerManager->SetRibbonRenderer(g_EffekseerRenderer->CreateRibbonRenderer());
    g_EffekseerManager->SetRingRenderer(g_EffekseerRenderer->CreateRingRenderer());
    g_EffekseerManager->SetTrackRenderer(g_EffekseerRenderer->CreateTrackRenderer());
    g_EffekseerManager->SetModelRenderer(g_EffekseerRenderer->CreateModelRenderer());
    g_EffekseerManager->SetTextureLoader(g_EffekseerRenderer->CreateTextureLoader());
    g_EffekseerManager->SetModelLoader(g_EffekseerRenderer->CreateModelLoader());
    
}

EffectM::~EffectM()
{
    g_EffekseerManager.Reset();
        g_EffekseerRenderer.Reset();
}

Effekseer::EffectRef EffectM::LoadEffect(const EFK_CHAR* path)
{
    auto effect = Effekseer::Effect::Create(g_EffekseerManager, path,1.0f);//effectに入れる1.0fは大きさ
    if (effect!=nullptr) {
        int handle = g_EffekseerManager->Play(effect, 0, 0, 0);//再生(再生するエフェクト,ポジジョンxyz)
        g_EffekseerManager->SetRotation(handle, 0.0f, 0.0f, 0.0f);
    }
    


    return effect;
 
}

void EffectM::ConvertXMMATRIXToEffekseerMatrix(const DirectX::XMMATRIX& dxMatrix, Effekseer::Matrix44& efkMatrix)
{
    // 行列の要素をコピー
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            efkMatrix.Values[row][col] = dxMatrix.r[row].m128_f32[col];//EffectのMatrix44にXMMatrixを変換
        }
    }
}

void EffectM::Update()
{
    g_EffekseerManager->Update();
}

void EffectM::Draw()
{
    DirectX::XMFLOAT4X4 a=m_pCamera->GetViewMatrix(false);
    DirectX::XMFLOAT4X4 a2 = m_pCamera->GetProjectionMatrix(false);
    DirectX::XMMATRIX b=DirectX::XMLoadFloat4x4(&a);
    DirectX::XMMATRIX b2=DirectX::XMLoadFloat4x4(&a2);
    Effekseer::Matrix44 c;
    Effekseer::Matrix44 c2;
    ConvertXMMATRIXToEffekseerMatrix(b, c);
    ConvertXMMATRIXToEffekseerMatrix(b2, c2);
   

    g_EffekseerRenderer->SetCameraMatrix(c);
    g_EffekseerRenderer->SetProjectionMatrix(c2);
    g_EffekseerRenderer->BeginRendering();
    g_EffekseerManager->Draw();
    g_EffekseerRenderer->EndRendering();
    
    // スワップチェインのバッファを表示
    
}

void EffectM::CleanupEffekseer()
{

    g_EffekseerRenderer.Reset();
    g_EffekseerManager.Reset();
}
