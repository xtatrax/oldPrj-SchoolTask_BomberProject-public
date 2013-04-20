////////////////////////////// //////////////////////////////
//	プロジェクト	：Magnetica
//	ファイル名		：Factory_Player.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{




/**************************************************************************
 class Factory_Player;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Player{
public:
/**************************************************************************
 Factory_Player(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Player(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Player();
};
}
//end of namespace wiz.
