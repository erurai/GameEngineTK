#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// CollisionNode�N���X�̊֐�
/// </summary>

void CollisionNode::SetObjParent(Obj3d * parent)
{
	m_obj.SetParentObj(parent);
}

/// <summary>
/// SphereNode�N���X�̊֐�
/// </summary>

//�R���X�g���N�^
SphereNode::SphereNode()
{
	//�f�t�H���g���a
	m_localradius = 1.0f;
}

void SphereNode::Initialize()
{
	//�f�o�b�O�\���p���f����ǂݍ���
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTransration(m_trans);
	m_obj.SetScale(Vector3(m_localradius));

	//�s����X�V
	m_obj.Update();
}

void SphereNode::Draw()
{
	//�f�o�b�O�p���f����`��
	m_obj.Draw();
}
