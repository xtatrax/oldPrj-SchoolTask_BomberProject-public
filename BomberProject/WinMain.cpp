////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：WinMain.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：エントリーポイント
//					▼中間
//	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
//
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"

int nDefaultShowCmd ;
HINSTANCE _hInstance ;
class MouseUtilityCushion{
public:
	static void setMouseLB( bool Bool ){ wiz::Cursor2D::m_bMouseLB = Bool ; }
	static void setMouseRB( bool Bool ){ wiz::Cursor2D::m_bMouseRB = Bool ; }
	static void setMouseMB( bool Bool ){ wiz::Cursor2D::m_bMouseMB = Bool ; }

};
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
			#if defined( CF_DEBUGINFORMATIONWINDOW_ENABLE )
				Debugger::DebugWindow::init(_hInstance,hWnd,nDefaultShowCmd);
			#endif
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
		case WM_LBUTTONDOWN		:	MouseUtilityCushion::setMouseLB( true )			;	break ;
		case WM_RBUTTONDOWN		:	MouseUtilityCushion::setMouseRB( true )			;	break ;
		case WM_MBUTTONDOWN		:	MouseUtilityCushion::setMouseMB( true )			;	break ;
		case WM_LBUTTONUP		:	MouseUtilityCushion::setMouseLB( false )		;	break ;
		case WM_RBUTTONUP		:	MouseUtilityCushion::setMouseRB( false )		;	break ;
		case WM_MBUTTONUP		:	MouseUtilityCushion::setMouseMB( false )		;	break ;
		case WM_LBUTTONDBLCLK	:	break;
		case WM_RBUTTONDBLCLK	:	break;
		case WM_MBUTTONDBLCLK	:	break;

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
	_hInstance = hInstance ;
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
    wcex.hIcon          = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));                     //アイコンの指定（ここではNULL）
    wcex.hCursor        = NULL;    //通常の矢印カーソル
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
		// DEVMODE    devMode;
		wiz::DxDevice::m_hWnd = ::CreateWindowEx( 
            WS_EX_ACCEPTFILES,  //オプションのウィンドウスタイル
            pClassName,         // 登録されているクラス名
            pWndTitle,          // ウインドウ名
            WS_POPUP,           // ウインドウスタイル（ポップアップウインドウを作成）
            0,                  // ウインドウの横方向の位置
            0,                  // ウインドウの縦方向の位置
			(int)STANDARD_WINDOW_WIDTH,       // フルスクリーンウインドウの幅
            (int)STANDARD_WINDOW_HEIGHT,      // フルスクリーンウインドウの高さ
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
		//devMode.dmPelsWidth  = BASE_CLIENT_WIDTH;
		//devMode.dmPelsHeight = BASE_CLIENT_HEIGHT;

		//ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);

    }
    else {
        //ウインドウの作成
		wiz::DxDevice::m_hWnd = ::CreateWindowEx(
            0,                              //オプションのウィンドウスタイル
            pClassName,                     //ウインドウクラス名
            pWndTitle,                      //ウインドウのタイトル
            WS_OVERLAPPED | WS_SYSMENU,            //移動バーをもつ通常のウインドウ
            100,
			100,							//
            iClientWidth,					//ウインドウ幅（暫定）
            iClientHeight,					//ウインドウ高さ（暫定）
            NULL,							//親ウインドウ（トップレベルなので、なし）
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
	SetCapture(wiz::DxDevice::m_hWnd);
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
		ReleaseCapture();

		//Debugger::DBGWRITINGLOGTEXT::addStr(L"ゲームシステム終了処理開始");
		SafeDelete( device );
		ShowCursor(true);
		//wiz::TextureManager::Release();
#if defined( CF_MEMORYMANAGER_ENABLE )
		TMemoryManager::Clear();
#endif
		_CrtDumpMemoryLeaks();
		::PostQuitMessage(0);
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
