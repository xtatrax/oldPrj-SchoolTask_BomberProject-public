////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Goal.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Goal ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Goal.h"
#include "Factory_Player.h"

namespace wiz{

/******************************************************
class	Item	: public PrimitiveSphere
用途 : アイテム
*******************************************************/
class	GoalObject	:public PrimitiveBox{
	PlayerCoil*	m_pCoil;
	struct GoalItem{
		D3DMATERIAL9 m_Material;
		D3DXMATRIX	m_Matrix;
		D3DXVECTOR3 m_vScale ;
		D3DXVECTOR3 m_vPos ;
		D3DXQUATERNION m_vRot;
		OBB			m_Obb;
		virtual ~GoalItem(){}
	};
	//map<オブジェクトのポジション,GoalItem>
	multimap<float,GoalItem*> m_ItemMap_All;	//全てのGoalItem
public:
	GoalObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void addGoal(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
	void GetOBBList( float Index, list<OBB>& ObbList );
};

/**************************************************************************
 class Factory_Goal;
 用途: メイン工場クラス
****************************************************************************/
	class Factory_Goal{
	public:
	/**************************************************************************
	 Factory_Goal(
		LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
		vector<Object*>& vec,			//オブジェクトの配列
		TextureManager& TexMgr		//テクスチャの配列
	);
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
	};
}
//end of namespace wiz.
