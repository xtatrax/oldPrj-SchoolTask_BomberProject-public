////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：DebugWindowMain.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバッグ情報表示用ウインドウ
//					▼
//	namespace TLIB;
//

#ifndef DEBUGGER_DEBUGWINDOWMAIN
#define DEBUGGER_DEBUGWINDOWMAIN


namespace Debugger{

static const wchar_t* RCTEXT_DEBUGWINDOWTITLE		= L"GameDebugger" ;
static const wchar_t* RCTEXT_DEBUGWINDOWCLASSNAME	= L"GameDebugWindow" ;


struct START_PACKET{
	HINSTANCE	hInstance;
	HWND		i_hParentWindow;
	int			nShowCmd ;
};
class DebugWindow{
	static DebugWindow*	m_pMyInstance	;
	static HANDLE		m_hMyThread		;
	const wchar_t*		m_pClassName	;
	const wchar_t*		m_pWndTitle		;
	HWND				m_hWnd			;
	LPDIRECT3D9				m_pD3D			;	// IDirect3D9インターフェイスへのポインタ
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// IDirect3DDevice9インターフェイスへのポインタ
	D3DPRESENT_PARAMETERS	m_D3DPP			;	// デバイスのプレゼンテーションパラメータ
	DebugWindow(START_PACKET pac);

public:
	static void init(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd){
		#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
			START_PACKET pac ;
			pac.hInstance			= hInstance ;
			pac.i_hParentWindow		= i_hParentWindow ;
			pac.nShowCmd			= nShowCmd ;

			if( !m_pMyInstance ) StartThread(pac);
		#endif
	};
	static DebugWindow* getInstance(){
		#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
			if( m_pMyInstance ) return m_pMyInstance ;
			else
		#endif
		return NULL ;
	}
/////////////////// ////////////////////
//// 関数名     ：void StartUpdateThread()
//// カテゴリ   ：メンバ関数
//// 用途       ：シーンのアップデート用スレッドを開始する
//// 引数       ：無し
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	static void StartThread(START_PACKET pac);

/////////////////// ////////////////////
//// 関数名     ：static void __cdecl updateThreadLauncher(void* args)
//// カテゴリ   ：静的メンバ関数
//// 用途       ：新しいスレッドを開始するための串
//// 引数       ：void* args	//	: 引数リスト
//// 戻値       ：無し
//// 備考       ：
////            ：
////
	static unsigned __stdcall ThreadLauncher(void* args);

};

}//end of namespace Debugger.
#endif