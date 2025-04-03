////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Demo.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包データと備考	：タイトルステージ
//					▼
//	namespace wiz;
//		class DemoStage : public Stage ;
//
#include "StdAfx.h"
#include "Stage_Demo.h"
#include "Factory_Demo.h"

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 DemoStage 定義部
****************************************************************************/
/**************************************************************************
 DemoStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
DemoStage::DemoStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{
		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);
		Factory_Demo  Dfac(&FPac,&Command());
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
DemoStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
DemoStage::~DemoStage(){
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"DemoStage::~DemoStage()\n");
}

}
//end of namespace wiz.
