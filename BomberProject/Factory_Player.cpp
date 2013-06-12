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
namespace bomberobject{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
extern class WallObject ;
const	float	GAUGE_VANISHRATE	= 0.87f;
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
,m_Camera(NULL)
,m_pPlayerCoil(NULL)
,m_pMGage_N(NULL)
,m_pMGage_S(NULL)
,m_pSound( NULL )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_MovePosY(0)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bDrawing(false)
,m_bPlaySound(false)
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
	m_Camera		= NULL ;
	m_pPlayerCoil	= NULL;
	m_pSound		= NULL;
	m_pMGage_N		= NULL;
	m_pMGage_S		= NULL;
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

	if( m_pPlayerCoil && ( m_pPlayerCoil->getState() == COIL_STATE_MOVE || m_pPlayerCoil->getState() == COIL_STATE_STICK ) ){
		if( m_bDrawing ){ 
			if( m_pSound && !m_bPlaySound ){
				m_bPlaySound = true ;
				m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_SETFIELD ) ;
			}
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
		else	m_pSound->SoundPause(RCTEXT_SOUND_SE_SETFIELD);
	}else{
		m_bPlaySound = false ;
		m_pSound->SoundPause( RCTEXT_SOUND_SE_SETFIELD );
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
	if( !m_pPlayerCoil ) m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	if( !m_pMGage_N )	 m_pMGage_N		= (MagneticGage_N*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_N));
	if( !m_pMGage_S )	 m_pMGage_S		= (MagneticGage_S*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_S));

	RECT rc;
	::GetClientRect(wiz::DxDevice::m_hWnd, &rc);

	Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_vPos.x , m_vPos.y, m_vPos.z ) ;

	if( m_pPlayerCoil->getState() == COIL_STATE_MOVE || m_pPlayerCoil->getState() == COIL_STATE_STICK ){
		if( (g_bMouseLB || g_bMouseRB) && !(g_bMouseLB && g_bMouseRB)){ 
			if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){				
				if( !m_bLastMouseLB && !m_bLastMouseRB){
					if(g_bMouseLB)m_pMGage_N->Consume(PLAYER_INVOCATION_POINT);
					if(g_bMouseRB)m_pMGage_S->Consume(PLAYER_INVOCATION_POINT);
					if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){
						wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
						D3DXVECTOR3 vMove = g_vZero ;
						Point MousePos ;
						GetCursorPos( &MousePos ) ;
						ScreenToClient( wiz::DxDevice::m_hWnd , &MousePos) ;

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
				if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){	

					if( g_bMouseLB  && !g_bMouseRB && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !g_bMouseLB && g_bMouseRB  && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !g_bMouseLB && g_bMouseRB  )m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
					if( g_bMouseLB  && !g_bMouseRB )m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);

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
			if(m_pPlayerCoil->getState() != COIL_STATE_STICK){
				m_bDrawing	= false;
				if( m_pMGage_N ) m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
				if( m_pMGage_S ) m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);
			}
		}
	}else{
			m_bDrawing	= false;
	}
	m_bLastMouseLB = g_bMouseLB ;
	m_bLastMouseRB = g_bMouseRB ;

	//磁界のエフェクトを動かす
	m_pMagneticField4->Update(i_UpdatePacket);

	if(m_pPlayerCoil->getState() == COIL_STATE_CONTINUE){
		if( m_pMGage_N ) m_pMGage_N->ResetGauge();
		if( m_pMGage_S ) m_pMGage_S->ResetGauge();
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
	const LPDIRECT3DDEVICE9		pD3DDevice	,						//	: デバイス
	const LPDIRECT3DTEXTURE9	pTexture	,						//	: テクスチャー
	const D3DXVECTOR3&			vScale		,						//	: 伸縮
	const D3DXQUATERNION&		vRot		,						//	: 回転
	const D3DXVECTOR3&			vPos		,						//	: 位置
	const bool					bEffect
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
	Debugger::DBGSTR::addStr(L"半径1 %f\n", m_Radius1);
	Debugger::DBGSTR::addStr(L"半径2 %f\n", m_Radius2);
	D3DXMatrixTranslation(&mMove, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling( &mScale, m_Radius1/m_vNormalSize.x, m_Radius2/m_vNormalSize.y, 1.0f );
	m_mMatrix	= mScale * mMove;

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
