////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Select.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：タイトルステージ
//					▼
//	namespace wiz;
//		class StageSelect : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Select.h"
#include "stage.h"
#include "Factory_Select.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 StageSelect 定義部
****************************************************************************/
/**************************************************************************
 StageSelect(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
StageSelect::StageSelect(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{
		FactoryPacket FPac(pD3DDevice,m_IsDialog,&m_Vec,&m_TexMgr,this);
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		Factory_Select	Sfac( &FPac )  ; 

	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
StageSelect();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
StageSelect::~StageSelect(){
	
}

}
//end of namespace wiz.
