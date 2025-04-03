////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Result.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包データと備考	：クリアステージ
//					▼
//	namespace wiz;
//		class ClearStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Clear.h"
#include "Factory_Clear.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 ClearStage 定義部
****************************************************************************/
/**************************************************************************
 ClearStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
ClearStage::ClearStage(LPDIRECT3DDEVICE9 pD3DDevice, int iDeadCount, int iMaxPosY, int iScratchPoint, Stage* pStage)
	:Stage(pStage)
{
	try{
		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);
		Factory_Clear	resultF( &FPac, iDeadCount, iMaxPosY, iScratchPoint );
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
ClearStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ClearStage::~ClearStage(){
	
}

}
//end of namespace wiz.
