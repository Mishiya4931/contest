#include "Wall.h"
#include"Geometory.h"
Wall::Wall()
{
}

Wall::Wall(DirectX::XMFLOAT3 InitPos, DirectX::XMFLOAT3 InitRotation, DirectX::XMFLOAT3 InitSize,int No)
{
    m_pos = InitPos;
    m_box = { m_pos, InitSize };
    m_Rotation = InitRotation;
    m_nNo = No;
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
    DirectX::XMFLOAT4X4 world;
    DirectX::XMMATRIX T =
        DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    DirectX::XMMATRIX S =
        DirectX::XMMatrixScaling(m_box.size.x, m_box.size.y, m_box.size.z);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // ‰ñ“]
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat));
    Geometory::SetWorld(world);

    Geometory::DrawBox();
}
