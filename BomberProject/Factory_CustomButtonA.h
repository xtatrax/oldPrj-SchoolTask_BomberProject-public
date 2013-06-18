////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CustomButtonA.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ButtonSpriteのCustom版
//					：タイトルとかで使用
//					▼
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#pragma once

#include "StdAfx.h"


namespace wiz{
namespace bomberobject{

/**************************************************************************
 class Factory_CustomButtonA;
 用途: メイン工場クラス
****************************************************************************/
class Factory_CustomButtonA{
public:
	/**************************************************************************
	 Factory_CustomButtonA(
		FactoryPacket* fpac //パケットデータ
	);
	 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
	 戻り値: なし
	***************************************************************************/
	Factory_CustomButtonA( FactoryPacket* fpac );
	/**************************************************************************
	 ~MyFactory();
	 用途: デストラクタ
	 戻り値: なし
	***************************************************************************/
	~Factory_CustomButtonA();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
