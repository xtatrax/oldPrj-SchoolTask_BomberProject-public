////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Clear.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Clear ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Clear.h"
#include "BassItems.h"
#include "Factory_Score.h"
#include "Factory_Title.h"
#include "Factory_Cursor.h"
#include "Factory_CustomButtonA.h"
#include "Factory_Result.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Clear ��`��
****************************************************************************/
/**************************************************************************
 Factory_Clear::Factory_Clear(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Clear::Factory_Clear(FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint)
{
	try{

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Frame_Clear3.png" ),
				D3DXVECTOR3( 1.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 53.0f, 150.0f, 0.0f ),
				Rect( 0, 0, 512, 256 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		);
		//CLEAR
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Clear4.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-256, 20.0f, 0.0f ),
				Rect( 0, 0, 512, 128 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//�ō����B�_**************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TEST.png" ),
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, 135.0f, 0.0f ),
				Rect( 0, 128, 512, 192),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//���߂���*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"SCRATCH_TIME2.png" ),
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, height-90.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//���S��*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TEST.png" ),
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, height-15.0f, 0.0f ),
				&Rect( 0, 192, 512, 256 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//�g�[�^���|�C���g*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TEST.png" ),
				D3DXVECTOR3( 1.0f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-430.0f, height+86.0f, 0.0f ),
				Rect( 0, 65, 512, 128),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//Please Click
		//*****************************************************************************
/////////////////////////////////////////////////////////////////////////////////
//                                 BACK                                        //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"BACK002.png"),
				fpac->AddTexture(L"BACK001.png"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(980.0f, 560.0f, 0.0f),
				Rect(0,0,148,30),
				Rect(0,0,148,30),
				D3DXVECTOR3( 148.0f,15.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFFFFFF,
				0xFFAAAAAA,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				0.5f,
				Command( GM_OPENSTAGE_TITLE, 0, 0 ),
				OBJID_UI_BUTTON_BACK
			)
		);

		//Score**********************************************
		fpac->m_pVec->push_back(
			new ResultScore(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base1.png"),
				fpac->AddTexture(L"Number_Base2.png"),
				fpac->AddTexture(L"Rate_Number.png"),
				fpac->AddTexture(L"Rate_Number2.png"),
				fpac->AddTexture(L"Rate_Number3.png"),
				D3DXVECTOR3( 0.8f, 0.8f, 0.0f ),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				iDeadCount,
				iMaxPosY,
				iScratchPoint,
				&Rect( 0, 0, 512, 64 )
			)
		);
		//***********************************************************
		// RANK ( S~C )
		fpac->m_pVec->push_back(
			new Rank(
				fpac->pD3DDevice,
				fpac->AddTexture( L"RANK_ver1.png" ),
				fpac->AddTexture( L"RANK_Base2.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f/*D3DXToRadian(30.0f)*/ ),
				D3DXVECTOR3( 830.0f, 400.0f, 0.0f ),
				&Rect( 0, 0, 128, 128 )
			)
		);
		//Click_Please
		fpac->m_pVec->push_back(
			new ClickChar(
					fpac->pD3DDevice,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"user_txt.png"),
					D3DXVECTOR3( 0.5f, 0.5f, 0.0f ),
					g_vZero,
					g_vZero,
					Rect( 0, 0, 512, 64 ),
					D3DXVECTOR3( 40.0f, -70.0f, 0.0f )
			)
		);						
		//�J�[�\��*************************************************
		float	fLineLength	= 550.0f;
		float	fPointSize	= 1.0f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 


		//***************************************************

		system::Sound* pSound = NULL;
		fpac->SetSound(
			pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_CLEAR );

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Clear::~Factory_Clear();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Clear::~Factory_Clear(){
    //�Ȃɂ����Ȃ�
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
