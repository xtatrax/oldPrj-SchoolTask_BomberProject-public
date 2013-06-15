////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Select.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Select ;
//
#include "StdAfx.h"
#include "Factory_Select.h"
#include "Factory_Cursor.h"

namespace wiz{
namespace bomberobject{


	
/**************************************************************************
 Factory_Select 定義部
****************************************************************************/
/**************************************************************************
 Factory_Select::Factory_Select(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Select::Factory_Select(FactoryPacket* fpac ){
	try{
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"↑Factory_Select::Factory_Select()"
				);
	}
	catch(...){
		//再throw
		throw;
	}
}
/**************************************************************************
 Factory_Select::~Factory_Select();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Select::~Factory_Select(){
	//なにもしない
}


}


//end of namespace bomberobject.
}
//end of namespace wiz.