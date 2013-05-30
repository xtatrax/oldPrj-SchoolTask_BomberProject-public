////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Mouse.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：曳地 大洋
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Mouse ;
//

#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Cursor.h"

namespace wiz{
/**************************************************************************
 MouseCursor 定義部
****************************************************************************/
/**************************************************************************
 MouseCursor::MouseCursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
MouseCursor::MouseCursor( LPDIRECT3DDEVICE9 pD3DDevice, TextureManager* m_pTexMgr)
:Cylinder( pD3DDevice, 1.0f, 1.0f, 0.01f,g_vZero,g_vZero, COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F),  OBJID_3D_CURSOR)
,PrimitiveSprite(pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"MouseCursor.png" ), NULL, D3DXVECTOR3( 22.0f, 22.0f, 0.0f ), g_vZero)
,m_pMouseTex( m_pTexMgr->addTexture( pD3DDevice, L"MouseCursor.png" ) )
,m_Ptn(0)
,m_MovePosY(0)
{

	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );
	Cylinder::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM, (float)MGPRM_MAGNETICUM, 0.0f) );
	m_pCamera = NULL;

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
void MouseCursor::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		m_pCamera && (m_MovePosY	= m_pCamera->getPosY());
	}


	//	: カーソルの設定
	//	: マウスのクライアント座標を獲得
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	
	//	: 座標の更新
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)MousePos.x, (float)MousePos.y, 0.0f);

	//	: 行列の算出
	m_mMatrix = m_mScale * mPos ;


	if( m_pCamera ){

		//	: マウス座標の３Ｄ変換
		D3DXVECTOR3 vCursol = D3DXVECTOR3( 
			(float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ,
			(( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION -
											MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_MovePosY ) ,
			0.0f
		);
		SetBasePos( vCursol );

		Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , vCursol.x , vCursol.y, vCursol.z ) ;

		Cylinder::CalcWorldMatrix();

	}
	++m_Ptn;
}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：本多寛之
//// 備考       ：
void MouseCursor::Draw(DrawPacket& i_DrawPacket)
{
	PrimitiveSprite::Draw(i_DrawPacket);
	Cylinder::Draw(i_DrawPacket);
}


/**************************************************************************
 Factory_Cursor 定義部
****************************************************************************/
/**************************************************************************
 Factory_Cursor::Factory_Cursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};

		fpac->m_pVec->push_back(
			new MouseCursor( 
						fpac->pD3DDevice,
						fpac->m_pTexMgr
						
			)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Cursor::~Factory_Cursor();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Cursor::~Factory_Cursor(){
    //なにもしない
}

}
//end of namespace wiz.