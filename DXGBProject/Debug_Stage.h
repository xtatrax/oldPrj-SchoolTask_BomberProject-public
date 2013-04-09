////////////////////////////// //////////////////////////////
//	プロジェクト	：Stick Figures
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
#pragma once

#include "StdAfx.h"
#include "Stage.h"
namespace wiz{

/**************************************************************************
 class DebugStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class DebugStage : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	DebugStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


/**************************************************************************
 class DebugMenu : public Stage;
 用途: デバッグ用ステージ
 　　（書く画面へ直接移動できる）
****************************************************************************/
class DebugMenu : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


//end of namespace wiz.
}
