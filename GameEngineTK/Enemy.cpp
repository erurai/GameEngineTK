//////////////////////////////////////////
//更新日:2017/05/22						//
//概要:Playerのソースファイル	        //
//製作者:山岸正都						//
//////////////////////////////////////////

#include "Enemy.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	//自機パーツの読み込み
	m_objEnemy.resize(ENEMY_PARTS_NUM);
	m_objEnemy[ENEMY_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objEnemy[ENEMY_PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_objEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_objEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_objEnemy[ENEMY_PARTS_ARM].LoadModel(L"Resources/arm.cmo");
	m_objEnemy[ENEMY_PARTS_GUN].LoadModel(L"Resources/gun.cmo");
	//m_objPlayer[PLAYER_PARTS_SHELD].LoadModel(L"Resources/sheld.cmo");

	//親子関係の構築
	m_objEnemy[ENEMY_PARTS_BASE].SetParentObj(&m_objEnemy[ENEMY_PARTS_TANK]);
	m_objEnemy[ENEMY_PARTS_BODY].SetParentObj(&m_objEnemy[ENEMY_PARTS_BASE]);
	m_objEnemy[ENEMY_PARTS_ARM].SetParentObj(&m_objEnemy[ENEMY_PARTS_BODY]);
	m_objEnemy[ENEMY_PARTS_HEAD].SetParentObj(&m_objEnemy[ENEMY_PARTS_BODY]);
	m_objEnemy[ENEMY_PARTS_GUN].SetParentObj(&m_objEnemy[ENEMY_PARTS_ARM]);
	//m_objPlayer[PLAYER_PARTS_SHELD].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	//親からのオフセット(ローカルの座標ずれ)
	m_objEnemy[ENEMY_PARTS_BASE].SetTransration(Vector3(0.05f, 0.4f, 0.5f));

	m_objEnemy[ENEMY_PARTS_BODY].SetTransration(Vector3(-0.1f, 0.7f, -0.6f));

	m_objEnemy[ENEMY_PARTS_HEAD].SetTransration(Vector3(0.1f, 0.07f, 0.55f));

	m_objEnemy[ENEMY_PARTS_ARM].SetTransration(Vector3(-0.3f, -0.1f, 0.25f));
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(1120.0f / 360.0f, 0.0f, 0.0f));

	m_objEnemy[ENEMY_PARTS_GUN].SetTransration(Vector3(0.0f, 0.0f, 0.0f));
	m_objEnemy[ENEMY_PARTS_GUN].SetRotation(Vector3(550.0f / 360.0f, 0.0f, 0.0f));

	//初期座標をランダムに決定
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;
	m_objEnemy[ENEMY_PARTS_TANK].SetTransration(pos);

	m_weapon_angle = 1120.0f;
	m_weapon_pos = m_objEnemy[ENEMY_PARTS_GUN].GetTransration();
	m_transform_flag = false;
	m_translate_flag = false;
	m_accel = true;
	m_time = 60;
	m_dist_angle = 0.0f;

	//当たり判定ノードの設定
	m_collisionnode.Initialize();
	//パーツにぶら下げる
	m_collisionnode.SetObjParent(&m_objEnemy[ENEMY_PARTS_BASE]);
	//パーツからのオフセット
	m_collisionnode.SetTrans(Vector3(0.0f, 0.5f, 0.0f));
	//当たり判定の半径
	m_collisionnode.SetLocalRadius(1.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{

}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{

	MoveAI();
	//TransformAI();

	for (vector<Obj3d>::iterator it = m_objEnemy.begin(); it != m_objEnemy.end(); it++)
	{
		it->Update();
	}

	m_collisionnode.Update();

}

/// <summary>
/// 描画
/// </summary>
void Enemy::Render()
{
	for (vector<Obj3d>::iterator it = m_objEnemy.begin(); it != m_objEnemy.end(); it++)
	{
		it->Draw();
	}

	m_collisionnode.Draw();
}

/// <summary>
/// パーツの変形(？)
/// </summary>
void Enemy::TransformParts()
{
	m_weapon_angle -= 10.0f;
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// 変形させたパーツを元に戻す
/// </summary>
void Enemy::RetrunParts()
{
	m_weapon_angle += 10.0f;
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

void Enemy::MoveAI()
{
	////左旋回
	//if (m_keystate.A)
	//{
	//	//自機の方向を旋回
	//	float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
	//	m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle + 0.03f, 0.0f));
	//}
	////右旋回
	//if (m_keystate.D)
	//{
	//	//自機の方向を旋回
	//	float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
	//	m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle - 0.03f, 0.0f));
	//}

	m_time--;

	//定期的に進行方向を変える
	if (m_time < 0)
	{
		m_time = 60;

		//目標角度の再抽選
		//-0.5～0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//-90～90の乱数
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_dist_angle += rnd;
	}

	//目標角度にじわじわと回転
	Vector3 rot = m_objEnemy[ENEMY_PARTS_TANK].GetRotation();
	float angle = m_dist_angle - rot.y;
	if (angle > XM_PI)
	{
		angle -= XM_2PI;
	}
	if (angle < -XM_PI)
	{
		angle += XM_2PI;
	}
	rot.y += angle * 0.02;

	//敵の角度を変更
	m_objEnemy[ENEMY_PARTS_TANK].SetRotation(Vector3(0.0f, rot.y, 0.0f));

	//前進
	if (m_accel == true)
	{
		//移動ベクトル
		Vector3 moveV(0.0f, 0.0f, 0.1f);
		//今の角度に合わせて移動ベクトルを回転
		//回転行列
		float angle = m_objEnemy[ENEMY_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_objEnemy[ENEMY_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objEnemy[ENEMY_PARTS_TANK].SetTransration(pos);

	}
	//後進
	else if (m_accel == false)
	{
		//移動ベクトル
		Vector3 moveV(0.0f, 0.0f, -0.1f);
		//今の角度に合わせて移動ベクトルを回転
		//回転行列
		float angle = m_objEnemy[ENEMY_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_objEnemy[ENEMY_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objEnemy[ENEMY_PARTS_TANK].SetTransration(pos);
	}
}

void Enemy::TransformAI()
{
	//if (m_keystate.Space && (m_weapon_angle == 550.0f || m_weapon_angle == 1120.0f))
	//{
	//	if (m_transform_flag == false)
	//	{
	//		m_transform_flag = true;
	//	}
	//	else if (m_transform_flag == true)
	//	{
	//		m_transform_flag = false;
	//	}
	//}

	//if (m_transform_flag == true && m_weapon_angle > 550.0f)
	//{
	//	TransformParts();
	//}
	//if (m_transform_flag == false && m_weapon_angle < 1120.0f)
	//{
	//	RetrunParts();
	//}
}