#pragma once


#include<SimpleMath.h>
#include<d3d11_1.h>

class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;//���S���W	
	float Radius; //���a


	Sphere()
	{
		Radius = 1.0f;
	}

};

//����
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;	//�n�_���W
	DirectX::SimpleMath::Vector3 End;	//�I�_���W

};


//�J�v�Z��
class Capsule
{
public:
	Segment Segment;	//�c��
	float Radius;		//���a

	Capsule()
	{
		Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		Segment.End = DirectX::SimpleMath::Vector3(0, 1, 0);
		Radius = 1.0f;
	}


};

bool CheckSphere(const Sphere & _sphereA, const Sphere & _sphereB);
