#pragma once
#include "GameObject.h"
#include"Camera.h"
#include"Geometory.h"
#include"Defines.h"
#include"Input.h"
#include"Collision.h"
#include"Wall.h"
#include"Model.h"
#include"Texture.h"
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
    void SetWall(std::vector <Wall*> InWall) { m_pWall = InWall; }
    int GetItemNum() { return m_nItemCnt; }
    void SetItemNum(int InItemNum) { m_nItemCnt = InItemNum; }
private:  
    void UpdateMove();
    void DrawUI();
    void OnCollisionWall();
private:
    Model* m_pModel;
    Model* m_pModelEquip;
    GaugeUI* m_pGaugeUI;
    Camera* m_pCamera; //カメラ情報
    DirectX::XMFLOAT3 m_move;//移動量
    Texture* m_pTexture;
    //bool m_isStop;//ボールの停止判定
    //int m_shotStep;
    float m_power;
    std::vector <Wall*> m_pWall;
    float m_fDashSpeed;
    bool m_bDashFlag;//ダッシュできるかどうか
    int m_nDashIntervalCnt;//ダッシュができるまで時間
    int m_nGaugeUICnt;//ゲージのカウント
    int m_nItemCnt;
};

