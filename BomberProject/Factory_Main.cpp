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
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "StageLoader.h"

#include "Factory_CheckPoint.h"
#include "Factory_Coil.h"
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
#include "Factory_Score.h"
#include "BassItems.h"

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
Factory_Main::Factory_Main(FactoryPacket* fpac, D3DXVECTOR3* vStartPos ){
	try{
//#if defined( ON_GUIDELINE ) 
//
//		//	: ガイドライン
//		fpac->m_pVec->push_back(new Guide( fpac->pD3DDevice ) );
//#endif
		//ライトのインスタンス初期化
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

		//カメラのインスタンス初期化
		float ECXPos = 25.1f;
		float ECYPos = 10.1f;		
        fpac->m_pVec->push_back(
			new Camera(
				fpac->pD3DDevice,
				D3DXVECTOR3( ECXPos, ECYPos, -55.7f),
				D3DXVECTOR3(ECXPos,ECYPos,0.0f),
				1 ,
				300.0f,
				30.0f
			)
		);

		//	: レンダーTARGET
		//fpac->m_pVec->push_back(
		//	new RenderTargetSprite((BassPacket*)fpac,800,512)
		//);

		float fBoxSizeX = 90.0f ;
		for( int i = 0 ; i < 20 ; i++ ){
			fpac->m_pVec->push_back(
				new Box(
					fpac->pD3DDevice ,
					D3DXVECTOR3( 50.0f, fBoxSizeX    , 0.0f ),
					D3DXVECTOR3( 25.0f, fBoxSizeX *i , 0.0f ),
					g_vZero,
					Diffuse,
					Specular,
					Ambient,
					OBJID_3D_BOX,
					false,
					fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"BGP_PLAY.tga")
				)
			);
		}


		Factory_Cursor		MCfac( fpac )  ; 
		Factory_Player		Pfac( fpac );
		StageLoader loader(fpac->pD3DDevice,L"media/Map/Stages.csv", 1,*fpac->m_pVec,*fpac->m_pTexMgr);
		Factory_CheckPoint	CPfac( fpac ) ;
		Factory_Coil		Cfac( fpac , vStartPos );
		//Factory_BG		Wfac( fpac );

		Factory_Magnetic	Mfac( fpac ) ;
		Factory_Enemy		Efac( fpac ) ;
		Factory_Item		Ifac( fpac ) ;
		Factory_Description	Dfac( fpac ) ;
		Factory_Gage		Gfac( fpac );
		Factory_Score		Sfac( fpac );
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
		//fpac->m_pVec->push_back(
		//	new SpriteObject(
		//			fpac->pD3DDevice ,
		//			fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"BGP_TITLE01.tga"),
		//			g_vOne,
		//			g_vZero,
		//			g_vZero,
		//			NULL,
		//			g_vZero,
		//			g_vZero
		//	)
		//);
		vector<Object*>::size_type pos = fpac->m_pVec->max_size();
		WallObject* wp = (WallObject*)SearchObjectFromID( fpac->m_pVec,OBJID_3D_WALL, &pos );
		fpac->m_pVec->erase( fpac->m_pVec->begin() + pos );
		fpac->m_pVec->push_back( wp );

		
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