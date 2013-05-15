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
DebugStage_Loader::DebugStage_Loader(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
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

		MapPartsStatus MapData[] = {
			{ OBJID_3D_WALL, D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f), L"", L"", 0, 1.0f },
			{ OBJID_END    , g_vZero, g_vZero, g_vZero, D3DCOLORVALUE(), D3DCOLORVALUE(), D3DCOLORVALUE(), L"", L"", 0, 1.0f }
		
		};


		StageLoader loader(pD3DDevice,m_Vec,m_TexMgr,MapData);
		Factory_Player Pfac( &FPac );
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}

};
