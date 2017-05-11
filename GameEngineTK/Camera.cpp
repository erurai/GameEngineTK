//////////////////////////////////////
//�X�V��:2017/05/11					//
//�T�v:�J�����N���X�̃\�[�X�t�@�C��	//
//�����:�R�ݐ��s					//
//////////////////////////////////////

#include "Camera.h"

using namespace std;
using namespace DirectX;
using namespace SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int width, int height)
{
	m_eyepos = Vector3(0.0f, 0.0f, 5.0f);
	m_refpos = Vector3(0.0f, 0.0f, 0.0f);
	m_upvec = Vector3(0.0f, 1.0f, 0.0f);
	m_upvec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = float(width) / float(height);
	m_nearclip = 0.1f;
	m_farclip = 500.0f;

	//�r���[�s��𐶐�
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//�ˉe�s��𐶐�
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// �J�����̍X�V
/// </summary>
void Camera::Update()
{
	//�r���[�s��𐶐�
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//�ˉe�s��𐶐�
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

/// <summary>
/// �r���[�s����擾
/// </summary>
/// <returns>�r���[�s��</returns>
Matrix Camera::GetViewMatrix()
{
	return m_view;
}

/// <summary>
/// �ˉe�s����擾
/// </summary>
/// <returns>�ˉe�s��</returns>
Matrix Camera::GetProjMatrix()
{
	return m_proj;
}

/// <summary>
/// ���_���W���Z�b�g
/// </summary>
/// <param name="eyepos">���_���W�s��</param>
void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyepos = eyepos + Vector3(0.0f,2.0f,-4.0f);
}

/// <summary>
/// �����_���W���Z�b�g
/// </summary>
/// <param name="refpos">�����_���W</param>
void Camera::SetRefPos(Vector3 refpos)
{
	m_refpos = refpos;
}

/// <summary>
/// ������x�N�g�����Z�b�g
/// </summary>
/// <param name="upvec">������x�N�g��</param>
void Camera::SetUpVec(Vector3 upvec)
{
	m_upvec = upvec;
}

/// <summary>
/// ������������p���Z�b�g
/// </summary>
/// <param name="fovY">������������p</param>
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

/// <summary>
/// �A�X�y�N�g����Z�b�g
/// </summary>
/// <param name="aspect">�A�X�y�N�g��</param>
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

/// <summary>
/// ��O�̕\�����E�������Z�b�g
/// </summary>
/// <param name="nearclip">��O�̕\�����E����</param>
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

/// <summary>
/// ���̕\�����E�������Z�b�g
/// </summary>
/// <param name="farclip">���̕\�����E����</param>
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}