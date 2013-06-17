////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStructs.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�����ŗ��p�����\���̌S
//					��
//	namespace wiz;
//
#include "StdAfx.h"
#include "Structs.h"
#include "Stage.h"

namespace wiz{
namespace structs{
LPDIRECT3DTEXTURE9 FactoryPacket::AddTexture(const wchar_t* sTextureName)		{	if( m_pTexMgr )	return m_pTexMgr->addTexture( pD3DDevice , sTextureName ) ;		}
void FactoryPacket::AddButton(Object* pButton)					{	if( m_pStage  )	m_pStage->AddButton( pButton )	;	AddObject( pButton ) ;	}
void FactoryPacket::AddObject(Object* pObje)					{	if( m_pVec    )	m_pVec->push_back( pObje )		;							}
}
}
