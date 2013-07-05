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

//#pragma comment(lib,"dinput8.lib")
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
//#include <dinput.h>

// HRESULT 使用 
#include <dxerr.h>

//
//////////


//////////
//
#include "resource1.h"

#include "SystemDefineValue.h"
#include "userInclude.h"
#include "BomberDefineValue.h"


extern wiz::RENDERSTATE_PARAM g_GlobalRenderStates[];
