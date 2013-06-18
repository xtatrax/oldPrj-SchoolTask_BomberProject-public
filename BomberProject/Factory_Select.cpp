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
		//fpac->m_pVec->push_back( new TestBehavior());
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ;
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"1-0.png"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(20.0f, 60.0f, 0.0f),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF,
				0x88888888,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 1, 0 ),
				0
			)
		);

		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"1-6.png"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(20.0f, 120.0f, 0.0f),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF,
				0x88888888,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 1, 6 ),
				1
			)
		);
		fpac->AddButton(
			new ButtonSprite(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"2-0.png"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f, 60.0f, 0.0f),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF,
				0x88888888,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				Command( GM_OPENSTAGE_LOAD_PLAY, 2, 0 ),
				2
			)
		);
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