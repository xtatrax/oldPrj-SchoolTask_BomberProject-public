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
				D3DXVECTOR3( wide-128-150, height-20.0f, 0.0f ),
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
				D3DXVECTOR3( wide+100, height, 0.0f ),
				iDeadCount,
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
				D3DXVECTOR3( wide-128-150, height+80.0f, 0.0f ),
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
				D3DXVECTOR3( wide+100, height+100.0f, 0.0f ),
				iMaxPosY,
				&Rect( 0, 0, 512, 64 )
			)
		);
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
