#pragma once

#include"Collision.h"
#include"Obj3d.h"
/// <summary>
/// �����蔻��m�[�h
/// </summary>

/// <summary>
/// �����蔻��m�[�h
/// </summary>
class CollisionNode
{
public:
	static bool GetDebugVisible() { return m_GetDebugVisible; };
	static void SetDebugVisible(bool Visible) { m_GetDebugVisible = Visible; };
protected:
	//�f�o�b�O�\��ON
	static bool m_GetDebugVisible;
public:
	//������
	virtual void Initialize()=0;
	//���t���[���X�V
	virtual void Update() =0;
	//�`��
	virtual void Draw() =0;
	//�e�̃Z�b�g
	void SetParent(Obj3d* parent);

	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { m_trans = trans; };


protected:
	//�f�o�b�N�\���I�u�W�F�N�g
	Obj3d m_obj;
	//�e����I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_trans;



};

//�����蔻�苅�m�[�h
class SphereNode : public CollisionNode, public Sphere
{
public:
	SphereNode();
	//������
	void Initialize();
	//���t���[���X�V
	void Update();
	//�`��
	void Draw();

	void SetLocalRadius(float radius) { m_LocalRadius = radius; };
protected:
	//���[�J�����a
	float m_LocalRadius;
};

