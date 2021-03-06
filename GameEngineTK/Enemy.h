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

class Enemy
{
public:
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_TANK,	//«
		ENEMY_PARTS_BASE,	//îê
		ENEMY_PARTS_BODY,	//Ì
		ENEMY_PARTS_HEAD,	//ª
		ENEMY_PARTS_ARM,	//r
		ENEMY_PARTS_GUN,	//e
		ENEMY_PARTS_SHELD,	//

		ENEMY_PARTS_NUM
	};

	Enemy();
	~Enemy();

	void Update();
	void Render();

	const DirectX::SimpleMath::Vector3& GetEnemyPos() { return m_objEnemy[ENEMY_PARTS_TANK].GetTransration(); }
	const DirectX::SimpleMath::Vector3& GetEnemyAngle() { return m_objEnemy[ENEMY_PARTS_TANK].GetRotation(); }
	const SphereNode& GetCollisionNodeBody() { return m_collisionnode; }

private:
	std::vector<Obj3d> m_objEnemy;
	void TransformParts();
	void RetrunParts();
	void MoveAI();
	void TransformAI();

	float m_weapon_angle;
	bool m_transform_flag;
	DirectX::SimpleMath::Vector3 m_weapon_pos;
	bool m_translate_flag;
	bool m_accel;
	int m_time;
	float m_dist_angle;

	SphereNode m_collisionnode;	//½è»èm[h
};
