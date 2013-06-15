////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Gage.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：ゲージファクトリー
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
//const static float	 = 0xA0 ;
//const static float	byGaugeAlpha = 0xA0 ;
namespace wiz{
namespace bomberobject{

/**************************************************************************
 Gage 定義部
***************************************************************************/
/************************************************************************
 関数名     ：Gage::Gage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPDIRECT3DTEXTURE9 pTex        // テクスチャ―
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：D3DXVECTOR3 &vDirOffset        // 描画オフセット
　　　　：RECT* vRect                    // 描画範囲
　　　　：RECT* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************************************************/
Gage::Gage(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTex		,
	const D3DXVECTOR3			&vScale		,
	const D3DXVECTOR3			&vRot		,
	const D3DXVECTOR3			&vPos		,
	const D3DXVECTOR3			&vDirOffset	,
	const RECT					GaugeRect	,		//	: 描画範囲
	const RECT					FrameRect	,		//	: 描画範囲
	const wiz::OBJID			id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	NULL,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_BassRect(  GaugeRect )
,m_GaugeRect( GaugeRect )
,m_FrameRect( FrameRect )
,m_fRate( 0.0f )
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
	m_fRate -= fAddValue ;
	if( m_fRate <= 0.0f ){
		m_fRate = 0.0f ;
	}
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
	m_fRate += fSubValue ;
	if( m_fRate >= 1.0f ){
		m_fRate = 1.0f ;
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
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Gage::Update( UpdatePacket& i_UpdatePacket ){
	//ゲージの描画
	m_GaugeRect.right  = m_BassRect.left - m_BassRect.right ;
	m_GaugeRect.right *= 1.0f - m_fRate ;
	
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
	m_pRect	= m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//ゲージの描画
	m_pRect	= m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 SuperGage 定義部
***************************************************************************/
/************************************************************************
 関数名     ：SuperGage::SuperGage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPDIRECT3DTEXTURE9 pTex        // テクスチャ―
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：D3DXVECTOR3 &vDirOffset        // 描画オフセット
　　　　：RECT* vRect                    // 描画範囲
　　　　：RECT* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************************************************/
SuperGage::SuperGage(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vScale		,
	D3DXVECTOR3			&vRot		,
	D3DXVECTOR3			&vPos		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	GaugeRect,FrameRect,id)
,m_vBassPos(vPos)
,m_vScale( vScale )
,m_vRot( vRot )
,m_pCursor( NULL )
,m_pLineTop( NULL )
,m_pLineLeft( NULL )
,m_pLineBottom( NULL )
,m_pLineRight( NULL )
,m_bAcquired(false)
{
	m_fRate = 0.0f;

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
	m_pCursor = NULL;
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
	m_pRect	= m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//ゲージの描画
	m_pRect	= m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );

	if(m_bAcquired){
		m_pLineTop->draw(i_DrawPacket.pD3DDevice);
		m_pLineLeft->draw(i_DrawPacket.pD3DDevice);
		m_pLineBottom->draw(i_DrawPacket.pD3DDevice);
		m_pLineRight->draw(i_DrawPacket.pD3DDevice);
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
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void SuperGage::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);

	D3DXMATRIX	mPos, mScale, mRot ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x + m_vBassPos.x - m_GaugeRect.right * m_vScale.x;
	vPos.y	= (float)m_pCursor->get2DPos().y + m_vBassPos.y;
	vPos.z	= 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x/2, m_vScale.y, m_vScale.z );
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mRot * mPos ;

	//アイテム獲得時のエフェクト
	if(m_bAcquired)Update_Line();

	//ゲージ用に座標のみ再計算
	vPos.x		= (float)m_pCursor->get2DPos().x + m_vBassPos.x ;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_Matrix	= mScale * mRot * mPos ;
	//ゲージの描画
	m_GaugeRect.right  = /*m_BassRect.left -*/ m_BassRect.right ;
	m_GaugeRect.right *= 0.0f + m_fRate ;
	
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
	D3DXMATRIX		mLineScale, mLinePos;
	D3DXVECTOR3		vLineScale	= D3DXVECTOR3(1.0f,1.0f,0.0f),vLinePos, 
					vBaseLinePos = D3DXVECTOR3((float)m_pCursor->get2DPos().x + m_vBassPos.x/**0.225f*/,
												(float)m_pCursor->get2DPos().y + m_vBassPos.y,0.0f);
	static float	s_fMovingDistance	= 0.0f; 

	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );

	//上部
	vLineScale;
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y - s_fMovingDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineTop->setMatrix( mLineScale * mLinePos );

	//左部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - s_fMovingDistance, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineLeft->setMatrix( mLineScale * mLinePos );

	//下部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y + s_fMovingDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineBottom->setMatrix( mLineScale * mLinePos );

	//右部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + s_fMovingDistance, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineRight->setMatrix( mLineScale * mLinePos );
	
	s_fMovingDistance	+= 0.8f;
	if(s_fMovingDistance >= 6.0f){
		s_fMovingDistance	= 0.0f;
		m_bAcquired = false;
	}	
}

/**************************************************************************
 MagneticGage_N 定義部
***************************************************************************/
/************************************************************************
 関数名     ：MagneticGage_N::MagneticGage_N(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPDIRECT3DTEXTURE9 pTex        // テクスチャ―
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：RECT* vRect                    // 描画範囲
　　　　：RECT* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：本多寛之
備考　　：
*************************************************************************/
MagneticGage_N::MagneticGage_N(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vScale		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
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
	m_pCursor  = NULL;
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
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticGage_N::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);
	Gage::Update(i_UpdatePacket);
	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x	;
	vPos.y	= (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
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
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPDIRECT3DTEXTURE9 pTex        // テクスチャ―
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：RECT* vRect                    // 描画範囲
　　　　：RECT* vRect2                   // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：本多寛之
備考　　：
*************************************************************************/
MagneticGage_S::MagneticGage_S(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vScale		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
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
	m_pCursor = NULL;
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
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticGage_S::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);
	Gage::Update(i_UpdatePacket);
	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;
	vPos.x	 = (float)m_pCursor->get2DPos().x	;
	vPos.y	 = (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	 = 0.0f	;
	//vPos	+= m_v;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
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
		//スーパーモード用ゲージ
		fpac->m_pVec->push_back(
			new SuperGage(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_Super5.png" ),
				D3DXVECTOR3(0.4f,0.25f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				//D3DXVECTOR3(950.0,30.0f,0.0f),
				//D3DXVECTOR3(140.0,-55.0f,0.0f),
				D3DXVECTOR3(38.0f,-35.0f,0.0f),
				Rect(0,32,512,64),
				Rect(0,0,512,32)
			)
		);

		//磁界N用ゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_N4.png" ),
				//D3DXVECTOR3( 60.0f,-250.0f,0.0f),
				D3DXVECTOR3( 60.0f,-450.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,32,-300,64),
				Rect(0,0,300,32)
				//Rect(0,32,-300,64),
				//Rect(0,0,256,32)
			)
		);
		//磁界用Sゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_S4.png" ),
				//D3DXVECTOR3( 60.0f,-220.0f,0.0f),
				D3DXVECTOR3( 60.0f,-410.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,32,-300,64),
				Rect(0,0,300,32)
				//Rect(0,32,-256,64),
				//Rect(0,0,256,32)
			)
		);
				//D3DXVECTOR3( 80.0f,-170.0f,0.0f),
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
