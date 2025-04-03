////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：曳地 大洋
//	└→			：本多 寛之
//	内包データと備考	：プレイヤーが誘導する物体
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
namespace bomberobject{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
extern class WallObject ;
const	float	GAUGE_VANISHRATE	= 0.0f;
// 3D用
/**************************************************************************
 ProvisionalPlayer3D 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：ProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE pTexture,
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
	LPDIRECT3DDEVICE9 pD3DDevice,								//	: デバイス
	LPTATRATEXTURE pTexture,						//	: テクスチャー
	LPTATRATEXTURE pTexture2,						//	: テクスチャー２
	D3DXVECTOR3		   &vScale,							//	: 伸縮
	D3DXQUATERNION	   &vRot,							//	: 回転
	D3DXVECTOR3	       &vPos,							//	: 位置
	wiz::OBJID id 										//	: ID
)
:MagnetField( pD3DDevice, id )
,m_Camera(NULL)
,m_pCursor(NULL)
,m_pPlayerCoil(NULL)
,m_pMGage_N(NULL)
,m_pMGage_S(NULL)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bDrawing(false)
,m_bPlaySound(false)
,m_bChangeFirst( false )
{
	D3DXMatrixIdentity( &m_Matrix ) ;
	setPoleS();
	

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
	m_Camera		= NULL ;
	m_pPlayerCoil	= NULL;
	m_pMGage_N		= NULL;
	m_pMGage_S		= NULL;
	m_pCursor		= NULL;
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
		m_Camera = (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA);
		//m_Camera && (m_MovePosY	= m_Camera->getPosY());
	}
	if( !m_pPlayerCoil	)	m_pPlayerCoil	= (     PlayerCoil* )i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL          );
	if( !m_pMGage_N		)	m_pMGage_N		= ( MagneticGage_N* )i_UpdatePacket.SearchObjectFromID(OBJID_UI_MAGNETGAUGE_N );
	if( !m_pMGage_S		)	m_pMGage_S		= ( MagneticGage_S* )i_UpdatePacket.SearchObjectFromID(OBJID_UI_MAGNETGAUGE_S );
	if( !m_pCursor		)	m_pCursor		= (    MouseCursor* )i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CURSOR       );

	RECT rc;
	::GetClientRect(wiz::DxDevice::m_hWnd, &rc);

	//Suction	: 吸引
	//Rebound	: 反発
	bool	Suction	= Cursor2D::getRButtonState();
	bool	Rebound	= Cursor2D::getLButtonState();
	if( !m_pPlayerCoil->getMagnetPole() ){
		Suction	= Cursor2D::getLButtonState();
		Rebound	= Cursor2D::getRButtonState();
	}

	if( m_pPlayerCoil->getState() == COIL_STATE_MOVE
		|| (m_pPlayerCoil->getState() == COIL_STATE_STICK && m_pPlayerCoil->getReadyToStart() && m_pPlayerCoil->getStandby() ) ){
		if( (Suction || Rebound) && !(Suction && Rebound)){ 
			if( (Suction && m_pMGage_N->getRate() > GAUGE_VANISHRATE) || (Rebound && m_pMGage_S->getRate() > GAUGE_VANISHRATE) ){				
				if( !m_bLastMouseLB && !m_bLastMouseRB){
					if(Suction)m_pMGage_N->Consume(PLAYER_INVOCATION_POINT);
					if(Rebound)m_pMGage_S->Consume(PLAYER_INVOCATION_POINT);
					if( (Suction && m_pMGage_N->getRate() > GAUGE_VANISHRATE) || (Rebound && m_pMGage_S->getRate() > GAUGE_VANISHRATE) ){

						D3DXVECTOR3 vMove = g_vZero ;
						m_vPos = m_pCursor->get3DPos();

						if(Suction){
							m_MagneticField.setPole(POLE_N);
						}
						else if(Rebound){
							m_MagneticField.setPole(POLE_S);
						}

						//磁界の属性を設定
						if( Suction )
							setPoleN() ;
						if( Rebound )
							setPoleS() ;
					}
				}

				//現在消費中のゲージが残っているならはいる
				if( (Suction && m_pMGage_N->getRate() > GAUGE_VANISHRATE) || (Rebound && m_pMGage_S->getRate() > GAUGE_VANISHRATE) ){	
	
					if( Suction  && !Rebound && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !Suction && Rebound  && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !Suction && Rebound  )m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
					if( Suction  && !Rebound )m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);

					//	: マウスのフラグ
					//Cursor2D::getLButtonState() = false ;
					//Cursor2D::getRButtonState() = false ;
					m_bDrawing	= true;
				}
			}
			else{
				m_bDrawing	= false;					
			}
		}else{
			if(m_pPlayerCoil->getState() != COIL_STATE_STICK){
				m_bDrawing	= false;
				if( m_pMGage_N ) m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
				if( m_pMGage_S ) m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);
			}
		}
		m_bChangeFirst	= true;
	}else{
		//COIL_STATE_STICKだが、アニメーションが終わっていない
		if( m_pPlayerCoil->getState() == COIL_STATE_STICK ){
			m_bDrawing	= true;
			if( m_pMGage_N && m_pMGage_S && m_bChangeFirst){
				//Rateの交換************************************
				float	fRate	= 0.0f;
				fRate	= m_pMGage_N->getRate();
				m_pMGage_N->setRate( m_pMGage_S->getRate() );
				m_pMGage_S->setRate( fRate );
				//位置の入れ替え*******************************
				m_pMGage_N->ChangePos();
				m_pMGage_S->ChangePos();
				//***********************************************
				m_bChangeFirst	= false;
			}
		}else	m_bDrawing	= false;
	}
	m_bLastMouseLB = Cursor2D::getLButtonState() ;
	m_bLastMouseRB = Cursor2D::getRButtonState() ;


	//死んでコンテニュー時にゲージを戻す
	if(m_pPlayerCoil->getState() == COIL_STATE_CONTINUE){
		if( m_pMGage_N ) m_pMGage_N->ResetGauge();
		if( m_pMGage_S ) m_pMGage_S->ResetGauge();
	}
	MagnetField::Update(i_UpdatePacket);

	//ゲージが3割切ったら、磁界を点滅させる*******************
	if(m_pPlayerCoil->getState() != COIL_STATE_STICK){
		if( MagnetField::getMagnetPole() == POLE_S && m_bDrawing ){
			if(m_pMGage_S->getRate() < 0.3f)
					MagnetField::Flashing(i_UpdatePacket, POLE_S);
			else	MagnetField::Reset();
		}
		else if( MagnetField::getMagnetPole() == POLE_N && m_bDrawing ){
			if(m_pMGage_N->getRate() < 0.3f)
					MagnetField::Flashing(i_UpdatePacket, POLE_N);
			else	MagnetField::Reset();
		}
	}else	MagnetField::Reset();
	//***************************************************************

};

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////			   ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////			   ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////			   ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////               ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：曳地 大洋
//// 備考       ：
void ProvisionalPlayer3D::Draw(DrawPacket& i_DrawPacket)
{

	if( m_pPlayerCoil && ( m_pPlayerCoil->getState() == COIL_STATE_MOVE || m_pPlayerCoil->getState() == COIL_STATE_STICK ) ){
		if( m_bDrawing ){ 
			if(  !m_bPlaySound ){
				m_bPlaySound = true ;
				i_DrawPacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_SETFIELD ) ;
			}

			MagnetField::Draw(i_DrawPacket);
		}
		else{
			m_bPlaySound = false ;
			i_DrawPacket.SoundStop(RCTEXT_SOUND_SE_SETFIELD);
		}
	}else{
		m_bPlaySound = false ;
		i_DrawPacket.SoundStop( RCTEXT_SOUND_SE_SETFIELD );
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
		//fpac->AddObject(
		//	new ProvisionalPlayer(
		//		fpac->GetDevice(),
		//		fpac->AddTexture( L"CircleP.png" ),
		//		vScale,
		//		g_vZero,
		//		D3DXVECTOR3(0.0f,0.0f,0.0f),
		//		NULL,
		//		0xFF0000FF
		//	)
		//);

		// 3D用
		D3DXVECTOR3 vScale2( 10.0f, 10.0f, 10.0f );
		fpac->AddObject(
			new ProvisionalPlayer3D(
				fpac->GetDevice(),
				NULL,
				fpac->AddTexture(  L"Field.png" ),
				vScale,
				D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
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
//end of namespace bomberobject.

}
//end of namespace wiz.
