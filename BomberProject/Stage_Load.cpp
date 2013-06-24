////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Load.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F���[�h�X�e�[�W
//					��
//	namespace wiz;
//		class LoadStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Load.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 LoadStage ��`��
****************************************************************************/
/**************************************************************************
 LoadStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
LoadStage::LoadStage(LPDIRECT3DDEVICE9 pD3DDevice,Command* Com,Stage* pStage)
	:Stage(pStage)
{
	try{
		FactoryPacket FPac(this);
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		Factory_Load	loadF( &FPac, Com );
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
LoadStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
LoadStage::~LoadStage(){
	
}

}
//end of namespace wiz.
