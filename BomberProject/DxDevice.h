////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：DxDevice.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバイスを管理します
//					：ゲームループは各ThreadRun関数の中に定義されています
//					：stdafx.h 内に ON_DEBUGGINGPROCESS をデファイン定義することで
//					：マルチスレッドを実装できます( 現在有効にするとプレイヤーの床
//					：との衝突判定でアクセス違反が発生します )
//					：★WinMain関数から呼ばれます
//					▼
//	namespace wiz;
//		class DxDevice;
//
#pragma once
 
#include "StdAfx.h"
#include "Object.h"
#include "Controller/Controller.h"
using namespace TLIB;
namespace wiz{
extern bool GameQuitFlag ;
namespace system{
/**************************************************************************
 依存するクラス
****************************************************************************/
class Scene;

/**************************************************************************
 class DxDevice;
 用途: DirectXデバイスクラス
****************************************************************************/
class DxDevice {
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//	: 非公開変数+α
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
private:
	LPDIRECT3D9				m_pD3D			;	// IDirect3D9インターフェイスへのポインタ
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// IDirect3DDevice9インターフェイスへのポインタ
	D3DPRESENT_PARAMETERS	m_D3DPP			;	// デバイスのプレゼンテーションパラメータ
	CONTROLLERS				m_Controller	;	// コントローラのポインタ
	Command					m_Com			;	// コマンド
	UpdatePacket			m_UpdatePacket	;	// アップデートスレッドの処理に流すデータ群
	RenderPacket			m_RenderPacket	;	// レンダースレッドの処理に流すデータ群
	DrawPacket				m_DrawPacket	;	// ドロースレッドの処理に流すデータ群
	Scene*					pScene			;	// 
	static bool				m_bDestroy		;	//
	static bool				m_bOnPlaySound	;	//
	static Rect				m_WindowRect	;	// ゲームの描画範囲の大きさを表す矩形
	static D3DXVECTOR2		m_v2AspectRate	;		// 基準解像度と現在の解像度の比率
	static HANDLE			m_hUpdateThread		;	// アップデート用スレッドのハンドル
	static HANDLE			m_hLoadingThread	;	// ロード画面用スレッドのハンドル
	enum ProgramState{
		PROGRAM_RUNNUNG,
		PROGRAM_ENDTHREAD,
		PROGRAM_END,
	}m_PrgState;

public:

