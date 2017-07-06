#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_debug_visible;

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

	//判定球の要素を計算
	const Matrix& worldm = m_obj.GetWorld();
	//モデル座標系での中心点
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);
	//ワールド座標に変換
	center = Vector3::Transform(center, worldm);
	right = Vector3::Transform(right, worldm);
	//判定球の要素を代入
	Sphere::Center = center;
	Sphere::Radius = Vector3::Distance(center, right);
}

void SphereNode::Draw()
{
	//デバッグ用モデルを描画
	m_obj.Draw();
}
