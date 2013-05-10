////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�C�X���Ǘ����܂�
//					�F�Q�[�����[�v�͊eThreadRun�֐��̒��ɒ�`����Ă��܂�
//					�Fstdafx.h ���� ON_DEBUGGINGPROCESS ��define���邱�Ƃ�
//					�FUpdate/Render/Draw�X���b�h�𕪂��邱�Ƃ��ł��܂�
//					�F��WinMain�֐�����Ă΂�܂�
//					��
//	namespace wiz;
//		class DxDevice;
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Object.h"
#include "Scene.h"
#include <process.h>

namespace wiz{
bool GameQuitFlag = false ;
/**************************************************************************
 DxDevice ��`��
***************************************************************************/
Rect		DxDevice::m_WindowRect;		// �Q�[���̕`��͈͂̑傫����\����`
D3DXVECTOR2	DxDevice::m_v2AspectRate  ;		// ��𑜓x�ƌ��݂̉𑜓x�̔䗦
HWND		DxDevice::m_hWnd			= NULL;		// ���C���E�C���h�E�̃n���h��
HANDLE		DxDevice::m_hUpdateThread	= NULL;		// �A�b�v�f�[�g�p�X���b�h�̃n���h��
HANDLE		DxDevice::m_hLoadingThread	= NULL;		// ���[�h��ʗp�X���b�h�̃n���h��
/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //�E�C���h�E�̃n���h��
    bool isFullScreen,  //�t���X�N���[�����ǂ���
    int Width,          //�̈�̕�
    int Height          //�̈�̍���
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B���s�������O��throw
***************************************************************************/
void DxDevice::initDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
{
    try{
		m_pD3D         = NULL;
		m_pD3DDevice   = NULL;
		m_pController  = NULL;
		m_hWnd		   = hWnd;
        D3DDISPLAYMODE d3ddm;
        // Direct3D9�I�u�W�F�N�g�̍쐬
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
            throw BaseException(
                L"DirectX�̏������Ɏ��s���܂����BDirectX�C���^�[�t�F�C�X���擾�ł��܂���B",
                L"DxDevice::DxDevice()"
                );
        }
        
        // ���݂̃f�B�X�v���C���[�h���擾
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
            throw BaseException(
                L"�f�o�C�X�̏������Ɏ��s���܂����B�f�B�X�v���C���[�h���擾�ł��܂���B",
                L"DxDevice::DxDevice()"
                );
        }

        // �f�o�C�X�̃v���[���e�[�V�����p�����[�^��������
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        if(isFullScreen) { // �t���X�N���[���̏ꍇ
            m_D3DPP.Windowed                = FALSE;            // �t���X�N���[���\���̎w��
            m_D3DPP.BackBufferWidth         = Width;            // �t���X�N���[�����̉���
            m_D3DPP.BackBufferHeight        = Height;           // �t���X�N���[�����̏c��
        }
        else {
            m_D3DPP.Windowed                = TRUE;             // �E�C���h�E���\���̎w��
        }
        m_D3DPP.BackBufferFormat        = d3ddm.Format;         // �J���[���[�h�̎w��
        m_D3DPP.SwapEffect              = D3DSWAPEFFECT_DISCARD; 
        m_D3DPP.EnableAutoDepthStencil  = TRUE;
        m_D3DPP.AutoDepthStencilFormat  = D3DFMT_D24S8;
        
        // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
        // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                        D3DDEVTYPE_HAL, 
                                        hWnd, 
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING, 
                                        &m_D3DPP, &m_pD3DDevice))) {
            // ��L�̐ݒ肪���s������
            // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                            D3DDEVTYPE_HAL, 
                                            hWnd, 
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                            &m_D3DPP, &m_pD3DDevice))) {
                // ��L�̐ݒ肪���s������
                // �`��ƒ��_������CPU�ōs�Ȃ�
                if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                                D3DDEVTYPE_REF, hWnd, 
                                                D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                                &m_D3DPP, &m_pD3DDevice))) {
                    // ���������s
                    throw BaseException(
                        L"�f�o�C�X�̏������Ɏ��s���܂����B�I�m�ȃf�o�C�X���擾�ł��܂���B",
                        L"DxDevice::DxDevice()"
                        );
                }
            }
        }
        m_pController = new CONTROLLERS(hWnd);
		Debugger::DBGSTR::Init(m_pD3DDevice);
    }
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 void DxDevice::Clear();
 �p�r: �I�u�W�F�N�g�̃N���A
 �߂�l: �Ȃ�
