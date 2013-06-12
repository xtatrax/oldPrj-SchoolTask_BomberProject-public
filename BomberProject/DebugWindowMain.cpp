////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FDebugWindowMain.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O���\���p�E�C���h�E
//					��
//	namespace TLIB;
//

#include "stdafx.h"
#include "DebugWindowMain.h"

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

DebugWindow::DebugWindow(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd)
	:m_pClassName( RCTEXT_DEBUGWINDOWCLASSNAME )
	,m_pWndTitle(  RCTEXT_DEBUGWINDOWTITLE     )
{
	try{
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
			WS_CAPTION|WS_THICKFRAME,	//�ړ��o�[�����ʏ�̃E�C���h�E
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
	}
	catch(...){
		throw;
	}
}

}//end of namespace Debugger.