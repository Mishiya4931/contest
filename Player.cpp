#include "Player.h"
#include"Defines.h"
enum eGolfBallShotStep {
	SHOT_WAIT,  //  球を打つのを待つ
	SHOT_KEEP,  //  キー入力開始
	SHOT_RELEASE, //  キー入力をやめた（球を打つ）
};

Player::Player() :
    m_pCamera(nullptr),
    m_move(0.0f, 0.0f, 0.0f),
    m_isStop(false),
    m_shotStep(SHOT_WAIT),
    m_power(0.0f),
    m_box({
        DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
        DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
        })
{
}

Player::~Player()
{
}
//更新処理
void Player::Update()
{
    //カメラが設定されていない場合は処理しない
    if (!m_pCamera) { return; }
    if (IsKeyPress('A'))
    {
        m_Rotation.z -= 0.9f;
    }
    if (IsKeyPress('D'))
    {
        m_Rotation.z += 0.9f;
    }
     if (IsKeyPress('W'))
    {
        m_Rotation.x -= 0.9f;
    }
    if (IsKeyPress('S'))
    {
        m_Rotation.x += 0.9f;
    }
    float pitch = DirectX::XMConvertToRadians(m_Rotation.x);
    float yaw = DirectX::XMConvertToRadians(m_Rotation.z);
    float roll = DirectX::XMConvertToRadians(m_Rotation.y);

    DirectX::XMMATRIX rotMatrix =
        DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    // 行列の z軸方向(row[2]) が forward になる
    DirectX::XMVECTOR forward = rotMatrix.r[2]; // r[2] は (x, y, z, w)
    // 移動量
    DirectX::XMVECTOR moveVec = DirectX::XMVectorScale(forward, 0.01f);

    // 位置を更新
    DirectX::XMVECTOR posVec = DirectX::XMLoadFloat3(&m_pos);
    posVec = DirectX::XMVectorAdd(posVec, moveVec);
    DirectX::XMStoreFloat3(&m_pos, posVec);

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
    // 移動処理 
    m_pos.x += m_move.x;
    m_pos.y += m_move.y;
    m_pos.z += m_move.z;

    // 減速処理(空気抵抗) 
    m_move.x *= 0.99f;
    m_move.y *= 0.99f;
    m_move.z *= 0.99f;

    //  重力
    m_move.y -= MSEC(GRAVITY);

    //  地面接触判定
    if (m_pos.y < 0.0f) {
        // 接触時の減速処理 
        m_move.x *= 0.95f;
        m_move.y *= 0.5f;
        m_move.z *= 0.95f;

        //  バウンド処理
        m_move.y = -m_move.y; // Yの移動方向を反転 
        if (m_move.y < CMETER(5.0f)) { //  バウンドが小さいか判定
            m_move.y = 0.0f;
            m_pos.y = 0.0f;
        }
        else {
            //  地面にめり込んでいるので、バウンドした場合の位置に変更
            m_pos.y = -m_pos.y;
        }
    }
   //  停止判定
    float speed;
    DirectX::XMVECTOR vMove = DirectX::XMLoadFloat3(&m_move);
    DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vMove);
    DirectX::XMStoreFloat(&speed, vLen);  // speedにvLenを格納 
    if (speed < CMSEC(30.0f)) { // 1秒間に30cmぐらい進むスピードであれば停止 
        m_isStop= true;
        m_shotStep = SHOT_WAIT;
    }
}
