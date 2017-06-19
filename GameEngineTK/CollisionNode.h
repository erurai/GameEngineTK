#pragma once
#include "Collision.h"
#include "Obj3d.h"

/// <summary>
/// �����蔻��m�[�h
/// </summary>
class CollisionNode
{
public:
	virtual void Initialize() = 0;			//������
	virtual void Update() = 0;				//���t���[���X�V
	virtual void Draw() = 0;				//�`��
	void SetObjParent(Obj3d* parent);		//�e���Z�b�g
	//�e����̃I�t�Z�b�g���Z�b�g
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; }
protected:
	Obj3d m_obj;							//�f�o�b�O�\���I�u�W�F�N�g
	DirectX::SimpleMath::Vector3 m_trans;	//�e����̃I�t�Z�b�g
};

//�����蔻�苅�m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();		//�R���X�g���N�^
	void Initialize();	//������
	void Update();		//���t���[���X�V
	void Draw();		//�`��

	void SetLocalRadius(float radius) { m_localradius = radius; }

protected:
	float m_localradius;//���[�J�����a
};