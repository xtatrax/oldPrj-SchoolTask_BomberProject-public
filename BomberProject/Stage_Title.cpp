////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�^�C�g���X�e�[�W
//					��
//	namespace wiz;
//		class TitleStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Title.h"
#include "Factory_Title.h"
#include "stage.h"

namespace wiz{

/**************************************************************************
 TitleStage ��`��
****************************************************************************/
/**************************************************************************
 TitleStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
TitleStage::TitleStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		Factory_Title	resultF( &FPac );
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
TitleStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
TitleStage::~TitleStage(){
	
}

}
//end of namespace wiz.
