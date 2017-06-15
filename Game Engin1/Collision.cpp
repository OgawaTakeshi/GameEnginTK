
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球と球の当たる判定
/// </summary>
/// <param name="_sphereA">球A</param>
/// <param name="_sphereB">球B</param>
/// <returns>true:当たっている　　false:当たっていない</returns>
bool CheckSphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	//球Aと球Bの中心座標を計算する
	Vector3 sub = _sphereA.Center - _sphereB.Center;

	//三平方の定理で、ベクトル長さを計算する
	//差分ベクトルの長さは、2点間の距離
	float distanceSQ = sub.x*sub.x + sub.y*sub.y + sub.z*sub.z;
	//半径の和
	float radiusSQ = _sphereA.Radius + _sphereB.Radius;
	radiusSQ = radiusSQ + radiusSQ;

	//距離が半径より大きければ当たってない
	if (distanceSQ > radiusSQ)
	{
		return false;
	}

	return true;

}
