////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{
	
class CheckPoint : public Cylinder{
protected:
	struct ITEM{
		
	};
	typedef multimap< float, ITEM* > ITEMCONTAINER ;
	ITEMCONTAINER m_TtemContainer ;
	//list 
/////////////////// ////////////////////
//// 関数名     ：bool HitTestIntersect(OBB i_obb, D3DXVECTOR3 i_vMove, HITGROUNDVECTOR& o_HitListVec)
//// カテゴリ   ：メンバ関数
//// 用途       ：
//// 引数       ：
////            ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
	void SetTarget();
/////////////////// ////////////////////
//// 関数名     ：bool HitTestIntersect(OBB i_obb, D3DXVECTOR3 i_vMove, HITGROUNDVECTOR& o_HitListVec)
//// カテゴリ   ：メンバ関数
//// 用途       ：
//// 引数       ：
////            ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
	void RemoveTarget();

public:
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id = OBJID_SYS_CHECKPOINT );
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
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;



};

/**************************************************************************
 class Factory_CheckPoint;
 用途: メイン工場クラス
****************************************************************************/
class Factory_CheckPoint{
public:
/**************************************************************************
 Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_CheckPoint();
};
}
//end of namespace wiz.
