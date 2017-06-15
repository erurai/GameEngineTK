#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="sphereA">��A</param>
/// <param name="sphereB">��B</param>
/// <returns>true:�������Ă��� false:�������Ă��Ȃ�</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//���S���W�Ԃ̍����v�Z
	Vector3 sub = sphereB.Center - sphereA.Center;
	//���S���W�Ԃ̋������v�Z
	float distance_square = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	//���a�̘a
	float radius_square = sphereA.Radius + sphereB.Radius;
	radius_square = radius_square * radius_square;

	//���������a�̘a���傫����΁A�������Ă��Ȃ�
	if (distance_square > radius_square)
	{
		return false;
	}
	
	return true;
}