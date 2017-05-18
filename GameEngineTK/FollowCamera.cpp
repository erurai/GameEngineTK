//////////////////////////////////////////////
//更新日:2017/05/15							//
//概要:フォローカメラクラスのソースファイル	//
//製作者:山岸正都							//
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

	//キーボードの状態の取得
	Keyboard::State key_state = m_keyboard->GetState();
	m_keyboard_tracker.Update(key_state);

	if (m_keyboard_tracker.IsKeyPressed(Keyboard::C))
	//フラグの切り替え
	if (m_view_point == false) { m_view_point = true; }
	else { m_view_point = false; }


	if(m_view_point == true)
	{	//FPS
		Vector3 position;
		//自機の上方0.2mの位置にカメラを置く
		position = m_target_pos + Vector3(0.0f, 0.2f, 0.0f);
		//参照点から視点への差分
		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DITANCE);
		//自機の後ろに回り込むための回転
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, -rotmat);
		eyepos = position + cameraV * 0.1f;
		//参照点座標を計算
		refpos = position + cameraV;

		//if (eyepos - cameraV * 0.1f == position)
		//{
		//	//ゴム紐カメラの処理
		//	//視点を現在位置から補間する
		//	eyepos = m_eyepos + (eyepos - m_eyepos) * 0.1f;
		//	//参照点を現在位置から補間する
		//	refpos = m_refpos + (refpos - m_refpos) * 0.1f;
		//}
	}
	else
	{	//TPS
		//自機の上方2mの位置を捉える
		refpos = m_target_pos + Vector3(0.0f, 2.0f, 0.0f);
		//参照点から視点への差分
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DITANCE);
		//自機の後ろに回り込むための回転
		Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
		//差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, -rotmat);

		//視点座標を計算
		eyepos = refpos + cameraV;

		//ゴム紐カメラの処理
		//視点を現在位置から補間する
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.075f;
		//参照点を現在位置から補間する
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}

	SetEyePos(eyepos);
	SetRefPos(refpos);

	//基底クラスの更新
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	//自機の上方2mの位置を捉える
	refpos = m_target_pos + Vector3(0.0f, 2.0f, 0.0f);
	//参照点から視点への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DITANCE);
	//自機の後ろに回り込むための回転
	Matrix rotmat = Matrix::CreateRotationY(m_target_angle);
	//差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, -rotmat);

	//視点座標を計算
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
