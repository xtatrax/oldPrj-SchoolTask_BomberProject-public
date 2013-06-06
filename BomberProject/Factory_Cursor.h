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
#include "seiyaEffect.h"

namespace wiz{
namespace bomberobject{

//	: UIの高さ
#define UI_HEIGHT					( 88.0f )
//	: 表示画面の倍率 x=800, y=512 : x=40, y=25.6
#define DRAW_CLIENT_MAGNIFICATION	( 20.0f )
//	: 磁界の半径
#define MAGNETIC_RADIUS				( 0.5f )

// スクリーン座標をワールド座標に変換
inline D3DXVECTOR3* CalcScreenToWorld(
   D3DXVECTOR3* pout,
   int Sx,  // スクリーンX座標
   int Sy,  // スクリーンY座標
   float fZ,  // 射影空間でのZ値（0～1）
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   // 各行列の逆行列を算出
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // 逆変換
   D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}
//スクリーン座標とXZ平面のワールド座標交点算出（ CalcScreenToXZ関数 ）
// XZ平面とスクリーン座標の交点算出関数
inline D3DXVECTOR3* CalcScreenToXZ(
   D3DXVECTOR3* pout,
   int Sx,
   int Sy,
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // 床との交差が起きている場合は交点を
   // 起きていない場合は遠くの壁との交点を出力
   if( ray.y <= 0 ) {
      // 床交点
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}

//**************************************************************************//
// class LineCursor 
//
// 担当者  : 鴫原 徹
// 用途    : マウスカーソル
//**************************************************************************//
class LineCursor{
protected:
	/*****************************************************************
	// static Vertex
	//
	// 担当者  : 鴫原 徹
	// 用途    : 3D視点頂点データ 
	******************************************************************/
	struct Vertex
	{
		D3DXVECTOR3 m_vPos ;	//ゲーム画面での位置
		DWORD		m_dwColor ;	//色

		/////////////////// ////////////////////
		//// 用途       ：Vertex();
		//// カテゴリ   ：デフォルトコンストラクタ
		//// 用途       ：
		//// 引数       ：なし
		//// 戻値       ：なし
		//// 担当者     ：鴫原 徹
		//// 備考       ：
		Vertex()	: m_vPos(g_vZero),m_dwColor(0xFFFFFFFF){}

		/////////////////// ////////////////////
		//// 用途       ：Vertex( D3DXVECTOR3 i_vPos, DWORD i_dwColor );
		//// カテゴリ   ：コンストラクタ
		//// 用途       ：
		//// 引数       ：なし
		//// 戻値       ：なし
		//// 担当者     ：鴫原 徹
		//// 備考       ：
		Vertex(	D3DXVECTOR3 i_vPos, DWORD i_dwColor )
			:m_vPos(i_vPos),m_dwColor(i_dwColor){}

		/////////////////// ////////////////////
		//// 用途       ：static DWORD Vertex::getFVF()
		//// カテゴリ   ：ゲッター
		//// 用途       ：FVF設定を返す
		//// 引数       ：なし
		//// 戻値       ：[ DWORD ] FVF設定
		//// 担当者     ：鴫原 徹
		//// 備考       ：
		static DWORD Vertex::getFVF()
		{
			return D3DFVF_XYZ | D3DFVF_DIFFUSE  ;
		}
		/////////////////// ////////////////////
		//// 用途       ：static DWORD Vertex::getSize()
		//// カテゴリ   ：ゲッター
		//// 用途       ：構造体の大きさを返す
		//// 引数       ：なし
		//// 戻値       ：[ DWORD ] 構造体の大きさ
		//// 担当者     ：鴫原 徹
		//// 備考       ：
		static DWORD Vertex::getSize()
		{
			return sizeof(Vertex) ;
		}
	};
private:

	Vertex*					m_pVertex					;	//頂点データのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer				;	//バッファ
public:
	LineCursor( LPDIRECT3DDEVICE9 pD3DDevice );
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix ) ;

};


//**************************************************************************//
// class MouseCursor : public PrimitiveBox
//
// 担当者  : 曳地 大洋
// 引継ぎ  : 鴫原 徹
// 用途    : マウスカーソル
//**************************************************************************//
class MouseCursor : public Box , public  PrimitiveSprite{

	int					m_Ptn			;
	float				m_MovePosY		;
	Camera*				m_pCamera		;
	NameLineEffect*		m_pCursorLine	;
	D3DXMATRIX			m_mScale		;
	D3DXVECTOR3			m_v3DPos		;
	Point				m_v2DPos		;
//protected:

public:
	/////////////////// ////////////////////
	//// 用途       ：MouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			： LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////            ：pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	MouseCursor(LPDIRECT3DDEVICE9  pD3DDevice,TextureManager* m_TexMgr);

	/////////////////// ////////////////////
	//// 用途       ：~MouseCursor();
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	~MouseCursor();

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
	Point		get2DPos(){ return m_v2DPos ; };
	D3DXVECTOR3	get3DPos(){ return m_v3DPos ; };

protected:

	//	: 
	void UpdateCursor();
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
//end of namespace bomberobject.
}
//end of namespace wiz.