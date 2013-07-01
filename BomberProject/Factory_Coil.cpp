////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Coil.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�����V
//	�ҏW			�F�g�n��m
//					�F������
//	�����ް��Ɣ��l	�F�v���C���[�R�C���֘A
//	�����ް��Ɣ��l	�FCoil�֘A
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagnetField ;
//			class Factory_Coil ;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_Coil.h"
//	: ��{�̃C���N���[�h
//////////

//////////
//	: �ǉ��̃C���N���[�h
#include "Factory_CheckPoint.h"
#include "Factory_Continue.h"
#include "Factory_Description.h"
#include "Factory_Score.h"

//	: �ǉ��̃C���N���[�h
//////////

namespace wiz{
namespace bomberobject{

extern class WallObject ;

/**************************************************************************
 PlayerCoil ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPlayerCoil::PlayerCoil(
////            �F    LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    float Radius1,float Radius2,float Lenght,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////            �F    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////            �F    wiz::OBJID id = OBJID_3D_PLAYER)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F  LPDIRECT3DDEVICE9   pD3DDevice   // �f�o�C�X
////            �F  LPDIRECT3DTEXTURE9  pTexture     // �e�N�X�`��	
////            �F  float               Radius1      // ���̒��a1
////            �F  float               Radius2      // ���̒��a2
////            �F  float               Radius3      // ���̒��a
////            �F  flaot               Lenght       // ����
////            �F  D3DXVECTOR3&        vScale       // �L�k
////            �F  D3DXVECTOR3&        vRot         // ��]�p
////            �F  D3DXVECTOR3&        vPos         // �ʒu
////            �F  D3DCOLORVALUE&      Diffuse      // �f�B�t���[�Y�F
////            �F  D3DCOLORVALUE&      Specular     // �X�y�L�����F
////            �F  D3DCOLORVALUE&      Ambient      // �A���r�G���g�F
////            �F  wiz::OBJID          id = OBJID_3D_COIL //ID
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���p��     �F�{�����V
//// ���l       �F
////            �F
////
PlayerCoil::PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,TextureManager* m_pTexMgr,
		float Radius1,float Radius2,float Radius3,float Lenght,
		D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTex,
		wiz::OBJID id
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
,m_pDeadTex( pTex )
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
		//LPDIRECT3DTEXTURE9 pTex2;
		//0(pD3DDevice,L"SuperField.png",&pTex2);
	m_pSuperField = new Box(pD3DDevice,v,vPos,vRot,Diffuse,Specular,Ambient,OBJID_3D_BOX,false,
									/*pTex2*/m_pTexMgr->addTexture( pD3DDevice, L"SuperField.png" ) );
	setPoleN();
	SetBaseRot(vRot);
		//0(pD3DDevice,L"CHANGE.png",&pTex2);
	m_pModeChangeChar	= new ModeChangeChar( pD3DDevice, /*pTex2*/m_pTexMgr->addTexture( pD3DDevice, L"CHANGE.png" ),
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
	m_pDeadEffect	= new DeadEffect( pD3DDevice, m_pDeadTex, m_vPos );


	//���U�G�t�F�N�g�̃|�C���^
	//for( int i = 0; i < PARTICLS_NUM; i++ )
	//	m_pDeadEffect[i]	= NULL;
}
/////////////////// ////////////////////
//// �֐���     �FPlayerCoil::~PlayerCoil()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F ���� �O
//// ���l       �F
////            �F
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
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"PlayerCoil::~PlayerCoil >>>> for  >>>> SAFE_DELETE(m_pDeadEffect[i]); [%d / %d]�� �폜���� \n" , i, PARTICLS_NUM  );

};

