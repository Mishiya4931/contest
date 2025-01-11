#include "Player.h"
#include"Defines.h"
#include"GaugeUI.h"

//=============定数定義=========================
#define MOVE_SPEED_BASE (0.07f)//スピードのベース
#define MOVE_SPEED_NORMAl (0.0f)//通常のスピード
#define MOVE_SPEED_DASH (0.05f)//ダッシュのスピード
#define MOVE_SPEED_SLOW (-0.06f)//減速時のスピード
#define ROTATION_SPEED_BASE (0.9f)//回転のスピードベース
#define DASH_TIME (60)//ダッシュする時間
#define DASH_INTERVAL (120)//ダッシュができるまでの時間
#define GAUGE_UI_CORRECT (0.0054f)
#define COLLISION_CORRECT (0.001f)

//============グロ－バル定義====================
//enum eGolfBallShotStep {
//	SHOT_WAIT,  //  球を打つのを待つ
//	SHOT_KEEP,  //  キー入力開始
//	SHOT_RELEASE, //  キー入力をやめた（球を打つ）
//};

enum ePlayerState {//プレイヤーの状態
    NORMAL,//通常
    DASH,//ダッシュ
    SLOW//減速
};
ePlayerState g_eState;
Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_power(0.0f),
    m_fDashSpeed(0.0f),
    m_nDashIntervalCnt(0),
    m_bDashFlag(false),
    m_pGaugeUI(nullptr),
    m_nGaugeUICnt(DASH_TIME+DASH_INTERVAL),
    m_nItemCnt(0)
{
    m_pos = { 0.0f,0.5f,0.0f };
    m_pGaugeUI = new GaugeUI();
    m_box = {
    DirectX::XMFLOAT3(0.0f,0.5f,0.0f),
    DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
        
}

Player::~Player()
{
    SAFE_DELETE(m_pGaugeUI);
}
//更新処理
void Player::Update()
{
    //カメラが設定されていない場合は処理しない
    if (!m_pCamera) { return; }
    UpdateMove();

    m_box.center = m_pos;
    OnCollisionWall();

}
//描画処理
void Player::Draw()
{
    m_pGaugeUI->Draw();
    DirectX::XMFLOAT4X4 world;
    DirectX::XMMATRIX T = 
        DirectX::XMMatrixTranslation(m_pos.x,m_pos.y,m_pos.z);
    DirectX::XMMATRIX S = 
        DirectX::XMMatrixScaling(0.4f,0.4f,0.4f);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // 回転
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat));
    Geometory::SetWorld(world);

    Geometory::DrawBox();
}

void Player::UpdateMove()
{

    if (IsKeyPress('A'))
    {
        m_Rotation.z += -ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('D'))
    {
        m_Rotation.z += ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('W'))
    {
        m_Rotation.x += -ROTATION_SPEED_BASE;
    }
    if (IsKeyPress('S'))
    {
        m_Rotation.x += ROTATION_SPEED_BASE;
    }
    //キャラクターの状態変更(基本はNORMAL状態)
    g_eState = NORMAL;
    if (IsKeyTrigger(VK_SHIFT))//ダッシュフラグを立てる
    {
        if (!m_bDashFlag) {
            m_bDashFlag = true;
            m_nGaugeUICnt = 0;
        }
        
    }
    if (m_bDashFlag)//ダッシュフラグが立っていたら
    {
        
        m_nDashIntervalCnt++;
        m_nGaugeUICnt++;
        if (m_nDashIntervalCnt < DASH_TIME)//DASH_TIMEの時間分DASH状態になりスピードが上がる
        {
            g_eState = DASH;
        }
        else if(DASH_TIME < m_nDashIntervalCnt && m_nDashIntervalCnt <DASH_TIME + DASH_INTERVAL)//時間が経過したらNORMAL状態へ
        {
            g_eState = NORMAL;
        }
        else if (DASH_TIME + DASH_INTERVAL < m_nDashIntervalCnt)//DASH_INTERVAL分ダッシュを使えなくする
        {
            m_nDashIntervalCnt = 0;//ダッシュフラグを下ろしてカウンタもゼロに
            m_bDashFlag = false;
        }
    }
    if (IsKeyPress(VK_SPACE))//減速
    {
        g_eState = SLOW;
    }
    switch (g_eState)//プレイヤーの状態によって移動スピードを変える
    {
    case NORMAL:
        m_fDashSpeed = MOVE_SPEED_NORMAl;//ノーマルは0.0f
        break;
    case DASH:
        m_fDashSpeed = MOVE_SPEED_DASH;
        break;
    case SLOW:
        m_fDashSpeed = MOVE_SPEED_SLOW;
        break;
    default:
        break;
    }
    m_pGaugeUI->SetGauge(static_cast<float>(m_nGaugeUICnt) * GAUGE_UI_CORRECT);
    m_pGaugeUI->Update();
    //移動関連の更新
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // 行列の z軸方向(row[2]) が forward になる
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] は (x, y, z, w)
    // 移動量+
    bool HitWallFlag = false;
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, MOVE_SPEED_BASE + m_fDashSpeed);
    if (HitWallFlag)moveVec = DirectX::XMVectorScale(forward, 0.0f);
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    // 位置を更新
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);
}

void Player::OnCollisionWall()
{

    for (auto& itr : m_pWall)
    {
        Collision::Result result = Collision::Hit(GetCollision(), itr->GetCollision());
        if (result.isHit)
        {
            switch (itr->GetNo())
            {
            case WALL_INNER:
                m_pos.z = itr->GetCollision().center.z + (GetCollision().size.z + itr->GetCollision().size.z + COLLISION_CORRECT) * 0.5f * result.normal.z;
                break;
            case WALL_UP:
                m_pos.y = itr->GetCollision().center.y + (GetCollision().size.y + itr->GetCollision().size.y + COLLISION_CORRECT) * 0.5f * result.normal.y;
                break;
            case WALL_LEFT:
                m_pos.x = itr->GetCollision().center.x + (GetCollision().size.x + itr->GetCollision().size.x + COLLISION_CORRECT) * 0.5f * result.normal.x;
                break;
            case WALL_RIGHT:
                m_pos.x = itr->GetCollision().center.x + (GetCollision().size.x + itr->GetCollision().size.x + COLLISION_CORRECT) * 0.5f* result.normal.x;
                break;
            case WALL_BACK:
                m_pos.z = itr->GetCollision().center.z + (GetCollision().size.z + itr->GetCollision().size.z + COLLISION_CORRECT) * 0.5f * result.normal.z;
                break;
            case WALL_DOWN:
                m_pos.y = itr->GetCollision().center.y + (GetCollision().size.y + itr->GetCollision().size.y + COLLISION_CORRECT) * 0.5f * result.normal.y;
                break;
            default:
                break;
            }
        }
    }
}
