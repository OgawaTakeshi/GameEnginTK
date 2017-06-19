#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;



	Initialize();


}

Player::~Player()
{
}


//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void Player::Initialize()
{

	// 自機パーツのロード
	m_ObjPlayer.resize(PLAYER_PARTS_NUM);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].LoadModel(L"Resources/houdai2.cmo");
	m_ObjPlayer[PLAYER_PARTS_BASE].LoadModel(L"Resources/asi.cmo");
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].LoadModel(L"Resources/taihou.cmo");

	// 親子関係の構築（子供に親をセット）
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);

	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);


	// 親からのオフセット（ローカルの座標ずれ）
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetScale(
		Vector3(2, 2, 2));
	m_ObjPlayer[PLAYER_PARTS_HOUDAI].SetTranslation(
		Vector3(-0.05f, 0.4f, -0.2f));

	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(
		Vector3(5, 5, 4));
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(
		Vector3(-0.05f, 0.8f, -0.5f));

	m_ObjPlayer[PLAYER_PARTS_BASE].SetTranslation(
		Vector3(0, 0, 0));


	//武器の当たり判定
	{
		m_CollisionNodeBullet.Initialize();
		//武器パーツに埋め込む
		m_CollisionNodeBullet.SetParent(&m_ObjPlayer[PLAYER_PARTS_TAIHOU]);
		//
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, -1.0f));
		//当たり判定の半径
		m_CollisionNodeBullet.SetLocalRadius(0.1);
	}
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void Player::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	
	if (keystate.A)
	{
		// 自機の角度を変動
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(
			Vector3(0, angle + 0.03f, 0));
	}

	// Dキーを押している間
	if (keystate.D)
	{
		// 自機の角度を変動
		float angle = m_ObjPlayer[0].GetRotation().y;
		m_ObjPlayer[0].SetRotation(
			Vector3(0, angle - 0.03f, 0));
	}

	// Wキーを押している間
	if (keystate.W)
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 今の角度に合わせて移動ベクトルを回転
		// 回転行列
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		pos += moveV;
		m_ObjPlayer[0].SetTranslation(pos);
	}

	// Sキーを押している間
	if (keystate.S)
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, +0.1f);
		// 回転行列
		float angle = m_ObjPlayer[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = m_ObjPlayer[0].GetTranslation();
		pos += moveV;
		m_ObjPlayer[0].SetTranslation(pos);
	}




	//スペースキーで発射
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (m_FireFlag)
		{
			ResetBullet();
		}
		else
		{
			// 発射
			FireBullet();
		}
	}
	if (m_FireFlag)
	{
		// 現在の座標を取得
		Vector3 trans = m_ObjPlayer[PLAYER_PARTS_TAIHOU].GetTranslation();

		trans += m_BulletVel;

		// 移動した座標を反映
		m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(trans);


	}
		// 行列更新
	Calc();
	m_CollisionNodeBullet.Initialize();
}

//-----------------------------------------------------------------------------
// 行列更新
//-----------------------------------------------------------------------------
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Update();
	}

	m_CollisionNodeBullet.Update();
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_ObjPlayer.begin();
		it != m_ObjPlayer.end();
		it++)
	{
		it->Draw();
	}
	m_CollisionNodeBullet.Draw();
}

void Player::FireBullet()
{

	// 既に発射中
	if (m_FireFlag)	return;

	m_FireFlag = true;
	// ワールド行列を取得
	Matrix worldm = m_ObjPlayer[PLAYER_PARTS_TAIHOU].GetWorld();

	Vector3 scale;	// ワールドスケーリング
	Quaternion rotation;	// ワールド回転
	Vector3 translation;	// ワールド座標

							// ワールド行列から各要素を取り出す
	worldm.Decompose(scale, rotation, translation);

	// 親子関係を解除してパーツを独立させる
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(nullptr);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(scale);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetRotationQ(rotation);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(translation);

	// 弾の速度を設定
	m_BulletVel = Vector3(0, 0, -0.1f);
	// 弾の向きに合わせて進行方向を回転
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

}

// 弾丸用のパーツをロボットに取り付けなおす
void Player::ResetBullet()
{
	// 発射中ではない
	if (!m_FireFlag)	return;

	
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetObjParent(
		&m_ObjPlayer[PLAYER_PARTS_BASE]);
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetScale(
		Vector3(5, 5, 4));
	m_ObjPlayer[PLAYER_PARTS_TAIHOU].SetTranslation(
		Vector3(-0.05f, 0.8f, -0.5f));

	m_FireFlag = false;
}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// タンクパーツの座標を返す
	return m_ObjPlayer[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	// タンクパーツの座標を返す
	return m_ObjPlayer[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_ObjPlayer[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_ObjPlayer[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_ObjPlayer[0].GetWorld();
}
