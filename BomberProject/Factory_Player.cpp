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

namespace wiz{

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
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos(vPos)
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
	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
	D3DXVECTOR3 vMove = g_vZero ;
	vMove.x += Controller1P.Gamepad.fThumbLX;
	vMove.y -= Controller1P.Gamepad.fThumbLY;

	this->m_vPos += vMove * 15.0f ;
	
	D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;

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
	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	RECT* pRect,								//	: 描画範囲
	Color color ,								//	: 色
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos(vPos)
,m_pPlayer(NULL)
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
void PlayerCoil::Update( UpdatePacket& i_UpdatePacket ){
	if( m_pPlayer ){


		D3DXVECTOR3 vMove = g_vZero ;
		D3DXVECTOR3 pPos = this->m_pPlayer->getPos();

		float Lng  = TwoPointToBassLength( pPos, m_vPos ) ;
		float Lng2 = VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", 100*100);
		if( Lng <= 100*100 ){
			vMove.x = 1 ;
			float degree = TwoPoint2Degree( m_vPos, pPos );	
			ArcMove( vMove , 10.0f, degree);

			//vMove.y *= -1.0f ;
			this->m_vPos += vMove ;
			D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
		}

		char atr[] = "いきるのめんどくさい";
		this->m_vPos += vMove * 1.0f ;

		D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
	} else {
		m_pPlayer = (ProvisionalPlayer*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer) );
	}
};

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
		fpac->m_pVec->push_back(
			new ProvisionalPlayer(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Circle.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f,100.0f,0.0f),
				NULL,
				0xFFFF0000
			)
		);
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Circle.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f,300.0f,0.0f),
				NULL,
				0xFFFF00000
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
