////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Coil.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 曳地大洋(編集) 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagneticumObject3D ;
//			class Factory_Coil ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Coil.h"
#include "BassItems.h"
#include "Factory_Wall.h"
#include "Factory_Cursor.h"


namespace wiz{
namespace bomberobject{

extern class WallObject ;

/**************************************************************************
 PlayerCoil 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::PlayerCoil(
////            ：    LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    float Radius1,float Radius2,float Lenght,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////            ：    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////            ：    wiz::OBJID id = OBJID_3D_PLAYER)
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：  LPDIRECT3DDEVICE9   pD3DDevice   // デバイス
////            ：  LPDIRECT3DTEXTURE9  pTexture     // テクスチャ	
////            ：  float               Radius1      // 錐の直径1
////            ：  float               Radius2      // 錐の直径2
////            ：  float               Radius3      // 球の直径
////            ：  flaot               Lenght       // 高さ
////            ：  D3DXVECTOR3&        vScale       // 伸縮
////            ：  D3DXVECTOR3&        vRot         // 回転角
////            ：  D3DXVECTOR3&        vPos         // 位置
////            ：  D3DCOLORVALUE&      Diffuse      // ディフューズ色
////            ：  D3DCOLORVALUE&      Specular     // スペキュラ色
////            ：  D3DCOLORVALUE&      Ambient      // アンビエント色
////            ：  wiz::OBJID          id = OBJID_3D_COIL //ID
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 引継ぎ     ：本多寛之
//// 備考       ：
////            ：
////
PlayerCoil::PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,LPDIRECT3DTEXTURE9 pTexture_Super,
		LPDIRECT3DTEXTURE9 pTexture_Dead,LPDIRECT3DTEXTURE9 pTexture_Continue,LPDIRECT3DTEXTURE9 pTexture_Title,
		LPDIRECT3DTEXTURE9 pTexture_DeadChar,
		float Radius1,float Radius2,float Radius3,float Lenght,
		D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id
	)
:MagneticumObject3D(pD3DDevice,pTexture,
					Radius1,Radius2,Lenght,vRot,vPos,
					Diffuse,Specular,Ambient,id)
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(D3DXVECTOR3( 0.0f, 0.0f, 0.0f))
,m_vOriginScale(vScale)
,m_OBBRadius(Radius3)
,m_vMove(D3DXVECTOR3( 1.0f, 0.0f, 0.0f))
,m_fMoveDir(COIL_BASSROT)
,m_fMovdSpeed(COIL_SPEED)
,m_fAcceleration(NULL)
,m_vStartPos(vPos)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bReadyToStart(false)
,m_bReadyContinue(false)
,m_bReadyToSuper(false)
,m_bIsSuperMode(false)
,m_bDrawContinue( false )
,m_pSuperField(NULL)
,m_fTurnAngle(PLAYER_TURN_ANGLE_Lv1)
,m_pPlayer(NULL)
,m_pMagneticumObject(NULL)
,m_pCamera(NULL)
,m_pSound( NULL )
,m_pDeadTex(pTexture_Dead)
,m_pContinueTex( pTexture_Continue )
,m_pTitleTex( pTexture_Title )
,m_pDeadCharTex( pTexture_DeadChar )
,m_enumCoilState(COIL_STATE_STOP)
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
,m_pDSPH(NULL)
,m_bDebugInvincibleMode( false )
#endif
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pSphere	  = new Sphere(pD3DDevice,Radius3,vPos,vRot,Diffuse,Specular,Ambient);
	D3DXVECTOR3	v = COIL_SUPER_MODE_FIELD_SCALE;
	m_pSuperField = new Box(pD3DDevice,v,vPos,vRot,Diffuse,Specular,Ambient,OBJID_3D_BOX,false,pTexture_Super);
	setPoleN();
	SetBaseRot(vRot);

	m_pSelect	= NULL;
	m_pSelect2	= NULL;
	m_pDeadChar	= NULL;
	//爆散エフェクトのポインタ
	for( int i = 0; i < PARTICLS_NUM; i++ )
		m_pDeadEffect[i]	= NULL;
}
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::~PlayerCoil()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ： 鴫原 徹
//// 備考       ：
////            ：
////
PlayerCoil::~PlayerCoil(){

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	SafeDelete( m_pDSPH );
#endif
	m_pCamera				= NULL ;
	m_pPlayer				= NULL ;
	m_pMagneticumObject		= NULL ;
	m_pCamera				= NULL ;
	m_pSphere				= NULL ;
	m_pSuperField			= NULL ;
	
	SAFE_DELETE(m_pSelect);
	SAFE_DELETE(m_pSelect2);
	SAFE_DELETE(m_pDeadChar);
	for( int i = 0; i < PARTICLS_NUM; i++ )
		SAFE_DELETE(m_pDeadEffect[i]);

};

/////////////////// ////////////////////
//// 用途       ：bool PlayerCoil::HitTestWall( OBB Obb )
//// カテゴリ   ：メンバ関数
//// 用途       ：壁との衝突判定
//// 引数       ：  OBB Obb           //  : 検査対象のOBB
//// 戻値       ：衝突していればtrue
//// 担当者     ：曳地 大洋
//// 備考       ：
bool PlayerCoil::HitTestWall( OBB Obb ){
	SPHERE sp;
	sp.m_Center = m_vPos;
	sp.m_Radius = m_OBBRadius;
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
//// 関数名     ：void PlayerCoil::Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：  UpdatePacket& i_UpdatePacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 引継ぎ     ：本多寛之
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
		m_pMagneticumObject = ( MagneticumObject3D* ) SearchObjectFromTypeID( i_UpdatePacket.pVec, typeid(MagneticumObject3D) ) ; 
	}
	if( m_pPlayer ){
		//デバック用-----------------------------------------------------------
		// 磁界反転
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		//状態ごとの処理
		switch(m_enumCoilState){
			//スタート
			case COIL_STATE_START:
				Update_StateStart();
				break;
			//移動
			case COIL_STATE_MOVE:
				Update_StateMove();
				break;
			//磁界中心に吸着
			case COIL_STATE_STICK:
				Update_StateStick();
				break;
			//死亡
			case COIL_STATE_DEAD:
				Update_StateDead();
				if( m_pDeadEffect[0] == NULL )
					CreateEffect(i_UpdatePacket);
				break;
			//コンティニュー
			case COIL_STATE_CONTINUE:
				Update_StateContinue();
				break;
			//クリア
			case COIL_STATE_STOP:
				Update_StateStop();
				break;
			default:
				break;
		}
		if(m_bIsSuperMode){
			//無敵状態
			SuperMode(i_UpdatePacket);
		}

		//デバック用-----------------------------------------------------------
		Debugger::DBGSTR::addStr( L"角度 = %f\n",m_fMoveDir);
		Debugger::DBGSTR::addStr( L"状態 = %d\n",m_enumCoilState);
		//-----------------------------------------------------------------------

		//マトリクス計算
		D3DXMATRIX mPos, mPos2, mScale, mRotZ, mRotX;
		D3DXVECTOR3 vCartesian  = ConvertToCartesianCoordinates(1.6f*(m_vScale.x/m_vOriginScale.x), m_fMoveDir);
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;		//球のPos
		D3DXMatrixTranslation( &mPos2 , m_vPos.x + vCartesian.x , m_vPos.y + vCartesian.y , m_vPos.z ) ;		//錐のPos
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - COIL_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos2 ;
		m_pSphere->CalcMatrix(mPos,mScale,mRotZ);
		m_pSphere->SetMaterial( m_Material );

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer3D) );
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

	//爆散エフェクト***********************************
	if( m_pDeadEffect[0] != NULL ){
		for( int i = 0; i < PARTICLS_NUM; i++ ){
			m_pDeadEffect[i]->Update( i_UpdatePacket );
		}
	}
	if( m_pDeadEffect[0] != NULL ){
		if(m_enumCoilState != COIL_STATE_DEAD){
			for( int i = 0; i < PARTICLS_NUM; i++ ){
				SafeDelete( m_pDeadEffect[i] );
				continue;
			}
		}
	}
	//***************************************************
	if( m_pDeadChar != NULL ){
		if( m_pDeadChar->getAlpha() <= 0 ){
			SafeDelete( m_pDeadChar );
			m_bDrawContinue	= true;
		}
	}
	if( m_pDeadChar != NULL ){
		m_pDeadChar->Update(i_UpdatePacket);
	}
	//ロゴ****************************************
	if( m_bDrawContinue ){
		if( m_pSelect != NULL ){
			if( m_enumCoilState != COIL_STATE_DEAD )
				SafeDelete( m_pSelect );
		}
		if( m_pSelect2 != NULL ){
			if( m_enumCoilState != COIL_STATE_DEAD )
				SafeDelete( m_pSelect2 );
		}

		if( m_pSelect != NULL ){
			m_pSelect->Update(i_UpdatePacket);
		}
		if( m_pSelect2 != NULL ){
			m_pSelect2->Update(i_UpdatePacket);
		}

		if( m_enumCoilState != COIL_STATE_DEAD )
			m_bDrawContinue	= false;
	}
	//***********************************************

};

/////////////////// ////////////////////
//// 関数名     ：void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当       ：佐藤涼
//// 備考       ：
////            ：
////
void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket ){

	//爆散エフェクトの作成
	for( int i = 0; i < PARTICLS_NUM; i++ ){
		m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.pD3DDevice, m_vPos,
					float((360/PARTICLS_NUM) * i), m_pDeadTex );
	}

	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;

	m_pDeadChar	= new Dead( i_UpdatePacket.pD3DDevice, m_pDeadCharTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
					D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),NULL,g_vZero,g_vZero);

	//Continue,Titleロゴの作成
	m_pSelect	= new Continue( i_UpdatePacket.pD3DDevice, m_pContinueTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,D3DXVECTOR3( wide-128.0f,height-100.0f,0.0f ),
								Rect( 0,0,256,64 ), g_vZero, g_vZero );
	m_pSelect2	= new Continue( i_UpdatePacket.pD3DDevice, m_pTitleTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,D3DXVECTOR3( wide-64.0f,height,0.0f ),
								Rect( 0,0,128,64 ), g_vZero, g_vZero );

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
	if(m_bReadyToStart){
		//クリックし、離したらMOVE状態に変更
		if(g_bMouseLB){
			m_bLastMouseLB = true;
		}
		if(g_bMouseRB){
			m_bLastMouseRB = true;
		}
		if((!g_bMouseLB && m_bLastMouseLB) || (!g_bMouseRB && m_bLastMouseRB)){
			m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
			m_enumCoilState =  COIL_STATE_MOVE;
			m_fAcceleration = COIL_ACCELERATION_VALUE;
			m_bLastMouseLB  =  false;
			m_bLastMouseRB  =  false;
			m_bReadyToStart =  false;
		}
	}else{
		m_vScale += COIL_SCALE_ADD_VALUE_START;
		if( m_vScale.x >= m_vOriginScale.x && m_vScale.y >= m_vOriginScale.y ){
			m_vScale = m_vOriginScale;
			m_bReadyToStart = true;
		}
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
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance ){
		m_fMoveDir = MagneticDecision(m_fMoveDir,m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	if( m_pMagneticumObject )
		m_pMagneticumObject->HitTest();
	//	//設置磁界と自機の判定
	//	TARGETCONTAINER ItemMap_Target = m_pMagneticumObject->getMapTarget();
	//	multimap<float,Magnet3DItem*>::iterator it = ItemMap_Target.begin();
	//	while(it != ItemMap_Target.end()){
	//		bool bCheckDistance = CheckDistance( it->second->m_vPos, m_vPos, (float)MGPRM_MAGNETICUM_QUAD, false );
	//		if( bCheckDistance ){
	//			m_fMoveDir = MagneticDecision(m_fMoveDir,it->second->m_vPos,it->second->m_bMagnetPole);
	//		}
	//		++it;
	//	}
	//}
	//速度指定
	if(m_bIsSuperMode) m_fMovdSpeed = COIL_SPEED_SUPER;
	else			   m_fMovdSpeed = COIL_SPEED;

	if( (m_bIsSuperMode && m_bReadyToSuper) || (!m_bIsSuperMode && !m_bReadyToSuper) ){
		//指定方向へ指定距離移動
		ArcMove( m_vMove , m_fMovdSpeed + m_fAcceleration, m_fMoveDir);
		if(m_fAcceleration >= 0.0f){
			m_fAcceleration -= COIL_ACCELERATION_DECREASE;
			if(m_fAcceleration <= 0.0f)m_fAcceleration = 0.0f;
		}
		if(m_fAcceleration < 0.0f){
			m_fAcceleration += COIL_ACCELERATION_DECREASE;
			if(m_fAcceleration >= 0.0f)m_fAcceleration = 0.0f;
		}
		//移動分を加算
		m_vPos += m_vMove;
	}

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
	if(m_bReadyToStart){
		m_fMoveDir += COIL_ROTATION_ANGLE;
		if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);
		switch(getMagnetPole()){
			case POLE_S:
				if(!g_bMouseRB || !m_pPlayer->getDrawing()){
					m_enumCoilState = COIL_STATE_MOVE;
					m_fAcceleration = COIL_ACCELERATION_VALUE;
					m_bReadyToStart = false;
				}
				break;
			case POLE_N:
				if(!g_bMouseLB || !m_pPlayer->getDrawing()){
					m_enumCoilState = COIL_STATE_MOVE;
					m_fAcceleration = COIL_ACCELERATION_VALUE;
					m_bReadyToStart = false;
				}
				break;
		}
	}else{
		static bool s_bExpanding = true;
		if(s_bExpanding){
			m_vScale += COIL_SCALE_ADD_VALUE_STICK;
			if(m_vScale.x >= m_vOriginScale.x * COIL_EXPANSION_VALUE_STICK){
				s_bExpanding = false;
				switch(getMagnetPole()){
					case POLE_S:
						setPoleN();
						break;
					case POLE_N:
						setPoleS();
						break;
				}
			}
		}else{
			m_vScale -= COIL_SCALE_ADD_VALUE_STICK;
			if( m_vScale.x <= m_vOriginScale.x && m_vScale.y <= m_vOriginScale.y ){
				s_bExpanding = true;	
				m_bReadyToStart = true;
			}
		}
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
	static float	s_fTimeCount		= 0;
	static int		s_iInterval			= 0;
	static bool		s_bIsColorChange	= false;
	static bool		s_bSound			= false;
	static float	s_fSFieldRotZ		= 0.0f;

	if( m_pSound && !s_bSound){
		m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_INVISIBLE , (BYTE)(COIL_SUPER_MODE_TIME / MGPRM_INVISIBLESOUND_TIME) +1 );
		s_bSound = true ;
	}
	
	D3DXMATRIX mPos, mScale, mRotZ;
	//無敵モードに変換し終わるまではゲージを消費しない
	if(m_bReadyToSuper){

		if(m_enumCoilState == COIL_STATE_MOVE)
			s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();

		s_fSFieldRotZ += 5.0f;
		if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);
		float fScalePercentage = 1.0f - s_fTimeCount / COIL_SUPER_MODE_TIME;
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
		D3DXMatrixScaling( &mScale, 
							m_vScale.x * fScalePercentage + m_OBBRadius/4, 
							m_vScale.y * fScalePercentage + m_OBBRadius/4, 
							m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( s_fSFieldRotZ ) ) ;
	}
	else{
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
		s_fSFieldRotZ += 5.0f;
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
		if(m_vScale.x >= m_vScale.x * s_fTimeCount && m_vScale.y >= m_vScale.y * s_fTimeCount){
			D3DXMatrixScaling( &mScale, 
								m_vScale.x * s_fTimeCount, 
								m_vScale.y * s_fTimeCount, 
								m_vScale.z);
		}else{
			D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
			m_bReadyToSuper = true;
			s_fTimeCount = 0.0f;
			m_fAcceleration = COIL_ACCELERATION_VALUE;
		}
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( s_fSFieldRotZ ) ) ;
	}
	m_pSuperField->CalcMatrix(mPos,mScale,mRotZ);

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
	if(s_iInterval >= COIL_SUPER_MODE_TIME*2 - ((int)s_fTimeCount*2-1)) s_iInterval = 0;

	//無敵モード終了
	if(s_fTimeCount >= COIL_SUPER_MODE_TIME){
		m_bIsSuperMode	= false;
		m_bReadyToSuper = false;
		s_bSound		= false;
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
	m_vScale = g_vZero;
	if( m_bReadyContinue ){
		m_enumCoilState = COIL_STATE_CONTINUE;
		m_vPos = m_vStartPos;
		m_pCamera->setPosY(m_vStartPos.y);
		m_bReadyContinue	= false;
	}

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
	if(m_bReadyToStart){
		//クリックし、離したらMOVE状態に変更
		if(g_bMouseLB){
			m_bLastMouseLB = true;
		}
		if(g_bMouseRB){
			m_bLastMouseRB = true;
		}
		if((!g_bMouseLB && m_bLastMouseLB) || (!g_bMouseRB && m_bLastMouseRB)){
			m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
			m_enumCoilState = COIL_STATE_MOVE;
			m_fAcceleration = COIL_ACCELERATION_VALUE;
			m_bLastMouseLB  = false;
			m_bLastMouseRB  = false;
			m_bReadyToStart = false;
		}
	}else{
		m_vScale += COIL_SCALE_ADD_VALUE_START;
		if( m_vScale.x >= m_vOriginScale.x && m_vScale.y >= m_vOriginScale.y ){
			m_vScale = m_vOriginScale;
			m_bReadyToStart = true;
		}
	}
};

/////////////////// ////////////////////
//// 関数名     ：void PlayerCoil::Update_StateStop()
//// カテゴリ   ：
//// 用途       ：STATE_STOP時の動き
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：佐藤涼
//// 備考       ：
////            ：
////
void PlayerCoil::Update_StateStop(){
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

	m_vScale += COIL_SCALE_ADD_VALUE_STOP;
	if( m_vScale.x >= m_vOriginScale.x && m_vScale.y >= m_vOriginScale.y ){
		m_vScale = m_vOriginScale;
		m_bReadyToStart = true;
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
		m_pSphere->Draw(i_DrawPacket);
		if(m_bIsSuperMode)m_pSuperField->Draw(i_DrawPacket);
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
		m_pSphere->Draw(i_DrawPacket);
		if(m_bIsSuperMode)m_pSuperField->Draw(i_DrawPacket);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

	//爆散
	if( m_pDeadEffect[0] != NULL ){
		for( int i = 0; i < PARTICLS_NUM; i++ ){
			m_pDeadEffect[i]->Draw( i_DrawPacket );
		}
	}

	if( m_pDeadChar != NULL ){
		m_pDeadChar->Draw(i_DrawPacket);
	}

	if( m_bDrawContinue ){
		//ロゴ
		if( m_pSelect != NULL ){
			m_pSelect->Draw(i_DrawPacket);
		}
		if( m_pSelect2 != NULL ){
			m_pSelect2->Draw(i_DrawPacket);
		}
	}
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
bool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, float i_iBorder, bool IsPlayer ){
	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, m_vPos ) ;
	if( Lng <= i_iBorder ){
		float fBorderLv = i_iBorder/3;
		if(m_enumCoilState == COIL_STATE_MOVE
						&& getMagnetPole() != m_pPlayer->getMagnetPole()
								&& Lng <= fBorderLv/30
									&& IsPlayer
										&& m_pPlayer->getDrawing()){
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
 Factory_Coil 定義部
****************************************************************************/
/**************************************************************************
 Factory_Coil::Factory_Coil(
	FactoryPacket* fpac		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Coil::Factory_Coil( FactoryPacket* fpac, D3DXVECTOR3* vStartPos  ){
	try{

		D3DXVECTOR3 vScale( 1.0f, 1.0f, 1.0f );
		D3DXVECTOR3 vPos( 25.0f, 5.0f,0.0f );
 		D3DCOLORVALUE CoilDiffuse = {1.0f,1.0f,1.0f,0.0f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {1.0f,1.0f,1.0f,0.0f};
		if( vStartPos ){
			vPos = *vStartPos ;
		}
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				NULL,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"SuperField.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadPerticul.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Continue.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Go_Title.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadChar.png" ),
				0.0f,0.7f,1.0f,1.0f,vScale,D3DXVECTOR3(90.0f,0.0f,0.0f),vPos,
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
Factory_Coil::~Factory_Coil(){

}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
