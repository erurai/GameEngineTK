//////////////////////////////////////////
//更新日:2017/05/22						//
//概要:3Dオブジェクトのソースファイル	//
//製作者:山岸正都						//
//////////////////////////////////////////
#include "Obj3d.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//静的メンバ関数の実体
Camera* Obj3d::m_pCamera;
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
Microsoft::WRL::ComPtr<ID3D11Device> Obj3d::m_d3dDevice;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Obj3d::m_d3dContext;
std::unique_ptr <DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Camera * pCamera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_pCamera = pCamera;
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;

	m_states = make_unique<CommonStates>(d3dDevice.Get());

	//エフェクトファクトリの生成
	m_factory = make_unique<EffectFactory>(m_d3dDevice.Get());
	//テクスチャの読み込みフォルダの指定
	m_factory->SetDirectory(L"Resources");
}

Obj3d::Obj3d()
{
	m_scale = Vector3(1.0f, 1.0f, 1.0f);

	m_pParent_obj = nullptr;
	m_use_quternion = false;
}

void Obj3d::Update()
{
	//頭パーツの行列の計算
	//スケーリング行列
	Matrix scalemat = Matrix::CreateScale(m_scale);
	//ローテーション行列
	Matrix rotmat;
	if (m_use_quternion)
	{//クォータニオン計算
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//オイラー計算
		//ロール
		Matrix rotmat_z = Matrix::CreateRotationZ(m_rotation.z);
		//ピッチ
		Matrix rotmat_x = Matrix::CreateRotationX(m_rotation.x);
		//ヨー
		Matrix rotmat_y = Matrix::CreateRotationY(m_rotation.y);
		//ローテーション行列の合成
		rotmat = rotmat_z * rotmat_x * rotmat_y;
	}
	//トランスレーション行列
	Matrix transmat = Matrix::CreateTranslation(m_transration);
	//各行列の合成
	m_world = scalemat * rotmat * transmat;
	
	//親がいる場合
	if (m_pParent_obj)
	{
		m_world *= m_pParent_obj->GetWorld();
	}
}

void Obj3d::Draw()
{
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(), 
			*m_states, 
			m_world, 
			m_pCamera->GetViewMatrix(),
			m_pCamera->GetProjMatrix());
	}
}

void Obj3d::LoadModel(const wchar_t * szFileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), szFileName, *m_factory);
}

