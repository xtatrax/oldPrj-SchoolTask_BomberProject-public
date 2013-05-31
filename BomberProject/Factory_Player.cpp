////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 曳地大洋(編集) 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Player ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Player.h"
#include "BassItems.h"
#include "Factory_Wall.h"
#include "Factory_Cursor.h"


namespace wiz{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
extern class WallObject ;

/**************************************************************************
 ProvisionalPlayer 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
//ProvisionalPlayer::ProvisionalPlayer(
//	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
//	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
//	D3DXVECTOR3 &vScale,						//	: 伸縮
//	D3DXVECTOR3 &vRot,							//	: 回転
//	D3DXVECTOR3 &vPos,							//	: 位置
//	RECT* pRect,								//	: 描画範囲
//	Color color ,								//	: 色
//	wiz::OBJID id 								//	: ID
//)
//	:MagneticumObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, color, id )
//{
//}
//
///////////////////// ////////////////////
////// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
////// カテゴリ   ：
////// 用途       ：
////// 引数       ：
////// 戻値       ：なし
////// 担当       ：鴫原 徹
////// 備考       ：
//////            ：
//////
//void ProvisionalPlayer::Update( UpdatePacket& i_UpdatePacket ){
//	if( g_bMouseLB || g_bMouseRB){
//		wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
//		D3DXVECTOR3 vMove = g_vZero ;
//		Point MousePos ;
//		GetCursorPos( &MousePos );
//		ScreenToClient( g_hWnd , &MousePos);
//		m_vPos.x = (float)MousePos.x;
//		m_vPos.y = (float)MousePos.y;	
//
//		if( g_bMouseLB )
//			setPoleN() ;
//		if( g_bMouseRB )
//			setPoleS() ;
//
//		//this->m_vPos += vMove * 15.0f ;
//	
//		D3DXMATRIX mPos , mScale ;
//
//		D3DXMatrixTranslation( &mPos , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
//		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
//		m_mMatrix = mScale * mPos ;
//	}else{
//	
//
//	
//	}
//
//	//g_bMouseLB = false ;
//	//g_bMouseRB = false ;
//};

// 3D用
/**************************************************************************
 ProvisionalPlayer3D 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：ProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
ProvisionalPlayer3D::ProvisionalPlayer3D(
	FactoryPacket*	fpac,								//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,						//	: テクスチャー
	LPDIRECT3DTEXTURE9 pTexture2,						//	: テクスチャー２
	D3DXVECTOR3		   &vScale,							//	: 伸縮
	D3DXQUATERNION	   &vRot,							//	: 回転
	D3DXVECTOR3	       &vPos,							//	: 位置
	wiz::OBJID id 										//	: ID
)
	:MagneticumObject3D( fpac->pD3DDevice, pTexture, id )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_MovePosY(0)
,m_Camera(NULL)
,m_MGage_N(NULL)
,m_MGage_S(NULL)
,m_pSound( NULL )
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bCoilWasStarting(false)
,m_bDrawing(false)
,m_enumCoilState(COIL_STATE_START)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	setPoleS();

	//m_Item_Poly.m_pTexture = pTexture2;
	//m_Item_Poly.m_vScale.x = vScale.x;
	//m_Item_Poly.m_vScale.y = vScale.y;
	//m_Item_Poly.m_vScale.z = 0.0f;
	//m_Item_Poly.m_vPos	= vPos;
 //   ::ZeroMemory(&m_Item_Poly.m_Material,sizeof(D3DMATERIAL9));
	//m_Item_Poly.m_Material.Diffuse = D3DCOLORVALUE();
	//m_Item_Poly.m_Material.Specular = D3DCOLORVALUE();
	//m_Item_Poly.m_Material.Ambient = D3DCOLORVALUE();
	////回転の初期化
	//D3DXQuaternionRotationYawPitchRoll(&m_Item_Poly.m_vRot,
	//		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
}
/////////////////// ////////////////////
//// 関数名     ：~ProvisionalPlayer3D();
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
ProvisionalPlayer3D::~ProvisionalPlayer3D(){
	m_Camera = NULL ;
}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////			   ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////			   ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////			   ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////               ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
void ProvisionalPlayer3D::Draw(DrawPacket& i_DrawPacket)
{
	if( m_pSound == NULL )
		m_pSound = (Sound*)SearchObjectFromTypeID(i_DrawPacket.pVec,typeid(Sound));

	if( m_bCoilWasStarting ){
		if( m_bDrawing ){ 
			m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_SETFIELD );
			//テクスチャがある場合
			if(m_pTexture){
				DWORD wkdword;
				//現在のテクスチャステータスを得る
				i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
				//ステージの設定
				i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
				//デフィーズ色とテクスチャを掛け合わせる設定
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

				//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
				// マトリックスをレンダリングパイプラインに設定
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &/*it->second->*/m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(i_DrawPacket);
				i_DrawPacket.pD3DDevice->SetTexture(0,0);
				//ステージを元に戻す
				i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{
			//テクスチャがない場合
				// マトリックスをレンダリングパイプラインに設定
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &/*it->second->*/m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(i_DrawPacket);
			}
			m_pMagneticField->Draw(i_DrawPacket);
			m_pMagneticField2->Draw(i_DrawPacket);
			m_pMagneticField3->Draw(i_DrawPacket);
			m_pMagneticField4->Draw(i_DrawPacket);
		}
	}
}

