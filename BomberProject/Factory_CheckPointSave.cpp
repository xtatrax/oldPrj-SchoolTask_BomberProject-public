//////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPointSave.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�`�F�b�N�|�C���g�ʉ݂ŃZ�[�u����@�\
//					��
//	namespace wiz;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_CheckPointSave.h"
//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////


namespace wiz{
namespace bomberbehavior{
CheckPointSave* CheckPointSave::m_pMyInstance = NULL ;
CheckPointSave::CheckPointSave(DWORD dwStageNum)
:Behavior(OBJID_BEHAVIOR_CHECKPOINTSAVE)
,m_pCheckPoint( NULL )
,m_pCoil( NULL )
{
	m_Data.dwStageNum = dwStageNum;

}

/////////////////// ////////////////////
//// �p�r       �Fvoid CheckPointSave::Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void CheckPointSave::Update( UpdatePacket& i_UpdatePacket ){
	!m_pCoil		&& (       m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL			) ) ;
	!m_pCheckPoint	&& ( m_pCheckPoint = (CheckPoint*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CHECKPOINT	) ) ;
	if( m_pCheckPoint->getActiveItem() > m_Data.dwCheckPoint){
		m_Data.dwCheckPoint = m_pCheckPoint->getActiveItem();
		m_Data.dwDeadNum	= m_pCoil->getDeadCount();
		TLIB::BinarySave( RCTEXT_SAVEDATA_FILENAME,m_Data);
	}

}


/////////////////// ////////////////////
//// �֐���     �FFactory_CheckPointSave(FactoryPacket* fpac)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�`�F�b�N�|�C���g�ŃZ�[�u����@�\���쐬���܂�
//// ����       �F  FactoryPacket* fpac
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
Factory_CheckPointSave::Factory_CheckPointSave(FactoryPacket* fpac,DWORD dwStageNum){
	fpac->AddObject(
		CheckPointSave::getInstance(dwStageNum)
	);
	
};


}
}