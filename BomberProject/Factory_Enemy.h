////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Enemy.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	引き継ぎ		：本多寛之
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Enemy ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Coil.h"


namespace wiz{
namespace bomberobject{

const float ENEMY_SPEED_LV3 = 0.09f;
const float ENEMY_SPEED_LV2 = 0.06f;
const float ENEMY_SPEED_LV1 = 0.03f;
const float ENEMY_RADIUS = 1.5f;


/**************************************************************************
 EnemyModel 定義部
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveSphere
//
// 担当者  : 斎藤謙吾
// 引継ぎ  : 本多寛之
// 用途    : 敵
//**************************************************************************//	
class EnemyModel : public Object {
	LPD3DXMESH				m_pMesh			;
	D3DMATERIAL9			m_Material		;
	Camera*					m_pCamera		;
	ProvisionalPlayer3D*	m_pPlayer		;
	PlayerCoil*				m_pCoil			;
	bool					m_bReset		;
	D3DXMATRIX				m_WorldMatrix	;
	//LPTATRATEXTURE			m_pTex			;
	DeadEffect*				m_pDeadEffect	;

	struct EnemyItem{
		D3DMATERIAL9	m_Material		;
		D3DXMATRIX		m_Matrix		;
		D3DXVECTOR3		m_vPos			;
		D3DXVECTOR3		m_vStartPos		;
		float			m_fRotY			;
		POLE			m_bPole			;
		float			m_fMapKey		;
		bool			m_bHidden		;
		bool			m_bIsAlive		;

		//DeadEffect*		m_pDeadEffect[PARTICLS_NUM_ENEMY]	;
		EnemyItem():m_bHidden(true){}
		virtual ~EnemyItem(){
			//for( int i=0; i<PARTICLS_NUM_ENEMY; i++ ){
			//	SafeDelete( m_pDeadEffect[i] );
			//}
		}
	};
	
	//map<オブジェクトのポジション,WallItem>
	typedef multimap<float,EnemyItem*>	ALLCONTAINER		;
	typedef list<EnemyItem*>			TARGETCONTAINER		;
	ALLCONTAINER						m_ItemMap_All		;	//全てのWallItem
	TARGETCONTAINER						m_ItemMap_Target	;	//描画対象のWallItem

//std::find

protected:

	/////////////////// ////////////////////
	//// 用途       ：UpdateTargetItem()
	//// カテゴリ   ：
	//// 用途       ：関数
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	void UpdateTargetItem();

public:

	/////////////////// ////////////////////
	//// 関数名     ：EnemyModel(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
	////            ：  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPTATRATEXTURE pTexture = 0);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：球体を作成
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	////            ：  D3DCOLORVALUE& Diffuse,         //ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,            //スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,          //アンビエント色
	////            ：  LPTATRATEXTURE pTexture = 0	//テクスチャを張るときは指定
	//// 戻値       ：なし（失敗時は例外をthrow）
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：PrimitiveSphereの派生型
	////           ：
	////
	EnemyModel(
		      BassPacket& Packet,
		const char *pFileName,
		const wiz::OBJID id = OBJID_3D_ENEMY);

	/////////////////// ////////////////////
	//// 用途       ：~EnemyModel();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	~EnemyModel();

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：斎藤謙吾
	//// 引継ぎ     ： 本多寛之
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
	//// 戻値       ：なし
	//// 担当者     ：斎藤謙吾
	//// 引継ぎ     ： 本多寛之
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
	//// 戻値       ：なし
	//// 担当者     ：斎藤謙吾
	//// 引継ぎ     ： 本多寛之
	//// 備考       ：
	void AddEnemy(
		const D3DXVECTOR3&		vScale		,
		const D3DXVECTOR3&		vRot		,
		const D3DXVECTOR3&		vPos		,
		const D3DCOLORVALUE&	Diffuse		,
		const D3DCOLORVALUE&	Specular	,
		const D3DCOLORVALUE&	Ambient		,
		const POLE				Pole
	);

	/////////////////// ////////////////////
	//// 関数名     ：void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void	CreateEffect( UpdatePacket& i_UpdatePacket, TARGETCONTAINER::iterator it );


	/////////////////// ////////////////////
	//// 用途       ：bool HitTestWall( OBB Obb )
	//// カテゴリ   ：メンバ関数
	//// 用途       ：壁との衝突判定
	//// 引数       ：  OBB Obb           //  : 検査対象のOBB
	//// 戻値       ：衝突していればtrue
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	void HitTestWall( OBB , UpdatePacket& i_UpdatePacket);


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
