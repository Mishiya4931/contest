#include "StageObjectManager.h"
#include "TrashObject.h"
#include <random>
#include"Collision.h"
#include"Player.h"
#include"Wall.h"

StageObjectManager::StageObjectManager():
	m_pPlayer(nullptr)
{
	if (m_pPlayer)
	{
		MessageBox(NULL, "StageObjectManager�Ƀv���C���[���Z�b�g����Ă��܂���", "�G���[", MB_OK);
	}

	//=======�I�u�W�F�N�g�̔z�u========
	std::random_device Rd;//�����Z���c�C�X�^�֐����g���ă����_���ɃI�u�W�F�N�g��z�u
	std::mt19937 Gen(Rd());
	std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ������-10.0f�`10.0f�͈̔�
	std::uniform_real_distribution<float> DistY(0.3f, 10.0f); //Y������ - 10.0f�`10.0f�͈̔�
	for (int i = 0; i < 100; i++)
	{
		while (Collision::Hit(Collision::Box{ {0.0f,0.0f,0.0f}, {0.4f,0.4f,0.4f} }, { {DistXZ(Gen),DistY(Gen),DistXZ(Gen)}, {0.4f,0.4f,0.4f} }).isHit)//�X�^�[�g�ʒu�ɏo�����Ȃ��悤�ɂ���
		{
			std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ������-10.0f�`10.0f�͈̔�
			std::uniform_real_distribution<float> DistY(0.0f, 10.0f); //Y������ - 10.0f�`10.0f�͈̔�
		}
		m_StageObjects.push_back(new TrashObject({ DistXZ(Gen),DistY(Gen),DistXZ(Gen) }));//�����_���ȍ��W�ɗ̈�m��
	}
	//=======�ǂ̔z�u===========

	struct WallIndex//�ǂ̈ʒu�A��]�A�T�C�Y�̏��
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Rotation;
		DirectX::XMFLOAT3 Size;
	};
	WallIndex wallindex[6];//�{�b�N�X��ɓ����蔻��
	wallindex[WALL_INNER] = { {0.0f,5.0f,WALL_POSITION},{0.0f,0.0f,0.0f},{20.0f,10.0f,1.0f} };//��
	wallindex[WALL_UP] = { {0.0f,WALL_POSITION,0.0f},{0.0f,0.0f,0.0f},{20.0f,1.0f,20.0f} };//��
	wallindex[WALL_LEFT] = { {-WALL_POSITION,0.0f,0.0f},{0.0f,0.0f,0.0f},{1.0f,20.0f,20.0f} };//��
	wallindex[WALL_RIGHT] = { {WALL_POSITION,0.0f,0.0f},{0.0f,0.0f,0.0f},{1.0f,20.0f,20.0f} };//�E
	wallindex[WALL_BACK] = { {0.0f,0.0f,-WALL_POSITION},{0.0f,0.0f,0.0f},{20.0f,20.0f,1.0f} };//��O
	wallindex[WALL_DOWN] = { {0.0f,-0.5f,0.0f},{0.0f,0.0f,0.0f},{20.0f,1.0f,20.0f} };//��

	for (int i = 0; i < WALL_NUM; i++)
	{
		m_WallObjects.push_back(new Wall(wallindex[i].Pos, wallindex[i].Rotation, wallindex[i].Size,i));
	}


}

StageObjectManager::~StageObjectManager()
{
	for (auto& itr : m_StageObjects)//�͈�for����delete
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		delete itr;
		itr = nullptr;
	}
	m_StageObjects.clear();
	for (auto& itr : m_WallObjects)//�͈�for����delete
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		delete itr;
		itr = nullptr;
	}
	m_WallObjects.clear();
}

void StageObjectManager::Update()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		itr->Update();
		if (Collision::Hit( itr->GetCollision(), m_pPlayer->GetCollision()).isHit)//�v���C���[�ƃI�u�W�F�N�g���������Ă�����I�u�W�F�N�g������
		{
			if (m_pPlayer->GetItemNum() < 5)
			{
				m_pPlayer->SetItemNum(m_pPlayer->GetItemNum() + 1);
				delete itr;
				itr = nullptr;
			}
		}
	}
	for (auto& itr : m_WallObjects)
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		itr->Update();
	}
}

void StageObjectManager::Draw()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		itr->Draw();
	}
	//for (auto& itr : m_WallObjects)
	//{
	//	if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
	//	itr->Draw();
	//}
}
