////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Gage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：ゲージファクトリー
//					▼
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Cursor.h"

const	int		SUPER_GAGE_MAX		= 512;
const	int		MAGNETIC_GAGE_MAX	= 256;

namespace wiz{
namespace bomberobject{

/************************************************
class Gage : public SpriteObject

用途　：スーパーモード用のゲージ
担当者：佐藤涼 本多寛之(編集)
*************************************************/
class Gage : public SpriteObject{
protected:
	D3DXMATRIX m_mGaugeMatrix;
	Rect	m_BassRect;
	Rect	m_GaugeRect;
	Rect	m_FrameRect;
	float	m_fRate;
	
public:
	Gage(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: デバイス
		LPDIRECT3DTEXTURE9	pTex		,		//	: コア部分のTexture
		D3DXVECTOR3			&vScale		,		//	: 伸縮
		D3DXVECTOR3			&vRot		,		//	: 回転
		D3DXVECTOR3			&vPos		,		//	: 位置
		D3DXVECTOR3			&vDirOffset	,		//	: 描画オフセット
		RECT				GaugeRect	,		//	: 描画範囲
		RECT				FrameRect	,		//	: 描画範囲
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);
	~Gage();
	void	Recovery( float fAddValue );	//	: エネルギーの回復
	void	Consume(  float fSubValue );	//	: エネルギーの消費
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
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
	
	float getRate()const{
		return m_fRate;
	}

	void ResetGauge(){
		m_fRate = 1.0f ;
	}

	//void getGaugeRot_Right(int i_iValue){
	//	m_GaugeRect.right = i_iValue;
	//}
};

/************************************************
class SuperGage : public SpriteObject

用途　：スーパーモード用のゲージ
担当者：佐藤涼 本多寛之(編集)
*************************************************/
class SuperGage : public Gage{
	D3DXVECTOR3 m_vBassPos;
public:
	SuperGage(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: デバイス
		LPDIRECT3DTEXTURE9	pTex		,		//	: コア部分のTexture
		D3DXVECTOR3			&vScale		,		//	: 伸縮
		D3DXVECTOR3			&vRot		,		//	: 回転
		D3DXVECTOR3			&vPos		,		//	: 位置
		RECT				GaugeRect	,		//	: 描画範囲
		RECT				FrameRect	,		//	: 描画範囲
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_N : public Gage

用途　：N磁界用のゲージ
担当者：本多寛之
*************************************************/
class MagneticGage_N : public Gage{
	MouseCursor* m_pCursor ;
public:
	MagneticGage_N(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: デバイス
		LPDIRECT3DTEXTURE9	pTex		,		//	: コア部分のTexture
		D3DXVECTOR3			&vPos		,		//	: 位置
		RECT				GaugeRect	,		//	: 描画範囲
		RECT				FrameRect	,		//	: 描画範囲
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);

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
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_S : public Gage

用途　：S磁界用のゲージ
担当者：本多寛之
*************************************************/
class MagneticGage_S : public Gage{
	MouseCursor*	m_pCursor	;
public:
	MagneticGage_S(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: デバイス
		LPDIRECT3DTEXTURE9	pTex		,		//	: コア部分のTexture
		D3DXVECTOR3			&vPos		,		//	: 位置
		RECT				GaugeRect	,		//	: 描画範囲
		RECT				FrameRect	,		//	: 描画範囲
		wiz::OBJID			id = OBJID_UI_GAUGE	//	: ID
	);

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
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Gage;

 用途　：メイン工場クラス
 担当者：佐藤涼 
****************************************************************************/
class Factory_Gage{
	public:
	/**************************************************************************
	 Factory_Item(FactoryPacket* fpac);
	 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
	 戻り値: なし
	***************************************************************************/
		Factory_Gage(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 用途: デストラクタ
	 戻り値: なし
	***************************************************************************/
		~Factory_Gage();
	};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
