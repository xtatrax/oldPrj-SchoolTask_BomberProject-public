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

		//	: タイトル
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
			GM_OPENSTAGE_PLAY,
			1
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

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
			GM_OPENSTAGE_RESULT,
			2
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

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
			GM_OPENSTAGE_GAMEOVER,
			3
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

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
			GM_OPENDEBUGSTAGE_TATEAWORKSPACE,
			4
			)));
		m_ButtonVec.push_back(pButton->getButtonP());

		//	: とじわーく
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

		//	: ランキング
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

		//	: ゲームクリア
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
