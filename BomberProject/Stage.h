////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ステージ
//					：ステージはシーンから呼ばれます
//					▼
//	namespace wiz;
//		class StageLoader ;
//		class Stage ;
//		class MenuStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassMenuItems.h"
#include "CSV.h"

namespace wiz{

// 仮宣言	
//class wiz::menuobject::Button;
using namespace menuobject ;
//class Button2;


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************//
// class Stage;
//
// 担当  : 鴫原 徹
// 用途  : ゲームをステージ単位で管理するクラス
//**************************************************************************//
class Stage{
protected:
	friend struct FactoryPacket		;
	friend struct BassPacket		;
	friend struct wiz::structs::UpdatePacket		;
	friend struct RenderPacket		;
	friend struct DrawPacket		;
	friend class  Button			;
	//	: メニュー等の画面へのポインタをとっておく
	Stage*						m_pParStage		;	//	: 親ステージ
	Stage*						m_pChildStage	;	//	: 子ステージ
	system::Sound*				m_pMySound		;
	system::Sound*				m_pSound		;
	bool						m_IsDialog		;	//	: ダイアログステージかどうか
	bool						m_bUpdate		;	//	: このフラグをtrueにするとステージのupdateが止まります
    vector<Object*>				m_Vec			;	//	: 配置オブジェクトのポインタのベクトル
	TextureManager				m_TexMgr		;	//	: テクスチャのポインタのベクトル
	vector<Button*>				m_ButtonVec		;	//	: ボタンオブジェクトのみの配列（カメラなどは入れない）
	vector<Button*>::size_type	m_SelectIndex	;
	bool m_SelectLock;
	bool m_IsAnimetion;
	/**************************************************************************
	 void AddButton(
	 Button* pButton	//ボタンのポインタ
	 );
	 用途: メニューにボタンを追加する。これ以外にm_Vecにも必ず入れる
	 戻り値: なし
	***************************************************************************/
	void AddButton(Object* pButton);
	/**************************************************************************
	 void AddButton(
	 Button* pButton	//ボタンのポインタ
	 );
	 用途: メニューにボタンを追加する。これ以外にm_Vecにも必ず入れる
	 戻り値: なし
	***************************************************************************/
	void EraseButton(vector<Object*>::iterator ObjIt);
#if defined(ON_DEBUGGINGPROCESS)
	bool m_bSlow;
#endif
protected:
	/////////////////// ////////////////////
	//// 関数名     ：void Stage::Clear()
	//// カテゴリ   ：関数
	//// 用途       ：内包データを破棄する
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：デストラクタで絶対呼ばれます
	////            ：
	////
	virtual void Clear();
public:
	/////////////////// ////////////////////
	//// 関数名     ：Stage::Stage(Stage* Par = NULL)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：デフォルトの構築処理
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	Stage(Stage* Par = NULL);

	/////////////////// ////////////////////
	//// 関数名     ：virtual Stage::~Stage()
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：デフォルトの構築処理
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
	virtual ~Stage();

	/////////////////// ////////////////////
	//// 関数名     ：const Stage* Stage::getNextStage() 
	//// カテゴリ   ：ゲッター
	//// 用途       ：次のステージへのポインタを返す
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：
	//// 備考       ：
	////            ：
	////
	const Stage* getNextStage() {
		return m_pParStage;
	}
	/////////////////// ////////////////////
	//// 関数名     ：const Stage* Stage::getPar() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：親ステージのポインタを返す
	//// 引数       ：なし
	//// 戻値       ：親ステージへのポインタ
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
	const Stage* getPar() const{
		return m_pParStage;
	}
	/////////////////// ////////////////////
	//// 関数名     ：const Stage* Stage::geChild() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：子ステージのポインタを返す
	//// 引数       ：なし
	//// 戻値       ：ステージへのポインタ
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
	const Stage* geChild() const{
		return m_pChildStage;
	}
	/////////////////// ////////////////////
	//// 関数名     ：Stage* Stage::getLastStage()
	//// カテゴリ   ：ゲッター
	//// 用途       ：一番最後尾の子ステージを得る
	//// 引数       ：なし
	//// 戻値       ：一番最後尾の子ステージのポインタ
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：
	////            ：
	////
	Stage* getLastStage(){
		if(m_pChildStage){
			return m_pChildStage->getLastStage();
		}
		else{
			return this;
		}
	}
	/////////////////// ////////////////////
	//// 関数名     ：Stage* Stage::getActiveStage()
	//// カテゴリ   ：ゲッター
	//// 用途       ：今、アクティブなステージを得る
	//// 引数       ：なし
	//// 戻値       ：アクティブなステージのポインタ
	//// 担当者     ：(山ノ井先生のひな形より)
	//// 備考       ：＊最後尾の子がダイアログタイプだった場合
	////            ：  そのダイアログを保持するステージを得る
	////
	Stage* getActiveStage(){
		Stage* ret = getLastStage();
		while(	ret && ret->m_IsDialog){
			if( ret->m_pParStage )
				ret = ret->m_pParStage;
			else
				return ret;
		}
		return ret;
	}
	/////////////////// ////////////////////
	//// 用途       ：virtual void ButtonUpdateUpdate( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：ボタンを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	virtual void ButtonUpdate(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：ステージを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	virtual void Update(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// 関数名     ：void Render(RenderPacket& i_RenderPacket);
	//// カテゴリ   ：関数
	//// 用途       ：ターゲットレンダリング
	//// 引数       ：  RenderPacket& i_RenderPacket        // レンダー処理に流すデータの集合体
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：画面以外のバッファーに描画する
	////            ：
	////
    virtual void Render(RenderPacket& i_RenderPacket);
	
	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：シーンを描画
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹(山ノ井先生のひな形より)
	//// 備考       ：
    virtual void Draw(DrawPacket& i_DrawPacket) ;
	/////////////////// ////////////////////
	//// 用途       ：
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	void TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget);
	/////////////////// ////////////////////
	//// 用途       ：
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	void DefaultRender();

	/////////////////// ////////////////////
	//// 関数名     ：void CommandTranslator(DrawPacket& i_DrawPacket);
	//// カテゴリ   ：関数
	//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void CommandTranslator(DrawPacket& i_DrawPacket);

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class MenuStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class MenuStage : public Stage{
protected:
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~MenuStage();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState	//コントローラーのステータス
	Command& i_DrawPacket.pCommand		//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,  //コントローラーのステータス
	Command& i_DrawPacket.pCommand		//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: ステージを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class MenuStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class MenuStage2 : public Stage{
protected:
	vector<Button*> m_Button2Vec;
	//ボタンオブジェクトのみの配列（カメラなどは入れない）
	vector<Button*>::size_type m_SelectIndex;
	bool m_SelectLock;
	bool m_IsAnimetion;
/**************************************************************************
 void AddButton2(
 Button2* pButton2	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。これ以外にm_Vecにも必ず入れる
 戻り値: なし
***************************************************************************/
	void AddButton2(Object* pButton2);
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	MenuStage2(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~MenuStage2();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand		//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,	//コントローラーのステータス
	Command& i_DrawPacket.pCommand		//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: ステージを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}
//end of namespace wiz.
