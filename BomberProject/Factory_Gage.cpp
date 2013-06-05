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
const static BYTE	byGaugeAlpha = 0x70 ;
//const static float	 = 0xA0 ;
//const static float	byGaugeAlpha = 0xA0 ;
namespace wiz{

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
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vScale		,
	D3DXVECTOR3			&vRot		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vDirOffset	,
	RECT				GaugeRect	,		//	: 描画範囲
	RECT				FrameRect	,		//	: 描画範囲
	wiz::OBJID			id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	NULL,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_BassRect(  GaugeRect )
,m_GaugeRect( GaugeRect )
,m_FrameRect( FrameRect )
,m_fRate( 1.0f )
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
	m_fRate += fAddValue ;
	if( m_fRate >= 1.0f ){
		m_fRate = 1.0f ;
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
	m_fRate -= fSubValue ;
	if( m_fRate <= 0.0f ){
		m_fRate = 0.0f ;
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
	m_GaugeRect.top  = m_BassRect.bottom - m_BassRect.top ;
	m_GaugeRect.top *= 1.0f - m_fRate ;
	
	Debugger::DBGSTR::addStr( L" Rate = %f \n", m_fRate);
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
	//ゲージの描画
	m_pRect	= m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );
	//枠の描画
	m_mMatrix = m_mGaugeMatrix ;
	m_pRect	= m_FrameRect;
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
	GaugeRect,FrameRect)
,m_vBassPos(vPos)
{
	m_fRate = 0.0f;
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

	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	= m_vBassPos.x	;
	vPos.y	= m_vBassPos.y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

	Gage::Draw( i_DrawPacket );
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
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect)
,m_pCursor( NULL )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
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
	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x	;
	vPos.y	= (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

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
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect)
,m_pCursor( NULL )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
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
	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	 = (float)m_pCursor->get2DPos().x	;
	vPos.y	 = (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	 = 0.0f	;
	//vPos	+= m_v;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(950.0,30.0f,0.0f),
				Rect(112,0,143,272),
				Rect(144,0,175,272)
			)
		);

		//磁界N用ゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3(-170.0f,-140.0f,0.0f),
				Rect(0,0,113,272),
				Rect(0,0,0,0)
			)
		);
		//磁界用Sゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3( +60.0f,-140.0f,0.0f),
				Rect(179,0,290,272),
				Rect(0,0,0,0)
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
//end of namespace wiz.
