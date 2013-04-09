////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Controller.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：コントローラーの管理
//					▼
//	namespace wiz;
//		class  GAMEPAD ;
//		struct BState  ;
//		struct CUSTOM_CONTROLER_STATE ;
//		struct CONTROLER_STATE ;
//		class  CONTROLLERS ;
//

//定数定義


#include "StdAfx.h"
#include "Controller.h"
namespace Controller__{
#define MOVE_SPEED 6
////関数プロトタイプの宣言
//GAMEPAD* m_pMain = new GAMEPAD;
 //
//
//アプリケーションで使用するコントローラーのプロパティを列挙して設定する
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
//利用可能なジョイスティックを列挙するコールバック関数
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	//// 「DirectInputデバイス」オブジェクトの作成
 //   if(FAILED( m_pMain->g_lpDI->CreateDevice(pdidInstance->guidInstance,
	//	&m_pMain->g_lpDIDevice, NULL)))
	//{
	//	return DIENUM_CONTINUE;
	//}
    return DIENUM_STOP;
}
 //
 //
 //ダイレクトインプットの初期化関数
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
	// 「DirectInput」オブジェクトの作成
	if( FAILED(  DirectInput8Create( GetModuleHandle(NULL), 
		DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&m_pDinput, NULL ) ) )
	{
		return E_FAIL;
	}
	//利用可能なゲームコントローラーの列挙関数を実行
	if(FAILED(m_pDinput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback,
				  NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}   
	if(!m_pPadDevice)
	{
		return E_FAIL;
	}
	// デバイスをジョイスティックに設定
	if( FAILED( m_pPadDevice->SetDataFormat( &c_dfDIJoystick2 ) ) )
	{
		return E_FAIL;
	}
	// 協調レベルの設定
    if( FAILED( m_pPadDevice->SetCooperativeLevel(m_hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND )) )
	{
		return E_FAIL;
	}
	//アプリケーションで使用するコントローラーのプロパティを列挙して設定する
	if(FAILED(m_pPadDevice->EnumObjects( EnumObjectsCallback,NULL, DIDFT_ALL)))
	{
		return E_FAIL;
	}
	// デバイスを「取得」する
    m_pPadDevice->Acquire();
	return S_OK;
	*/
}
//
//
//　パッドで押されているキーを調べ、対応する音を出す
void GAMEPAD::GetState()
{	

	HRESULT hr=g_lpDIDevice->Acquire();
	if((hr==DI_OK) || (hr==S_FALSE))
	{
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE2), &m_State);
	}
	
}
};