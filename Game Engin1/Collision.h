#pragma once


#include<SimpleMath.h>
#include<d3d11_1.h>

class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;//中心座標	
	float Radius; //半径


	Sphere()
	{
		Radius = 1.0f;
	}

};

//線分
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;	//始点座標
	DirectX::SimpleMath::Vector3 End;	//終点座標

};


//カプセル
class Capsule
{
public:
	Segment Segment;	//芯線
	float Radius;		//半径

	Capsule()
	{
		Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		Segment.End = DirectX::SimpleMath::Vector3(0, 1, 0);
		Radius = 1.0f;
	}


};

bool CheckSphere(const Sphere & _sphereA, const Sphere & _sphereB);
