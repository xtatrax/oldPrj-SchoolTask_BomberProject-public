////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：タイトルファクトリー
//					▼
//	namespace wiz;
//		class Factory_Title ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Title.h"
#include "Factory_Sound.h"

const D3DXVECTOR3 MAGNET_FIELD_POS_1 = D3DXVECTOR3( 230.0f, 370.0f, 0.0f );
const D3DXVECTOR3 MAGNET_FIELD_POS_2 = D3DXVECTOR3( 290.0f, 460.0f, 0.0f );
const D3DXVECTOR3 MAGNET_FIELD_POS_3 = D3DXVECTOR3( 170.0f, 460.0f, 0.0f );

namespace wiz{
namespace bomberobject{

/*************************************************************************
class ClickChar  public SpriteObject

担当者：佐藤涼
用途　：クリックを促す
*************************************************************************/
class	ClickChar	: public SpriteObject{
	MouseCursor*	m_pCursor;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vOffsetPos;
public:
	ClickChar(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vOffsetPos
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/*************************************************************************
class Title_Select  public SpriteObject

担当者：佐藤涼
用途　：タイトル画面のボタン
*************************************************************************/
class	Title_Select	: public SpriteObject{
	D3DXVECTOR3		m_vPos		;
	DWORD			m_dNext		;
	int				m_iTime		;
	bool			m_bPush		;
	bool			m_bPushRock	;
	bool			m_bSelect	;
	bool			m_bCanSelect;
public:
	Title_Select(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const DWORD					next		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF,
		bool						bCanSelect	= true
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setCanSelect( bool b ){
		m_bCanSelect	= b;
	}
};

/*************************************************************************
class MagnetField  public SpriteObject

担当者：本多寛之
用途　：磁界
*************************************************************************/
class	MagnetField	: public SpriteObject{
	//Coil*			m_pCoil;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRot;
	float			m_fRotZ;
	int				m_iNowPosNum;
public:
	MagnetField(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const D3DXVECTOR3&			vCenter		,
		const RECT*					pRect		
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	float	getRotZ(){
		return m_fRotZ;
	}
	D3DXVECTOR3 getPos(){
		return m_vPos;
	}
	int getNowPosNum(){
		return m_iNowPosNum;
	}
	void setNowPos(int i_iNum){
		m_iNowPosNum = i_iNum;
		switch(m_iNowPosNum){
			case 1:
				m_vPos = MAGNET_FIELD_POS_1;
				break;
			case 2:
				m_vPos = MAGNET_FIELD_POS_2;
				break;
			case 3:
				m_vPos = MAGNET_FIELD_POS_3;
				break;
			default:
				break;
		}
	}
};

/*************************************************************************
class Coil  public SpriteObject

担当者：本多寛之
用途　：コイル
*************************************************************************/
class	Coil	: public SpriteObject{
	MagnetField*	m_pMagnetField;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vScale;
	D3DXVECTOR3		m_vRot;
	float			m_fRotZ;
public:
	Coil(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const D3DXVECTOR3&			vCenter		,
		const RECT*					pRect		
	);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	float	getRotZ(){
		return m_fRotZ;
	}
	D3DXVECTOR3 getPos(){
		return m_vPos;
	}
};

/**************************************************************************
class Factory_Title;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Title{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Title(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Title();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
