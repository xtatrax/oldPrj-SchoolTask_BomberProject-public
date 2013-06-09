////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library_DirectX
//	ファイル名		：DebugFunctions.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：デバッグ用関数群
//					▼
//	namespace wiz;
//		class DBGSTR ;
//		class DBGWRITINGLOGTEXT ;
//
#include "StdAfx.h"
#include "DebugFunctions.h"

#if defined( DIRECT3D_VERSION )
bool		Debugger::DBGSTR::m_bDrawFlag	= true			;
wstring		Debugger::DBGSTR::str			= L"デバッグ\n"	;
LPD3DXFONT	Debugger::DBGSTR::m_lpDebagFont = NULL			;
#endif
wstring		Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder   = L"LogDatas/";
wstring     Debugger::DBGWRITINGLOGTEXT::DefaultLogFileName = Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder + L"LogData.txt";
