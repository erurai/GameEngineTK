//////////////////////////////////////////////
//�X�V��:2017/05/15							//
//�T�v:�t�H���[�J�����N���X�̃\�[�X�t�@�C��	//
//�����:�R�ݐ��s							//
//////////////////////////////////////////////

#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float FollowCamera::CAMERA_DITANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height) : Camera(width, height)
{
	m_target_pos = Vector3::Zero;
	m_target_angle = 0.0f;
	m_keyboard = nullptr;
	m_view_point = false;

	InitializeTPS();
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
{
	Vector3 eyepos, refpos;

	//�L�[�{�[�h�̏�Ԃ̎擾
	Keyboard::State key_state = m_keyboard->GetState();
	m_keyboard_tracker.Update(key_state);

	if (m_keyboard_tracker.IsKeyPressed(Keyboard::C))
	//�t���O�̐؂�ւ�
	if (m_view_point == false) { m_view_point = true; }
	else { m_view_point = false; }


	if(m_view_point == true)
	{	//FPS
		Vector3 position;
		//���@�̏��0.2m�̈ʒu�ɃJ������u��
		position = m_target_pos + Vector3(0.0f, 0.2f, 0.0f);
		//�Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DITANCE);
		//���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, -rotmat);
		eyepos = position + cameraV * 0.1f;
		//�Q�Ɠ_���W���v�Z
		refpos = position + cameraV;

		//if (eyepos - cameraV * 0.1f == position)
		//{
		//	//�S���R�J�����̏���
		//	//���_�����݈ʒu�����Ԃ���
		//	eyepos = m_eyepos + (eyepos - m_eyepos) * 0.1f;
		//	//�Q�Ɠ_�����݈ʒu�����Ԃ���
		//	refpos = m_refpos + (refpos - m_refpos) * 0.1f;
		//}
	}
	else
	{	//TPS
		//���@�̏��2m�̈ʒu�𑨂���
		refpos = m_target_pos + Vector3(0.0f, 2.0f, 0.0f);
		//�Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DITANCE);
		//���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, -rotmat);

		//���_���W���v�Z
		eyepos = refpos + cameraV;

		//�S���R�J�����̏���
		//���_�����݈ʒu�����Ԃ���
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.075f;
		//�Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	//���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	//���@�̏��2m�̈ʒu�𑨂���
	refpos = m_target_pos + Vector3(0.0f, 2.0f, 0.0f);
	//�Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DITANCE);
	//���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
	//�����x�N�g������]������
	cameraV = Vector3::TransformNormal(cameraV, -rotmat);

	//���_���W���v�Z
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);
}

void FollowCamera::SetTargetPos(const Vector3& target_pos)
{
	m_target_pos = target_pos;
}

void FollowCamera::SetTargetAngle(const float& target_angle)
{
	m_target_angle = target_angle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
