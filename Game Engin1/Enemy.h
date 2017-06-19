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


	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �s��̌v�Z
	void Calc();
	// �`��
	void Render();
	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();


protected:

	// �^�C�}�[
	int m_Timer;
	// �ڕW�p�x
	float m_DistAngle;

	// �L�[�{�[�h
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	std::vector<Obj3d> m_ObjEnemy;

	//�����蔻��
	SphereNode m_CollisionNodeBullet;
};