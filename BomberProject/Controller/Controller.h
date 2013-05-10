////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Controller.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：コントローラーの読み込み等を管理する
//					▼
//	namespace wiz;
//		class  GAMEPAD ;					//	: [ tatra ] 参考用に拾ったソース( 未使用 )
//		struct BState  ;					//	: [ tatra ] XBOXコントローラーに対応したボタンの状態を格納する構造体	
//		struct CUSTOM_CONTROLER_STATE ;		//	: [ tatra ] XINPUT_STATを拡張した構造体
//		struct CONTROLER_STATE ;			//	: [ tatra ] 一つのコントローラーの情報をまとめておく構造体
//		class  CONTROLLERS ;				//	: [ tatra ] コントローラーを管理するクラス
//



#pragma once
#include "Input.h"

namespace Controller__{
//**************************************************************************//
// class GAMEPAD;
// 用途: 拾い物#未知
//**************************************************************************//
class GAMEPAD
{
public:

	HWND m_hWnd;
	HDC m_hdc;
	//DirectInput
	DIJOYSTATE2		m_State;
	LPDIRECTINPUT8	g_lpDI;
	LPDIRECTINPUTDEVICE8 g_lpDIDevice;
	DIDEVCAPS            g_diDevCaps;
	HRESULT GAMEPAD::InitDinput(HWND hWnd);
	void GAMEPAD::GetState();
	GAMEPAD()
	{
		ZeroMemory(this,sizeof(GAMEPAD));
	}
	~GAMEPAD()
	{
		SAFE_RELEASE(g_lpDIDevice);
		SAFE_RELEASE(g_lpDI);
	}
};
};
namespace wiz {
//**************************************************************************//
// struct;
// 担当  : 鴫原 徹
// 用途  : コントローラーのボタンの状態
//         XBOXコントローラー対応ボタン名版
//         XBOXコントローラーを前提に作らない限り使わないほうが良い (とおもう
//**************************************************************************//
struct BoxCon{
	bool  UP     :1 ;  //  : ハット↑ (01ボタン)
	bool  DOWN    :1 ;  //  : ハット↓ (02ボタン)
	bool  LEFT     :1 ;  //  : ハット← (03ボタン)
	bool  RIGHT	    :1 ;  //  : ハット→ (04ボタン)
	bool  START	     :1 ;  //  : スタートボタン (05ボタン)
	bool  BACK	      :1 ;  //  : バックボタン (06ボタン)
	bool  LEFT_THUMB   :1 ;  //  : 左トリガー (07ボタン)
	bool  RIGHT_THUNB   :1 ;  //  : 右トリガー (08ボタン)
	bool  LEFT_SHOULDER  :1 ;  //  : 左ショルダー (09ボタン)
	bool  RIGHT_SHOULDER :1 ;  //  : 右ショルダー (10ボタン)
	bool                 :2 ;  //  : 空きビット(11､12ボタン)
	bool  A             :1 ;  //  : A (13ボタン)
	bool  B          :1 ;  //  : B (14ボタン)
	bool  X       :1 ;  //  : X (15ボタン)
	bool  Y    :1 ;  //  : Y (16ボタン)
};
//**************************************************************************//
// struct State;
// 担当  : 鴫原 徹
// 用途  : コントローラーのボタンの状態
//         #define XINPUT_GAMEPAD_DPAD_UP          0x0001
//         #define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
//         #define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
//         #define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
//         #define XINPUT_GAMEPAD_START            0x0010
//         #define XINPUT_GAMEPAD_BACK             0x0020
//         #define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
//         #define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
//         #define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
//         #define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
//         #define XINPUT_GAMEPAD_A                0x1000
//         #define XINPUT_GAMEPAD_B                0x2000
//         #define XINPUT_GAMEPAD_X                0x4000
//         #define XINPUT_GAMEPAD_Y                0x8000
//**************************************************************************//
union BState{
	//union {
	protected:
		WORD wButton;
	public:
		//friend struct BState;
		//**************************************************************************//
		// struct;
		// 担当  : 鴫原 徹
		// 用途  : コントローラーのボタンの状態
		//         番号別真偽版
		//**************************************************************************//
		struct{
			bool  b01 :1 ;	//	:  1ボタン
			bool  b02 :1 ;	//	:  2ボタン
			bool  b03 :1 ;	//	:  3ボタン
			bool  b04 :1 ;	//	:  4ボタン
			bool  b05 :1 ;	//	:  5ボタン
			bool  b06 :1 ;	//	:  6ボタン
			bool  b07 :1 ;	//	:  7ボタン
			bool  b08 :1 ;	//	:  8ボタン
			bool  b09 :1 ;	//	:  9ボタン
			bool  b10 :1 ;	//	: 10ボタン
			bool  b11 :1 ;	//	: 11ボタン
			bool  b12 :1 ;	//	: 12ボタン
			bool  b13 :1 ;	//	: 13ボタン
			bool  b14 :1 ;	//	: 14ボタン
			bool  b15 :1 ;	//	: 15ボタン
			bool  b16 :1 ;	//	: 16ボタン
		};
		BoxCon XConState ;
	//};
public:
	WORD   operator & (const UINT	var) const	{	return this->wButton & var ;	};
	WORD   operator ^ (const WORD	var) const	{	return this->wButton ^ var ;	};
	WORD   operator = (      WORD	var)		{	return this->wButton = var ;	};
	WORD   operator | (const WORD	var) const	{	return this->wButton | var ;	};
	BState operator & (const BState	var) const	{	return BState(this->wButton & var.wButton ) ; };
	BState operator ^ (const BState	var) const	{	return BState(this->wButton ^ var.wButton ) ; };
	BState(){};
	BState(WORD w):wButton(w){};
};

//**************************************************************************//
// struct CUSTOM_CONTROLER_STATE;
// 担当  : 鴫原 徹
// 用途  : コントローラーのステータス
//**************************************************************************//
struct CUSTOM_CONTROLER_STATE
{
	////	: スティックの入力値 
	public:
    SHORT	sThumbLX;				////  : 左スティックのX値【SHORT型】
    SHORT	sThumbLY;				////  : 左スティックのY値【SHORT型】
    SHORT	sThumbRX;				////  : 右スティックのX値【SHORT型】
    SHORT	sThumbRY;				////  : 右スティックのY値【SHORT型】

