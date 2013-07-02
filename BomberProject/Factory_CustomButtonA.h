////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CustomButtonA.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ButtonSpriteのCustom版
//					：タイトルとかで使用
//					▼
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#pragma once

#include "StdAfx.h"


namespace wiz{
namespace bomberobject{

class CustomButtonA : public ButtonSprite{
	PrimitiveSprite*	m_pSprite				;
	Color				m_dwStringSelectColor	;
	Color				m_dwStringUnSelectColor	;
	int					m_iPtn					;
public:
	CustomButtonA(
		const LPDIRECT3DDEVICE9		pD3DDevice				,
		const LPTATRATEXTURE		pFrameTexture			,
		const LPTATRATEXTURE		pStringTexture			,
		const D3DXVECTOR3			vScalse					,
		const D3DXVECTOR3			vRot					,
		const D3DXVECTOR3			vPos					,
		const Rect*					pFrameRect				,
		const Rect*					pStringRect				,
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
		const wiz::OBJID			id						,
		const bool					bKillAfterIssuing		= false		,
		const bool					bApplyAspect			= true
	);


	~CustomButtonA();

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
    virtual void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：純粋仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：
	//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
	////            ：
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
};


/**************************************************************************
 class Factory_CustomButtonA;
 用途: メイン工場クラス
****************************************************************************/
class Factory_CustomButtonA{
public:
	/**************************************************************************
	 Factory_CustomButtonA(
		FactoryPacket* fpac //パケットデータ
	);
	 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
	 戻り値: なし
	***************************************************************************/
	Factory_CustomButtonA( FactoryPacket* fpac );
	/**************************************************************************
	 ~MyFactory();
	 用途: デストラクタ
	 戻り値: なし
	***************************************************************************/
	~Factory_CustomButtonA();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
