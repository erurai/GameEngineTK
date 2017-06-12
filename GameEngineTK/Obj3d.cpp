//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:3D�I�u�W�F�N�g�̃\�[�X�t�@�C��	//
//�����:�R�ݐ��s						//
//////////////////////////////////////////
#include "Obj3d.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�ÓI�����o�֐��̎���
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

	//�G�t�F�N�g�t�@�N�g���̐���
	m_factory = make_unique<EffectFactory>(m_d3dDevice.Get());
	//�e�N�X�`���̓ǂݍ��݃t�H���_�̎w��
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
	//���p�[�c�̍s��̌v�Z
	//�X�P�[�����O�s��
	Matrix scalemat = Matrix::CreateScale(m_scale);
	//���[�e�[�V�����s��
	Matrix rotmat;
	if (m_use_quternion)
	{//�N�H�[�^�j�I���v�Z
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//�I�C���[�v�Z
		//���[��
		Matrix rotmat_z = Matrix::CreateRotationZ(m_rotation.z);
		//�s�b�`
		Matrix rotmat_x = Matrix::CreateRotationX(m_rotation.x);
		//���[
		Matrix rotmat_y = Matrix::CreateRotationY(m_rotation.y);
		//���[�e�[�V�����s��̍���
		rotmat = rotmat_z * rotmat_x * rotmat_y;
	}
	//�g�����X���[�V�����s��
	Matrix transmat = Matrix::CreateTranslation(m_transration);
	//�e�s��̍���
	m_world = scalemat * rotmat * transmat;
	
	//�e������ꍇ
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

