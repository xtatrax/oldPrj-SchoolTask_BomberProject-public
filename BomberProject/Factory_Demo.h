////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：タイトルファクトリー
//					▼
//	namespace wiz;
//		class Load ;
//		class Factory_Demo ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Demo.h"
#include "Factory_Sound.h"


namespace wiz{
namespace bomberobject{

/**************************************************************************
class Factory_Demo;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Demo{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Demo(FactoryPacket* fpac,Command* Com);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Demo();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
