#pragma once


#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"

class Enemy{

public:

	enum ENEMY_PARTS
	{
		PLAYER_PARTS_BASE,
		PLAYER_PARTS_TAIHOU,
		PLAYER_PARTS_HOUDAI,
		PLAYER_PARTS_TATE,

		PLAYER_PARTS_NUM
	};

public:
	
	Enemy(DirectX::Keyboard* keyboard);
	~Enemy();


	// 初期化
	void Initialize();
	// 毎フレーム更新
	void Update();
	// 行列の計算
	void Calc();
	// 描画
	void Render();
	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();


protected:

	// タイマー
	int m_Timer;
	// 目標角度
	float m_DistAngle;

	// キーボード
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	std::vector<Obj3d> m_ObjEnemy;

	//当たり判定
	SphereNode m_CollisionNodeBullet;
};