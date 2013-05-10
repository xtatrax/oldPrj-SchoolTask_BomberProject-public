////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FController.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�R���g���[���[�̓ǂݍ��ݓ����Ǘ�����
//					��
//	namespace wiz;
//		class  GAMEPAD ;					//	: [ tatra ] �Q�l�p�ɏE�����\�[�X( ���g�p )
//		struct BState  ;					//	: [ tatra ] XBOX�R���g���[���[�ɑΉ������{�^���̏�Ԃ��i�[����\����	
//		struct CUSTOM_CONTROLER_STATE ;		//	: [ tatra ] XINPUT_STAT���g�������\����
//		struct CONTROLER_STATE ;			//	: [ tatra ] ��̃R���g���[���[�̏����܂Ƃ߂Ă����\����
//		class  CONTROLLERS ;				//	: [ tatra ] �R���g���[���[���Ǘ�����N���X
//



#pragma once
#include "Input.h"

namespace Controller__{
//**************************************************************************//
// class GAMEPAD;
// �p�r: �E����#���m
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
// �S��  : ���� �O
// �p�r  : �R���g���[���[�̃{�^���̏��
//         XBOX�R���g���[���[�Ή��{�^������
//         XBOX�R���g���[���[��O��ɍ��Ȃ�����g��Ȃ��ق����ǂ� (�Ƃ�����
//**************************************************************************//
struct BoxCon{
	bool  UP     :1 ;  //  : �n�b�g�� (01�{�^��)
	bool  DOWN    :1 ;  //  : �n�b�g�� (02�{�^��)
	bool  LEFT     :1 ;  //  : �n�b�g�� (03�{�^��)
	bool  RIGHT	    :1 ;  //  : �n�b�g�� (04�{�^��)
	bool  START	     :1 ;  //  : �X�^�[�g�{�^�� (05�{�^��)
	bool  BACK	      :1 ;  //  : �o�b�N�{�^�� (06�{�^��)
	bool  LEFT_THUMB   :1 ;  //  : ���g���K�[ (07�{�^��)
	bool  RIGHT_THUNB   :1 ;  //  : �E�g���K�[ (08�{�^��)
	bool  LEFT_SHOULDER  :1 ;  //  : ���V�����_�[ (09�{�^��)
	bool  RIGHT_SHOULDER :1 ;  //  : �E�V�����_�[ (10�{�^��)
	bool                 :2 ;  //  : �󂫃r�b�g(11�12�{�^��)
	bool  A             :1 ;  //  : A (13�{�^��)
	bool  B          :1 ;  //  : B (14�{�^��)
	bool  X       :1 ;  //  : X (15�{�^��)
	bool  Y    :1 ;  //  : Y (16�{�^��)
};
//**************************************************************************//
// struct State;
// �S��  : ���� �O
// �p�r  : �R���g���[���[�̃{�^���̏��
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
		// �S��  : ���� �O
		// �p�r  : �R���g���[���[�̃{�^���̏��
		//         �ԍ��ʐ^�U��
		//**************************************************************************//
		struct{
			bool  b01 :1 ;	//	:  1�{�^��
			bool  b02 :1 ;	//	:  2�{�^��
			bool  b03 :1 ;	//	:  3�{�^��
			bool  b04 :1 ;	//	:  4�{�^��
			bool  b05 :1 ;	//	:  5�{�^��
			bool  b06 :1 ;	//	:  6�{�^��
			bool  b07 :1 ;	//	:  7�{�^��
			bool  b08 :1 ;	//	:  8�{�^��
			bool  b09 :1 ;	//	:  9�{�^��
			bool  b10 :1 ;	//	: 10�{�^��
			bool  b11 :1 ;	//	: 11�{�^��
			bool  b12 :1 ;	//	: 12�{�^��
			bool  b13 :1 ;	//	: 13�{�^��
			bool  b14 :1 ;	//	: 14�{�^��
			bool  b15 :1 ;	//	: 15�{�^��
			bool  b16 :1 ;	//	: 16�{�^��
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
// �S��  : ���� �O
// �p�r  : �R���g���[���[�̃X�e�[�^�X
//**************************************************************************//
struct CUSTOM_CONTROLER_STATE
{
	////	: �X�e�B�b�N�̓��͒l 
	public:
    SHORT	sThumbLX;				////  : ���X�e�B�b�N��X�l�ySHORT�^�z
    SHORT	sThumbLY;				////  : ���X�e�B�b�N��Y�l�ySHORT�^�z
    SHORT	sThumbRX;				////  : �E�X�e�B�b�N��X�l�ySHORT�^�z
    SHORT	sThumbRY;				////  : �E�X�e�B�b�N��Y�l�ySHORT�^�z

