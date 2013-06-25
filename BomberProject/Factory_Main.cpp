////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Main.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Main ;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_Main.h"
//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
#include "StageLoader.h"
#include "Factory_Description.h"
#include "Factory_Description.h"
#include "Factory_Enemy.h"
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "Factory_Score.h"
#include "Factory_Wall.h"
#include "Factory_CheckPointSave.h"
#include "Factory_BackGround.h"
//	: 追加のインクルード
//////////

namespace wiz{
namespace bomberobject{


	
/**************************************************************************
 Factory_Main 定義部
****************************************************************************/
/**************************************************************************
 Factory_Main::Factory_Main(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Main::Factory_Main(FactoryPacket* fpac, DWORD dwStageNum, DWORD dwResumptionCheckPoint, D3DXVECTOR3* vStartPos ){
	try{
#if defined( ON_GUIDELINE ) 

		//	: ガイドライン
		fpac->m_pVec->push_back(new Guide( fpac->pD3DDevice ) );
#endif
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"\n\n//////////\n");
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"//  : \n");
		Debugger::DBGWRITINGLOGTEXT::addStrToFile(L"Score.txt",L"StageNum   = %d\n",dwStageNum);

		//////////
		//	: ライトの設定
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        fpac->m_pVec->push_back(
			new DirectionalLight(
				fpac->pD3DDevice,
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3( -0.0f, -1.0f, 0.0f)
			)
		);
		//	: ライトの設定
		//////////

		//////////
		//	: カメラの設定
		float ECXPos = 25.1f;
		float ECYPos = 10.666f;
		float ECZPos = -55.7f;
        fpac->m_pVec->push_back(
			new Camera(
				fpac->pD3DDevice,
				D3DXVECTOR3( ECXPos, ECYPos, ECZPos),
				D3DXVECTOR3( ECXPos, ECYPos,   0.0f),
				1 ,
				ECZPos+0.5f,
				30.0f
			)
		);
		//	: カメラの設定
		//////////


//←──────────────────────────────────────────────→//	

		//////////
		//	: 下請け工場へ発注
		float	fLineLength	= 230.0f;
		float	fPointSize	= 0.5f;
		Factory_BG			Bfac( fpac ) ;
		Factory_Cursor		Mfac( fpac, fLineLength, fPointSize )  ; 
		Factory_Player		Pfac( fpac );
		if( dwStageNum != 5 )
			Factory_Item	Ifac( fpac ) ;
		Factory_Wall		Wfac( fpac ) ;
		if( dwStageNum == 0 )	dwStageNum = 5 ;
		StageLoader			loader(fpac->pD3DDevice,L"media/Map/Stages.csv", dwStageNum,*fpac->m_pVec,*fpac->m_pTexMgr);
		Factory_Coil		Cfac( fpac , dwResumptionCheckPoint, vStartPos );
		Factory_Description	Dfac( fpac ) ;
		Factory_Gage		Gfac( fpac ) ;
		Factory_Score		Sfac( fpac ) ;
		//Factory_Enemy		Efac( fpac ) ;
		Factory_CheckPointSave	CPSfac( fpac , dwStageNum);
		//	: 下請け工場へ発注
		//////////

//←──────────────────────────────────────────────→//	


		//////////
		//	: 音声の構築とBGMの再生開始
		system::Sound* pSound = NULL;
		fpac->SetSound(
			pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_PLAY );
		//pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_SPARK );
		//	: 音声の構築とBGMの再生開始
		//////////


		//////////
		//	: オブジェクトのソート( 透過処理の問題対策 )
		vector<Object*>::size_type pos = fpac->m_pVec->max_size();
		WallObject* wp = (WallObject*)SearchObjectFromID( fpac->m_pVec,OBJID_3D_WALL, &pos );
		fpac->m_pVec->erase( fpac->m_pVec->begin() + pos );
		fpac->m_pVec->push_back( wp );
		//	: オブジェクトのソート( 透過処理の問題対策 )
		//////////

		
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"↑Factory_Main::Factory_Main()"
				);
	}
	catch(...){
		//再throw
		throw;
	}
}
/**************************************************************************
 Factory_Main::~Factory_Main();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Main::~Factory_Main(){
	//なにもしない
}


}


//end of namespace bomberobject.
}
//end of namespace wiz.