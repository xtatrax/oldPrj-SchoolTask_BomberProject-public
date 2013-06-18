////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Result.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Result ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Result.h"
#include "BassItems.h"
#include "Factory_Score.h"
#include "Factory_Title.h"
#include "Factory_Cursor.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Result ��`��
****************************************************************************/
/**************************************************************************
 Factory_Result::Factory_Result(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Result::Factory_Result(FactoryPacket* fpac, int iDeadCount, int iMaxPosY)
{
	try{
		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		//RSULT
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"RESULT.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128, 50.0f, 0.0f ),
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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"dead_count1.png" ),
				D3DXVECTOR3( 0.5f, 1.6f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-150, height-50.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		fpac->m_pVec->push_back(
			new Score(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base1.png"),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				D3DXVECTOR3( wide+100, height-30, 0.0f ),
				321/*iDeadCount*/,
				&Rect( 0, 0, 512, 64 )
			)
		);

		//�ō����B�_**************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MAX_RANGE1.png" ),
				D3DXVECTOR3( 0.5f, 1.6f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-150, height+50.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		fpac->m_pVec->push_back(
			new Score(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base2.png"),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				D3DXVECTOR3( wide+100, height+70.0f, 0.0f ),
				100/*iMaxPosY*/,
				&Rect( 0, 0, 512, 64 )
			)
		);
		//*****************************************************************************
		//Please Click
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->AddTexture( L"Click_Please1.png" ),
					GM_OPENSTAGE_TITLE,
					D3DXVECTOR3(1.0f,1.0f,0.0f),
					g_vZero,
					D3DXVECTOR3( wide-256.0f, 500.0f, 0.0f ),
					Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);

		//�J�[�\��*************************************************
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 

		//*****************************************************************************
		//system::Sound* pSound = NULL;
		//fpac->SetSound(
		//	pSound = new system::Sound( 
		//		RCTEXT_SOUND_WAVEBANK,
		//		RCTEXT_SOUND_SOUNDBANK,
		//		OBJID_SYS_SOUND
		//	)
		//);
		//pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_CLEAR );

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Result::~Factory_Result();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Result::~Factory_Result(){
    //�Ȃɂ����Ȃ�
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
