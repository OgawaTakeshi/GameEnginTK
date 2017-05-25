//------------------------------
//�J�����𐧌䂷��CPP
//------------------------------

#include"Camera.h"

using namespace DirectX;
using namespace SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="value">�����̐��l</param>
/// <returns>�v�Z����</returns>
Camera::Camera(int m_outputWidth,int  m_outputHeight)
{
	//�����o�ϐ��̏�����
	 m_eyepos=Vector3(0, 0, 5.0f);	//���_
	 m_refpos = Vector3(0, 0, 0);		//�Q�Ɠ_
	 m_upvec = Vector3(0, 1, 0);		//������x�N�g��
	// m_upvec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)m_outputHeight / m_outputWidth;	//�c��
	m_nearClip = 0.1f;	//�O
	m_farClip = 1000.0f; //��ʉ�

	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

Camera::~Camera()
{

}

void Camera::Update()
{

	//�r���[�s��̐���
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//�ˉe�s��̐���
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

const DirectX::SimpleMath::Matrix Camera::GetView()
{
	
	return m_view;
}

const DirectX::SimpleMath::Matrix Camera::Getproj()
{
	return m_proj;
}

void Camera::SetEyePos(const DirectX::SimpleMath::Vector3& eyepos)
{
	m_eyepos = eyepos;
}

void Camera::SetRefPos(const DirectX::SimpleMath::Vector3& refpos)
{
	m_refpos = refpos;
}

void Camera::SetUpvec(const DirectX::SimpleMath::Vector3& upvec)
{
	m_upvec = upvec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearClip(float nearClip)
{
	m_nearClip = nearClip;
}

void Camera::SetFarClip(float farClip)
{
	m_farClip = farClip;
}
