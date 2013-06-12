////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：WinMain.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：エントリーポイント
//					▼
//	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"

int nDefaultShowCmd ;
HINSTANCE hInstance ;
/**************************************************************************
LRESULT CALLBACK WindowProc(
HWND hWnd,      //ウィンドウハンドル
UINT msg,       //メッセージ
WPARAM wParam,  //メッセージの最初のパラメータ
LPARAM lParam   //メッセージの2番目のパラメータ
)
用途: ウインドウプロシージャ
戻り値: メッセージ処理結果
***************************************************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_CREATE:
			DragAcceptFiles(hWnd,TRUE); // D&D を許可する
			Debugger::DebugWindow::init(hInstance,hWnd,nDefaultShowCmd);
			return 0;
        case WM_CLOSE:                // ウインドウが破棄されようとしている
			wiz::DxDevice::Destroy();
            return 0;
        break;
		case WM_DESTROY:
			
			break ;
        case WM_KEYDOWN: 
			// キーが押された
			if (wParam == VK_ESCAPE) {  // 押されたのはESCキーだ
				wiz::DxDevice::Destroy();  // ウインドウを破棄するよう要求する
			}
			if (wParam == (VK_MENU | VK_RETURN)) { 
            }
            return 0;
        break;
        case WM_ACTIVATEAPP:
            if( wParam == TRUE )   XInputEnable( true );
            else                   XInputEnable( false );
            return 0;
        case WM_SIZING:
			wiz::__GetClientSize(*((wiz::Rect*)lParam));
			wiz::DxDevice::setClientRect(*((wiz::Rect*)lParam));
            return 0;
		case WM_DROPFILES: // ファイルがドロップされた
			TCHAR szDropFile[MAX_PATH + 1];
			DragQueryFile((HDROP)wParam,0,szDropFile,MAX_PATH);

			// 構造体のハンドルで使ったメモリを解放する
			DragFinish((HDROP)wParam);
			return 0;
        default:
        break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
/**************************************************************************
 関数名:int WINAPI WinMain(
        HINSTANCE hInstance,            //インスタンスのハンドル
        HINSTANCE hPrevInstance,        //以前のインスタンス
        LPSTR lpCmdLine,                //コマンドライン
        int nShowCmd                    //起動時の状態
        );
 用途: エントリポイント。
 戻り値: 終了コード
****************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE 
    hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	nDefaultShowCmd = nShowCmd ;
	hInstance = hInstance ;
	setlocale( LC_CTYPE, "jpn" );
	time_t timer;
	struct tm local ;

    /* 現在時刻を取得 */
    timer = time(NULL);

    localtime_s(&local ,&timer); /* 地方時に変換 */

    /* 地方時 変換後表示 */
    printf("地方時: ");
    printf("%4d/", local.tm_year + 1900);
    printf("%2d/", local.tm_mon + 1);
    printf("%2d ", local.tm_mday);
    printf("%2d:", local.tm_hour);
    printf("%2d:", local.tm_min);
    printf("%2d", local.tm_sec);
    printf(" %d\n", local.tm_isdst);

	Debugger::DBGWRITINGLOGTEXT::Init();
	Debugger::DBGWRITINGLOGTEXT::addStr(L" 最終起動 \n");
	Debugger::DBGWRITINGLOGTEXT::addStr(L" ローカル時間 %4d/%2d/%2d %2d:%2d:%2d %d \n",
		local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
		local.tm_min, local.tm_sec, local.tm_isdst);
    //定数
    const wchar_t* pClassName = DEFAULT_WINDOW_CLASS_NAME;
    const wchar_t* pWndTitle  = DEFAULT_WINDOW_TITLE;
    //ウインドウの幅と高さ
    int iClientWidth  = (int)STANDARD_WINDOW_WIDTH;
    int iClientHeight = (int)STANDARD_WINDOW_HEIGHT;
    // フルスクリーンにするかどうかの判定
    // コマンドラインに/fか/Fが設定されていたらフルスクリーンにする
#ifdef CF_FULLSCREEN
    bool isFullScreen = true;
#else
    bool isFullScreen = false;
