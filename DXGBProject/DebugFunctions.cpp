////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDebugFunctions.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�O�p�֐��Q
//					��:
//	namespace wiz;
//		class DBGSTR ;
//		class DBGWRITINGLOGTEXT ;
//
#include "StdAfx.h"
#include "DebugFunctions.h"

bool		Debugger::DBGSTR::m_bDrawFlag	= true			;
wstring		Debugger::DBGSTR::str			= L"�f�o�b�O\n"	;
LPD3DXFONT	Debugger::DBGSTR::m_lpDebagFont = NULL			;
wstring		Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder   = L"LogDatas/";
wstring     Debugger::DBGWRITINGLOGTEXT::DefaultLogFileName = Debugger::DBGWRITINGLOGTEXT::DefaultLogFolder + L"LogData.txt";
