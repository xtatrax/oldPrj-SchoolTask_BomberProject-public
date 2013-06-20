////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CustomButtonA.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ButtonSpriteのCustom版
//					：タイトルとかで使用
//					▼
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#include "StdAfx.h"
#include "Factory_CustomButtonA.h"


namespace wiz{
namespace bomberobject{
CustomButtonA::CustomButtonA(
	const LPDIRECT3DDEVICE9		pD3DDevice				,
	const LPDIRECT3DTEXTURE9	pFrameTexture			,
	const LPDIRECT3DTEXTURE9	pStringTexture			,
	const D3DXVECTOR3			vScalse					,
	const D3DXVECTOR3			vRot					,
	const D3DXVECTOR3			vPos					,
	const RECT*					pFrameRect				,
	const RECT*					pStringRect				,
	const D3DXVECTOR3			vCenter					,
	const D3DXVECTOR3			vOffset					,
	const Color					dwFrameSelectColor		,
	const Color					dwFrameUnSelectColor	,
	const Color					dwStringSelectColor		,
	const Color					dwStringUnSelectColor	,
	const char*					sSelectSound			,
	const char*					sDecisionSound			,
	const float					fWaitTime				,
	const Command				Com						,
	const DWORD					dwIndex					,
	const wiz::OBJID			id						,
	const bool					bApplyAspect	
)
:ButtonSprite(
		pD3DDevice				,
		pFrameTexture			,	//	異
		vScalse					,
		vRot					,
		vPos					,
		pFrameRect				,	//	異
		vCenter					,
		vOffset					,
		dwFrameSelectColor		,
		dwFrameUnSelectColor	,
		sSelectSound			,
		sDecisionSound			,
		fWaitTime				,
		Com						,
		dwIndex					,
		id						,
		bApplyAspect
	)
,m_dwStringSelectColor(dwStringSelectColor)
,m_dwStringUnSelectColor(dwStringUnSelectColor)
{
	m_pSprite = new PrimitiveSprite(
		pD3DDevice				,
		pStringTexture			,	//	異
		pStringRect				,
		vCenter					,
		vOffset					,
		dwStringSelectColor			//	異
	);
	m_pSprite->setMatrix(CustomButtonA::getMatrix());
}
CustomButtonA::~CustomButtonA()
{
	SafeDelete( m_pSprite );
}

/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void CustomButtonA::Update( UpdatePacket& i_UpdatePacket ){
	
	if( ButtonSprite::m_ButtonState.getMouseSelect() ){
		m_pSprite->setColor( m_dwStringSelectColor );
	}else{
		m_pSprite->setColor( m_dwStringUnSelectColor );	
	}

	ButtonSprite::Update(i_UpdatePacket);
};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
void CustomButtonA::Draw( DrawPacket& i_DrawPacket ){
	ButtonSprite::Draw(i_DrawPacket);
	m_pSprite->Draw(i_DrawPacket);
};

/**************************************************************************
 Factory_CustomButtonA 定義部
****************************************************************************/
/**************************************************************************
 Factory_CustomButtonA::Factory_CustomButtonA(
	FactoryPacket* fpac		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_CustomButtonA::Factory_CustomButtonA( FactoryPacket* fpac ){
	try{


	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_CustomButtonA::~Factory_CustomButtonA();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_CustomButtonA::~Factory_CustomButtonA(){
    //なにもしない
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
