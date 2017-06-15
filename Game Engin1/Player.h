#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3d.h"


// 自機
class Player
{
public:
	// パーツ
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_BASE,
		PLAYER_PARTS_TAIHOU,
		PLAYER_PARTS_HOUDAI,
		PLAYER_PARTS_TATE,

		PLAYER_PARTS_NUM
	};

	// コンストラクタ
	Player(DirectX::Keyboard* keyboard);
	// デストラクタ
	~Player();
	// 初期化
	void Initialize();
	// 毎フレーム更新
	void Update();
	// 行列の計算
	void Calc();
	// 描画
	void Draw();
	// 弾発射
	void FireBullet();
	// 戻す
	void ResetBullet();

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// 座標を設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// 回転を設定
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

protected:
	// メンバ変数
	// ロボットの構成パーツ
	std::vector<Obj3d>	m_ObjPlayer;
	// キーボード
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;
	// 弾の速度
	DirectX::SimpleMath::Vector3 m_BulletVel;

	bool m_FireFlag;
};