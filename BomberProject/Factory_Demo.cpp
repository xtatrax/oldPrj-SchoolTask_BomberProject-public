////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Demo.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：ロードファクトリー
//					▼
//	namespace wiz;
//		class Load ;
//		class Factory_Demo ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Demo.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Demo 定義部
****************************************************************************/
/**************************************************************************
 Factory_Demo::Factory_Demo(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Demo::Factory_Demo(FactoryPacket* fpac,Command* Com){
	try{

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Demo::~Factory_Demo();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Demo::~Factory_Demo(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
