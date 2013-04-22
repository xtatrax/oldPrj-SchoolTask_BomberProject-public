////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Pray.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：プレイステージ
//					▼
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
namespace wiz{
class PlayStage;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class PlayStage : public Stage;
 用途: ゲームステージクラス
****************************************************************************/
class PlayOpeningStage : public Stage{
public:	
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	PlayOpeningStage(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
PlayStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~PlayOpeningStage();
/**************************************************************************
 void PlayStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
	virtual void Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_Time,const CONTROLER_STATE* pCntlState,Command& Com);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice, Tempus2 *i_Time, Command &Com);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class PlayStage : public Stage;
 用途: ゲームステージクラス
****************************************************************************/
class PlayStage : public Stage{
	friend class PlayOpeningStage;
public:	
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage = NULL);
/**************************************************************************
PlayStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~PlayStage();
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}
//end of namespace wiz.
