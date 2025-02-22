#pragma once
#include "Camera.h"
#include"Player.h"
class CameraMinimap : public Camera {
public:
    CameraMinimap();
    virtual ~CameraMinimap() override;

    void Update() override;
    //ƒvƒŒƒCƒ„[‚Ìî•ñ‚ğİ’è
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
    Player* m_pPlayer;
};
