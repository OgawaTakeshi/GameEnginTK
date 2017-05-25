//------------------------------
//�J�����𐧌䂷��.h
//------------------------------

#pragma once

#include <d3d11.h>
#include <simplemath.h>
class Camera
{
public:
			//�����o�֐���u���Ƃ���

	Camera(int wirth,int m_outputHeight);
	virtual~Camera();

	//�X�V
	virtual void Update();

	//�r���[�s����擾
	const DirectX::SimpleMath::Matrix GetView();

	//�ˉe�s����擾
	const DirectX::SimpleMath::Matrix Getproj();

	//���_���W���Q�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	void SetUpvec(const DirectX::SimpleMath::Vector3& upvec);

	void SetFovY(float fovY);
	void SetAspect(float aspect);
	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);
protected:
	//�����o�ϐ���u���Ƃ���	
	//�r���[�s��

	DirectX::SimpleMath::Vector3 m_eyepos;	//���_
	DirectX::SimpleMath::Vector3 m_refpos;		//�Q�Ɠ_�i�ǂ�������̂��j
	DirectX::SimpleMath::Vector3 m_upvec;		//������x�N�g��

	DirectX::SimpleMath::Matrix m_view;	//���_
	

	//�ˉe�s��
	float m_fovY;		//��������
	float m_aspect;
	float m_nearClip;	//�O
	float m_farClip; //��ʉ�
DirectX::SimpleMath::Matrix m_proj;		//�Q�Ɠ_

};