////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Structs.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：多所で利用される構造体郡
//					▼
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
