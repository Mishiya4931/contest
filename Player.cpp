#include "Player.h"
#include"Defines.h"


//=============定数定義=========================
#define MOVE_SPEED_BASE (0.07f)//スピードのベース
#define MOVE_SPEED_NORMAl (0.0f)//通常のスピード
#define MOVE_SPEED_DASH (0.05f)//ダッシュのスピード
#define MOVE_SPEED_SLOW (-0.04f)//減速時のスピード
#define ROTATION_SPEED_BASE (0.9f)//回転のスピードベース
#define DASH_TIME (30)//ダッシュする時間
#define DASH_INTERVAL (120)//ダッシュができるまでの時間
//============グロ－バル定義====================
enum eGolfBallShotStep {
	SHOT_WAIT,  //  球を打つのを待つ
	SHOT_KEEP,  //  キー入力開始
	SHOT_RELEASE, //  キー入力をやめた（球を打つ）
};
enum ePlayerState {//プレイヤーの状態
    NORMAL,//通常
    DASH,//ダッシュ
    SLOW//減速
};
ePlayerState g_eState;
Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_isStop(false),
    m_shotStep(SHOT_WAIT),
    m_power(0.0f),
    m_fDashSpeed(0.0f),
    m_bDashFlag(false),
    m_nDashIntervalCnt(0)
{
    m_box = {
    DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
    DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
        
}

Player::~Player()
{
}
//更新処理
void Player::Update()
{
    //カメラが設定されていない場合は処理しない
    if (!m_pCamera) { return; }
    UpdateMove();

    m_box.center = m_pos;
}
//描画処理
void Player::Draw()
{
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
void Player::OnCollision()
{
    if (m_move.x > 0.0f)m_move.x = -m_move.x;
    if (m_move.z > 0.0f)m_move.z = -m_move.z;
}
//球を打つ処理
void Player::UpdateShot()
{
    switch (m_shotStep) {
        //球の打ちはじめ  
    case SHOT_WAIT:
        if (IsKeyTrigger('Z')) {
            m_power = 0.0f;
            m_shotStep = SHOT_KEEP;
        }
        break;
        //キー入力継続中 
    case SHOT_KEEP:
        m_power += 0.1f;  //  
        if (IsKeyRelease('Z')) {
            m_shotStep = SHOT_RELEASE;
        }
        break;
        // 球を打つ 
    case SHOT_RELEASE:
    {
        //  打ち出す計算
        DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();
        DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
        DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
        DirectX::XMVECTOR vec = DirectX::XMVectorSubtract(vPos,vCamPos);
        vec = DirectX::XMVector3Normalize(vec);
        vec = DirectX::XMVectorScale(vec,m_power);
        DirectX::XMStoreFloat3(&m_move, vec);

        //  打ち出し後の情報を設定
        m_isStop = false;   //  移動している
        m_shotStep = SHOT_WAIT;  //  また再び打つ
        break;
    }
    }
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
    if (IsKeyTrigger(VK_SHIFT))//加速
    {
        m_bDashFlag = true;
        
    }
    if (IsKeyPress(VK_SPACE))//減速
    {
        g_eState = SLOW;
    }
    if (m_bDashFlag)//ダッシュフラグが立っていたら
    {
        
        m_nDashIntervalCnt++;
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


    //移動関連の更新
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // 行列の z軸方向(row[2]) が forward になる
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] は (x, y, z, w)
    // 移動量+
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, MOVE_SPEED_BASE + m_fDashSpeed);

    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    // 位置を更新
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);
}
