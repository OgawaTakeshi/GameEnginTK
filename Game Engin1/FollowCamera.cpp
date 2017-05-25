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
	//カメラの距離
	const float GAMERA_DISTANCE = 5.0f;
	//視点
	Vector3 eyepos, refpos;

	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboaredTracker.Update(keystate);

	if(m_keyboaredTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// フラグを切り替え
		isFPS = !isFPS;
		if (!isFPS)
		{
			InitializeTPS();
		}
	}
	if(isFPS)
	{//FPS
		Vector3 position;
		//ターゲット座標から自機座標への追従対象
		position = m_targetpos + Vector3(0, 0.6f, 0);
		//ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0.0f, 0.0f, -GAMERA_DISTANCE);
		//カメラの回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.4f;
		//参照点カメラ座標を計算
		refpos = eyepos + cameraV;
	}
	else
	{//TPS
		//ターゲット座標から自機座標への追従対象
		refpos = m_targetpos + Vector3(0, 2.0f, 0);
		//ターゲット座標からカメラ座標への差分
		Vector3 cameraV(0.0f, 0.0f, GAMERA_DISTANCE);
		//カメラの回転
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		//カメラ座標を計算
		eyepos = refpos + cameraV;

	//拠点から現在位置から補間する
	eyepos = m_eyepos + (eyepos - m_eyepos)*0.2f;
	//参照点を現在位置から補間する
	refpos = m_refpos + (refpos - m_refpos)*0.2f;
	}


	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
	Camera::Update();
}

void FollowCamera::InitializeTPS()
{
	Vector3 eyepos, refpos;

	// 自機の上方２ｍの位置を捉える
	refpos = m_targetpos + Vector3(0, 2, 0);
	// 参照点から視点への差分
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);
	// 自機の後ろに回り込むための回転
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	// 差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// 視点座標を計算
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
