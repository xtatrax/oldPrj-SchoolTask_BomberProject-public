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
		m_vPos.x = MousePos.x;
		m_vPos.y = MousePos.y;	

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

	g_bMouseLB = false ;
	g_bMouseRB = false ;
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


		//	: 必要な変数の宣言
		// 移動の方向 + 距離
		D3DXVECTOR3 vMove = D3DXVECTOR3( 1.0f, 0.0f, 0.0f) ;
		// ユーザー磁界の座標
		D3DXVECTOR3 pPos  = this->m_pPlayer->getPos();

		// コイルとユーザー磁界の距離を算出
		float Lng  = TwoPointToBassLength( pPos, m_vPos ) ;
		// テスト用
		float Lng2 = VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );

		// 磁界反転
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;

		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", MGPRM_MAGNETICUM_QUAD);

		if( Lng <= MGPRM_MAGNETICUM_QUAD ){

			//	: 角度の算出
			m_fMoveDir = TwoPoint2Degree( m_vPos, pPos );

			//	: 反発処理
			//	: 同じ磁界だと反発する
			if( m_pPlayer->getMagnetPole() != this->getMagnetPole() ){
				TurnAngle( &m_fMoveDir , -180.0f ) ;
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

		D3DXVECTOR3 vScale( 0.7f, 0.7f, 1.0f );
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
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleC.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CoilDir.png" ),
				vScale,
				g_vZero,
				D3DXVECTOR3(200.0f,300.0f,0.0f),
				D3DXVECTOR3( -16.5f, -26.0f,0.0f),
				NULL,
				NULL
			)
		);

		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"display.png" ),
				g_vOne,
				g_vZero,
				g_vZero,
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
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