/////////////////// ////////////////////
//// �p�r       �Fbool PlayerCoil::HitTestWall( OBB Obb )
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�ǂƂ̏Փ˔���
//// ����       �F  OBB Obb           //  : �����Ώۂ�OBB
//// �ߒl       �F�Փ˂��Ă����true
//// �S����     �F�g�n ��m
//// ���l       �F
bool PlayerCoil::HitTestWall( OBB Obb ){
	SPHERE sp;
	sp.m_Center = m_vPos;
	sp.m_Radius = m_OBBRadius;
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( m_pDSPH ) m_pDSPH->UpdateSPHERE(sp);
	if( m_bDebugInvincibleMode ) return false ;
#endif
	//�ʏ�̏Փ˔���
	D3DXVECTOR3 Vec ;
	if(HitTest::SPHERE_OBB(sp,Obb,Vec)){
		//MessageBox( NULL, L"���������I�I", L"�����蔻��", NULL) ;
		return true;
	}
	return false;
}
/////////////////// ////////////////////
//// �֐���     �Fvoid PlayerCoil::Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F  UpdatePacket& i_UpdatePacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���p��     �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update( UpdatePacket& i_UpdatePacket ){

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( GetAsyncKeyState( MYVK_DEBUG_COIL_INVISIBLE ) )		m_bDebugInvincibleMode ? m_bDebugInvincibleMode = false : m_bDebugInvincibleMode = true ;
	if( m_bDebugInvincibleMode )							Debugger::DBGSTR::addStrTop( L"**********  ���G���[�h  **********\n" );
	if( !m_pDSPH ){
		SPHERE sp;
		sp.m_Center = g_vMax ;
		sp.m_Radius = 1.0f ;
		m_pDSPH = new DrawSphere( i_UpdatePacket.pD3DDevice, sp );
	}
	if( GetAsyncKeyState( MYVK_DEBUG_INVISIBLEGAUGE_MAX ) ){
		m_pSuperGage->Recovery(-1) ;
	}

#endif
#if defined(CF_DEBUG_JUMPTOOTHGOAL)
	if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RULER ) ){
		GoalObject*		pc		= (GoalObject*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CLEARAREA );
		if( pc )		m_vPos	= pc->GetPos();
		m_vPos.y -= 3.0f;
	}
