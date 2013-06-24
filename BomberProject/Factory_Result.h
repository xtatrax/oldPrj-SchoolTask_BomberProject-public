////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Result.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Result ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{

enum Result_Rank{
	Rank_S	= 1,
	Rank_A,
	Rank_B,
	Rank_C
};

/************************************************************
class  Rank  : public SpriteObject

用途　：ランク
担当者：佐藤涼
************************************************************/
class	Rank	: public	SpriteObject{
	bool				m_bDrawing;
	LPDIRECT3DTEXTURE9	m_pTex_S;
	LPDIRECT3DTEXTURE9	m_pTex_A;
	LPDIRECT3DTEXTURE9	m_pTex_B;
	LPDIRECT3DTEXTURE9	m_pTex_C;
public:
	Rank(	LPDIRECT3DDEVICE9	pD3DDevice,
			LPDIRECT3DTEXTURE9	pTex_S,
			LPDIRECT3DTEXTURE9	pTex_A,
			LPDIRECT3DTEXTURE9	pTex_B,
			LPDIRECT3DTEXTURE9	pTex_C,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect	= NULL,
			wiz::OBJID	id		= OBJID_UI_RANK
	);
	~Rank();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	setDrawing( bool i_bDraw, int i_iRank ){
		m_bDrawing	= i_bDraw;

		switch( i_iRank ){
			case	1:
				m_pTexture	= m_pTex_S;
				break;
			case	2:
				m_pTexture	= m_pTex_A;
				break;
			case	3:
				m_pTexture	= m_pTex_B;
				break;
			case	4:
				m_pTexture	= m_pTex_C;
				break;
			default	 :
				break;
		};
	}
};

/**************************************************************************
class Factory_Result;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Result{
public:
/**************************************************************************
 Factory_Result(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Result( FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint );
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Result();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
