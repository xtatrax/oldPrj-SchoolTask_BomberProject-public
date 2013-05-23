////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Pray.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：プレイステージ
//					▼
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Factory_Main.h"
#include "Factory_Sound.h"
#include "Stage_Play.h"
#include "stage.h"

namespace wiz{




/**************************************************************************
 PlayStage 定義部
****************************************************************************/
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
PlayStage::PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		OneSound* pSound ;
		m_Vec.push_back(
			pSound = new OneSound(
				L"media/Sound/MagneticaWave.xwb",
				L"media/Sound/MagneticaSound.xsb",
				2,
				OBJID_SOUND_BGM_PLAY
			)
		);
		pSound->PlaySound(255);
		Factory_Main mainF( &FPac );

	}
	catch(exception& e){
		Clear();
		//再スロー
		throw e;
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
PlayStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
PlayStage::~PlayStage(){
	
}

}
//end of namespace wiz.
