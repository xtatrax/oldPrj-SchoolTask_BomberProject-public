////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library_DirectX
//	�t�@�C����		�FDebugFunctions.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O�p�֐��Q
//					��
//	namespace wiz;
//		class DBGSTR ;
//		class DBGWRITINGLOGTEXT ;
//
#include "StdAfx.h"
#include "DebugFunctions.h"

#if defined( DIRECT3D_VERSION )
bool		Debugger::DBGSTR::m_bDrawFlag	= true			;
wstring		Debugger::DBGSTR::str			= L"�f�o�b�O\n"	;
LPD3DXFONT	Debugger::DBGSTR::m_lpDebagFont = NULL			;
#endif
wstring		Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder   = L"LogDatas/";
wstring     Debugger::DBGWRITINGLOGTEXT::DefaultLogFileName = Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder + L"LogData.txt";
