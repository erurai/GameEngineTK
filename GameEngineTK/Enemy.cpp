//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:Player�̃\�[�X�t�@�C��	        //
//�����:�R�ݐ��s						//
//////////////////////////////////////////

#include "Enemy.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	//���@�p�[�c�̓ǂݍ���
	m_objEnemy.resize(ENEMY_PARTS_NUM);
	m_objEnemy[ENEMY_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objEnemy[ENEMY_PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_objEnemy[ENEMY_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_objEnemy[ENEMY_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_objEnemy[ENEMY_PARTS_ARM].LoadModel(L"Resources/arm.cmo");
	m_objEnemy[ENEMY_PARTS_GUN].LoadModel(L"Resources/gun.cmo");
	//m_objPlayer[PLAYER_PARTS_SHELD].LoadModel(L"Resources/sheld.cmo");

	//�e�q�֌W�̍\�z
	m_objEnemy[ENEMY_PARTS_BASE].SetParentObj(&m_objEnemy[ENEMY_PARTS_TANK]);
	m_objEnemy[ENEMY_PARTS_BODY].SetParentObj(&m_objEnemy[ENEMY_PARTS_BASE]);
	m_objEnemy[ENEMY_PARTS_ARM].SetParentObj(&m_objEnemy[ENEMY_PARTS_BODY]);
	m_objEnemy[ENEMY_PARTS_HEAD].SetParentObj(&m_objEnemy[ENEMY_PARTS_BODY]);
	m_objEnemy[ENEMY_PARTS_GUN].SetParentObj(&m_objEnemy[ENEMY_PARTS_ARM]);
	//m_objPlayer[PLAYER_PARTS_SHELD].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	//�e����̃I�t�Z�b�g(���[�J���̍��W����)
	m_objEnemy[ENEMY_PARTS_BASE].SetTransration(Vector3(0.05f, 0.4f, 0.5f));

	m_objEnemy[ENEMY_PARTS_BODY].SetTransration(Vector3(-0.1f, 0.7f, -0.6f));

	m_objEnemy[ENEMY_PARTS_HEAD].SetTransration(Vector3(0.1f, 0.07f, 0.55f));

	m_objEnemy[ENEMY_PARTS_ARM].SetTransration(Vector3(-0.3f, -0.1f, 0.25f));
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(1120.0f / 360.0f, 0.0f, 0.0f));

	m_objEnemy[ENEMY_PARTS_GUN].SetTransration(Vector3(0.0f, 0.0f, 0.0f));
	m_objEnemy[ENEMY_PARTS_GUN].SetRotation(Vector3(550.0f / 360.0f, 0.0f, 0.0f));

	//�������W�������_���Ɍ���
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

	//�����蔻��m�[�h�̐ݒ�
	m_collisionnode.Initialize();
	//�p�[�c�ɂԂ牺����
	m_collisionnode.SetObjParent(&m_objEnemy[ENEMY_PARTS_BASE]);
	//�p�[�c����̃I�t�Z�b�g
	m_collisionnode.SetTrans(Vector3(0.0f, 0.5f, 0.0f));
	//�����蔻��̔��a
	m_collisionnode.SetLocalRadius(1.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{

}

/// <summary>
/// �X�V
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
/// �`��
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
/// �p�[�c�̕ό`(�H)
/// </summary>
void Enemy::TransformParts()
{
	m_weapon_angle -= 10.0f;
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// �ό`�������p�[�c�����ɖ߂�
/// </summary>
void Enemy::RetrunParts()
{
	m_weapon_angle += 10.0f;
	m_objEnemy[ENEMY_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

void Enemy::MoveAI()
{
	////������
	//if (m_keystate.A)
	//{
	//	//���@�̕��������
	//	float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
	//	m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle + 0.03f, 0.0f));
	//}
	////�E����
	//if (m_keystate.D)
	//{
	//	//���@�̕��������
	//	float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
	//	m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle - 0.03f, 0.0f));
	//}

	m_time--;

	//����I�ɐi�s������ς���
	if (m_time < 0)
	{
		m_time = 60;

		//�ڕW�p�x�̍Ē��I
		//-0.5�`0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		//-90�`90�̗���
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_dist_angle += rnd;
	}

	//�ڕW�p�x�ɂ��킶��Ɖ�]
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

	//�G�̊p�x��ύX
	m_objEnemy[ENEMY_PARTS_TANK].SetRotation(Vector3(0.0f, rot.y, 0.0f));

	//�O�i
	if (m_accel == true)
	{
		//�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, 0.1f);
		//���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		//��]�s��
		float angle = m_objEnemy[ENEMY_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�
		Vector3 pos = m_objEnemy[ENEMY_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objEnemy[ENEMY_PARTS_TANK].SetTransration(pos);

	}
	//��i
	else if (m_accel == false)
	{
		//�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, -0.1f);
		//���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		//��]�s��
		float angle = m_objEnemy[ENEMY_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�
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