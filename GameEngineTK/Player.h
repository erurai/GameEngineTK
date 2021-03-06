//////////////////////////////////////////
//XVú:2017/05/22						//
//Tv:PlayerÌ\[Xt@C	        //
//»ìÒ:RÝ³s						//
//////////////////////////////////////////
#pragma once
#include "Obj3d.h"
#include <SimpleMath.h>
#include <Keyboard.h>
#include "CollisionNode.h"
#include "State.h"
#include "Standing.h"
#include "Shot.h"

class State;

class Player
{
public:
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_TANK,	//«
		PLAYER_PARTS_BASE,	//îê
		PLAYER_PARTS_BODY,	//Ì
		PLAYER_PARTS_HEAD,	//ª
		PLAYER_PARTS_ARM,	//r
		PLAYER_PARTS_GUN,	//e
		PLAYER_PARTS_SHELD,	//

		PLAYER_PARTS_NUM
	};

	Player(DirectX::Keyboard* keyboard);
	~Player();

	void Update();
	void Render();
	void BulletFire();
	void ResetBullet();

	const DirectX::SimpleMath::Vector3& GetPlayerPos() { return m_objPlayer[PLAYER_PARTS_TANK].GetTransration(); }
	const DirectX::SimpleMath::Vector3& GetPlayerAngle() { return m_objPlayer[PLAYER_PARTS_TANK].GetRotation(); }
	const SphereNode& GetCollisionNodeBullet() { return m_collisionnode_bullet; }
	const DirectX::Keyboard::State GetKeyState() { return m_keystate; }
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTracker() { return this->m_keyboard_tracker; }

	void ChangeState(std::shared_ptr<State> currentState);

private:
	std::vector<Obj3d> m_objPlayer;
	void TransformParts();
	void RetrunParts();

	float m_weapon_angle;
	bool m_transform_flag;
	DirectX::SimpleMath::Vector3 m_weapon_pos;
	bool m_translate_flag;
	bool m_fireflag;
	DirectX::SimpleMath::Vector3 m_bulletvec;
	int m_firetime;
	float m_speed;
	float m_anglespeed;

	SphereNode m_collisionnode_bullet;	//½è»èm[h

	DirectX::Keyboard* m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboard_tracker;
	DirectX::Keyboard::State m_keystate;
	std::shared_ptr<State> currentState;
};
