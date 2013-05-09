////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

#define  POLE_S true		/* S極 */
#define  POLE_N false		/* N極 */


namespace wiz{

//**************************************************************************//
// class MagneticumObject : public SpriteObject ;
//
// 担当者  : 鴫原 徹
// 用途    : 磁界オブジェクト
//         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
//**************************************************************************//
class MagneticumObject : public SpriteObject{

//////////
//	: 非公開
private:
	//	: 磁極フラグ
	//	: S極 = POLE_S
	//	: N極 = POLE_N
	bool m_bMagnetPole ;

//////////
//	: プロテクト
protected:
	//	: 座標
	D3DXVECTOR3 m_vPos ;
	D3DXVECTOR3 m_vScale ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; m_Color = 0xFF0000FF	; } ;
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	; } ;
/////////////////// ////////////////////
//// 関数名     ：void ChangePole()
//// カテゴリ   ：非公開アクセッサ
//// 用途       ：磁極を反転させる
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ： 磁極フラグとカラーを変更する
////            ：
////
	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: 公開
public:
	MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
/////////////////// ////////////////////
//// 関数名     ：void ChangePole()
//// カテゴリ   ：ゲッター
//// 用途       ：磁極を獲得
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ： S極 = POLE_S = false
////            ： N極 = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
///////////////////// ////////////////////
//// 関数名     ：D3DXVECTOR3 getPos() const { return g_vZero; }
//// カテゴリ   ：ゲッター
//// 用途       ：DEAD OR ALIVE
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	D3DXVECTOR3 getPos() const {
		return m_vPos; 
	}

};




//3D変換用
//**************************************************************************//
// class MagneticumObject3D : public PrimitiveCylinder ;
//
// 担当者  : 曳地 大洋
// 用途    : 磁界オブジェクト
//         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
//**************************************************************************//
class MagneticumObject3D : public PrimitiveCylinder{
	static Camera*	   m_pCamera ;
//////////
//	: 非公開
private:
	//	: 磁極フラグ
	//	: S極 = POLE_S
	//	: N極 = POLE_N
	bool m_bMagnetPole ;
//////////
//	: プロテクト
protected:
	struct Magnet3DItem{
		//	: 座標
		D3DMATERIAL9	m_Material ;
		D3DXMATRIX		m_Matrix ;
		D3DXVECTOR3		m_vScale ;
		D3DXVECTOR3		m_vPos ;
		D3DXQUATERNION	m_vRot ;
		//bool			m_bMagnetPole ;
		virtual ~Magnet3DItem(){}
	};

	//map<オブジェクトのポジション, Magnet3DItem>
	multimap<float, Magnet3DItem*> m_ItemMap_All ;
	multimap<float, Magnet3DItem*> m_ItemMap_Target ;

	D3DXVECTOR3			m_vPos ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; 
	m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 1.0f ;
	m_Material.Ambient.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;} ;
	void setPoleN(){ m_bMagnetPole = POLE_N	 ;
	m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 1.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 0.0f ;
	m_Material.Ambient.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;} ;


/////////////////// ////////////////////
//// 関数名     ：void ChangePole()
//// カテゴリ   ：非公開アクセッサ
//// 用途       ：磁極を反転させる
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ： 磁極フラグとカラーを変更する
////            ：
////

	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: 公開
public:
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		wiz::OBJID id = OBJID_3D_MAGNET
		) ;

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			 ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////             ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////             ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////             ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
	////			  ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////              ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////              ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////              ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////              ：  └       Command            pCommand        // コマンド
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	void Update( UpdatePacket& i_UpdatePacket );


/////////////////// ////////////////////
//// 関数名     ：D3DXVECTOR3 getPos() const
//// カテゴリ   ：ゲッター
//// 用途       ：中心座標を獲得
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;

/////////////////// ////////////////////
//// 関数名     ：void ChangePole()
//// カテゴリ   ：ゲッター
//// 用途       ：磁極を獲得
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：曳地大洋
//// 備考       ： S極 = POLE_S = false
////			 ： N極 = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;

/////////////////// ////////////////////
//// 用途       ：void AddMagnetic( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：マグネットの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
////
	void AddMagnetic(
		D3DXVECTOR3 &vScale,
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
		) ;

};


//// 3D変換用
////**************************************************************************//
//// class MagneticumObject3D : public PrimitiveCylinder ;
////
//// 担当者  : 曳地 大洋
//// 用途    : 磁界オブジェクト
////         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
////**************************************************************************//
//class MagneticumObject3DverT : public PrimitiveCylinder{
////////////
////	: 非公開
//private:
//	//	: 磁極フラグ
//	//	: S極 = POLE_S
//	//	: N極 = POLE_N
//	bool m_bMagnetPole ;
//
////////////
////	: プロテクト
//protected:
//	//	: 座標
//	D3DXVECTOR3 m_vPos ;
//	D3DXVECTOR3 m_vScale ;
//	//Color		m_Color;
//
//	void setPoleS(){ /*m_ = POLE_S  ; m_Color = 0xFF0000FF	;*/ } ;
//	void setPoleN(){ /*m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	;*/ } ;
///////////////////// ////////////////////
////// 関数名     ：void ChangePole()
////// カテゴリ   ：非公開アクセッサ
////// 用途       ：磁極を反転させる
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ： 磁極フラグとカラーを変更する
//////            ：
//////
//	bool ChangePole(){
//		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
//		else							{ setPoleS() ; }
//		return true ;
//	}
//
////////////
////	: 公開
//public:
//	MagneticumObject3DverT( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
//		wiz::OBJID id = OBJID_2D_PLAYER );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
///////////////////// ////////////////////
////// 関数名     ：D3DXVECTOR3 getPos() const
////// カテゴリ   ：ゲッター
////// 用途       ：中心座標を獲得
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ：
//////            ：
//	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;
///////////////////// ////////////////////
////// 関数名     ：void ChangePole()
////// カテゴリ   ：ゲッター
////// 用途       ：磁極を獲得
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ： S極 = POLE_S = false
//////            ： N極 = POLE_N = true
//	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
//	
//};


//	void setPoleS(){ /*m_ = POLE_S  ; m_Color = 0xFF0000FF	;*/ } ;
//	void setPoleN(){ /*m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	;*/ } ;
///////////////////// ////////////////////
////// 関数名     ：void ChangePole()
////// カテゴリ   ：非公開アクセッサ
////// 用途       ：磁極を反転させる
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ： 磁極フラグとカラーを変更する
//////            ：
//////
//	bool ChangePole(){
//		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
//		else							{ setPoleS() ; }
//		return true ;
//	}
//
////////////
////	: 公開
//public:
//	MagneticumObject3DverT( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
//		wiz::OBJID id = OBJID_3D_MAGNET );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
///////////////////// ////////////////////
////// 関数名     ：D3DXVECTOR3 getPos() const
////// カテゴリ   ：ゲッター
////// 用途       ：中心座標を獲得
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ：
//////            ：
//	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;
///////////////////// ////////////////////
////// 関数名     ：void ChangePole()
////// カテゴリ   ：ゲッター
////// 用途       ：磁極を獲得
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ： S極 = POLE_S = false
//////            ： N極 = POLE_N = true
//	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
//	
//};
//

/**************************************************************************
 class Factory_Magnetic;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Magnetic{
public:
/**************************************************************************
 Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	//Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_Magnetic( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
~Factory_Magnetic() ;
};
}
//end of namespace wiz.
