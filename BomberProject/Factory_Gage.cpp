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
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DXVECTOR3 &vDirOffset,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_Rect( vRect )
,m_Rect2( vRect2 )

{
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
void Gage::Recovery( int i_iValue, int i_iMaxValue ){
	if(m_Rect2.right < i_iMaxValue){
		m_pRect->right	+= i_iValue;
		if( m_Rect2.right > i_iMaxValue )
			m_pRect->right	= i_iMaxValue;
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
void Gage::Consume( int i_iValue ){
	if(m_Rect2.right > 0){
		m_Rect2.right	-= i_iValue;
		if(m_Rect2.right < 0){
			m_Rect2.right	= 0;
		}
	}
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
	m_pRect	= m_Rect;
	SpriteObject::Draw( i_DrawPacket );
	//ゲージの描画
	m_pRect	= m_Rect2;
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
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	vRect,vRect2)
{
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
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
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
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_Super.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(144.0f,550.0f,0.0f),
				Rect(0,0,512,32),
				Rect(0,32,0,256)
			)
		);

		//磁界N用ゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_N.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(120.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
			)
		);
		//磁界用Sゲージ
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_S.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(420.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
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
