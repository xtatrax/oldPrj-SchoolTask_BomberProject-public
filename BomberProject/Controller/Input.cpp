//-----------------------------------------------------
//	DirectInputを使った入力サンプル
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

//デバイスの作成
bool CInput::Create( HWND hWnd, int useDevice )
{
	if ( m_pDInput ) {
		Release();
	}
	m_hWnd = hWnd;

	//DirectInputオブジェクトの生成
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

//デバイスの解放
void CInput::Release()
{
	//各デバイス解放
	m_keyboard.Release();
	m_mouse.Release();
	m_gamepad.Release();

	//DirectInputオブジェクトの解放
	if ( m_pDInput != NULL ) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}

	m_hWnd		= NULL;
	m_useDevice = 0;
}
//*/