/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void ProvisionalPlayer3D::Update( UpdatePacket& i_UpdatePacket ){
	if(m_Camera == NULL){
		m_Camera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		m_Camera && (m_MovePosY	= m_Camera->getPosY());
	}
	if( !m_MGage_N )	 m_MGage_N	= (MagneticGage_N*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_N));
	if( !m_MGage_S )	 m_MGage_S	= (MagneticGage_S*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_S));

	RECT rc;
	::GetClientRect(g_hWnd, &rc);

	Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_vPos.x , m_vPos.y, m_vPos.z ) ;

	//if((g_bMouseLB && m_MGage_N->getRect2().right >= MAGNETIC_GAGE_MAX) || (g_bMouseRB && m_MGage_S->getRect2().right >= MAGNETIC_GAGE_MAX)){
	//if(g_bMouseLB)m_MGage_N->Consume(MAGNETIC_GAGE_MAX);
	//if(g_bMouseRB)m_MGage_S->Consume(MAGNETIC_GAGE_MAX);
	//if(g_bMouseLB)m_MGage_N->Consume(1);
	//if(g_bMouseRB)m_MGage_S->Consume(1);
	//m_MGage_N->Recovery(1,MAGNETIC_GAGE_MAX);
	//m_MGage_S->Recovery(1,MAGNETIC_GAGE_MAX);

	if( m_bCoilWasStarting ){
		if( (g_bMouseLB || g_bMouseRB) && !(g_bMouseLB && g_bMouseRB)){ 
			if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){				
				if( !m_bLastMouseLB && !m_bLastMouseRB){
					if(g_bMouseLB)m_MGage_N->Consume(PLAYER_INVOCATION_POINT);
					if(g_bMouseRB)m_MGage_S->Consume(PLAYER_INVOCATION_POINT);
					if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){
						wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
						D3DXVECTOR3 vMove = g_vZero ;
						Point MousePos ;
						GetCursorPos( &MousePos ) ;
						ScreenToClient( g_hWnd , &MousePos) ;

						m_vPos.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
						m_vPos.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_Camera->getPosY() - m_MovePosY ) ;

						if(g_bMouseLB){
							m_pMagneticField->setPole(POLE_N);
							m_pMagneticField2->setPole(POLE_N);
							m_pMagneticField3->setPole(POLE_N);
							m_pMagneticField4->setPole(POLE_N);
						}
						else if(g_bMouseRB){
							m_pMagneticField->setPole(POLE_S);
							m_pMagneticField2->setPole(POLE_S);
							m_pMagneticField3->setPole(POLE_S);
							m_pMagneticField4->setPole(POLE_S);
						}

						//磁界に描画地点を渡す
						m_pMagneticField->SetPos(m_vPos);
						m_pMagneticField2->SetPos(m_vPos);
						m_pMagneticField3->SetPos(m_vPos);
						m_pMagneticField4->SetPos(m_vPos);

						m_pMagneticField->Update(i_UpdatePacket);
						m_pMagneticField2->Update(i_UpdatePacket);
						m_pMagneticField3->Update(i_UpdatePacket);

						m_pMagneticField4->SetPos(m_vPos);
						m_pMagneticField4->Update(i_UpdatePacket);

						if( g_bMouseLB )
							setPoleN() ;
						if( g_bMouseRB )
							setPoleS() ;
					}
				}
				if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){	

					if( g_bMouseLB  && !g_bMouseRB )m_MGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !g_bMouseLB && g_bMouseRB  )m_MGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !g_bMouseLB && g_bMouseRB  )m_MGage_N->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
					if( g_bMouseLB  && !g_bMouseRB )m_MGage_S->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);

					//	: 拡大縮小
					D3DXMATRIX mScale ;
					D3DXMatrixIdentity( &mScale ) ;
					D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z ) ;
					
					//	: 回転
					D3DXMATRIX mRot ;
					D3DXMatrixIdentity( &mRot ) ;
					D3DXMatrixRotationQuaternion( &mRot, &m_vRot ) ;
					
					//	: 移動用
					D3DXMATRIX mMove ;
					D3DXMatrixIdentity( &mMove ) ;
					D3DXMatrixTranslation( &mMove, m_vPos.x, m_vPos.y, m_vPos.z ) ;
					
					//	: ミックス行列
					m_Matrix = mScale * mRot * mMove ;

					//	: マティリアル設定
					m_Material = m_Material ;

					//	: マウスのフラグ
					//g_bMouseLB = false ;
					//g_bMouseRB = false ;
					m_bDrawing	= true;
				}
			}
			else{
				m_bDrawing	= false;
			}
		}else{
			m_bDrawing	= false;
			m_MGage_N->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
			m_MGage_S->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
		}
	}else{
			m_bDrawing	= false;
	}
	m_bLastMouseLB = g_bMouseLB ;
	m_bLastMouseRB = g_bMouseRB ;

	//磁界のエフェクトを動かす
	m_pMagneticField4->Update(i_UpdatePacket);

	if(m_enumCoilState == COIL_STATE_CONTINUE){
		m_MGage_N->setRect2_Right(MAGNETIC_GAGE_MAX);
		m_MGage_S->setRect2_Right(MAGNETIC_GAGE_MAX);
	}
};

