#include "TrashObject.h"
#include"Geometory.h"

TrashObject::TrashObject()
{

}

TrashObject::TrashObject(DirectX::XMFLOAT3 InitPos):GameObject(InitPos)
{
    m_box = {
DirectX::XMFLOAT3(m_pos),
DirectX::XMFLOAT3(0.4f,0.4f,0.4f)
    };
}

TrashObject::~TrashObject()
{
}

void TrashObject::Update()
{
}

void TrashObject::Draw()
{
    DirectX::XMFLOAT4X4 world;
    DirectX::XMMATRIX T =
        DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    DirectX::XMMATRIX S =
        DirectX::XMMatrixScaling(0.4f, 0.4f, 0.4f);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_Rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_Rotation.z)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rotation.y)); // ‰ñ“]
    DirectX::XMMATRIX mat = S * R * T;
    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat));
    Geometory::SetWorld(world);
    Geometory::DrawBox();
}
