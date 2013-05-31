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

		//	: �g
		//	: ��{��	�c
		D3DXVECTOR3	   BaseWallSize( 2.0f, 26.0f, 0.0f ),
					   BaseWallRot1( 0.0f,  0.0f, 0.0f ),
		//	: ��{��	��90�K
					   BaseWallRot2( 0.0f,  0.0f, 90.0f );
		D3DCOLORVALUE  BaseWallDiffuse  = getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f );		//	Diffuse
		D3DCOLORVALUE  BaseWallSpecular = getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f );		//	Specular
		D3DCOLORVALUE  BaseWallAmbient  = getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f );		//	Ambient


		//	: �p�[�c(�e��)
		//	: ��(���)
		D3DXVECTOR3	   PartsWallSize( 2.0f, 20.0f, 0.0f ),
					   PartsWallRot1( 0.0f,  0.0f, 0.0f ),
					   PartsWallRot2( 0.0f,  0.0f, 0.0f );

		float i = 26.0f ;
		// ��.x=51,�c.y=25.5, UI.y=4.5
		MapPartsStatus MapData[] = {
							 //scale	   Rot			 Pos							    Diffuse			 Specular		   Ambient
			//����
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot2, D3DXVECTOR3( 12.0f, 0.0f, 0.0f), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot2, D3DXVECTOR3( 38.0f, 0.0f, 0.0f), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			//�c����
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f,	   0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f+i*1, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f+i*2, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f+i*3, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f+i*4, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 0.5f, 13.0f+i*5, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			//�c�E��
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f,     0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*1, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*2, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*3, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*4, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },
			{ OBJID_3D_WALL, BaseWallSize, BaseWallRot1, D3DXVECTOR3( 49.5f, 13.0f+i*5, 0.0f ), BaseWallDiffuse, BaseWallSpecular, BaseWallAmbient },

			//�ǉ�
			//1
			{ OBJID_3D_WALL, PartsWallSize, PartsWallRot1, D3DXVECTOR3(20.0f, 28.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//2
			{ OBJID_3D_WALL, PartsWallSize, PartsWallRot1, D3DXVECTOR3(10.0f, 30.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//3
			{ OBJID_3D_WALL, PartsWallSize, PartsWallRot1, D3DXVECTOR3(30.0f, 50.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//4
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(30.0f, 40.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//5
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(15.0f, 60.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//6
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(25.0f, 70.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//7
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(15.0f, 110.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//8
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(13.0f, 90.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//9
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,32.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(29.5f, 93.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//10
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,16.5f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(21.0f, 102.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//11
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,5.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(35.0f, 90.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//12
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(25.0f, 120.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//13
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(10.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//14
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(20.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//15
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(30.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//16
			{ OBJID_3D_WALL, PartsWallSize, D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(30.0f, 145.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//17
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(5.0f, 145.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },

			{ OBJID_3D_MAGNET, D3DXVECTOR3( 1.0f,1.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(30.0f, 10.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f), POLE_N },

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
