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
	LPDIRECT3D9				m_pD3D			;	// IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	m_D3DPP			;	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	DebugWindow(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd);
public:
	static void init(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd){
		#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
			if( !m_pMyInstance )m_pMyInstance = new DebugWindow(hInstance,i_hParentWindow,nShowCmd);
		#endif
	};
	static DebugWindow* getInstance(){
		#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
			if( m_pMyInstance ) return m_pMyInstance ;
			else
		#endif
		return NULL ;
	}
};

}//end of namespace Debugger.
#endif