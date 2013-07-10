////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library_DirectX
//	ファイル名		：DebugFunctions.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバッグ用関数群
//					▼
//	namespace wiz;
//		class DBGSTR ;
//		class DBGWRITINGLOGTEXT ;
//
#ifndef TLIBDEBUGGER_STRINGS
#define TLIBDEBUGGER_STRINGS
#include "StdAfx.h"
namespace Debugger{
//************************************************//
//class DBGWRITINGLOGTEXT
//
// 担当者  : 鴫原 徹
// 目的    : ログファイルを出力する関数群
//************************************************//
class DBGWRITINGLOGTEXT{
	static wstring DefaultLogFolder ;
	static wstring DefaultLogFileName; 
public:
	static void OutputSystemLog(LPCWSTR i_sOutPutString){
		OutputDebugStringW(i_sOutPutString);
	}
	/////////////////// ////////////////////
	//// 関数名     ：static void Init()
	//// カテゴリ   ：イニシャライザ
	//// 用途       ：ファイルの初期化
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：必ずこの関数か､同名の別の関数を最初に一回だけ呼んでください
	////            ：
	////･････････････
	////======== サンプル ========
	//// void main(){
	////
	////     // ※本関数
	////     DBGWRITINGLOGTEXT::Init();   // クラスの初期化
	////
	////     while( boolean ){
	////
	//// ～～～～～～～～～～～～
	//// ～～～～～～～～～～～～
	////
	////         if( foo ){
	////
	////             DBGWRITINGLOGTEXT::addStr( "追記したい文字列\n %s" , "付随のパラメータ" );
	////
	////         }
	////     }
	//// }
	////
	static void Init(){
		if(PathFileExists(DefaultLogFileName.c_str())){
			_wremove( DefaultLogFileName.c_str() );
		}
	}

