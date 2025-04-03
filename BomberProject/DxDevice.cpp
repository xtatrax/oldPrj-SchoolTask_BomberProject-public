////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：DxDevice.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：デバイスを管理します
//					：ゲームループは各ThreadRun関数の中に定義されています
//					：stdafx.h 内に ON_DEBUGGINGPROCESS をdefineすることで
//					：Update/Render/Drawスレッドを分けることができます
//					：★WinMain関数から呼ばれます
//					▼
//	namespace wiz;
//		class DxDevice;
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Object.h"
#include "Scene.h"
#include <process.h>

namespace wiz{
/**************************************************************************
 DxDevice 定義部
***************************************************************************/
Rect		DxDevice::m_WindowRect		;		// ゲームの描画範囲の大きさを表す矩形
D3DXVECTOR2	DxDevice::m_v2AspectRate	;		// 基準解像度と現在の解像度の比率
HWND		DxDevice::m_hWnd			= NULL	;		// メインウインドウのハンドル
HANDLE		DxDevice::m_hUpdateThread	= NULL	;		// アップデート用スレッドのハンドル
HANDLE		DxDevice::m_hLoadingThread	= NULL	;		// ロード画面用スレッドのハンドル
bool		DxDevice::m_bDestroy		= false	;
bool		DxDevice::m_bOnPlaySound	= true	;

/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //ウインドウのハンドル
    bool isFullScreen,  //フルスクリーンかどうか
    int Width,          //領域の幅
    int Height          //領域の高さ
);
 用途: コンストラクタ
 戻り値: なし。失敗したら例外をthrow
***************************************************************************/
void DxDevice::initDevice(bool isFullScreen,int Width,int Height)
{
    try{
		m_pD3D         = NULL;
		m_pD3DDevice   = NULL;
        D3DDISPLAYMODE d3ddm;
        // Direct3D9オブジェクトの作成
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
            throw BaseException(
                L"DirectXの初期化に失敗しました。DirectXインターフェイスが取得できません。",
                L"DxDevice::DxDevice()"
                );
        }
        
        // 現在のディスプレイモードを取得
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
            throw BaseException(
                L"デバイスの初期化に失敗しました。ディスプレイモードを取得できません。",
                L"DxDevice::DxDevice()"
                );
        }

        // デバイスのプレゼンテーションパラメータを初期化
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        if(isFullScreen) { // フルスクリーンの場合
            m_D3DPP.Windowed                = FALSE;            // フルスクリーン表示の指定
            m_D3DPP.BackBufferWidth         = Width;            // フルスクリーン時の横幅
            m_D3DPP.BackBufferHeight        = Height;           // フルスクリーン時の縦幅
        }
        else {
            m_D3DPP.Windowed                = TRUE;             // ウインドウ内表示の指定
        }
        m_D3DPP.BackBufferFormat        = d3ddm.Format;         // カラーモードの指定
        m_D3DPP.SwapEffect              = D3DSWAPEFFECT_DISCARD; 
        m_D3DPP.EnableAutoDepthStencil  = TRUE;
        m_D3DPP.AutoDepthStencilFormat  = D3DFMT_D24S8;
        
        // ディスプレイアダプタを表すためのデバイスを作成
        // 描画と頂点処理をハードウェアで行なう
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                        D3DDEVTYPE_HAL, 
                                        m_hWnd, 
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING, 
                                        &m_D3DPP, &m_pD3DDevice))) {
            // 上記の設定が失敗したら
            // 描画をハードウェアで行い、頂点処理はCPUで行なう
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                            D3DDEVTYPE_HAL, 
                                            m_hWnd, 
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                            &m_D3DPP, &m_pD3DDevice))) {
                // 上記の設定が失敗したら
                // 描画と頂点処理をCPUで行なう
                if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                                D3DDEVTYPE_REF, m_hWnd, 
                                                D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                                &m_D3DPP, &m_pD3DDevice))) {
                    // 初期化失敗
                    throw BaseException(
                        L"デバイスの初期化に失敗しました。的確なデバイスを取得できません。",
                        L"DxDevice::DxDevice()"
                        );
                }
            }
        }
		const static UINT n = m_pD3D->GetAdapterCount();
		D3DCAPS9 cap ;
		m_pD3D->GetDeviceCaps( n, D3DDEVTYPE_HAL, &cap);
		//SafeDeleteArr( cap );
        m_Controller = CONTROLLERS(m_hWnd);
		Debugger::DBGSTR::Init(m_pD3DDevice);
    }
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 void DxDevice::Clear();
 用途: オブジェクトのクリア
 戻り値: なし
