#pragma once
#include "GameObject.h"
#include"Camera.h"
#include"Geometory.h"
#include"Defines.h"
#include"Input.h"
#include"Collision.h"
#include"Wall.h"
//==============�O���錾========================
class GaugeUI;


class Player :public GameObject
{
public:
    Player();
    ~Player();
    void Update();  
    void Draw();
    //�J�����̐ݒ�
    void SetCamera(Camera* camera) { m_pCamera = camera; }
    void SetWall(std::vector <Wall*> InWall) { m_pWall = InWall; }
    void OnCollision();
private:  
    void UpdateShot();
    void UpdateMove();
    void OnCollisionWall();
private:
    GaugeUI* m_pGaugeUI;
    Camera* m_pCamera; //�J�������
    DirectX::XMFLOAT3 m_move;//�ړ���
    bool m_isStop;//�{�[���̒�~����
    bool m_bDashFlag;//�{�[���̒�~����
    int m_shotStep;
    float m_power;
    std::vector <Wall*> m_pWall;
    float m_fDashSpeed;
    int m_nDashIntervalCnt;//�_�b�V�����ł���܂Ŏ���
    int m_nGaugeUICnt;//�Q�[�W�̃J�E���g
};

