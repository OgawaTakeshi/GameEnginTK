#pragma once
//
//3dオブジェクトクラス
//

#include"Camera.h"

#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

class Obj3d
{	//静的メンバ
public:

	static void Initialize(Camera* pCamera,
		static std::unique_ptr<DirectX::CommonStates> states,
		static std::unique_ptr<DirectX::EffectFactory> factory,
		static Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext);


private:
	//カメラ
	Camera* m_pCamera;
	//汎用ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//ファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	//デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//コンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
public:
	Obj3d();

	//モデルの読み込み
	void LoadModel(const wchar_t* szFileName);

	//set
	//スケーリング用

	//回転角用

	//平行移動用

	//get
	//スケーリング用

	//回転角用

	//平行移動用

	//ワールド行列


private:
	//モデル(ユニークポインタ）



	//スケーリング

	//平行移動	

	//回転移動

	//ワールド行列


	//親となるオブジェクトのクラスのポインタ
};

