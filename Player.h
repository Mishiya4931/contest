#pragma once
#include "GameObject.h"
#include"Camera.h"
#include"Geometory.h"
#include"Defines.h"
#include"Input.h"
#include"Collision.h"
class Player :public GameObject
{
public:
    Player();
    ~Player();
    void Update();  
    void Draw();
    //カメラの設定
    void SetCamera(Camera* camera) { m_pCamera = camera; }
    Collision::Box GetCollision() {
        return m_box;
    }
    void OnCollision();
private:  
    void UpdateShot();
    void UpdateMove();
private:
    Camera* m_pCamera; //カメラ情報
    DirectX::XMFLOAT3 m_move;//移動量
    bool m_isStop;//ボールの停止判定
    int m_shotStep;
    float m_power;
    float m_moveSpeed; // 移動速度
    Collision::Box m_box;
    float m_yaw; // Yaw角（水平回転）
    float m_pitch; // Pitch角（垂直回転）
    float m_turnSpeed;
};

