////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Mouse.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：曳地 大洋
//  引継ぎ			：鴫原 徹
//	編集			：佐藤 涼
//	内包ﾃﾞｰﾀと備考	：ゲーム内カーソル関連
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class Factory_Mouse ;
//

#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Cursor.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 MouseCursor 定義部
****************************************************************************/
/**************************************************************************
 MouseCursor::MouseCursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPTATRATEXTURE pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
MouseCursor::MouseCursor( LPDIRECT3DDEVICE9 pD3DDevice,  float fLineLength, float fPointSize,LPTATRATEXTURE pCenterPointTex)
:Box( pD3DDevice, g_vOne, g_vZero, g_vZero, D3DCOLORVALUE(), D3DCOLORVALUE(), D3DCOLORVALUE(),  OBJID_SYS_CURSOR, false,  NULL )
,PrimitiveSprite(pD3DDevice, NULL, NULL, D3DXVECTOR3( 92.0f, 67.0f, 0.0f ), g_vZero)
,m_SelectPos( pD3DDevice, pCenterPointTex,&Rect(128-8,96,128,106), D3DXVECTOR3( 4.0f, 4.0f, 0.0f ), g_vZero, -1 ,false)
,m_Line( g_vZero, D3DXVECTOR3( cosf( D3DXToRadian(-55.0f) ), sinf( D3DXToRadian(-55.0f) ), 0.0f ), 100.0f, g_YellowColor.dwColor )
,m_Line2( m_Line.getEndPos(), D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f ), fLineLength, g_YellowColor.dwColor )
,m_Ptn(0)
,m_MovePosY(0)
,m_pCamera( NULL )
,m_pCoil( NULL )
,m_pTorus( NULL )
,m_fTorusMagnification(0)
,m_fTorusTimeCount(0.0f)
,m_bIsReverse(false)

{

	//	: 
	D3DXVECTOR3 vScale = D3DXVECTOR3(0.5f,0.5f,0.0f);
	D3DXMatrixScaling( &m_mScale, vScale.x, vScale.y, vScale.z );

	Box::SetBaseScale( D3DXVECTOR3( (float)MGPRM_MAGNETICUM*2, (float)MGPRM_MAGNETICUM*2, 0.0f) );
	
	m_vScale	= D3DXVECTOR3( fPointSize, fPointSize, 0.0f );


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
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
MouseCursor::~MouseCursor(){
	m_MovePosY	= 0 ;
	m_pCamera = ( NULL ) ;
	m_pCoil   = ( NULL ) ;
	SafeDelete( m_pTorus )	;
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
void MouseCursor::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil   ) m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);
	if( !m_pCamera ){
		m_pCamera = (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA);
		m_pCamera && (m_MovePosY	= m_pCamera->getPosY());
	}


	//	: マウスの2D座標をアップデート
	Update2DPos();

	Update3DPos();



	//Box::CalcWorldMatrix();

	m_Line.setMatrix( m_mMatrix );
	m_Line2.setMatrix( m_mMatrix );

	//	: ポイントの更新***********************************************
	D3DXMATRIX mMatrix, mPos, mScale2 ;
	D3DXMatrixScaling( &mScale2, m_vScale.x, m_vScale.y, 0.0f);
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);

	mMatrix	= mScale2 * mPos;
	m_SelectPos.setMatrix( mMatrix );
	//*******************************************************************

	D3DXMATRIX mPos2, mScale, mRot;


	D3DXMatrixTranslation(&mPos2, m_v3DPos.x, m_v3DPos.y, m_v3DPos.z);
	D3DXMatrixScaling(&mScale, m_fTorusMagnification,m_fTorusMagnification,0.0f);
	D3DXMatrixRotationZ(&mRot, 0.0f);
	m_pTorus->CalcMatrix(mPos2, mScale, mRot);

	if(m_fTorusMagnification >= CURSOR_FIELD_LENGHT){
		m_fTorusMagnification = CURSOR_FIELD_LENGHT;
		m_fTorusTimeCount += (float)i_UpdatePacket.GetTime()->getElapsedTime();
		if( m_fTorusTimeCount >= CURSOR_FIELD_TIME){		
			m_fTorusMagnification = 0.0f;
			m_fTorusTimeCount	  = 0.0f;
		}
	}
	else{
		m_fTorusMagnification += CURSOR_FIELD_LENGHT * (float)i_UpdatePacket.GetTime()->getElapsedTime();
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
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：本多寛之
//// 備考       ：
////
void MouseCursor::Draw(DrawPacket& i_DrawPacket)
{
	//PrimitiveSprite::Draw(i_DrawPacket);
	//Box::Draw(i_DrawPacket);
	m_Line.draw(i_DrawPacket.GetDevice());
	m_Line2.draw(i_DrawPacket.GetDevice());
	m_SelectPos.Draw(i_DrawPacket);
	if(m_pCamera)m_pTorus->Draw(i_DrawPacket);
}
/////////////////// ////////////////////
//// 用途       ：void MouseCursor::Update2DPos()
//// カテゴリ   ：関数
//// 用途       ：スクリーン座標上のマウスの位置を更新する
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////
void MouseCursor::Update2DPos(){
	//	: カーソルの設定
	//	: マウスのクライアント座標を獲得
	m_v2DPos = Cursor2D::getPos();

	//	: 座標の更新
	D3DXMATRIX mPos ;
	D3DXMatrixTranslation( &mPos, (float)m_v2DPos.x, (float)m_v2DPos.y, 0.0f);
	//////////
	//	: はんてん
	D3DXMATRIX mScale ;
	if( m_bIsReverse ){
		if(m_pCoil){
			Point poBuf = g_GaugeReverseSize ;
			poBuf.y  = -poBuf.y ;
			poBuf.x  = -poBuf.x ;
			poBuf	+= m_v2DPos ;
			D3DXVECTOR3 vLT = T2DPointTo3DPoint( m_pCamera ,m_v2DPos ) ,
						vRB = T2DPointTo3DPoint( m_pCamera ,poBuf ) ,
						vCPos = m_pCoil->getPos() ;

			if(		vLT.x > m_pCoil->getPos().x +1.0f && vRB.x < m_pCoil->getPos().x +1.0f 
				//&&	vLT.y < m_pCoil->getPos().y && vRB.y > m_pCoil->getPos().y
			){
				m_bIsReverse = false ;
			}

		}
		D3DXMatrixScaling(&mScale, -1.0f,1.0f,1.0f);
		D3DXMatrixMultiply(&mScale,&m_mScale,&mScale);
	}else{
		if(m_pCoil){
			Point poBuf = g_GaugeReverseSize ;
			poBuf.y  = -poBuf.y ;
			poBuf	+= m_v2DPos ;
			D3DXVECTOR3 vLT = T2DPointTo3DPoint( m_pCamera ,m_v2DPos ) ,
						vRB = T2DPointTo3DPoint( m_pCamera ,poBuf ) ,
						vCPos = m_pCoil->getPos() ;

			if(		vLT.x < m_pCoil->getPos().x -1.0f&& vRB.x > m_pCoil->getPos().x  -1.0f
				//&&	vLT.y < m_pCoil->getPos().y && vRB.y > m_pCoil->getPos().y
			){
				m_bIsReverse = true ;
			}
		}	
		D3DXMatrixScaling(&mScale, 1.0f,1.0f,1.0f);
		D3DXMatrixMultiply(&mScale,&m_mScale,&mScale);
	}
	//	: はんてん
	//////////

	//	: 行列の算出
	m_mMatrix = mScale * mPos ;
}
/////////////////// ////////////////////
//// 用途       ：void MouseCursor::Update3DPos()
//// カテゴリ   ：関数
//// 用途       ：3D座標上のマウスの位置を更新する
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////
void MouseCursor::Update3DPos(){
	if( !m_pCamera )return;

	//Debugger::DBGSTR::addStr( L"before  = %d %d\n", Cursor2D::getPos().x,Cursor2D::getPos().y);
	m_v3DPos = Cursor3D::getPos(m_pCamera);
	//Point po = T3DPointTo2DPoint(m_pCamera,m_v3DPos);
	//Debugger::DBGSTR::addStr( L"after   = %d %d\n",po.x,po.y );

	SetBasePos( m_v3DPos );

	//Box::CalcWorldMatrix();
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
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac, float fLineLength, float fPointSize)
{
	try{


 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};
		fpac->AddObject(
			new MouseCursor( 
						fpac->GetDevice(),
						fLineLength,
						fPointSize,
						fpac->AddTexture(L"GAGE0.png")
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