////////////////////////////// //////////////////////////////
//	プロジェクト	：Stick Figures
//	ファイル名		：MainFactory.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class MainFactory ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "MainFactory.h"
#include "BassItems.h"

namespace wiz{


	
/**************************************************************************
 MainFactory 定義部
****************************************************************************/
/**************************************************************************
 MainFactory::MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
MainFactory::MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
	try{
		
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 MainFactory::~MainFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MainFactory::~MainFactory(){
    //なにもしない
}

}
//end of namespace wiz.
