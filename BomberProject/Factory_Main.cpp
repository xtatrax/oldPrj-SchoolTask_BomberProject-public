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
#include "Factory_Main.h"
#include "Factory_Player.h"
#include "Factory_Wall.h"
#include "Factory_Goal.h"
#include "Factory_Enemy.h"
#include "Factory_Magnetic.h"
#include "Factory_Item.h"
#include "BassItems.h"

namespace wiz{


	
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
Factory_Main::Factory_Main(FactoryPacket* fpac){
	try{
		//	: ガイドライン
		fpac->m_pVec->push_back(new Guide( fpac->pD3DDevice ) );

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
		Factory_Wall   Wfac( fpac );
		Factory_Magnetic Mfac( fpac ) ;
		Factory_Item   Ifac( fpac ) ;
		Factory_Enemy Efac( fpac ) ;
		Factory_Goal	gfac( fpac );

		//	: スプライト
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"display.png" ),
				g_vOne,
				g_vZero,
				g_vZero,
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
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
//end of namespace wiz.