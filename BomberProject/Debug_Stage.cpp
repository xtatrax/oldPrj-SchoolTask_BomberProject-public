////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FDebug_Stage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�N�p�X�e�[�W
//					��
//	namespace wiz;
//		class DebugStage : public MenuStage;
//		class DebugMenu  : public MenuStage;
//
#include "StdAfx.h"
#include "BassMenuItems.h"
#include "Debug_Stage.h"
#include "Factory_Main.h"

namespace wiz{


/**************************************************************************
 DebugStage ��`��
****************************************************************************/
/**************************************************************************
 DebugStage::DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
DebugStage::DebugStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	m_pChildStage = 0;
	try{
	}
	catch(...){
	}
}

/**************************************************************************
 DebugMenu ��`��
****************************************************************************/
/**************************************************************************
 DebugMenu::DebugMenu(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
DebugMenu::DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	m_pChildStage = 0;
	try{
		ButtonSprite* pButton = NULL;
		LPDIRECT3DTEXTURE9 pTex;
		m_Vec.push_back(
			new SpriteObject(
				pD3DDevice,
				m_TexMgr.addTexture(pD3DDevice,L"DBG_DebugMenu.png"),
				D3DXVECTOR3(1.0f,1.0f,1.0f),
				g_vZero,
				D3DXVECTOR3(450.0f,0.0f,0.0f),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF,
				OBJID_UI_SPRITE
			)
		);

		//	: �^�C�g��
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(50.0f,50.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_TITLE,
			0
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: �v���C
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_PLAY.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(50.0f,150.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_PLAY,
			1
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: ���U���g
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(50.0f,250.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_RESULT,
			2
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: ���[�ނ��[�΁[
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(50.0f,350.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_GAMEOVER,
			3
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: �ĂƂ�[��
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(250.0f,50.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENDEBUGSTAGE_TATEAWORKSPACE,
			4
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: �Ƃ���[��
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(250.0f,150.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENDEBUGSTAGE_TOJIWORKSPACE,
			5
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: �����L���O
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(250.0f,250.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_RANKING,
			6
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: �Q�[���N���A
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_.png");
		m_Vec.push_back((pButton = new ButtonSprite(
			pD3DDevice,
			pTex,
			D3DXVECTOR3(0.3f,0.3f,0.3f),
			g_vZero,
			D3DXVECTOR3(250.0f,350.0f,0.0f),
			NULL,
			g_vZero,
			g_vZero,
			0xFFFFFFFF,
			0xFFAAAAAA,
			GM_OPENSTAGE_GAMECLEAR,
			7
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//pTex = m_TexMgr.addTexture(pD3DDevice,L"media/Textures/DBG_CREATE.png");
		//m_Vec.push_back((pButton = new ButtonSprite(
		//	pD3DDevice,
		//	pTex,
		//	D3DXVECTOR3(0.3f,0.3f,0.3f),
		//	g_vZero,
		//	D3DXVECTOR3(50.0f,350.0f,0.0f),
		//	NULL,
		//	g_vZero,
		//	g_vZero,
		//	0xFFFFFFFF,
		//	0xFFAAAAAA,
		//	GM_OPENDEBUGSTAGE_STAGECREATE,
		//	3
		//	)));
		//m_ButtonVec.push_back(pButton->getButtonP());
	}
	catch(wiz::BaseException& e){
        //�ăX���[
        throw BaseException(
				e.what_w(), 
                L"��DebugMenu::DebugMenu()"
                );
	}
	catch(...){
		throw;
	}
}
}
//end of namespace wiz.
