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
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Result.h"
#include "Factory_Result.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 ResultStage 定義部
****************************************************************************/
/**************************************************************************
 ResultStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
ResultStage::ResultStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)
{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		Factory_Result	resultF( &FPac );
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
ResultStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ResultStage::~ResultStage(){
	
}

void	ResultStage::Update(UpdatePacket &i_UpdatePacket){
  //マウス用データ*************************
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
  //*****************************************
	if( g_bMouseLB/* || g_bMouseRB*/ ){
		//選ばれた画面へとぶ
		i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_TITLE;
	}
}

}
//end of namespace wiz.
