////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多 寛之
//	編集			：曳地 大洋
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class WallObject : public PrimitiveBox 
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Player.h"
#include "Factory_Enemy.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"
#include "Factory_CheckPoint.h"
#include "Factory_DeadEffect.h"
#include "Factory_Continue.h"

namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;
extern class EnemyModel ;

/**************************************************************************
 Warning 定義部
****************************************************************************/
//**************************************************************************//
// class Warning
//
// 担当者  : 本多寛之
//     
// 用途    : エフェクト
//**************************************************************************//
class Warning : public PrimitiveBox{
	PrimitivePlate m_Plate;
	int	m_iPtn;
	LPDIRECT3DTEXTURE9	m_pTexture	;
	D3DMATERIAL9		m_Material	;
	D3DXMATRIX			m_Matrix	;
	D3DXVECTOR3			m_vPos		;	//	: 座標
	D3DXVECTOR3			m_vRot		;	//	: 回転
	D3DXVECTOR3			m_vScale	;	//	: 伸縮
	bool				m_bToDraw	;
public:
	/////////////////// ////////////////////
	//// 用途       ：Warning(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	Warning(LPDIRECT3DDEVICE9 pD3DDevice,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			LPDIRECT3DTEXTURE9 pTexture,
			wiz::OBJID id = OBJID_3D_WARNING
			);
	/////////////////// ////////////////////
	//// 用途       ：~Warning();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	~Warning();
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

	void setMatrix(D3DXMATRIX& i_Matrix){
		m_Matrix = i_Matrix;
	}

	void setPos(D3DXVECTOR3& i_Pos){
		m_vPos = i_Pos;
	}
	void setRot(D3DXVECTOR3& i_Rot){
		m_vRot = i_Rot;
	}
	void setScale(D3DXVECTOR3& i_Scale){
		m_vScale = i_Scale;
	}

	void setToDraw(bool i_bFlg){
		m_bToDraw = i_bFlg;
	}
	bool getToDraw(){
		return m_bToDraw;
	}
};



/**************************************************************************
 WallObject 定義部
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveBox
//
// 担当者  : 本多寛之
//         : 曳地 大洋
// 編集    : 鴫原 徹
// 用途    : 壁
//**************************************************************************//
class WallObject : public PrimitiveBox{
	int					m_Ptn			;
	PlayerCoil*			m_pPlayerCoil	;
	EnemyModel*			m_pEnemy		;
	Sound*				m_pSound		;
	Camera*				m_pCamera		;
	PrimitivePlate		m_Plate			;
	LPDIRECT3DTEXTURE9	m_pWallTex		;
	Warning*			m_pWarning		;
	struct WallItem{
		D3DMATERIAL9	m_Material	;
		D3DXMATRIX		m_Matrix	;
		OBB				m_Obb		;
		OBB				m_Obb_W		;
		float			m_fMapKey	;
		bool			m_bHidden	;
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		DrawOBB*       m_pDOB		;
		~WallItem(){SafeDelete(m_pDOB);}
#endif
		WallItem(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
		:m_bHidden(true)
		,m_fMapKey(vPos.y)
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		,m_pDOB()
#endif
		{
			::ZeroMemory(&m_Material,sizeof(D3DMATERIAL9));

			//衝突判定用のOBBの初期化
			D3DXVECTOR3 vOBBScale	= D3DXVECTOR3(vScale.x/4,vScale.y*0.97f,vScale.z),
						vOBBScale_W	= D3DXVECTOR3(vScale.x,vScale.y,vScale.z),
						vOBBRot		= D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian( vRot.z ));
			m_Obb = OBB( vOBBScale, vOBBRot, vPos ) ;
			m_Obb_W = OBB( vOBBScale_W, vOBBRot, vPos ) ;
			D3DXMATRIX mScalse, mRot, mPos;
			D3DXMatrixIdentity(&mScalse);
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixIdentity(&mPos);
			D3DXMatrixScaling(&mScalse,vScale.x,vScale.y,vScale.z);
			D3DXMatrixRotationZ(&mRot,vOBBRot.z);
			D3DXMatrixTranslation(&mPos, vPos.x,vPos.y,vPos.z);
			m_Matrix = mScalse * mRot * mPos ;
			m_Material.Ambient = Ambient ;
			m_Material.Diffuse = Diffuse ;
			m_Material.Specular = Specular ;

		}

	};
	//map<オブジェクトのポジション,WallItem>
	typedef multimap<float,WallItem*>	ALLCONTAINER		;
	typedef list<WallItem*>				TARGETCONTAINER		;
	ALLCONTAINER				m_ItemMap_All		;	//全てのWallItem
	TARGETCONTAINER				m_ItemMap_Target	;	//描画対象のWallItem

protected:

	/////////////////// ////////////////////
	//// 用途       ：WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：関数
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	void UpdateTargetItem();

public:
	/////////////////// ////////////////////
	//// 用途       ：WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPDIRECT3DTEXTURE9 pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：無し
	//// 担当者     ：本多寛之
	//// 備考       ：
	WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
	/////////////////// ////////////////////
	//// 用途       ：~WallObject();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	~WallObject();

	bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );

	

	///////////////////// ////////////////////
	////// 用途       ：void GetOBB( size_t Index, OBB& obb )
	////// カテゴリ   ：関数
	////// 用途       ：オブジェクトをディスプレイに表示する
	////// 引数       ： float Index,
	//////				 OBB& obb			//取得するOBB
	////// 戻値       ：なし。インデックスが範囲外なら例外
	//////				＊現在のOBBを代入する
	////// 担当者     ：曳地 大洋
	////// 備考       ：
	void GetOBBList( float Index, list<OBB>& ObbList );


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


	bool HitTest3DAddWall( MultiBox* pBox, size_t& Index, D3DXVECTOR3& Vec, D3DXVECTOR3& ElsePos );


};

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
//end of namespace bomberobject.
}
//end of namespace wiz.
