#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"


// ���@
class Player
{
public:
	// �p�[�c
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BASE,
		PLAYER_PARTS_TAIHOU,
		PLAYER_PARTS_HOUDAI,
		PLAYER_PARTS_TATE,

		PLAYER_PARTS_NUM
	};

	// �R���X�g���N�^
	Player(DirectX::Keyboard* keyboard);
	// �f�X�g���N�^
	~Player();
	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �s��̌v�Z
	void Calc();
	// �`��
	void Draw();
	// �e����
	void FireBullet();
	// �߂�
	void ResetBullet();

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
	// �����o�ϐ�
	// ���{�b�g�̍\���p�[�c
	std::vector<Obj3d>	m_ObjPlayer;
	// �L�[�{�[�h
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;
	// �e�̑��x
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_FireFlag;
};