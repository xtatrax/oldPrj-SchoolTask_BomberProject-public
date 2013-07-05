//-----------------------------------------------------
//	DirectInput���g�������̓T���v��
//	2009.12.29 TMO
//-----------------------------------------------------
#include "StdAfx.h"
//#include "Input.h"

/*
CInput::CInput()
{
	m_pDInput   = NULL;
	m_hWnd		= NULL;
	m_useDevice = 0;
}

CInput::~CInput()
{
	Release();
}

//�f�o�C�X�̍쐬
bool CInput::Create( HWND hWnd, int useDevice )
{
	if ( m_pDInput ) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInput�I�u�W�F�N�g�̐���
	HRESULT hr = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if ( FAILED( hr ) ) {
		return false;
	}

	m_useDevice = useDevice;
	if ( useDevice & UseInputDevice_KEYBOARD ) { m_keyboard.Create(m_pDInput, hWnd); }
	if ( useDevice & UseInputDevice_MOUSE    ) { m_mouse.Create(m_pDInput, hWnd);    }
	if ( useDevice & UseInputDevice_GAMEPAD  ) { m_gamepad.Create(m_pDInput, hWnd);  }

	return true;
}

//�f�o�C�X�̉��
void CInput::Release()
{
	//�e�f�o�C�X���
	m_keyboard.Release();
	m_mouse.Release();
	m_gamepad.Release();

	//DirectInput�I�u�W�F�N�g�̉��
	if ( m_pDInput != NULL ) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	m_hWnd		= NULL;
	m_useDevice = 0;
}
//*/