/**************************************************************************
 MagneticField 定義部
****************************************************************************/
/***************************************************************************
関数名    ：MagneticField(
                   LPDIRECT3DDEVICE9   pD3DDevice,
                   LPDIRECT3DTEXTURE9  pTexture,
                   D3DXVECTOR3         &vScale,
                   D3DXQUATERNION      &vRot,
                   D3DXVECTOR3         &vPos
              )
カテゴリ　：コンストラクタ
用途      ：
引数　　　：LPDIRECT3DDEVICE9   pD3DDevice    //デバイスなど
　　　　　：LPDIRECT3DTEXTURE9  pTexture      //テクスチャ
　　　　　：D3DXVECTOR3         &vScale       //伸縮
　　　　　：D3DXQUATERNION      &vRot         //回転
　　　　　：D3DXVECTOR3         &vPos         //位置
戻り値　　：
担当者　　：佐藤涼
備考　　　：
****************************************************************************/
MagneticField::MagneticField(
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,						//	: テクスチャー
	D3DXVECTOR3		   &vScale,							//	: 伸縮
	D3DXQUATERNION	   &vRot,							//	: 回転
	D3DXVECTOR3	       &vPos,							//	: 位置
	bool				bEffect
)
:Cylinder(pD3DDevice,vScale.x, vScale.y, vScale.z, g_vZero, g_vZero,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE()
	)
,m_Pole( POLE_N )
,m_bEffect( bEffect )
,m_vNormalSize(vScale)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//再スロー
		throw;
	}
}

/**************************************************************
関数名     ：void	 MagneticField::Draw(DrawPacket &i_DrawPacket)
用途       ：オブジェクトの描画
=======
関数名　　：void MagneticField::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket     //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************/
void	MagneticField::Draw(DrawPacket &i_DrawPacket){
	//テクスチャがある場合
	if(m_pTexture){
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}
	//Cylinder::Draw(i_DrawPacket);
};

