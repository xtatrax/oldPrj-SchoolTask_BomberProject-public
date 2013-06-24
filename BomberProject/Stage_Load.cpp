////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Load.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：ロードステージ
//					▼
//	namespace wiz;
//		class LoadStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Load.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 LoadStage 定義部
****************************************************************************/
/**************************************************************************
 LoadStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
LoadStage::LoadStage(LPDIRECT3DDEVICE9 pD3DDevice,Command* Com,Stage* pStage)
	:Stage(pStage)
{
	try{
		FactoryPacket FPac(this);
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		Factory_Load	loadF( &FPac, Com );
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
LoadStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
LoadStage::~LoadStage(){
	
}

}
//end of namespace wiz.
