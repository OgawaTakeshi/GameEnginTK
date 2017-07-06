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

	// ���@�p�[�c�̃��[�h
	m_ObjEnemy.resize(PLAYER_PARTS_NUM);
	m_ObjEnemy[PLAYER_PARTS_TAIHOU].LoadModel(L"Resources/houdai2.cmo");
	m_ObjEnemy[PLAYER_PARTS_BASE].LoadModel(L"Resources/asi.cmo");
	m_ObjEnemy[PLAYER_PARTS_HOUDAI].LoadModel(L"Resources/taihou.cmo");

	// �e�q�֌W�̍\�z�i�q���ɐe���Z�b�g�j
	m_ObjEnemy[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjEnemy[PLAYER_PARTS_BASE]);

	m_ObjEnemy[PLAYER_PARTS_HOUDAI].SetObjParent(
		&m_ObjEnemy[PLAYER_PARTS_BASE]);


	// �e����̃I�t�Z�b�g�i���[�J���̍��W����j
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

	//����̓����蔻��
	{
		m_CollisionNodeBody.Initialize();
		//����p�[�c�ɖ��ߍ���
		m_CollisionNodeBody.SetParent(&m_ObjEnemy[0]);
		//
		m_CollisionNodeBody.SetTrans(Vector3(0, 0, -0));
		//�����蔻��̔��a
		m_CollisionNodeBody.SetLocalRadius(1.0f);
	}
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	m_Timer--;
	if (m_Timer < 0)
	{
		// �ڕW�p�x�̍Ē��I
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90�`+90�̗���
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x��ϓ�
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

	// �@�̂̌����Ă�������ɑO�i
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = m_ObjEnemy[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_ObjEnemy[0].GetTranslation();
		pos += moveV;
		m_ObjEnemy[0].SetTranslation(pos);
	}

	// �s��X�V
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
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjEnemy[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Enemy::GetRot()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjEnemy[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjEnemy[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjEnemy[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_ObjEnemy[0].GetWorld();
}

