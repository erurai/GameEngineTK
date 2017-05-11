//////////////////////////////////////
//更新日:2017/05/11					//
//概要:カメラクラスのソースファイル	//
//製作者:山岸正都					//
//////////////////////////////////////

#include "Camera.h"

using namespace std;
using namespace DirectX;
using namespace SimpleMath;

/// <summary>
/// コンストラクタ
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

	//ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列を生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{

}

/// <summary>
/// カメラの更新
/// </summary>
void Camera::Update()
{
	//ビュー行列を生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列を生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

/// <summary>
/// ビュー行列を取得
/// </summary>
/// <returns>ビュー行列</returns>
Matrix Camera::GetViewMatrix()
{
	return m_view;
}

/// <summary>
/// 射影行列を取得
/// </summary>
/// <returns>射影行列</returns>
Matrix Camera::GetProjMatrix()
{
	return m_proj;
}

/// <summary>
/// 視点座標をセット
/// </summary>
/// <param name="eyepos">視点座標行列</param>
void Camera::SetEyePos(Vector3 eyepos)
{
	m_eyepos = eyepos + Vector3(0.0f,2.0f,-4.0f);
}

/// <summary>
/// 注視点座標をセット
/// </summary>
/// <param name="refpos">注視点座標</param>
void Camera::SetRefPos(Vector3 refpos)
{
	m_refpos = refpos;
}

/// <summary>
/// 上方向ベクトルをセット
/// </summary>
/// <param name="upvec">上方向ベクトル</param>
void Camera::SetUpVec(Vector3 upvec)
{
	m_upvec = upvec;
}

/// <summary>
/// 垂直方向視野角をセット
/// </summary>
/// <param name="fovY">垂直方向視野角</param>
void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

/// <summary>
/// アスペクト比をセット
/// </summary>
/// <param name="aspect">アスペクト比</param>
void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

/// <summary>
/// 手前の表示限界距離をセット
/// </summary>
/// <param name="nearclip">手前の表示限界距離</param>
void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

/// <summary>
/// 奥の表示限界距離をセット
/// </summary>
/// <param name="farclip">奥の表示限界距離</param>
void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}