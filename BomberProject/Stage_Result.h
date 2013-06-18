////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Result.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：クリアステージ
//					▼
//	namespace wiz;
//		class ResultStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class ResultStage : public Stage;
 用途: ゲームステージクラス
****************************************************************************/
class ResultStage : public Stage{
	int	m_iTime;
public:	
/**************************************************************************
 ResultStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	ResultStage(LPDIRECT3DDEVICE9 pD3DDevice, int iDeadCount, int iMaxPosY, Stage* pStage = NULL);
/**************************************************************************
ResultStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~ResultStage();
	virtual void Update(UpdatePacket& i_UpdatePacket);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}
//end of namespace wiz.
