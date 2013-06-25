////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Main.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Main ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_Main.h"
//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
#include "StageLoader.h"
#include "Factory_Description.h"
#include "Factory_Description.h"
#include "Factory_Enemy.h"
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "Factory_Score.h"
#include "Factory_Wall.h"
#include "Factory_CheckPointSave.h"
#include "Factory_BackGround.h"
//	: �ǉ��̃C���N���[�h
//////////

namespace wiz{
namespace bomberobject{


	
/**************************************************************************
 Factory_Main ��`��
****************************************************************************/
/**************************************************************************
 Factory_Main::Factory_Main(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Main::Factory_Main(FactoryPacket* fpac, DWORD dwStageNum, DWORD dwResumptionCheckPoint, D3DXVECTOR3* vStartPos ){
	try{
#if defined( ON_GUIDELINE ) 

		//	: �K�C�h���C��
		fpac->m_pVec->push_back(new Guide( fpac->pD3DDevice ) );
#endif
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"\n\n//////////\n");
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"//  : \n");
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"StageNum   = %d\n",dwStageNum);

		//////////
		//	: ���C�g�̐ݒ�
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        fpac->m_pVec->push_back(
			new DirectionalLight(
				fpac->pD3DDevice,
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3( -0.0f, -1.0f, 0.0f)
			)
		);
		//	: ���C�g�̐ݒ�
		//////////

		//////////
		//	: �J�����̐ݒ�
		float ECXPos = 25.1f;
		float ECYPos = 10.666f;
		float ECZPos = -55.7f;
        fpac->m_pVec->push_back(
			new Camera(
				fpac->pD3DDevice,
				D3DXVECTOR3( ECXPos, ECYPos, ECZPos),
				D3DXVECTOR3( ECXPos, ECYPos,   0.0f),
				1 ,
				ECZPos+0.5f,
				30.0f
			)
		);
		//	: �J�����̐ݒ�
		//////////


//������������������������������������������������������������������������������������������������//	

		//////////
		//	: �������H��֔���
		float	fLineLength	= 230.0f;
		float	fPointSize	= 0.5f;
		Factory_BG			Bfac( fpac ) ;
		Factory_Cursor		Mfac( fpac, fLineLength, fPointSize )  ; 
		Factory_Player		Pfac( fpac );
		if( dwStageNum != 5 )
			Factory_Item	Ifac( fpac ) ;
		Factory_Wall		Wfac( fpac ) ;
		if( dwStageNum == 0 )	dwStageNum = 5 ;
		StageLoader			loader(fpac->pD3DDevice,L"media/Map/Stages.csv", dwStageNum,*fpac->m_pVec,*fpac->m_pTexMgr);
		Factory_Coil		Cfac( fpac , dwResumptionCheckPoint, vStartPos );
		Factory_Description	Dfac( fpac ) ;
		Factory_Gage		Gfac( fpac ) ;
		Factory_Score		Sfac( fpac ) ;
		//Factory_Enemy		Efac( fpac ) ;
		Factory_CheckPointSave	CPSfac( fpac , dwStageNum);
		//	: �������H��֔���
		//////////

//������������������������������������������������������������������������������������������������//	


		//////////
		//	: �����̍\�z��BGM�̍Đ��J�n
		system::Sound* pSound = NULL;
		fpac->SetSound(
			pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_PLAY );
		//pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_SPARK );
		//	: �����̍\�z��BGM�̍Đ��J�n
		//////////


		//////////
		//	: �I�u�W�F�N�g�̃\�[�g( ���ߏ����̖��΍� )
		vector<Object*>::size_type pos = fpac->m_pVec->max_size();
		WallObject* wp = (WallObject*)SearchObjectFromID( fpac->m_pVec,OBJID_3D_WALL, &pos );
		fpac->m_pVec->erase( fpac->m_pVec->begin() + pos );
		fpac->m_pVec->push_back( wp );
		//	: �I�u�W�F�N�g�̃\�[�g( ���ߏ����̖��΍� )
		//////////

		
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"��Factory_Main::Factory_Main()"
				);
	}
	catch(...){
		//��throw
		throw;
	}
}
/**************************************************************************
 Factory_Main::~Factory_Main();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Main::~Factory_Main(){
	//�Ȃɂ����Ȃ�
}


}


//end of namespace bomberobject.
}
//end of namespace wiz.