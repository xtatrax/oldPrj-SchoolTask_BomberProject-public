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
namespace bomberobject{

/**************************************************************************
 MouseCursor 定義部
****************************************************************************/
LineCursor::LineCursor( LPDIRECT3DDEVICE9 pD3DDevice ){

	UINT iVertexSize = 0;

	//	: 頂点バッファの生成（内包できる領域のサイズ、データの扱い、頂点データの中身、頂点データを管理するメモリ、生成されたバッファを示すアドレスが帰ってくる））
	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * iVertexSize , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	


	m_pVertex[ 0 ] = Vertex(D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 1 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 2 ] = Vertex(D3DXVECTOR3( 0.2f , 1.0f , 0.0f ) , 0xFFFFFFFF );
	m_pVertex[ 3 ] = Vertex(D3DXVECTOR3( 1.0f , 1.0f , 0.0f ) , 0xFFFFFFFF );


	m_pVertexBuffer->Unlock();



}
/******************************************************************************
void VertexLineState::Draw(
	LPDIRECT3DDEVICE9 pD3DDevice ,	//デバイス
	const D3DXMATRIX& i_Matrix		//描画したいプレートの配列
	)
用途 : 正方形のプレートを描画
戻り値 : なし
******************************************************************************/
void LineCursor::Draw(LPDIRECT3DDEVICE9 pD3DDevice , const D3DXMATRIX& i_Matrix )
{
	 pD3DDevice->SetRenderState( D3DRS_LIGHTING , FALSE );

	//if( m_pTexture ) pD3DDevice->SetTexture( 0 , m_pTexture->getTexture() );			//	: テクスチャを設定（NULL の場合はテクスチャ無し）

	 //ワールド変換行列を設定
	pD3DDevice->SetTransform( D3DTS_WORLD , &i_Matrix );								//変換済み頂点の場合は無視される

	//	: 頂点バッファを用いてモデルを描画する
	pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: 描画対象となる頂点バッファを設定
	pD3DDevice->SetFVF( Vertex::getFVF() );											//	: 頂点データの形式を設定
	//pD3DDevice->DrawPrimitive( m_PrimitiveType , 0, m_iDrawPrimitiveVertexNum );	//	: 頂点データの描画（描画の仕方、描画開始位置、プリミティブ数）


	pD3DDevice->SetTexture( 0 , NULL );												//	: テクスチャを設定（NULL の場合はテクスチャ無し）
	pD3DDevice->SetRenderState( D3DRS_LIGHTING , TRUE );

}


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
:Box( pD3DDevice, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), g_vZero, g_vZero, COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F),  OBJID_SYS_CURSOR, false, m_pTexMgr->addTexture( pD3DDevice, L"Field.png" ) )
,PrimitiveSprite(pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"CARSOL.tga" ), NULL, D3DXVECTOR3( 92.0f, 67.0f, 0.0f ), g_vZero)
,m_Ptn(0)
,m_MovePosY(0)
,m_pCamera( NULL )
{

	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );

	Box::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM*2, (float)MGPRM_MAGNETICUM*2, 0.0f) );


	m_pCursorLine = new NameLineEffect( pD3DDevice, NULL, 1);
	m_pCursorLine->AddNameLineEffect( pD3DDevice, g_vZero, g_vOne);
}

/////////////////// ////////////////////
//// 用途       ：~MouseCursor();
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
MouseCursor::~MouseCursor(){
	m_MovePosY = 0 ;
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
	GetCursorPos( &m_v2DPos ) ;
	ScreenToClient( g_hWnd , &m_v2DPos) ;
	
	//	: 座標の更新
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);

	//	: 行列の算出
	m_mMatrix = m_mScale * mPos ;



	UpdateCursor();
	m_pCursorLine->setPos(m_v3DPos);

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
	m_pCursorLine->Draw(i_DrawPacket.pD3DDevice,*i_DrawPacket.pVec,NULL,*i_DrawPacket.pCommand);
	//PrimitiveSprite::Draw(i_DrawPacket);
	Box::Draw(i_DrawPacket);
}

void MouseCursor::UpdateCursor(){
	if( m_pCamera ){

		float fYPosCorrection = 10.0f ;
		//	: マウス座標の３Ｄ変換
		m_v3DPos = D3DXVECTOR3( 
			(float)m_v2DPos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ,
			(( STANDARD_WINDOW_HEIGHT - m_v2DPos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION -
											MAGNETIC_RADIUS +  m_pCamera->getPosY() - fYPosCorrection  ,
			0.0f
		);
		SetBasePos( m_v3DPos );

		Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_v3DPos.x , m_v3DPos.y, m_v3DPos.z ) ;

		Box::CalcWorldMatrix();
	}
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
//end of namespace bomberobject.
}
//end of namespace wiz.