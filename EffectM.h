#pragma once
#include"EffekseerRendererDX11.h"
#include"Effekseer.h"
#include"DirectX.h"
#include"Camera.h";
class EffectM
{
public:
	EffectM();
	~EffectM();
	void Update();
	void Draw();
	void CleanupEffekseer();
	Effekseer::EffectRef LoadEffect(const EFK_CHAR* path);
	void SetCamera(Camera* Incamera) { m_pCamera = Incamera; }
	void ConvertXMMATRIXToEffekseerMatrix(const DirectX::XMMATRIX& dxMatrix, Effekseer::Matrix44& efkMatrix);
private:
	Camera* m_pCamera;
	Effekseer::ManagerRef g_EffekseerManager;
	EffekseerRendererDX11::RendererRef g_EffekseerRenderer;
};

