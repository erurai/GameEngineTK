//////////////////////////////////////////
//更新日:2017/05/22						//
//概要:3Dオブジェクトのヘッダファイル	//
//製作者:山岸正都						//
//////////////////////////////////////////
#pragma once

#include <Windows.h>
#include <wrl/client.h>
#include <memory>
#include <Effects.h>
#include <CommonStates.h>

#include <Model.h>
#include "Camera.h"
//#include <SimpleMath.h>

class Obj3d
{
//静的メンバ
public:
	//静的メンバの初期化
	static void InitializeStatic(Camera* pCamera,
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);

private:
	static Camera* m_pCamera;											//カメラ
	static std::unique_ptr<DirectX::CommonStates> m_states;				//汎用ステート
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;			//デバイス
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;	//コンテキスト
	static std::unique_ptr < DirectX::EffectFactory> m_factory;			//エフェクトファクトリ

public:
	Obj3d();															//コンストラクタ
	//~Obj3d();															//デストラクタ

	void Update();														//アップデート関数
	void Draw();														//描画関数

	void LoadModel(const wchar_t* szFileName);							//モデルの読み込み

	//setter
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{ m_scale = scale; }												//スケーリング用
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation)
	{ m_rotation = rotation; m_use_quternion = false; }					//オイラー角回転角用
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& quaternion)
	{ m_rotationQ = quaternion; m_use_quternion = true; }				//クォータニオン回転角用
	void SetTransration(const DirectX::SimpleMath::Vector3& transration)
	{ m_transration = transration; }									//平行移動用
	void SetWorld(const DirectX::SimpleMath::Matrix& world)
	{ m_world = world; }												//ワールド行列用
	void SetParentObj(Obj3d* pParent_obj)
	{ m_pParent_obj = pParent_obj; }									//親行列用

	//getter
	const DirectX::SimpleMath::Vector3& GetScale()
	{ return m_scale; }													//スケーリング用
	const DirectX::SimpleMath::Vector3& GetRotation()
	{ return m_rotation; }												//回転角用
	const DirectX::SimpleMath::Vector3& GetTransration()
	{ return m_transration; }											//平行移動用
	const DirectX::SimpleMath::Matrix& GetWorld()
	{ return m_world; }													//ワールド行列を取得する
	Obj3d* SetParentObj()
	{ return m_pParent_obj; }											//親行列用

private:
	std::unique_ptr<DirectX::Model> m_model;							//モデルのユニークポインタ
	DirectX::SimpleMath::Vector3 m_scale;								//スケーリング行列
	DirectX::SimpleMath::Vector3 m_rotation;							//回転角行列(オイラー角)
	DirectX::SimpleMath::Vector3 m_transration;							//平行移動行列
	DirectX::SimpleMath::Matrix m_world;								//ワールド行列
	bool m_use_quternion;												//クォータニオンを使うかどうか
	DirectX::SimpleMath::Quaternion m_rotationQ;						//回転角(クォータニオン)
	Obj3d* m_pParent_obj;												//親となる3Dオブジェクトのポインタ

};
