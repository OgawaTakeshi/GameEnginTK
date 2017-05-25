#pragma once
//
//3d�I�u�W�F�N�g�N���X
//

#include"Camera.h"

#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

class Obj3d
{	//�ÓI�����o
public:

	static void Initialize(Camera* pCamera,
		static std::unique_ptr<DirectX::CommonStates> states,
		static std::unique_ptr<DirectX::EffectFactory> factory,
		static Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext);


private:
	//�J����
	Camera* m_pCamera;
	//�ėp�X�e�[�g
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;
	//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	//�R���e�L�X�g
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
public:
	Obj3d();

	//���f���̓ǂݍ���
	void LoadModel(const wchar_t* szFileName);

	//set
	//�X�P�[�����O�p

	//��]�p�p

	//���s�ړ��p

	//get
	//�X�P�[�����O�p

	//��]�p�p

	//���s�ړ��p

	//���[���h�s��


private:
	//���f��(���j�[�N�|�C���^�j



	//�X�P�[�����O

	//���s�ړ�	

	//��]�ړ�

	//���[���h�s��


	//�e�ƂȂ�I�u�W�F�N�g�̃N���X�̃|�C���^
};

