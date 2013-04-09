//-----------------------------------------------------
//	DirectInput���g�������̓T���v��(�Q�[���p�b�h)
//	2009.12.29 TMO
//-----------------------------------------------------
#include "StdAfx.h"
#include "Input.h"
/*
CInputGamepad::CInputGamepad()
{
	m_pDIDevJS = NULL;
	ZeroMemory(gamepadState, sizeof(gamepadState));
	ZeroMemory(gamepadAction, sizeof(gamepadAction));
}

//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
struct DIDeviceEnumPrm
{
	bool isFind;
	GUID guid;
};

//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X��񋓂��ăQ�[���p�b�h��T��
static BOOL CALLBACK DIEnumDeviceCallback( LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef )
{
	DIDeviceEnumPrm* prm = (DIDeviceEnumPrm*)pvRef;
	prm->guid   = ipddi->guidInstance;
	prm->isFind = true;

	return DIENUM_STOP;	//�񋓂𑱂���Ȃ�DIENUM_CONTINUE
}

//�Q�[���p�b�h�f�o�C�X�̍쐬
bool CInputGamepad::Create( IDirectInput8* pDInput, HWND hWnd )
{
	HRESULT hr;

	if ( !pDInput ) {
		return false;
	}

	try {
		
		DIDeviceEnumPrm prm;
		prm.isFind = false;
		
		//�Q�[���p�b�h�f�o�C�X��񋓂��Č���������GUID���擾����
		pDInput->EnumDevices( DI8DEVTYPE_JOYSTICK, DIEnumDeviceCallback, (LPVOID)&prm, DIEDFL_ATTACHEDONLY );
		
		if ( prm.isFind != true ) {
			throw "�Q�[���p�b�h�͌�����܂���ł���";
		}

		hr = pDInput->CreateDevice( prm.guid, &m_pDIDevJS, NULL );

		if ( FAILED( hr ) ) {
			throw "err";
		}

		m_pDIDevJS->SetDataFormat(&c_dfDIJoystick);

		//�����[�h���Βl���[�h��
		DIPROPDWORD diprop;
		ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize		= sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj		= 0;
		diprop.diph.dwHow		= DIPH_DEVICE;
		diprop.dwData			= DIPROPAXISMODE_ABS;
		m_pDIDevJS->SetProperty( DIPROP_AXISMODE, &diprop.diph );
		
		//���̒l�͈̔͐ݒ�
		//�\���L�[�������Ă��Ȃ��Ƃ���0�ɂȂ�悤��
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize		= sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj		= DIJOFS_X;
		diprg.diph.dwHow		= DIPH_BYOFFSET;
		diprg.lMin = -1000;
		diprg.lMax = 1000;
		m_pDIDevJS->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		diprg.diph.dwObj		= DIJOFS_Y;
		m_pDIDevJS->SetProperty( DIPROP_RANGE, &diprg.diph );
		
		//�o�b�t�@�T�C�Y�̐ݒ�
		ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = 1000;
		hr = m_pDIDevJS->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		if ( FAILED( hr ) ) {
			return false;
		}

		//�������[�h�̐ݒ�
		hr = m_pDIDevJS->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr))
		{
			throw "err";
		}

		//���͂�������
		m_pDIDevJS->Acquire();

	} catch(...) {
		return false;
	}

	return true;
}

//�Q�[���p�b�h�̓��͏�Ԃ��X�V�i�\���L�[�ƂS�̃{�^�������`�F�b�N���Ă���j
void CInputGamepad::Update()
{
	if ( !m_pDIDevJS ) { return; }

	ZeroMemory( gamepadAction, sizeof(gamepadAction) );

	DIDEVICEOBJECTDATA od;
	DWORD dwItems = 1;
	HRESULT hr;
	if( !m_pDIDevJS ){
		while ( true ) {
			hr = m_pDIDevJS->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),&od,&dwItems,0);
			
			if ( hr == DIERR_INPUTLOST ) {
				m_pDIDevJS->Acquire();
			} else
			if ( dwItems == 0 || FAILED(hr) ) {
				
				if ( hr == DIERR_NOTACQUIRED ) {
					m_pDIDevJS->Acquire();
				}

				break;
			} else {
				dwData = od.dwData;
				switch ( od.dwOfs ) {
					case DIJOFS_X:
						JoyStickLX = od.dwData;
						break;
					case DIJOFS_Y:
						JoyStickLY = od.dwData;
						break;
					case DIJOFS_POV(GamePadBtn_UP):
						gamepadState[ 0 ] = false;
						gamepadState[ 1 ] = false;
						gamepadState[ 2 ] = false;
						gamepadState[ 3 ] = false;
						switch(od.dwData){
							case 0:
								gamepadState[ GamePadBtn_UP ] = true ;
								
								if ( gamepadState[ GamePadBtn_UP ] ) {
									gamepadAction[ GamePadBtn_UP ]= true;
								}
								break;
							case 4500:
								gamepadState[ GamePadBtn_UP ] = true ;
								
								if ( gamepadState[ GamePadBtn_UP ] ) {
									gamepadAction[ GamePadBtn_UP ]= true;
								}

								gamepadState[ GamePadBtn_RIGHT ] = true ;
								
								if ( gamepadState[ GamePadBtn_RIGHT ] ) {
									gamepadAction[ GamePadBtn_RIGHT ]= true;
								}

								break;
							case 9000:
								gamepadState[ GamePadBtn_RIGHT ] = true ;
								
								if ( gamepadState[ GamePadBtn_RIGHT ] ) {
									gamepadAction[ GamePadBtn_RIGHT ]= true;
								}
								break;
							case 13500:
								gamepadState[ GamePadBtn_DOWN ] = true ;
								
								if ( gamepadState[ GamePadBtn_DOWN ] ) {
									gamepadAction[ GamePadBtn_DOWN ]= true;
								}

								gamepadState[ GamePadBtn_RIGHT ] = true ;
								
								if ( gamepadState[ GamePadBtn_RIGHT ] ) {
									gamepadAction[ GamePadBtn_RIGHT ]= true;
								}

								break;
							case 18000:
								gamepadState[ GamePadBtn_DOWN ] = true ;
								
								if ( gamepadState[ GamePadBtn_DOWN ] ) {
									gamepadAction[ GamePadBtn_DOWN ]= true;
								}

								break;
							case 22500:
								gamepadState[ GamePadBtn_DOWN ] = true ;
								
								if ( gamepadState[ GamePadBtn_DOWN ] ) {
									gamepadAction[ GamePadBtn_DOWN ]= true;
								}

								gamepadState[ GamePadBtn_LEFT ] = true ;
								
								if ( gamepadState[ GamePadBtn_LEFT ] ) {
									gamepadAction[ GamePadBtn_LEFT ]= true;
								}
								break;
							case 27000:
								gamepadState[ GamePadBtn_LEFT ] = true ;
								
								if ( gamepadState[ GamePadBtn_LEFT ] ) {
									gamepadAction[ GamePadBtn_LEFT ]= true;
								}

								break;
							case 31500:
								gamepadState[ GamePadBtn_UP ] = true ;
								
								if ( gamepadState[ GamePadBtn_UP ] ) {
									gamepadAction[ GamePadBtn_UP ]= true;
								}

								gamepadState[ GamePadBtn_LEFT ] = true ;
								
								if ( gamepadState[ GamePadBtn_LEFT ] ) {
									gamepadAction[ GamePadBtn_LEFT ]= true;
								}
								break;
						}
						break;
					case DIJOFS_BUTTON0:
						gamepadState[ GamePadBtn_Btn0 ] = ( od.dwData & 0x80 )? true : false;
						
						if ( gamepadState[ GamePadBtn_Btn0 ] ) {
							gamepadAction[ GamePadBtn_Btn0 ]= true;
						}
						break;
					case DIJOFS_BUTTON1:
						gamepadState[ GamePadBtn_Btn1 ] = ( od.dwData & 0x80 )? true : false;
						
						if ( gamepadState[ GamePadBtn_Btn1 ] ) {
							gamepadAction[ GamePadBtn_Btn1 ]= true;
						}
						break;
					case DIJOFS_BUTTON2:
						gamepadState[ GamePadBtn_Btn2 ] = ( od.dwData & 0x80 )? true : false;
						
						if ( gamepadState[ GamePadBtn_Btn2 ] ) {
							gamepadAction[ GamePadBtn_Btn2 ]= true;
						}
						break;
					case DIJOFS_BUTTON3:
						gamepadState[ GamePadBtn_Btn3 ] = ( od.dwData & 0x80 )? true : false;
						
						if ( gamepadState[ GamePadBtn_Btn3 ] ) {
							gamepadAction[ GamePadBtn_Btn3 ]= true;
						}
						break;
				}
			}
		}
	}
}
//�Q�[���p�b�h�f�o�C�X�̉��
void CInputGamepad::Release()
{
	if ( m_pDIDevJS != NULL ) {
		m_pDIDevJS->Unacquire();
		m_pDIDevJS->Release();
		m_pDIDevJS=NULL;
	}
	ZeroMemory(gamepadState, sizeof(gamepadState));
	ZeroMemory(gamepadAction, sizeof(gamepadAction));

}
//*/