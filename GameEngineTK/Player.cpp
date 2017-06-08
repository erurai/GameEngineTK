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

	if (m_keystate.Space && (m_weapon_angle == 550.0f || m_weapon_angle == 1120.0f))
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

	if (m_transform_flag == true && m_weapon_angle > 550.0f)
	{
		TransformParts();
	}
	if (m_transform_flag == false && m_weapon_angle < 1120.0f)
	{
		RetrunParts();
	}

	for (vector<Obj3d>::iterator it = m_objPlayer.begin(); it != m_objPlayer.end(); it++)
	{
		it->Update();
	}

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
