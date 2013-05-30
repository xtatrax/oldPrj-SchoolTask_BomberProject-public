////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Mouse.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：曳地 大洋
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Mouse ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{

/**************************************************************************
 MouseCursor 定義部
****************************************************************************/
//**************************************************************************//
// class MouseCursor : public PrimitiveBox
//
// 担当者  : 曳地 大洋
// 用途    : マウスカーソル
//**************************************************************************//
class MouseCursor : public PrimitiveBox{
	int			m_Ptn;
	LPDIRECT3DTEXTURE9 m_pMouseTex;
	Camera*	    m_pCamera;

//protected:
///////////////////// ////////////////////
////// 用途       ：MouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
////// カテゴリ   ：コンストラクタ
////// 用途       ：関数
////// 引数       ：なし
////// 戻値       ：なし
////// 担当者     ：鴫原 徹
////// 備考       ：
//	void UpdateTargetItem();

public:
	/////////////////// ////////////////////
	//// 用途       ：MouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	MouseCursor(LPDIRECT3DDEVICE9  pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				D3DXVECTOR3		   &vScale,
				D3DXVECTOR3		   &vPos,
				wiz::OBJID id = OBJID_3D_Cursor
				);

	//bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );
};

/**************************************************************************
 class Factory_Cursor;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Cursor{
public:
/**************************************************************************
 Factory_Cursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Cursor(FactoryPacket* fpac);
/**************************************************************************
 ~Factory_Cursor();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Cursor();
};
}
//end of namespace wiz.