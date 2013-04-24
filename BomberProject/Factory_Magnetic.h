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
class MagneticumObject : public PrimitiveCylinder ,public Object{

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
<<<<<<< HEAD
		if( m_bMagnetPole == POLE_S )
		{ m_bMagnetPole = POLE_N ; m_Material.Diffuse.r = 0x00 ; m_Material.Diffuse.b = 0xFF ; }
		else
		{ m_bMagnetPole = POLE_S ; m_Material.Diffuse.b = 0x00 ; m_Material.Diffuse.r = 0xFF ; }
=======
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
>>>>>>> WorkSpace
		return true ;
	}

//////////
//	: 公開
public:
	MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec)
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec                // オブジェクトの配列
////            ：  Tempus2* i_DrawPacket.pTime	        // 時間を管理するクラスへのポインター
////            ：  Command i_DrawPacket.pCommand       // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket);

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
//// 担当       ：鴫原 徹
//// 備考       ： S極 = POLE_S = false
////            ： N極 = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
	
};


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
	Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Magnetic();
};
}
//end of namespace wiz.
