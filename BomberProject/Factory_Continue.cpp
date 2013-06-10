////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Continue.h"
#include "BassItems.h"


namespace wiz{
namespace bomberobject{

/************************************************************************
Dead 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Dead(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Dead::Dead(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_iTime(0)
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
};

/////////////////// ////////////////////
//// 関数名     ：void Dead::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Dead::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void Dead::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Dead::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_iTime > 60 ){
		m_Color.byteColor.a	-= 5;
		if( m_Color.byteColor.a <= 5)
			m_Color.byteColor.a	= 0;

	}
	m_iTime++;
};

/************************************************************************
Continue 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Continue(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Continue::Continue(const LPDIRECT3DDEVICE9 pD3DDevice,const  LPDIRECT3DTEXTURE9 pTexture,const bool mark,
		const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
		const RECT *pRect,const  D3DXVECTOR3 &vCenter,const  D3DXVECTOR3 &vOffsetPos,const  Color color)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_vPos( vPos )
,m_bMark( mark )
,m_pCoil( NULL )
,m_bPushRock( false )
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
};

/////////////////// ////////////////////
//// 関数名     ：void Continue::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Continue::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void Continue::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Continue::Update(UpdatePacket& i_UpdatePacket)
{
	if(m_pCoil == NULL){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
  //マウス用データ*************************
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
  //*****************************************
	if( (MousePos.x > m_vPos.x && MousePos.x < ( m_vPos.x + m_pRect->right )) 
		&& (MousePos.y > m_vPos.y && MousePos.y < ( m_vPos.y + m_pRect->bottom )) ){
		if( g_bMouseLB/* || g_bMouseRB*/ ){
			if( m_bPushRock ){
				if( m_bMark )
					m_pCoil->setReadyContinue(true);
				else
					i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_TITLE;

				m_bPushRock	= false;
			}
		}
		else	m_bPushRock	= true;
		m_Color	= 0xFFFFFFFF;
	}
	else{
		m_Color	= 0xA0FFFFFF;

		if( g_bMouseLB )	m_bPushRock	= false;
		else				m_bPushRock	= true;
	}

};

}
}