//////////////////////////////////////////////
//�X�V��:2017/05/15							//
//�T�v:�t�H���[�J�����N���X�̃w�b�_�t�@�C��	//
//�����:�R�ݐ��s							//
//////////////////////////////////////////////

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	FollowCamera(int width, int height);//�R���X�g���N�^
	~FollowCamera();					//�f�X�g���N�^

	void Update() override;
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target_pos);	//�Ǐ]�Ώۍ��W���Z�b�g
	void SetTargetAngle(const float& target_angle);						//�Ǐ]�Ώۊp�x���Z�b�g

	const static float CAMERA_DITANCE;	//�J�����Ǝ����̋���

protected:
	DirectX::SimpleMath::Vector3 m_target_pos;	//�Ǐ]�Ώۂ̍��W
	float m_target_angle;						//�Ǐ]�Ώۂ̊p�x

};
