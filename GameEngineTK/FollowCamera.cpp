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
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
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

	//���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(const Vector3& target_pos)
{
	m_target_pos = target_pos;
}

void FollowCamera::SetTargetAngle(const float& target_angle)
{
	m_target_angle = target_angle;
}