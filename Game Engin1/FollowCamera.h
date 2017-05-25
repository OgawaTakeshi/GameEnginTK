#pragma once
//
//カメラを追従するカメラクラス
//

#include "Camera.h"
#include<Keyboard.h>


class FollowCamera:public Camera
{
public:
	// カメラと自機の距離
	static const float CAMERA_DISTANCE;
	// コンストラクタ
	FollowCamera(int width, int height);
	// 毎フレーム更新
	void Update() override;

	// 追従対象座標をセット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	// 追従対象角度をセット
	void SetTargetAngle(float targetAngle);

	void SetKeyboard(DirectX::Keyboard* m_keyboard);

	// TPSカメラの初期化
	void InitializeTPS();

private:

	DirectX::SimpleMath::Vector3 m_targetpos;
	float m_targetAngle;
	//キーボード
	DirectX::Keyboard* m_keyboard;
	//キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboaredTracker;
	//FPS ture 
	bool isFPS;
};

