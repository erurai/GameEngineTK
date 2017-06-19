#pragma once
#include "Collision.h"
#include "Obj3d.h"

/// <summary>
/// 当たり判定ノード
/// </summary>
class CollisionNode
{
public:
	virtual void Initialize() = 0;			//初期化
	virtual void Update() = 0;				//毎フレーム更新
	virtual void Draw() = 0;				//描画
	void SetObjParent(Obj3d* parent);		//親をセット
	//親からのオフセットをセット
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; }
protected:
	Obj3d m_obj;							//デバッグ表示オブジェクト
	DirectX::SimpleMath::Vector3 m_trans;	//親からのオフセット
};

//当たり判定球ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();		//コンストラクタ
	void Initialize();	//初期化
	void Update();		//毎フレーム更新
	void Draw();		//描画

	void SetLocalRadius(float radius) { m_localradius = radius; }

protected:
	float m_localradius;//ローカル半径
};