    ////	: 数値幅変更版[-1,+1]
	public:
    float	fThumbRX;				////  : 右スティックのX値【float型】
    float	fThumbRY;				////  : 右スティックのY値【float型】
    float	fThumbLX;				////  : 左スティックのX値【float型】
    float	fThumbLY;				////  : 左スティックのY値【float型】

	////	: 押されてるボタン
	public:
    BState	wButtons;				////  : 今押されてるボタン
    BYTE	bLeftTrigger;			////  : 左トリガー
    BYTE	bRightTrigger;			////  : 右トリガー
		
	////	: 一フレームのみ有効
	public:
	BState	wPressedButtons;		////  :     ボタンが押され初めてから1フレームめのフラグ
    bool	bPressedLeftTrigger;	////  : 左トリガーが押され初めてから1フレームめのフラグ
    bool	bPressedRightTrigger;	////  : 右トリガーが押され初めてから1フレームめのフラグ

    ////	: 最後に押されたボタンCONTROLER_STATE
	public:
    BState	wLastButtons;			////  : 前回押されたたボタン
    bool	bLastLeftTrigger;		////  : 前回左トリガーが押されてたか
    bool	bLastRightTrigger;		////  : 前回右トリガーが押されてたか

	//	: XINPUT_STATE からのコピー
	CUSTOM_CONTROLER_STATE& operator = (XINPUT_STATE& other){
		sThumbLX      = other.Gamepad.sThumbLX ;
		sThumbLY      = other.Gamepad.sThumbLY ;
		sThumbRX      = other.Gamepad.sThumbRX  ;
		sThumbRY      = other.Gamepad.sThumbRY   ;
		wButtons      = other.Gamepad.wButtons    ;	
		bLeftTrigger  = other.Gamepad.bLeftTrigger ;
		bRightTrigger = other.Gamepad.bRightTrigger ;
		return *this;
	};

};
//**************************************************************************//
// struct CONTROLER_STATE;
// 担当  : 鴫原 徹
// 用途  : コントローラーのステータス
//**************************************************************************//
struct CONTROLER_STATE
{
	CUSTOM_CONTROLER_STATE	Gamepad;
	DWORD					dwPacketNumber;
    bool					bConnected;
};
struct MouseState{
	Point Position;

};
//**************************************************************************
// class CONTROLLERS;
// 担当  : 鴫原 徹
// 用途  : コントローラー
//****************************************************************************/
class CONTROLLERS{
    static const DWORD MAX_CONTROLLERS = 4;
	//CInput CI;
    CONTROLER_STATE m_State[MAX_CONTROLLERS];
	XINPUT_STATE XIStateBuf;
	//CInputGamepad* CIGpBuf;
public:
	//static WPARAM KeyBoardState;
	//static Point  MousePoint;
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当       ：
//// 備考       ：
////            ：
////
    CONTROLLERS(HWND hWnd){
		::ZeroMemory(m_State,sizeof(CONTROLER_STATE));
		//CI.Create( hWnd );
	}
/**************************************************************************
 ~CONTROLLERS();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    ~CONTROLLERS(){}	
/**************************************************************************
 Release();
 用途: 
 戻り値: なし
***************************************************************************/
    void Release(){
		//CI.Release();
		//SAFE_RELEASE(CIGpBuf);
	}
/////////////////// ////////////////////
//// 関数名     ：const CONTROLER_STATE* GetState()
//// カテゴリ   ：ゲッター(?)
//// 用途       ：コントローラーの状態を得る
//// 引数       ：なし
//// 戻値       ：コントローラーのステータス
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
/**************************************************************************
 const CONTROLER_STATE* GetState();
 用途: コントローラーの状態を得る
 戻り値: コントローラーのステータス
***************************************************************************/
    const CONTROLER_STATE* GetState(){
        DWORD dwResult;
        for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
        {

			//CI.InputUpdate();
			//CIGpBuf = CI.Gamepad();
			//{

			//	
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_UP))		m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP		;		
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_DOWN))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN		;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_LEFT))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT		;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_RIGHT))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT	;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_Btn0))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_Y				;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_Btn1))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_B				;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_Btn2))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_X				;
			//	if(CIGpBuf->ChkGamePadDown(GamePadBtn_Btn3))	m_State[i].Gamepad.wButtons |= XINPUT_GAMEPAD_A				;
			//}


			m_State[i].Gamepad.wLastButtons      = m_State[i].Gamepad.wButtons;
			m_State[i].Gamepad.bLastLeftTrigger  = m_State[i].Gamepad.bLeftTrigger  != 0;
			m_State[i].Gamepad.bLastRightTrigger = m_State[i].Gamepad.bRightTrigger != 0;
			m_State[i].Gamepad.wButtons = 0;
            // XInputから在のステータスを得る
            dwResult = XInputGetState( i, &XIStateBuf );

			
		#ifdef DEBUG_KEYBORD_ON
			if( dwResult == ERROR_SUCCESS || i == 0)
		#else
			if( dwResult == ERROR_SUCCESS )
		#endif
			{
				(dwResult != ERROR_SUCCESS) && (ZeroMemory(&XIStateBuf,sizeof(XINPUT_STATE))) && (XIStateBuf.dwPacketNumber = 1) ;
                m_State[i].bConnected		= true;
				m_State[i].dwPacketNumber	= XIStateBuf.dwPacketNumber;
				m_State[i].Gamepad			= XIStateBuf;

				//////////
				//	: レバーのデッドゾーンを設定
				if( abs( m_State[i].Gamepad.sThumbLX ) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE		/3.5f )
					m_State[i].Gamepad.sThumbLX = 0;
				if( abs( m_State[i].Gamepad.sThumbLY ) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE		/3.5f )
					m_State[i].Gamepad.sThumbLY = 0;
				if( abs( m_State[i].Gamepad.sThumbRX ) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE	/3.5f )
					m_State[i].Gamepad.sThumbRX = 0;
				if( abs( m_State[i].Gamepad.sThumbRY ) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE	/3.5f )
					m_State[i].Gamepad.sThumbRY = 0;
				//
				//////////

				//////////
				//	: デバッグ用にキーボードで操作できるようにしてみた
				#ifdef DEBUG_KEYBORD_ON
				if( i == 0 ){
					m_State[i].bConnected		= true;


					m_State[i].Gamepad.wButtons.XConState.UP				|= ( GetAsyncKeyState( VK_UP    ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.DOWN				|= ( GetAsyncKeyState( VK_DOWN  ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.RIGHT				|= ( GetAsyncKeyState( VK_RIGHT ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.LEFT				|= ( GetAsyncKeyState( VK_LEFT  ) != 0 );

					if( m_State[i].Gamepad.sThumbLX			== 0 &&
					   (m_State[i].Gamepad.sThumbLX			= ( GetAsyncKeyState( MYVK_GAMEPAD_STICK_RIGHT  ) != 0 ) ? SHRT_MAX : 0 ) == 0 ){
						m_State[i].Gamepad.sThumbLX			= ( GetAsyncKeyState( MYVK_GAMEPAD_STICK_LEFT   ) != 0 ) ? SHRT_MIN : 0 ;
					}
					if( m_State[i].Gamepad.sThumbLY			== 0 &&
					   (m_State[i].Gamepad.sThumbLY			= ( GetAsyncKeyState( MYVK_GAMEPAD_STICK_UP     ) != 0 ) ? SHRT_MAX : 0 ) == 0 ){
						m_State[i].Gamepad.sThumbLY			= ( GetAsyncKeyState( MYVK_GAMEPAD_STICK_DOWN   ) != 0 ) ? SHRT_MIN : 0 ;
					}

					m_State[i].Gamepad.wButtons.XConState.A					|= ( GetAsyncKeyState( MYVK_GAMEPAD_A ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.B					|= ( GetAsyncKeyState( MYVK_GAMEPAD_B ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.X					|= ( GetAsyncKeyState( MYVK_GAMEPAD_X ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.Y					|= ( GetAsyncKeyState( MYVK_GAMEPAD_Y ) != 0 );

					m_State[i].Gamepad.wButtons.XConState.BACK				|= ( GetAsyncKeyState( MYVK_GAMEPAD_BACK  ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.START				|= ( GetAsyncKeyState( MYVK_GAMEPAD_START ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.LEFT_SHOULDER		|= ( GetAsyncKeyState( MYVK_GAMEPAD_LB    ) != 0 );
					m_State[i].Gamepad.wButtons.XConState.RIGHT_SHOULDER	|= ( GetAsyncKeyState( MYVK_GAMEPAD_RB    ) != 0 );
				}
				#endif
				// 
				//////////

				//////////
				//	: 数値のfloat化
				m_State[i].Gamepad.fThumbLX = (float)m_State[i].Gamepad.sThumbLX / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbLY = (float)m_State[i].Gamepad.sThumbLY / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbRX = (float)m_State[i].Gamepad.sThumbRX / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbRY = (float)m_State[i].Gamepad.sThumbRY / (float)SHRT_MAX;
				//
				//////////

				//////////
				//	: 
				m_State[i].Gamepad.wPressedButtons = (m_State[i].Gamepad.wLastButtons ^ m_State[i].Gamepad.wButtons) & m_State[i].Gamepad.wButtons;

				//Debugger::DBGSTR::addStr( L"\nコントローラー\n" );
				//Debugger::DBGSTR::addStr( L"sThumbLX = %d\n"   , m_State[i].Gamepad.sThumbLX );
				//Debugger::DBGSTR::addStr( L"sThumbLY = %d\n"   , m_State[i].Gamepad.sThumbLY );
				//Debugger::DBGSTR::addStr( L"sThumbRX = %d\n"   , m_State[i].Gamepad.sThumbRX );
				//Debugger::DBGSTR::addStr( L"sThumbRY = %d\n"   , m_State[i].Gamepad.sThumbRY );
				//Debugger::DBGSTR::addStr( L"fThumbLX = %f\n"   , m_State[i].Gamepad.fThumbLX );
				//Debugger::DBGSTR::addStr( L"fThumbLY = %f\n"   , m_State[i].Gamepad.fThumbLY );
				//Debugger::DBGSTR::addStr( L"fThumbRX = %f\n"   , m_State[i].Gamepad.fThumbRX );
				//Debugger::DBGSTR::addStr( L"fThumbRY = %f\n\n" , m_State[i].Gamepad.fThumbRY );

            }
            else{
                m_State[i].bConnected = false;
            }
        }
        return m_State;
    }
/**************************************************************************
 const DWORD getMaxControllers() const;
 用途: コントローラーの最大数を得る
 戻り値: 現バージョンでは定数が返る（4）
***************************************************************************/
    const DWORD getMaxControllers() const{
        return MAX_CONTROLLERS;
    }
};

};