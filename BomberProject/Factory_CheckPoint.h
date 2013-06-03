////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"

namespace wiz{

/**************************************************************************
class CheckEffect;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class CheckEffect : public PrimitiveBox{
	D3DXMATRIX		m_Matrix;
	D3DXVECTOR3		m_vPos ;
	int				m_Num;
	float			m_fWide;
	float			m_fHight;
	bool			m_bMark;
	PlayerCoil*		m_pCoil;
public:
	/////////////////// ////////////////////
	//// 用途       ：Description(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：佐藤涼
	//// 備考       ：
	CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3		vPos,
				float			fLength,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

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
	//// 担当者     ：佐藤涼
	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void update( int i )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void update( int i ,DrawPacket& i_DrawPacket);

/*************************************
関数名　：
用途　　：サイズ縮小
カテゴリ：
引数　　：
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************/
	void	Reduction();

/*************************************
関数名　：
用途　　：サイズ拡大（拡大率は縦横等価）
カテゴリ：
引数　　：
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************/
	void	Expansion();
};

/******************************************************:
******************************************************/
class CheckPoint : public Cylinder{
protected:
	struct ITEM{
		float	fPosY ;
		D3DXVECTOR3		vStartPos;
		ITEM(D3DXVECTOR3 i_vPos)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	typedef vector< ITEM* > ITEMCONTAINER ;
	ITEMCONTAINER			m_ItemContainer ;
	size_t					m_ActiveItem    ;
	PlayerCoil*				m_pCoil			;
	Camera*					m_pCamera		;
	D3DCOLORVALUE			m_Color;
	float					m_Thicken;
	float					m_Length;
	CheckEffect*			m_pEffect;
	Sound*					m_pSound;
	LPDIRECT3DTEXTURE9		m_pTexture;
/////////////////// ////////////////////
//// 関数名     ：bool HitTestIntersect(OBB i_obb, D3DXVECTOR3 i_vMove, HITGROUNDVECTOR& o_HitListVec)
//// カテゴリ   ：メンバ関数
//// 用途       ：
//// 引数       ：
////            ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
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
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	void RemoveTarget();

public:
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id = OBJID_SYS_CHECKPOINT );
	~CheckPoint();
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
//// 担当者     ：鴫原 徹
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：
//// 用途       ：チェックポイントを追加
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	void add(D3DXVECTOR3 i_vPos){
		m_ItemContainer.push_back( new ITEM( i_vPos ) );
	}

/////////////////// ////////////////////
//// 用途       ：void Blink()
//// カテゴリ   ：
//// 用途       ：オブジェクトを明滅させる
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
	void	Blink();

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
