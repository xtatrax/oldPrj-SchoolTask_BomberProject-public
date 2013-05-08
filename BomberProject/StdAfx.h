#pragma once

#ifndef UNICODE
#error This App requires a Unicode build.
#endif

#include "dxsdkver.h"
#if ( _DXSDK_PRODUCT_MAJOR < 9 || _DXSDK_BUILD_MAJOR < 1949 )
#error The installed DXSDK is out of date.
#endif

#pragma warning( disable : 4091 )

//必要なバージョンは Windows XP 以降
#ifndef WINVER
#define WINVER         0x0501
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0600
#endif

//////////
//  リンカの設計
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "XInput.lib" )

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "shlwapi.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

#pragma comment(lib,"dinput8.lib")
//
//////////


//////////
//  基本的なインクルード
#include "resource.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <time.h>
#include <shlwapi.h>

//サウンド用
#include <xact3.h>
#include <shellapi.h>

// STL
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <algorithm>
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <new>
using namespace std;

// Direct3D9
#include <d3d9.h>
#include <d3dx9.h>

// XInput
#include <XInput.h>
#include <dinput.h>

// HRESULT 使用 
#include <dxerr.h>

//
//////////


//////////
//

#include "DefineValue.h"
#include "userInclude.h"

//<<<<<<< HEAD
//		GM_OPENDEBUGSTAGE_DEBUGMENU      ,
//		GM_OPENDEBUGSTAGE_TATEAWORKSPACE ,
//		GM_OPENDEBUGSTAGE_TOJIWORKSPACE  ,
//		GM_OPENDEBUGSTAGE_HSWORKSPACE    ,
//		GM_OPENDEBUGSTAGE_STAGECREATE    ,
//
//		//////////
//		//	: 
//		GM_PLAYOPENING_END	,
//
//	};
//
//	enum OBJID{
//		OBJID_UNK				,
//		OBJID_SYS_CAMERA		,
//		OBJID_SYS_LIGHT			,
//		OBJID_SYS_GUIDELINE		,
//		OBJID_SYS_SOUND			,
//		OBJID_SYS_ENEMYMANAGER	,
//		OBJID_SYS_CLEARAREA		,
//		OBJID_UI_SPRITE			,
//		OBJID_UI_SPRITEBUTTON	,
//		OBJID_UI_LIFE			,
//		OBJID_UI_GAUGE			,
//		OBJID_UI_SCORE			,
//		OBJID_UI_TIME			,
//		OBJID_2D_WALL			,
//		OBJID_3D_TESTBOX		,
//		OBJID_3D_TESTANIMMODEL	,
//		OBJID_3D_BOX			,
//		OBJID_3D_MAGNET			,
//		OBJID_3D_PLAYER			,
//		OBJID_3D_EFFECT			,
//		OBJID_3D_GROUND_FLAT	,
//		OBJID_3D_GROUND_SLOPE	,
//		OBJID_3D_GROUND_CLIFF	,
//		OBJID_3D_GROUND_WALL	,
//		OBJID_3D_ABORIGINE		,
//		OBJID_3D_BIRDE			,
//		OBJID_3D_ROCK			,
//	} ;
//
//}
////
////////////
//
////////////
////	: グローバルな変数
//
//extern D3DXVECTOR3 g_vZero ;	//	: ゼロベクトル
//extern D3DXVECTOR3 g_vOne  ;	//	: 一ベクトル
//extern D3DXVECTOR3 g_vMax  ;	//	: 最高ベクトル
//extern D3DXVECTOR3 g_vMin  ;	//	: 最低ベクトル
//
//extern wstring g_sDefaultTexturePath ;	//	: テクスチャの置き場
//
////	
////////////
//
////////////
////例外とユーティリティ関数等
//#include "TL-String.h"
//#include "MemoryManager.h"
//#include "Prim2D.h"
//#include "DebugFunctions.h"
//#include "Tempus/Tempus.h"
//#include "Structs.h"
//#include "DxDevice.h"
//#include "Object.h"
//#include "Function.h"
//#include "BassItems.h"
//using namespace TLIB;
//=======
//>>>>>>> ebfb324bf6f52bbf95fdfa6a42c9181b48fda531
//
//////////

extern wiz::RENDERSTATE_PARAM g_GlobalRenderStates[];
extern HWND g_hWnd;
extern bool g_bMouseLB;
extern bool g_bMouseRB;
