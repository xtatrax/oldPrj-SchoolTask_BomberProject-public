////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Select.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Select ;
//
#include "StdAfx.h"
#include "Factory_Select.h"
#include "Factory_Cursor.h"
#include "Factory_CustomButtonA.h"
#include "Factory_SelectInformation.h"

namespace wiz{
namespace bomberobject{


//class TestBehavior : public Behavior{
//public:
//	TestBehavior()
//		:Behavior(OBJID_BEHAVIOR_TEST)
//	{}
//	/////////////////// ////////////////////
//	//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//	//// カテゴリ   ：仮想関数
//	//// 用途       ：オブジェクトを更新
//	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
//	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
//	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
//	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
//	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
//	////            ：  └       Command            pCommand        // コマンド
//	//// 戻値       ：無し
//	//// 担当者     ：鴫原 徹
//	//// 備考       ：継承したものでも必ずとも定義をしなくても良い
//	////            ：
//	////
//    void Update( UpdatePacket& i_UpdatePacket ){
//		if( Cursor2D::clickLorRButtonWithLock() )
//			(i_UpdatePacket.pCommand->m_Command = GM_CHANGE_PARENTSTAGE) ;
//	};
//};
	
/**************************************************************************
 Factory_Select 定義部
****************************************************************************/
/**************************************************************************
 Factory_Select::Factory_Select(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Select::Factory_Select(FactoryPacket* fpac ){
	try{

/////////////////////////////////////////////////////////////////////////////////
//                           説明用のテクスチャ                          //
/////////////////////////////////////////////////////////////////////////////////
		fpac->m_pVec->push_back(
			new SelectInformation(
					fpac->pD3DDevice,						//↓マウスがここの上にあるとき表示する画像
					fpac->AddTexture(L"Select_blue.png"),	//枠外
					fpac->AddTexture(L"Select_Green.png"),	//NORMAL
					fpac->AddTexture(L"Select_Orenge.png"),	//HARD
					fpac->AddTexture(L"Select_Pink.png"),	//EXTRA
					D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
					g_vZero,
					D3DXVECTOR3( 50.0f, 50.0f, 0.0f ),
					Rect( 0, 0, 512, 512 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                 NORMAL                                      //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,
				fpac->AddTexture(L"NORMAL002.tga"),
				fpac->AddTexture(L"NORMAL001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(980.0f, 300.0f, 0.0f),
				Rect(0,0,220,30),
				Rect(0,0,220,30),
				D3DXVECTOR3( 220.0f,0.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFF00FFFF,
				0xFF0000DD,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 3, 0 ),
				0,
				OBJID_UI_BUTTON_NORMAL
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                  HARD                                       //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"HARD002.tga"),
				fpac->AddTexture(L"HARD001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(980.0f, 375.0f, 0.0f),
				Rect(0,0,148,30),
				Rect(0,0,148,30),
				D3DXVECTOR3( 148.0f,0.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFFCC00,
				0xFFDD3300,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 4, 0 ),
				1,
				OBJID_UI_BUTTON_HARD
			)
		);
/////////////////////////////////////////////////////////////////////////////////
//                                 EXTRA                                       //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"EXTRA002.tga"),
				fpac->AddTexture(L"EXTRA001.tga"),
				D3DXVECTOR3( 1.8f,1.8f,0.0f ),
				g_vZero,
				D3DXVECTOR3(900.0f, 450.0f, 0.0f),
				Rect(0,0,179,26),
				Rect(0,0,179,26),
				g_vZero,
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFF5555,
				0xFF880000,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				1.0f,
				Command( GM_OPENSTAGE_LOAD_PLAY, 5, 0 ),
				2,
				OBJID_UI_BUTTON_EXTRA
			)
		);
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ;
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"↑Factory_Select::Factory_Select()"
				);
	}
	catch(...){
		//再throw
		throw;
	}
}
/**************************************************************************
 Factory_Select::~Factory_Select();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Select::~Factory_Select(){
	//なにもしない
}


}


//end of namespace bomberobject.
}
//end of namespace wiz.