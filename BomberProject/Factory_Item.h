////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Item;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"

const	float		VanishArea			= 1.5f;		//	: アイテムを消すエリア
const	float		SuctionArea			= 5.0f;		//	: アイテムが吸いよる範囲
const	float		SpeedRate			= 0.05f;	//	: アイテムの速さ調整倍率
const	float		RECOVERY_POINT		= 0.01f;
const	float		RECOVERY_POINT_L	= 0.10f;

const	float		ITEM_TYPE_NULL		= 0.0f;
const	D3DXVECTOR3 ITEM_SCALE			= D3DXVECTOR3(0.5f,0.5f,0.5f);		
const   float		ItemDiffusionRate	= 1.0f;
//enum ITEM_TYPE{
//	ITEM_TYPE_NULL,
//	ITEM_TYPE_RECOVETY,
//	ITEM_TYPE_RECOVETY_BIG
//};

namespace wiz{
namespace bomberobject{

/******************************************************
class  Item : public PrimitiveSphere

用途　：アイテム
担当者：佐藤涼
編集  ：鴫原 徹
*******************************************************/
class	Item	: public PrimitiveSphere {
protected:
	PlayerCoil*	m_pPlayerCoil	;
	SuperGage*	m_pSuperGage	;
	Camera*		m_pCamera		;
	struct BallItem{
		D3DMATERIAL9	m_Material	;		//マテリアル
		D3DXMATRIX		m_mMatrix	;		//マトリックス
		D3DXVECTOR3		m_Size		;		//サイズ
		float			m_fDistance	;		//対象との距離
		D3DXVECTOR3		m_Pos		;		//オブジェクトの位置(中心)
		float			m_fMapKey	;
		bool			m_bHidden	;
		//float			m_fItemType ;
		float			m_fRecoveryPoint;
		//派生クラスを作ってもClear()関数で
		//削除できるように仮想デストラクタにしておく
		virtual ~BallItem(){}
	};
	typedef multimap<float,BallItem*>	ALLCONTAINER	;
	typedef list<BallItem*>				TARGETCONTAINER ;
	ALLCONTAINER		m_ItemMap_All		;	//全てのBallItem
	TARGETCONTAINER		m_ItemMap_Target	;	//描画対象のアイテム
	void	setDrawTarget();
public:
	Item(FactoryPacket* fpac,LPTATRATEXTURE pTexture, wiz::OBJID id);
	/////////////////// ////////////////////
	//// 関数名     ：~Item();
	//// カテゴリ   ：デストラクタ
	//// 用途       ：破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	~Item();

    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void	addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,
					float itemType = RECOVERY_POINT);
};

/**************************************************************************
 class Factory_Item;

 用途　：メイン工場クラス
 担当者：佐藤涼
****************************************************************************/
class Factory_Item{
public:
/**************************************************************************
 Factory_Item(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Item(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Item();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
