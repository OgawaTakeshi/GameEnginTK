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

// �@���t���O�p�`�i�����v��肪�\�ʁj
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// �@���x�N�g��
};

bool CheckSphere(const Sphere & _sphereA, const Sphere & _sphereB , DirectX::SimpleMath::Vector3* inter = nullptr);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);


