////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：タイトルステージ
//					▼
//	namespace wiz;
//		class TitleStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_Title.h"
#include "stage.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 TitleStage 定義部
****************************************************************************/
/**************************************************************************
 TitleStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
TitleStage::TitleStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{

		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		Factory_Title	Tfac( &FPac );


	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
TitleStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
TitleStage::~TitleStage(){
	
}

}
//end of namespace wiz.
