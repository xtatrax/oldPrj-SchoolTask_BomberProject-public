////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Result.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�N���A�X�e�[�W
//					��
//	namespace wiz;
//		class ResultStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Result.h"
#include "Factory_Result.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;
namespace stage{
/**************************************************************************
 ResultStage ��`��
****************************************************************************/
/**************************************************************************
 ResultStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
ResultStage::ResultStage(LPDIRECT3DDEVICE9 pD3DDevice, int iDeadCount, int iMaxPosY, int iScratchPoint, Stage* pStage)
	:Stage(pStage)
{
	try{
		FactoryPacket FPac(this);
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		Factory_Result	resultF( &FPac, iDeadCount, iMaxPosY, iScratchPoint);
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
ResultStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ResultStage::~ResultStage(){
	
}

}
//end of namespace stage.
}
//end of namespace wiz.
