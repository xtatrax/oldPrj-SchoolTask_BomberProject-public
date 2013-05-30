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




namespace wiz{


extern	class	MagneticField;

////**************************************************************************//
//// class MagneticumObject : public SpriteObject ;
////
//// 担当者  : 鴫原 徹
//// 用途    : 磁界オブジェクト
////         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
////**************************************************************************//
//class MagneticumObject : public SpriteObject{
//
////////////
////	: 非公開
//private:
//	//	: 磁極フラグ
//	//	: S極 = POLE_S
//	//	: N極 = POLE_N
//	POLE m_bMagnetPole ;
//
////////////
////	: プロテクト
//protected:
//	//	: 座標
//	D3DXVECTOR3 m_vPos ;
//	D3DXVECTOR3 m_vScale ;
//
//	void setPoleS(){ m_bMagnetPole = POLE_S  ; m_Color = 0xFF0000FF	; } ;
//	void setPoleN(){ m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	; } ;
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
//	MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
//		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
///////////////////// ////////////////////
////// 関数名     ：void ChangePole()
////// カテゴリ   ：ゲッター
////// 用途       ：磁極を獲得
////// 引数       ：なし
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ： S極 = POLE_S = false
//////            ： N極 = POLE_N = true
//	POLE getMagnetPole() const { return m_bMagnetPole	;	}	;
/////////////////////// ////////////////////
////// 関数名     ：D3DXVECTOR3 getPos() const { return g_vZero; }
////// カテゴリ   ：ゲッター
////// 用途       ：DEAD OR ALIVE
////// 引数       ：なし
////// 戻値       ：なし
////// 担当者     ：鴫原 徹
////// 備考       ：
//////            ：
//////
//	D3DXVECTOR3 getPos() const {
//		return m_vPos; 
//	}
//
//};
//
//


//3D変換用
//**************************************************************************//
// class MagneticumObject3D : public PrimitiveCylinder ;
//
// 担当者  : 曳地 大洋
// 編集    : 鴫原 徹
// 用途    : 磁界オブジェクト
//         : コイルオブジェクトやユーザー設置磁界にも応用しています｡
//**************************************************************************//
class MagneticumObject3D : public PrimitiveCylinder{
protected:
	static Camera*		m_pCamera ;
	MagneticField*		m_pMagneticField;
	MagneticField*		m_pMagneticField2;
	MagneticField*		m_pMagneticField3;
	MagneticField*		m_pMagneticField4;
//////////
//	: 非公開
private:
	//	: 磁極フラグ
	//	: S極 = POLE_S
	//	: N極 = POLE_N
	POLE  m_bMagnetPole ;
	float m_fMagneticum ;
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
		POLE			m_bMagnetPole ;
		virtual ~Magnet3DItem(){}
	};

	//map<オブジェクトのポジション, Magnet3DItem>
	multimap<float, Magnet3DItem*> m_ItemMap_All ;
	multimap<float, Magnet3DItem*> m_ItemMap_Target ;

	D3DXVECTOR3			m_vPos ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; setColorS() ; }
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; setColorN() ; }
	void setPole( POLE bPool ){
		     if( bPool == POLE_N ) setPoleN() ;
		else if( bPool == POLE_S ) setPoleS() ;
	}
	
	void setColorS(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 1.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 0.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ; 
	}
	void setColorN(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 1.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ;	
	}
	void setColorSuper(){
		m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;
		m_Material.Diffuse.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Diffuse.g = 1.0f ; m_Material.Diffuse.r = 1.0f ;			
	}

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
	/////////////////// ////////////////////
	//// 用途       ：MagneticumObject3D(
	///										LPDIRECT3DDEVICE9 pD3DDevice,
	///										LPDIRECT3DTEXTURE9 pTexture,
	///										wiz::OBJID id = OBJID_3D_MAGNET
	///										) ;
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// 戻値       ：無し
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	////	
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		wiz::OBJID id = OBJID_3D_MAGNET
		) ;

	/////////////////// ////////////////////
	//// 用途       ：	MagneticumObject3D(
	////									LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////									float Radius1,float Radius2,float Lenght,
	////									D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,D3DCOLORVALUE& Diffuse,
	////									D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////									wiz::OBJID id = OBJID_3D_MAGNET)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Player用のコンストラクタ
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////		      :   float Radius1						//円の直径1
	////		      :   float Radius2						//円の直径2
	////			  :   float Lenght						//高さ
	////		      :   D3DXVECTOR3 &vRot				//回転角
	////		      :   D3DXVECTOR3 &vPos				//位置
	////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
	////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
	////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	////	
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,
		float Radius2,
		float Lenght,
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_MAGNET
		) ;


	/////////////////// ////////////////////
	//// 用途       ：  ~MagneticumObject3D()
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：Player用のコンストラクタ
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////	
	~MagneticumObject3D();

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
		POLE		vPole,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
		) ;
	
	/////////////////// ////////////////////
	//// 用途       ：bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// カテゴリ   ：関数
	//// 用途       ：距離を判定
	//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
	////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
	////　　　　　　：float        i_iBorder           //判定する値
	//// 戻値       ：true , false
	//// 担当者     ：本多寛之
	//// 備考       ：
	//bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const;
	

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const {
		return m_vPos			;	
	}	;

	/////////////////// ////////////////////
	//// 関数名     ：void ChangePole()
	//// カテゴリ   ：ゲッター
	//// 用途       ：磁極を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：曳地大洋
	//// 備考       ： S極 = POLE_S = false
	////			 ： N極 = POLE_N = true
	POLE  getMagnetPole() const { return m_bMagnetPole	;	}	;

	float getMagneticum() const { return m_fMagneticum*m_fMagneticum  ;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：multimap<float, Magnet3DItem*> getMapTarget() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_ItemMap_Targetを獲得
	//// 引数       ：なし
	//// 戻値       ：m_ItemMap_Target
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	multimap<float, Magnet3DItem*> getMapTarget() const{
		return m_ItemMap_Target;
	}

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
