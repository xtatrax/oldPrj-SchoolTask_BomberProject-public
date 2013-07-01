////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：タイトルファクトリー
//					▼
//	namespace wiz;
//		class Load ;
//		class Factory_Load ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Load.h"
#include "Factory_Sound.h"


namespace wiz{
namespace bomberobject{

/*************************************************************************
class Load  public SpriteObject

担当者：佐藤涼
用途　：タイトル画面のボタン
*************************************************************************/
class	Load	: public SpriteObject{
	Command			m_Com;
	D3DXVECTOR3		m_vPos;
	int				m_iTime;
	float			m_fRate;
	int				m_iPtn;
public:
	Load(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Command*				Com			,
		const Color					color		= 0xFFFFFFFF
	);
	~Load();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
class Factory_Load;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Load{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Load(FactoryPacket* fpac,Command* Com);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Load();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