	static HWND				m_hWnd				;	// メインウインドウのハンドル

private:
/////////////////// ////////////////////
//// 関数名     ：void initDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
//// カテゴリ   ：イニシャライザ
//// 用途       ：プログラムで使うデバイスを初期化
//// 引数       ：  HWND hWnd,          //ウインドウのハンドル
////            ：  bool isFullScreen,  //フルスクリーンかどうか
////            ：  int Width,          //領域の幅
////            ：  int Height          //領域の高さ
//// 戻値       ：無し
//// 備考       ：
////            ：
////
    void initDevice(bool isFullScreen,int Width,int Height);




/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//	: 公開関数
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
public:
/**************************************************************************
 void Clear();
 用途: オブジェクトのクリア
 戻り値: なし
***************************************************************************/
    void Clear();
/**************************************************************************
 DxDevice(
    HWND hWnd,          //ウインドウのハンドル
    bool isFullScreen,  //フルスクリーンかどうか
    int Width,          //領域の幅
    int Height          //領域の高さ
);
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    DxDevice(bool isFullScreen,int Width,int Height);
/**************************************************************************
 ~DxDevice();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~DxDevice();
/**************************************************************************
 LPDIRECT3DDEVICE9 getDevice();
 用途: デバイスの取得
 戻り値: IDirect3DDevice9インターフェイスへのポインタ。失敗したら0
***************************************************************************/
    LPDIRECT3DDEVICE9 getDevice();
/////////////////// ////////////////////
//// 関数名     ：void End()
//// カテゴリ   ：メンバ関数
//// 用途       ：ゲームの終了を宣言
//// 引数       ：無し
//// 戻値       ：int
//// 備考       ：スレッドの終了準備とか
////            ：
////
	void End();
/////////////////// ////////////////////
//// 関数名     ：int MainThreadRun()
//// カテゴリ   ：メンバ関数
//// 用途       ：メインスレッドのープ
//// 引数       ：無し
//// 戻値       ：int
//// 備考       ：
////            ：
////
	int MainThreadRun();
	static Rect getClientRect(){return m_WindowRect;}
	static void setClientRect(Rect i_Rect){
		m_WindowRect = i_Rect;
		m_v2AspectRate   = D3DXVECTOR2( i_Rect.right / BASE_CLIENT_WIDTH , i_Rect.bottom / BASE_CLIENT_HEIGHT );
	}
	static D3DXVECTOR2 getAspectRate(){return m_v2AspectRate;}
/////////////////// ////////////////////
//// 関数名     ：static HWND getGameWindowHandle()
//// カテゴリ   ：静的メンバ関数
//// 用途       ：ゲーム画面を描画してるウインドウのハンドルを返す
//// 引数       ：無し
//// 戻値       ：
//// 備考       ：
////            ：
////
	static HWND getGameWindowHandle(){return m_hWnd;};
/////////////////// ////////////////////
//// 関数名     ：static HANDLE getUpdateThreadHandle()
//// カテゴリ   ：静的メンバ関数
//// 用途       ：アップデート用スレッドのハンドルを返す
//// 引数       ：無し
//// 戻値       ：
//// 備考       ：シングルスレッドモードの場合はNULLを返す
////            ：
////
	static HANDLE getUpdateThreadHandle(){return m_hUpdateThread;};
/////////////////// ////////////////////
//// 関数名     ：static HANDLE getLoadingThreadHandle()
//// カテゴリ   ：静的メンバ関数
//// 用途       ：ロード画面用スレッドのハンドルを返す
//// 引数       ：無し
//// 戻値       ：
//// 備考       ：シングルスレッドモードの場合はNULLを返す
////            ：
////
	static HANDLE getLoadingThreadHandle(){return m_hLoadingThread;};

/////////////////// ////////////////////
//// 関数名     ：static bool getIsPlaySound() ;
//// カテゴリ   ：静的メンバ関数
//// 用途       ：音声を再生させるかどうかを返す
//// 引数       ：なしし
//// 戻値       ： true  : 再生
////            ： false : 停止
//// 備考       ：
////            ：
////
	static bool getIsPlaySound(){return m_bOnPlaySound;};

/////////////////// ////////////////////
//// 関数名     ：static bool getSwitchingSoundOnOff()
//// カテゴリ   ：静的メンバ関数
//// 用途       ：音声のONとOFFを切り替える
//// 引数       ：なし
//// 戻値       ：なし
//// 備考       ：
////            ：
////
	static void SwitchingSoundOnOff(){ m_bOnPlaySound ? m_bOnPlaySound = false : m_bOnPlaySound = true ; } ;

/////////////////// ////////////////////
//// 関数名     ：void Destroy()
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	static void Destroy(){	m_bDestroy = true ; };

/////////////////// ////////////////////
//// 関数名     ：void EndUpdateThread()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドを終了する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	// static void Destroy(){	m_bDestroy = true ; };

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//	: 非公開関数
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
private:
/////////////////// ////////////////////
//// 関数名     ：void UpdateThreadRun()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドのループ
//// 引数       ：無し
//// 戻値       ：int
//// 備考       ：
////            ：
////
	int UpdateThreadRun();

/////////////////// ////////////////////
//// 関数名     ：void UpdateScene()
//// カテゴリ   ：メンバ関数
//// 用途       ：オブジェクト関連の演算
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	void UpdateScene();

/////////////////// ////////////////////
//// 関数名     ：static void __cdecl updateThreadLauncher(void* args)
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンを描画する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	void RenderScene();

/////////////////// ////////////////////
//// 関数名     ：void StartUpdateThread()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドを開始する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	void StartUpdateThread();

/////////////////// ////////////////////
//// 関数名     ：static void __cdecl updateThreadLauncher(void* args)
//// カテゴリ   ：静的メンバ関数
//// 用途       ：新しいスレッドを開始するための串
//// 引数       ：void* args	//	: 引数リスト
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	static unsigned __stdcall updateThreadLauncher(void* args);

/////////////////// ////////////////////
//// 関数名     ：void EndUpdateThread()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドを終了する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	void EndUpdateThread();
/////////////////// ////////////////////
//// 関数名     ：void EndUpdateThread()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドを終了する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
};
}
//end of namespace system.
using namespace system;
}
//end of namespace wiz.

