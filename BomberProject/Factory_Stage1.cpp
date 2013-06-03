////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Stage1.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Stage1 ;
//
#include "StdAfx.h"
#include "Stage.h"
#include "Factory_Stage1.h"
#include "Factory_Player.h"


namespace wiz{

/**************************************************************************
 Factory_Stage1 ��`��
****************************************************************************/
/**************************************************************************
 Factory_Stage1::Factory_Stage1(
	Factory_Stage1 *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Stage1::Factory_Stage1(FactoryPacket *fpac){
	try{
		LPDIRECT3DDEVICE9 pD3DDevice	= fpac->pD3DDevice	;
		vector<Object*>*  pVec			= fpac->m_pVec		;

		//	: ��{��  �T�C�Y	
		//	:		   �g��
		D3DXVECTOR3	   BaseWallSize ( 2.0f, 26.0f,  0.0f ),
		//	: �p�[�c(�e��)
					   PartsWallSize02( 2.0f,  2.0f,  0.0f ),
					   PartsWallSize05( 2.0f,  5.0f,  0.0f ),
					   PartsWallSize10( 2.0f, 10.0f,  0.0f ),
					   PartsWallSize20( 2.0f, 20.0f,  0.0f ),
					   PartsWallSize25( 2.0f, 25.0f,  0.0f ),
					   PartsWallSize30( 2.0f, 30.0f,  0.0f ),
					   PartsWallSize32( 2.0f, 32.0f,  0.0f ),
					   PartsWallSize35( 2.0f, 35.0f,  0.0f ),
					   PartsWallSize40( 2.0f, 40.0f,  0.0f ),
		//	: ��{��  ��]
					   WallRot1		( 0.0f,  0.0f,  0.0f ),
					   WallRot2		( 0.0f,  0.0f, 90.0f );
		D3DCOLORVALUE  WallDiffuse  = getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f );		//	Diffuse
		D3DCOLORVALUE  WallSpecular = getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f );		//	Specular
		D3DCOLORVALUE  WallAmbient  = getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f );		//	Ambient


		//	: MAP�����E
		D3DCOLORVALUE  MagDiffuse  = getD3DCOLORVALUE( 1.0f, 1.0f, 1.0f, 1.0f );		//	Diffuse
		D3DCOLORVALUE  MagSpecular = getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f );		//	Specular
		D3DCOLORVALUE  MagAmbient  = getD3DCOLORVALUE( 1.0f, 1.0f, 1.0f, 1.0f );		//	Ambient


		float i = 26.0f ;
		// ��.x=51,�c.y=25.5, UI.y=4.5
		MapPartsStatus MapData[] = {
			//	:			 scale		   Rot		   Pos							          Diffuse	   Specular	     Ambient
			//����
			{ OBJID_3D_WALL, BaseWallSize, WallRot2, D3DXVECTOR3( 12.0f,  0.0f,     0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot2, D3DXVECTOR3( 38.0f,  0.0f,     0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			//�c����
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f,	    0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f+i*1, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f+i*2, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f+i*3, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f+i*4, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3(  0.5f, 13.0f+i*5, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			//�c�E��
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f,     0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*1, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*2, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*3, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*4, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, WallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*5, 0.0f ), WallDiffuse, WallSpecular, WallAmbient },

			//�ǉ�
			//1
			{ OBJID_3D_WALL, PartsWallSize20, WallRot1, D3DXVECTOR3(25.0f,  30.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//2
			{ OBJID_3D_WALL, PartsWallSize35, WallRot2, D3DXVECTOR3(35.0f,  65.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//3
			{ OBJID_3D_WALL, PartsWallSize40, WallRot2, D3DXVECTOR3(20.0f,  90.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//4
			{ OBJID_3D_WALL, PartsWallSize40, WallRot2, D3DXVECTOR3(30.0f, 105.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//5
			{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(10.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//6
			{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(20.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//7
			{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(30.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//8
			{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(40.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//9
			{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3( 5.0f, 148.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//10
			{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3(15.0f, 148.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//11
			{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3(25.0f, 148.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			//12
			{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3(45.0f, 148.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			////13
			//{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(10.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			////14
			//{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(20.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			////15
			//{ OBJID_3D_WALL, PartsWallSize25, WallRot1, D3DXVECTOR3(30.0f, 140.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			////16
			//{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3(30.0f, 145.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },
			////17
			//{ OBJID_3D_WALL, PartsWallSize10, WallRot2, D3DXVECTOR3(5.0f, 145.0, 0.0f), WallDiffuse, WallSpecular, WallAmbient },

			//	: MAP���̎��E
			{ OBJID_3D_STATIC_MAGNET, D3DXVECTOR3( 1.0f,1.0f, 0.0f), WallRot1, D3DXVECTOR3(30.0f, 10.0, 0.0f), MagDiffuse, MagSpecular, WallAmbient, POLE_N },
			{ OBJID_3D_STATIC_MAGNET, D3DXVECTOR3( 1.0f,1.0f, 0.0f), WallRot1, D3DXVECTOR3(30.0f, 10.0, 0.0f), MagDiffuse, MagSpecular, WallAmbient, POLE_N },

			{ OBJID_END }
		
		};
		StageLoader loader(pD3DDevice,*pVec,*fpac->m_pTexMgr,MapData);
	}
	catch(...){
		//��throw
		throw;
	}

}

}
//end of namespace wiz.
