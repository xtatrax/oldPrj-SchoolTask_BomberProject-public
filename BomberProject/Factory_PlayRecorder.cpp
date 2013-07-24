//////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_PlayRecorder.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_PlayRecorder.h"
//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////


namespace wiz{
namespace bomberbehavior{

PlayRecorder::PlayRecorder(wiz::OBJID id)
:Behavior(id)
,m_pLButtonBuf(NULL)
,m_pMButtonBuf(NULL)
,m_pRButtonBuf(NULL)
,m_pCamera(NULL)
{

}
PlayRecorder::~PlayRecorder(){
	const char* sDataPath  = "PlayRec/RecordData01.bkr";
	PlayDataBIN SavePacket ;
	//////////
	//	: Folder�p�X�̕�������
	size_t	pathLength ;
	char* pFilePath ;
	for(  pathLength = strlen(sDataPath) ; pathLength >= 0 ; pathLength--  )
		if(  sDataPath[ pathLength ] == '/' || sDataPath[ pathLength ] == '\\'  )
			break ;
	pFilePath	= new char[ pathLength + 1 ] ;
	for(  size_t i = 0 ; i < pathLength ; i++  )
		pFilePath[ i ]	= sDataPath[ i ] ;
	pFilePath[ pathLength ]	= '\0' ;
	//	: Folder�p�X�̕�������
	//////////

	//////////
	//	: �t�H���_�̑��݊m�F�Ɛ�������
	wstring wstr ;
	TLIB::widen(string(pFilePath),wstr);
	if(!PathIsDirectory(wstr.c_str())){
		if(!CreateDirectory(wstr.c_str(),NULL)){
			::MessageBoxA(NULL,"�t�H���_���m�ۏo���܂���ł����[><�A\nTLIB::BinarySave()","����[",MB_OK);
		}
	}
	//	: �t�H���_�̑��݊m�F�Ɛ�������
	//////////


	//////////
	//	: �t�@�C���̍쐬�Ə������ݏ���
	FILE* fp;
	if( fopen_s(&fp,sDataPath,"wb") != 0 ){
		return;	//	: ���Ƃ�TLIB�p��O����Ēu��������
	}
	size_t	PacketSize = sizeof(PlayDataBIN),
			retSize = fwrite((void*)&SavePacket,PacketSize,1,fp);
	if( retSize == 0 ){
		fclose(fp);
		return ;	//	: ���Ƃ�TLIB�p��O����Ēu��������
	}
	fclose(fp);
	//	: �t�@�C���̍쐬�Ə������ݏ���
	//////////

	SafeDeletePointerContainer(m_DataVec);

}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void PlayRecorder::Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void PlayRecorder::Update( UpdatePacket& i_UpdatePacket ){

	if( !m_pCamera ) m_pCamera = (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA);

	if( Cursor2D::getLButtonState() ){
		if( !m_pLButtonBuf ){
			m_pLButtonBuf = new PlayData();
			m_pLButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pLButtonBuf->enumClickType = PlayData::CT_L ;
			m_pLButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pLButtonBuf ){

			m_pLButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pLButtonBuf );
			m_pLButtonBuf = NULL ;
		}
	}

	if( Cursor2D::getMButtonState() ){
		if( !m_pMButtonBuf ){
			m_pMButtonBuf = new PlayData();
			m_pMButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pMButtonBuf->enumClickType = PlayData::CT_M ;
			m_pMButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pMButtonBuf ){
			m_pMButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pMButtonBuf );
			m_pMButtonBuf = NULL ;
		}
	}

	if( Cursor2D::getRButtonState() ){
		if( !m_pRButtonBuf ){
			m_pRButtonBuf = new PlayData();
			m_pRButtonBuf->fBeginTime = i_UpdatePacket.GetTime()->getStageActiveTime();
			m_pRButtonBuf->enumClickType = PlayData::CT_R ;
			m_pRButtonBuf->vClickPoint = Cursor3D::getPos(m_pCamera);
		}
	}else{
		if( m_pRButtonBuf ){
			m_pRButtonBuf->fEndTime = i_UpdatePacket.GetTime()->getStageActiveTime() ;
			m_DataVec.push_back( m_pRButtonBuf );
			m_pRButtonBuf = NULL ;
		}
	}

	Debugger::DBGSTR::addStr(L"m_DataVec.size() = %d\n",m_DataVec.size());
}

RecorderFactory::RecorderFactory(FactoryPacket* fpac){
	fpac->AddObject(new PlayRecorder(OBJID_BEHAVIOR_PLAYSAVE));
}
}
}