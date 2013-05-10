////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{

extern class PlayerCoil ;

/**************************************************************************
 WallObject 定義部
****************************************************************************/
//壁クラス---------------------------------------------------------------------
class WallObject : public PrimitiveBox{
	static PlayerCoil* m_pPlayerCoil ;
	static Camera*	   m_pCamera;
	struct WallItem{
		D3DMATERIAL9 m_Material;
		D3DXMATRIX	m_Matrix;
		D3DXVECTOR3 m_vScale ;
		D3DXVECTOR3 m_vPos ;
		D3DXQUATERNION m_vRot;
		virtual ~WallItem(){}
	};
	
	//map<オブジェクトのポジション,WallItem>
	multimap<float,WallItem*> m_ItemMap_All;	//全てのWallItem
	multimap<float,WallItem*> m_ItemMap_Target;//描画対象のWallItem
	//std::find

public:
	/**************************************************************************
	 WallObject::WallObject(
		LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
		LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
		wiz::OBJID id					//オブジェクトの種類
	);
	 用途: コンストラクタ
	 戻り値: なし
	 担当：本多寛之
	***************************************************************************/
	WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_2D_WALL);

	bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );

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

	/////////////////// ////////////////////
	//// 用途       ：void AddWall( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：Wallの追加
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
	////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
	////		    ：  D3DXVECTOR3 &vRot				//回転角
	////		    ：  D3DXVECTOR3 &vPos				//位置
	////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	void AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

	/////////////////// ////////////////////
	//// 用途       ：void GetOBB( size_t Index, OBB& obb )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ： size_t Index,
	////				 OBB& obb			//取得するOBB
	//// 戻値       ：なし。インデックスが範囲外なら例外
	////				＊現在のOBBを代入する
	//// 担当者     ：曳地 大洋
	//// 備考       ：
/**************************************************************************
	void GetOBB(
		size_t Index,
		OBB& obb	//取得するOBB
	);
 用途: 指定のインデックスの現在のOBBを得る
 戻り値: なし。インデックスが範囲外なら例外
 ＊現在のOBBを代入する
***************************************************************************/
	void GetOBB(size_t Index,OBB& obb);
};
//-------------------------------------------------------------------------------

//class WallManager {
//	typedef multimap< float, Wall > WALLCONTAINER ;
//	WALLCONTAINER m_Walls ;
//
//public:
//	WallManager();
//
//};
//
/**************************************************************************
 class Factory_Wall;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Wall{
public:
/**************************************************************************
 Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Wall(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Wall();
};
}
//end of namespace wiz.
