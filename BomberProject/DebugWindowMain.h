////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDebugWindowMain.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O���\���p�E�C���h�E
//					��
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