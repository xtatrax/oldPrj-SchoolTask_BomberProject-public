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
	LPTATRATEXTURE	m_pRankTex;
	LPTATRATEXTURE	m_pFrameTex;
	Result_Rank			m_ResultRank;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vRot;
	D3DXVECTOR3			m_vScale;
public:
	Rank(	LPDIRECT3DDEVICE9	pD3DDevice,
			LPTATRATEXTURE	pRankTex,
			LPTATRATEXTURE	pFrameTex,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect	= NULL,
			wiz::OBJID	id		= OBJID_UI_RANK
	);
	~Rank();
	void	Draw(DrawPacket& i_DrawPacket);

	void	setDrawing( bool i_bDraw, Result_Rank i_iRank ){
		m_bDrawing		= i_bDraw;
		m_ResultRank	= i_iRank;

	}

	void setRect( Result_Rank i_iRank ){
		switch( i_iRank ){
			case	Rank_S:
				m_pRect->left	= 0;
				m_pRect->top	= 0;
				m_pRect->right	= 128;
				m_pRect->bottom	= 128;
				//m_pRect	= Rect( 0, 0, 128, 128 );
				break;
			case	Rank_A:
				m_pRect->left	= 128;
				m_pRect->top	= 0;
				m_pRect->right	= 256;
				m_pRect->bottom	= 128;
				//m_pRect	= Rect( 128, 0, 256, 128 );
				break;
			case	Rank_B:
				m_pRect->left	= 0;
				m_pRect->top	= 128;
				m_pRect->right	= 128;
				m_pRect->bottom	= 256;
				//m_pRect	= Rect( 0, 128, 128, 256 );
				break;
			case	Rank_C:
				m_pRect->left	= 128;
				m_pRect->top	= 128;
				m_pRect->right	= 256;
				m_pRect->bottom	= 256;
				//m_pRect	= Rect( 128, 128, 256, 256 );
				break;
			default	 :
				m_pRect->left	= 128;
				m_pRect->top	= 128;
				m_pRect->right	= 256;
				m_pRect->bottom	= 256;
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
