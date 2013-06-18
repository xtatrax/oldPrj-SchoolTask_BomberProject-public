////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Mouse.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：曳地 大洋
//  引継ぎ			：鴫原 徹
//	編集			：佐藤 涼
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class Factory_Mouse ;
//
#pragma once

//////////
//	: インクルード
#include "Line.h"
//	: インクルード
//////////
namespace wiz{
namespace bomberobject{
enum MOUSE_POSITION{
	RIGTH	,
	LEFT	,
};

//**************************************************************************//
// class MouseCursor : public PrimitiveBox
//
// 担当者  : 曳地 大洋
// 引継ぎ  : 鴫原 徹
// 用途    : マウスカーソル
//**************************************************************************//
class MouseCursor : public Box , public  PrimitiveSprite{

	int					m_Ptn		;
	float				m_MovePosY	;
	Camera*				m_pCamera	;
	D3DXMATRIX			m_mScale	;
	D3DXVECTOR3			m_v3DPos	;
	D3DXVECTOR3			m_vScale	;
	Point				m_v2DPos	;
	Line*				m_pLine		;
	Line*				m_pLine2	;
	Torus*				m_pTorus	;
	SpriteObject*		m_pSelectPos;
	float				m_fTorusMagnification;
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
	MouseCursor(LPDIRECT3DDEVICE9  pD3DDevice,TextureManager* m_TexMgr, float fLineLength, float fPointSize);

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
	void Update2DPos();
	//	: 
	void Update3DPos();
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
	Factory_Cursor(FactoryPacket* fpac, float fLineLength, float fPointSize );
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