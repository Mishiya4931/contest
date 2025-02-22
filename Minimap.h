#pragma once
#include "Texture.h" // テクスチャ関連のヘッダ
#include"DirectX.h"
#include"Sprite.h"
#include"Defines.h"
#include"CameraMinimap.h"
class Minimap {
public:
    Minimap();
    ~Minimap();

    void Draw();

    void BeginRender();

    void EndRender();

    void SetCamera(Camera* InCamera) { m_pCamera = InCamera; }
private:
    RenderTarget* m_pRenderTarget;
    DepthStencil* m_pDepthStencil;
    Camera* m_pCamera;
};
