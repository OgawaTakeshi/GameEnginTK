#include "pch.h"
#include "CollisionNode.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

bool CollisionNode::m_GetDebugVisible;

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

	{//���苅�̗v�f���v�Z
		const Matrix& worldm = m_obj.GetWorld();

		//���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		Vector3 right(1, 0, 0);
		//���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);
		//���苅�̗v�f����
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);

	}
}

void SphereNode::Draw()
{
	//�f�o�b�N�p���f����`��
	m_obj.Draw();
}


