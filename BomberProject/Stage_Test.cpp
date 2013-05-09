////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage_Test.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�e�X�g�p�̃X�e�[�W
//					�F��Scene.cpp Scene::CommandTranslator �֐��Ŏ��̉�����܂�
//					�F��Scene.cpp Scene::Update / AnotherTargetRender / Draw �֐�����Ă΂�܂�
//					��
//	namespace wiz;
//	;
//
#include "StdAfx.h"
#include "Stage_Test.h"
#include "Factory_Player.h"
namespace wiz{

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
DebugStage_TATRA::DebugStage_TATRA(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		//�J�����̃C���X�^���X������
		float ECXPos = 25.1f;
		float ECYPos = 10.1f;		
        m_Vec.push_back(
			new Camera(pD3DDevice,D3DXVECTOR3( ECXPos, ECYPos, -55.7f),D3DXVECTOR3(ECXPos,ECYPos,0.0f), 1 ,300.0f,30.0f)
		);
		//	: �K�C�h���C��
		m_Vec.push_back(new Guide( pD3DDevice ) );



		StageLoader loader(pD3DDevice,L"media/Map/Stages.csv",1,m_Vec,m_TexMgr);
		Factory_Player Pfac( &FPac );
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}

};
