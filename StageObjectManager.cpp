#include "StageObjectManager.h"
#include "TrashObject.h"
#include <random>
#include"Collision.h"
#include"Player.h"
StageObjectManager::StageObjectManager():
	m_pPlayer(nullptr)
{
	if (m_pPlayer)
	{
		MessageBox(NULL, "StageObjectManagerにプレイヤーがセットされていません", "エラー", MB_OK);
	}
	std::random_device Rd;//メルセンツイスタ関数を使ってランダムにオブジェクトを配置
	std::mt19937 Gen(Rd());
	std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ方向は-10.0f～10.0fの範囲
	std::uniform_real_distribution<float> DistY(0.0f, 10.0f); //Y方向は - 10.0f～10.0fの範囲
	for (int i = 0; i < 100; i++)
	{
		while (Collision::Hit({ {0.0f,0.0f,0.0f}, {0.4f,0.4f,0.4f} }, { {DistXZ(Gen),DistY(Gen),DistXZ(Gen)}, {0.4f,0.4f,0.4f} }).isHit)//スタート位置に出現しないようにする
		{
			std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ方向は-10.0f～10.0fの範囲
			std::uniform_real_distribution<float> DistY(0.0f, 10.0f); //Y方向は - 10.0f～10.0fの範囲
		}
		m_StageObjects.push_back(new TrashObject({ DistXZ(Gen),DistY(Gen),DistXZ(Gen) }));//ランダムな座標に領域確保
	}
	
}

StageObjectManager::~StageObjectManager()
{
	for (auto& itr : m_StageObjects)//範囲for文でdelete
	{
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		delete itr;
		itr = nullptr;
	}
	m_StageObjects.clear();
}

void StageObjectManager::Update()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		itr->Update();
		if (Collision::Hit( itr->GetCollision(), m_pPlayer->GetCollision()).isHit)//プレイヤーとオブジェクトが当たっていたらオブジェクトを消す
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
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		itr->Draw();
	}
}