***************************************************************************/
void DxDevice::Clear(){
    //�R���g���[���[�̊J��
    SafeRelease(m_pController);
    // �f�o�C�X�I�u�W�F�N�g�̉��
    SafeRelease(m_pD3DDevice);
    // DirectXGraphics�̉��
    SafeRelease(m_pD3D);
	// �V�[���̍폜
	SafeDelete(pScene);
}
/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //�E�C���h�E�̃n���h��
    bool isFullScreen,  //�t���X�N���[�����ǂ���
    int Width,          //�̈�̕�
    int Height          //�̈�̍���
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B���s�������O��throw
***************************************************************************/
DxDevice::DxDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
 : m_pD3D(0), m_pD3DDevice(0),m_pController(0)
 , m_PrgState(PROGRAM_RUNNUNG),pScene(NULL)
{
    try{
		m_hWnd = hWnd ;
		initDevice(hWnd,isFullScreen,Width,Height);
		//�V�[���̏�����
        pScene = new Scene(getDevice());

	}
	catch(wiz::BaseException& e){
		//�j������
        Clear();
		//�ăX���[
        throw BaseException(
				e.what_w(), 
                L"��DxDevice::DxDevice()"
                );
	}
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 DxDevice::~DxDevice();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
DxDevice::~DxDevice(){
    //�I�u�W�F�N�g�̔j��
    Clear();
}
/**************************************************************************
 LPDIRECT3DDEVICE9 DxDevice::getDevice();
 �p�r: �f�o�C�X�̎擾
 �߂�l: IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^�B���s������0
***************************************************************************/
LPDIRECT3DDEVICE9 DxDevice::getDevice(){
    return m_pD3DDevice;
}
/////////////////// ////////////////////
//// �֐���     �Fint MainThreadRun()
//// �J�e�S��   �F�֐�
//// �p�r       �F��PostQuitMessage()���Ă΂ꂽ���̏��������s
//// ����       �F����
//// �ߒl       �F�Ȃ�
//// ���l       �F
////            �F
////
void DxDevice::End(){
#ifndef CF_SINGLETHREAD
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	//	: �V���O���X���b�h���[�h����Ȃ�������
	//	: �A�b�v�f�[�g�p�X���b�h���N���[�Y����
	CloseHandle(m_hUpdateThread);
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
#endif
	m_PrgState = PROGRAM_END;
};
/////////////////// ////////////////////
//// �֐���     �Fint MainThreadRun()
//// �J�e�S��   �F�֐�
//// �p�r       �F���C���X���b�h�́[�v
//// ����       �F����
//// �ߒl       �Fint
//// ���l       �F
////            �F
////
int DxDevice::MainThreadRun(){
 	Tempus2 mainFTime;
	m_DrawPacket.pTime = &mainFTime;

	#ifndef CF_SINGLETHREAD
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		//	: �V���O���X���b�h���錾����Ă��Ȃ��ꍇ
		//	: �A�b�v�f�[�g�X���b�h�𐶐�����
		StartUpdateThread();
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	#else
		m_UpdatePacket.pTime = &mainFTime;
	#endif 


	MSG msg;    //���b�Z�[�W�\���̂̐錾��`
	//	: ���C���X���b�h���[�v
	while(true){
        if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            switch(msg.message){ 
				case WM_QUIT:// PostQuitMessage()���Ă΂ꂽ
	 				End();
					break;
				case WM_DROPFILES: // �t�@�C�����h���b�v���ꂽ
					TCHAR szDropFile[MAX_PATH + 1];
					DragQueryFile((HDROP)msg.wParam,0,szDropFile,MAX_PATH);

					// �\���̂̃n���h���Ŏg�������������������
					DragFinish((HDROP)msg.wParam);
					break;
				case WM_LBUTTONDOWN :
					g_bMouseLB = true;
					break ; 
				case WM_LBUTTONUP:
					g_bMouseLB = false;
					break;
				case WM_RBUTTONDOWN :
					g_bMouseRB = true;
					break ;
				case WM_RBUTTONUP:
					g_bMouseRB = false;
					break;

				default:
	                // ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					break;
            }
        }
        else {  // �������郁�b�Z�[�W�������Ƃ��͕`����s��
			mainFTime.TimeUpdate();
			#ifdef CF_SINGLETHREAD
			/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
				//	: �V���O���X���b�h�錾������Ă�����
				//	: �����ŃV�[���̃A�b�v�f�[�g������

				UpdateScene();
			/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
			#endif
			// �E�B���h�E�������Ă��鎞�����`�悷�邽�߂̏���
            WINDOWPLACEMENT wndpl;
            ::GetWindowPlacement(m_hWnd, &wndpl); // �E�C���h�E�̏�Ԃ��擾
            if((wndpl.showCmd != SW_HIDE) && 
                (wndpl.showCmd != SW_MINIMIZE) &&
                (wndpl.showCmd != SW_SHOWMINIMIZED) &&
                (wndpl.showCmd != SW_SHOWMINNOACTIVE)) {
                // �`�揈���̎��s
                RenderScene();
            }

        }
		if(m_PrgState == PROGRAM_END){
			::WaitForSingleObject( m_hUpdateThread , INFINITE );
			SAFE_DELETE( pScene );
			break;
		}
    }

	return (int) msg.wParam;
}
/////////////////// ////////////////////
//// �֐���     �Fvoid UpdateThreadRun()
//// �J�e�S��   �F�֐�
//// �p�r       �F�V�[���̃A�b�v�f�[�g�p�X���b�h�̃��[�v
//// ����       �F����
//// �ߒl       �Fint
//// ���l       �F�V���O���X���b�h�錾������ꍇ�͂��̊֐��͎��s����Ȃ�
////            �F
////
int DxDevice::UpdateThreadRun(){
	TLIB::Tempus::Tempus();
	Tempus2 updateFTime;
	m_UpdatePacket.pTime = &updateFTime ;

	MSG msg;    //���b�Z�[�W�\���̂̐錾��`
	//���b�Z�[�W���[�v
    while(true){
		g_bMouseLB = false ;
		g_bMouseRB = false ;

		if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            switch(msg.message){ 
				case WM_QUIT:// PostQuitMessage()���Ă΂ꂽ
	 				End();
					break;
				case WM_DROPFILES: // �t�@�C�����h���b�v���ꂽ
					TCHAR szDropFile[MAX_PATH + 1];
					DragQueryFile((HDROP)msg.wParam,0,szDropFile,MAX_PATH);

					// �\���̂̃n���h���Ŏg�������������������
					DragFinish((HDROP)msg.wParam);
					break;
				default:
	                // ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					break;
            }
		}else{
			updateFTime.TimeUpdate();
			UpdateScene();
		}
    }
	return 0;
}
/**************************************************************************
 void DxDevice::UpdateScene(
 Scene* pScene  // �V�[���ւ̃|�C���^
 );
 �p�r: �V�[���̕`��
 �߂�l: �Ȃ�
***************************************************************************/
void DxDevice::UpdateScene()
{
    try{
		if(!pScene){
			//�V�[���������Ȃ�X���[
			throw BaseException(
				L"�V�[����������܂���B",
				L"DxDevice::RenderScene()"
				);
		}
		if(m_pController){
			m_UpdatePacket.pCntlState = m_pController->GetState();
		}
		m_UpdatePacket.pD3DDevice	= m_pD3DDevice	;
		m_UpdatePacket.pCommand		= &m_Com		;
		m_RenderPacket.pD3DDevice	= m_pD3DDevice	;
		m_RenderPacket.pCommand		= &m_Com		;
		#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS) 

		#endif
		pScene->Update(m_UpdatePacket);
		pScene->Render(m_RenderPacket);

		#ifndef CF_SINGLETHREAD 
			//	: �}���`�X���b�h���[�h�̏ꍇ
			//	: �x�~���N�G�X�g������Ύ����̃X���b�h���x�~����
			if(pScene->getUpdateThreadSuspendRequest()){
				pScene->setUpdateThreadSuspend();	//	: �X���b�h�̒�~��ʒm
				SuspendThread(m_hUpdateThread);		//	: �A�b�v�f�[�g�X���b�h���ꎞ��~
				//	: �O������ĊJ����������܂�
				pScene->setUpdateThreadResume();	//	: �X���b�h���ĊJ�������Ƃ�ʒm
			}
		#endif
	}
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 void DxDevice::RenderScene(
 Scene* pScene  // �V�[���ւ̃|�C���^
 );
 �p�r: �V�[���̕`��
 �߂�l: �Ȃ�
***************************************************************************/
void DxDevice::RenderScene()
{
    try{
		if(!pScene){
			//�V�[���������Ȃ�X���[
			throw BaseException(
				L"�V�[����������܂���B",
				L"DxDevice::RenderScene()"
				);
		}
		// �r���[�|�[�g�Ɛ[�x�o�b�t�@�̏������ƃX�e���V���o�b�t�@�̃N���A
		if(FAILED(m_pD3DDevice->Clear(0,NULL,               // ����������̈�͑S��
						D3DCLEAR_STENCIL |                  // �X�e���V���o�b�t�@���w��
						D3DCLEAR_TARGET |                   // �o�b�N�o�b�t�@���w��
						D3DCLEAR_ZBUFFER,                   // �[�x�o�b�t�@�iZ�o�b�t�@�j���w��
						D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f),  // ����������F
						1.0f,                               // ����������[�x�o�b�t�@�iZ�o�b�t�@�j�̒l
						0))){                               // ����������X�e���V���o�b�t�@�̒l
			//���s������X���[
			throw BaseException(
				L"�o�b�t�@���N���A�ł��܂���B",
				L"DxDevice::RenderScene()"
				);
		}
		// �`��J�n�錾
		if(SUCCEEDED(m_pD3DDevice->BeginScene())) {

			m_DrawPacket.pD3DDevice	= m_pD3DDevice ;
			m_DrawPacket.pCommand	= &m_Com ;

			pScene->Draw(m_DrawPacket);///**************************

			Debugger::DBGSTR::Draw();
			TMemoryManager::Draw();
			// �`��I���錾
			m_pD3DDevice->EndScene();
		}

		// �`�挋�ʂ̓]��
		if(FAILED(m_pD3DDevice->Present( 0, 0, 0, 0 ))) {
			// �f�o�C�X�������畜�A
			if(m_pD3DDevice->Reset(&m_D3DPP)!= D3D_OK){
				//�f�o�C�X�̕��A�Ɏ��s������X���[
				throw BaseException(
					L"�f�o�C�X�𕜋A�ł��܂���B",
					L"DxDevice::RenderScene()"
					);
			}
		}
		if(pScene->getUpdateThreadResumeRequest()){
			ResumeThread(m_hUpdateThread);
			pScene->setUpdateThreadResume();
		}
		//�^�C�~���O�����킹��
		//::Sleep(10);
    }
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
void DxDevice::StartUpdateThread(){
	m_hUpdateThread = (HANDLE) _beginthreadex(
		NULL,
		0,
		&DxDevice::updateThreadLauncher,	// �����`�����N��
		this,
		0,
		NULL);

}
unsigned __stdcall DxDevice::updateThreadLauncher(void *args){
	reinterpret_cast<DxDevice*>(args)->UpdateThreadRun();
	return 0;
}

}
//end of namespace wiz.

