////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Stage1.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Stage1 ;
//
#pragma once

#include "StdAfx.h"

namespace wiz{

/**************************************************************************
 class Factory_Stage1;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Stage1{
public:
/**************************************************************************
 Factory_Stage1(
	FactoryPacket* fpac //パケットデータ
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Stage1( FactoryPacket* fpac );
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Stage1();
};
}
//end of namespace wiz.
