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
/// SphereNode�̃����o�֐�
/// </summary>

//�R���X�g���N�^
SphereNode::SphereNode()
{
	//�f�t�H���g���a
	m_LocalRadius = 0.1f;
}

void SphereNode::Initialize()
{
	//�f�o�b�N�\���p���f����ǂݍ���
	m_obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(Vector3 (m_LocalRadius));
	
	//�s����X�V
	m_obj.Update();
}

void SphereNode::Draw()
{
	//�f�o�b�N�p���f����`��
	m_obj.Draw();
}


