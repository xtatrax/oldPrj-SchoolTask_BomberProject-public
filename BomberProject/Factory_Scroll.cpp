////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Scroll.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤謙吾
//	内包ﾃﾞｰﾀと備考	：スクロールファクトリー
//					▼
//	namespace wiz;
//		class Factory_Scroll ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Scroll.h"
namespace wiz{
namespace bomberobject{
/************************************************************************
ScrollObject 定義部
************************************************************************/
ScrollObject::ScrollObject(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pFrontTexture, LPDIRECT3DTEXTURE9 pBGTexture,D3DXVECTOR3& vScale)
	:Object(OBJID_UI_SPRITE){
	for( BYTE i = 0 ; i < m_csbySpriteQty ; i++ ){
		m_pBGSpriteArr[i] = new SpriteObject(
			pD3DDevice,
			pBGTexture,
			vScale,
			g_vZero,
			D3DXVECTOR3( 0.0f, 0.0f , 0.0f ),// iのところはあとでへんこうしる！
			NULL,
			g_vZero,
			g_vZero
		);
	}
	m_pFrontSprite = new SpriteObject(
		pD3DDevice,
		pFrontTexture,
		g_vOne,
		g_vZero,
		D3DXVECTOR3( 0.0f, 0.0f, 0.1f ),
		//D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		NULL,
		g_vZero,
		g_vZero,
		0xFFFFFFFF
	);

}
void ScrollObject::Update( UpdatePacket& i_UpdatePacket) {
	for(int i = 0; i < m_csbySpriteQty; i++){
		D3DXVECTOR3 vOtherPos = m_pBGSpriteArr[i]->getPos();
		vOtherPos.y += 20.0f;
		if(vOtherPos.y >= 600.0f){
			vOtherPos.y = -600;
		}
		
	}
};
void ScrollObject::Draw( DrawPacket& i_DrawPacket )
{
	for(int i = 0;i < m_csbySpriteQty; i++){
		m_pBGSpriteArr[i]->Draw( i_DrawPacket );
	}
	m_pFrontSprite->Draw( i_DrawPacket );
};
/**************************************************************************
 ScrollObject::~ScrollObject();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ScrollObject::~ScrollObject()
{
}
/**************************************************************************
 Factory_Scroll 定義部
****************************************************************************/
Factory_Scroll::Factory_Scroll(FactoryPacket* fpac)
{
	try{
		fpac->m_pVec->push_back(
			new ScrollObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"BGP_TITLE02.tga" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, /*L"Lightning.tga"*/L"BGP_TITLE01.tga" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.2f )
			)
		);
	}
		catch(...){
		//再throw
		throw;
	}
}

/**************************************************************************
 Factory_Title::~Factory_Title();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Scroll::~Factory_Scroll()
{
//なにもしない
}

}
}
