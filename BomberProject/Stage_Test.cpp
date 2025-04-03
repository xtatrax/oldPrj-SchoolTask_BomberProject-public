////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage_Test.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：テスト用のステージ
//					：★Scene.cpp Scene::CommandTranslator 関数で実体化されます
//					：★Scene.cpp Scene::Update / AnotherTargetRender / Draw 関数から呼ばれます
//					▼
//	namespace wiz;
//	;
//
#include "StdAfx.h"
#include "Stage_Test.h"
#include "StageLoader.h"
#include "Factory_Player.h"
#include "Factory_Stage1.h"
#include "Factory_CheckPoint.h"
#include "Factory_Description.h"
#include "Factory_Enemy.h"
#include "Factory_Goal.h"
#include "Factory_Gage.h"
#include "Factory_Item.h"
#include "Factory_Main.h"
#include "Factory_Magnetic.h"
#include "Factory_Player.h"
#include "Factory_Stage1.h"
#include "Factory_Description.h"
#include "Factory_Cursor.h"
#include "Factory_Wall.h"
#include "BassItems.h"


namespace wiz{
using namespace bomberobject;

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
DebugStage_TATRA::DebugStage_TATRA(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{
		FactoryPacket FPac, *fpac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		fpac = &FPac;
		//ライトのインスタンス初期化
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        fpac->m_pVec->push_back(new DirectionalLight(fpac->pD3DDevice,Diffuse,Specular,Ambient,
                    D3DXVECTOR3( -0.0f, -1.0f, 0.0f)));

		//カメラのインスタンス初期化
		float ECXPos = 25.1f;
		float ECYPos = 10.1f;		
        fpac->m_pVec->push_back(
			new Camera(fpac->pD3DDevice,D3DXVECTOR3( ECXPos, ECYPos, -55.7f),D3DXVECTOR3(ECXPos,ECYPos,0.0f), 1 ,300.0f,30.0f));

		fpac->m_pVec->push_back(
			new RenderTargetSprite((BassPacket*)fpac,800,512)
		);


		Factory_Player Pfac( fpac );
		Factory_Magnetic Mfac( fpac ) ;
		Factory_Enemy Efac( fpac ) ;
		Factory_CheckPoint CPfac( fpac ) ;
		Factory_Item   Ifac( fpac ) ;
		Factory_Gage	Gfac( fpac );
		//Factory_Stage1 Sfac( fpac ) ;

		Factory_Goal GPfac( fpac ) ;
		Factory_Description Dfac( fpac ) ;
		Factory_Cursor MCfac( fpac )  ; 

		StageLoader loader(pD3DDevice,L"media/Map/Stages.csv",1,m_Vec,m_TexMgr);
		Sound* pSound = NULL;
		fpac->m_pVec->push_back(
			pSound = new Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_PLAY );
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_SPARK );

	}
	catch(LoaderException& e){

		throw LoaderException(
			e.what_w(),
			L"↑DebugStage_TATRA::DebugStage_TATRA()");
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}


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
DebugStage_Loader::DebugStage_Loader(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:MenuStage(pD3DDevice,pStage)

{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;

		Factory_Stage1 Sfac(&FPac);
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}

};
