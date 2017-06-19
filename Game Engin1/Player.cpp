#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;



	Initialize();


}

Player::~Player()
{
}


//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Player::Initialize()
{

	// ���@�p�[�c�̃��[�h
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].LoadModel(L"Resources/houdai2.cmo");
	m_ObjPlayer[PLAYER_PARTS_BASE].LoadModel(L"Resources/asi.cmo");
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].LoadModel(L"Resources/taihou.cmo");

	// �e�q�֌W�̍\�z�i�q���ɐe���Z�b�g�j
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);

	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);


	// �e����̃I�t�Z�b�g�i���[�J���̍��W����j
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetScale(
		Vector3(2, 2, 2));
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetTranslation(
		Vector3(-0.05f, 0.4f, -0.2f));

	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(
		Vector3(5, 5, 4));
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(
		Vector3(-0.05f, 0.8f, -0.5f));

	m_ObjPlayer[PLAYER_PARTS_BASE].SetTranslation(
		Vector3(0, 0, 0));


	//����̓����蔻��
	{
		m_CollisionNodeBullet.Initialize();
		//����p�[�c�ɖ��ߍ���
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_TAIHOU]);
		//
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, -1.0f));
		//�����蔻��̔��a
		m_CollisionNodeBullet.SetLocalRadius(0.1);
	}
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Player::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	
	if (keystate.A)
	{
		// ���@�̊p�x��ϓ�
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(
			Vector3(0, angle + 0.03f, 0));
	}

	// D�L�[�������Ă����
	if (keystate.D)
	{
		// ���@�̊p�x��ϓ�
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(
			Vector3(0, angle - 0.03f, 0));
	}

	// W�L�[�������Ă����
	if (keystate.W)
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		pos += moveV;
		m_ObjPlayer[0].SetTranslation(pos);
	}

	// S�L�[�������Ă����
	if (keystate.S)
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, +0.1f);
		// ��]�s��
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		pos += moveV;
		m_ObjPlayer[0].SetTranslation(pos);
	}




	//�X�y�[�X�L�[�Ŕ���
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (m_FireFlag)
		{
			ResetBullet();
		}
		else
		{
			// ����
			FireBullet();
		}
	}
	if (m_FireFlag)
	{
		// ���݂̍��W���擾
		Vector3 trans = m_ObjPlayer[PLAYER_PARTS_TAIHOU].GetTranslation();

		trans += m_BulletVel;

		// �ړ��������W�𔽉f
		m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(trans);


	}
		// �s��X�V
	Calc();
	m_CollisionNodeBullet.Initialize();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Update();
	}

	m_CollisionNodeBullet.Update();
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Draw();
	}
	m_CollisionNodeBullet.Draw();
}

void Player::FireBullet()
{

	// ���ɔ��˒�
	if (m_FireFlag)	return;

	m_FireFlag = true;
	// ���[���h�s����擾
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_TAIHOU].GetWorld();

	Vector3 scale;	// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

							// ���[���h�s�񂩂�e�v�f�����o��
	worldm.Decompose(scale, rotation, translation);

	// �e�q�֌W���������ăp�[�c��Ɨ�������
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(translation);

	// �e�̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.1f);
	// �e�̌����ɍ��킹�Đi�s��������]
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

}

// �e�ۗp�̃p�[�c�����{�b�g�Ɏ��t���Ȃ���
void Player::ResetBullet()
{
	// ���˒��ł͂Ȃ�
	if (!m_FireFlag)	return;

	
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(
		Vector3(5, 5, 4));
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(
		Vector3(-0.05f, 0.8f, -0.5f));

	m_FireFlag = false;
}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjPlayer[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_ObjPlayer[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjPlayer[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_ObjPlayer[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_ObjPlayer[0].GetWorld();
}