/*******************************************************************
関数名　　：void MagneticField::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket     //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
********************************************************************/
void	MagneticField::Update(UpdatePacket& i_UpdatePacket)
{
	//	: マティリアル設定
	if(m_Pole){
		//N極
		D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,0.2f};
		D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,0.2f};

		m_Material.Diffuse	= Diffuse;
		m_Material.Specular	= Specular;
		m_Material.Ambient	= Ambient;
	}
	else{
		//S極
		D3DCOLORVALUE Diffuse = {0.0f,0.0f,1.0f,0.2f};
		D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE Ambient = {0.0f,0.0f,1.0f,0.2f};

		m_Material.Diffuse	= Diffuse;
		m_Material.Specular	= Specular;
		m_Material.Ambient	= Ambient;
	}

	PlayerCoil*	pc = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	POLE	cPole	= pc->getMagnetPole();

	D3DXMATRIX mMove, mScale;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixIdentity(&mScale);
	if(m_Pole == cPole){
		//反発のエフェクト
		if( m_bEffect ){
			m_Radius1	+= 0.2f;
			m_Radius2	+= 0.2f;

			if( m_Radius1 > MGPRM_MAGNETICUM ){
				m_Radius1	= 0;
				m_Radius2	= 0;
				
			}
			//移動用
			Debugger::DBGSTR::addStr(L"*************************************************\n");
		}
	}
	else{
		//吸い寄せるエフェクト
		if( m_bEffect ){
			m_Radius1	-= 0.2f;
			m_Radius2	-= 0.2f;

			if( m_Radius1 < 0 ){
				m_Radius1	= MGPRM_MAGNETICUM;
				m_Radius2	= MGPRM_MAGNETICUM;
				
			}
			//移動用
			Debugger::DBGSTR::addStr(L"*************************************************\n");
		}
	}
	D3DXMatrixTranslation(&mMove, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling( &mScale, m_Radius1/m_vNormalSize.x, m_Radius2/m_vNormalSize.y, 1.0f );
	m_mMatrix	= mScale * mMove;

	//Context ct ;
	//Cylinder::Transform(*i_UpdatePacket.pVec,i_UpdatePacket.pCntlState,ct);

};

/**************************************************************************
 StartField 定義部
****************************************************************************/
/***************************************************************************
関数名    ：StartField(
                   LPDIRECT3DDEVICE9   pD3DDevice,
                   LPDIRECT3DTEXTURE9  pTexture,
                   D3DXVECTOR3         &vScale,
                   D3DXQUATERNION      &vRot,
                   D3DXVECTOR3         &vPos
              )
カテゴリ　：コンストラクタ
用途      ：
引数　　　：LPDIRECT3DDEVICE9   pD3DDevice    //デバイスなど
　　　　　：LPDIRECT3DTEXTURE9  pTexture      //テクスチャ
　　　　　：D3DXVECTOR3         &vScale       //伸縮
　　　　　：D3DXQUATERNION      &vRot         //回転
　　　　　：D3DXVECTOR3         &vPos         //位置
			:D3DCOLORVALUE&      Diffuse,
			:D3DCOLORVALUE&      Specular,
			:D3DCOLORVALUE&      bAmbient,
戻り値　　：
担当者　　：本多寛之
備考　　　：
****************************************************************************/
StartField::StartField(
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,						//	: テクスチャー
	float Radius1,
	float Radius2,
	float Lenght,
	D3DXVECTOR3			&vRot,							//	: 回転
	D3DXVECTOR3	       &vPos,							//	: 位置
	D3DCOLORVALUE&     Diffuse,
	D3DCOLORVALUE&     Specular,
	D3DCOLORVALUE&     Ambient
)
:Cylinder(pD3DDevice,Radius1,Radius2,Lenght,vPos,vRot,Diffuse,Specular,Ambient)

{
	try{
	}
	catch(...){
		//再スロー
		throw;
	}
}

/**************************************************************
関数名　　：void StartField::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket     //もろもろのデータ
戻り値　　：
担当者　　：本多寛之
備考　　　：
***************************************************************/
void	StartField::Draw(DrawPacket &i_DrawPacket){
	Cylinder::Draw(i_DrawPacket);
};

/*******************************************************************
関数名　　：void StartField::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket     //もろもろのデータ
戻り値　　：
担当者　　：本多寛之
備考　　　：
********************************************************************/
void	StartField::Update(UpdatePacket& i_UpdatePacket)
{
	//D3DXMATRIX mMove, mScale;
	//D3DXMatrixIdentity(&mMove);
	//D3DXMatrixIdentity(&mScale);
	this->SetBaseScale(D3DXVECTOR3(m_Radius1,m_Radius2,1.0f));
	this->CalcWorldMatrix();
};

