////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
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


namespace wiz{

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
ProvisionalPlayer::ProvisionalPlayer(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	RECT* pRect,								//	: 描画範囲
	Color color ,								//	: 色
	wiz::OBJID id 								//	: ID
)
	:MagneticumObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, color, id )
{
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
void ProvisionalPlayer::Update( UpdatePacket& i_UpdatePacket ){
	if( g_bMouseLB || g_bMouseRB ){
		wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
		D3DXVECTOR3 vMove = g_vZero ;
		Point MousePos ;
		GetCursorPos( &MousePos );
		ScreenToClient( g_hWnd , &MousePos);
		m_vPos.x = (float)MousePos.x;
		m_vPos.y = (float)MousePos.y;	

		if( g_bMouseLB )
			setPoleN() ;
		if( g_bMouseRB )
			setPoleS() ;

		//this->m_vPos += vMove * 15.0f ;
	
		D3DXMATRIX mPos , mScale ;

		D3DXMatrixTranslation( &mPos , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
		m_mMatrix = mScale * mPos ;
	}

	//g_bMouseLB = false ;
	//g_bMouseRB = false ;
};

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
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,						//	: テクスチャー
	D3DXVECTOR3		   &vScale,							//	: 伸縮
	D3DXQUATERNION	   &vRot,							//	: 回転
	D3DXVECTOR3	       &vPos,							//	: 位置
	wiz::OBJID id 										//	: ID
)
	:MagneticumObject3D( pD3DDevice, pTexture, id )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	setPoleS();

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
	//multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_Target.begin();
	//while(it != m_ItemMap_Target.end()){
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
		//++it;
	//}
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
	//m_ItemMap_Target.clear() ;
	//multimap<float, Magnet3DItem*>::iterator it2 = m_ItemMap_Target.begin() ;
	//while(it2 != m_ItemMap_Target.end()){
		if( g_bMouseLB || g_bMouseRB ){
			wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
			D3DXVECTOR3 vMove = g_vZero ;
			Point MousePos ;
			GetCursorPos( &MousePos );
			ScreenToClient( g_hWnd , &MousePos);
			
			//float m_vStage ;
			/*it2->second->*/m_vPos.x = (float)MousePos.x / 20.0f - 0.5f ;
			m_vPos.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - 88.0f ) / 20.0f - 0.5f ;
			///*it2->second->*/m_vPos.x = (float)MousePos.x ;
			//m_vStage = ( STANDARD_WINDOW_HEIGHT - 88.0f ) -(float)MousePos.y + 88.0f ;
			//m_vPos.y = -( m_vStage - (float)MousePos.y ) ;
			//m_vPos.y + 88.0f = ( STANDARD_WINDOW_HEIGHT - 88.0f ) -(float)MousePos.y - 88.0f ;
			//*it2->second->*/m_vPos.y = ((512.0f -  (float)MousePos.y ) / 12.5f ) ;
			///*it2->second->*/m_vPos.y = ((STANDARD_WINDOW_HEIGHT -  (float)MousePos.y ) / 12.5f ) ;
			//m_vPos.y = m_vPos.y - 30.0f ;

			if( g_bMouseLB )
				setPoleN() ;
			if( g_bMouseRB )
				setPoleS() ;

			//this->m_vPos += vMove * 15.0f ;

			/*
			D3DXMATRIX mPos , mScale ;

			D3DXMatrixTranslation( &mPos , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
			//D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
			D3DXMatrixScaling(&mScale,
				it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
			it2->second->m_Matrix = mScale * mPos ;
			*/

					//拡大縮小
			D3DXMATRIX mScale;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale,
				/*it2->second->*/m_vScale.x, /*it2->second->*/m_vScale.y,/*it2->second->*/m_vScale.z);
			//回転
			D3DXMATRIX mRot;
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixRotationQuaternion(&mRot,/*it2->second->*/&m_vRot);
			//移動用
			D3DXMATRIX mMove;
			D3DXMatrixIdentity(&mMove);
			D3DXMatrixTranslation(&mMove,
				/*it2->second->*/m_vPos.x, /*it2->second->*/m_vPos.y,/*it2->second->*/m_vPos.z);
			//ミックス行列
			/*it2->second->*/m_Matrix = mScale * mRot * mMove;
			//マティリアル設定
			m_Material = /*it2->second->*/m_Material;

		//}

		g_bMouseLB = false ;
		g_bMouseRB = false ;

		//++it2 ;
	}
};

