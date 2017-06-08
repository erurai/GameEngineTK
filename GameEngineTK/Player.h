//////////////////////////////////////////
//更新日:2017/05/22						//
//概要:Playerのソースファイル	        //
//製作者:山岸正都						//
//////////////////////////////////////////
#pragma once
#include "Obj3d.h"
#include <SimpleMath.h>
#include <Keyboard.h>

class Player
{
public:
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TANK,	//足
		PLAYER_PARTS_BASE,	//基底
		PLAYER_PARTS_BODY,	//体
		PLAYER_PARTS_HEAD,	//頭
		PLAYER_PARTS_ARM,	//腕
		PLAYER_PARTS_GUN,	//銃
		PLAYER_PARTS_SHELD,	//盾

		PLAYER_PARTS_NUM
	};

	Player(DirectX::Keyboard* keyboard);
	~Player();

	void Update();
	void Render();

	const DirectX::SimpleMath::Vector3& GetPlayerPos() { return m_objPlayer[PLAYER_PARTS_TANK].GetTransration(); }
	const DirectX::SimpleMath::Vector3& GetPlayerAngle() { return m_objPlayer[PLAYER_PARTS_TANK].GetRotation(); }

private:
	std::vector<Obj3d> m_objPlayer;
	void TransformParts();
	void RetrunParts();

	float m_weapon_angle;
	bool m_transform_flag;
	DirectX::SimpleMath::Vector3 m_weapon_pos;
	bool m_translate_flag;

	DirectX::Keyboard* m_keyboard;
	DirectX::Keyboard::State m_keystate;
};