/**************************************************************************
 PlayerCoil 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::PlayerCoil( 	
////							LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////							float Radius1,float Radius2,float Lenght,
////							D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////							D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////							wiz::OBJID id = OBJID_3D_PLAYER)
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
////		      :   float Radius1						//円の直径1
////		      :   float Radius2						//円の直径2
////			  :   flaot Lenght						//高さ
////			  :   D3DXVECTOR3 &vScale
////		      :   D3DXVECTOR3 &vRot				//回転角
////		      :   D3DXVECTOR3 &vPos				//位置
////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
////			  : wiz::OBJID id = OBJID_2D_PLAYER //ID
//// 戻値       ：なし
//// 担当       ：鴫原 徹 本多寛之
//// 備考       ：
////            ：
////
PlayerCoil::PlayerCoil(

		LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,float Radius2,float Lenght,
		D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id
	)
:MagneticumObject3D(pD3DDevice,pTexture,
					Radius1,Radius2,Lenght,vRot,vPos,
					Diffuse,Specular,Ambient,id)
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_vMove(D3DXVECTOR3( 1.0f, 0.0f, 0.0f))
,m_fMoveDir(PLAYER_BASSROT)
,m_fMovdSpeed(PLAYER_SPEED)
,m_vStartPos(vPos)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bIsSuperMode(false)
,m_fTurnAngle(PLAYER_TURN_ANGLE_Lv1)
,m_pPlayer(NULL)
,m_pMagneticumObject(NULL)
,m_pCamera(NULL)
,m_pSound( NULL )
,m_enumCoilState(COIL_STATE_START)
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
,m_pDSPH(NULL)
,m_bDebugInvincibleMode( false )
#endif
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pCylinder = new Cylinder( pD3DDevice, m_Radius1, m_Radius2, m_Length, m_vPos, g_vZero, Diffuse, Specular, Ambient ) ;
	m_pStartField = new StartField(pD3DDevice,NULL,
									3.45f,3.45f,1.0f,
									g_vZero,D3DXVECTOR3(vPos.x,vPos.y,2.0f),
									Diffuse,Specular,Ambient);
	setPoleN();
	SetBaseRot(vRot);
}
/////////////////// ////////////////////
//// 関数名     ：~PlayerCoil()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ： 鴫原 徹
//// 備考       ：
////            ：
////
PlayerCoil::~PlayerCoil(){

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	SafeDelete( m_pDSPH );
#endif

	SafeDelete( m_pCylinder );
	SafeDelete( m_pStartField );

	m_pPlayer				= NULL ;
	m_pMagneticumObject		= NULL ;
	m_pCamera				= NULL ;
	
};

/////////////////////// ////////////////////
//////// 用途       ：bool PlayerCoil::HitTestWall( SPHERE& Coil )
//////// カテゴリ   ：MultiBoxとの衝突判定
//////// 用途       ：マルチボックスとの衝突判定
//////// 引数       ：  bool HitTestMultiBox
////////				  MultiBox* pBox,	//マルチボックス
////////				  size_t& Index,	//ヒットしていたらインデックスが戻る
////////				  D3DXVECTOR3& Vec,         //最近接点
////////				  D3DXVECTOR3& ElsePos         //一つ前のポジション
//////// 戻値       ：衝突していればtrue
//////// 担当者     ：曳地 大洋
//////// 備考       ：
bool PlayerCoil::HitTestWall( OBB Obb, float Index ){
	D3DXVECTOR3 Pos = GetPos();
	SPHERE sp;
	sp.m_Center = m_vPos;
	sp.m_Radius = m_pCylinder->getRadius2() ;
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( m_pDSPH ) m_pDSPH->UpdateSPHERE(sp);
	if( m_bDebugInvincibleMode ) return false ;
#endif
	//通常の衝突判定
	D3DXVECTOR3 Vec ;
	if(HitTest::SPHERE_OBB(sp,Obb,Vec)){
		//MessageBox( NULL, L"当たった！！", L"当たり判定", NULL) ;
		return true;
	}
	return false;
}
/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void PlayerCoil::Update( UpdatePacket& i_UpdatePacket ){

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( !m_pDSPH ){
		SPHERE sp;
		sp.m_Center = g_vMax ;
		sp.m_Radius = 1.0f ;
		m_pDSPH = new DrawSphere( i_UpdatePacket.pD3DDevice, sp );
	}
#endif

	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;

	if( !m_pCamera ){ 
		m_pCamera = ( Camera* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ; 
	}

	if( m_pSound == NULL )
		m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));

	if( !m_pMagneticumObject ){ 
		m_pMagneticumObject = ( MagneticumObject3D* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_STATIC_MAGNET) ; 
	}
	if( m_pPlayer ){
		//デバック用-----------------------------------------------------------
		// 磁界反転
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		//状態ごとの処理
		switch(m_enumCoilState){
			case COIL_STATE_START:
				Update_StateStart();
				break;
			case COIL_STATE_MOVE:
				Update_StateMove();
				break;
			case COIL_STATE_STICK:
				Update_StateStick();
				break;
			case COIL_STATE_DEAD:
				Update_StateDead();
				break;
			case COIL_STATE_CONTINUE:
				Update_StateContinue();
				break;
			case COIL_STATE_CLEAR:
				break;
			default:
				break;
		}

		if(m_bIsSuperMode){
			SuperMode(i_UpdatePacket);
			m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_INVISIBLE );
		}

		//デバック用-----------------------------------------------------------
		Debugger::DBGSTR::addStr( L"角度 = %f\n",m_fMoveDir);
		//-----------------------------------------------------------------------

		//マトリクス計算
		D3DXMATRIX mPos, mScale, mRotZ, mRotX;
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - PLAYER_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos ;

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer3D) );
	}
	m_pPlayer->setState(m_enumCoilState);
	if(m_enumCoilState == COIL_STATE_START || m_enumCoilState == COIL_STATE_CONTINUE){
		m_pStartField->SetBasePos(D3DXVECTOR3(m_vStartPos.x,m_vStartPos.y,1.0f));
		m_pStartField->Update(i_UpdatePacket);
	}
	//カメラ座標設定
	if( m_pCamera ){
		m_pCamera->setPosY( m_vPos.y );
	}
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( GetAsyncKeyState( MYVK_DEBUG_COIL_INVISIBLE ) )
		m_bDebugInvincibleMode ? m_bDebugInvincibleMode = false : m_bDebugInvincibleMode = true ;
	if( m_bDebugInvincibleMode )
	Debugger::DBGSTR::addStrTop( L"**********  無敵モード  **********\n" );
#endif 
};

/////////////////// ////////////////////
//// 関数名     ：void PlayerCoil::Update_StateStart()
//// カテゴリ   ：
//// 用途       ：STATE_START時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateStart(){
	//if( m_pSound == NULL )
	//	m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));

	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//マウス座標計算
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	vPlayer.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
	vPlayer.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_pPlayer->getMoveY() ) ;
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//角度の更新
	m_fMoveDir = fTargetDir;
	//左クリックが押し、離したらMOVE状態に変更
	float fLng  = (float)TwoPointToBassLength( vPlayer, m_vPos ) ;
	if(g_bMouseLB && fLng <= START_EFFECTIVE_RANGE_QUAD){
		m_bLastMouseLB = true;
	}
	if(!g_bMouseLB && m_bLastMouseLB){
		m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
		m_enumCoilState = COIL_STATE_MOVE;
		m_bLastMouseLB = false;
		m_pPlayer->CoilWasFired(true);
	}
};

/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::Update_StateMove()
//// カテゴリ   ：
//// 用途       ：STATE_MOVE時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateMove(){
	//プレイヤー磁界と自機の判定
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), m_vPos, (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance ){
		m_fMoveDir = MagneticDecision(m_fMoveDir,m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	//設置磁界と自機の判定
	multimap<float, Magnet3DItem*> ItemMap_Target = m_pMagneticumObject->getMapTarget();
	multimap<float,Magnet3DItem*>::iterator it = ItemMap_Target.begin();
	while(it != ItemMap_Target.end()){
		bool bCheckDistance = CheckDistance( it->second->m_vPos, m_vPos, (float)MGPRM_MAGNETICUM_QUAD, false );
		if( bCheckDistance ){
			m_fMoveDir = MagneticDecision(m_fMoveDir,it->second->m_vPos,it->second->m_bMagnetPole);
		}
		++it;
	}

	//速度指定
	if(m_bIsSuperMode) m_fMovdSpeed = PLAYER_SPEED_SUPER;
	else			   m_fMovdSpeed = PLAYER_SPEED;
	//指定方向へ指定距離移動
	ArcMove( m_vMove , m_fMovdSpeed, m_fMoveDir);
	//移動分を加算
	m_vPos += m_vMove;

	if(m_vPos.x <= 0){
		m_vPos.x = 0.0f;
	}
	if(m_vPos.x >= 50.0f){
		m_vPos.x = 50.0f;		
	}
	if(m_vPos.y <= 0){
		m_vPos.y = 0.0f;
	}
};

/////////////////// ////////////////////
//// 関数名     ：void Update_StateStick()
//// カテゴリ   ：
//// 用途       ：STATE_STICK時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateStick(){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	m_fMoveDir += 5.0f;
	if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);

	//発射時に極を変える
	switch(getMagnetPole()){
		case POLE_S:
			if(!g_bMouseLB || !m_pPlayer->getDrawing()){
				setPoleN();
				m_enumCoilState = COIL_STATE_MOVE;
			}
			break;
		case POLE_N:
			if(!g_bMouseRB || !m_pPlayer->getDrawing()){
				setPoleS();
				m_enumCoilState = COIL_STATE_MOVE;
			}
			break;
	}
};


/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::SuperMode()
//// カテゴリ   ：
//// 用途       ：STATE_SUPER時の動き
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////			  ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////			  ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////			  ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////              ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////			  ：
////
void PlayerCoil::SuperMode( UpdatePacket& i_UpdatePacket ){	
	static float s_fTimeCount		= 0;
	static int	s_iInterval			= 0;
	static bool s_bIsColorChange	= false;

	if(m_enumCoilState == COIL_STATE_MOVE)
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
	
	//色の点滅
	if(s_iInterval == 0){
		if(s_bIsColorChange){
			s_bIsColorChange = false;
			switch(getMagnetPole()){
				case POLE_S:
					setColorS();
					break;
				case POLE_N:
					setColorN();
					break;
			}
		}
		else{
			s_bIsColorChange  = true;
			setColorSuper();
		}
	}
	s_iInterval++;
	if(s_iInterval >= 5) s_iInterval = 0;

	//無敵モード終了
	if(s_fTimeCount >= COIL_SUPER_MODE_TIME){
		m_bIsSuperMode = false;
		s_fTimeCount = 0.0f;
		switch(getMagnetPole()){
			case POLE_S:
				setColorS();
				break;
			case POLE_N:
				setColorN();
				break;
		}
	}
};


/////////////////// ////////////////////
//// 関数名     ：void PlayerCoil::Update_StateDead()
//// カテゴリ   ：
//// 用途       ：STATE_DEAD時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateDead(){
	m_enumCoilState = COIL_STATE_CONTINUE;
	m_vPos = m_vStartPos;
	m_pCamera->setPosY(m_vStartPos.y);
	m_pPlayer->CoilWasFired(false);
}

/////////////////// ////////////////////
//// 関数名     ：void PlayerCoil::Update_StateContinue()
//// カテゴリ   ：
//// 用途       ：STATE_START時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateContinue(){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//マウス座標計算
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	vPlayer.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
	vPlayer.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_pPlayer->getMoveY() ) ;
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//角度の更新
	m_fMoveDir = fTargetDir;
	//左クリックが押し、離したらMOVE状態に変更
	float fLng  = (float)TwoPointToBassLength( vPlayer, m_vPos ) ;
	if(g_bMouseLB && fLng <= START_EFFECTIVE_RANGE_QUAD){
		m_bLastMouseLB = true;
	}
	if(!g_bMouseLB && m_bLastMouseLB){
		m_enumCoilState = COIL_STATE_MOVE;
		m_bLastMouseLB = false;
		m_pPlayer->CoilWasFired(true);
	}
};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void PlayerCoil::Draw(DrawPacket& i_DrawPacket){
	if(m_pTexture){
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//ステージの設定
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}
	if(m_enumCoilState == COIL_STATE_START || m_enumCoilState == COIL_STATE_CONTINUE){
		m_pStartField->Draw(i_DrawPacket);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

};

/////////////////// ////////////////////
//// 関数名     ：float PlayerCoil::MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
//// カテゴリ   ：関数
//// 用途       ：自機に対する吸い寄せ、反発の処理
//// 引数       ：float i_fCoilDir            //自機の角度
////　　　　　　：D3DXVECTOR3& i_vMagnetPos   //磁界の位置
////　　　　　　：bool i_bMagnetPole_Field	// 磁界の極
//// 戻値       ：
//// 担当       ：本多寛之
//// 備考       ：
////　　　　　　：
float PlayerCoil::MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, POLE i_bMagnetPole_Field ) const{
	float	fTargetDir = TwoPoint2Degree( i_vMagnetPos , getPos() );
	float	fReverse   = 0.0f;
	if(i_fCoilDir > 180.0f){
		fReverse = i_fCoilDir - 180.0f;
	}
	else{
		fReverse = i_fCoilDir + 180.0f;
	}

	if(i_bMagnetPole_Field != this->getMagnetPole()){
		if(i_fCoilDir < fTargetDir){
			if(fTargetDir - i_fCoilDir <= 180.0f){
				i_fCoilDir += m_fTurnAngle;
				i_fCoilDir = float(int(i_fCoilDir) % 360);						
			}
			else{
				i_fCoilDir -= m_fTurnAngle;
				if(i_fCoilDir < 0.0f){
					i_fCoilDir += 360.0f;
				}
			}
		}
		else if(i_fCoilDir > fTargetDir){
			if(i_fCoilDir - fTargetDir <= 180.0f){
				i_fCoilDir -= m_fTurnAngle;
				if(i_fCoilDir < 0.0f){
					i_fCoilDir += 360.0f;
				}
			}
			else{
				i_fCoilDir += m_fTurnAngle;
				i_fCoilDir = float(int(i_fCoilDir) % 360);												
			}
		}
	}
	else{
		if(fReverse != fTargetDir){
			if(i_fCoilDir < fTargetDir){
				if(fTargetDir - i_fCoilDir <= 180.0f){
					i_fCoilDir -= m_fTurnAngle;
					if(i_fCoilDir < 0.0f){
						i_fCoilDir += 360.0f;
					}
				}
				else{
					i_fCoilDir += m_fTurnAngle;
					i_fCoilDir = float(int(i_fCoilDir) % 360);						
				}
			}
			else if(i_fCoilDir > fTargetDir){
				if(i_fCoilDir - fTargetDir <= 180.0f){
					i_fCoilDir += m_fTurnAngle;
					i_fCoilDir = float(int(i_fCoilDir) % 360);												
				}
				else{
					i_fCoilDir -= m_fTurnAngle;
					if(i_fCoilDir < 0.0f){
						i_fCoilDir += 360.0f;
					}
				}
			}
		}
	}
	return i_fCoilDir;
};

/////////////////// ////////////////////
//// 用途       ：bool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
//// カテゴリ   ：関数
//// 用途       ：距離を判定
//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
////　　　　　　：float        i_iBorder           //判定する値
////　　　　　　：bool　　　　IsPlayer　　　　　//相手がプレイヤーかどうか
//// 戻値       ：true , false
//// 担当者     ：本多寛之
//// 備考       ：
bool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer ){
	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, i_vCoilPos ) ;
	if( Lng <= i_iBorder ){
		float fBorderLv = i_iBorder/3;
		if(m_enumCoilState == COIL_STATE_MOVE
						&& getMagnetPole() != m_pPlayer->getMagnetPole()
								&& Lng <= fBorderLv/30
									&& IsPlayer){
			m_vPos = m_pPlayer->getPos();
			m_enumCoilState = COIL_STATE_STICK;
			return false;
		}
		if(Lng <= fBorderLv && IsPlayer){
			m_fTurnAngle = PLAYER_TURN_ANGLE_Lv3;
		}
		else if(Lng <= fBorderLv*2 && IsPlayer){
			m_fTurnAngle = PLAYER_TURN_ANGLE_Lv2;
		}
		else{
			m_fTurnAngle = PLAYER_TURN_ANGLE_Lv1;
		}
		return true;
	}
	else{
		return false;
	}
}


/**************************************************************************
 Factory_Player 定義部
****************************************************************************/
/**************************************************************************
 Factory_Player::Factory_Player(
	FactoryPacket* fpac		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Player::Factory_Player( FactoryPacket* fpac ){
	try{

		D3DXVECTOR3 vScale( 1.0f, 1.0f, 1.0f );
		//fpac->m_pVec->push_back(
		//	new ProvisionalPlayer(
		//		fpac->pD3DDevice,
		//		fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleP.png" ),
		//		vScale,
		//		g_vZero,
		//		D3DXVECTOR3(0.0f,0.0f,0.0f),
		//		NULL,
		//		0xFF0000FF
		//	)
		//);

		// 3D用
		D3DXVECTOR3 vScale2( 10.0f, 10.0f, 10.0f );
		fpac->m_pVec->push_back(
			new ProvisionalPlayer3D(
				fpac,
				NULL,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Field.png" ),
				vScale,
				D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
		);

 		D3DCOLORVALUE CoilDiffuse = {1.0f,1.0f,0.0f,0.5f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {1.0f,1.0f,0.0f,0.5f};
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleC.png" ),
				NULL,
				0.0f,1.0f,3.0f,vScale,D3DXVECTOR3(90.0f,0.0f,0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f),
				CoilDiffuse,CoilSpecular,CoilAmbient
				)
		);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Player::~Factory_Player();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Player::~Factory_Player(){
    //なにもしない
}

}
//end of namespace wiz.
