////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Select.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�^�C�g���X�e�[�W
//					��
//	namespace wiz;
//		class StageSelect : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Select.h"
#include "stage.h"
#include "Factory_Select.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 StageSelect ��`��
****************************************************************************/
/**************************************************************************
 StageSelect(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
StageSelect::StageSelect(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{
		FactoryPacket FPac(pD3DDevice,m_IsDialog,&m_Vec,&m_TexMgr,this);
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		Factory_Select	Sfac( &FPac )  ; 

	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
StageSelect();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
StageSelect::~StageSelect(){
	
}

}
//end of namespace wiz.