    ////	: ���l���ύX��[-1,+1]
	public:
    float	fThumbRX;				////  : �E�X�e�B�b�N��X�l�yfloat�^�z
    float	fThumbRY;				////  : �E�X�e�B�b�N��Y�l�yfloat�^�z
    float	fThumbLX;				////  : ���X�e�B�b�N��X�l�yfloat�^�z
    float	fThumbLY;				////  : ���X�e�B�b�N��Y�l�yfloat�^�z

	////	: ������Ă�{�^��
	public:
    BState	wButtons;				////  : ��������Ă�{�^��
    BYTE	bLeftTrigger;			////  : ���g���K�[
    BYTE	bRightTrigger;			////  : �E�g���K�[
		
	////	: ��t���[���̂ݗL��
	public:
	BState	wPressedButtons;		////  :     �{�^���������ꏉ�߂Ă���1�t���[���߂̃t���O
    bool	bPressedLeftTrigger;	////  : ���g���K�[�������ꏉ�߂Ă���1�t���[���߂̃t���O
    bool	bPressedRightTrigger;	////  : �E�g���K�[�������ꏉ�߂Ă���1�t���[���߂̃t���O

    ////	: �Ō�ɉ����ꂽ�{�^��CONTROLER_STATE
	public:
    BState	wLastButtons;			////  : �O�񉟂��ꂽ���{�^��
    bool	bLastLeftTrigger;		////  : �O�񍶃g���K�[��������Ă���
    bool	bLastRightTrigger;		////  : �O��E�g���K�[��������Ă���

	//	: XINPUT_STATE ����̃R�s�[
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
// �S��  : ���� �O
// �p�r  : �R���g���[���[�̃X�e�[�^�X
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
// �S��  : ���� �O
// �p�r  : �R���g���[���[
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
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S��       �F
//// ���l       �F
////            �F
////
    CONTROLLERS(HWND hWnd){
		::ZeroMemory(m_State,sizeof(CONTROLER_STATE));
		//CI.Create( hWnd );
	}
/**************************************************************************
 ~CONTROLLERS();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    ~CONTROLLERS(){}	
/**************************************************************************
 Release();
 �p�r: 
 �߂�l: �Ȃ�
***************************************************************************/
    void Release(){
		//CI.Release();
		//SAFE_RELEASE(CIGpBuf);
	}
/////////////////// ////////////////////
//// �֐���     �Fconst CONTROLER_STATE* GetState()
//// �J�e�S��   �F�Q�b�^�[(?)
//// �p�r       �F�R���g���[���[�̏�Ԃ𓾂�
//// ����       �F�Ȃ�
//// �ߒl       �F�R���g���[���[�̃X�e�[�^�X
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
/**************************************************************************
 const CONTROLER_STATE* GetState();
 �p�r: �R���g���[���[�̏�Ԃ𓾂�
 �߂�l: �R���g���[���[�̃X�e�[�^�X
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
            // XInput����݂̃X�e�[�^�X�𓾂�
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
				//	: ���o�[�̃f�b�h�]�[����ݒ�
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
				//	: �f�o�b�O�p�ɃL�[�{�[�h�ő���ł���悤�ɂ��Ă݂�
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
				//	: ���l��float��
				m_State[i].Gamepad.fThumbLX = (float)m_State[i].Gamepad.sThumbLX / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbLY = (float)m_State[i].Gamepad.sThumbLY / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbRX = (float)m_State[i].Gamepad.sThumbRX / (float)SHRT_MAX;
				m_State[i].Gamepad.fThumbRY = (float)m_State[i].Gamepad.sThumbRY / (float)SHRT_MAX;
				//
				//////////

				//////////
				//	: 
				m_State[i].Gamepad.wPressedButtons = (m_State[i].Gamepad.wLastButtons ^ m_State[i].Gamepad.wButtons) & m_State[i].Gamepad.wButtons;

				//Debugger::DBGSTR::addStr( L"\n�R���g���[���[\n" );
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
 �p�r: �R���g���[���[�̍ő吔�𓾂�
 �߂�l: ���o�[�W�����ł͒萔���Ԃ�i4�j
***************************************************************************/
    const DWORD getMaxControllers() const{
        return MAX_CONTROLLERS;
    }
};

};