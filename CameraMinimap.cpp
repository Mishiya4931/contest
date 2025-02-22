#include "CameraMinimap.h"
/// @brief �R���X�g���N�^
CameraMinimap::CameraMinimap() : m_pPlayer(nullptr) {
    m_aspect = 1.0f;
}
/// @brief  �f�X�g���N�^
CameraMinimap::~CameraMinimap()
{
}
/// @brief �X�V����
void CameraMinimap::Update() {
    //�v���C���[���ݒ肳��Ă��邩�m�F
    if (!m_pPlayer) { return; }
    //�v���C���[�̏��ɃJ������ݒ�
    m_look = m_pPlayer->GetPos();
    m_pos = m_look;
    m_pos.y += 5.0f; 

    // �^�ォ�猩���낷���߃A�b�v�x�N�g����Z�����֌�����
    m_up = { 0.0f, 0.0f, 1.0f };
}