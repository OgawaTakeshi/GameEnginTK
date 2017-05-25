#include"Obj3d.h"

void Obj3d::Initialize(Camera * pCamera, std::unique_ptr<DirectX::CommonStates> states, std::unique_ptr<DirectX::EffectFactory> factory, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_pCamera = pCamera;
	m_d3dDevice = d3dDevice;

}

Obj3d::Obj3d()
{
	//•Ï”‚Ì‰Šú‰»
}

void Obj3d::LoadModel(const wchar_t * szFileName)
{
}
