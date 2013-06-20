////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_SelectInformation.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：セレクト画面の説明ウインドウ
//					▼
//	namespace wiz;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_SelectInformation.h"
//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberobject{
/**************************************************************************
 SelectInformation 定義部
***************************************************************************/
SelectInformation::SelectInformation(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTexture	,
	const LPDIRECT3DTEXTURE9	pNomalTex	,
	const LPDIRECT3DTEXTURE9	pHardTexture	,
	const LPDIRECT3DTEXTURE9	pExtraTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const RECT*					pRect		,
	const D3DXVECTOR3&			vCenter		,
	const D3DXVECTOR3&			vOffsetPos	,
	const Color					color		,
	const wiz::OBJID			id
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color, id)
,m_pTex(		pTexture		)
,m_pNomalTex(	pNomalTex		)
,m_pHardTex(	pHardTexture	)
,m_pExtraTex(	pExtraTexture	)
,m_iPtn(		0				)
{	
}

/**********************************************************
デストラクタ
**********************************************************/
SelectInformation::~SelectInformation()
{
}

/**********************************************************
描画
**********************************************************/
void	SelectInformation::Draw(DrawPacket &i_DrawPacket)
{
	SpriteObject::Draw( i_DrawPacket );
}

/**********************************************************
更新
**********************************************************/
void	SelectInformation::Update(UpdatePacket &i_UpdatePacket)
{
	switch( m_iPtn ){
		case	0:
			m_pTexture	= m_pTex;
			break;
		case	1:
			m_pTexture	= m_pNomalTex;
			break;
		case	2:
			m_pTexture	= m_pHardTex;
			break;
		case	3:
			m_pTexture	= m_pExtraTex;
			break;
		default:
			break;
	}
}
/**************************************************************************
 Factory_SelectInformation 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Factory_SelectInformation(FactoryPacket* fpac)
//// カテゴリ   ：コンストラクタ
//// 用途       ：チェックポイントでセーブする機能を作成します
//// 引数       ：  FactoryPacket* fpac
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
Factory_SelectInformation::Factory_SelectInformation(FactoryPacket* fpac){
	
};


}
}