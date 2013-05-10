////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Item;
//		class Bar;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

const	float	VanishArea	= 0.2f;		//	: アイテムを消すエリア
const	float	SuctionArea	= 5.0f;		//	: アイテムが吸いよる範囲
const	float	SpeedRate	= 0.05f;	//	: アイテムの速さ調整倍率

namespace wiz{

/******************************************************
class	Item	: public PrimitiveSphere
用途 : アイテム
*******************************************************/
class	Item	: public PrimitiveSphere {
protected:
	struct BallItem{
		//マテリアル
		D3DMATERIAL9 m_Material;
		//マトリックス
		D3DXMATRIX m_mMatrix;
		//サイズ
		D3DXVECTOR3	m_Size;
		//対象との距離
		float	m_fDistance;
		//オブジェクトの位置(中心)
		D3DXVECTOR3	m_Pos;
		//派生クラスを作ってもClear()関数で
		//削除できるように仮想デストラクタにしておく
		virtual ~BallItem(){}
	};
	multimap<float,BallItem*> m_ItemMap_All;	//全てのBallItem
public:
	Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void	addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
};
/************************************************
class Bar : public SpriteObject
用途 : エネルギーバー
*************************************************/
class Bar : public SpriteObject{
	int m_Time;
public:
	Bar(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		LPDIRECT3DTEXTURE9 pTex,		//	: コア部分のTexture
		D3DXVECTOR3 &vScale,			//	: 伸縮
		D3DXVECTOR3 &vRot,				//	: 回転
		D3DXVECTOR3 &vPos,				//	: 位置
		D3DXVECTOR3 &vDirOffset,		//	: 描画オフセット
		RECT* vRect = NULL,				//	: 描画範囲
		wiz::OBJID id	=OBJID_UNK		//	: ID
	);

	void	Recovery();	//	: エネルギーの回復
	void	Consume();	//	: エネルギーの消費
    void	Draw(DrawPacket& i_DrawPacket) ;
};


/**************************************************************************
 class Factory_Item;
 用途: メイン工場クラス
****************************************************************************/
	class Factory_Item{
	public:
	/**************************************************************************
	 Factory_Item(
		LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
		vector<Object*>& vec,			//オブジェクトの配列
		TextureManager& TexMgr		//テクスチャの配列
	);
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
//end of namespace wiz.
