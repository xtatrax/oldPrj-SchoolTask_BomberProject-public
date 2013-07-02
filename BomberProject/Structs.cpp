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
TLIB::Tempus2*		BassPacket::GetTime(											)	{	return m_pTime ; }
LPDIRECT3DDEVICE9	BassPacket::GetDevice(											)	{	return m_pD3DDevice ;}
LPTATRATEXTURE		BassPacket::AddTexture(			const wchar_t*	sTextureName	)	{	if( m_pStage  ){ return m_pStage->m_TexMgr.addTexture( m_pD3DDevice , sTextureName )			;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); return NULL;}		}
void				BassPacket::AddButton(			       Object*	pButton			)	{	if( m_pStage  ){ m_pStage->AddButton( pButton )	;	AddObject( pButton )						;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::AddObject(			       Object*	pObje			)	{	if( m_pStage  ){ m_pStage->m_Vec.push_back( pObje )												;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::SearchSoundAndPlay(	const    char*	SoundName		)	{	if( m_pStage  ){ if( m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::SearchSoundAndStop(	const    char*	SoundName		)	{	if( m_pStage  ){ if( m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::SearchWaveAndPlay(	const    char*	WaveName		)	{	if( m_pStage  ){ if( m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::SearchWaveAndStop(	const    char*	WaveName		)	{	if( m_pStage  ){ if( m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::SoundStop(			const    char*	SoundName		)	{	if( m_pStage  ){ if( m_pStage->m_pSound )	m_pStage->m_pSound->SoundStop( SoundName  )			;}	else{Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); }}
void				BassPacket::PushCommand(		const  Command	Com				)	{	if( m_pCommand ) *m_pCommand = Com			; };
void				BassPacket::ClearCommand(										)	{	m_pCommand->Clear()							; };
Command				BassPacket::PopCommand(											)	{	return m_pCommand ? *m_pCommand : Command()	; };
Object*				BassPacket::SearchObjectFromID(	         DWORD	i_dwID			,
						vector<Object*>::size_type*					o_pPoint		,
						std::vector<Object*>*						o_pVec			,
						std::vector<vector<Object*>::size_type>*	o_pPointList	)
{	if( m_pStage  ){	return wiz::functions::SearchObjectFromID( &m_pStage->m_Vec, i_dwID, o_pPoint, o_pVec, o_pPointList );	}else{ Debugger::DBGWRITINGLOGTEXT::OutputSystemLog(L"NULLStage参照\n"); return NULL; }	}
//	:FactoryPacket
LPTATRATEXTURE		FactoryPacket::AddTexture(const wchar_t* sTextureName)	{	if( m_pTexMgr )	return m_pTexMgr->addTexture( pD3DDevice , sTextureName )	;	else return NULL;	}
void				FactoryPacket::AddButton(Object* pButton)				{	if( m_pStage  )	m_pStage->AddButton( pButton )	;	AddObject( pButton )	;	}
void				FactoryPacket::AddObject(Object* pObje)					{	if( m_pVec    )	m_pVec->push_back( pObje )		;								}
void				FactoryPacket::SearchSoundAndPlay(	const char*  SoundName )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				FactoryPacket::SearchSoundAndStop(	const char*  SoundName )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( SoundName )	; }
void				FactoryPacket::SearchWaveAndPlay(	const char*  WaveName  )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				FactoryPacket::SearchWaveAndStop(	const char*  WaveName  )	{	if( m_pStage && m_pStage->m_pSound )	m_pStage->m_pSound->SearchSoundAndPlay( WaveName  )	; }
void				FactoryPacket::SetSound(			system::Sound* pSound    )	{	if( m_pStage->m_pMySound ) SafeDelete( m_pStage->m_pMySound ) ; m_pStage->m_pMySound = pSound		; }
}
}
