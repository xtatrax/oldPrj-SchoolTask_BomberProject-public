////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Pray.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�v���C�X�e�[�W
//					��
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Factory_Main.h"
#include "Factory_Sound.h"
#include "Stage_Play.h"
#include "stage.h"
#include "Factory_Player.h"

namespace wiz{
using namespace bomberobject;




/**************************************************************************
 PlayStage ��`��
****************************************************************************/
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
PlayStage::PlayStage( LPDIRECT3DDEVICE9 pD3DDevice, DWORD dwStageNum, DWORD dwResumptionCheckPoint, D3DXVECTOR3 vStartPos, Stage* pStage )
	:Stage(pStage)
{
	try{
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"// PlayStage �\�z�J�n\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);

		D3DXVECTOR3* vp = NULL ;
		if( vStartPos != g_vMax )
			vp = &vStartPos;
	
		Factory_Main mainF( &FPac, dwStageNum, dwResumptionCheckPoint, vp );
		m_dwNowStage = dwStageNum ;
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"// PlayStage �\�z����\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
		Debugger::DBGWRITINGLOGTEXT::addStr(L"//-----------------------------------------------------------------------------------------------------//\n");
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"��PlayStage::PlayStage()"
				);
	}
	catch(exception& e){
		Clear();
		//�ăX���[
		throw e;
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
PlayStage::~PlayStage(){
	Debugger::DBGWRITINGLOGTEXT::addStr(L"////////////////////////////////////////////////////////\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"//\n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L"PlayStage::~PlayStage %X\n",this);
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�X�e�[�W���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void PlayStage::Update(UpdatePacket& i_UpdatePacket){
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )

	//	:  �G���^�[�ōăX�^�[�g
	if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RESTART )  ){
		//	:  Alt+ENTER�ōēǂݍ���
		if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RELOAD_SUBKEY ) ){
			PlayerCoil* pc = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL );
			i_UpdatePacket.PushCommand(Command( GM_OPENDEBUGSTAGE_PLAY_RELOAD, (DWORD)pc ));

		}else
		if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RESTART_SUBKEY ) ){
			i_UpdatePacket.PushCommand(Command( GM_OPENSTAGE_PLAY, getNowStage() ));

		}
	}
#endif
	Stage::Update( i_UpdatePacket );
}

}
//end of namespace wiz.
