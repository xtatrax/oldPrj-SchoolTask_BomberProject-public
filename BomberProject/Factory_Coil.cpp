////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Coil.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多寛之
//	編集			：曳地大洋
//					：佐藤涼
//	内包データと備考	：プレイヤーコイル関連
//	内包データと備考	：Coil関連
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagnetField ;
//			class Factory_Coil ;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_Coil.h"
//	: 基本のインクルード
//////////

//////////
//	: 追加のインクルード
#include "Factory_CheckPoint.h"
#include "Factory_Continue.h"
#include "Factory_Description.h"
#include "Factory_Score.h"

//	: 追加のインクルード
//////////

namespace wiz{
namespace bomberobject{

extern class WallObject ;

/**************************************************************************
 PlayerCoil 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::PlayerCoil(
////            ：    LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
////            ：    float Radius1,float Radius2,float Lenght,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////            ：    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////            ：    wiz::OBJID id = OBJID_3D_PLAYER)
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：  LPDIRECT3DDEVICE9   pD3DDevice   // デバイス
////            ：  LPTATRATEXTURE  pTexture     // テクスチャ	
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
		LPDIRECT3DDEVICE9	pD3DDevice		,
		float				Radius1			,
		float				Radius2			,
		float				Radius3			,
		float				Lenght			,
		D3DXVECTOR3&		vScale			,
		D3DXVECTOR3&		vRot			,
		D3DXVECTOR3&		vPos			,
		D3DCOLORVALUE&		Diffuse			,
		D3DCOLORVALUE&		Specular		,
		D3DCOLORVALUE&		Ambient			,
		LPTATRATEXTURE		pSuperFieldTex	,
		LPTATRATEXTURE		pModeChangeTex	,
		LPTATRATEXTURE		pDeadTex		,
		wiz::OBJID			id
	)
:Cylinder(pD3DDevice,Radius1,Radius2,Lenght,vPos,vRot,Diffuse,Specular,Ambient, id )
,MagneticObject()
,m_vPos( vPos )
,m_vRot( vRot )
,m_vScale(D3DXVECTOR3( 0.0f, 0.0f, 0.0f) )
,m_vOriginScale( vScale )
,m_vMove( D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) )
,m_vStartPos( vPos )

,m_iDeadCount( 0 )
,m_iMaxPosY( 0 )
,m_iScratchTime( 0 )
,m_fRecordTime( 0 )
,m_iChangeColorInterval( 0 )

,m_OBBRadius( Radius3 )
,m_fMoveDir( COIL_BASSROT )
,m_fMovdSpeed( COIL_SPEED )
,m_fAcceleration( NULL )
,m_fTurnAngle( PLAYER_TURN_ANGLE_Lv1 )
,m_fSuperTimeCount( 0.0f )
,m_fSuperFieldRotZ( 0.0f )
,m_fSuperTimeAccumulator( 0.0f )
,m_fLineMovingDistance( 0.0f )

,m_bLastMouseRB( false )
,m_bLastMouseLB( false )
,m_bReadyToStart( false )
,m_bReadyContinue( false )
,m_bRestart( true )
,m_pReStart( NULL )
,m_bModeChangeChar( false )
,m_bReDrawing_ChangeChar( true )
,m_bStandby( false )
,m_bIsFirstDeadLoop( false )
,m_bExpanding( true )
,m_bIsColorChange(false)
,m_bSuperSound( false )


,m_pCursor(	NULL )
,m_pCamera(	NULL )
,m_pSuperGage( NULL	)
,m_pSuperField( NULL )
,m_pPlayer(	NULL )
,m_pMagneticumObject( NULL )
,m_pTime( NULL )
,m_pContinueBehavior( NULL )

,m_enumCoilState( COIL_STATE_STOP )
,m_enumCoilStateSuper( COIL_STATE_SUPER_CHARGE )

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
,m_pDSPH(				NULL								)
,m_bDebugInvincibleMode(false								)
#endif
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pSphere	  = new Sphere(pD3DDevice,Radius3,vPos,vRot,Diffuse,Specular,Ambient);
	D3DXVECTOR3	v = COIL_SUPER_MODE_FIELD_SCALE;
		//LPTATRATEXTURE pTex2;
		//0(pD3DDevice,L"SuperField.png",&pTex2);
	m_pSuperField = new Box(pD3DDevice,v,vPos,vRot,Diffuse,Specular,Ambient,OBJID_3D_BOX,false,pSuperFieldTex);
	setPoleN();
	SetBaseRot(vRot);
		//0(pD3DDevice,L"CHANGE.png",&pTex2);
	m_pModeChangeChar	= new ModeChangeChar( pD3DDevice, pModeChangeTex,
														D3DXVECTOR3( 0.25f, 0.25f, 0.0f ), &Rect( 0, 0, 512, 128 ) );
	//m_pSphere->ShaderChange( new CookTrance(pD3DDevice) );

	const	D3DXVECTOR3	vDir1	= D3DXVECTOR3( cosf( D3DXToRadian(45.0f) ), sinf( D3DXToRadian(45.0f) ), 0.0f );
	const	D3DXVECTOR3	vDir2	= D3DXVECTOR3( cosf( D3DXToRadian(315.0f) ), sinf( D3DXToRadian(315.0f) ), 0.0f );
	const	D3DXVECTOR3	vDir3	= D3DXVECTOR3( cosf( D3DXToRadian(225.0f) ), sinf( D3DXToRadian(225.0f) ), 0.0f );
	const	D3DXVECTOR3	vDir4	= D3DXVECTOR3( cosf( D3DXToRadian(135.0f) ), sinf( D3DXToRadian(135.0f) ), 0.0f );
	const	float	fRangeW	= 3.5f;
	const	float	fRangeH	= 3.5f;
	m_pLine1		= new Line3D( g_vZero, vDir1, fRangeW, 0xFF00FFFF );
	m_pLine2		= new Line3D( m_pLine1->getEndPos(), vDir2, fRangeH, 0xFF00FFFF );
	m_pLine3		= new Line3D( m_pLine2->getEndPos(), vDir3, fRangeW, 0xFF00FFFF );
	m_pLine4		= new Line3D( m_pLine3->getEndPos(), vDir4, fRangeH, 0xFF00FFFF );

//	m_pDeadEffect	= NULL;
	m_pDeadEffect	= new DeadEffect( pD3DDevice, pDeadTex, m_vPos );


	//爆散エフェクトのポインタ
	//for( int i = 0; i < PARTICLS_NUM; i++ )
	//	m_pDeadEffect[i]	= NULL;
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
	m_pCursor				= NULL ;
//	m_pSphere				= NULL ;
	m_pSuperGage			= NULL ;
//	m_pSuperField			= NULL ;
	m_pReStart				= NULL ;
	m_pTime					= NULL ;
	//m_pDeadEffect			= NULL ;
	SafeDelete(m_pSphere);
	SafeDelete(m_pSuperField);
	
	SafeDelete(m_pModeChangeChar);
	SafeDelete(m_pLine1);
	SafeDelete(m_pLine2);
	SafeDelete(m_pLine3);
	SafeDelete(m_pLine4);
	SafeDelete(m_pDeadEffect);
	//int i ;
	//for( i = 0; i < PARTICLS_NUM; i++ ){
	//	SafeDelete(m_pDeadEffect[i]);
	//}
	////Debugger::DBGWRITINGLOGTEXT::addStr(L"PlayerCoil::~PlayerCoil >>>> for  >>>> SAFE_DELETE(m_pDeadEffect[i]); [%d / %d]個 削除完了 \n" , i, PARTICLS_NUM  );

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
	if( GetAsyncKeyState( MYVK_DEBUG_COIL_INVISIBLE ) )		m_bDebugInvincibleMode ? m_bDebugInvincibleMode = false : m_bDebugInvincibleMode = true ;
	if( m_bDebugInvincibleMode )							Debugger::DBGSTR::addStrTop( L"**********  無敵モード  **********\n" );
	if( !m_pDSPH ){
		SPHERE sp;
		sp.m_Center = g_vMax ;
		sp.m_Radius = 1.0f ;
		m_pDSPH = new DrawSphere( i_UpdatePacket.GetDevice(), sp );
	}
	if( GetAsyncKeyState( MYVK_DEBUG_INVISIBLEGAUGE_MAX ) ){
		m_pSuperGage->Recovery(-1) ;
	}
	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.m_pCntlState[0] ;
	//デバック用-----------------------------------------------------------
	// 磁界反転
	Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
	//-----------------------------------------------------------------------

#endif
#if defined(CF_DEBUG_JUMPTOOTHGOAL)
	if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RULER ) ){
		if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RULER_SUBKEY ) ){
			GoalObject*		pc		= (GoalObject*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CLEARAREA );
			if( pc )		m_vPos	= pc->GetPos();
			m_vPos.y -= 3.0f;
		}else{
			CheckPoint*		pc		= (CheckPoint*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CHECKPOINT );
			if( pc )		m_vPos	= pc->getLastPosition();
			m_vPos.y -= 3.0f;
		}
	}
#endif

	if( !m_pCursor )			m_pCursor				=        ( MouseCursor* ) i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CURSOR ) ; 
	if( !m_pCamera )			m_pCamera				=             ( Camera* ) i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA ) ; 
	if( !m_pMagneticumObject )	m_pMagneticumObject		=  ( StaticMagnetField* ) i_UpdatePacket.SearchObjectFromID( OBJID_3D_STATIC_MAGNET ) ; 
	if( !m_pReStart )			m_pReStart				=		 ( StartSprite* ) i_UpdatePacket.SearchObjectFromID( OBJID_SYS_START  ) ;
	if( !m_pSuperGage )			m_pSuperGage			=          ( SuperGage* ) i_UpdatePacket.SearchObjectFromID( OBJID_UI_SUPERGAUGE );
	if( !m_pContinueBehavior )	m_pContinueBehavior		=	( ContinueBehavior* ) i_UpdatePacket.SearchObjectFromID( OBJID_BEHAVIOR_CONTINUE );

	if( m_pPlayer ){

		

		if( m_enumCoilState != COIL_STATE_STICK ){
			m_bModeChangeChar		= false;
			m_bReDrawing_ChangeChar	= true;
			m_bStandby				= false;
		}

		//状態ごとの処理
		switch(m_enumCoilState){
			//スタート
			case COIL_STATE_START:
				Update_StateStart(i_UpdatePacket);
				break;
			//移動
			case COIL_STATE_MOVE:
				Update_StateMove(i_UpdatePacket);
				break;
			//磁界中心に吸着
			case COIL_STATE_STICK:
				if( m_bReDrawing_ChangeChar ){
					m_bModeChangeChar		= true;
					m_bReDrawing_ChangeChar	= false;
					m_pModeChangeChar->setStart();
				}
				Update_StateStick(i_UpdatePacket);
				break;
			//死亡
			case COIL_STATE_DEAD:
				Update_StateDead(i_UpdatePacket);
				this->CreateEffect(i_UpdatePacket);
				break;
			//コンティニュー
			case COIL_STATE_CONTINUE:
				Update_StateContinue(i_UpdatePacket);
				break;
			//クリア
			case COIL_STATE_STOP:
				Update_StateStop(i_UpdatePacket);
				break;
			default:
				break;
		}

		//ゲージが最大になったらCOIL_STATE_SUPER_READYに
		if(m_pSuperGage && m_pSuperGage->getRate() <= 0.0f && m_enumCoilStateSuper == COIL_STATE_SUPER_CHARGE && m_enumCoilState != COIL_STATE_CLEAR){
			m_enumCoilStateSuper = COIL_STATE_SUPER_READY;
			i_UpdatePacket.SearchSoundAndPlay(RCTEXT_SOUND_SE_SUPER_FULL);
		}
		//COIL_STATE_SUPER_READYの間はLineを更新
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY)Update_Line();
		//ホイールクリックで無敵状態に
		if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_READY && Cursor2D::getMButtonState())m_enumCoilStateSuper = COIL_STATE_SUPER_CHANGING;
		//無敵状態
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING)SuperMode(i_UpdatePacket);

		//デバック用-----------------------------------------------------------
		//Debugger::DBGSTR::addStr( L"角度 = %f\n",m_fMoveDir);
		//Debugger::DBGSTR::addStr( L"状態 = %d\n",m_enumCoilState);
		//-----------------------------------------------------------------------

		m_Material = MagneticObject::getMaterial() ;
		//マトリクス計算
		D3DXMATRIX mPos, mPos2, mScale, mRotZ, mRotX;
		D3DXVECTOR3 vCartesian  = ConvertToCartesianCoordinates(1.6f*(m_vScale.x/m_vOriginScale.x), m_fMoveDir);
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;									//球のPos
		D3DXMatrixTranslation( &mPos2 , m_vPos.x + vCartesian.x , m_vPos.y + vCartesian.y , m_vPos.z ) ;	//錐のPos
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - COIL_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos2 ;
		m_pSphere->CalcMatrix(mPos,mScale,mRotZ);
		m_pSphere->SetMaterial(m_Material );

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_USERMAGNET );
	}
	//カメラ座標設定
	if( m_pCamera ){
		m_pCamera->setPosY( m_vPos.y );
	}

	//if( m_pDeadEffect != NULL ){
	//	if(m_enumCoilState != COIL_STATE_DEAD){
	//		SafeDelete( m_pDeadEffect );
	//	}else{
	//		m_pDeadEffect->Update( i_UpdatePacket );
	//	}
	//}
	if( m_pDeadEffect && m_enumCoilState == COIL_STATE_DEAD )
		m_pDeadEffect->Update( i_UpdatePacket );
	//爆散エフェクト***********************************
	//for( int i = 0; i < PARTICLS_NUM; i++ ){
	//	if( m_pDeadEffect[i] != NULL ){
	//		if(m_enumCoilState != COIL_STATE_DEAD){
	//			SafeDelete( m_pDeadEffect[i] );
	//		}else{
	//			m_pDeadEffect[i]->Update( i_UpdatePacket );
	//		}
	//	}
	//}

		//if( m_enumCoilState != COIL_STATE_DEAD )
			//m_bDrawContinue	= false;
	//}
	//***********************************************
	//ModeChangeの座標指定
	float	wide	= BASE_CLIENT_WIDTH/50*m_vPos.x*2;
	float	height	= (BASE_CLIENT_HEIGHT/2-100.0f)*2;
	if( m_vPos.y < 12.0f ){
		height	= ((BASE_CLIENT_HEIGHT/2-100.0f)+(12.0f-m_vPos.y)*24)*2;
	}
	D3DXMATRIX	mTexMatrix, mTexPos, mTexScale;
	D3DXMatrixScaling( &mTexScale, 0.5f, 0.5f, 0.0f );
	D3DXMatrixTranslation( &mTexPos, wide, height, 0 );
	mTexMatrix	= mTexPos * mTexScale;
	m_pModeChangeChar->setMatrix(mTexMatrix);
	//***************************************************
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
//// 編集       ：曳地 大洋（画像の配置）
//// 備考       ：
////            ：
////
void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket ){

	if( m_bIsFirstDeadLoop ){
		m_bIsFirstDeadLoop = false;
		m_pDeadEffect->setPos( m_vPos );
		if( m_pContinueBehavior )m_pContinueBehavior->OperationStart();
		if( m_iDeadCount < MAX_DIGHT_SCORE ) ++m_iDeadCount;
	}
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
void PlayerCoil::Update_StateStart(UpdatePacket& i_UpdatePacket){

	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//マウス座標計算
	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//角度の更新
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//クリックし、離したらMOVE状態に変更
		if(Cursor2D::getLButtonState()){
			m_bLastMouseLB = true;
		}
		if(Cursor2D::getRButtonState()){
			m_bLastMouseRB = true;
		}
		if((!Cursor2D::getLButtonState() && m_bLastMouseLB) || (!Cursor2D::getRButtonState() && m_bLastMouseRB)){
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
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
void PlayerCoil::Update_StateMove(UpdatePacket& i_UpdatePacket){
	//プレイヤー磁界と自機の判定
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance && m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING){
		MagneticDecision(m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	if( m_pMagneticumObject && m_enumCoilStateSuper != COIL_STATE_SUPER_MOVE && m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING )
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
	if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE) m_fMovdSpeed = COIL_SPEED_SUPER;
	else											  m_fMovdSpeed = COIL_SPEED;

	if( m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING ){
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
void PlayerCoil::Update_StateStick(UpdatePacket& i_UpdatePacket){
	if(m_bReadyToStart){
		m_fMoveDir += COIL_ROTATION_ANGLE;
		if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);
		switch(getMagnetPole()){
			case POLE_S:
				if(!Cursor2D::getLButtonState() || !m_pPlayer->getDrawing()){
					m_enumCoilState = COIL_STATE_MOVE;
					m_fAcceleration = COIL_ACCELERATION_VALUE;
					m_bReadyToStart = false;
				}
				break;
			case POLE_N:
				if(!Cursor2D::getLButtonState() || !m_pPlayer->getDrawing()){
					m_enumCoilState = COIL_STATE_MOVE;
					m_fAcceleration = COIL_ACCELERATION_VALUE;
					m_bReadyToStart = false;
				}
				break;
		}
		m_bStandby	= true;
	}else{
		m_bStandby	= false;
		if(m_bExpanding){
			m_vScale += COIL_SCALE_ADD_VALUE_STICK;
			if(m_vScale.x >= m_vOriginScale.x * COIL_EXPANSION_VALUE_STICK){
				m_bExpanding = false;
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
				m_bExpanding = true;	
				m_bReadyToStart = true;
			}
		}
	}

	m_pModeChangeChar->Update(i_UpdatePacket);
};


/////////////////// ////////////////////
//// 関数名     ：PlayerCoil::SuperMode()
//// カテゴリ   ：
//// 用途       ：STATE_SUPER時の動き
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 編集       ：鴫原 徹
//// 備考       ：
////            ：
////
void PlayerCoil::SuperMode( UpdatePacket& i_UpdatePacket ){	
	
	float			fScalePercentage;
	D3DXMATRIX mPos, mScale, mRotZ;
	//無敵モードに変換し終わるまではゲージを消費しない
	switch(m_enumCoilStateSuper){
		case COIL_STATE_SUPER_MOVE:
			if( !m_bSuperSound){
				i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_INVISIBLE  );
				m_bSuperSound = true ;
			}
			if(m_enumCoilState == COIL_STATE_MOVE)
				m_fSuperTimeCount += (float)i_UpdatePacket.GetTime()->getElapsedTime();

			m_fSuperFieldRotZ += 5.0f;
			if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);
			fScalePercentage = 1.0f - m_fSuperTimeCount / COIL_SUPER_MODE_TIME;
			D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
			D3DXMatrixScaling( &mScale, 
								m_vScale.x * fScalePercentage + m_OBBRadius/4, 
								m_vScale.y * fScalePercentage + m_OBBRadius/4, 
								m_vScale.z);
			D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fSuperFieldRotZ ) ) ;
			break;

		case COIL_STATE_SUPER_CHANGING:
			m_fSuperTimeCount += (float)i_UpdatePacket.GetTime()->getElapsedTime()*0.7f;
			m_fSuperFieldRotZ += 5.0f;
			D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
			if(m_vScale.x >= m_vScale.x * m_fSuperTimeCount && m_vScale.y >= m_vScale.y * m_fSuperTimeCount){
				D3DXMatrixScaling( &mScale, 
									m_vScale.x * m_fSuperTimeCount, 
									m_vScale.y * m_fSuperTimeCount, 
									m_vScale.z);
			}else{
				D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
				m_enumCoilStateSuper = COIL_STATE_SUPER_MOVE;
				m_fSuperTimeCount = 0.0f;
				m_fAcceleration = COIL_ACCELERATION_VALUE;
			}
			D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fSuperFieldRotZ ) ) ;
			break;

		default:
			break;
	}

	m_pSuperField->CalcMatrix(mPos,mScale,mRotZ);

	//色の点滅
	if(m_iChangeColorInterval == 0){
		if(m_bIsColorChange){
			m_bIsColorChange = false;
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
			m_bIsColorChange  = true;
			setColorSuper();
		}
	}
	m_iChangeColorInterval++;
	if(m_iChangeColorInterval >= COIL_SUPER_MODE_TIME*2 - ((int)m_fSuperTimeCount*2-1)) m_iChangeColorInterval = 0;

	//ゲージ減少
	if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE){
		if( ( m_fSuperTimeAccumulator += (float)i_UpdatePacket.GetTime()->getElapsedTime()) < COIL_SUPER_MODE_TIME ){
			float fOneSecondSub = (1.0f / (float)COIL_SUPER_MODE_TIME);
			float fFrameSub     = fOneSecondSub * (float)i_UpdatePacket.GetTime()->getElapsedTime();
			m_pSuperGage->Consume( -fFrameSub );	
		}
	}else{
		m_fSuperTimeAccumulator = 0 ;	
	}

	//無敵モード終了
	if(m_fSuperTimeCount >= COIL_SUPER_MODE_TIME){
		m_enumCoilStateSuper = COIL_STATE_SUPER_CHARGE;
		if( m_bSuperSound ){
			i_UpdatePacket.SoundStop( RCTEXT_SOUND_SE_INVISIBLE  );
			m_bSuperSound = false ;
		}
		m_fSuperTimeCount = 0.0f;
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
void PlayerCoil::Update_StateDead(UpdatePacket& i_UpdatePacket){
	m_vScale = g_vZero;
	if( m_bReadyContinue ){
		m_enumCoilState = COIL_STATE_CONTINUE;
		//if( m_pReStart )	m_pReStart->ReStart();
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
void PlayerCoil::Update_StateContinue(UpdatePacket& i_UpdatePacket){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;

	//マウス座標計算
	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//角度の更新
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//クリックし、離したらMOVE状態に変更
		if(Cursor2D::getLButtonState()){
			m_bLastMouseLB = true;
		}
		if(Cursor2D::getRButtonState()){
			m_bLastMouseRB = true;
		}
		if((!Cursor2D::getLButtonState() && m_bLastMouseLB) || (!Cursor2D::getRButtonState() && m_bLastMouseRB)){
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
			m_enumCoilState = COIL_STATE_MOVE;
			m_fAcceleration = COIL_ACCELERATION_VALUE;
			m_bLastMouseLB  = false;
			m_bLastMouseRB  = false;
			m_bReadyToStart = false;
			m_bRestart		= true;
		}
	}else{
		m_vScale += COIL_SCALE_ADD_VALUE_START;
		if( m_vScale.x >= m_vOriginScale.x && m_vScale.y >= m_vOriginScale.y ){
			m_vScale = m_vOriginScale;
			if( m_bRestart ){
				m_iScratchTime	= m_fRecordTime;
				if( m_pReStart )	m_pReStart->ReStart();
				m_bRestart	= false;
			}//m_bReadyToStart = true;
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
void PlayerCoil::Update_StateStop(UpdatePacket& i_UpdatePacket){
	D3DXVECTOR3 vPlayer		= g_vZero	;
	float		fTargetDir	= NULL		;

	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();


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

	//テクスチャがない場合
	// マトリックスをレンダリングパイプラインに設定
	i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);
	//コモンメッシュのDraw()を呼ぶ
	CommonMesh::Draw(i_DrawPacket);

	if( g_bIsCookTranceEnable_Coil ){
		((CookTrance*)m_pSphere->getShader())->Draw(i_DrawPacket,m_pSphere);
	}
	else{
		m_pSphere->Draw(i_DrawPacket);
	}
	if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING){
		m_pSuperField->Draw(i_DrawPacket);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif
	//ライン用にワールド座標再定義
	D3DXMATRIX	mRot, mPos;
	D3DXMatrixIdentity( &mRot );
	D3DXMatrixTranslation( &mPos, m_vPos.x, m_vPos.y, m_vPos.z );
	m_Matrix	= mRot*mPos;
	i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);

	if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY && m_enumCoilState != COIL_STATE_DEAD && m_enumCoilState != COIL_STATE_CLEAR){
		m_pLine1->draw(i_DrawPacket.GetDevice());
		m_pLine2->draw(i_DrawPacket.GetDevice());
		m_pLine3->draw(i_DrawPacket.GetDevice());
		m_pLine4->draw(i_DrawPacket.GetDevice());
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

	//爆散
	if( m_pDeadEffect && m_enumCoilState == COIL_STATE_DEAD )
		m_pDeadEffect->Draw( i_DrawPacket );

	if( m_bModeChangeChar )
		m_pModeChangeChar->Draw(i_DrawPacket);
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
void PlayerCoil::MagneticDecision( D3DXVECTOR3& i_vMagnetPos, POLE i_bMagnetPole_Field ) {
	float	fWorkDir	= m_fMoveDir ;
	float	fTargetDir	= TwoPoint2Degree( i_vMagnetPos , getPos() );
	float	fReverse	= 0.0f;
	if(fWorkDir > 180.0f){
		fReverse = fWorkDir - 180.0f;
	}
	else{
		fReverse = fWorkDir + 180.0f;
	}

	if(i_bMagnetPole_Field != this->getMagnetPole()){
		if(fWorkDir < fTargetDir){
			if(fTargetDir - fWorkDir <= 180.0f){
				fWorkDir += m_fTurnAngle;
				fWorkDir = float(int(fWorkDir) % 360);						
			}
			else{
				fWorkDir -= m_fTurnAngle;
				if(fWorkDir < 0.0f){
					fWorkDir += 360.0f;
				}
			}
		}
		else if(fWorkDir > fTargetDir){
			if(fWorkDir - fTargetDir <= 180.0f){
				fWorkDir -= m_fTurnAngle;
				if(fWorkDir < 0.0f){
					fWorkDir += 360.0f;
				}
			}
			else{
				fWorkDir += m_fTurnAngle;
				fWorkDir = float(int(fWorkDir) % 360);												
			}
		}
	}
	else{
		if(fReverse != fTargetDir){
			if(fWorkDir < fTargetDir){
				if(fTargetDir - fWorkDir <= 180.0f){
					fWorkDir -= m_fTurnAngle;
					if(fWorkDir < 0.0f){
						fWorkDir += 360.0f;
					}
				}
				else{
					fWorkDir += m_fTurnAngle;
					fWorkDir = float(int(fWorkDir) % 360);						
				}
			}
			else if(fWorkDir > fTargetDir){
				if(fWorkDir - fTargetDir <= 180.0f){
					fWorkDir += m_fTurnAngle;
					fWorkDir = float(int(fWorkDir) % 360);												
				}
				else{
					fWorkDir -= m_fTurnAngle;
					if(fWorkDir < 0.0f){
						fWorkDir += 360.0f;
					}
				}
			}
		}
	}
	m_fMoveDir = fWorkDir ;
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

/////////////////// ////////////////////
//// 関数名     ：SuperGage::Update_Line()
//// カテゴリ   ：関数
//// 用途       ：Lineの更新
//// 引数       ：なし
//// 戻値       ：なし
//// 担当       ：本多寛之
//// 備考       ：
////            ：
void PlayerCoil::Update_Line(){

	D3DXMATRIX		mLineScale, mLinePos;
	D3DXVECTOR3		vLineScale = D3DXVECTOR3(1.0f,1.0f,0.0f),
		vBaseLinePos = D3DXVECTOR3(-m_pLine1->getEndPos().x,-m_pLine2->getEndPos().y,0.0f),
					vLinePos;
	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );
	
	//左上部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - m_fLineMovingDistance, 
							  vBaseLinePos.y + m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine1->setMatrix( mLineScale * mLinePos );
	//右上部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + m_fLineMovingDistance,
							  vBaseLinePos.y + m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine2->setMatrix( mLineScale * mLinePos );
	//左下部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + m_fLineMovingDistance,
							  vBaseLinePos.y - m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine3->setMatrix( mLineScale * mLinePos );
	//右下部
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - m_fLineMovingDistance,
							  vBaseLinePos.y - m_fLineMovingDistance, 
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine4->setMatrix( mLineScale * mLinePos );
	
	m_fLineMovingDistance	+= 0.04f;
	if(m_fLineMovingDistance >= 0.3f){
		m_fLineMovingDistance	= 0.0f;
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
Factory_Coil::Factory_Coil( FactoryPacket* fpac, DWORD dwResumptionCheckPoint, D3DXVECTOR3* vStartPos  ){
	try{

		D3DXVECTOR3 vScale( 1.0f, 1.0f, 1.0f );
		D3DXVECTOR3 vPos( 25.0f, 5.0f,0.0f );
 		D3DCOLORVALUE CoilDiffuse = {1.0f,1.0f,1.0f,0.0f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {1.0f,1.0f,1.0f,0.0f};


		CheckPoint*									pc		= (CheckPoint*)fpac->SearchObjectFromID( OBJID_SYS_CHECKPOINT );
		if( vStartPos )								vPos	= *vStartPos;
		else if( dwResumptionCheckPoint && pc )		vPos	= pc->getThisPosition(dwResumptionCheckPoint);
		//LPTATRATEXTURE pTex;
		//0(fpac->GetDevice(),L"DeadPerticul.png",&pTex);
/*pTex2*/
		fpac->AddObject(
			new PlayerCoil(
				fpac->GetDevice(),
				0.0f,0.7f,1.0f,1.0f,vScale,D3DXVECTOR3(90.0f,0.0f,0.0f),vPos,
				CoilDiffuse,CoilSpecular,CoilAmbient	,
				fpac->AddTexture( L"SuperField.png" )	,
				fpac->AddTexture( L"CHANGE.png" )		,
				fpac->AddTexture( L"DeadPerticul.png" )
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
