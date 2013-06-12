////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：DebugWindowMain.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバッグ情報表示用ウインドウ
//					▼
//	namespace TLIB;
//

#include "stdafx.h"
#include "DebugWindowMain.h"

namespace Debugger{

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case 0:
        default:
        break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}


DebugWindow* DebugWindow::m_pMyInstance = NULL ;

DebugWindow::DebugWindow(HINSTANCE hInstance, HWND i_hParentWindow, int nShowCmd)
	:m_pClassName( RCTEXT_DEBUGWINDOWCLASSNAME )
	,m_pWndTitle(  RCTEXT_DEBUGWINDOWTITLE     )
{
	try{
		////////// /////////
		// 
		//	: WNDCLASSEX構造体の初期化
		//
		WNDCLASSEX wcex;
		wcex.cbSize         = sizeof(WNDCLASSEX);       //この構造体のサイズ
		wcex.style          = 0;                        //自動的にredrawをかけない
		wcex.lpfnWndProc    = WindowProc;               //ウインドウプロシージャ（コールバック関数）の指定
		wcex.cbClsExtra     = 0;                        //常に0
		wcex.cbWndExtra     = 0;                        //常に0
		wcex.hInstance      = hInstance;                //アプリケーションのインスタンスを指定
		wcex.hIcon          = NULL;                     //アイコンの指定（ここではNULL）
		wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);    //通常の矢印カーソル
		wcex.hbrBackground  = NULL;                      //背景なし
		wcex.lpszMenuName   = NULL;                     //メニューなし
		wcex.lpszClassName  = m_pClassName;               //クラス名の指定
		wcex.hIconSm        = NULL;                     //小さいアイコンなし
		//ウインドウクラスの登録
		if (!::RegisterClassEx(&wcex))
		{
			//失敗した
			::MessageBox(NULL,L"子ウインドウクラス登録に失敗しました",L"エラー",MB_OK);
			return ;   //エラー終了
		}
		// 
		//	: WNDCLASSEX構造体の初期化
		//
		////////// /////////

		////////// /////////
		// 
		//	: ウインドウの作成
		//
		m_hWnd = ::CreateWindow(
			m_pClassName,						//ウインドウクラス名
			m_pWndTitle,						//ウインドウのタイトル
			WS_CHILD,							//WS_THICKFRAME
			CW_USEDEFAULT,						// 
			CW_USEDEFAULT,						//位置はWindowsに任せる
			(int)STANDARD_WINDOW_WIDTH,			//ウインドウ幅（暫定）
			(int)STANDARD_WINDOW_HEIGHT,		//ウインドウ高さ（暫定）
			i_hParentWindow,								//親ウインドウ（トップレベルなので、なし）
			(HMENU)1,							//メニューなし
			hInstance,							//このインスタンス
			NULL								//使用しない
		);
		if (!m_hWnd){
			//失敗した
			::MessageBox(0,L"子ウインドウ作成に失敗しました",L"エラー",MB_OK);
			return ;   //エラー終了
		}
		// 
		//	: ウインドウの作成
		//
		////////// /////////

		//ウインドウの表示
		::ShowWindow(
			m_hWnd,       //取得したウインドウのハンドル
			nShowCmd    //WinMainに渡されたパラメータ
		);

		m_pD3D         = NULL;
		m_pD3DDevice   = NULL;
        D3DDISPLAYMODE d3ddm;
        // Direct3D9オブジェクトの作成
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
			::MessageBox(0,
                L"子ウインドウで\nDirectXの初期化に失敗しました。DirectXインターフェイスが取得できません。",
                L"DxDevice::DxDevice()",
				MB_OK
                );
        }
        
        // 現在のディスプレイモードを取得
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
			::MessageBox(0,
                L"子ウインドウで\n子ウインドウで\n初期化に失敗しました。ディスプレイモードを取得できません。",
                L"DxDevice::DxDevice()",
				MB_OK
                );
        }

        // デバイスのプレゼンテーションパラメータを初期化
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        m_D3DPP.Windowed                = TRUE;             // ウインドウ内表示の指定
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
				::MessageBox(0,
					L"子ウインドウで\nデバイスの初期化に失敗しました。的確なデバイスを取得できません。",
					L"DxDevice::DxDevice()",
					MB_OK
					);
                }
            }
        }

	}
	catch(...){
		throw;
	}
}

}//end of namespace Debugger.