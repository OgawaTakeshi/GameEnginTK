//------------------------------
//カメラを制御するCPP
//------------------------------

#include"Camera.h"

using namespace DirectX;
using namespace SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="value">何かの数値</param>
/// <returns>計算結果</returns>
Camera::Camera(int m_outputWidth,int  m_outputHeight)
{
	//メンバ変数の初期化
	 m_eyepos=Vector3(0, 0, 5.0f);	//視点
	 m_refpos = Vector3(0, 0, 0);		//参照点
	 m_upvec = Vector3(0, 1, 0);		//上方向ベクトル
	// m_upvec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)m_outputHeight / m_outputWidth;	//縦横
	m_nearClip = 0.1f;	//前
	m_farClip = 1000.0f; //画面奥

	//ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列の生成
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

Camera::~Camera()
{

}

void Camera::Update()
{

	//ビュー行列の生成
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);
	//射影行列の生成
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
