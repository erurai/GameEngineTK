//////////////////////////////////////////////
//更新日:2017/05/15							//
//概要:フォローカメラクラスのヘッダファイル	//
//製作者:山岸正都							//
//////////////////////////////////////////////

#pragma once

#include "Camera.h"
#include <Keyboard.h>

class FollowCamera : public Camera
{
public:
	FollowCamera(int width, int height);								//コンストラクタ
	~FollowCamera();													//デストラクタ

	void Update() override;
	void InitializeTPS();												//TPSカメラの初期化

	void SetTargetPos(const DirectX::SimpleMath::Vector3& target_pos);	//追従対象座標をセット
	void SetTargetAngle(const float& target_angle);						//追従対象角度をセット
	void SetKeyboard(DirectX::Keyboard* keyboard);						//キーボードをセット

	const static float CAMERA_DITANCE;									//カメラと時期の距離

protected:
	DirectX::SimpleMath::Vector3 m_target_pos;					//追従対象の座標
	float m_target_angle;										//追従対象の角度
	DirectX::Keyboard* m_keyboard;								//キーボード
	DirectX::Keyboard::KeyboardStateTracker m_keyboard_tracker;	//キーボードトラッカー
	bool m_view_point;											//視点のフラグ

};
