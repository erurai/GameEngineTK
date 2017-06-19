//////////////////////////////////////////
//更新日:2017/05/22						//
//概要:Playerのソースファイル	        //
//製作者:山岸正都						//
//////////////////////////////////////////

#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(Keyboard* keyboard)
{
	//キーボードの初期化
	m_keyboard = keyboard;

	//自機パーツの読み込み
	m_objPlayer.resize(PLAYER_PARTS_NUM);
	m_objPlayer[PLAYER_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objPlayer[PLAYER_PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_objPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_objPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_objPlayer[PLAYER_PARTS_ARM].LoadModel(L"Resources/arm.cmo");
	m_objPlayer[PLAYER_PARTS_GUN].LoadModel(L"Resources/gun.cmo");
	//m_objPlayer[PLAYER_PARTS_SHELD].LoadModel(L"Resources/sheld.cmo");

	//親子関係の構築
	m_objPlayer[PLAYER_PARTS_BASE].SetParentObj(&m_objPlayer[PLAYER_PARTS_TANK]);
	m_objPlayer[PLAYER_PARTS_BODY].SetParentObj(&m_objPlayer[PLAYER_PARTS_BASE]);
	m_objPlayer[PLAYER_PARTS_ARM].SetParentObj(&m_objPlayer[PLAYER_PARTS_BODY]);
	m_objPlayer[PLAYER_PARTS_HEAD].SetParentObj(&m_objPlayer[PLAYER_PARTS_BODY]);
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);
	//m_objPlayer[PLAYER_PARTS_SHELD].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	//親からのオフセット(ローカルの座標ずれ)
	m_objPlayer[PLAYER_PARTS_BASE].SetTransration(Vector3(0.05f, 0.4f, 0.5f));

	m_objPlayer[PLAYER_PARTS_BODY].SetTransration(Vector3(-0.1f, 0.7f, -0.6f));

	m_objPlayer[PLAYER_PARTS_HEAD].SetTransration(Vector3(0.1f, 0.07f, 0.55f));

	m_objPlayer[PLAYER_PARTS_ARM].SetTransration(Vector3(-0.3f, -0.1f, 0.25f));
	m_objPlayer[PLAYER_PARTS_ARM].SetRotation(Vector3(1120.0f / 360.0f, 0.0f, 0.0f));

	m_objPlayer[PLAYER_PARTS_GUN].SetTransration(Vector3(0.0f, 0.0f, 0.0f));
	m_objPlayer[PLAYER_PARTS_GUN].SetRotation(Vector3(550.0f / 360.0f, 0.0f, 0.0f));

	m_weapon_angle = 1120.0f;
	m_weapon_pos = m_objPlayer[PLAYER_PARTS_GUN].GetTransration();
	m_transform_flag = false;
	m_translate_flag = false;
	m_fireflag = false;
	m_firetime = 0;

	//当たり判定ノードの設定
	m_collisionnode_bullet.Initialize();
	//武器パーツにぶら下げる
	m_collisionnode_bullet.SetObjParent(&m_objPlayer[PLAYER_PARTS_GUN]);
	//武器パーツからのオフセット
	m_collisionnode_bullet.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	//当たり判定の半径
	m_collisionnode_bullet.SetLocalRadius(0.2f);
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	//キーボードの状態を取得
	m_keystate = m_keyboard->GetState();
	//auto state = m_keyboard->GetState();
	//m_keytracker->Update(state);

	//左旋回
	if (m_keystate.A)
	{
		//自機の方向を旋回
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle + 0.03f, 0.0f));
	}
	//右旋回
	if (m_keystate.D)
	{
		//自機の方向を旋回
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle - 0.03f, 0.0f));
	}
	//前進
	if (m_keystate.W)
	{
		//移動ベクトル
		Vector3 moveV(0.0f, 0.0f, 0.1f);
		//今の角度に合わせて移動ベクトルを回転
		//回転行列
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_objPlayer[PLAYER_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objPlayer[PLAYER_PARTS_TANK].SetTransration(pos);

	}
	//後進
	if (m_keystate.S)
	{
		//移動ベクトル
		Vector3 moveV(0.0f, 0.0f, -0.1f);
		//今の角度に合わせて移動ベクトルを回転
		//回転行列
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//自機の座標を移動
		Vector3 pos = m_objPlayer[PLAYER_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objPlayer[PLAYER_PARTS_TANK].SetTransration(pos);
	}

	if (m_keystate.Z && (m_weapon_angle == 550.0f || m_weapon_angle == 1120.0f))
	{
		if (m_transform_flag == false)
		{
			m_transform_flag = true;
		}
		else if (m_transform_flag == true)
		{
			m_transform_flag = false;
		}
	}

	//キーを押して発射
	if (m_keystate.Space)
	{
		BulletFire();
	}

	if (m_transform_flag == true && m_weapon_angle > 550.0f)
	{
		TransformParts();
	}
	if (m_transform_flag == false && m_weapon_angle < 1120.0f)
	{
		RetrunParts();
	}

	if(m_fireflag == true)
	{
		//自機の座標を移動
		Vector3 pos = m_objPlayer[PLAYER_PARTS_GUN].GetTransration();
		pos += m_bulletvec;
		m_objPlayer[PLAYER_PARTS_GUN].SetTransration(pos);

		m_firetime++;
		if (m_firetime >= 120)
		{
			m_firetime = 0;
			ResetBullet();
		}
	}

	for (vector<Obj3d>::iterator it = m_objPlayer.begin(); it != m_objPlayer.end(); it++)
	{
		it->Update();
	}

	//当たり判定ノードの更新
	m_collisionnode_bullet.Update();

}

/// <summary>
/// 描画
/// </summary>
void Player::Render()
{
	for (vector<Obj3d>::iterator it = m_objPlayer.begin(); it != m_objPlayer.end(); it++)
	{
		it->Draw();
	}

	m_collisionnode_bullet.Draw();
}

/// <summary>
/// パーツの変形(？)
/// </summary>
void Player::TransformParts()
{
	m_weapon_angle -= 10.0f;
	m_objPlayer[PLAYER_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// 変形させたパーツを元に戻す
/// </summary>
void Player::RetrunParts()
{
	m_weapon_angle += 10.0f;
	m_objPlayer[PLAYER_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// パーツを発射
/// </summary>
void Player::BulletFire()
{
	//既に発射中
	if (m_fireflag) return;
	if (!m_transform_flag) return;

	//親子関係を加味したワールド座標を取得
	Matrix worldm = m_objPlayer[PLAYER_PARTS_GUN].GetWorld();

	Vector3 scale;
	Quaternion rotation;
	Vector3 transration;

	//ワールド行列から各要素を取り出す
	worldm.Decompose(scale, rotation, transration);

	//親子関係を解除してパーツを独立させる
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(nullptr);
	m_objPlayer[PLAYER_PARTS_GUN].SetScale(scale);
	m_objPlayer[PLAYER_PARTS_GUN].SetRotationQ(rotation);
	m_objPlayer[PLAYER_PARTS_GUN].SetTransration(transration);

	//発射する弾丸の速度ベクトル
	m_bulletvec = Vector3(0.0f, 0.0f, -0.5f);
	//ベクトルをクォータニオンで回転
	m_bulletvec = Vector3::Transform(m_bulletvec, rotation);

	m_fireflag = true;

}

/// <summary>
/// 発射したパーツを戻す
/// </summary>
void Player::ResetBullet()
{
	//発射中ではない
	if (!m_fireflag) return;

	//パーツを戻す
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	m_objPlayer[PLAYER_PARTS_GUN].SetTransration(Vector3(0.0f, 0.0f, 0.0f));
	m_objPlayer[PLAYER_PARTS_GUN].SetRotation(Vector3(550.0f / 360.0f, 0.0f, 0.0f));

	m_fireflag = false;
}
