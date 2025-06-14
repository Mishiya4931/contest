#pragma once
#include "Camera.h"
#include"Player.h"
class CameraMinimap : public Camera {
public:
    CameraMinimap();
    virtual ~CameraMinimap() override;

    void Update() override;
    //プレイヤーの情報を設定
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
    Player* m_pPlayer;
};
