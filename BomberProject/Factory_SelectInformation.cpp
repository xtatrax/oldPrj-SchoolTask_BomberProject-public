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
#include "Factory_CustomButtonA.h"
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberobject{
/**************************************************************************
 SelectInformation 定義部
***************************************************************************/
SelectInformation::SelectInformation(
	const LPDIRECT3DDEVICE9		pD3DDevice			,
	const LPTATRATEXTURE	pFrameTexture		,
	const LPTATRATEXTURE	pDescTexture		,
	const LPTATRATEXTURE	pNomalTex			,
	const LPTATRATEXTURE	pHardTexture		,
	const LPTATRATEXTURE	pExtraTexture		,
	const D3DXVECTOR3&			vScale				,
	const D3DXVECTOR3&			vRot				,
	const D3DXVECTOR3&			vPos				,
	const Rect*					pRect				,
	const D3DXVECTOR3&			vCenter				,
	const D3DXVECTOR3&			vOffsetPos			,
	const Color					DefaultFrameColor	,
	const Color					NormalFrameColor	,
	const Color					HardFrameColor		,
	const Color					ExtraFrameColor		,
	const wiz::OBJID			id
)
:SpriteObject( pD3DDevice, pDescTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, 0xFFFFFFFF, id)
,m_SpriteObject(pD3DDevice, pFrameTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, 0xFFFFFFFF, id)
,m_pDescTex(		pDescTexture	)
,m_pNomalTex(	pNomalTex		)
,m_pHardTex(	pHardTexture	)
,m_pExtraTex(	pExtraTexture	)
,m_iPtn(		0				)
,m_pButtonNormal( NULL )
,m_pButtonHard(NULL)	
,m_pButtonExtra(NULL)
,m_pButtonBack(NULL)
,m_DefaultFrameColor(DefaultFrameColor)
,m_NormalFrameColor(NormalFrameColor)
,m_HardFrameColor(HardFrameColor)
,m_ExtraFrameColor(ExtraFrameColor)

{	
}

/**********************************************************
デストラクタ
**********************************************************/
SelectInformation::~SelectInformation()
{
	this->m_pTexture = NULL ;

	//SafeRelease( m_pDescTex );	
	//SafeRelease( m_pNomalTex );	
	//SafeRelease( m_pHardTex );	
	//SafeRelease( m_pExtraTex );		

	m_pButtonNormal = NULL;
	m_pButtonHard = NULL;	
	m_pButtonExtra = NULL;
	m_pButtonBack = NULL;
}

/**********************************************************
描画
**********************************************************/
void	SelectInformation::Draw(DrawPacket &i_DrawPacket)
{

	SpriteObject::Draw( i_DrawPacket );
	m_SpriteObject.Draw( i_DrawPacket );
}

/**********************************************************
更新
**********************************************************/
void	SelectInformation::Update(UpdatePacket &i_UpdatePacket)
{
	if( !m_pButtonNormal ) m_pButtonNormal  = (CustomButtonA*)i_UpdatePacket.SearchObjectFromID(OBJID_UI_BUTTON_NORMAL);
	if( !m_pButtonHard   ) m_pButtonHard    = (CustomButtonA*)i_UpdatePacket.SearchObjectFromID(OBJID_UI_BUTTON_HARD  );
	if( !m_pButtonExtra  ) m_pButtonExtra   = (CustomButtonA*)i_UpdatePacket.SearchObjectFromID(OBJID_UI_BUTTON_EXTRA );
	if( !m_pButtonBack   ) m_pButtonBack    = (CustomButtonA*)i_UpdatePacket.SearchObjectFromID(OBJID_UI_BUTTON_BACK  );

	if( m_pButtonNormal && m_pButtonNormal->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pNomalTex;
			m_SpriteObject.setColor( m_NormalFrameColor );
	}
	else
	if( m_pButtonHard && m_pButtonHard->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pHardTex;
			m_SpriteObject.setColor( m_HardFrameColor );
	}
	else
	if( m_pButtonExtra && m_pButtonExtra->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pExtraTex;
			m_SpriteObject.setColor( m_ExtraFrameColor );
			//Debugger::DBGSTR::addStr(L" R = %d\n",m_ExtraFrameColor.byteColor.r);
			//Debugger::DBGSTR::addStr(L" G = %d\n",m_ExtraFrameColor.byteColor.g);
			//Debugger::DBGSTR::addStr(L" B = %d\n",m_ExtraFrameColor.byteColor.b);
			//	: 緑加算
			if( m_ExtraFrameColor.byteColor.r >= 0xFF && m_ExtraFrameColor.byteColor.b == 0 ){
				m_ExtraFrameColor.byteColor.g += 17;
			}
			//	: 赤減算
			if( m_ExtraFrameColor.byteColor.r > 0 && m_ExtraFrameColor.byteColor.g == 0xFF && m_ExtraFrameColor.byteColor.b == 0){
				m_ExtraFrameColor.byteColor.r -= 17;
			}
			//	: 青加算
			if( m_ExtraFrameColor.byteColor.r <= 1 && m_ExtraFrameColor.byteColor.g >= 0xFE ){
				m_ExtraFrameColor.byteColor.b += 17;
			}
			//	: 緑減算
			if( m_ExtraFrameColor.byteColor.r == 0 && m_ExtraFrameColor.byteColor.g > 0 && m_ExtraFrameColor.byteColor.b == 0xFF){
				m_ExtraFrameColor.byteColor.g -= 17;
			}
			//	: 赤加算
			if( m_ExtraFrameColor.byteColor.g == 0 && m_ExtraFrameColor.byteColor.b >= 0xFF ){
				m_ExtraFrameColor.byteColor.r += 17;
			}
			//	: 青減算
			if( m_ExtraFrameColor.byteColor.r == 0xFF && m_ExtraFrameColor.byteColor.g == 0 && m_ExtraFrameColor.byteColor.b > 0){
				m_ExtraFrameColor.byteColor.b -= 17;
			}

	}
	else
	if( m_pButtonBack && m_pButtonBack->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pDescTex;	
	}
	else{
		//	: 通常時
			m_pTexture	= m_pDescTex;	
			m_SpriteObject.setColor( m_DefaultFrameColor );
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