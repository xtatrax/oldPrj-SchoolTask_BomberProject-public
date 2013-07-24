////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FScene.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�V�[��
//					�F�V�[���̓f�o�C�X����Ă΂�܂�
//					��
//	namespace wiz;
//		class Scene ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Debug_Stage.h"
#include "Stage_Title.h"
#include "Stage_Select.h"
#include "Stage_Play.h"
#include "Stage_Clear.h"
#include "Stage_Result.h"
#include "Stage_Load.h"
#include "Stage_Test.h"
#include "Stage_Demo.h"
#include <process.h>
#include "Factory_Player.h"
#include <string.h>

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 Scene ��`��
***************************************************************************/
HANDLE	Scene::m_hLoadingThread				;

/////////////////// ////////////////////
//// �֐���     �Fvoid Clear()
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g�̃N���A
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::setStages(){
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Clear()
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g�̃N���A
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::Clear(){
	SafeDeleteStage(m_pRootStage);
}
/////////////////// ////////////////////
//// �֐���     �FScene(LPDIRECT3DDEVICE9 pD3DDevice)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�V�[���𐶐�
//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F���s�������O��throw
////            �F
////
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice,Command* pCommand)
:m_pRootStage(NULL)
,m_pStgBuf(NULL)
,m_pLoadDevice(NULL)
,m_bLoadingComplete(false)
,m_bUpdateThreadSuspendRequest(false)
,m_bUpdateThreadResumeRequest(false)
,m_fStageNotFoundMessageTime(0.0f)
{
	try{
        //�����`�F�b�N
        if(!pD3DDevice){
            throw BaseException(L"�V�[���̏������Ɏ��s���܂����B�f�o�C�X�������ł��B",
            L"Scene::Scene()");
		}
		//////////
		//	: �f�o�b�O�p�ݒ�
		#if defined(ON_DEBUGGINGPROCESS)
			//���[�g�̃X�e�[�W�Ƀf�o�b�O���j���[��ݒ�
			pCommand->m_Command = GM_OPENSTAGE_TITLE ;
			//*pCommand = Command(GM_OPENSTAGE_PLAY,3,0) ;
			//*pCommand = Command(GM_OPENSTAGE_PLAY,100,0) ;
		#else 
		//	: �����[�X�p�ݒ�
		//���[�g�̃X�e�[�W�Ƀ^�C�g�����j���[��ݒ�
			pCommand->m_Command = GM_OPENSTAGE_TITLE ;

		#endif
		//
		//////////

		//////////
		//	: ���[�h�p�X���b�h�쐬
		#ifdef CF_LOADINGANIMATION
		//m_hLoadingThread = (HANDLE) _beginthread(
		//	&Scene::LoadingThread,	// �����`�����N��
		//	0,
		//	this);
		m_hLoadingThread = (HANDLE) _beginthreadex(
			NULL,
			0,
			&Scene::LoadingThread,	// �����`�����N��
			this,
			CREATE_SUSPENDED,
			NULL);
		#endif
		//
		//////////

		SetRenderStateArray(pD3DDevice,g_GlobalRenderStates);

    }
    catch(wiz::BaseException& e){
        //�j������
        Clear();
        throw BaseException(
			e.what_w(), 
            L"��Scene::Scene()"
            );
	}
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �֐���     �F~Scene()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�V�[����j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
Scene::~Scene()
{
    //�j������
    Clear();
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.GetTime(),
////            �F      const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F�֐�
//// �p�r       �F�V�[�����X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���[�̃X�e�[�^�X
////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::Update(UpdatePacket& i_UpdatePacket){

	if(m_pRootStage){

		#if defined(ON_DEBUGGINGPROCESS)
		//	:  �o�b�N�{�^���Ńf�o�b�O���j���[��
		if(i_UpdatePacket.m_pCntlState->Gamepad.wPressedButtons.XConState.BACK)
			i_UpdatePacket.PushCommand( GM_OPENDEBUGSTAGE_DEBUGMENU );
		#endif
		m_pRootStage->getActiveStage()->Update(i_UpdatePacket);
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid AnotherTargetRender(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
//// �J�e�S��   �F�֐�
//// �p�r       �F�^�[�Q�b�g�����_�����O
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
////            �F
////
void Scene::Render(RenderPacket& i_RenderPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Render(i_RenderPacket);
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw(DrawPacket& i_DrawPacket);
//// �J�e�S��   �F�֐�
//// �p�r       �F�V�[����`��
//// ����       �F  DrawPacket& i_DrawPacket 
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O(�R�m��搶�̂ЂȌ`���)
//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
////            �F
////
void Scene::Draw(DrawPacket& i_DrawPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Draw(i_DrawPacket);
	}
	//CommandTranslator(i_DrawPacket);
}

/////////////////// ////////////////////
//// �֐���     �Fvoid CommandTranslator(BassPacket& i_BassPacket);
//// �J�e�S��   �F�֐�
//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Scene::CommandTranslator(BassPacket& i_BassPacket){

	Command comBuf = i_BassPacket.PopCommand();
	switch(comBuf.m_Command){
		case GM_OPENSTAGE_TITLE:
			//	: �^�C�g�����
			SafeDeleteStage(m_pRootStage);
			m_pRootStage =
				new
				StageSelect( i_BassPacket.GetDevice() , new TitleStage(i_BassPacket.GetDevice()));
			//strrchr(__FILE__,'\\' );
			break;
		case GM_OPENSTAGE_DEMO:
			//	: �^�C�g�����
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DemoStage( i_BassPacket.GetDevice() );
			break;
		case GM_OPENSTAGE_LOAD_PLAY:
			comBuf.m_Command = GM_OPENSTAGE_PLAY;
			goto PRGOTO_GM_OPENSTAGE_LOAD;
		case GM_OPENSTAGE_LOAD:
			//	: ���[�h���
			PRGOTO_GM_OPENSTAGE_LOAD:
			SafeDeleteStage(m_pRootStage);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  PRGOTO_GM_OPENSTAGE_LOAD  �X�e�[�W�쐬�J�n  ");
			m_pRootStage = new LoadStage(i_BassPacket.GetDevice(),&comBuf);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  PRGOTO_GM_OPENSTAGE_LOAD  �X�e�[�W�쐬OK  ");
			break;
		case GM_OPENSTAGE_PLAY:
			try{
				//	: �Q�[���X�e�[�W
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  �X�e�[�W�쐬�J�n  ");
				this->m_pStgBuf = new PlayStage(i_BassPacket.GetDevice(), comBuf.m_Param1, comBuf.m_Param2);
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  �X�e�[�W�쐬����  ");
				//	: 
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  �O�X�e�[�W�폜�J�n  ");
				SafeDeleteStage(m_pRootStage);
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  �O�X�e�[�W�폜�I��  ");
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ���[�h���s
				::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"�G���[",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_BassPacket.GetDevice());
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENDEBUGSTAGE_DEBUGMENU:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugMenu(i_BassPacket.GetDevice());
			break;

		case GM_OPENSTAGE_CLEAR:
			//	: �Q�[���N���A���
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  �X�e�[�W�폜�J�n  ");
			SafeDeleteStage(m_pRootStage);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  �X�e�[�W�폜OK  ");
			m_pRootStage = new ClearStage(i_BassPacket.GetDevice(), comBuf.m_Param1,
														comBuf.m_Param2, comBuf.m_Param3 );
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  �X�e�[�W�쐬OK  ");
			break;

		case GM_OPENSTAGE_RESULT:
			//	: ���U���g���
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new ResultStage(i_BassPacket.GetDevice(), comBuf.m_Param1,
														comBuf.m_Param2, comBuf.m_Param3 );
			break;

		case GM_OPENDEBUGSTAGE_PLAY_RELOAD:
			//	: �����[�h
			try{
				//	: �Q�[���X�e�[�W
				PlayerCoil* pc = (PlayerCoil*)comBuf.m_Param1 ;
				DWORD dwStageNum = m_pRootStage ? ((PlayStage*)m_pRootStage)->getNowStage() : 0 ;
				this->m_pStgBuf = new PlayStage( i_BassPacket.GetDevice(), dwStageNum ,comBuf.m_Param2, pc->getPos() );
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ���[�h���s
				::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"�G���[",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_BassPacket.GetDevice());
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;

//���Ή��̃X�e�[�W

		case GM_OPENSTAGE_RANKING:
			//	: �����L���O���
		case GM_OPENSTAGE_GAMEOVER:
			//	: �Q�[���I�[�o�[���
		case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:

		case GM_OPENDEBUGSTAGE_STAGELOADERTEST:


		case GM_OPENDEBUGSTAGE_STAGECREATE:
			m_fStageNotFoundMessageTime          = 3.0f ;
			break ; 

		case GM_EXIT:
			SafeDeleteStage(m_pRootStage);
			wiz::DxDevice::Destroy();

			//::DestroyWindow(wiz::DxDevice::m_hWnd);
			break;
	}
	if(m_bLoadingComplete){
		SafeDeleteStage(m_pRootStage);
		m_pRootStage = m_pStgBuf;
		m_bLoadingComplete = false;
		i_BassPacket.GetTime()->TimeUpdate();
		i_BassPacket.GetTime()->TimeUpdate();
	}
	if( m_fStageNotFoundMessageTime > 0.0f ){
		float f = (float)i_BassPacket.GetTime()->getElapsedTime();
		m_fStageNotFoundMessageTime -= f ;
		Debugger::DBGSTR::addStrTop(L"���Ή��̃V�[���ł�");
	}
	i_BassPacket.ClearCommand();
}
/////////////////// ////////////////////
//// �֐���     �Funsigned __stdcall Scene::LoadingThread(void *args)
//// �J�e�S��   �F�֐�
//// �p�r       �F���[�h�p�X���b�h����
//// ����       �F  void*	args	//	: �V�[���ւ̃|�C���^��n���Ă�������
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
unsigned __stdcall Scene::LoadingThread(void *args)
//void Scene::LoadingThread(void* args)
{
	Scene* This = reinterpret_cast<Scene*>(args);
	
	//	: �T�X�y���h�����p���[�v
	while(true){
		//switch(This->m_LoadCommand.m_Command){
			//	: �Q�[���X�e�[�W
			//case GM_OPENSTAGE_PLAY:
			//	This->m_pStgBuf = new PlayOpeningStage(This->m_pLoadDevice);
			//	break;


			//	: �f�o�b�O�X�e�[�W
			//case GM_OPENDEBUGSTAGE_STAGECREATE:
			//	SafeDeleteStage();
			//	m_pRootStage = new DevelopStage(i_DrawPacket.GetDevice());
			//	break;
		//}
		This->m_bLoadingComplete = true;
		This->m_pLoadDevice = NULL ;
		This->m_LoadCommand.Clear();
		#ifdef CF_LOADINGANIMATION
			SuspendThread(m_hLoadingThread);
			//CloseHandle(m_hLoadingThread);
			//_endthread();
		#else
			break;
		#endif
	}
	return 0;
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand)
//// �J�e�S��   �F�֐�
//// �p�r       �F���[�h�p�X���b�h�̃����`���[
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand){

	m_LoadCommand = *pCommand;
	m_pLoadDevice = pD3DDevice ;
#ifdef CF_LOADINGANIMATION
	ResumeThread(m_hLoadingThread);
#else
	LoadingThread(this);
#endif
}
/////////////////// ////////////////////
//// �֐���     �Fvoid SafeDeleteStage()
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�e�[�W�����S�ɍ폜����
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::SafeDeleteStage(Stage* &pStage){
	#ifndef CF_SINGLETHREAD
		//	: �}���`�X���b�h���[�h�̏ꍇ
		//	: �f�[�^�փA�N�Z�X���ɂ����Ȃ�폜�����̂�h�����߂�
		//	: ��U�A�b�v�f�[�g�X���b�h���x�~����
		setUpdateThreadSuspendRequest();
		//	: �A�b�v�f�[�g�X���b�h���x�~����܂ő҂�
		while(!getUpdateThreadSuspend()){
			Sleep(1);
		}
	#endif
	//	: �V�[�����폜
	SafeDelete( pStage );
	pStage = NULL;
	#ifndef CF_SINGLETHREAD
		//	: �x�~�����X���b�h���ĊJ������
		setUpdateThreadResumeRequest();
	#endif
}


}
//end of namespace wiz.

