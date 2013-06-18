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
//	:BassPacket
LPDIRECT3DTEXTURE9	BassPacket::AddTexture(			const wchar_t* sTextureName	)	{	if( pTxMgr   )	return pTxMgr->addTexture( pD3DDevice , sTextureName )		;	else return NULL;		}
void				BassPacket::AddButton(			       Object* pButton		)	{	if( m_pStage )	m_pStage->AddButton( pButton )	;	AddObject( pButton )	;	}
void				BassPacket::AddObject(			       Object* pObje		)	{	if( pVec     )	pVec->push_back( pObje )		;							}
void				BassPacket::SearchSoundAndPlay(	const    char* SoundName	)	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				BassPacket::SearchSoundAndStop(	const    char* SoundName	)	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				BassPacket::SearchWaveAndPlay(	const    char* WaveName		)	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				BassPacket::SearchWaveAndStop(	const    char* WaveName		)	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				BassPacket::SoundStop(			const    char* SoundName	)	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SoundStop( SoundName  )	; }

//	:FactoryPacket
LPDIRECT3DTEXTURE9	FactoryPacket::AddTexture(const wchar_t* sTextureName)	{	if( m_pTexMgr )	return m_pTexMgr->addTexture( pD3DDevice , sTextureName )	;	else return NULL;	}
void				FactoryPacket::AddButton(Object* pButton)				{	if( m_pStage  )	m_pStage->AddButton( pButton )	;	AddObject( pButton )	;	}
void				FactoryPacket::AddObject(Object* pObje)					{	if( m_pVec    )	m_pVec->push_back( pObje )		;								}
void				FactoryPacket::SearchSoundAndPlay(	const char*  SoundName )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				FactoryPacket::SearchSoundAndStop(	const char*  SoundName )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				FactoryPacket::SearchWaveAndPlay(	const char*  WaveName  )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				FactoryPacket::SearchWaveAndStop(	const char*  WaveName  )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				FactoryPacket::SetSound(			system::Sound* pSound    )	{	if( m_pStage->m_pSound ) SafeDelete( m_pStage->m_pSound ) ; m_pStage->m_pSound = pSound		; }
}
}
