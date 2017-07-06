#include"Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;


	Initialize();
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{

	// 自機パーツのロード
	m_ObjEnemy.resize(PLAYER_PARTS_NUM);
	m_ObjEnemy[PLAYER_PARTS_TAIHOU].LoadModel(L"Resources/houdai2.cmo");
	m_ObjEnemy[PLAYER_PARTS_BASE].LoadModel(L"Resources/asi.cmo");
	m_ObjEnemy[PLAYER_PARTS_HOUDAI].LoadModel(L"Resources/taihou.cmo");

	// 親子関係の構築（子供に親をセット）
	m_ObjEnemy[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjEnemy[PLAYER_PARTS_BASE]);

	m_ObjEnemy[PLAYER_PARTS_HOUDAI].SetObjParent(
		&m_ObjEnemy[PLAYER_PARTS_BASE]);


	// 親からのオフセット（ローカルの座標ずれ）
	m_ObjEnemy[PLAYER_PARTS_HOUDAI].SetScale(
		Vector3(2, 2, 2));
	m_ObjEnemy[PLAYER_PARTS_HOUDAI].SetTranslation(
		Vector3(-0.05f, 0.4f, -0.2f));

	m_ObjEnemy[PLAYER_PARTS_TAIHOU].SetScale(
		Vector3(5, 5, 4));
	m_ObjEnemy[PLAYER_PARTS_TAIHOU].SetTranslation(
		Vector3(-0.05f, 0.8f, -0.5f));

	m_ObjEnemy[PLAYER_PARTS_BASE].SetTranslation(
		Vector3(0, 0, 0));

	Vector3 pos;

	pos.x = rand() % 10;
	pos.z = rand() % 10;

	SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

	//武器の当たり判定
	{
		m_CollisionNodeBody.Initialize();
		//武器パーツに埋め込む
		m_CollisionNodeBody.SetParent(&m_ObjEnemy[0]);
		//
		m_CollisionNodeBody.SetTrans(Vector3(0, 0, -0));
		//当たり判定の半径
		m_CollisionNodeBody.SetLocalRadius(1.0f);
	}
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	m_Timer--;
	if (m_Timer < 0)
	{
		// 目標角度の再抽選
		m_Timer = 60;
		// -0.5～+0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90～+90の乱数
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// 自機の角度を変動
		Vector3 rot = GetRot();

		float angle = m_DistAngle - rot.y;

		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		rot.y += angle *0.05f;

		SetRot(rot);
	}

	// 機体の向いている方向に前進
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 今の角度に合わせて移動ベクトルを回転
		// 回転行列
		float angle = m_ObjEnemy[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = m_ObjEnemy[0].GetTranslation();
		pos += moveV;
		m_ObjEnemy[0].SetTranslation(pos);
	}

	// 行列更新
	Calc();

}

void Enemy::Calc()
{	
	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Update();
	}
	m_CollisionNodeBody.Update();
}

void Enemy::Render()
{

	for (std::vector<Obj3d>::iterator it = m_ObjEnemy.begin();
		it != m_ObjEnemy.end();
		it++)
	{
		it->Draw();
	}
	m_CollisionNodeBody.Draw();
}

const DirectX::SimpleMath::Vector3& Enemy::GetTrans()
{
	// タンクパーツの座標を返す
	return m_ObjEnemy[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Enemy::GetRot()
{
	// タンクパーツの座標を返す
	return m_ObjEnemy[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_ObjEnemy[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_ObjEnemy[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_ObjEnemy[0].GetWorld();
}