#endif
	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;

	if( !m_pCursor )			m_pCursor				=        ( MouseCursor* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CURSOR ) ; 
	if( !m_pCamera )			m_pCamera				=             ( Camera* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ; 
	if( !m_pMagneticumObject )	m_pMagneticumObject		=  ( StaticMagnetField* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_STATIC_MAGNET ) ; 
	if( !m_pReStart )			m_pReStart				=		 ( StartSprite* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_START  ) ;
	if( !m_pSuperGage )			m_pSuperGage			=          ( SuperGage* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_UI_SUPERGAUGE );
	if( !m_pContinueBehavior )	m_pContinueBehavior		=	( ContinueBehavior* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_BEHAVIOR_CONTINUE );

	if( m_pPlayer ){
		//�f�o�b�N�p-----------------------------------------------------------
		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		if( m_enumCoilState != COIL_STATE_STICK ){
			m_bModeChangeChar		= false;
			m_bReDrawing_ChangeChar	= true;
			m_bStandby				= false;
		}

		//��Ԃ��Ƃ̏���
		switch(m_enumCoilState){
			//�X�^�[�g
			case COIL_STATE_START:
				Update_StateStart(i_UpdatePacket);
				break;
			//�ړ�
			case COIL_STATE_MOVE:
				Update_StateMove(i_UpdatePacket);
				break;
			//���E���S�ɋz��
			case COIL_STATE_STICK:
				if( m_bReDrawing_ChangeChar ){
					m_bModeChangeChar		= true;
					m_bReDrawing_ChangeChar	= false;
					m_pModeChangeChar->setStart();
				}
				Update_StateStick(i_UpdatePacket);
				break;
			//���S
			case COIL_STATE_DEAD:
				Update_StateDead(i_UpdatePacket);
				this->CreateEffect(i_UpdatePacket);
				break;
			//�R���e�B�j���[
			case COIL_STATE_CONTINUE:
				Update_StateContinue(i_UpdatePacket);
				break;
			//�N���A
			case COIL_STATE_STOP:
				Update_StateStop(i_UpdatePacket);
				break;
			default:
				break;
		}

		//�Q�[�W���ő�ɂȂ�����COIL_STATE_SUPER_READY��
		if(m_pSuperGage && m_pSuperGage->getRate() <= 0.0f && m_enumCoilStateSuper == COIL_STATE_SUPER_CHARGE && m_enumCoilState != COIL_STATE_CLEAR){
			m_enumCoilStateSuper = COIL_STATE_SUPER_READY;
			i_UpdatePacket.SearchSoundAndPlay(RCTEXT_SOUND_SE_SUPER_FULL);
		}
		//COIL_STATE_SUPER_READY�̊Ԃ�Line���X�V
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY)Update_Line();
		//�z�C�[���N���b�N�Ŗ��G��Ԃ�
		if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_READY && Cursor2D::getMButtonState())m_enumCoilStateSuper = COIL_STATE_SUPER_CHANGING;
		//���G���
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING)SuperMode(i_UpdatePacket);

		//�f�o�b�N�p-----------------------------------------------------------
		//Debugger::DBGSTR::addStr( L"�p�x = %f\n",m_fMoveDir);
		//Debugger::DBGSTR::addStr( L"��� = %d\n",m_enumCoilState);
		//-----------------------------------------------------------------------

		m_Material = MagneticObject::getMaterial() ;
		//�}�g���N�X�v�Z
		D3DXMATRIX mPos, mPos2, mScale, mRotZ, mRotX;
		D3DXVECTOR3 vCartesian  = ConvertToCartesianCoordinates(1.6f*(m_vScale.x/m_vOriginScale.x), m_fMoveDir);
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;									//����Pos
		D3DXMatrixTranslation( &mPos2 , m_vPos.x + vCartesian.x , m_vPos.y + vCartesian.y , m_vPos.z ) ;	//����Pos
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - COIL_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos2 ;
		m_pSphere->CalcMatrix(mPos,mScale,mRotZ);
		m_pSphere->SetMaterial(m_Material );

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromID( i_UpdatePacket.pVec , OBJID_3D_USERMAGNET );
	}
	//�J�������W�ݒ�
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
	//���U�G�t�F�N�g***********************************
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
	//ModeChange�̍��W�w��
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
//// �֐���     �Fvoid	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S��       �F������
//// �ҏW       �F�g�n ��m�i�摜�̔z�u�j
//// ���l       �F
////            �F
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
//// �֐���     �Fvoid PlayerCoil::Update_StateStart()
//// �J�e�S��   �F
//// �p�r       �FSTATE_START���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateStart(UpdatePacket& i_UpdatePacket){

	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//�}�E�X���W�v�Z
	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//�p�x�̍X�V
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//�N���b�N���A��������MOVE��ԂɕύX
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
//// �֐���     �FPlayerCoil::Update_StateMove()
//// �J�e�S��   �F
//// �p�r       �FSTATE_MOVE���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateMove(UpdatePacket& i_UpdatePacket){
	//�v���C���[���E�Ǝ��@�̔���
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance && m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING){
		MagneticDecision(m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	if( m_pMagneticumObject && m_enumCoilStateSuper != COIL_STATE_SUPER_MOVE && m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING )
		m_pMagneticumObject->HitTest();
	//	//�ݒu���E�Ǝ��@�̔���
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
	//���x�w��
	if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE) m_fMovdSpeed = COIL_SPEED_SUPER;
	else											  m_fMovdSpeed = COIL_SPEED;

	if( m_enumCoilStateSuper != COIL_STATE_SUPER_CHANGING ){
		//�w������֎w�苗���ړ�
		ArcMove( m_vMove , m_fMovdSpeed + m_fAcceleration, m_fMoveDir);
		if(m_fAcceleration >= 0.0f){
			m_fAcceleration -= COIL_ACCELERATION_DECREASE;
			if(m_fAcceleration <= 0.0f)m_fAcceleration = 0.0f;
		}
		if(m_fAcceleration < 0.0f){
			m_fAcceleration += COIL_ACCELERATION_DECREASE;
			if(m_fAcceleration >= 0.0f)m_fAcceleration = 0.0f;
		}
		//�ړ��������Z
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
//// �֐���     �Fvoid Update_StateStick()
//// �J�e�S��   �F
//// �p�r       �FSTATE_STICK���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
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
//// �֐���     �FPlayerCoil::SuperMode()
//// �J�e�S��   �F
//// �p�r       �FSTATE_SUPER���̓���
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// �ҏW       �F���� �O
//// ���l       �F
////            �F
////
void PlayerCoil::SuperMode( UpdatePacket& i_UpdatePacket ){	
	
	float			fScalePercentage;
	D3DXMATRIX mPos, mScale, mRotZ;
	//���G���[�h�ɕϊ����I���܂ł̓Q�[�W������Ȃ�
	switch(m_enumCoilStateSuper){
		case COIL_STATE_SUPER_MOVE:
			if( !m_bSuperSound){
				i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_INVISIBLE  );
				m_bSuperSound = true ;
			}
			if(m_enumCoilState == COIL_STATE_MOVE)
				m_fSuperTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();

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
			m_fSuperTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime()*0.7f;
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

	//�F�̓_��
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

	//�Q�[�W����
	if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE){
		if( ( m_fSuperTimeAccumulator += (float)i_UpdatePacket.pTime->getElapsedTime()) < COIL_SUPER_MODE_TIME ){
			float fOneSecondSub = (1.0f / (float)COIL_SUPER_MODE_TIME);
			float fFrameSub     = fOneSecondSub * (float)i_UpdatePacket.pTime->getElapsedTime();
			m_pSuperGage->Consume( -fFrameSub );	
		}
	}else{
		m_fSuperTimeAccumulator = 0 ;	
	}

	//���G���[�h�I��
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
//// �֐���     �Fvoid PlayerCoil::Update_StateDead()
//// �J�e�S��   �F
//// �p�r       �FSTATE_DEAD���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
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
//// �֐���     �Fvoid PlayerCoil::Update_StateContinue()
//// �J�e�S��   �F
//// �p�r       �FSTATE_START���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateContinue(UpdatePacket& i_UpdatePacket){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;

	//�}�E�X���W�v�Z
	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//�p�x�̍X�V
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//�N���b�N���A��������MOVE��ԂɕύX
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
//// �֐���     �Fvoid PlayerCoil::Update_StateStop()
//// �J�e�S��   �F
//// �p�r       �FSTATE_STOP���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F������
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateStop(UpdatePacket& i_UpdatePacket){
	D3DXVECTOR3 vPlayer		= g_vZero	;
	float		fTargetDir	= NULL		;

	if( m_pCursor ) vPlayer = m_pCursor->get3DPos();


	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//�p�x�̍X�V
	m_fMoveDir = fTargetDir;

	m_vScale += COIL_SCALE_ADD_VALUE_STOP;
	if( m_vScale.x >= m_vOriginScale.x && m_vScale.y >= m_vOriginScale.y ){
		m_vScale = m_vOriginScale;
		m_bReadyToStart = true;
	}
};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void PlayerCoil::Draw(DrawPacket& i_DrawPacket){

	//�e�N�X�`�����Ȃ��ꍇ
	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
	//�R�������b�V����Draw()���Ă�
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
	//���C���p�Ƀ��[���h���W�Ē�`
	D3DXMATRIX	mRot, mPos;
	D3DXMatrixIdentity( &mRot );
	D3DXMatrixTranslation( &mPos, m_vPos.x, m_vPos.y, m_vPos.z );
	m_Matrix	= mRot*mPos;
	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);

	if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY && m_enumCoilState != COIL_STATE_DEAD && m_enumCoilState != COIL_STATE_CLEAR){
		m_pLine1->draw(i_DrawPacket.pD3DDevice);
		m_pLine2->draw(i_DrawPacket.pD3DDevice);
		m_pLine3->draw(i_DrawPacket.pD3DDevice);
		m_pLine4->draw(i_DrawPacket.pD3DDevice);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

	//���U
	if( m_pDeadEffect && m_enumCoilState == COIL_STATE_DEAD )
		m_pDeadEffect->Draw( i_DrawPacket );

	if( m_bModeChangeChar )
		m_pModeChangeChar->Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// �֐���     �Ffloat PlayerCoil::MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
//// �J�e�S��   �F�֐�
//// �p�r       �F���@�ɑ΂���z���񂹁A�����̏���
//// ����       �Ffloat i_fCoilDir            //���@�̊p�x
////�@�@�@�@�@�@�FD3DXVECTOR3& i_vMagnetPos   //���E�̈ʒu
////�@�@�@�@�@�@�Fbool i_bMagnetPole_Field	// ���E�̋�
//// �ߒl       �F
//// �S��       �F�{�����V
//// ���l       �F
////�@�@�@�@�@�@�F
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
//// �p�r       �Fbool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
//// �J�e�S��   �F�֐�
//// �p�r       �F�����𔻒�
//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
////�@�@�@�@�@�@�Fbool�@�@�@�@IsPlayer�@�@�@�@�@//���肪�v���C���[���ǂ���
//// �ߒl       �Ftrue , false
//// �S����     �F�{�����V
//// ���l       �F
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
//// �֐���     �FSuperGage::Update_Line()
//// �J�e�S��   �F�֐�
//// �p�r       �FLine�̍X�V
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
void PlayerCoil::Update_Line(){

	D3DXMATRIX		mLineScale, mLinePos;
	D3DXVECTOR3		vLineScale = D3DXVECTOR3(1.0f,1.0f,0.0f),
		vBaseLinePos = D3DXVECTOR3(-m_pLine1->getEndPos().x,-m_pLine2->getEndPos().y,0.0f),
					vLinePos;
	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );
	
	//���㕔
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - m_fLineMovingDistance, 
							  vBaseLinePos.y + m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine1->setMatrix( mLineScale * mLinePos );
	//�E�㕔
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + m_fLineMovingDistance,
							  vBaseLinePos.y + m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine2->setMatrix( mLineScale * mLinePos );
	//������
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + m_fLineMovingDistance,
							  vBaseLinePos.y - m_fLineMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLine3->setMatrix( mLineScale * mLinePos );
	//�E����
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
 Factory_Coil ��`��
****************************************************************************/
/**************************************************************************
 Factory_Coil::Factory_Coil(
	FactoryPacket* fpac		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Coil::Factory_Coil( FactoryPacket* fpac, DWORD dwResumptionCheckPoint, D3DXVECTOR3* vStartPos  ){
	try{

		D3DXVECTOR3 vScale( 1.0f, 1.0f, 1.0f );
		D3DXVECTOR3 vPos( 25.0f, 5.0f,0.0f );
 		D3DCOLORVALUE CoilDiffuse = {1.0f,1.0f,1.0f,0.0f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {1.0f,1.0f,1.0f,0.0f};


		CheckPoint*									pc		= (CheckPoint*)SearchObjectFromID( fpac->m_pVec, OBJID_SYS_CHECKPOINT );
		if( vStartPos )								vPos	= *vStartPos;
		else if( dwResumptionCheckPoint && pc )		vPos	= pc->getThisPosition(dwResumptionCheckPoint);
		//LPDIRECT3DTEXTURE9 pTex;
		//0(fpac->pD3DDevice,L"DeadPerticul.png",&pTex);
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr,
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"SuperField.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadPerticul.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CONTINUE4.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"GAME_END3.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"dead6.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"REALLY4.png" ),
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"YESorNO5.png" ),
				0.0f,0.7f,1.0f,1.0f,vScale,D3DXVECTOR3(90.0f,0.0f,0.0f),vPos,
				CoilDiffuse,CoilSpecular,CoilAmbient,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"DeadPerticul.png" )
				)
		);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Player::~Factory_Player();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Coil::~Factory_Coil(){

}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
