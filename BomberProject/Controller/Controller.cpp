////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FController.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�R���g���[���[�̊Ǘ�
//					��
//	namespace wiz;
//		class  GAMEPAD ;
//		struct BState  ;
//		struct CUSTOM_CONTROLER_STATE ;
//		struct CONTROLER_STATE ;
//		class  CONTROLLERS ;
//

//�萔��`


#include "StdAfx.h"
#include "Controller.h"
namespace Controller__{
#define MOVE_SPEED 6
////�֐��v���g�^�C�v�̐錾
//GAMEPAD* m_pMain = new GAMEPAD;
 //
//
//�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
BOOL CALLBACK EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,VOID* pContext )
{
	//if( pdidoi->dwType & DIDFT_AXIS )
	//{
	//	DIPROPRANGE diprg; 
	//	diprg.diph.dwSize	 = sizeof(DIPROPRANGE); 
	//	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	//	diprg.diph.dwHow	  = DIPH_BYID; 
	//	diprg.diph.dwObj	  = pdidoi->dwType; 
	//	diprg.lMin= -MOVE_SPEED; 
	//	diprg.lMax= MOVE_SPEED; 
	//
	//	if( FAILED( m_pMain->g_lpDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
	//	{
	//		return DIENUM_STOP;
	//	}
	//}
    return DIENUM_CONTINUE;
}
//
//
//���p�\�ȃW���C�X�e�B�b�N��񋓂���R�[���o�b�N�֐�
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	//// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
 //   if(FAILED( m_pMain->g_lpDI->CreateDevice(pdidInstance->guidInstance,
	//	&m_pMain->g_lpDIDevice, NULL)))
	//{
	//	return DIENUM_CONTINUE;
	//}
    return DIENUM_STOP;
}
 //
 //
 //�_�C���N�g�C���v�b�g�̏������֐�
 HRESULT GAMEPAD::InitDinput(HWND hWnd)
{
	HINSTANCE hInst;
	HRESULT   hr;
	
	hInst = (HINSTANCE)GetWindowLong( hWnd , GWL_HINSTANCE );
	
	hr = DirectInput8Create( hInst , DIRECTINPUT_VERSION , IID_IDirectInput8 ,
	                         (void**)&g_lpDI , NULL );
	if ( FAILED( hr ) ){ return FALSE; }
	hr = g_lpDI->EnumDevices( DI8DEVCLASS_GAMECTRL , EnumJoysticksCallback ,
	                        NULL , DIEDFL_ATTACHEDONLY );
	if ( FAILED( hr ) ){ return FALSE; }
	
	hr = g_lpDIDevice->SetDataFormat( &c_dfDIJoystick );
	if ( FAILED( hr ) ){ return FALSE; }
	
	hr = g_lpDIDevice->SetCooperativeLevel( hWnd , DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if ( FAILED( hr ) ){ return FALSE; }
	
	g_diDevCaps.dwSize = sizeof( DIDEVCAPS );
	hr = g_lpDIDevice->GetCapabilities( &g_diDevCaps );
	if ( FAILED( hr ) ){ return FALSE; }
	
	hr = g_lpDIDevice->EnumObjects( EnumObjectsCallback , (VOID*)hWnd , DIDFT_AXIS );
	if ( FAILED( hr ) ){ return FALSE; }
	
	hr = g_lpDIDevice->Poll();
	if ( FAILED( hr ) ){
		hr = g_lpDIDevice->Acquire();
		while( hr == DIERR_INPUTLOST ){
			hr = g_lpDIDevice->Acquire();
		}
	}
	
	return TRUE;
	/*
	// �uDirectInput�v�I�u�W�F�N�g�̍쐬
	if( FAILED(  DirectInput8Create( GetModuleHandle(NULL), 
		DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&m_pDinput, NULL ) ) )
	{
		return E_FAIL;
	}
	//���p�\�ȃQ�[���R���g���[���[�̗񋓊֐������s
	if(FAILED(m_pDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
				  NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}   
	if(!m_pPadDevice)
	{
		return E_FAIL;
	}
	// �f�o�C�X���W���C�X�e�B�b�N�ɐݒ�
	if( FAILED( m_pPadDevice->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		return E_FAIL;
	}
	// �������x���̐ݒ�
    if( FAILED( m_pPadDevice->SetCooperativeLevel(m_hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND )) )
	{
		return E_FAIL;
	}
	//�A�v���P�[�V�����Ŏg�p����R���g���[���[�̃v���p�e�B��񋓂��Đݒ肷��
	if(FAILED(m_pPadDevice->EnumObjects( EnumObjectsCallback,NULL, DIDFT_ALL)))
	{
		return E_FAIL;
	}
	// �f�o�C�X���u�擾�v����
    m_pPadDevice->Acquire();
	return S_OK;
	*/
}
//
//
//�@�p�b�h�ŉ�����Ă���L�[�𒲂ׁA�Ή����鉹���o��
void GAMEPAD::GetState()
{	

	HRESULT hr=g_lpDIDevice->Acquire();
	if((hr==DI_OK) || (hr==S_FALSE))
	{
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE2), &m_State);
	}
	
}
};