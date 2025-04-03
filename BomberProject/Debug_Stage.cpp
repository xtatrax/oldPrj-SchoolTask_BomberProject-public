////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Debug_Stage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバック用ステージ
//					▼
//	namespace wiz;
//		class DebugStage : public MenuStage;
//		class DebugMenu  : public MenuStage;
//
#include "StdAfx.h"
#include "BassMenuItems.h"
#include "Debug_Stage.h"
#include "Factory_Main.h"
#include "Factory_Cursor.h"
namespace wiz{


/**************************************************************************
 DebugStage 定義部
****************************************************************************/
/**************************************************************************
 DebugStage::DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
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
 DebugMenu 定義部
****************************************************************************/
/**************************************************************************
 DebugMenu::DebugMenu(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
DebugMenu::DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	m_pChildStage = 0;
	try{
		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);

		ButtonSprite* pButton = NULL;
		LPTATRATEXTURE pTex;
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_DebugMenu.png");
		m_Vec.push_back(
			new SpriteObject(
				pD3DDevice,
				pTex,
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

		//	: タイトル
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_TITLE.png");
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_OPENSTAGE_TITLE
			)));
		this->AddButton(pButton);

		//	: プレイ
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_OPENSTAGE_PLAY
			)));
		this->AddButton(pButton);

		//	: リザルト
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_WITHOUT
			)));
		this->AddButton(pButton);

		//	: げーむおーばー
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_WITHOUT
			)));
		this->AddButton(pButton);

		//	: てとわーく
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_WITHOUT
			)));
		this->AddButton(pButton);

		//	: デモシーン
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_DEMO.png");
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_OPENSTAGE_DEMO
			)));
		this->AddButton(pButton);

		//	: ステージローダー
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_StageLoader.png");
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_OPENDEBUGSTAGE_STAGELOADERTEST
			)));
		this->AddButton(pButton);

		//	: てとらわーく
		pTex = m_TexMgr.addTexture(pD3DDevice,L"DBG_TATRA.png");
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
			RCTEXT_SOUND_SE_SELECT,
			RCTEXT_SOUND_SE_ENTER,
			0.5f,
			GM_OPENDEBUGSTAGE_TATEAWORKSPACE
			)));
		this->AddButton(pButton);

		float	fLineLength	= 550.0f;
		float	fPointSize	= 1.0f;
		bomberobject::Factory_Cursor	MCfac( &FPac, fLineLength, fPointSize )  ; 

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
		//	RCTEXT_SOUND_SE_SELECT,
		//	RCTEXT_SOUND_SE_ENTER,
		//	0.5f,
		//	GM_OPENDEBUGSTAGE_STAGECREATE
		//	)));
		//m_ButtonVec.push_back(pButton->getButtonP());
	}
	catch(wiz::BaseException& e){
        //再スロー
        throw BaseException(
				e.what_w(), 
                L"↑DebugMenu::DebugMenu()"
                );
	}
	catch(...){
		throw;
	}
}
}
//end of namespace wiz.
