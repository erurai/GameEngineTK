//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:Player�̃\�[�X�t�@�C��	        //
//�����:�R�ݐ��s						//
//////////////////////////////////////////
#pragma once
#include "Obj3d.h"
#include <SimpleMath.h>
#include <Keyboard.h>

class Enemy
{
public:
	enum ENEMY_PARTS
	{
		ENEMY_PARTS_TANK,	//��
		ENEMY_PARTS_BASE,	//���
		ENEMY_PARTS_BODY,	//��
		ENEMY_PARTS_HEAD,	//��
		ENEMY_PARTS_ARM,	//�r
		ENEMY_PARTS_GUN,	//�e
		ENEMY_PARTS_SHELD,	//��

		ENEMY_PARTS_NUM
	};

	Enemy();
	~Enemy();

	void Update();
	void Render();

	const DirectX::SimpleMath::Vector3& GetEnemyPos() { return m_objEnemy[ENEMY_PARTS_TANK].GetTransration(); }
	const DirectX::SimpleMath::Vector3& GetEnemyAngle() { return m_objEnemy[ENEMY_PARTS_TANK].GetRotation(); }

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
};
