////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Gage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之(編集)
//	内包データと備考	：ゲージファクトリー
//					▼
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Gage.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"
const static BYTE	byGaugeAlpha = 0xFF ;
namespace wiz{
namespace bomberobject{

/******************************************************
 SuperNotice 定義部
******************************************************/
/****************************************************
用途　：コンストラクタ
担当者：佐藤涼
****************************************************/
SuperNotice::SuperNotice(const LPDIRECT3DDEVICE9 pD3DDevice, const LPTATRATEXTURE pTex,
		const D3DXVECTOR3 &vScale, const D3DXVECTOR3 &vPos, const Rect Rect, const wiz::OBJID id)
		:SpriteObject( pD3DDevice, pTex, vScale, g_vZero, vPos, &Rect, g_vZero, g_vZero,-1 , id, false )
,m_vPos( vPos )
,m_vScale( vScale )
,m_pCursor( NULL )
,m_fMovePos( 0 )
,m_vInitPos( vPos )
,m_bDraw( false )
{
}

/****************************************************
用途　：デストラクタ
担当者：佐藤涼
****************************************************/
SuperNotice::~SuperNotice()
{
	m_pCursor = NULL;
}

/***************************************************
用途　：描画
担当者：佐藤涼
***************************************************/
void	SuperNotice::Draw(DrawPacket &i_DrawPacket)
{
	if( m_bDraw ){
		SpriteObject::Draw( i_DrawPacket );
	}
}

/***************************************************
用途　：更新
担当者：佐藤涼
***************************************************/
void	SuperNotice::Update(UpdatePacket &i_UpdatePacket)
{
	if( !m_pCursor ) m_pCursor = (MouseCursor*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR);

	if( !m_pCursor ) return ;

	m_vPos.x	 = (float)m_pCursor->get2DPos().x +  30.0f + m_vInitPos.x + m_fMovePos ;
	m_vPos.y	 = (float)m_pCursor->get2DPos().y + -60.0f + m_vInitPos.y ;

	if( m_pCursor->getReverse() )
			m_fMovePos	= -(185.0f);
	else	m_fMovePos	= 0.0f;

	D3DXMATRIX	mScale, mPos;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
	D3DXMatrixTranslation( &mPos, m_vPos.x, m_vPos.y, m_vPos.z );
	m_mMatrix	= mScale * mPos;
}

/******************************************************
 Relationship_Gage 定義部
******************************************************/
/****************************************************
用途　：コンストラクタ
担当者：佐藤涼
****************************************************/
Relationship_Gage::Relationship_Gage(const LPDIRECT3DDEVICE9 pD3DDevice, const LPTATRATEXTURE pTex,
		const D3DXVECTOR3 &vScale, const D3DXVECTOR3 &vRot, const D3DXVECTOR3 &vPos, const Rect Rect, const wiz::OBJID id)
		:SpriteObject( pD3DDevice, pTex, vScale, g_vZero, vPos, &Rect, g_vZero, g_vZero,-1 ,id,false )
,m_vPos( vPos )
,m_vScale( vScale )
,m_pCursor( NULL )
,m_fMovePos( 0 )
{
}

/****************************************************
用途　：デストラクタ
担当者：佐藤涼
****************************************************/
Relationship_Gage::~Relationship_Gage()
{
	m_pCursor = NULL;
}

/***************************************************
用途　：描画
担当者：佐藤涼
***************************************************/
void	Relationship_Gage::Draw(DrawPacket &i_DrawPacket)
{
	SpriteObject::Draw( i_DrawPacket );
}

/***************************************************
用途　：更新
担当者：佐藤涼
***************************************************/
void	Relationship_Gage::Update(UpdatePacket &i_UpdatePacket)
{
	if( !m_pCursor ) m_pCursor = (MouseCursor*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR);

	if( !m_pCursor ) return ;

	m_vPos.x	 = (float)m_pCursor->get2DPos().x +  30.0f + m_fMovePos ;
	m_vPos.y	 = (float)m_pCursor->get2DPos().y + -60.0f ;

	if( m_pCursor->getReverse() )
			m_fMovePos	= -(185.0f);
	else	m_fMovePos	= 0.0f;

	D3DXMATRIX	mScale, mPos;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
	D3DXMatrixTranslation( &mPos, m_vPos.x, m_vPos.y, m_vPos.z );
	m_mMatrix	= mScale * mPos;
}

/**************************************************************************
 Gage 定義部
***************************************************************************/
/************************************************************************
 関数名     ：Gage::Gage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPTATRATEXTURE pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                Rect* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPTATRATEXTURE pTex        // テクスチャ—
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：D3DXVECTOR3 &vDirOffset        // 描画オフセット
　　　　：Rect* vRect                    // 描画範囲
　　　　：Rect* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************************************************/
Gage::Gage(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPTATRATEXTURE	pTex		,
	const D3DXVECTOR3			&vScale		,
	const D3DXVECTOR3			&vRot		,
	const D3DXVECTOR3			&vPos		,
	const D3DXVECTOR3			&vDirOffset	,
	const Rect					GaugeRect	,		//	: 描画範囲
	const Rect					FrameRect	,		//	: 描画範囲
	const wiz::OBJID			id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	NULL,g_vZero,vDirOffset,0xFFFFFFFF,id,false)
,m_BassRect(  GaugeRect )
,m_GaugeRect( GaugeRect )
,m_FrameRect( FrameRect )
,m_fRate( 1.0f )
,m_fMovePos( 0.0f )
{
	m_mGaugeMatrix = m_mMatrix ;
}
Gage::~Gage(){
	m_pRect = NULL ;
}
/****************************************
関数名　　：void Gage::Recovery()
カテゴリ　：関数
用途　　　：エネルギー充填
引数　　　：int i_iValue		//減らす値
         　：int i_iMaxValue	//ゲージの最大値
戻り値　　：
担当者　　：佐藤涼 本多寛之(編集)
備考　　　：
*****************************************/
void Gage::Recovery( float fAddValue ){
	m_fRate += (fAddValue) ;
	if( m_fRate >= 1.0f ){
		m_fRate = 1.0f ;
	}
	else if( m_fRate <= 0.0f )
		m_fRate	= 0.0f;
}
/*****************************************
 関数名　　：void Gage::Consume()
 カテゴリ　：関数
 用途　　　：エネルギー消費
 引数　　　：
 戻り値　　：
 担当者　　：佐藤涼 本多寛之(編集)
 備考　　　：
 *****************************************/
void Gage::Consume( float fSubValue ){
	m_fRate -= (fSubValue) ;
	if( m_fRate <= 0.0f ){
		m_fRate = 0.0f ;
	}
	else if( m_fRate >= 1.0f )
		m_fRate	= 1.0f;
}
/////////////////// ////////////////////
//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Gage::Update( UpdatePacket& i_UpdatePacket ){
	//ゲージの描画
	m_GaugeRect.right  = m_BassRect.right ;
	m_GaugeRect.right  = (LONG)( m_GaugeRect.right * m_fRate ) ;
	
}

/**************************************************************
関数名　　：void Gage::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket    //描画用のデータもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************/
void Gage::Draw(DrawPacket& i_DrawPacket){
	//枠の描画
	m_pRect	= &m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//ゲージの描画
	m_pRect	= &m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 SuperGage 定義部
***************************************************************************/
/************************************************************************
 関数名     ：SuperGage::SuperGage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPTATRATEXTURE pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                Rect* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPTATRATEXTURE pTex        // テクスチャ—
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：D3DXVECTOR3 &vDirOffset        // 描画オフセット
　　　　：Rect* vRect                    // 描画範囲
　　　　：Rect* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************************************************/
SuperGage::SuperGage(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPTATRATEXTURE	pTex		,
	D3DXVECTOR3			&vScale		,
	D3DXVECTOR3			&vRot		,
	D3DXVECTOR3			&vPos		,
	Rect				GaugeRect	,
	Rect				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	GaugeRect,FrameRect,id)
,m_vBassPos(vPos)
,m_vScale( vScale )
,m_vRot( vRot )
,m_fLineMoveDistance( 0.0f )
,m_bAcquired(false)
,m_pCursor( NULL )
,m_pLineTop( NULL )
,m_pLineLeft( NULL )
,m_pLineBottom( NULL )
,m_pLineRight( NULL )
,m_pSuperNotice( NULL )
{
	const	D3DXVECTOR3	vDirTop		= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirLeft	= D3DXVECTOR3( cosf( D3DXToRadian(90.0f) ), sinf( D3DXToRadian(90.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirBottom	= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirRight	= D3DXVECTOR3( cosf( D3DXToRadian(90.0f) ), sinf( D3DXToRadian(90.0f) ), 0.0f );
	const	float	fRangeW	= 100.0f;
	const	float	fRangeH	= 5.0f;
	m_pLineTop		= new Line( g_vZero, vDirTop,	 fRangeW, 0xFF00FFFF );
	m_pLineLeft		= new Line( g_vZero, vDirLeft,	 fRangeH, 0xFF00FFFF );
	m_pLineBottom	= new Line( m_pLineLeft->getEndPos(), vDirBottom, fRangeW, 0xFF00FFFF );
	m_pLineRight	= new Line( m_pLineTop->getEndPos(), vDirRight,	 fRangeH, 0xFF00FFFF );
}

/////////////////// ////////////////////
//// 関数名     ：~SuperGage();
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
SuperGage::~SuperGage(){
	m_pCursor		= NULL;
	m_pSuperNotice	= NULL;
	SafeDelete( m_pLineTop );
	SafeDelete( m_pLineLeft );
	SafeDelete( m_pLineBottom );
	SafeDelete( m_pLineRight );
}

/**************************************************************
関数名　　：void SuperGage::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket    //描画用のデータもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************/
void SuperGage::Draw(DrawPacket& i_DrawPacket){

	//枠の描画
	m_mMatrix = m_Matrix ;
	m_pRect	= &m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//ゲージの描画
	m_pRect	= &m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );

	if(m_bAcquired){
		m_pLineTop->draw(i_DrawPacket.GetDevice());
		m_pLineLeft->draw(i_DrawPacket.GetDevice());
		m_pLineBottom->draw(i_DrawPacket.GetDevice());
		m_pLineRight->draw(i_DrawPacket.GetDevice());
	}
}
/////////////////// ////////////////////
//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void SuperGage::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR);
	if( !m_pSuperNotice ) m_pSuperNotice = (SuperNotice*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_NOTICE);

	if( !m_pCursor ) return ;
	if( !m_pSuperNotice ) return ;

	D3DXMATRIX	mPos, mScale, mRot ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x + m_vBassPos.x - m_GaugeRect.right * m_vScale.x;
	vPos.y	= (float)m_pCursor->get2DPos().y + m_vBassPos.y;
	vPos.z	= 0.0f	;
	if( m_pCursor->getReverse() ){
		////	:

		///*//
		//vPos.x -= g_GaugeReverseSize.cx + 40;
		////*/
		//D3DXMATRIX m;
		//D3DXMatrixScaling( &m, -1,1,1);
		//D3DXMatrixMultiply(&mScale,&mScale,&m);
		////*//
	}
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mRot * mPos ;

	//アイテム獲得時のエフェクト
	if(m_bAcquired)Update_Line();

	//ゲージ用に座標のみ再計算
	vPos.x		= (float)m_pCursor->get2DPos().x + m_vBassPos.x ;
	if( m_pCursor->getReverse() ){
		///*//
		//vPos.x -= g_GaugeReverseSize.cx + 40;
		vPos.x -=  85;
		//*/
		D3DXMATRIX m;
		D3DXMatrixScaling( &m, -1,1,1);
		D3DXMatrixMultiply(&mScale,&mScale,&m);
		//*//
	}
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_Matrix	= mScale * mRot * mPos ;
	//ゲージの描画
	m_GaugeRect.right  = /*m_BassRect.left -*/ m_BassRect.right ;
	m_GaugeRect.right  = (LONG)( m_GaugeRect.right * (1.0f - m_fRate)) ;

	if( m_pSuperNotice ){
		if( m_fRate <= 0.0f )
			m_pSuperNotice->setDraw( true );
		else
			m_pSuperNotice->setDraw( false );
	}
}

/////////////////// ////////////////////
//// 関数名     ：SuperGage::Update_Line()
//// カテゴリ   ：関数
//// 用途       ：Lineの更新
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
void SuperGage::Update_Line(){
	if( !m_pCursor ) return ;

	D3DXMATRIX		mLineScale, mLinePos;
	D3DXVECTOR3		vLineScale	= D3DXVECTOR3(1.0f,1.0f,0.0f),vLinePos, 
					vBaseLinePos = D3DXVECTOR3((float)m_pCursor->get2DPos().x + m_vBassPos.x/**0.225f*/,
												(float)m_pCursor->get2DPos().y + m_vBassPos.y,0.0f);

	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );

	int	iDir	= 1;
	if( m_pCursor->getReverse() ){
		vBaseLinePos.x	-= 85.0f;
		iDir	*= -1;
		//*/
		D3DXMATRIX m;
		D3DXMatrixScaling( &m, -1,1,1);
		D3DXMatrixMultiply(&mLineScale,&mLineScale,&m);
		//*//
	}

	//上部
	vLineScale;
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y - m_fLineMoveDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineTop->setMatrix( mLineScale * mLinePos );

	//左部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - m_fLineMoveDistance*iDir, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineLeft->setMatrix( mLineScale * mLinePos );

	//下部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y + m_fLineMoveDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineBottom->setMatrix( mLineScale * mLinePos );

	//右部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + m_fLineMoveDistance*iDir, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineRight->setMatrix( mLineScale * mLinePos );
	
	m_fLineMoveDistance	+= 0.8f;
	if(m_fLineMoveDistance >= 6.0f){
		m_fLineMoveDistance	= 0.0f;
		m_bAcquired = false;
	}	
}

/**************************************************************************
 MagneticGage_N 定義部
***************************************************************************/
/************************************************************************
 関数名     ：MagneticGage_N::MagneticGage_N(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPTATRATEXTURE pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                Rect* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPTATRATEXTURE pTex        // テクスチャ—
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：Rect* vRect                    // 描画範囲
　　　　：Rect* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：本多寛之
備考　　：
*************************************************************************/
MagneticGage_N::MagneticGage_N(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPTATRATEXTURE	pTex		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vScale		,
	Rect				GaugeRect	,
	Rect				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_pCoil( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
	m_fMovePos	= GAUGE_POS_LOW;
}
/////////////////// ////////////////////
//// 関数名     ：~MagneticGage_N();
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
MagneticGage_N::~MagneticGage_N(){
	m_pCursor	= NULL;
	m_pCoil		= NULL;
}
/////////////////// ////////////////////
//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticGage_N::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil )	 m_pCoil	= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);
	if( !m_pCoil ) return ;

	if( !m_pCursor ) m_pCursor = (MouseCursor*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR);
	if( !m_pCursor ) return ;

	Gage::Update(i_UpdatePacket);

	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x	;
	vPos.y	= (float)m_pCursor->get2DPos().y + m_fMovePos;
	vPos.z	= 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
	if( m_pCursor->getReverse() ){
		D3DXMATRIX m;
		D3DXMatrixScaling( &m, -1,1,1);
		D3DXMatrixMultiply(&mScale,&mScale,&m);
		//*//
	}
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mPos ;

}

/**************************************************************
関数名　　：void MagneticGage_N::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket    //描画用のデータもろもろ
戻り値　　：
担当者　　：本多寛之
備考　　　：
***************************************************************/
void MagneticGage_N::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 MagneticGage_S 定義部
***************************************************************************/
/************************************************************************
 関数名     ：MagneticGage_S::MagneticGage_S(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPTATRATEXTURE pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                Rect* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPTATRATEXTURE pTex        // テクスチャ—
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：Rect* vRect                    // 描画範囲
　　　　：Rect* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：本多寛之
備考　　：
*************************************************************************/
MagneticGage_S::MagneticGage_S(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPTATRATEXTURE	pTex		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vScale		,
	Rect				GaugeRect	,
	Rect				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_pCoil( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
	m_fMovePos	= GAUGE_POS_HIGH;
}
/////////////////// ////////////////////
//// 関数名     ：~MagneticGage_N();
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
MagneticGage_S::~MagneticGage_S(){
	m_pCursor	= NULL;
	m_pCoil		= NULL;
}
/////////////////// ////////////////////
//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticGage_S::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil )		 m_pCoil	= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);
	if( !m_pCoil )	return;

	if( !m_pCursor ) m_pCursor = (MouseCursor*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR);
	if( !m_pCursor ) return ;

	Gage::Update(i_UpdatePacket);

	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;

	vPos.x	 = (float)m_pCursor->get2DPos().x	;
	vPos.y	 = (float)m_pCursor->get2DPos().y + m_fMovePos	;
	vPos.z	 = 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
	if( m_pCursor->getReverse() ){
		D3DXMATRIX m;
		D3DXMatrixScaling( &m, -1,1,1);
		D3DXMatrixMultiply(&mScale,&mScale,&m);
		//*//
	}
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mPos ;

}

/**************************************************************
関数名　　：void MagneticGage_S::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket    //描画用のデータもろもろ
戻り値　　：
担当者　　：本多寛之
備考　　　：
***************************************************************/
void MagneticGage_S::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 Factory_Item 定義部
****************************************************************************/
/**************************************************************************
関数名　　：Factory_Item::Factory_Item( FactoryPacket* fpac );
カテゴリ　：コンストラクタ
用途　　　：
引数　　　：FactoryPacket* fpac     // もろもろのデータ
戻り値　　：
担当者　　：佐藤涼 本多寛之(編集)
備考　　　：
***************************************************************************/
Factory_Gage::Factory_Gage(FactoryPacket* fpac){
	try{

		//ゲージの種類
		fpac->AddObject(
			new Relationship_Gage(
				fpac->GetDevice(),
				fpac->AddTexture( L"GAGE1.png" ),
				D3DXVECTOR3( 0.25f, 0.25f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				Rect( 0, 192, 32, 256 )
			)
		);

		//スーパーモード用ゲージ
		fpac->AddObject(
			new SuperGage(
				fpac->GetDevice(),
				fpac->AddTexture( L"GAGE2.png" ),
				D3DXVECTOR3(0.4f,0.25f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(43.0f,-35.0f,0.0f),
				Rect(0,160,256,192),
				Rect(0,128,256,160)
			)
		);

		//磁界N用ゲージ
		fpac->AddObject(
			new MagneticGage_N(
				fpac->GetDevice(),
				fpac->AddTexture( L"GAGE3.png" ),
				D3DXVECTOR3( 105.0f,-410.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,32,256,64),
				Rect(0,0,256,32)
			)
		);
		//磁界用Sゲージ
		fpac->AddObject(
			new MagneticGage_S(
				fpac->GetDevice(),
				fpac->AddTexture( L"GAGE4.png" ),
				D3DXVECTOR3( 105.0f,-410.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,64,256,96),
				Rect(0,0,256,32)
			)
		);

		//Ready
		fpac->AddObject(
			new SuperNotice(
				fpac->GetDevice(),
				fpac->AddTexture( L"GAGE5.png" ),
				D3DXVECTOR3( 0.5f, 0.25f, 0.0f ),
				D3DXVECTOR3( 35.0f, 25.0f, 0.0f ),
				Rect( 0, 96, 120, 128 )
			)
		);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 関数名　　：Factory_Item::~Factory_Item();
 カテゴリ　：デストラクタ
 用途　　　：
 引数　　　：
 戻り値　　：
 担当者　　：佐藤涼
 備考　　　：
***************************************************************************/
Factory_Gage::~Factory_Gage(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
