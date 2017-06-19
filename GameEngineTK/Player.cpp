//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:Player�̃\�[�X�t�@�C��	        //
//�����:�R�ݐ��s						//
//////////////////////////////////////////

#include "Player.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player(Keyboard* keyboard)
{
	//�L�[�{�[�h�̏�����
	m_keyboard = keyboard;

	//���@�p�[�c�̓ǂݍ���
	m_objPlayer.resize(PLAYER_PARTS_NUM);
	m_objPlayer[PLAYER_PARTS_TANK].LoadModel(L"Resources/tank.cmo");
	m_objPlayer[PLAYER_PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_objPlayer[PLAYER_PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_objPlayer[PLAYER_PARTS_HEAD].LoadModel(L"Resources/head.cmo");
	m_objPlayer[PLAYER_PARTS_ARM].LoadModel(L"Resources/arm.cmo");
	m_objPlayer[PLAYER_PARTS_GUN].LoadModel(L"Resources/gun.cmo");
	//m_objPlayer[PLAYER_PARTS_SHELD].LoadModel(L"Resources/sheld.cmo");

	//�e�q�֌W�̍\�z
	m_objPlayer[PLAYER_PARTS_BASE].SetParentObj(&m_objPlayer[PLAYER_PARTS_TANK]);
	m_objPlayer[PLAYER_PARTS_BODY].SetParentObj(&m_objPlayer[PLAYER_PARTS_BASE]);
	m_objPlayer[PLAYER_PARTS_ARM].SetParentObj(&m_objPlayer[PLAYER_PARTS_BODY]);
	m_objPlayer[PLAYER_PARTS_HEAD].SetParentObj(&m_objPlayer[PLAYER_PARTS_BODY]);
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);
	//m_objPlayer[PLAYER_PARTS_SHELD].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	//�e����̃I�t�Z�b�g(���[�J���̍��W����)
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

	//�����蔻��m�[�h�̐ݒ�
	m_collisionnode_bullet.Initialize();
	//����p�[�c�ɂԂ牺����
	m_collisionnode_bullet.SetObjParent(&m_objPlayer[PLAYER_PARTS_GUN]);
	//����p�[�c����̃I�t�Z�b�g
	m_collisionnode_bullet.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	//�����蔻��̔��a
	m_collisionnode_bullet.SetLocalRadius(0.2f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
/// �X�V
/// </summary>
void Player::Update()
{
	//�L�[�{�[�h�̏�Ԃ��擾
	m_keystate = m_keyboard->GetState();
	//auto state = m_keyboard->GetState();
	//m_keytracker->Update(state);

	//������
	if (m_keystate.A)
	{
		//���@�̕��������
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle + 0.03f, 0.0f));
	}
	//�E����
	if (m_keystate.D)
	{
		//���@�̕��������
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		m_objPlayer[PLAYER_PARTS_TANK].SetRotation(Vector3(0.0f, angle - 0.03f, 0.0f));
	}
	//�O�i
	if (m_keystate.W)
	{
		//�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, 0.1f);
		//���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		//��]�s��
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�
		Vector3 pos = m_objPlayer[PLAYER_PARTS_TANK].GetTransration();
		pos += moveV;
		m_objPlayer[PLAYER_PARTS_TANK].SetTransration(pos);

	}
	//��i
	if (m_keystate.S)
	{
		//�ړ��x�N�g��
		Vector3 moveV(0.0f, 0.0f, -0.1f);
		//���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		//��]�s��
		float angle = m_objPlayer[PLAYER_PARTS_TANK].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		//���@�̍��W���ړ�
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

	//�L�[�������Ĕ���
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
		//���@�̍��W���ړ�
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

	//�����蔻��m�[�h�̍X�V
	m_collisionnode_bullet.Update();

}

/// <summary>
/// �`��
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
/// �p�[�c�̕ό`(�H)
/// </summary>
void Player::TransformParts()
{
	m_weapon_angle -= 10.0f;
	m_objPlayer[PLAYER_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// �ό`�������p�[�c�����ɖ߂�
/// </summary>
void Player::RetrunParts()
{
	m_weapon_angle += 10.0f;
	m_objPlayer[PLAYER_PARTS_ARM].SetRotation(Vector3(m_weapon_angle / 360.0f, 0.0f, 0.0f));
}

/// <summary>
/// �p�[�c�𔭎�
/// </summary>
void Player::BulletFire()
{
	//���ɔ��˒�
	if (m_fireflag) return;
	if (!m_transform_flag) return;

	//�e�q�֌W�������������[���h���W���擾
	Matrix worldm = m_objPlayer[PLAYER_PARTS_GUN].GetWorld();

	Vector3 scale;
	Quaternion rotation;
	Vector3 transration;

	//���[���h�s�񂩂�e�v�f�����o��
	worldm.Decompose(scale, rotation, transration);

	//�e�q�֌W���������ăp�[�c��Ɨ�������
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(nullptr);
	m_objPlayer[PLAYER_PARTS_GUN].SetScale(scale);
	m_objPlayer[PLAYER_PARTS_GUN].SetRotationQ(rotation);
	m_objPlayer[PLAYER_PARTS_GUN].SetTransration(transration);

	//���˂���e�ۂ̑��x�x�N�g��
	m_bulletvec = Vector3(0.0f, 0.0f, -0.5f);
	//�x�N�g�����N�H�[�^�j�I���ŉ�]
	m_bulletvec = Vector3::Transform(m_bulletvec, rotation);

	m_fireflag = true;

}

/// <summary>
/// ���˂����p�[�c��߂�
/// </summary>
void Player::ResetBullet()
{
	//���˒��ł͂Ȃ�
	if (!m_fireflag) return;

	//�p�[�c��߂�
	m_objPlayer[PLAYER_PARTS_GUN].SetParentObj(&m_objPlayer[PLAYER_PARTS_ARM]);

	m_objPlayer[PLAYER_PARTS_GUN].SetTransration(Vector3(0.0f, 0.0f, 0.0f));
	m_objPlayer[PLAYER_PARTS_GUN].SetRotation(Vector3(550.0f / 360.0f, 0.0f, 0.0f));

	m_fireflag = false;
}
