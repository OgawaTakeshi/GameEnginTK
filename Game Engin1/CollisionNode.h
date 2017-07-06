#pragma once

#include"Collision.h"
#include"Obj3d.h"
/// <summary>
/// 当たり判定ノード
/// </summary>

/// <summary>
/// 当たり判定ノード
/// </summary>
class CollisionNode
{
public:
	static bool GetDebugVisible() { return m_GetDebugVisible; };
	static void SetDebugVisible(bool Visible) { m_GetDebugVisible = Visible; };
protected:
	//デバッグ表示ON
	static bool m_GetDebugVisible;
public:
	//初期化
	virtual void Initialize()=0;
	//毎フレーム更新
	virtual void Update() =0;
	//描画
	virtual void Draw() =0;
	//親のセット
	void SetParent(Obj3d* parent);

	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; };


protected:
	//デバック表示オブジェクト
	Obj3d m_obj;
	//親からオフセット
	DirectX::SimpleMath::Vector3 m_trans;



};

//当たり判定球ノード
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	//初期化
	void Initialize();
	//毎フレーム更新
	void Update();
	//描画
	void Draw();

	void SetLocalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//ローカル半径
	float m_LocalRadius;
};

