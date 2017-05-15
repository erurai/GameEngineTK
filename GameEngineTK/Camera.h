//////////////////////////////////////
//�X�V��:2017/05/11					//
//�T�v:�J�����N���X�̃w�b�_�t�@�C��	//
//�����:�R�ݐ��s					//
//////////////////////////////////////
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	virtual void Update();		//�X�V
	const DirectX::SimpleMath::Matrix GetViewMatrix();			//�r���[�s����擾
	const DirectX::SimpleMath::Matrix GetProjMatrix();			//�ˉe�s����擾

	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);	//���_���W���Z�b�g
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);	//�����_���Z�b�g
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);		//������x�N�g�����Z�b�g

	void SetFovY(const float& fovY);								//������������p���Z�b�g
	void SetAspect(const float& aspect);							//�A�X�y�N�g����Z�b�g
	void SetNearClip(const float& nearclip);						//��O�̕\�����E�������Z�b�g
	void SetFarClip(const float& farclip);							//���̕\�����E�������Z�b�g

protected:
	DirectX::SimpleMath::Matrix m_view;						//�r���[�s��
	DirectX::SimpleMath::Vector3 m_eyepos;					//�J�����̈ʒu(���_���W)
	DirectX::SimpleMath::Vector3 m_refpos;					//�ǂ�������̂�(�����_/�Q�Ɠ_)
	DirectX::SimpleMath::Vector3 m_upvec;					//������x�N�g��

	DirectX::SimpleMath::Matrix m_proj;						//�ˉe�s��
	float m_fovY;											//������������p
	float m_aspect;											//��ʉ����Əc���̔䗦(�A�X�y�N�g��)
	float m_nearclip;										//��O�̕\�����E����
	float m_farclip;										//���̕\�����E����
	
};