***************************************************************************/
void DxDevice::Clear(){

	// デバイスオブジェクトの解放
    SafeRelease(m_pD3DDevice);
	// シーンの削除
	SafeDelete(pScene);
    // DirectXGraphicsの解放
    SafeRelease(m_pD3D);
}
/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //ウインドウのハンドル
    bool isFullScreen,  //フルスクリーンかどうか
    int Width,          //領域の幅
    int Height          //領域の高さ
);
 用途: コンストラクタ
 戻り値: なし。失敗したら例外をthrow
***************************************************************************/
DxDevice::DxDevice(bool isFullScreen,int Width,int Height)
 : m_pD3D(0), m_pD3DDevice(0)
 , m_PrgState(PROGRAM_RUNNUNG),pScene(NULL)
 , m_Controller(m_hWnd)
{
    try{
		m_Com.Clear();
		initDevice(isFullScreen,Width,Height);
		//シーンの初期化
        pScene = new Scene(getDevice(),&m_Com);

	}
	catch(wiz::BaseException& e){
		//破棄処理
        Clear();
		//再スロー
        throw BaseException(
				e.what_w(), 
                L"↑DxDevice::DxDevice()"
                );
	}
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 DxDevice::~DxDevice();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
DxDevice::~DxDevice(){
    //オブジェクトの破棄
    this->Clear();
}
/**************************************************************************
 LPDIRECT3DDEVICE9 DxDevice::getDevice();
 用途: デバイスの取得
 戻り値: IDirect3DDevice9インターフェイスへのポインタ。失敗したら0
***************************************************************************/
LPDIRECT3DDEVICE9 DxDevice::getDevice(){
    return m_pD3DDevice;
}
/////////////////// ////////////////////
//// 関数名     ：int MainThreadRun()
//// カテゴリ   ：関数
//// 用途       ：メPostQuitMessage()が呼ばれた時の処理を実行
//// 引数       ：なし
//// 戻値       ：なし
//// 備考       ：
////            ：
////
void DxDevice::End(){
//#ifndef CF_SINGLETHREAD
///*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//	//	: シングルスレッドモードじゃなかったら
//	//	: アップデート用スレッドをクローズする
//	CloseHandle(m_hUpdateThread);
///*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//#endif
	m_PrgState = PROGRAM_END;
};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆                                                             ★*☆*★*/
/*★*☆                    アイドリングループ                       ★*☆*★*/
/*★*☆                                                             ★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/////////////////// ////////////////////
//// 関数名     ：int MainThreadRun()
//// カテゴリ   ：関数
//// 用途       ：メインスレッドのープ
//// 引数       ：なし
//// 戻値       ：int
//// 備考       ：
////            ：
////
int DxDevice::MainThreadRun(){
 	Tempus2 mainFTime;
	m_DrawPacket.m_pTime = &mainFTime;

	#ifndef CF_SINGLETHREAD
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		//	: シングルスレッドが宣言されていない場合
		//	: アップデートスレッドを生成する
		StartUpdateThread();
	/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
	#else
		m_UpdatePacket.m_pTime = &mainFTime;
	#endif 


	MSG msg;    //メッセージ構造体の宣言定義
	//	: メインスレッドループ
	while(true){

		if( !this ){
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"DxDevice::MainThreadRun メインゲームループで this が ぬるぽじょうほうををキャッチしちゃいました><、");
			::MessageBox(0,L"システム的異常が発生しました。",L"エラー",MB_OK);
			return 1;
		}
		if( m_bDestroy ){
			#ifndef CF_SINGLETHREAD
				CloseHandle(m_hUpdateThread);
			#endif
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"デバイスの破棄の開始");
			this->Clear();
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"デバイスの破棄の完了");
			DestroyWindow(m_hWnd);
			return 0;
		}

		//	: メセージ解決
		//	: またわ
		//	: シーンの描画
		if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            switch(msg.message){ 

				#ifdef CF_SINGLETHREAD
				/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
					//	: シングルスレッド宣言がされていたら
					//	: ここでマウスの状態を獲得する
				case WM_LBUTTONDOWN		:	Cursor2D::m_bMouseLB = true		;	break ; 
				case WM_RBUTTONDOWN		:	Cursor2D::m_bMouseRB = true		;	break ;
				case WM_MBUTTONDOWN		:	Cursor2D::m_bMouseMB = true		;	break ;
				case WM_LBUTTONUP		:	Cursor2D::m_bMouseLB = false	;	break ;
				case WM_RBUTTONUP		:	Cursor2D::m_bMouseRB = false	;	break ;
				case WM_MBUTTONUP		:	Cursor2D::m_bMouseMB = false	;	break ;
				case WM_LBUTTONDBLCLK	:	break;
				case WM_RBUTTONDBLCLK	:	break;
				case WM_MBUTTONDBLCLK	:	break;

				/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
				#endif

				default:
	                // メッセージの翻訳とディスパッチ
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					break;
            }
        }
        else {  // 処理するメッセージが無いときは描画を行う
			mainFTime.TimeUpdate();
			#ifdef CF_SINGLETHREAD
			/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
				//	: シングルスレッド宣言がされていたら
				//	: ここでシーンのアップデートをする

				UpdateScene();
			/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
			#endif
			// ウィンドウが見えている時だけ描画するための処理
            WINDOWPLACEMENT wndpl;
            ::GetWindowPlacement(m_hWnd, &wndpl); // ウインドウの状態を取得
            if((wndpl.showCmd != SW_HIDE) && 
                (wndpl.showCmd != SW_MINIMIZE) &&
                (wndpl.showCmd != SW_SHOWMINIMIZED) &&
                (wndpl.showCmd != SW_SHOWMINNOACTIVE)) {
                // 描画処理の実行
                RenderScene();
            }

        }
    }
	m_DrawPacket.m_pTime = NULL;
	#ifdef CF_SINGLETHREAD
		m_UpdatePacket.m_pTime = NULL;
	#endif 
	return (int) msg.wParam;
}
/////////////////// ////////////////////
//// 関数名     ：void UpdateThreadRun()
//// カテゴリ   ：関数
//// 用途       ：シーンのアップデート用スレッドのループ
//// 引数       ：なし
//// 戻値       ：int
//// 備考       ：シングルスレッド宣言がある場合はこの関数は実行されない
////            ：
////
int DxDevice::UpdateThreadRun(){
	TLIB::Tempus::Tempus();
	Tempus2 updateFTime;
	m_UpdatePacket.m_pTime = &updateFTime ;

	MSG msg;    //メッセージ構造体の宣言定義
	//メッセージループ
    while(true){


		if(::PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            switch(msg.message){ 
				case WM_LBUTTONDOWN	:	Cursor2D::m_bMouseLB = true		;	break ; 
				case WM_RBUTTONDOWN :	Cursor2D::m_bMouseRB = true		;	break ;
				case WM_MBUTTONDOWN	:	Cursor2D::m_bMouseMB = true		;	break ;
				case WM_LBUTTONUP	:	Cursor2D::m_bMouseLB = false	;	break ;
				case WM_RBUTTONUP	:	Cursor2D::m_bMouseRB = false	;	break ;
				case WM_MBUTTONUP	:	Cursor2D::m_bMouseMB = false	;	break ;

				//	:  削除
				default:
	                // メッセージの翻訳とディスパッチ
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					break;
            }
		}else{
			updateFTime.TimeUpdate();
			UpdateScene();
		}
    }
	m_UpdatePacket.m_pTime = NULL ;
	return 0;
}

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆                                                             ★*☆*★*/
/*★*☆                      シーンアクセス                         ★*☆*★*/
/*★*☆                                                             ★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/**************************************************************************
 void DxDevice::UpdateScene(
 Scene* pScene  // シーンへのポインタ
 );
 用途: シーンの描画
 戻り値: なし
***************************************************************************/
void DxDevice::UpdateScene()
{
    try{
		if(!pScene){
			//シーンが無効ならスロー
			throw BaseException(
				L"シーンが見つかりません。",
				L"DxDevice::RenderScene()"
				);
		}
		m_UpdatePacket.m_pCntlState	= m_Controller.GetState();
		m_UpdatePacket.m_pD3DDevice	= m_pD3DDevice	;
		m_UpdatePacket.m_pCommand	= &m_Com		;

		//m_RenderPacket.pD3DDevice	= m_pD3DDevice	;
		//m_RenderPacket.pCommand		= &m_Com		;

		pScene->Update(m_UpdatePacket);
		//pScene->Render(m_RenderPacket);

		#ifndef CF_SINGLETHREAD 
			//	: マルチスレッドモードの場合
			//	: 休止リクエストがあれば自分のスレッドを休止する
			if(pScene->getUpdateThreadSuspendRequest()){
				pScene->setUpdateThreadSuspend();	//	: スレッドの停止を通知
				SuspendThread(m_hUpdateThread);		//	: アップデートスレッドを一時停止
				//	: 外部から再開処理が来るまで
				pScene->setUpdateThreadResume();	//	: スレッドが再開したことを通知
			}
		#endif
	}
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 void DxDevice::RenderScene(
 Scene* pScene  // シーンへのポインタ
 );
 用途: シーンの描画
 戻り値: なし
***************************************************************************/
void DxDevice::RenderScene()
{
    try{
		if(!pScene){
			//シーンが無効ならスロー
			throw BaseException(
				L"シーンが見つかりません。",
				L"DxDevice::RenderScene()"
				);
		}
		// ビューポートと深度バッファの初期化とステンシルバッファのクリア
		if(FAILED(m_pD3DDevice->Clear(0,NULL,               // 初期化する領域は全面
						D3DCLEAR_STENCIL |                  // ステンシルバッファを指定
						D3DCLEAR_TARGET |                   // バックバッファを指定
						D3DCLEAR_ZBUFFER,                   // 深度バッファ（Zバッファ）を指定
						D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),  // 初期化する色
						1.0f,                               // 初期化する深度バッファ（Zバッファ）の値
						0))){                               // 初期化するステンシルバッファの値
			//失敗したらスロー
			throw BaseException(
				L"バッファをクリアできません。",
				L"DxDevice::RenderScene()"
				);
		}
		// 描画開始宣言
		if(SUCCEEDED(m_pD3DDevice->BeginScene())) {

			m_DrawPacket.m_pD3DDevice	= m_pD3DDevice ;
			m_DrawPacket.m_pCommand		= &m_Com ;

			pScene->Draw(m_DrawPacket);///**************************

			Debugger::DBGSTR::Draw();
#if defined( CF_MEMORYMANAGER_ENABLE )
			TMemoryManager::Draw();
#endif
			// 描画終了宣言
			m_pD3DDevice->EndScene();
		}

		// 描画結果の転送
		if(FAILED(m_pD3DDevice->Present( 0, 0, 0, 0 ))) {
			// デバイス消失から復帰
			if(m_pD3DDevice->Reset(&m_D3DPP)!= D3D_OK){
				//デバイスの復帰に失敗したらスロー
				throw BaseException(
					L"デバイスを復帰できません。",
					L"DxDevice::RenderScene()"
					);
			}
		}

		pScene->CommandTranslator(m_DrawPacket);

#ifndef CF_SINGLETHREAD 
		if(pScene->getUpdateThreadResumeRequest()){
			ResumeThread(m_hUpdateThread);
			pScene->setUpdateThreadResume();
		}
#endif
		//タイミングをあわせる
		//::Sleep(10);
    }
	catch(exception& e){
		
        Clear();
        //再スロー
        throw e;
	}
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }






}
void DxDevice::StartUpdateThread(){
	m_hUpdateThread = (HANDLE) _beginthreadex(
		NULL,
		0,
		&DxDevice::updateThreadLauncher,	// ランチャを起動
		this,
		0,
		NULL);

}
unsigned __stdcall DxDevice::updateThreadLauncher(void *args){
	//reinterpret_cast<DxDevice*>(args)->UpdateThreadRun();
	return 0;
}

}
//end of namespace wiz.

