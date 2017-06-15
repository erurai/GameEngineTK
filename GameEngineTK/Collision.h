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

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
