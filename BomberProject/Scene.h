////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Scene.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：シーン
//					：シーンはデバイスから呼ばれます
//					▼
//	namespace wiz;
//		class Scene ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Stage.h"

namespace wiz{
namespace system{
//**************************************************************************
// class Scene;
//
// 担当者  : 鴫原 徹(山ノ井先生のひな形より)
// 用途    : シーンを管理するクラス
//         : 
//**************************************************************************/
class Scene
{
	//////////
	//	: ロード画面専用
	//LPDIRECT3DDEVICE9 m_pD3DDevice		;
	Command	m_LoadCommand				;
	static HANDLE	m_hLoadingThread	;	// ロード画面用スレッドのハンドル
	bool	m_bLoadingComplete			;
	Stage*	m_pStgBuf					;
	//
	//////////

	float	m_fStageNotFoundMessageTime		;

	Stage*	m_pRootStage					;
	bool	m_bUpdateThreadSuspendRequest	;	//	: スレッド停止要求フラグ(メインスレッド発行->アップデートスレッド解釈)
	bool	m_bUpdateThreadSuspend			;	//	: スレッド停止完了フラグ(アップデートスレッド発行->メインスレッド解釈)
	bool	m_bUpdateThreadResumeRequest	;	//	: スレッド再開要求フラグ(シーン発行->デバイス解釈)


//	: 非公開関数
private:

	/////////////////// ////////////////////
	//// 関数名     ：void Clear()
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトのクリア
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    void Clear();
	
	/////////////////// ////////////////////
	//// 関数名     ：void setStages()
	//// カテゴリ   ：関数
	//// 用途       ：ステージリストを構築
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    void setStages();
public:
	/////////////////// ////////////////////
	//// 関数名     ：Scene(LPDIRECT3DDEVICE9 pD3DDevice)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：シーンを生成
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：失敗したら例外をthrow
	////            ：
	////
	Scene(LPDIRECT3DDEVICE9 pD3DDevice,Command* pCommand );
	/////////////////// ////////////////////
	//// 関数名     ：~Scene()
	//// カテゴリ   ：デストラクタ
	//// 用途       ：シーンを破棄
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    virtual ~Scene();
	/////////////////// ////////////////////
	//// 関数名     ：void Update(UpdatePacket& i_UpdatePacket)
	//// カテゴリ   ：関数
	//// 用途       ：シーンを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket        // アップデート処理に流すデータの集合体
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    void Update(UpdatePacket& i_UpdatePacket);
	/////////////////// ////////////////////
	//// 関数名     ：void Render(RenderPacket& i_RenderPacket);
	//// カテゴリ   ：関数
	//// 用途       ：ターゲットレンダリング
	//// 引数       ：  RenderPacket& i_RenderPacket        // レンダー処理に流すデータの集合体
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：画面以外のバッファーに描画する
	////            ：
	////
    void Render(RenderPacket& i_RenderPacket);
	/////////////////// ////////////////////
	//// 関数名     ：void Draw(DrawPacket& i_DrawPacket);
	//// カテゴリ   ：関数
	//// 用途       ：シーンを描画
	//// 引数       ：  DrawPacket& i_DrawPacket            // ドロー処理に流すデータの集合体
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：画面以外のバッファーに描画する
	////            ：
	////
	void Draw(DrawPacket& i_DrawPacket);
	/////////////////// ////////////////////
	//// 関数名     ：void CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
	//// カテゴリ   ：関数
	//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  Command& i_DrawPacket.pCommand      // コマンド
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void CommandTranslator(DrawPacket& i_DrawPacket);
	/////////////////// ////////////////////
	//// 関数名     ：unsigned __stdcall LoadingThreadLauncher(void *args)
	//// カテゴリ   ：関数
	//// 用途       ：ロード専用のスレッドを起動します
	//// 引数       ：void *args //
	//// 戻値       ：0
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static unsigned __stdcall LoadingThread(void* args);
	//static void LoadingThread(void* args);
	/////////////////// ////////////////////
	//// 関数名     ：void CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
	//// カテゴリ   ：関数
	//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  Command& i_DrawPacket.pCommand						// コマンド
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand);
	/////////////////// ////////////////////
	//// 関数名     ：void SafeDeleteStage()
	//// カテゴリ   ：関数
	//// 用途       ：ステージを安全に削除する
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void SafeDeleteStage(Stage* &pStage);

//////////
//  : ゲッター
public:
	/////////////////// ////////////////////
	//// 関数名     ：bool getUpdateThreadSuspendRequest()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの一時停止要求の確認
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：メインスレッド->アップデートスレッド
	////            ：
	////
	bool getUpdateThreadSuspendRequest(){
		return m_bUpdateThreadSuspendRequest;
	};
	/////////////////// ////////////////////
	//// 関数名     ：bool getUpdateThreadSuspend()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの一時停止完了の確認
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：アップデートスレッド->メインスレッド
	////            ：
	////
	bool getUpdateThreadSuspend(){
		return m_bUpdateThreadSuspend;
	};
	/////////////////// ////////////////////
	//// 関数名     ：bool getUpdateThreadSuspend()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの再開要求の確認
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：シーン->デバイス
	////            ：
	////
	bool getUpdateThreadResumeRequest(){
		return m_bUpdateThreadResumeRequest;
	};


//////////
//  : セッター
public:
	/////////////////// ////////////////////
	//// 関数名     ：void setUpdateThreadSuspendRequest()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの一時停止要求
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：メインスレッド->アップデートスレッド
	////            ：
	////
	void setUpdateThreadSuspendRequest(){
		m_bUpdateThreadSuspendRequest = true ;
	};
	/////////////////// ////////////////////
	//// 関数名     ：void setUpdateThreadSuspend()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの一時停止完了確認
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：アップデートスレッド->メインスレッド
	////            ：
	////
	void setUpdateThreadSuspend(){
		m_bUpdateThreadSuspend        = true ;
	};
	/////////////////// ////////////////////
	//// 関数名     ：void setUpdateThreadSuspend()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの再開要求
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：アップデートスレッド->全体
	////            ：
	////
	void setUpdateThreadResumeRequest(){
		m_bUpdateThreadResumeRequest = true ;
	};

	/////////////////// ////////////////////
	//// 関数名     ：void setUpdateThreadSuspend()
	//// カテゴリ   ：ゲッター
	//// 用途       ：アップデートスレッドの再開通知
	//// 引数       ：無し
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：アップデートスレッド->全体
	////            ：
	////
	void setUpdateThreadResume(){
		m_bUpdateThreadSuspendRequest = false ;	//	: スレッド停止要求フラグ(メインスレッド->アップデートスレッド)
		m_bUpdateThreadSuspend        = false ;	//	: スレッド停止完了フラグ(アップデートスレッド->メインスレッド)
		m_bUpdateThreadResumeRequest  = false ;	//	: スレッド再開要求フラグ(シーン->デバイス)
	};

};
}
//end of namespace system.
using namespace system ;
}
//end of namespace wiz.

