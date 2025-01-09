#include "StageObjectManager.h"
#include "TrashObject.h"
#include <random>
#include"Collision.h"
#include"Player.h"
StageObjectManager::StageObjectManager()
{
	std::random_device Rd;//�����Z���c�C�X�^�֐����g���ă����_���ɃI�u�W�F�N�g��z�u
	std::mt19937 Gen(Rd());
	std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ������-10.0f�`10.0f�͈̔�
	std::uniform_real_distribution<float> DistY(0.0f, 10.0f); //Y������ - 10.0f�`10.0f�͈̔�
	for (int i = 0; i < 100; i++)
	{
		m_StageObjects.push_back(new TrashObject({ DistXZ(Gen),DistY(Gen),DistXZ(Gen) }));//�����_���ȍ��W�ɗ̈�m��
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
}

void StageObjectManager::Update()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		itr->Update();
		if (Collision::Hit( itr->GetCollision(), m_pPlayer->GetCollision()).isHit)//�v���C���[�ƃI�u�W�F�N�g���������Ă�����I�u�W�F�N�g������
		{
			delete itr;
			itr = nullptr;
		}
	}
}

void StageObjectManager::Draw()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//�I�u�W�F�N�g�����邩�ǂ����`�F�b�N
		itr->Draw();
	}
}
