////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Clear.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Clear ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{
/**************************************************************************
class Factory_Clear;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Clear{
public:
/**************************************************************************
 Factory_Clear(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Clear(FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Clear();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