/**************************************************************************
 PlayerCoil 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
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
PlayerCoil::PlayerCoil(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pCoreTexture,			//	: コア部分のTexture
	LPDIRECT3DTEXTURE9 pDirTexture,				//	: 方向を表す三角のてくすたー
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	D3DXVECTOR3 &vDirOffset,					//	: 方向を表す三角の描画オフセット
	RECT* pCoreRect,							//	: 描画範囲
	RECT* pDirRect,								//	: 描画範囲
	wiz::OBJID id 								//	: ID
)
:MagneticumObject(pD3DDevice,pCoreTexture,vScale,vRot,vPos,
	pCoreRect,0xFFFFFFFF,id)
,m_pPlayer(    NULL )
,m_fMoveDir(   PLAYER_BASSROT )
,m_fMovdSpeed( PLAYER_SPEED   )
,m_pDirParts( NULL )

{
	m_pDirParts = new SpriteObject( pD3DDevice, pDirTexture, vScale, vRot, vPos, pDirRect, g_vZero, vDirOffset ) ;
	setPoleN();
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

	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;

	if( m_pPlayer ){
		//m_fMovdSpeed = 0;
		//ConvertToCartesianCoordinatesを使って自機のデカルト座標を出す
		//ThreePoint2Radianでデカルト座標(1)、自機の位置(2)、磁界の位置(3)を入れて角度を出す

		//	: 必要な変数の宣言
		// 移動の方向 + 距離
		D3DXVECTOR3 vMove = D3DXVECTOR3( 1.0f, 0.0f, 0.0f) ;
		// ユーザー磁界の座標
		D3DXVECTOR3 pPos  = this->m_pPlayer->getPos();

		// コイルとユーザー磁界の距離を算出
		float Lng  = (float)TwoPointToBassLength( pPos, m_vPos ) ;
		// テスト用
		float Lng2 = (float)VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );

		// 磁界反転
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;

		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", MGPRM_MAGNETICUM_QUAD);

		if( Lng <= MGPRM_MAGNETICUM_QUAD ){
			//自機と磁界の角度
			float fTargetDir = TwoPoint2Degree( pPos , m_vPos );
			//fTargetDir = 360.0f - fTargetDir;
			Debugger::DBGSTR::addStr( L"fTargetDir : %f\n", fTargetDir);
			//自機のデカルト座標
			D3DXVECTOR3 vDescartes = ConvertToCartesianCoordinates(vMove.x,m_fMoveDir);
			Debugger::DBGSTR::addStr( L"vDescartes : %f\n", vDescartes.x);

			float	fReverse = 0.0f;
			if(m_fMoveDir > 180.0f){
				fReverse = m_fMoveDir - 180.0f;
			}
			else{
				fReverse = m_fMoveDir + 180.0f;
			}

			if(m_pPlayer->getMagnetPole() != this->getMagnetPole()){

				if(m_fMoveDir < fTargetDir){
					if(fTargetDir - m_fMoveDir <= 180.0f){
						m_fMoveDir += 1.0f;
						m_fMoveDir = float(int(m_fMoveDir) % 360);						
					}
					else{
						m_fMoveDir -= 1.0f;
						if(m_fMoveDir < 0.0f){
							m_fMoveDir += 360.0f;
						}
					}
				}
				else if(m_fMoveDir > fTargetDir){
					if(m_fMoveDir - fTargetDir <= 180.0f){
						m_fMoveDir -= 1.0f;
						if(m_fMoveDir < 0.0f){
							m_fMoveDir += 360.0f;
						}
					}
					else{
						m_fMoveDir += 1.0f;
						m_fMoveDir = float(int(m_fMoveDir) % 360);												
					}
				}
			}
			else{
				if(fReverse != fTargetDir){
					if(m_fMoveDir < fTargetDir){
						if(fTargetDir - m_fMoveDir <= 180.0f){
							m_fMoveDir -= 1.0f;
							if(m_fMoveDir < 0.0f){
								m_fMoveDir += 360.0f;
							}
						}
						else{
							m_fMoveDir += 1.0f;
							m_fMoveDir = float(int(m_fMoveDir) % 360);						
						}
					}
					else if(m_fMoveDir > fTargetDir){
						if(m_fMoveDir - fTargetDir <= 180.0f){
							m_fMoveDir += 1.0f;
							m_fMoveDir = float(int(m_fMoveDir) % 360);												
						}
						else{
							m_fMoveDir -= 1.0f;
							if(m_fMoveDir < 0.0f){
								m_fMoveDir += 360.0f;
							}
						}
					}
				}
			}
		}

		Debugger::DBGSTR::addStr( L"角度 = %f",m_fMoveDir);

		//	: 指定方向へ指定距離移動
		ArcMove( vMove , m_fMovdSpeed, m_fMoveDir);

		this->m_vPos += vMove ;

		WallObject* pWall = (WallObject*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_2D_WALL ) ;
		if( pWall && pWall->HitTest2DRectAndCircle( m_vPos, 32.0f) ){
			m_vPos = D3DXVECTOR3( 300, 300, 0 );
		}
		if( m_vPos.x <= 0 || m_vPos.x >= 800 || m_vPos.y <= 0 || m_vPos.y >= 500 ){
			m_vPos = D3DXVECTOR3( 100, 500, 0 );
		}
		//	: 移動の確定
		//	: 
		D3DXMATRIX mPos , mScale , mRotZ ;

		D3DXMatrixTranslation( &mPos  , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ(   &mRotZ ,  D3DXToRadian( m_fMoveDir - PLAYER_BASSROT ) ) ;

		this->m_mMatrix = mScale * mRotZ * mPos ;

	} else {
		m_pPlayer = (ProvisionalPlayer*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer) );
	}
	if( m_pDirParts ) m_pDirParts->setMatrix( m_mMatrix );
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
	if( m_pDirParts ) m_pDirParts->Draw( i_DrawPacket ) ;
	else ;

	MagneticumObject::Draw( i_DrawPacket );
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
		fpac->m_pVec->push_back(
			new ProvisionalPlayer(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleP.png" ),
				vScale,
				g_vZero,
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				NULL,
				0xFF0000FF
			)
		);

		// 3D用
		D3DXVECTOR3 vScale2( 10.0f, 10.0f, 10.0f );
		fpac->m_pVec->push_back(
			new ProvisionalPlayer3D(
				fpac->pD3DDevice,
				//NULL,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleP.png" ),
				vScale,
				D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
		);

		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleC.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CoilDir.png" ),
				vScale,
				g_vZero,
				D3DXVECTOR3(100.0f,400.0f,0.0f),
				D3DXVECTOR3( -16.5f, -26.0f,0.0f),
				NULL,
				NULL
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
