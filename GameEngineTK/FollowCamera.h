//////////////////////////////////////////////
//更新日:2017/05/15							//
//概要:フォローカメラクラスのヘッダファイル	//
//製作者:山岸正都							//
//////////////////////////////////////////////

#pragma once

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	FollowCamera(int width, int height);//コンストラクタ
	~FollowCamera();					//デストラクタ

	void Update() override;
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target_pos);	//追従対象座標をセット
	void SetTargetAngle(const float& target_angle);						//追従対象角度をセット

	const static float CAMERA_DITANCE;	//カメラと時期の距離

protected:
	DirectX::SimpleMath::Vector3 m_target_pos;	//追従対象の座標
	float m_target_angle;						//追従対象の角度

};
