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
ScrollObject::ScrollObject(const LPDIRECT3DDEVICE9 pD3DDevice, const LPTATRATEXTURE pTexture,
							const D3DXVECTOR3& vScale, const D3DXVECTOR3& vPos, Rect pRect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, &pRect, g_vZero, g_vZero, 0xFFFFFFFF , OBJID_UI_SPRITE, true)
,m_vPos1(g_vZero)
,m_vPos2(D3DXVECTOR3(0.0f,(float)pRect.top-pRect.bottom,0.0f))
,m_vScale(vScale)
{

	//グラデーション
	//LPTATRATEXTURE pTex = NULL;
	//for( BYTE i = 0 ; i < g_csbySpriteQty ; i++ ){
	//	0(pD3DDevice,L"BGP_TITLE02.png",&pTex2);
	//	g_pBGSpriteArr[i] = new SpriteObject(
	//		pD3DDevice,
	//		pTex2,
	//		vScale,
	//		g_vZero,
	//		D3DXVECTOR3( 0.0f, i*(-600.0f) , 0.0f ),// iのところはあとでへんこうしる！
	//		NULL,
	//		g_vZero,
	//		g_vZero
	//	);
	//	g_vPos[i]	= D3DXVECTOR3( 0.0f, i*(-600.0f) , 0.0f );
	//}
	////背景
	//g_pFrontSprite = new SpriteObject(
	//	pD3DDevice,
	//	pFrontTexture,
	//	g_vOne,
	//	g_vZero,
	//	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	//	NULL,
	//	g_vZero,
	//	g_vZero,
	//	0xFFFFFFFF
	//);

}
void ScrollObject::Update( UpdatePacket& i_UpdatePacket) {
	//for(int i = 0; i < g_csbySpriteQty; i++){
	//	if( g_pBGSpriteArr[i] != NULL ){
	//		g_vPos[i].y += 0.6f;
	//		if(g_vPos[i].y >= 600.0f){
	//			g_vPos[i].y = -600.0f;
	//		}
	//	}
	//}
	D3DXMATRIX mScale, mPos;

	m_vPos1.y += 0.6f;
	if(m_vPos1.y >= BASE_CLIENT_HEIGHT)m_vPos1.y = -BASE_CLIENT_HEIGHT;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos1.x,m_vPos1.y,m_vPos1.z);
	m_Matrix1 = mScale * mPos;

	m_vPos2.y += 0.6f;
	if(m_vPos2.y >= BASE_CLIENT_HEIGHT)m_vPos2.y = -BASE_CLIENT_HEIGHT;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos2.x,m_vPos2.y,m_vPos2.z);
	m_Matrix2 = mScale * mPos;

};
void ScrollObject::Draw( DrawPacket& i_DrawPacket )
{
	//for(int i = 0;i < g_csbySpriteQty; i++){
	//	if( g_pBGSpriteArr[i] != NULL ){
	//		D3DXMATRIX	mPos;
	//		D3DXMatrixTranslation( &mPos, g_vPos[i].x, g_vPos[i].y, g_vPos[i].z );
	//		g_pBGSpriteArr[i]->setMatrix( mPos );
	//		g_pBGSpriteArr[i]->Draw( i_DrawPacket );
	//	}
	//}
	//if( g_pFrontSprite != NULL )
	//	g_pFrontSprite->Draw( i_DrawPacket );
	setMatrix(m_Matrix1);
	SpriteObject::Draw(i_DrawPacket);
	setMatrix(m_Matrix2);
	SpriteObject::Draw(i_DrawPacket);
};
/**************************************************************************
 ScrollObject::~ScrollObject();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ScrollObject::~ScrollObject()
{
	//SAFE_DELETE(g_pFrontSprite);
	//for( BYTE i = 0 ; i < g_csbySpriteQty ; i++ ){
	//	SAFE_DELETE(g_pBGSpriteArr[i]);
	//}
}
/**************************************************************************
 Factory_Scroll 定義部
****************************************************************************/
Factory_Scroll::Factory_Scroll(FactoryPacket* fpac)
{
	try{
		//LPTATRATEXTURE pTex = NULL;
		//LPTATRATEXTURE pTex2 = NULL ;
		//0(fpac->pD3DDevice,L"BGP_TITLE01.png",&pTex);
		//0(fpac->pD3DDevice,L"BGP_TITLE02.png",&pTex2);
		//fpac->m_pVec->push_back(
		//	new ScrollObject(
		//		fpac->pD3DDevice,
		//		pTex/*fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"BGP_TITLE01.png" )*/,
		//		pTex2/*fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"BGP_TITLE02.png" )*/,
		//		D3DXVECTOR3( 1.0f, 1.0f, 0.2f )
		//	)
		//);
		LPTATRATEXTURE pTex = NULL ;
		fpac->m_pVec->push_back( new ScrollObject(fpac->pD3DDevice,fpac->AddTexture(L"Title_Back2.png"),D3DXVECTOR3( 1.0f, 1.0f, 0.0f),g_vZero,Rect(0,0,(int)BASE_CLIENT_WIDTH,(int)BASE_CLIENT_HEIGHT)));
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
