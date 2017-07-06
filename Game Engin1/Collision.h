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

// 法線付き三角形（反時計回りが表面）
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル
};

bool CheckSphere(const Sphere & _sphereA, const Sphere & _sphereB , DirectX::SimpleMath::Vector3* inter = nullptr);

void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, Triangle * _triangle);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);