	/////////////////// ////////////////////
	//// 関数名     ： static void Init(wstring FileName)
	//// カテゴリ   ： イニシャライザ
	//// 用途       ： 出力先ファイルの変更と初期化
	//// 引数       ：    wstring FileName    // ログファイルの名前を指定
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ： 必ずこの関数か､同名の別の関数を最初に一回だけ呼んでください
	////            ：
	////･････････････
	////======== サンプル ========
	//// void main( void ){
	////
	////     // ※本関数
	////     DBGWRITINGLOGTEXT::Init( L"保存するファイル名" );   // クラスの初期化
	////
	////     while( boolean ){
	////
	//// ～～～～～～～～～～～～
	//// ～～～～～～～～～～～～
	////
	////         if( foo ){
	////
	////             DBGWRITINGLOGTEXT::addStr( "追記したい文字列\n %s" , "付随のパラメータ" );
	////
	////         }
	////     }
	//// }
	////
	static void Init(wstring FileName){
		DefaultLogFileName = FileName;
		if(PathFileExists(DefaultLogFileName.c_str())){
			_wremove( DefaultLogFileName.c_str() );
		}
	}
	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(const wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： ファイルへ文字列を追記 ( ワイド版 )
	//// 引数       ：    wchar_t* addStr      //  : 書式
	////            ：    ･･･                  //  : 
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：
	////            ：
	////･････････････
	////======== サンプル ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // クラスの初期化
	////
	////     while( boolean ){
	////
	//// ～～～～～～～～～～～～
	//// ～～～～～～～～～～～～
	////
	////         if( foo ){
	////
	////             // ※本関数
	////             DBGWRITINGLOGTEXT::addStr( L"追記したい文字列\n %s" , L"付随のパラメータ" );  // データの追記
	////
	////         }
	////     }
	//// }
	////
	static void addStr(const wchar_t* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
				int d;
				d = 0;
			}
		}
		wchar_t strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： ファイルへ文字列を追加
	//// 引数       ： なし
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：
	////            ：
	////
	//static void addStr(wchar_t* addStr){
	//	FILE* fp ;
	//	_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
	//	if(fp){
	//		fwprintf_s(fp,L"%s",addStr);
	//		fclose(fp);
	//	}
	//}

/* 上のComment表示避け */

	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(const addStr* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： ファイルへ文字列を追記 ( マルチバイト版 )
	//// 引数       ：    wchar_t* addStr      //  : 書式
	////            ：    ･･･                  //  : 
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：
	////            ：
	////･････････････
	////======== サンプル ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // クラスの初期化
	////
	////     while( boolean ){
	////
	//// ～～～～～～～～～～～～
	//// ～～～～～～～～～～～～
	////
	////         if( foo ){
	////
	////             // ※本関数
	////             DBGWRITINGLOGTEXT::addStr( "追記したい文字列\n %s" , "付随のパラメータ" );  // データの追記
	////
	////         }
	////     }
	//// }
	////
	static void addStr(const char* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
				int d;
				d = 0;
			}
		}
		char strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vsprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		_wfopen_s(&fp,DefaultLogFileName.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(wstring FileName,wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： ファイルを指定して文字列を追加
	//// 引数       ：    wstring     FileName    //  : 出力先のファイル名
	////            ：    wchar_t*    addStr      //  : 書式
	////            ：    ...                     //  : 
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：★超キケン!!
	////            ：★使用して放置するとHDDパンクの恐れあり!
	////･････････････
	////======== サンプル ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // クラスの初期化
	////
	////     if( foo ){
	////
	////          // ※本関数
	////          DBGWRITINGLOGTEXT::addStr( "追記したい文字列\n %s" , "付随のパラメータ" );  // データの追記
	////      }
	//// }
	////
	static void addStrToFile(const wstring FileName,const wchar_t* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
			}
		}
		wchar_t strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);
		FILE* fp ;
		wstring path = DefaultLogFolder + FileName;
		_wfopen_s(&fp,path.c_str(),L"a");
		if(fp){
			fwprintf_s(fp,L"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(wstring FileName,wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： ファイルを指定して文字列を追加
	//// 引数       ：    wstring     FileName    //  : 出力先のファイル名
	////            ：    wchar_t*    addStr      //  : 書式
	////            ：    ...                     //  : 
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：★超キケン!!
	////            ：★使用して放置するとHDDパンクの恐れあり!
	////･････････････
	////======== サンプル ========
	//// void main( void ){
	////
	////     DBGWRITINGLOGTEXT::Init( );   // クラスの初期化
	////
	////     while( boolean ){
	////
	//// ～～～～～～～～～～～～
	//// ～～～～～～～～～～～～
	////
	////         if( foo ){
	////
	////             // ※本関数
	////             DBGWRITINGLOGTEXT::addStr( "追記したい文字列\n %s" , "付随のパラメータ" );  // データの追記
	////
	////         }
	////     }
	//// }
	////
	static void addStrToFile(const string FileName,const char* addStr,...){
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)

		//	: 
		if(!PathIsDirectory(DefaultLogFolder.c_str())){
			if(!CreateDirectory(DefaultLogFolder.c_str(),NULL)){
			}
		}
		//	: 書式適応
		char strBuf[5024];
		va_list	argp;
		va_start(argp, addStr);
		vsprintf_s( strBuf , 5024 , addStr, argp);
		va_end(argp);

		//	: ファイルオープン
		FILE* fp ;
		string defaultPath ;
		TLIB::narrow( DefaultLogFolder , defaultPath);
		string path = defaultPath + FileName;
		fopen_s(&fp,path.c_str(),"a");

		if(fp){
			fprintf_s(fp,"%s",strBuf);
			fclose(fp);
		}
		#endif
	}
};
#if defined( DIRECT3D_VERSION )
//************************************************//
//class DBGSTR
//
// 担当者  : 鴫原 徹
// 目的    :  デバッグ用文字列を画面上に描画
//         : デファイン定義
//         : ・DEBUG
//         : ・_DEBUG
//	       : ・ON_DEBUGGINGPROCESS
//	       : の内、一つ以上が定義されている場合のみ有効
//	       : 上記が定義されていない場合すべてのメンバ関
//	       : 数は空関数化する
//*************************************************//
class DBGSTR{
public:
	#if defined( DIRECT3D_VERSION )
	static bool				m_bDrawFlag;
	static wstring			str;
	static LPD3DXFONT		m_lpDebagFont;        // フォントオブジェク
	#endif
	/////////////////// ////////////////////
	//// 関数名     ： static void addStr(wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： 描画文字列の追加
	//// 引数       ：    wchar_t* addStr,    // 描画文字 フォーマット
	////            ：    ...,                // 可変長引数
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ： 末尾に追加
	////            ：
	////
	static void addStr(const wchar_t* addStr,...){
		#if defined( DIRECT3D_VERSION ) && defined(CF_DRAW_DEBUGSTRING)
		if(5120 > str.size()  ){
			wchar_t strBuf[1024];
			va_list	argp;
			va_start(argp, addStr);
			vswprintf_s( strBuf , 1024 , addStr, argp);
			va_end(argp);
			str += strBuf;
		}
		#endif
	}
	/////////////////// ////////////////////
	//// 関数名     ： static void addStrTop(wchar_t* addStr,...)
	//// カテゴリ   ： メンバ関数
	//// 用途       ： 描画文字列の追加
	//// 引数       ：    wchar_t* addStr,    // 描画文字 フォーマット
	////            ：    ...,                // 可変長引数
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ： 先頭に追加
	////            ：
	////
	static void addStrTop(const wchar_t* addStr,...){
		#if defined( DIRECT3D_VERSION ) && defined(CF_DRAW_DEBUGSTRING)
		if(5120 > str.size()  ){
			wchar_t strBuf[1024];
			va_list	argp;
			va_start(argp, addStr);
			vswprintf_s( strBuf , 1024 , addStr, argp);
			va_end(argp);
			str = strBuf + str;
		}
		#endif
	}

