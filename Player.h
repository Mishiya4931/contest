#pragma once
#include "GameObject.h"
#include"Camera.h"
#include"Geometory.h"
#include"Defines.h"
#include"Input.h"
#include"Collision.h"
//==============前方宣言========================
class GaugeUI;


class Player :public GameObject
{
public:
    Player();
    ~Player();
    void Update();  
    void Draw();
    //カメラの設定
    void SetCamera(Camera* camera) { m_pCamera = camera; }

    void OnCollision();
private:  
    void UpdateShot();
    void UpdateMove();
private:
    GaugeUI* m_pGaugeUI;
    Camera* m_pCamera; //カメラ情報
    DirectX::XMFLOAT3 m_move;//移動量
    bool m_isStop;//ボールの停止判定
    bool m_bDashFlag;//ボールの停止判定
    int m_shotStep;
    float m_power;
   
    float m_fDashSpeed;
    int m_nDashIntervalCnt;//ダッシュができるまで時間
    int m_nGaugeUICnt;//ゲージのカウント
};

