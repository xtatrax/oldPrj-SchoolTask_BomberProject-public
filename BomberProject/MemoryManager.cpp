////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���Ȋ֐��Q�̃C�����C����`
//					��
//	namespace TLIB;
//
#include "stdafx.h"
#include "MemoryManager.h"
#if defined( CF_MEMORYMANAGER_ENABLE )
	std::list<TMemoryManager::itemInfo> TMemoryManager::m_ItemInfo ;
	DWORD	TMemoryManager::m_dwAreaSize = 0 ; 
#endif