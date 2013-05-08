////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Enemy.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓��@����
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{
	namespace baseobject{

	class EnemySphere : public PrimitiveSphere {

		struct  SphereVertex{
			D3DXVECTOR3 vec;
			D3DXVECTOR3 n;
			FLOAT       tu,tv;
		};

		//PrimitiveSphere�p��FVF��DIrectXAPI�ɓn���Ƃ��̃p�����[�^
		enum { BallFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
			LPDIRECT3DTEXTURE9 m_pTexture;

	//Enemy�p		
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Vec2UV(float x,float y,float z,float r,float& u,float& v );
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �FVector��U��V�ɃR���o�[�g
	//// ����       �F  float x     //x�̒l
	////            �F  float y     //y�̒l
	////            �F  float z     //z�̒l
	////            �F  float r     //���̔��a
	////            �F  float& u    //�ϊ�����u�i�e�N�X�`�����U���W�j
	////            �F  float& v    //�ϊ�����v�i�e�N�X�`�����V���W�j
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O(�R�m��搶�̂ЂȌ`���)
	//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
	////            �F
	////
			void Vec2UV(float x,float y,float z,float r,float& u,float& v);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F���𐶐�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
	////            �F
	////
		void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice);
	protected:
	/////////////////// ////////////////////
	//// �֐���     �FEnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
	////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F���̂��쐬
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
	//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �FPrimitiveSphere�̔h���^
	////           �F
	////
		EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			LPDIRECT3DTEXTURE9 pTexture = 0 , wiz::OBJID id = OBJID_3D_ENEMY);


	/////////////////// ////////////////////
	//// �֐���     �F~EnemySphere();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F���̂�j��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �FPrimitiveSphere�̔h���^
	////            �F
	////
		virtual ~EnemySphere();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���̂�`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
		virtual void Draw(DrawPacket& i_DrawPacket) ;
	};

	}//end of namespace baseobject.
	using namespace baseobject;
}//end of namespace wiz.