//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:Player�̃\�[�X�t�@�C��	        //
//�����:�R�ݐ��s						//
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
		PLAYER_PARTS_TANK,	//��
		PLAYER_PARTS_BASE,	//���
		PLAYER_PARTS_BODY,	//��
		PLAYER_PARTS_HEAD,	//��
		PLAYER_PARTS_ARM,	//�r
		PLAYER_PARTS_GUN,	//�e
		PLAYER_PARTS_SHELD,	//��

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
