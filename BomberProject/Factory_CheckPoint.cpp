////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_CheckPoint.h"
#include "Factory_Player.h"
#include "BassItems.h"
const float CHECK_POINT_RADIUS = 0.25f ;
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.0f, 1.0f, 0.0f, 1.0f } ;
namespace wiz{
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_ActiveItem( NULL )
{
	
}
CheckPoint::~CheckPoint(){
	SafeDeletePointerContainer( m_ItemContainer ) ;
}
/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec, typeid(PlayerCoil) );
	if( !m_pCamera ) m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA );
	
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){

		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;
		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->fPosY);
		}
	}
};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹 本多寛之(編集)
//// 備考       ：
////            ：
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){

		float DrawEndLength = m_pCamera->getPosY() - DRAW_TOLERANCE ;
		if(  DrawEndLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_ActiveItem++ ;
			if(m_ActiveItem <= m_ItemContainer.size()) return ;
		}

		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;
			CalcWorldMatrix();
			Cylinder::Draw( i_DrawPacket );
			
			OBB obb = OBB( m_BasePos, m_BaseQt, m_BaseScale );
			//DrawOBB(i_DrawPacket);
			//m_pCoil->HitTestWall();
		}
	}
};

/**************************************************************************
 Factory_CheckPoint 定義部
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,1.0f,1.0f,1.0f};
			
			CheckPoint* pcp ;
			fpac->m_pVec->push_back(
				pcp = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp->add( 30.0f );

			CheckPoint* pcp2 ;
			fpac->m_pVec->push_back(
				pcp2 = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp2->add( 40.0f );

		}
		
		catch(...){
			//再throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//なにもしない
	}
}//end of namespace wiz.