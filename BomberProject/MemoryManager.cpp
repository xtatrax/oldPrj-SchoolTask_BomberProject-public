////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：MemoryManager.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：グローバルな関数群のインライン定義
//					▼
//	namespace TLIB;
//
#include "stdafx.h"
#include "MemoryManager.h"
#if defined( CF_MEMORYMANAGER_ENABLE )
	std::list<TMemoryManager::itemInfo> TMemoryManager::m_ItemInfo ;
	DWORD	TMemoryManager::m_dwAreaSize = 0 ; 
#endif