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
	LPDIRECT3D9				m_pD3D			;	// IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	m_D3DPP			;	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
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
//// �֐���     �Fvoid StartUpdateThread()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h���J�n����
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	static void StartThread(START_PACKET pac);

/////////////////// ////////////////////
//// �֐���     �Fstatic void __cdecl updateThreadLauncher(void* args)
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F�V�����X���b�h���J�n���邽�߂̋�
//// ����       �Fvoid* args	//	: �������X�g
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	static unsigned __stdcall ThreadLauncher(void* args);

};

}//end of namespace Debugger.
#endif