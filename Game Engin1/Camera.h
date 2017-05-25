//------------------------------
//カメラを制御する.h
//------------------------------

#pragma once

#include <d3d11.h>
#include <simplemath.h>
class Camera
{
public:
			//メンバ関数を置くところ

	Camera(int wirth,int m_outputHeight);
	virtual~Camera();

	//更新
	virtual void Update();

	//ビュー行列を取得
	const DirectX::SimpleMath::Matrix GetView();

	//射影行列を取得
	const DirectX::SimpleMath::Matrix Getproj();

	//視点座標をゲット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);
	void SetUpvec(const DirectX::SimpleMath::Vector3& upvec);

	void SetFovY(float fovY);
	void SetAspect(float aspect);
	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);
protected:
	//メンバ変数を置くところ	
	//ビュー行列

	DirectX::SimpleMath::Vector3 m_eyepos;	//視点
	DirectX::SimpleMath::Vector3 m_refpos;		//参照点（どこを見るのか）
	DirectX::SimpleMath::Vector3 m_upvec;		//上方向ベクトル

	DirectX::SimpleMath::Matrix m_view;	//視点
	

	//射影行列
	float m_fovY;		//垂直方向
	float m_aspect;
	float m_nearClip;	//前
	float m_farClip; //画面奥
DirectX::SimpleMath::Matrix m_proj;		//参照点

};