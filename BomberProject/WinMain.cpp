////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FWinMain.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�G���g���[�|�C���g
//					������
//	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"

int nDefaultShowCmd ;
HINSTANCE _hInstance ;
class MouseUtilityCushion{
public:
	static void setMouseLB( bool Bool ){ wiz::Cursor2D::m_bMouseLB = Bool ; }
	static void setMouseRB( bool Bool ){ wiz::Cursor2D::m_bMouseRB = Bool ; }
	static void setMouseMB( bool Bool ){ wiz::Cursor2D::m_bMouseMB = Bool ; }

};
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
			#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
				Debugger::DebugWindow::init(_hInstance,hWnd,nDefaultShowCmd);
			#endif
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
		case WM_LBUTTONDOWN		:	MouseUtilityCushion::setMouseLB( true )			;	break ;
		case WM_RBUTTONDOWN		:	MouseUtilityCushion::setMouseRB( true )			;	break ;
		case WM_MBUTTONDOWN		:	MouseUtilityCushion::setMouseMB( true )			;	break ;
		case WM_LBUTTONUP		:	MouseUtilityCushion::setMouseLB( false )		;	break ;
		case WM_RBUTTONUP		:	MouseUtilityCushion::setMouseRB( false )		;	break ;
		case WM_MBUTTONUP		:	MouseUtilityCushion::setMouseMB( false )		;	break ;
		case WM_LBUTTONDBLCLK	:	break;
		case WM_RBUTTONDBLCLK	:	break;
		case WM_MBUTTONDBLCLK	:	break;

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
	_hInstance = hInstance ;
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
    wcex.hIcon          = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));                     //�A�C�R���̎w��i�����ł�NULL�j
    wcex.hCursor        = NULL;    //�ʏ�̖��J�[�\��
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
		// DEVMODE    devMode;
		wiz::DxDevice::m_hWnd = ::CreateWindowEx( 
            WS_EX_ACCEPTFILES,  //�I�v�V�����̃E�B���h�E�X�^�C��
            pClassName,         // �o�^����Ă���N���X��
            pWndTitle,          // �E�C���h�E��
            WS_POPUP,           // �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
            0,                  // �E�C���h�E�̉������̈ʒu
            0,                  // �E�C���h�E�̏c�����̈ʒu
			(int)STANDARD_WINDOW_WIDTH,       // �t���X�N���[���E�C���h�E�̕�
            (int)STANDARD_WINDOW_HEIGHT,      // �t���X�N���[���E�C���h�E�̍���
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
		//devMode.dmPelsWidth  = BASE_CLIENT_WIDTH;
		//devMode.dmPelsHeight = BASE_CLIENT_HEIGHT;

		//ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

    }
    else {
        //�E�C���h�E�̍쐬
		wiz::DxDevice::m_hWnd = ::CreateWindowEx(
            0,                              //�I�v�V�����̃E�B���h�E�X�^�C��
            pClassName,                     //�E�C���h�E�N���X��
            pWndTitle,                      //�E�C���h�E�̃^�C�g��
            WS_OVERLAPPED | WS_SYSMENU,            //�ړ��o�[�����ʏ�̃E�C���h�E
            100,
			100,							//
            iClientWidth,					//�E�C���h�E���i�b��j
            iClientHeight,					//�E�C���h�E�����i�b��j
            NULL,							//�e�E�C���h�E�i�g�b�v���x���Ȃ̂ŁA�Ȃ��j
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
	SetCapture(wiz::DxDevice::m_hWnd);
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
		ReleaseCapture();

		//Debugger::DBGWRITINGLOGTEXT::addStr(L"�Q�[���V�X�e���I�������J�n");
		SafeDelete( device );
		ShowCursor(true);
		//wiz::TextureManager::Release();
#if defined( CF_MEMORYMANAGER_ENABLE )
		TMemoryManager::Clear();
#endif
		::PostQuitMessage(0);
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
