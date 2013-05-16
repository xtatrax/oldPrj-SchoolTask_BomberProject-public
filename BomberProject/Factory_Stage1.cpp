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

		//�J�����̃C���X�^���X������
		float ECXPos = 25.1f;
		float ECYPos = 10.1f;
		pVec->push_back(
			new Camera(pD3DDevice,D3DXVECTOR3( ECXPos, ECYPos, -55.7f),D3DXVECTOR3(ECXPos,ECYPos,0.0f), 1 ,300.0f,30.0f)
		);
		//	: �K�C�h���C��
		pVec->push_back(new Guide( pD3DDevice ) );

		/*
			DWORD			enClassid ;	//	wiz::CLASSID�Ŏw�肵�Ă�������
			D3DXVECTOR3		vScale    ;
			D3DXVECTOR3		vRot      ;
			D3DXVECTOR3		vPos      ;
			D3DCOLORVALUE   Diffuse   ;
			D3DCOLORVALUE   Specular  ;
			D3DCOLORVALUE   Ambient   ;
			bool			bPool     ;

			//	: �I�v�V����
			wstring			sTexturePath	;

			wstring			sFilePath		;
			DWORD			dwMotionNum		;
			float			fTracSpeed		;

		*/
		MapPartsStatus MapData[] = {
			{ OBJID_3D_WALL,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_ITEM,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_MAGNET,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_END }
		
		};


		StageLoader loader(pD3DDevice,*pVec,*fpac->m_pTexMgr,MapData);


		Factory_Player Pfac( fpac );


		//	: �X�v���C�g
		pVec->push_back(
			new SpriteObject(
				pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"display.png" ),
				g_vOne,
				g_vZero,
				g_vZero,
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		);


	}
	catch(...){
		//��throw
		throw;
	}

}

}
//end of namespace wiz.
