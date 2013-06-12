////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FWinMain.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�G���g���[�|�C���g
//					��
//	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"

int nDefaultShowCmd ;
HINSTANCE hInstance ;
/**************************************************************************
LRESULT CALLBACK WindowProc(
HWND hWnd,      //�E�B���h�E�n���h��
UINT msg,       //���b�Z�[�W
WPARAM wParam,  //���b�Z�[�W�̍ŏ��̃p�����[�^
LPARAM lParam   //���b�Z�[�W��2�Ԗڂ̃p�����[�^
)
�p�r: �E�C���h�E�v���V�[�W��
�߂�l: ���b�Z�[�W��������
***************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE:
			DragAcceptFiles(hWnd,TRUE); // D&D ��������
			Debugger::DebugWindow::init(hInstance,hWnd,nDefaultShowCmd);
			return 0;
        case WM_CLOSE:                // �E�C���h�E���j������悤�Ƃ��Ă���
			wiz::DxDevice::Destroy();
            return 0;
        break;
		case WM_DESTROY:
			
			break ;
        case WM_KEYDOWN: 
			// �L�[�������ꂽ
			if (wParam == VK_ESCAPE) {  // �����ꂽ�̂�ESC�L�[��
				wiz::DxDevice::Destroy();  // �E�C���h�E��j������悤�v������
			}
			if (wParam == (VK_MENU | VK_RETURN)) { 
            }
            return 0;
        break;
        case WM_ACTIVATEAPP:
            if( wParam == TRUE )   XInputEnable( true );
            else                   XInputEnable( false );
            return 0;
        case WM_SIZING:
			wiz::__GetClientSize(*((wiz::Rect*)lParam));
			wiz::DxDevice::setClientRect(*((wiz::Rect*)lParam));
            return 0;
		case WM_DROPFILES: // �t�@�C�����h���b�v���ꂽ
			TCHAR szDropFile[MAX_PATH + 1];
			DragQueryFile((HDROP)wParam,0,szDropFile,MAX_PATH);

			// �\���̂̃n���h���Ŏg�������������������
			DragFinish((HDROP)wParam);
			return 0;
        default:
        break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
/**************************************************************************
 �֐���:int WINAPI WinMain(
        HINSTANCE hInstance,            //�C���X�^���X�̃n���h��
        HINSTANCE hPrevInstance,        //�ȑO�̃C���X�^���X
        LPSTR lpCmdLine,                //�R�}���h���C��
        int nShowCmd                    //�N�����̏��
        );
 �p�r: �G���g���|�C���g�B
 �߂�l: �I���R�[�h
****************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE 
    hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	nDefaultShowCmd = nShowCmd ;
	hInstance = hInstance ;
	setlocale( LC_CTYPE, "jpn" );
	time_t timer;
	struct tm local ;

    /* ���ݎ������擾 */
    timer = time(NULL);

    localtime_s(&local ,&timer); /* �n�����ɕϊ� */

    /* �n���� �ϊ���\�� */
    printf("�n����: ");
    printf("%4d/", local.tm_year + 1900);
    printf("%2d/", local.tm_mon + 1);
    printf("%2d ", local.tm_mday);
    printf("%2d:", local.tm_hour);
    printf("%2d:", local.tm_min);
    printf("%2d", local.tm_sec);
    printf(" %d\n", local.tm_isdst);

	Debugger::DBGWRITINGLOGTEXT::Init();
	Debugger::DBGWRITINGLOGTEXT::addStr(L" �ŏI�N�� \n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L" ���[�J������ %4d/%2d/%2d %2d:%2d:%2d %d \n",
		local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
		local.tm_min, local.tm_sec, local.tm_isdst);
    //�萔
    const wchar_t* pClassName = DEFAULT_WINDOW_CLASS_NAME;
    const wchar_t* pWndTitle  = DEFAULT_WINDOW_TITLE;
    //�E�C���h�E�̕��ƍ���
    int iClientWidth  = (int)STANDARD_WINDOW_WIDTH;
    int iClientHeight = (int)STANDARD_WINDOW_HEIGHT;
    // �t���X�N���[���ɂ��邩�ǂ����̔���
    // �R�}���h���C����/f��/F���ݒ肳��Ă�����t���X�N���[���ɂ���
#ifdef CF_FULLSCREEN
    bool isFullScreen = true;
#else
    bool isFullScreen = false;
#endif
    for(int i = 0; i < nShowCmd; i++) {
        if(_stricmp((char*)&lpCmdLine[i], "/f") == 0) { // �R�}���h���C����/f�𔭌�
            isFullScreen = true;     // �t���O��true�ɐݒ�
            break;
        }
    }
	//WNDCLASSEX�\���̂̏�����
    WNDCLASSEX wcex;
    wcex.cbSize         = sizeof(WNDCLASSEX);       //���̍\���̂̃T�C�Y
    wcex.style          = 0;                        //�����I��redraw�������Ȃ�
    wcex.lpfnWndProc    = WindowProc;               //�E�C���h�E�v���V�[�W���i�R�[���o�b�N�֐��j�̎w��
    wcex.cbClsExtra     = 0;                        //���0
    wcex.cbWndExtra     = 0;                        //���0
    wcex.hInstance      = hInstance;                //�A�v���P�[�V�����̃C���X�^���X���w��
    wcex.hIcon          = NULL;                     //�A�C�R���̎w��i�����ł�NULL�j
    wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);    //�ʏ�̖��J�[�\��
    wcex.hbrBackground  = NULL;                      //�w�i�Ȃ�
    wcex.lpszMenuName   = NULL;                     //���j���[�Ȃ�
    wcex.lpszClassName  = pClassName;               //�N���X���̎w��
    wcex.hIconSm        = NULL;                     //�������A�C�R���Ȃ�
    //�E�C���h�E�N���X�̓o�^
    if (!::RegisterClassEx(&wcex))
    {
        //���s����
        ::MessageBox(NULL,L"�E�C���h�E�N���X�o�^�Ɏ��s���܂���",L"�G���[",MB_OK);
        return 1;   //�G���[�I��
    }
    // �E�B���h�E�̍쐬
    if(isFullScreen) { // �t���X�N���[��
		//DEVMODE    devMode;
		//ShowCursor(DRAW_MOUSE);
        // ��ʑS�̂̕��ƍ������擾
        //iClientWidth = ::GetSystemMetrics(SM_CXSCREEN);
        //iClientHeight = ::GetSystemMetrics(SM_CYSCREEN);
        wiz::DxDevice::m_hWnd = ::CreateWindowEx( 
            WS_EX_ACCEPTFILES,  //�I�v�V�����̃E�B���h�E�X�^�C��
            pClassName,         // �o�^����Ă���N���X��
            pWndTitle,          // �E�C���h�E��
            WS_POPUP,           // �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
            0,                  // �E�C���h�E�̉������̈ʒu
            0,                  // �E�C���h�E�̏c�����̈ʒu
            (int)BASE_CLIENT_WIDTH,       // �t���X�N���[���E�C���h�E�̕�
            (int)BASE_CLIENT_HEIGHT,      // �t���X�N���[���E�C���h�E�̍���
            NULL,               // �e�E�C���h�E�̃n���h���i�Ȃ��j
            NULL,               // ���j���[��q�E�C���h�E�̃n���h��
            hInstance,          // �A�v���P�[�V�����C���X�^���X�̃n���h��
            NULL                // �E�C���h�E�̍쐬�f�[�^
        );
        if (!wiz::DxDevice::m_hWnd){
            //���s����
            ::MessageBox(0,L"�E�C���h�E�쐬�Ɏ��s���܂���",L"�G���[",MB_OK);
            return 1;   //�G���[�I��
        }
		//devMode.dmSize       = sizeof(DEVMODE);
		//devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		//devMode.dmPelsWidth  = (DWORD)BASE_CLIENT_WIDTH;
		//devMode.dmPelsHeight = (DWORD)BASE_CLIENT_HEIGHT;

		//ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);


    }
    else {
        //�E�C���h�E�̍쐬
		wiz::DxDevice::m_hWnd = ::CreateWindowEx(
            0,                              //�I�v�V�����̃E�B���h�E�X�^�C��
            pClassName,                     //�E�C���h�E�N���X��
            pWndTitle,                      //�E�C���h�E�̃^�C�g��
            WS_OVERLAPPEDWINDOW,            //�ړ��o�[�����ʏ�̃E�C���h�E
            CW_USEDEFAULT, CW_USEDEFAULT,   //�ʒu��Windows�ɔC����
            iClientWidth,                    //�E�C���h�E���i�b��j
            iClientHeight,                   //�E�C���h�E�����i�b��j
            NULL,                            //�e�E�C���h�E�i�g�b�v���x���Ȃ̂ŁA�Ȃ��j
            NULL,                           //���j���[�Ȃ�
            hInstance,                      //���̃C���X�^���X
            NULL                            //�g�p���Ȃ�
        );
        if (!wiz::DxDevice::m_hWnd){
            //���s����
            ::MessageBox(0,L"�E�C���h�E�쐬�Ɏ��s���܂���",L"�G���[",MB_OK);
            return 1;   //�G���[�I��
        }
        // �E�B���h�E�T�C�Y���Đݒ肷��
        RECT rect;
        int w_width,w_height,c_width,c_height;
        // �E�C���h�E�S�̂̑傫�����v�Z
        ::GetWindowRect(wiz::DxDevice::m_hWnd,&rect);       // �E�C���h�E�S�̂̃T�C�Y�擾
        w_width = rect.right - rect.left;   // �E�C���h�E�S�̂̕��̉������v�Z
        w_height = rect.bottom - rect.top;  // �E�C���h�E�S�̂̕��̏c�����v�Z
        // �N���C�A���g�̈�̑傫�����v�Z
        ::GetClientRect(wiz::DxDevice::m_hWnd,&rect);       // �N���C�A���g�����̃T�C�Y�̎擾
        c_width = rect.right - rect.left;   // �N���C�A���g�̈�O�̉������v�Z
        c_height = rect.bottom - rect.top;  // �N���C�A���g�̈�O�̏c�����v�Z
        // �E�B���h�E�T�C�Y�̍Čv�Z
        w_width = iClientWidth + (w_width - c_width);     // �K�v�ȃE�C���h�E�̕�
        w_height = iClientHeight + (w_height - c_height); // �K�v�ȃE�C���h�E�̍���
        // �E�C���h�E�T�C�Y�̍Đݒ�
        ::SetWindowPos(wiz::DxDevice::m_hWnd,HWND_TOP,0,0,w_width,w_height,SWP_NOMOVE);
    }
	ShowCursor(DRAW_MOUSE);
	wiz::__GetClientSize(wiz::Rect(0,0,iClientWidth,iClientHeight));
	wiz::DxDevice::setClientRect(wiz::Rect(0,0,iClientWidth,iClientHeight));

    //�E�C���h�E�̕\��
    ::ShowWindow(
        wiz::DxDevice::m_hWnd,       //�擾�����E�C���h�E�̃n���h��
        nShowCmd    //WinMain�ɓn���ꂽ�p�����[�^
    );
    // WM_PAINT���Ă΂�Ȃ��悤�ɂ���
    ::ValidateRect(wiz::DxDevice::m_hWnd, 0);
    //��O�����J�n
    try{
		/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		// 
        // DirectX�f�o�C�X�I�u�W�F�N�g�̏�����
        wiz::DxDevice* device = new wiz::DxDevice(isFullScreen,iClientWidth,iClientHeight);
		int ret =  (int) device->MainThreadRun();
		SafeDelete( device );
		::PostQuitMessage(0);
		ShowCursor(true);
		//wiz::TextureManager::Release();
#if defined( CF_MEMORYMANAGER_ENABLE )
		TMemoryManager::Clear();
#endif
		return ret ;
		/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	}
    catch(wiz::BaseException& e){
        //���������s����
        ::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"�G���[",MB_OK);
        return 1;   //�G���[�I��
    }
    catch(exception& e){
        //STL�G���[
        //�}���`�o�C�g�o�[�W�����̃��b�Z�[�W�{�b�N�X���Ă�
        ::MessageBoxA(wiz::DxDevice::m_hWnd,e.what(),"�G���[",MB_OK);
        return 1;   //�G���[�I��
    }
    catch(...){
        //�����s�����s����
        ::MessageBox(wiz::DxDevice::m_hWnd,L"�����s���̃G���[�ł�",L"�G���[",MB_OK);
        return 1;   //�G���[�I��
    }
    //��O�����I��
	//COM�R���|�[�l���g�̃����[�X
	::CoUninitialize();
    return 1;   //�G���[�I��
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//// ChildWindow.cpp
////
//// ���[�W�����̌���
//
//#include <windows.h>
//
//
//#define BUTTON_ID   1000
//#define CHILD_ID_A  5000
//#define CHILD_ID_B  5001
//#define BUTTON_ID_OPEN_A 6000
//#define BUTTON_ID_OPEN_B 6001
//
//
//
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK ChildWindowProc(HWND , UINT , WPARAM , LPARAM );
//ATOM InitApp(HINSTANCE);
//HWND InitInstance(HINSTANCE, int);
//HINSTANCE hInst;
//
//TCHAR szClassName[] = _T("ParentWindow"); // �E�B���h�E�N���X�BUNICODE�Ƃ��Ă̕�����萔
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nShowCmd)
//{
//   MSG msg;
//   BOOL bRet;
//   HWND hWnd;
//
//   hInst = hInstance;
//
//   if (!InitApp(hInstance))
//       return FALSE;
//   if (!(hWnd = InitInstance(hInstance,nShowCmd)))
//       return FALSE;
//   while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
//       if (bRet == -1){
//           break;
//       } else {
//           TranslateMessage(&msg);
//           DispatchMessage(&msg);
//       }
//   }
//   return (int)msg.wParam;
//}
//
//// �E�B���h�E�N���X�̓o�^
//
//ATOM InitApp(HINSTANCE hInst)
//{
//   WNDCLASS wc;
//   wc.style        = CS_HREDRAW|CS_VREDRAW;
//   wc.lpfnWndProc  = WndProc;  // �v���V�[�W����
//   wc.cbClsExtra   = 0;
//   wc.cbWndExtra   = 0;
//   wc.hInstance    = hInst;
//   wc.hIcon        = NULL;     // ���T�|�[�g
//   wc.hCursor      = NULL;     // ���T�|�[�g
//   wc.hbrBackground= (HBRUSH) COLOR_WINDOW;
//   wc.lpszMenuName = NULL;     // ���T�|�[�g
//   wc.lpszClassName=(LPCTSTR) szClassName;
//
//   return (RegisterClass(&wc));
//}
//
//// �E�B���h�E�̐���
//HWND InitInstance(HINSTANCE hInst, int nShowCmd)
//{
//   HWND hWnd;
//
//   hWnd = CreateWindow(
//       szClassName,_T("ChildWindow�T���v��"),
//       WS_CLIPCHILDREN,    // �E�B���h�E�̎��
//       CW_USEDEFAULT,      // x���W
//       CW_USEDEFAULT,      // y���W
//       CW_USEDEFAULT,      // ��
//       CW_USEDEFAULT,      // ����
//       NULL,               // �e�E�B���h�E�̃n���h���B�e�����̂�NULL
//       NULL,               // ���j���[�n���h���܂��͎q�E�B���h�EID
//       hInst,              // �C���X�^���X�n���h��
//       NULL);
//   if (!hWnd)
//       return FALSE;
//   ShowWindow(hWnd, nShowCmd);
//   UpdateWindow(hWnd);
//   return hWnd;
//}
//// �E�B���h�E�N���X�̓o�^
//void CreateWindowClass(HINSTANCE hInst, LPCTSTR szClassName, WNDCLASSW &wc)
//{
//   wc.style  = CS_HREDRAW|CS_VREDRAW;
//   wc.lpfnWndProc = ChildWindowProc ; // �v���V�[�W����
//   wc.cbClsExtra = 0;
//   wc.cbWndExtra = 0;
//   wc.hInstance = hInst;
//   wc.hIcon  = NULL;
//   wc.hCursor  = NULL;
//   wc.hbrBackground= reinterpret_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)); //�O���[�ɂ���
//   wc.lpszMenuName = NULL;  // ���T�|�[�g
//   wc.lpszClassName=(LPCWSTR) szClassName;
//}
//
//// �q�E�B���h�E�̐���
//HWND CreateChildWindow(HINSTANCE hInst, int nShowCmd,LPTSTR ClassName,HMENU hMenuChildId,HWND hParent)
//{
//   HWND hWnd;
//
//   // �e�E�B���h�E�̃T�C�Y���擾
//   RECT rect;
//   GetWindowRect(hParent, (LPRECT)&rect);
//
//   hWnd = CreateWindow(
//       ClassName,
//       NULL,
//       WS_CHILD,
//       0,                      //�e�E�B���h�E�Ɠ����T�C�Y
//       0,
//       rect.right - rect.left,
//       rect.bottom - rect.top,
//       hParent,        //�e�E�B���h�E�̃n���h��
//       (HMENU)hMenuChildId,    // �q�E�B���h�E�𔻕ʂ��邽�߂�ID
//       hInst,          //�C���X�^���X�n���h��
//       NULL);
//   if (!hWnd)
//       return FALSE;
//   ShowWindow(hWnd, nShowCmd);
//   UpdateWindow(hWnd);
//   return hWnd;
//}
//// �E�B���h�E�v���V�[�W��
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//   PAINTSTRUCT ps;
//   HDC hdc;
//
//   TCHAR buf[256];
//   size_t size;        // ������̃T�C�Y���i�[����
//
//   WNDCLASSW wc_A;
//   WNDCLASSW wc_B;
//   static HWND hChildWnd_A;
//   static HWND hChildWnd_B;
//
//   static HWND hButton;
//
//   switch (msg){
//       case WM_CREATE:
//
//           // �q�E�B���h�E�`�̐���
//           CreateWindowClass(hInst,_T("ChildWindow_A"),wc_A);
//           RegisterClassW(&wc_A);
//           hChildWnd_A = CreateChildWindow(hInst,SW_HIDE,_T("ChildWindow_A"),(HMENU)CHILD_ID_A,hWnd);
//
//           // �q�E�B���h�E�a�̐���
//           CreateWindowClass(hInst,_T("ChildWindow_B"),wc_B);
//           RegisterClassW(&wc_B);
//           hChildWnd_B = CreateChildWindow(hInst,SW_HIDE,_T("ChildWindow_B"),(HMENU)CHILD_ID_B,hWnd);
//
//           // �v�b�V���{�^�����쐬����
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // �E�B���h�E�N���X��
//               _T("OPEN A"),                            // �L���v�V����
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // �X�^�C���w��
//               50, 50,                                  // ���W
//               60, 40,                                  // �T�C�Y
//               hWnd,                                    // �e�E�B���h�E�̃n���h��
//               (HMENU)BUTTON_ID_OPEN_A,                 // ���j���[�n���h��
//               hInst,                                   // �C���X�^���X�n���h��
//               NULL                                     // ���̑��̍쐬�f�[�^
//               );
//
//           // �v�b�V���{�^�����쐬����
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // �E�B���h�E�N���X��
//               _T("OPEN B"),                            // �L���v�V����
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // �X�^�C���w��
//               50, 100,                                 // ���W
//               60, 40,                                  // �T�C�Y
//               hWnd,                                    // �e�E�B���h�E�̃n���h��
//               (HMENU)BUTTON_ID_OPEN_B,                 // ���j���[�n���h��
//               hInst,                                   // �C���X�^���X�n���h��
//               NULL                                     // ���̑��̍쐬�f�[�^
//               );
//
//           break;
//       case WM_COMMAND:
//           GetClassName(hWnd, buf, 255);
//           NKDbgPrintfW(_T("%s\n"),buf);
//           switch(LOWORD(wp) ){
//           case BUTTON_ID_OPEN_A:
//               // �e�E�B���h�E�́uOPEN_A�v�{�^���������̏���
//               // �q�E�B���h�E�`��\������
//               ShowWindow(hChildWnd_A,SW_SHOW);
//               UpdateWindow(hChildWnd_A);
//
//               return (DefWindowProc(hWnd, msg, wp, lp));
//               break;
//           case BUTTON_ID_OPEN_B:
//               // �e�E�B���h�E�́uOPEN_B�v�{�^���������̏���
//               // �q�E�B���h�E�a��\������
//               ShowWindow(hChildWnd_B,SW_SHOW);
//               UpdateWindow(hChildWnd_B);
//
//               return (DefWindowProc(hWnd, msg, wp, lp));
//               break;
//
//           case BUTTON_ID:
//               // �q�E�B���h�E�́uCLOSE�v�{�^���������̏���
//               if( IsWindowVisible(hChildWnd_A) ){
//                   ShowWindow(hChildWnd_A,SW_HIDE);
//               }else{
//                   ShowWindow(hChildWnd_B,SW_HIDE);
//               }
//
//               break;
//           default:
//               return (DefWindowProc(hWnd, msg, wp, lp));
//           }
//
//           break;
//       case WM_PAINT:
//           hdc = BeginPaint(hWnd,&ps);     // �`�揈�����J�n���܂��B
//
//           SetBkMode(hdc, TRANSPARENT);    // �w�i�𓧉߃��[�h�ɂ��܂�
//
//           GetClassName(hWnd, buf, 255);   // �N���X�����擾
//
//           StringCchLength(buf,255,&size); // �����񒷂̎擾
//
//           ExtTextOut(
//               hdc,    // �f�o�C�X�R���e�L�X�g�̃n���h��
//               0,      // �J�n�ʒu�i��_�j�� x ���W
//               20,     // �J�n�ʒu�i��_�j�� y ���W
//               NULL,   // �����`�̈�̎g�����̃I�v�V����
//               NULL,   // �����`�̈�̓������\���̂ւ̃|�C���^
//               buf,    // ������
//               size,   // ������
//               NULL    // �����Ԋu�̓������z��
//               );
//
//           EndPaint(hWnd,&ps);             // �`�揈�����I�����܂��B
//
//           break;
//       case WM_DESTROY:
//           PostQuitMessage(0);
//           break;
//       default:
//           return (DefWindowProc(hWnd, msg, wp, lp));
//   }
//   return 0;
//}
//
//
//
//LRESULT CALLBACK ChildWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//   PAINTSTRUCT ps;
//   HWND hButton;
//   HDC hdc;
//   COLORREF bkColor;
//   TCHAR buf[256];
//   size_t size;        // ������̃T�C�Y���i�[����
//
//
//   switch (msg){
//       case WM_CREATE:
//           // �v�b�V���{�^�����쐬����
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // �E�B���h�E�N���X��
//               _T("CLOSE"),                             // �L���v�V����
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // �X�^�C���w��
//               100, 200,                                // ���W
//               60, 40,                                  // �T�C�Y
//               hWnd,                                    // �e�E�B���h�E�̃n���h��
//               (HMENU)BUTTON_ID,                        // ���j���[�n���h��
//               hInst,                                   // �C���X�^���X�n���h��
//               NULL                                     // ���̑��̍쐬�f�[�^
//               );
//           break;
//       case WM_PAINT:
//           hdc = BeginPaint(hWnd,&ps);     // �`�揈�����J�n���܂��B
//
//           SetBkMode(hdc, TRANSPARENT);    // �w�i�𓧉߃��[�h�ɂ��܂�
//
//           GetClassName(hWnd, buf, 255);   // �N���X�����擾
//
//           StringCchLength(buf,255,&size); // �����񒷂̎擾
//
//           ExtTextOut(
//               hdc,    // �f�o�C�X�R���e�L�X�g�̃n���h��
//               0,      // �J�n�ʒu�i��_�j�� x ���W
//               20,     // �J�n�ʒu�i��_�j�� y ���W
//               NULL,   // �����`�̈�̎g�����̃I�v�V����
//               NULL,   // �����`�̈�̓������\���̂ւ̃|�C���^
//               buf,    // ������
//               size,   // ������
//               NULL    // �����Ԋu�̓������z��
//               );
//
//           EndPaint(hWnd,&ps);
//
//           break;
//       case WM_COMMAND:
//           GetClassName(hWnd, buf, 255);
//           NKDbgPrintfW(_T("%s\n"),buf);
//           switch(LOWORD(wp) ){
//           case BUTTON_ID:
//
//               // �e�E�B���h�E�փ��b�Z�[�W�`�d�B�����͐e�ɔC����B
//               SendMessage(GetParent(hWnd),msg,wp,lp);
//
//               // ���E�B���h�E���\���ɂ���
//               //ShowWindow(hWnd,SW_HIDE);
//               //UpdateWindow(hWnd);
//
//               break;
//           default:
//               return (DefWindowProc(hWnd, msg, wp, lp));
//           }
//
//           break;
//       case WM_DESTROY:
//           PostQuitMessage(0);
//           break;
//       default:
//           return (DefWindowProc(hWnd, msg, wp, lp));
//   }
//   return 0;
//}
//
