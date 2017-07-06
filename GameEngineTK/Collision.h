/// <summary>
/// 衝突判定ライブラリ
/// </summary>
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//中心座標
	float Radius;							//半径

	Sphere() { Radius = 1.0f; }				//コンストラクタ

};

//線分
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;		//視点座標
	DirectX::SimpleMath::Vector3 End;		//終点座標
};

//法線付き三角形(反時計回りが表面)
class Triangle
{
public:
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	DirectX::SimpleMath::Vector3 Normal;	//法線ベクトル
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);

