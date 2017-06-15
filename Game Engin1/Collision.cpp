
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���Ƌ��̓����锻��
/// </summary>
/// <param name="_sphereA">��A</param>
/// <param name="_sphereB">��B</param>
/// <returns>true:�������Ă���@�@false:�������Ă��Ȃ�</returns>
bool CheckSphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	//��A�Ƌ�B�̒��S���W���v�Z����
	Vector3 sub = _sphereA.Center - _sphereB.Center;

	//�O�����̒藝�ŁA�x�N�g���������v�Z����
	//�����x�N�g���̒����́A2�_�Ԃ̋���
	float distanceSQ = sub.x*sub.x + sub.y*sub.y + sub.z*sub.z;
	//���a�̘a
	float radiusSQ = _sphereA.Radius + _sphereB.Radius;
	radiusSQ = radiusSQ + radiusSQ;

	//���������a���傫����Γ������ĂȂ�
	if (distanceSQ > radiusSQ)
	{
		return false;
	}

	return true;

}
