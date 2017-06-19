#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// CollisionNodeクラスの関数
/// </summary>

void CollisionNode::SetObjParent(Obj3d * parent)
{
	m_obj.SetParentObj(parent);
}

/// <summary>
/// SphereNodeクラスの関数
/// </summary>

//コンストラクタ
SphereNode::SphereNode()
{
	//デフォルト半径
	m_localradius = 1.0f;
}

void SphereNode::Initialize()
{
	//デバッグ表示用モデルを読み込む
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTransration(m_trans);
	m_obj.SetScale(Vector3(m_localradius));

	//行列を更新
	m_obj.Update();
}

void SphereNode::Draw()
{
	//デバッグ用モデルを描画
	m_obj.Draw();
}
