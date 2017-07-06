#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_debug_visible;

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

	//���苅�̗v�f���v�Z
	const Matrix& worldm = m_obj.GetWorld();
	//���f�����W�n�ł̒��S�_
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);
	//���[���h���W�ɕϊ�
	center = Vector3::Transform(center, worldm);
	right = Vector3::Transform(right, worldm);
	//���苅�̗v�f����
	Sphere::Center = center;
	Sphere::Radius = Vector3::Distance(center, right);
}

void SphereNode::Draw()
{
	//�f�o�b�O�p���f����`��
	m_obj.Draw();
}
