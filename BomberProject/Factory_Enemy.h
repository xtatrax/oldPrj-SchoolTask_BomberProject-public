////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Enemy.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Enemy ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

const float ENEMY_SPEED = 0.1f;

/**************************************************************************
 EnemySphere 定義部
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveSphere
//
// 担当者  : 斎藤謙吾
// 用途    : 敵
//**************************************************************************//	
	class EnemySphere : public PrimitiveSphere {
		Camera*					m_pCamera	;
		Sound*					m_pSound;
		ProvisionalPlayer3D*	m_pPlayer	;
		PlayerCoil*				m_pCoil		;
		bool					m_bReset	;
		struct EnemyItem{
			D3DMATERIAL9	m_Material		;
			D3DXMATRIX		m_Matrix		;
			D3DXVECTOR3		m_vScale		;
			D3DXVECTOR3		m_vPos			;
			D3DXVECTOR3		m_vStartPos		;
			D3DXQUATERNION	m_vRot			;
			POLE			m_bPole			;
			virtual ~EnemyItem(){}
		};
		
//map<オブジェクトのポジション,EnemyItem>
		multimap<float,EnemyItem*> m_ItemMap_All;	//全てのEnemyItem
		multimap<float,EnemyItem*> m_ItemMap_Target;//描画対象のEnemyItem
//std::find

		public:

/////////////////// ////////////////////
//// 関数名     ：EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            ：  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  D3DCOLORVALUE& Diffuse,         //ディフューズ色
////            ：  D3DCOLORVALUE& Specular,            //スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,          //アンビエント色
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：PrimitiveSphereの派生型
////           ：
////
		EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			LPDIRECT3DTEXTURE9 pTexture = 0 , wiz::OBJID id = OBJID_3D_ENEMY);

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
//// 担当者     ：斎藤謙吾
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
//// 担当者     ：斎藤謙吾
//// 備考       ：
////            ：
////
		void Update( UpdatePacket& i_UpdatePacket );



/////////////////// ////////////////////
//// 用途       ：void AddEnemy( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：Enemyの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：斎藤謙吾
//// 備考       ：
		void AddEnemy(
			const D3DXVECTOR3 &vScale		,
			const D3DXVECTOR3 &vRot			,
			const D3DXVECTOR3 &vPos			,
			const D3DCOLORVALUE& Diffuse	,
			const D3DCOLORVALUE& Specular	,
			const D3DCOLORVALUE& Ambient
		);

	
			~EnemySphere();
	};

/**************************************************************************
 class Factory_Enemy;
 用途: メイン工場クラス
****************************************************************************/
	class Factory_Enemy{
		public:
/**************************************************************************
 Factory_Enemy(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
		Factory_Enemy(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
		~Factory_Enemy();
	};
}//end of namespace bomberobject.
}//end of namespace wiz.
