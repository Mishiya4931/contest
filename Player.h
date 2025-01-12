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
    Camera* m_pCamera; //�J�������
    DirectX::XMFLOAT3 m_move;//�ړ���
    Texture* m_pTexture;
    //bool m_isStop;//�{�[���̒�~����
    //int m_shotStep;
    float m_power;
    std::vector <Wall*> m_pWall;
    float m_fDashSpeed;
    bool m_bDashFlag;//�_�b�V���ł��邩�ǂ���
    int m_nDashIntervalCnt;//�_�b�V�����ł���܂Ŏ���
    int m_nGaugeUICnt;//�Q�[�W�̃J�E���g
    int m_nItemCnt;
};

