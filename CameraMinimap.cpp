#include "CameraMinimap.h"

CameraMinimap::CameraMinimap() : m_pPlayer(nullptr) {
    m_aspect = 1.0f;
}

void CameraMinimap::Update() {
    if (!m_pPlayer) { return; }

    m_look = m_pPlayer->GetPos();
    m_pos = m_look;
    m_pos.y += 5.0f;  // (”’l‚ª•s–¾)

    // Z Ž²‚Ìã•ûŒü‚ðÝ’è
    m_up = { 0.0f, 0.0f, 1.0f };
}