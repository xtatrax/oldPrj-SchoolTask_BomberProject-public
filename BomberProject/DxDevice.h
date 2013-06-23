////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�C�X���Ǘ����܂�
//					�F�Q�[�����[�v�͊eThreadRun�֐��̒��ɒ�`����Ă��܂�
//					�Fstdafx.h ���� ON_DEBUGGINGPROCESS ���f�t�@�C����`���邱�Ƃ�
//					�F�}���`�X���b�h�������ł��܂�( ���ݗL���ɂ���ƃv���C���[�̏�
//					�F�Ƃ̏Փ˔���ŃA�N�Z�X�ᔽ���������܂� )
//					�F��WinMain�֐�����Ă΂�܂�
//					��
//	namespace wiz;
//		class DxDevice;
//
#pragma once
 
#include "StdAfx.h"
#include "Object.h"
#include "Controller/Controller.h"
using namespace TLIB;
namespace wiz{
extern bool GameQuitFlag ;
namespace system{
/**************************************************************************
 �ˑ�����N���X
****************************************************************************/
class Scene;

/**************************************************************************
 class DxDevice;
 �p�r: DirectX�f�o�C�X�N���X
****************************************************************************/
class DxDevice {
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//	: ����J�ϐ�+��
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
private:
	LPDIRECT3D9				m_pD3D			;	// IDirect3D9�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DPRESENT_PARAMETERS	m_D3DPP			;	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	CONTROLLERS				m_Controller	;	// �R���g���[���̃|�C���^
	Command					m_Com			;	// �R�}���h
	UpdatePacket			m_UpdatePacket	;	// �A�b�v�f�[�g�X���b�h�̏����ɗ����f�[�^�Q
	RenderPacket			m_RenderPacket	;	// �����_�[�X���b�h�̏����ɗ����f�[�^�Q
	DrawPacket				m_DrawPacket	;	// �h���[�X���b�h�̏����ɗ����f�[�^�Q
	Scene*					pScene			;	// 
	static bool				m_bDestroy		;	//
	static bool				m_bOnPlaySound	;	//
	static Rect				m_WindowRect	;	// �Q�[���̕`��͈͂̑傫����\����`
	static D3DXVECTOR2		m_v2AspectRate	;		// ��𑜓x�ƌ��݂̉𑜓x�̔䗦
	static HANDLE			m_hUpdateThread		;	// �A�b�v�f�[�g�p�X���b�h�̃n���h��
	static HANDLE			m_hLoadingThread	;	// ���[�h��ʗp�X���b�h�̃n���h��
	enum ProgramState{
		PROGRAM_RUNNUNG,
		PROGRAM_ENDTHREAD,
		PROGRAM_END,
	}m_PrgState;

public:

