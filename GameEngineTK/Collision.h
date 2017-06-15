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

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