#endif
    for(int i = 0; i < nShowCmd; i++) {
        if(_stricmp((char*)&lpCmdLine[i], "/f") == 0) { // コマンドラインに/fを発見
            isFullScreen = true;     // フラグをtrueに設定
            break;
        }
    }
	//WNDCLASSEX構造体の初期化
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
    wcex.lpszClassName  = pClassName;               //クラス名の指定
    wcex.hIconSm        = NULL;                     //小さいアイコンなし
    //ウインドウクラスの登録
    if (!::RegisterClassEx(&wcex))
    {
        //失敗した
        ::MessageBox(NULL,L"ウインドウクラス登録に失敗しました",L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    // ウィンドウの作成
    if(isFullScreen) { // フルスクリーン
		//DEVMODE    devMode;
		//ShowCursor(DRAW_MOUSE);
        // 画面全体の幅と高さを取得
        //iClientWidth = ::GetSystemMetrics(SM_CXSCREEN);
        //iClientHeight = ::GetSystemMetrics(SM_CYSCREEN);
        wiz::DxDevice::m_hWnd = ::CreateWindowEx( 
            WS_EX_ACCEPTFILES,  //オプションのウィンドウスタイル
            pClassName,         // 登録されているクラス名
            pWndTitle,          // ウインドウ名
            WS_POPUP,           // ウインドウスタイル（ポップアップウインドウを作成）
            0,                  // ウインドウの横方向の位置
            0,                  // ウインドウの縦方向の位置
            (int)BASE_CLIENT_WIDTH,       // フルスクリーンウインドウの幅
            (int)BASE_CLIENT_HEIGHT,      // フルスクリーンウインドウの高さ
            NULL,               // 親ウインドウのハンドル（なし）
            NULL,               // メニューや子ウインドウのハンドル
            hInstance,          // アプリケーションインスタンスのハンドル
            NULL                // ウインドウの作成データ
        );
        if (!wiz::DxDevice::m_hWnd){
            //失敗した
            ::MessageBox(0,L"ウインドウ作成に失敗しました",L"エラー",MB_OK);
            return 1;   //エラー終了
        }
		//devMode.dmSize       = sizeof(DEVMODE);
		//devMode.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		//devMode.dmPelsWidth  = (DWORD)BASE_CLIENT_WIDTH;
		//devMode.dmPelsHeight = (DWORD)BASE_CLIENT_HEIGHT;

		//ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);


    }
    else {
        //ウインドウの作成
		wiz::DxDevice::m_hWnd = ::CreateWindowEx(
            0,                              //オプションのウィンドウスタイル
            pClassName,                     //ウインドウクラス名
            pWndTitle,                      //ウインドウのタイトル
            WS_OVERLAPPEDWINDOW,            //移動バーをもつ通常のウインドウ
            CW_USEDEFAULT, CW_USEDEFAULT,   //位置はWindowsに任せる
            iClientWidth,                    //ウインドウ幅（暫定）
            iClientHeight,                   //ウインドウ高さ（暫定）
            NULL,                            //親ウインドウ（トップレベルなので、なし）
            NULL,                           //メニューなし
            hInstance,                      //このインスタンス
            NULL                            //使用しない
        );
        if (!wiz::DxDevice::m_hWnd){
            //失敗した
            ::MessageBox(0,L"ウインドウ作成に失敗しました",L"エラー",MB_OK);
            return 1;   //エラー終了
        }
        // ウィンドウサイズを再設定する
        RECT rect;
        int w_width,w_height,c_width,c_height;
        // ウインドウ全体の大きさを計算
        ::GetWindowRect(wiz::DxDevice::m_hWnd,&rect);       // ウインドウ全体のサイズ取得
        w_width = rect.right - rect.left;   // ウインドウ全体の幅の横幅を計算
        w_height = rect.bottom - rect.top;  // ウインドウ全体の幅の縦幅を計算
        // クライアント領域の大きさを計算
        ::GetClientRect(wiz::DxDevice::m_hWnd,&rect);       // クライアント部分のサイズの取得
        c_width = rect.right - rect.left;   // クライアント領域外の横幅を計算
        c_height = rect.bottom - rect.top;  // クライアント領域外の縦幅を計算
        // ウィンドウサイズの再計算
        w_width = iClientWidth + (w_width - c_width);     // 必要なウインドウの幅
        w_height = iClientHeight + (w_height - c_height); // 必要なウインドウの高さ
        // ウインドウサイズの再設定
        ::SetWindowPos(wiz::DxDevice::m_hWnd,HWND_TOP,0,0,w_width,w_height,SWP_NOMOVE);
    }
	ShowCursor(DRAW_MOUSE);
	wiz::__GetClientSize(wiz::Rect(0,0,iClientWidth,iClientHeight));
	wiz::DxDevice::setClientRect(wiz::Rect(0,0,iClientWidth,iClientHeight));

    //ウインドウの表示
    ::ShowWindow(
        wiz::DxDevice::m_hWnd,       //取得したウインドウのハンドル
        nShowCmd    //WinMainに渡されたパラメータ
    );
    // WM_PAINTが呼ばれないようにする
    ::ValidateRect(wiz::DxDevice::m_hWnd, 0);
    //例外処理開始
    try{
		/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		// 
        // DirectXデバイスオブジェクトの初期化
        wiz::DxDevice* device = new wiz::DxDevice(isFullScreen,iClientWidth,iClientHeight);
		int ret =  (int) device->MainThreadRun();
		SafeDelete( device );
		::PostQuitMessage(0);
		ShowCursor(true);
		//wiz::TextureManager::Release();
#if defined( CF_MEMORYMANAGER_ENABLE )
		TMemoryManager::Clear();
#endif
		return ret ;
		/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
	}
    catch(wiz::BaseException& e){
        //初期化失敗した
        ::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    catch(exception& e){
        //STLエラー
        //マルチバイトバージョンのメッセージボックスを呼ぶ
        ::MessageBoxA(wiz::DxDevice::m_hWnd,e.what(),"エラー",MB_OK);
        return 1;   //エラー終了
    }
    catch(...){
        //原因不明失敗した
        ::MessageBox(wiz::DxDevice::m_hWnd,L"原因不明のエラーです",L"エラー",MB_OK);
        return 1;   //エラー終了
    }
    //例外処理終了
	//COMコンポーネントのリリース
	::CoUninitialize();
    return 1;   //エラー終了
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//// ChildWindow.cpp
////
//// リージョンの結合
//
//#include <windows.h>
//
//
//#define BUTTON_ID   1000
//#define CHILD_ID_A  5000
//#define CHILD_ID_B  5001
//#define BUTTON_ID_OPEN_A 6000
//#define BUTTON_ID_OPEN_B 6001
//
//
//
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK ChildWindowProc(HWND , UINT , WPARAM , LPARAM );
//ATOM InitApp(HINSTANCE);
//HWND InitInstance(HINSTANCE, int);
//HINSTANCE hInst;
//
//TCHAR szClassName[] = _T("ParentWindow"); // ウィンドウクラス。UNICODEとしての文字列定数
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,int nShowCmd)
//{
//   MSG msg;
//   BOOL bRet;
//   HWND hWnd;
//
//   hInst = hInstance;
//
//   if (!InitApp(hInstance))
//       return FALSE;
//   if (!(hWnd = InitInstance(hInstance,nShowCmd)))
//       return FALSE;
//   while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
//       if (bRet == -1){
//           break;
//       } else {
//           TranslateMessage(&msg);
//           DispatchMessage(&msg);
//       }
//   }
//   return (int)msg.wParam;
//}
//
//// ウィンドウクラスの登録
//
//ATOM InitApp(HINSTANCE hInst)
//{
//   WNDCLASS wc;
//   wc.style        = CS_HREDRAW|CS_VREDRAW;
//   wc.lpfnWndProc  = WndProc;  // プロシージャ名
//   wc.cbClsExtra   = 0;
//   wc.cbWndExtra   = 0;
//   wc.hInstance    = hInst;
//   wc.hIcon        = NULL;     // 未サポート
//   wc.hCursor      = NULL;     // 未サポート
//   wc.hbrBackground= (HBRUSH) COLOR_WINDOW;
//   wc.lpszMenuName = NULL;     // 未サポート
//   wc.lpszClassName=(LPCTSTR) szClassName;
//
//   return (RegisterClass(&wc));
//}
//
//// ウィンドウの生成
//HWND InitInstance(HINSTANCE hInst, int nShowCmd)
//{
//   HWND hWnd;
//
//   hWnd = CreateWindow(
//       szClassName,_T("ChildWindowサンプル"),
//       WS_CLIPCHILDREN,    // ウィンドウの種類
//       CW_USEDEFAULT,      // x座標
//       CW_USEDEFAULT,      // y座標
//       CW_USEDEFAULT,      // 幅
//       CW_USEDEFAULT,      // 高さ
//       NULL,               // 親ウィンドウのハンドル。親を作るのでNULL
//       NULL,               // メニューハンドルまたは子ウィンドウID
//       hInst,              // インスタンスハンドル
//       NULL);
//   if (!hWnd)
//       return FALSE;
//   ShowWindow(hWnd, nShowCmd);
//   UpdateWindow(hWnd);
//   return hWnd;
//}
//// ウィンドウクラスの登録
//void CreateWindowClass(HINSTANCE hInst, LPCTSTR szClassName, WNDCLASSW &wc)
//{
//   wc.style  = CS_HREDRAW|CS_VREDRAW;
//   wc.lpfnWndProc = ChildWindowProc ; // プロシージャ名
//   wc.cbClsExtra = 0;
//   wc.cbWndExtra = 0;
//   wc.hInstance = hInst;
//   wc.hIcon  = NULL;
//   wc.hCursor  = NULL;
//   wc.hbrBackground= reinterpret_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)); //グレーにする
//   wc.lpszMenuName = NULL;  // 未サポート
//   wc.lpszClassName=(LPCWSTR) szClassName;
//}
//
//// 子ウィンドウの生成
//HWND CreateChildWindow(HINSTANCE hInst, int nShowCmd,LPTSTR ClassName,HMENU hMenuChildId,HWND hParent)
//{
//   HWND hWnd;
//
//   // 親ウィンドウのサイズを取得
//   RECT rect;
//   GetWindowRect(hParent, (LPRECT)&rect);
//
//   hWnd = CreateWindow(
//       ClassName,
//       NULL,
//       WS_CHILD,
//       0,                      //親ウィンドウと同じサイズ
//       0,
//       rect.right - rect.left,
//       rect.bottom - rect.top,
//       hParent,        //親ウィンドウのハンドル
//       (HMENU)hMenuChildId,    // 子ウィンドウを判別するためのID
//       hInst,          //インスタンスハンドル
//       NULL);
//   if (!hWnd)
//       return FALSE;
//   ShowWindow(hWnd, nShowCmd);
//   UpdateWindow(hWnd);
//   return hWnd;
//}
//// ウィンドウプロシージャ
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//   PAINTSTRUCT ps;
//   HDC hdc;
//
//   TCHAR buf[256];
//   size_t size;        // 文字列のサイズを格納する
//
//   WNDCLASSW wc_A;
//   WNDCLASSW wc_B;
//   static HWND hChildWnd_A;
//   static HWND hChildWnd_B;
//
//   static HWND hButton;
//
//   switch (msg){
//       case WM_CREATE:
//
//           // 子ウィンドウＡの生成
//           CreateWindowClass(hInst,_T("ChildWindow_A"),wc_A);
//           RegisterClassW(&wc_A);
//           hChildWnd_A = CreateChildWindow(hInst,SW_HIDE,_T("ChildWindow_A"),(HMENU)CHILD_ID_A,hWnd);
//
//           // 子ウィンドウＢの生成
//           CreateWindowClass(hInst,_T("ChildWindow_B"),wc_B);
//           RegisterClassW(&wc_B);
//           hChildWnd_B = CreateChildWindow(hInst,SW_HIDE,_T("ChildWindow_B"),(HMENU)CHILD_ID_B,hWnd);
//
//           // プッシュボタンを作成する
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // ウィンドウクラス名
//               _T("OPEN A"),                            // キャプション
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // スタイル指定
//               50, 50,                                  // 座標
//               60, 40,                                  // サイズ
//               hWnd,                                    // 親ウィンドウのハンドル
//               (HMENU)BUTTON_ID_OPEN_A,                 // メニューハンドル
//               hInst,                                   // インスタンスハンドル
//               NULL                                     // その他の作成データ
//               );
//
//           // プッシュボタンを作成する
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // ウィンドウクラス名
//               _T("OPEN B"),                            // キャプション
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // スタイル指定
//               50, 100,                                 // 座標
//               60, 40,                                  // サイズ
//               hWnd,                                    // 親ウィンドウのハンドル
//               (HMENU)BUTTON_ID_OPEN_B,                 // メニューハンドル
//               hInst,                                   // インスタンスハンドル
//               NULL                                     // その他の作成データ
//               );
//
//           break;
//       case WM_COMMAND:
//           GetClassName(hWnd, buf, 255);
//           NKDbgPrintfW(_T("%s\n"),buf);
//           switch(LOWORD(wp) ){
//           case BUTTON_ID_OPEN_A:
//               // 親ウィンドウの「OPEN_A」ボタン押下時の処理
//               // 子ウィンドウＡを表示する
//               ShowWindow(hChildWnd_A,SW_SHOW);
//               UpdateWindow(hChildWnd_A);
//
//               return (DefWindowProc(hWnd, msg, wp, lp));
//               break;
//           case BUTTON_ID_OPEN_B:
//               // 親ウィンドウの「OPEN_B」ボタン押下時の処理
//               // 子ウィンドウＢを表示する
//               ShowWindow(hChildWnd_B,SW_SHOW);
//               UpdateWindow(hChildWnd_B);
//
//               return (DefWindowProc(hWnd, msg, wp, lp));
//               break;
//
//           case BUTTON_ID:
//               // 子ウィンドウの「CLOSE」ボタン押下字の処理
//               if( IsWindowVisible(hChildWnd_A) ){
//                   ShowWindow(hChildWnd_A,SW_HIDE);
//               }else{
//                   ShowWindow(hChildWnd_B,SW_HIDE);
//               }
//
//               break;
//           default:
//               return (DefWindowProc(hWnd, msg, wp, lp));
//           }
//
//           break;
//       case WM_PAINT:
//           hdc = BeginPaint(hWnd,&ps);     // 描画処理を開始します。
//
//           SetBkMode(hdc, TRANSPARENT);    // 背景を透過モードにします
//
//           GetClassName(hWnd, buf, 255);   // クラス名を取得
//
//           StringCchLength(buf,255,&size); // 文字列長の取得
//
//           ExtTextOut(
//               hdc,    // デバイスコンテキストのハンドル
//               0,      // 開始位置（基準点）の x 座標
//               20,     // 開始位置（基準点）の y 座標
//               NULL,   // 長方形領域の使い方のオプション
//               NULL,   // 長方形領域の入った構造体へのポインタ
//               buf,    // 文字列
//               size,   // 文字数
//               NULL    // 文字間隔の入った配列
//               );
//
//           EndPaint(hWnd,&ps);             // 描画処理を終了します。
//
//           break;
//       case WM_DESTROY:
//           PostQuitMessage(0);
//           break;
//       default:
//           return (DefWindowProc(hWnd, msg, wp, lp));
//   }
//   return 0;
//}
//
//
//
//LRESULT CALLBACK ChildWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//   PAINTSTRUCT ps;
//   HWND hButton;
//   HDC hdc;
//   COLORREF bkColor;
//   TCHAR buf[256];
//   size_t size;        // 文字列のサイズを格納する
//
//
//   switch (msg){
//       case WM_CREATE:
//           // プッシュボタンを作成する
//           hButton = CreateWindow(
//               _T("BUTTON"),                            // ウィンドウクラス名
//               _T("CLOSE"),                             // キャプション
//               WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // スタイル指定
//               100, 200,                                // 座標
//               60, 40,                                  // サイズ
//               hWnd,                                    // 親ウィンドウのハンドル
//               (HMENU)BUTTON_ID,                        // メニューハンドル
//               hInst,                                   // インスタンスハンドル
//               NULL                                     // その他の作成データ
//               );
//           break;
//       case WM_PAINT:
//           hdc = BeginPaint(hWnd,&ps);     // 描画処理を開始します。
//
//           SetBkMode(hdc, TRANSPARENT);    // 背景を透過モードにします
//
//           GetClassName(hWnd, buf, 255);   // クラス名を取得
//
//           StringCchLength(buf,255,&size); // 文字列長の取得
//
//           ExtTextOut(
//               hdc,    // デバイスコンテキストのハンドル
//               0,      // 開始位置（基準点）の x 座標
//               20,     // 開始位置（基準点）の y 座標
//               NULL,   // 長方形領域の使い方のオプション
//               NULL,   // 長方形領域の入った構造体へのポインタ
//               buf,    // 文字列
//               size,   // 文字数
//               NULL    // 文字間隔の入った配列
//               );
//
//           EndPaint(hWnd,&ps);
//
//           break;
//       case WM_COMMAND:
//           GetClassName(hWnd, buf, 255);
//           NKDbgPrintfW(_T("%s\n"),buf);
//           switch(LOWORD(wp) ){
//           case BUTTON_ID:
//
//               // 親ウィンドウへメッセージ伝播。処理は親に任せる。
//               SendMessage(GetParent(hWnd),msg,wp,lp);
//
//               // 自ウィンドウを非表示にする
//               //ShowWindow(hWnd,SW_HIDE);
//               //UpdateWindow(hWnd);
//
//               break;
//           default:
//               return (DefWindowProc(hWnd, msg, wp, lp));
//           }
//
//           break;
//       case WM_DESTROY:
//           PostQuitMessage(0);
//           break;
//       default:
//           return (DefWindowProc(hWnd, msg, wp, lp));
//   }
//   return 0;
//}
//
