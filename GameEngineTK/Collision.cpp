#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
/// </summary>
/// <param name="sphereA">‹…A</param>
/// <param name="sphereB">‹…B</param>
/// <returns>true:“–‚½‚Á‚Ä‚¢‚é false:“–‚½‚Á‚Ä‚¢‚È‚¢</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//’†SÀ•WŠÔ‚Ì·‚ðŒvŽZ
	Vector3 sub = sphereB.Center - sphereA.Center;
	//’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	float distance_square = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;
	//”¼Œa‚Ì˜a
	float radius_square = sphereA.Radius + sphereB.Radius;
	radius_square = radius_square * radius_square;

	//‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distance_square > radius_square)
	{
		return false;
	}
	
	return true;
}