////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Load.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包データと備考	：ロードステージ
//					▼
//	namespace wiz;
//		class LoadStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
#include "Factory_Load.h"
namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class LoadStage : public Stage;
 用途: ロードステージクラス
****************************************************************************/
class LoadStage : public Stage{
public:	
/**************************************************************************
 LoadStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	LoadStage(LPDIRECT3DDEVICE9 pD3DDevice,Command* Com,Stage* pStage = NULL);
/**************************************************************************
ResultStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~LoadStage();
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}
//end of namespace wiz.
