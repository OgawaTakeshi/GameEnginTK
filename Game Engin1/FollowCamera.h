#pragma once
//
//�J������Ǐ]����J�����N���X
//

#include "Camera.h"
#include<Keyboard.h>


class FollowCamera:public Camera
{
public:
	// �J�����Ǝ��@�̋���
	static const float CAMERA_DISTANCE;
	// �R���X�g���N�^
	FollowCamera(int width, int height);
	// ���t���[���X�V
	void Update() override;

	// �Ǐ]�Ώۍ��W���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	// �Ǐ]�Ώۊp�x���Z�b�g
	void SetTargetAngle(float targetAngle);

	void SetKeyboard(DirectX::Keyboard* m_keyboard);

	// TPS�J�����̏�����
	void InitializeTPS();

private:

	DirectX::SimpleMath::Vector3 m_targetpos;
	float m_targetAngle;
	//�L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboaredTracker;
	//FPS ture 
	bool isFPS;
};

