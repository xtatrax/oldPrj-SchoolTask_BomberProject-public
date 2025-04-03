////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Goal.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包データと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Goal ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
class FMemoryTex;

用途　：説明文の挿入
担当者：佐藤涼
**************************************************************************/
class FMemoryTex : public PrimitiveBox{
	Camera*			m_pCamera;
	PlayerCoil*		m_pCoil;
	D3DXVECTOR3		m_vScale ;
	D3DXVECTOR3		m_vPos ;
	int				m_iPtn;
	bool			m_bEnding;
	struct mItem{
		D3DMATERIAL9	mMaterial;
		D3DXMATRIX		mMatrix;
		D3DXVECTOR3		vScale ;
		D3DXVECTOR3		vPos ;
		D3DXQUATERNION	vRot;
		virtual ~mItem(){}
	};

	//map<オブジェクトのポジション,WallItem>
	multimap<float,mItem*> m_ItemMap_Memory;	//全てのDescItem
	multimap<float,mItem*> m_ItemMap_Target; //描画対象のDescItem
public:
	/////////////////// ////////////////////
	//// 用途       ：Description(	LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice //デバイス
	////			  : LPTATRATEXTURE pTexture  //テクスチャ
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	FMemoryTex(LPDIRECT3DDEVICE9 pD3DDevice,
				LPTATRATEXTURE pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
	/////////////////// ////////////////////
	//// 関数名     ：~FMemoryTex();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~FMemoryTex();
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
	//// 担当者     ：佐藤涼
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
	//// 担当者     ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：void AddDesc( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：Descの追加
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
	////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
	////		    ：  D3DXVECTOR3 &vRot				//回転角
	////		    ：  D3DXVECTOR3 &vPos				//位置
	////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
	////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
	////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
	//// 戻値       ：なし
	//// 担当者     ：佐藤涼
	//// 備考       ：
	void AddMemory(
		const D3DXVECTOR3&		vScale		,
		const D3DXVECTOR3&		vRot		,
		const D3DXVECTOR3&		vPos		,
		const D3DCOLORVALUE&	Diffuse		,
		const D3DCOLORVALUE&	Specular	,
		const D3DCOLORVALUE&	Ambient
	);

/****************************************************
関数名　：void	OrientGoal()
カテゴリ：関数
用途　　：クリア後プレーヤーを動かす
引数　　：なし
戻り値　：なし
担当者　：佐藤涼
備考　　：
****************************************************/
	void	OrientGoal(UpdatePacket& i_UpdatePacket);
};

/******************************************************
class Item : public PrimitiveSphere

用途　：アイテム
担当者：佐藤涼
*******************************************************/
class	GoalObject	:public PrimitiveBox{
	PlayerCoil*			m_pCoil;
	Camera*				m_pCamera;
	SpriteObject*		m_pGoalChar;
	bool				m_bPlaySound;
	OBB					m_Obb;
	float				m_fInitPosY;
	LPTATRATEXTURE	m_pGoalCharTex;
public:
	GoalObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3 vPos,
				LPTATRATEXTURE pTexture,
				LPTATRATEXTURE pGoakCharTex,
				wiz::OBJID id = OBJID_SYS_CLEARAREA
				);
	/////////////////// ////////////////////
	//// 関数名     ：~GoalObject();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~GoalObject();
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
class Factory_Goal;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Goal{
public:
/**************************************************************************
 Factory_Goal(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Goal(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Goal();
//};
};


}
//end of namespace bomberobject.
}
//end of namespace wiz.