	/////////////////// ////////////////////
	//// 関数名     ： static void Init(LPDIRECT3DDEVICE9 i_pD3DDevice)
	//// カテゴリ   ： イニシャライザ
	//// 用途       ： 初期化
	//// 引数       ：    LPDIRECT3DDEVICE9 i_pD3DDevice,    // デバイス
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：フォントなどを構築
	////            ：必ず最初に一度だけ呼んでください
	////
#if defined( DIRECT3D_VERSION )
	static void Init(LPDIRECT3DDEVICE9	i_pD3DDevice){
		#if defined(CF_DRAW_DEBUGSTRING)
		try{
			if (FAILED(D3DXCreateFont(i_pD3DDevice,				/* デバイス */
							10,									/* 文字の高さ */
							0,									/* 文字幅 */
							FW_NORMAL,							/* フォントの太さ */
							1,									/* MIPMAPのレベル */
							FALSE,								/* イタリックか？ */
							DEFAULT_CHARSET,					/* 文字セット */
							OUT_DEFAULT_PRECIS,					/* 出力精度 */
							DEFAULT_QUALITY,					/* 出力品質 */
							DEFAULT_PITCH | FF_SWISS,			/* フォントピッチとファミリ */
							L"ＭＳ ゴシック",					/* フォント名 */
							&m_lpDebagFont))) {					/* Direct3Dフォントへのポインタへのアドレス */
				char		strBuf[2048]={0};
				sprintf_s(strBuf,sizeof(strBuf), "デバッグ用フォントの生成に失敗\n 場所 : \"%s(%d) Func:%s\" \n続けますか？",__FILE__,__LINE__,__FUNCTION__);
				wchar_t		outBuf[4096]={0};
				setlocale( LC_CTYPE, "jpn" );
				size_t nNameSize = 0;
				mbstowcs_s(&nNameSize,outBuf,strlen(strBuf),strBuf,_TRUNCATE);
				if(MessageBox(NULL,outBuf,L"デバッグ関数エラー 場所:tagDBGSTR::Init",MB_YESNO) == IDNO){
					throw 1;
				}
			}
		}
		catch(...){
			throw;
		}
		#endif
	}
#endif
	/////////////////// ////////////////////
	//// 関数名     ： static void Draw()
	//// カテゴリ   ： メンバ関数
	//// 用途       ： 文字列の描画
	//// 引数       ： なし
	//// 戻値       ： なし
	//// 担当者     ： 鴫原 徹
	//// 備考       ：
	////            ：
	////
	static void Draw(){
		#if defined(CF_DRAW_DEBUGSTRING)
			if(GetAsyncKeyState( MYVK_DEBUG_OUTPUT_DBGSTR )){
				addStrTop(L"============================================================================================================\n");
				addStrTop(L"=====                                      デバッグ文字列出力                                          =====\n");
				addStrTop(L"============================================================================================================\n");
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( wstring(L"DebugStr.LOG"), str.c_str() );
			}
			if(m_bDrawFlag){
				m_lpDebagFont->DrawText(NULL,str.c_str(), -1, NULL
					, 0 , D3DCOLOR_ARGB(255, 255, 255, 0));
				str   = L"\n\n[ENTER]RESTART : [ALT+ENTER]CSVRELOAD : [CONTROL]INVISIBLE MODE : [F6]SOUND SWITCH : [F7]OBB DRAW : [F8]MEMORY OUTPUT : [F9]DBGSTR OUTPUT : [F11]1FPS MODE : [F12] UPDATE STOP\n";
				str  += L"\nデバッグ\n";
				//str += L"                                                                                                     コントローラー＝キーボード / A = X / B = C / X = S / Y = D /  \n";
			}
		#endif
	}
};
#endif
}
#endif