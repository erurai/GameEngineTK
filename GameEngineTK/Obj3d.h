//////////////////////////////////////////
//�X�V��:2017/05/22						//
//�T�v:3D�I�u�W�F�N�g�̃w�b�_�t�@�C��	//
//�����:�R�ݐ��s						//
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
//�ÓI�����o
public:
	//�ÓI�����o�̏�����
	static void InitializeStatic(Camera* pCamera,
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);

private:
	static Camera* m_pCamera;											//�J����
	static std::unique_ptr<DirectX::CommonStates> m_states;				//�ėp�X�e�[�g
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;			//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;	//�R���e�L�X�g
	static std::unique_ptr < DirectX::EffectFactory> m_factory;			//�G�t�F�N�g�t�@�N�g��

public:
	Obj3d();															//�R���X�g���N�^
	//~Obj3d();															//�f�X�g���N�^

	void Update();														//�A�b�v�f�[�g�֐�
	void Draw();														//�`��֐�

	void LoadModel(const wchar_t* szFileName);							//���f���̓ǂݍ���

	//setter
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{ m_scale = scale; }												//�X�P�[�����O�p
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation)
	{ m_rotation = rotation; m_use_quternion = false; }					//�I�C���[�p��]�p�p
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& quaternion)
	{ m_rotationQ = quaternion; m_use_quternion = true; }				//�N�H�[�^�j�I����]�p�p
	void SetTransration(const DirectX::SimpleMath::Vector3& transration)
	{ m_transration = transration; }									//���s�ړ��p
	void SetWorld(const DirectX::SimpleMath::Matrix& world)
	{ m_world = world; }												//���[���h�s��p
	void SetParentObj(Obj3d* pParent_obj)
	{ m_pParent_obj = pParent_obj; }									//�e�s��p

	//getter
	const DirectX::SimpleMath::Vector3& GetScale()
	{ return m_scale; }													//�X�P�[�����O�p
	const DirectX::SimpleMath::Vector3& GetRotation()
	{ return m_rotation; }												//��]�p�p
	const DirectX::SimpleMath::Vector3& GetTransration()
	{ return m_transration; }											//���s�ړ��p
	const DirectX::SimpleMath::Matrix& GetWorld()
	{ return m_world; }													//���[���h�s����擾����
	Obj3d* SetParentObj()
	{ return m_pParent_obj; }											//�e�s��p

private:
	std::unique_ptr<DirectX::Model> m_model;							//���f���̃��j�[�N�|�C���^
	DirectX::SimpleMath::Vector3 m_scale;								//�X�P�[�����O�s��
	DirectX::SimpleMath::Vector3 m_rotation;							//��]�p�s��(�I�C���[�p)
	DirectX::SimpleMath::Vector3 m_transration;							//���s�ړ��s��
	DirectX::SimpleMath::Matrix m_world;								//���[���h�s��
	bool m_use_quternion;												//�N�H�[�^�j�I�����g�����ǂ���
	DirectX::SimpleMath::Quaternion m_rotationQ;						//��]�p(�N�H�[�^�j�I��)
	Obj3d* m_pParent_obj;												//�e�ƂȂ�3D�I�u�W�F�N�g�̃|�C���^

};
