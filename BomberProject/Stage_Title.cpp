////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包データと備考	：タイトルステージ
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

		FactoryPacket FPac(pD3DDevice,this->m_IsDialog,&Command(),this);

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
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"TitleStage::~TitleStage()\n");
}

}
//end of namespace wiz.
