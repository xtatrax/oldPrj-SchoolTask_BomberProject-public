////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FObject.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		class Object ;
//		class Light  ;
//		class DirectionalLight : public Light , public Object ;
//
#include "StdAfx.h"
#include "Object.h"

namespace wiz{
/**************************************************************************
 Light ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �FLight()
//// �J�e�S��   �F���񂷂Ƃ炭��
//// �p�r       �F�v���e�N�g�R���X�g���N�^
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ� 
//// �S����     �F
//// ���l       �F���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
////            �F
////
Light::Light(){
    // D3DLIGHT9�\���̂�0�ŃN���A����
    ::ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}
/////////////////// ////////////////////
//// �p�r       �FLight()
//// �J�e�S��   �F�ł��Ƃ炭��
//// �p�r       �F�v���e�N�g�f�X�g���N�^�i���z�f�X�g���N�^�j
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ� 
//// �S����     �F
//// ���l       �F���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
////            �F
Light::~Light(){}
/**************************************************************************
 DirectionalLight ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �FDirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
////            �F    D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,
////            �F    D3DCOLORVALUE Ambient,D3DXVECTOR3 Direction)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F  LPDIRECT3DDEVICE9 pD3DDevice,   //�f�o�C�X
////            �F  D3DCOLORVALUE Diffuse,          //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE Specular,         //�X�y�L�����F
////            �F  D3DCOLORVALUE Ambient,          //�A���r�G���g�F
////            �F  D3DXVECTOR3 Direction           //���[���h��ԂŌ����w������
//// �S����     �F
//// ���l       �F�f�B���N�V���i�����C�g���\�z����
////            �F
////
DirectionalLight::DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
    D3DCOLORVALUE Diffuse,
    D3DCOLORVALUE Specular,
    D3DCOLORVALUE Ambient,
    D3DXVECTOR3 Direction,
	wiz::OBJID id)
    :Light()
	,Object(id)
{
    m_Light.Type       = D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse = Diffuse;
    m_Light.Specular = Specular;
    m_Light.Ambient = Ambient;
    D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &Direction);
    // ���C�g�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetLight( 0, &m_Light );
    // ���C�g��L���ɂ���
    pD3DDevice->LightEnable( 0, TRUE );
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual ~DirectionalLight()
//// �J�e�S��   �F�Z�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
DirectionalLight::~DirectionalLight(){}


}
//end of namespace wiz.

