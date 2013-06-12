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



class DebugWindow{
	static DebugWindow*	m_pMyInstance	;
	const wchar_t*		m_pClassName	;
	const wchar_t*		m_pWndTitle		;
	HWND				m_hWnd			;
	DebugWindow(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd);
public:
	static void init(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd){
		if( !m_pMyInstance )m_pMyInstance = new DebugWindow(hInstance,i_hParentWindow,nShowCmd);
	};
	static DebugWindow* getInstance(){
		if( m_pMyInstance ) return m_pMyInstance ;
		else return NULL ;
	}
};

}//end of namespace Debugger.
#endif