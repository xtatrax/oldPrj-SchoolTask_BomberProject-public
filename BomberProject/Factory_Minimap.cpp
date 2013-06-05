////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Minimap.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Minimap ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Minimap.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{


/**************************************************************************
 Factory_Minimap 定義部
****************************************************************************/
/**************************************************************************
 Factory_Minimap::Factory_Minimap(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Minimap::Factory_Minimap(FactoryPacket* fpac){
		try{
		}
		catch(...){
			//再throw
			throw;
		}
	}

/**************************************************************************
 Factory_Minimap::~Factory_Minimap();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_Minimap::~Factory_Minimap(){
//なにもしない
	}
}//end of namespace bomberobject.
}//end of namespace wiz.