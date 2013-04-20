////////////////////////////// //////////////////////////////
//	プロジェクト	：Magnetica
//	ファイル名		：Factory_Main.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Main ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Main.h"
#include "BassItems.h"

namespace wiz{


	
/**************************************************************************
 Factory_Main 定義部
****************************************************************************/
/**************************************************************************
 Factory_Main::Factory_Main(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Main::Factory_Main(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
	try{
		
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Main::~Factory_Main();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Main::~Factory_Main(){
    //なにもしない
}

}
//end of namespace wiz.
