////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Scroll.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤謙吾
//	内包ﾃﾞｰﾀと備考	：スクロールファクトリー
//					▼
//	namespace wiz;
//		class Factory_Scroll ;
//
#pragma once

#include "StdAfx.h"
namespace wiz{
namespace bomberobject{
//const static BYTE	g_csbySpriteQty  = 2 ;
//D3DXVECTOR3			g_vPos[2];
//SpriteObject*		g_pBGSpriteArr[g_csbySpriteQty];

class ScrollObject : public SpriteObject{
	D3DXMATRIX	m_Matrix1;
	D3DXMATRIX	m_Matrix2;
	D3DXVECTOR3 m_vPos1;
	D3DXVECTOR3 m_vPos2;
	D3DXVECTOR3 m_vScale;

public:
	ScrollObject(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,
					const D3DXVECTOR3& vScale, const D3DXVECTOR3& vPos, RECT pRect
);

/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////             ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////             ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////             ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////             ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////             ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////             ：
////
	virtual void Update( UpdatePacket& i_UpdatePacket );


/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////             ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////             ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////             ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////             ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////             ：
////
	virtual void Draw( DrawPacket& i_DrawPacket ) ;
/**************************************************************************
 ~ScrollObject();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~ScrollObject();
};

/**************************************************************************
class Factory_Scroll;

用途　：メイン工場クラス
担当者：斎藤 謙吾
****************************************************************************/
class Factory_Scroll{
public:
	Factory_Scroll(FactoryPacket* fpac);

	~Factory_Scroll();
};

}

}