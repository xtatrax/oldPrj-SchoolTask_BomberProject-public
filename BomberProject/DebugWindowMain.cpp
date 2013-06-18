////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FDebugWindowMain.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O���\���p�E�C���h�E
//					�F�ɂȎ��ɂ����Ԃ悤�̂ӂ�����Ew�E
//					��
//	namespace TLIB;
//

#include "stdafx.h"
#include "DebugWindowMain.h"
#include <process.h>

namespace Debugger{

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case 0:
        default:
        break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}


DebugWindow* DebugWindow::m_pMyInstance = NULL ;
HANDLE	DebugWindow::m_hMyThread = NULL ;

void DebugWindow::StartThread(START_PACKET pac){
	m_hMyThread = (HANDLE) _beginthreadex(
		NULL,
		0,
		&DebugWindow::ThreadLauncher,	// �����`�����N��
		&pac,
		0,
		NULL);

}

unsigned __stdcall DebugWindow::ThreadLauncher(void *args){
	START_PACKET pac = *(START_PACKET*)args;
	m_pMyInstance = new DebugWindow(pac);
	//reinterpret_cast<DebugWindow*>(args)(pac);
	return 0;
}

DebugWindow::DebugWindow(START_PACKET pac)
	:m_pClassName( RCTEXT_DEBUGWINDOWCLASSNAME )
	,m_pWndTitle(  RCTEXT_DEBUGWINDOWTITLE     )
{
	try{
		HINSTANCE hInstance		= pac.hInstance;
		HWND i_hParentWindow    = pac.i_hParentWindow;
		int nShowCmd			= pac.nShowCmd;
		////////// /////////
		// 
		//	: WNDCLASSEX�\���̂̏�����
		//
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
		wcex.lpszClassName  = m_pClassName;               //�N���X���̎w��
		wcex.hIconSm        = NULL;                     //�������A�C�R���Ȃ�
		//�E�C���h�E�N���X�̓o�^
		if (!::RegisterClassEx(&wcex))
		{
			//���s����
			::MessageBox(NULL,L"�q�E�C���h�E�N���X�o�^�Ɏ��s���܂���",L"�G���[",MB_OK);
			return ;   //�G���[�I��
		}
		// 
		//	: WNDCLASSEX�\���̂̏�����
		//
		////////// /////////

		////////// /////////
		// 
		//	: �E�C���h�E�̍쐬
		//
		m_hWnd = ::CreateWindow(
			m_pClassName,						//�E�C���h�E�N���X��
			m_pWndTitle,						//�E�C���h�E�̃^�C�g��
			WS_CHILD,							//WS_THICKFRAME
			CW_USEDEFAULT,						// 
			CW_USEDEFAULT,						//�ʒu��Windows�ɔC����
			(int)STANDARD_WINDOW_WIDTH,			//�E�C���h�E���i�b��j
			(int)STANDARD_WINDOW_HEIGHT,		//�E�C���h�E�����i�b��j
			i_hParentWindow,								//�e�E�C���h�E�i�g�b�v���x���Ȃ̂ŁA�Ȃ��j
			(HMENU)1,							//���j���[�Ȃ�
			hInstance,							//���̃C���X�^���X
			NULL								//�g�p���Ȃ�
		);
		if (!m_hWnd){
			//���s����
			::MessageBox(0,L"�q�E�C���h�E�쐬�Ɏ��s���܂���",L"�G���[",MB_OK);
			return ;   //�G���[�I��
		}
		// 
		//	: �E�C���h�E�̍쐬
		//
		////////// /////////

		//�E�C���h�E�̕\��
		::ShowWindow(
			m_hWnd,       //�擾�����E�C���h�E�̃n���h��
			nShowCmd    //WinMain�ɓn���ꂽ�p�����[�^
		);
		// WM_PAINT���Ă΂�Ȃ��悤�ɂ���
		::ValidateRect(wiz::DxDevice::m_hWnd, 0);

		m_pD3D         = NULL;
		m_pD3DDevice   = NULL;
        D3DDISPLAYMODE d3ddm;
        // Direct3D9�I�u�W�F�N�g�̍쐬
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
			::MessageBox(0,
                L"�q�E�C���h�E��\nDirectX�̏������Ɏ��s���܂����BDirectX�C���^�[�t�F�C�X���擾�ł��܂���B",
                L"DebugWindow::DebugWindow()",
				MB_OK
                );
        }
        
        // ���݂̃f�B�X�v���C���[�h���擾
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
			::MessageBox(0,
                L"�q�E�C���h�E��\n�q�E�C���h�E��\n�������Ɏ��s���܂����B�f�B�X�v���C���[�h���擾�ł��܂���B",
                L"DebugWindow::DebugWindow()",
				MB_OK
                );
        }

        // �f�o�C�X�̃v���[���e�[�V�����p�����[�^��������
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        m_D3DPP.Windowed                = TRUE;             // �E�C���h�E���\���̎w��
        m_D3DPP.BackBufferFormat        = d3ddm.Format;         // �J���[���[�h�̎w��
        m_D3DPP.SwapEffect              = D3DSWAPEFFECT_DISCARD; 
        m_D3DPP.EnableAutoDepthStencil  = TRUE;
        m_D3DPP.AutoDepthStencilFormat  = D3DFMT_D24S8;
        
        // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
        // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                        D3DDEVTYPE_HAL, 
                                        m_hWnd, 
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING, 
                                        &m_D3DPP, &m_pD3DDevice))) {
            // ��L�̐ݒ肪���s������
            // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                            D3DDEVTYPE_HAL, 
                                            m_hWnd, 
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                            &m_D3DPP, &m_pD3DDevice))) {
                // ��L�̐ݒ肪���s������
                // �`��ƒ��_������CPU�ōs�Ȃ�
                if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                                D3DDEVTYPE_REF, m_hWnd, 
                                                D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                                &m_D3DPP, &m_pD3DDevice))) {
                    // ���������s
				::MessageBox(0,
					L"�q�E�C���h�E��\n�f�o�C�X�̏������Ɏ��s���܂����B�I�m�ȃf�o�C�X���擾�ł��܂���B",
					L"DebugWindow::DebugWindow()",
					MB_OK
					);
                }
            }
        }
		MSG msg;    //���b�Z�[�W�\���̂̐錾��`
		//	: ���C���X���b�h���[�v
		while(true)
		{
			//	: ���Z�[�W����
			//	: �܂���
			//	: �V�[���̕`��
			if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				switch(msg.message)
				{

					default:
						// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
						::TranslateMessage(&msg);
						::DispatchMessage(&msg);
						break;
				}
			}
			else
			{  // �������郁�b�Z�[�W�������Ƃ��͕`����s��


				// �E�B���h�E�������Ă��鎞�����`�悷�邽�߂̏���
				WINDOWPLACEMENT wndpl;
				::GetWindowPlacement(m_hWnd, &wndpl); // �E�C���h�E�̏�Ԃ��擾
				if((wndpl.showCmd != SW_HIDE) && 
					(wndpl.showCmd != SW_MINIMIZE) &&
					(wndpl.showCmd != SW_SHOWMINIMIZED) &&
					(wndpl.showCmd != SW_SHOWMINNOACTIVE))
				{

					// �r���[�|�[�g�Ɛ[�x�o�b�t�@�̏������ƃX�e���V���o�b�t�@�̃N���A
					if(FAILED(m_pD3DDevice->Clear(0,NULL,               // ����������̈�͑S��
									D3DCLEAR_STENCIL |                  // �X�e���V���o�b�t�@���w��
									D3DCLEAR_TARGET |                   // �o�b�N�o�b�t�@���w��
									D3DCLEAR_ZBUFFER,                   // �[�x�o�b�t�@�iZ�o�b�t�@�j���w��
									D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),  // ����������F
									1.0f,                               // ����������[�x�o�b�t�@�iZ�o�b�t�@�j�̒l
									0))){                               // ����������X�e���V���o�b�t�@�̒l
						//���s������X���[
						::MessageBox(0,
							L"�q�E�C���h�E��\n�o�b�t�@���N���A�ł��܂���B",
							L"DebugWindow::DebugWindow()",
							MB_OK
						);
					}
					// �`��J�n�錾
					if(SUCCEEDED(m_pD3DDevice->BeginScene())) {


						m_pD3DDevice->EndScene();
					}

					// �`�挋�ʂ̓]��
					if(FAILED(m_pD3DDevice->Present( 0, 0, 0, 0 ))) {
						// �f�o�C�X�������畜�A
						if(m_pD3DDevice->Reset(&m_D3DPP)!= D3D_OK){
							//�f�o�C�X�̕��A�Ɏ��s������X���[
							::MessageBox(0,
								L"�q�E�C���h�E��\n�f�o�C�X�𕜋A�ł��܂���B",
								L"DebugWindow::DebugWindow()",
								MB_OK
							);
						}
					}
				}
			}
		}
	}
	catch(...){
		throw;
	}
}

}//end of namespace Debugger.