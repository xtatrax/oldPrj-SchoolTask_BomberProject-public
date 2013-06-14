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
MouseCursor::MouseCursor( LPDIRECT3DDEVICE9 pD3DDevice, TextureManager* m_pTexMgr, float fLineLength, float fPointSize)
:Box( pD3DDevice, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), g_vZero, g_vZero, COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F), COLOR2D3DCOLORVALUE(0x0FFFFF0F),  OBJID_SYS_CURSOR, false, m_pTexMgr->addTexture( pD3DDevice, L"Field.png" ) )
,PrimitiveSprite(pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"CARSOL.tga" ), NULL, D3DXVECTOR3( 92.0f, 67.0f, 0.0f ), g_vZero)
,m_Ptn(0)
,m_MovePosY(0)
,m_pCamera( NULL )
,m_pLine( NULL )
,m_pLine2( NULL )
,m_pTorus( NULL )
,m_fTorusMagnification(0)
{

	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );

	Box::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM*2, (float)MGPRM_MAGNETICUM*2, 0.0f) );
	
	const	D3DXVECTOR3	vDir	= D3DXVECTOR3( cosf( D3DXToRadian(-55.0f) ), sinf( D3DXToRadian(-55.0f) ), 0.0f );
	const	D3DXVECTOR3	vDir2	= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	float		fRange	= 100.0f;

	//m_vScale	= D3DXVECTOR3( 0.125f, 0.125f, 0.0f );
	m_vScale	= D3DXVECTOR3( fPointSize, fPointSize, 0.0f );
	m_pSelectPos	= new SpriteObject( pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"point.png" ), m_vScale,
										g_vZero, g_vZero, NULL, D3DXVECTOR3( 16.0f, 16.0f, 0.0f ), g_vZero );

	m_pLine			= new Line( g_vZero, vDir, fRange, 0xFFFFFF00 );
	m_pLine2		= new Line( m_pLine->getEndPos(), vDir2, fLineLength, 0xFFFFFF00 );

	m_pTorus	= new Torus(
		pD3DDevice,
		0.01f,
		1.0f,
		g_vZero,
		g_vZero,
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		COLOR2D3DCOLORVALUE(0x80FFFFFF),
		OBJID_UNK,
		false,
		NULL,
		36,
		150
	);
	
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
	m_MovePosY	= 0 ;
	SafeDelete( m_pLine	 )	;
	SafeDelete( m_pLine2 )	;
	SafeDelete( m_pTorus )	;
	SafeDelete( m_pSelectPos )	;
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

	static float s_fTimeCount = 0.0f;

	Update2DPos();

	//	: 座標の更新
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);

	//	: 行列の算出
	m_mMatrix = m_mScale * mPos ;

	Update3DPos();

	m_pLine->setMatrix( m_mMatrix );
	m_pLine2->setMatrix( m_mMatrix );

	D3DXMATRIX mPos2, mScale, mRot;

	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
	m_mMatrix = mScale * mPos ;
	m_pSelectPos->setMatrix( m_mMatrix );

	D3DXMatrixTranslation(&mPos2, m_v3DPos.x, m_v3DPos.y, m_v3DPos.z);
	D3DXMatrixScaling(&mScale, m_fTorusMagnification,m_fTorusMagnification,0.0f);
	D3DXMatrixRotationZ(&mRot, 0.0f);
	m_pTorus->CalcMatrix(mPos2, mScale, mRot);

	if(m_fTorusMagnification >= CURSOR_FIELD_LENGHT){
		m_fTorusMagnification = CURSOR_FIELD_LENGHT;
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeCount >= CURSOR_FIELD_TIME){		
			m_fTorusMagnification = 0.0f;
			s_fTimeCount		  = 0.0f;
		}
	}
	else{
		m_fTorusMagnification += CURSOR_FIELD_LENGHT * i_UpdatePacket.pTime->getElapsedTime();
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
	//PrimitiveSprite::Draw(i_DrawPacket);
	//Box::Draw(i_DrawPacket);
	m_pLine->draw(i_DrawPacket.pD3DDevice);
	m_pLine2->draw(i_DrawPacket.pD3DDevice);
	m_pSelectPos->Draw(i_DrawPacket);
	if(m_pCamera)m_pTorus->Draw(i_DrawPacket);
}
void MouseCursor::Update2DPos(){
	//	: カーソルの設定
	//	: マウスのクライアント座標を獲得
	GetCursorPos( &m_v2DPos ) ;
	ScreenToClient( wiz::DxDevice::m_hWnd , &m_v2DPos) ;

	
}
void MouseCursor::Update3DPos(){
	if( m_pCamera ){

		float fYPosCorrection = 10.0f ;
		//	: マウス座標の３Ｄ変換
		m_v3DPos = D3DXVECTOR3( 
			(float)m_v2DPos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ,
			(( STANDARD_WINDOW_HEIGHT - m_v2DPos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION -
											MAGNETIC_RADIUS +  m_pCamera->getPosY() - fYPosCorrection  , 0.0f
		);
		SetBasePos( m_v3DPos );


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
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac, float fLineLength, float fPointSize){
	try{

 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};

		fpac->m_pVec->push_back(
			new MouseCursor( 
						fpac->pD3DDevice,
						fpac->m_pTexMgr,
						fLineLength,
						fPointSize
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