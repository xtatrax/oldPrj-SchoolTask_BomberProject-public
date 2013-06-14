////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Continue.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：コンテニュー
//					▼
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
namespace wiz{
namespace bomberobject{

/*************************************************************************
class Reply  public SpriteObject

担当者：佐藤涼
用途　：コンテニュー時のボタン
*************************************************************************/
class	Reply	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	bool			m_bPushRock;
	bool			m_bWhichDraw;
public:
	Reply(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
	void	setWhichDraw(bool b){
		m_bWhichDraw	= b;
	}
};

/*************************************************************************
class Dead  public SpriteObject

担当者：佐藤涼
用途　：死亡時に出す文字
*************************************************************************/
class	Dead	: public SpriteObject{
	int	m_iTime;
public:
	Dead(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	BYTE	getAlpha(){
		return m_Color.byteColor.a;
	}
};

/*************************************************************************
class Continue  public SpriteObject

担当者：佐藤涼
用途　：コンテニュー時のボタン
*************************************************************************/
class	Continue	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	bool			m_bPushRock;
	bool			m_bWhichDraw;

	PlayerCoil*		m_pCoil;
	Reply*			m_pReply_Yes;
	Reply*			m_pReply_No;
	SpriteObject*	m_pRethinking;
	SpriteObject*	m_pContinueChar				;	//	: コンテニューロゴのポインタ

	LPDIRECT3DTEXTURE9	m_pRethinkingTex;	//Really?
	LPDIRECT3DTEXTURE9	m_pAnswerTex	;	//Yes : No
	LPDIRECT3DTEXTURE9	m_pContinueTex	;	//Yes : No
public:
	Continue(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pTexture_Rethinking	,
		const LPDIRECT3DTEXTURE9	pTexture_Answer		,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Continue();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
};

}
}