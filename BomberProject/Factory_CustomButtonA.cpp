////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CustomButtonA.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ButtonSpriteのCustom版
//					：タイトルとかで使用
//					▼
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#include "StdAfx.h"
#include "Factory_CustomButtonA.h"


namespace wiz{
namespace bomberobject{

class CustomButtonA{
};

/**************************************************************************
 Factory_CustomButtonA 定義部
****************************************************************************/
/**************************************************************************
 Factory_CustomButtonA::Factory_CustomButtonA(
	FactoryPacket* fpac		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_CustomButtonA::Factory_CustomButtonA( FactoryPacket* fpac ){
	try{


	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_CustomButtonA::~Factory_CustomButtonA();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_CustomButtonA::~Factory_CustomButtonA(){
    //なにもしない
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
