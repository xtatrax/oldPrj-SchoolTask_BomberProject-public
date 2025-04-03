////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage_Test.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：テスト用のステージ
//					：★Scene.cpp Scene::CommandTranslator 関数で実体化されます
//					：★Scene.cpp Scene::Update / AnotherTargetRender / Draw 関数から呼ばれます
//					▼
//	namespace wiz;
//	;
//
#include "Stage.h"
namespace wiz{

/**************************************************************************
 class DebugStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class DebugStage_TATRA : public Stage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	DebugStage_TATRA(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};

/**************************************************************************
 class DebugStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class DebugStage_Loader : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	DebugStage_Loader(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};

};