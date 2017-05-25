#include "FollowCamera.h"

using namespace DirectX;
using namespace SimpleMath;

//
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int m_outputWidth, int  m_outputHeight)
	:Camera(m_outputWidth,m_outputHeight)
{
	m_targetpos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	isFPS = false;
	InitializeTPS();
}



void FollowCamera::Update()
{
	//�J�����̋���
	const float GAMERA_DISTANCE = 5.0f;
	//���_
	Vector3 eyepos, refpos;

	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboaredTracker.Update(keystate);

	if(m_keyboaredTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// �t���O��؂�ւ�
		isFPS = !isFPS;
		if (!isFPS)
		{
			InitializeTPS();
		}
	}
	if(isFPS)
	{//FPS
		Vector3 position;
		//�^�[�Q�b�g���W���玩�@���W�ւ̒Ǐ]�Ώ�
		position = m_targetpos + Vector3(0, 0.6f, 0);
		//�^�[�Q�b�g���W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, -GAMERA_DISTANCE);
		//�J�����̉�]
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.4f;
		//�Q�Ɠ_�J�������W���v�Z
		refpos = eyepos + cameraV;
	}
	else
	{//TPS
		//�^�[�Q�b�g���W���玩�@���W�ւ̒Ǐ]�Ώ�
		refpos = m_targetpos + Vector3(0, 2.0f, 0);
		//�^�[�Q�b�g���W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, GAMERA_DISTANCE);
		//�J�����̉�]
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//�J�������W���v�Z
		eyepos = refpos + cameraV;

	//���_���猻�݈ʒu�����Ԃ���
	eyepos = m_eyepos + (eyepos - m_eyepos)*0.2f;
	//�Q�Ɠ_�����݈ʒu�����Ԃ���
	refpos = m_refpos + (refpos - m_refpos)*0.2f;
	}


	SetEyePos(eyepos);
	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	// ���@�̏���Q���̈ʒu�𑨂���
	refpos = m_targetpos + Vector3(0, 2, 0);
	// �Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);
	// ���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	// �����x�N�g������]������
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// ���_���W���v�Z
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_targetAngle = targetangle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetpos = targetpos;
}
