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
		MessageBox(NULL, "StageObjectManagerにプレイヤーがセットされていません", "エラー", MB_OK);
	}

	//=======オブジェクトの配置========
	std::random_device Rd;//メルセンツイスタ関数を使ってランダムにオブジェクトを配置
	std::mt19937 Gen(Rd());
	std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ方向は-10.0f～10.0fの範囲
	std::uniform_real_distribution<float> DistY(0.3f, 10.0f); //Y方向は - 10.0f～10.0fの範囲
	for (int i = 0; i < 100; i++)
	{
		while (Collision::Hit(Collision::Box{ {0.0f,0.0f,0.0f}, {0.4f,0.4f,0.4f} }, { {DistXZ(Gen),DistY(Gen),DistXZ(Gen)}, {0.4f,0.4f,0.4f} }).isHit)//スタート位置に出現しないようにする
		{
			std::uniform_real_distribution<float> DistXZ(-10.0f, 10.0f);//XZ方向は-10.0f～10.0fの範囲
			std::uniform_real_distribution<float> DistY(0.0f, 10.0f); //Y方向は - 10.0f～10.0fの範囲
		}
		m_StageObjects.push_back(new TrashObject({ DistXZ(Gen),DistY(Gen),DistXZ(Gen) }));//ランダムな座標に領域確保
	}
	//=======壁の配置===========

	struct WallIndex//壁の位置、回転、サイズの情報
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Rotation;
		DirectX::XMFLOAT3 Size;
	};
	WallIndex wallindex[6];//ボックス上に当たり判定
	wallindex[WALL_INNER] = { {0.0f,5.0f,WALL_POSITION},{0.0f,0.0f,0.0f},{20.0f,10.0f,1.0f} };//奥
	wallindex[WALL_UP] = { {0.0f,WALL_POSITION,0.0f},{0.0f,0.0f,0.0f},{20.0f,1.0f,20.0f} };//上
	wallindex[WALL_LEFT] = { {-WALL_POSITION,0.0f,0.0f},{0.0f,0.0f,0.0f},{1.0f,20.0f,20.0f} };//左
	wallindex[WALL_RIGHT] = { {WALL_POSITION,0.0f,0.0f},{0.0f,0.0f,0.0f},{1.0f,20.0f,20.0f} };//右
	wallindex[WALL_BACK] = { {0.0f,0.0f,-WALL_POSITION},{0.0f,0.0f,0.0f},{20.0f,20.0f,1.0f} };//手前
	wallindex[WALL_DOWN] = { {0.0f,-0.5f,0.0f},{0.0f,0.0f,0.0f},{20.0f,1.0f,20.0f} };//下

	for (int i = 0; i < WALL_NUM; i++)
	{
		m_WallObjects.push_back(new Wall(wallindex[i].Pos, wallindex[i].Rotation, wallindex[i].Size,i));
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
	for (auto& itr : m_WallObjects)//範囲for文でdelete
	{
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		delete itr;
		itr = nullptr;
	}
	m_WallObjects.clear();
}

void StageObjectManager::Update()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		itr->Update();
		if (Collision::Hit( itr->GetCollision(), m_pPlayer->GetCollision()).isHit)//プレイヤーとオブジェクトが当たっていたらオブジェクトを消す
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
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		itr->Update();
	}
}

void StageObjectManager::Draw()
{
	for (auto& itr : m_StageObjects)
	{
		if (!itr)continue;//オブジェクトがあるかどうかチェック
		itr->Draw();
	}
	//for (auto& itr : m_WallObjects)
	//{
	//	if (!itr)continue;//オブジェクトがあるかどうかチェック
	//	itr->Draw();
	//}
}
