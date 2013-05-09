////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage_Test.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：テスト用のステージ
//					：★Scene.cpp Scene::CommandTranslator 関数で実体化されます
//					：★Scene.cpp Scene::Update / AnotherTargetRender / Draw 関数から呼ばれます
//					▼
//	namespace wiz;
//	;
//
#include "StdAfx.h"
#include "Stage_Test.h"
namespace wiz{

/**************************************************************************
 PlayStage 定義部
****************************************************************************/
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
DebugStage_TATRA::DebugStage_TATRA(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		//	: ガイドライン
		m_Vec.push_back(new Guide( pD3DDevice ) );

		StageLoader loader(pD3DDevice,L"media/Map/Stages.csv",1,m_Vec,m_TexMgr);
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}

};
