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
#include "Stage_Play.h"
#include "Stage_Result.h"
#include "Stage_Test.h"
#include <process.h>
#include "Factory_Player.h"


namespace wiz{
using namespace bomberobject;

/**************************************************************************
 Scene ��`��
***************************************************************************/
HANDLE	Scene::m_hLoadingThread				;
//Stage*	Scene::m_pStgBuf			= NULL	;
//bool	Scene::m_bLoadingComplete	= false	;
/////////////////// ////////////////////
//// �֐���     �Fvoid Clear()
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g�̃N���A
//// ����       �F����
//// �ߒl       �F����
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
//// ����       �F����
//// �ߒl       �F����
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
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F���s�������O��throw
////            �F
////
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pRootStage(NULL)
,m_pStgBuf(NULL)
,m_bLoadingComplete(false)
,m_bUpdateThreadSuspendRequest(false)
,m_bUpdateThreadResumeRequest(false)
,m_pD3DDevice(pD3DDevice)
,m_fStageNotFoundMessageTime(0.0f)
{
    try{
        //�����`�F�b�N
        if(!pD3DDevice){
            throw BaseException(L"�V�[���̏������Ɏ��s���܂����B�f�o�C�X�������ł��B",
            L"Scene::Scene()");
        }
		m_pD3DDevice = pD3DDevice;
//////////
//	: �f�o�b�O�p�ݒ�
#if defined(DEBUG) || defined(_DEBUG) || defined(ON_DEBUGGINGPROCESS)
		try{
			//���[�g�̃X�e�[�W�Ƀf�o�b�O���j���[��ݒ�
			m_pRootStage	= new PlayStage(pD3DDevice);
			//m_pRootStage	= new TitleStage(pD3DDevice);
			//m_pRootStage	= new ResultStage(pD3DDevice);
		}
		catch(LoaderException& e){
			//	: ���[�h���s
			::MessageBox(g_hWnd,e.what_w(),L"�G���[",MB_OK);
			if( !m_pRootStage ) m_pRootStage = new TitleStage(pD3DDevice);
			//SafeDeleteStage(this->m_pStgBuf);
		}
		catch(...){
			throw ;
		}

#else 
//	: �����[�X�p�ݒ�
		//���[�g�̃X�e�[�W�Ƀ^�C�g�����j���[��ݒ�
		m_pRootStage = new TitleStage(pD3DDevice);

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
//// ����       �F����
//// �ߒl       �F����
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
//// �֐���     �Fvoid Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            �F      const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F�֐�
//// �p�r       �F�V�[�����X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���[�̃X�e�[�^�X
////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::Update(UpdatePacket& i_UpdatePacket){

	if(m_pRootStage){

#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
		//	:  �o�b�N�{�^���Ńf�o�b�O���j���[��
		if(i_UpdatePacket.pCntlState->Gamepad.wPressedButtons.XConState.BACK)
			i_UpdatePacket.pCommand->m_Command = GM_OPENDEBUGSTAGE_DEBUGMENU;
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
//// �ߒl       �F����
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
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
////            �F
////
void Scene::Draw(DrawPacket& i_DrawPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Draw(i_DrawPacket);
	}
	CommandTranslator(i_DrawPacket);
}

/////////////////// ////////////////////
//// �֐���     �Fvoid CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
//// �J�e�S��   �F�֐�
//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F
////            �F
////
void Scene::CommandTranslator(DrawPacket& i_DrawPacket){

	switch(i_DrawPacket.pCommand->m_Command){
		case GM_OPENSTAGE_TITLE:
			//	: �^�C�g�����
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
			break;
		case GM_OPENSTAGE_PLAY:
			try{
				//	: �Q�[���X�e�[�W

				this->m_pStgBuf = new PlayStage(i_DrawPacket.pD3DDevice);
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ���[�h���s
				::MessageBox(g_hWnd,e.what_w(),L"�G���[",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENSTAGE_PLAY_RELOAD:
			try{
				//	: �Q�[���X�e�[�W
				PlayerCoil* pc = (PlayerCoil*)i_DrawPacket.pCommand->m_Param1 ;
				this->m_pStgBuf = new PlayStage( i_DrawPacket.pD3DDevice, pc->getPos() );
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ���[�h���s
				::MessageBox(g_hWnd,e.what_w(),L"�G���[",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENDEBUGSTAGE_DEBUGMENU:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugMenu(i_DrawPacket.pD3DDevice);
			break;

		case GM_OPENSTAGE_RESULT:
			//	: �Q�[���N���A���
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new ResultStage(i_DrawPacket.pD3DDevice);
			break;


		case GM_OPENSTAGE_RANKING:
			//	: �����L���O���
		case GM_OPENSTAGE_GAMEOVER:
			//	: �Q�[���I�[�o�[���



		//case GM_OPENDEBUGSTAGE_STAGECREATE:
		//	SafeDeleteStage();
		//	m_pRootStage = new DevelopStage(i_DrawPacket.pD3DDevice);
		//	break;
			m_fStageNotFoundMessageTime          = 3.0f ;
			break ; 
		//	: �f�o�b�O�X�e�[�W
		case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:
			try{
				//	: �Q�[���X�e�[�W
				this->m_pStgBuf = new DebugStage_TATRA(i_DrawPacket.pD3DDevice);
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ���[�h���s
				::MessageBox(g_hWnd,e.what_w(),L"�G���[",MB_OK);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}
			//SafeDeleteStage(m_pRootStage);
			//m_pRootStage = new DebugStage_TATRA(i_DrawPacket.pD3DDevice);
			break;

		case GM_OPENDEBUGSTAGE_STAGELOADERTEST:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugStage_Loader(i_DrawPacket.pD3DDevice);
			break;
		case GM_EXIT:
			::DestroyWindow(g_hWnd);
			break;
	}
	if(m_bLoadingComplete){
		SafeDeleteStage(m_pRootStage);
		m_pRootStage = m_pStgBuf;
		m_bLoadingComplete = false;
		i_DrawPacket.pTime->TimeUpdate();
		i_DrawPacket.pTime->TimeUpdate();
	}
	if( m_fStageNotFoundMessageTime > 0.0f ){
		float f = (float)i_DrawPacket.pTime->getElapsedTime();
		m_fStageNotFoundMessageTime -= f ;
		Debugger::DBGSTR::addStrTop(L"���Ή��̃V�[���ł�");
	}
	i_DrawPacket.pCommand->m_Command = GM_WITHOUT ;
	i_DrawPacket.pCommand->m_Param1  = 0 ;
	i_DrawPacket.pCommand->m_Param2  = 0 ;

}
unsigned __stdcall Scene::LoadingThread(void *args)
//void Scene::LoadingThread(void* args)
{
	Scene* This = reinterpret_cast<Scene*>(args);
	while(true){
		//switch(This->m_LoadCommand.m_Command){
		//	//	: �Q�[���X�e�[�W
		//	case GM_OPENSTAGE_PLAY:
		//		This->m_pStgBuf = new PlayOpeningStage(This->m_pD3DDevice);
		//		break;


		//	//	: �f�o�b�O�X�e�[�W
		//	case GM_OPENDEBUGSTAGE_TOJIWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_TojimaWorkSpace(This->m_pD3DDevice);
		//		break;
		//	case GM_OPENDEBUGSTAGE_HSWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_HSWorkSpace(This->m_pD3DDevice);
		//		break;
		//	case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_TatraWorkSpace(This->m_pD3DDevice);
		//		break;
		//	//case GM_OPENDEBUGSTAGE_STAGECREATE:
		//	//	SafeDeleteStage();
		//	//	m_pRootStage = new DevelopStage(i_DrawPacket.pD3DDevice);
		//	//	break;
		//}
		//This->m_bLoadingComplete = true;
		//#ifdef CF_LOADINGANIMATION
		//	SuspendThread(m_hLoadingThread);
		//	//CloseHandle(m_hLoadingThread);
		//	//_endthread();
		//#else
		//	break;
		//#endif
	}
	return 0;
}

void Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand){

	m_LoadCommand = *pCommand;
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
//// ����       �F����
//// �ߒl       �F����
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

