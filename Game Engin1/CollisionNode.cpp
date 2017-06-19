#include "pch.h"
#include "CollisionNode.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// 
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_obj.SetObjParent(parent);
}

/// <summary>
/// SphereNodeのメンバ関数
/// </summary>

//コンストラクタ
SphereNode::SphereNode()
{
	//デフォルト半径
	m_LocalRadius = 0.1f;
}

void SphereNode::Initialize()
{
	//デバック表示用モデルを読み込む
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(Vector3 (m_LocalRadius));
	
	//行列を更新
	m_obj.Update();
}

void SphereNode::Draw()
{
	//デバック用モデルを描画
	m_obj.Draw();
}


