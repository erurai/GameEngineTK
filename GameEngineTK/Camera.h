//////////////////////////////////////
//更新日:2017/05/11					//
//概要:カメラクラスのヘッダファイル	//
//製作者:山岸正都					//
//////////////////////////////////////
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	Camera(int width, int height);
	virtual ~Camera();
	virtual void Update();		//更新
	const DirectX::SimpleMath::Matrix GetViewMatrix();			//ビュー行列を取得
	const DirectX::SimpleMath::Matrix GetProjMatrix();			//射影行列を取得

	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);	//視点座標をセット
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);	//注視点をセット
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);		//上方向ベクトルをセット

	void SetFovY(const float& fovY);								//垂直方向視野角をセット
	void SetAspect(const float& aspect);							//アスペクト比をセット
	void SetNearClip(const float& nearclip);						//手前の表示限界距離をセット
	void SetFarClip(const float& farclip);							//奥の表示限界距離をセット

protected:
	DirectX::SimpleMath::Matrix m_view;						//ビュー行列
	DirectX::SimpleMath::Vector3 m_eyepos;					//カメラの位置(視点座標)
	DirectX::SimpleMath::Vector3 m_refpos;					//どこを見るのか(注視点/参照点)
	DirectX::SimpleMath::Vector3 m_upvec;					//上方向ベクトル

	DirectX::SimpleMath::Matrix m_proj;						//射影行列
	float m_fovY;											//垂直方向視野角
	float m_aspect;											//画面横幅と縦幅の比率(アスペクト比)
	float m_nearclip;										//手前の表示限界距離
	float m_farclip;										//奥の表示限界距離
	
};
