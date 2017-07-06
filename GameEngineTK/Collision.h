/// <summary>
/// �Փ˔��胉�C�u����
/// </summary>
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//���S���W
	float Radius;							//���a

	Sphere() { Radius = 1.0f; }				//�R���X�g���N�^

};

//����
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;		//���_���W
	DirectX::SimpleMath::Vector3 End;		//�I�_���W
};

//�@���t���O�p�`(�����v��肪�\��)
class Triangle
{
public:
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	DirectX::SimpleMath::Vector3 Normal;	//�@���x�N�g��
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