	static HWND				m_hWnd				;	// ���C���E�C���h�E�̃n���h��

private:
/////////////////// ////////////////////
//// �֐���     �Fvoid initDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
//// �J�e�S��   �F�C�j�V�����C�U
//// �p�r       �F�v���O�����Ŏg���f�o�C�X��������
//// ����       �F  HWND hWnd,          //�E�C���h�E�̃n���h��
////            �F  bool isFullScreen,  //�t���X�N���[�����ǂ���
////            �F  int Width,          //�̈�̕�
////            �F  int Height          //�̈�̍���
//// �ߒl       �F����
//// ���l       �F
////            �F
////
    void initDevice(bool isFullScreen,int Width,int Height);




/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//	: ���J�֐�
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
public:
/**************************************************************************
 void Clear();
 �p�r: �I�u�W�F�N�g�̃N���A
 �߂�l: �Ȃ�
***************************************************************************/
    void Clear();
/**************************************************************************
 DxDevice(
    HWND hWnd,          //�E�C���h�E�̃n���h��
    bool isFullScreen,  //�t���X�N���[�����ǂ���
    int Width,          //�̈�̕�
    int Height          //�̈�̍���
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    DxDevice(bool isFullScreen,int Width,int Height);
/**************************************************************************
 ~DxDevice();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~DxDevice();
/**************************************************************************
 LPDIRECT3DDEVICE9 getDevice();
 �p�r: �f�o�C�X�̎擾
 �߂�l: IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^�B���s������0
***************************************************************************/
    LPDIRECT3DDEVICE9 getDevice();
/////////////////// ////////////////////
//// �֐���     �Fvoid End()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�Q�[���̏I����錾
//// ����       �F����
//// �ߒl       �Fint
//// ���l       �F�X���b�h�̏I�������Ƃ�
////            �F
////
	void End();
/////////////////// ////////////////////
//// �֐���     �Fint MainThreadRun()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F���C���X���b�h�́[�v
//// ����       �F����
//// �ߒl       �Fint
//// ���l       �F
////            �F
////
	int MainThreadRun();
	static Rect getClientRect(){return m_WindowRect;}
	static void setClientRect(Rect i_Rect){
		m_WindowRect = i_Rect;
		m_v2AspectRate   = D3DXVECTOR2( i_Rect.right / BASE_CLIENT_WIDTH , i_Rect.bottom / BASE_CLIENT_HEIGHT );
	}
	static D3DXVECTOR2 getAspectRate(){return m_v2AspectRate;}
/////////////////// ////////////////////
//// �֐���     �Fstatic HWND getGameWindowHandle()
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F�Q�[����ʂ�`�悵�Ă�E�C���h�E�̃n���h����Ԃ�
//// ����       �F����
//// �ߒl       �F
//// ���l       �F
////            �F
////
	static HWND getGameWindowHandle(){return m_hWnd;};
/////////////////// ////////////////////
//// �֐���     �Fstatic HANDLE getUpdateThreadHandle()
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F�A�b�v�f�[�g�p�X���b�h�̃n���h����Ԃ�
//// ����       �F����
//// �ߒl       �F
//// ���l       �F�V���O���X���b�h���[�h�̏ꍇ��NULL��Ԃ�
////            �F
////
	static HANDLE getUpdateThreadHandle(){return m_hUpdateThread;};
/////////////////// ////////////////////
//// �֐���     �Fstatic HANDLE getLoadingThreadHandle()
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F���[�h��ʗp�X���b�h�̃n���h����Ԃ�
//// ����       �F����
//// �ߒl       �F
//// ���l       �F�V���O���X���b�h���[�h�̏ꍇ��NULL��Ԃ�
////            �F
////
	static HANDLE getLoadingThreadHandle(){return m_hLoadingThread;};

/////////////////// ////////////////////
//// �֐���     �Fstatic bool getIsPlaySound() ;
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F�������Đ������邩�ǂ�����Ԃ�
//// ����       �F�Ȃ���
//// �ߒl       �F true  : �Đ�
////            �F false : ��~
//// ���l       �F
////            �F
////
	static bool getIsPlaySound(){return m_bOnPlaySound;};

/////////////////// ////////////////////
//// �֐���     �Fstatic bool getSwitchingSoundOnOff()
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F������ON��OFF��؂�ւ���
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// ���l       �F
////            �F
////
	static void SwitchingSoundOnOff(){ m_bOnPlaySound ? m_bOnPlaySound = false : m_bOnPlaySound = true ; } ;

/////////////////// ////////////////////
//// �֐���     �Fvoid Destroy()
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	static void Destroy(){	m_bDestroy = true ; };

/////////////////// ////////////////////
//// �֐���     �Fvoid EndUpdateThread()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h���I������
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	// static void Destroy(){	m_bDestroy = true ; };

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//	: ����J�֐�
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
private:
/////////////////// ////////////////////
//// �֐���     �Fvoid UpdateThreadRun()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h�̃��[�v
//// ����       �F����
//// �ߒl       �Fint
//// ���l       �F
////            �F
////
	int UpdateThreadRun();

/////////////////// ////////////////////
//// �֐���     �Fvoid UpdateScene()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�֘A�̉��Z
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	void UpdateScene();

/////////////////// ////////////////////
//// �֐���     �Fstatic void __cdecl updateThreadLauncher(void* args)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[����`�悷��
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	void RenderScene();

/////////////////// ////////////////////
//// �֐���     �Fvoid StartUpdateThread()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h���J�n����
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	void StartUpdateThread();

/////////////////// ////////////////////
//// �֐���     �Fstatic void __cdecl updateThreadLauncher(void* args)
//// �J�e�S��   �F�ÓI�����o�֐�
//// �p�r       �F�V�����X���b�h���J�n���邽�߂̋�
//// ����       �Fvoid* args	//	: �������X�g
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	static unsigned __stdcall updateThreadLauncher(void* args);

/////////////////// ////////////////////
//// �֐���     �Fvoid EndUpdateThread()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h���I������
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
	void EndUpdateThread();
/////////////////// ////////////////////
//// �֐���     �Fvoid EndUpdateThread()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h���I������
//// ����       �F����
//// �ߒl       �F����
//// ���l       �F
////            �F
////
};
}
//end of namespace system.
using namespace system;
}
//end of namespace wiz.

