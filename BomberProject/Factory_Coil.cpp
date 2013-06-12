////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Coil.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O �g�n��m(�ҏW) �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
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
	//���U�G�t�F�N�g�̃|�C���^
	for( int i = 0; i < PARTICLS_NUM; i++ )
		m_pDeadEffect[i]	= NULL;
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
		//�f�o�b�N�p-----------------------------------------------------------
		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		//��Ԃ��Ƃ̏���
		switch(m_enumCoilState){
			//�X�^�[�g
			case COIL_STATE_START:
				Update_StateStart();
				break;
			//�ړ�
			case COIL_STATE_MOVE:
				Update_StateMove();
				break;
			//���E���S�ɋz��
			case COIL_STATE_STICK:
				Update_StateStick();
				break;
			//���S
			case COIL_STATE_DEAD:
				Update_StateDead();
				if( m_pDeadEffect[0] == NULL )
					CreateEffect(i_UpdatePacket);
				break;
			//�R���e�B�j���[
			case COIL_STATE_CONTINUE:
				Update_StateContinue();
				break;
			//�N���A
			case COIL_STATE_STOP:
				Update_StateStop();
				break;
			default:
				break;
		}
		if(m_bIsSuperMode){
			//���G���
			SuperMode(i_UpdatePacket);
		}

		//�f�o�b�N�p-----------------------------------------------------------
		Debugger::DBGSTR::addStr( L"�p�x = %f\n",m_fMoveDir);
		Debugger::DBGSTR::addStr( L"��� = %d\n",m_enumCoilState);
		//-----------------------------------------------------------------------

		//�}�g���N�X�v�Z
		D3DXMATRIX mPos, mPos2, mScale, mRotZ, mRotX;
		D3DXVECTOR3 vCartesian  = ConvertToCartesianCoordinates(1.6f*(m_vScale.x/m_vOriginScale.x), m_fMoveDir);
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;		//����Pos
		D3DXMatrixTranslation( &mPos2 , m_vPos.x + vCartesian.x , m_vPos.y + vCartesian.y , m_vPos.z ) ;		//����Pos
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - COIL_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos2 ;
		m_pSphere->CalcMatrix(mPos,mScale,mRotZ);
		m_pSphere->SetMaterial( m_Material );

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer3D) );
	}
	//�J�������W�ݒ�
	if( m_pCamera ){
		m_pCamera->setPosY( m_vPos.y );
	}
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( GetAsyncKeyState( MYVK_DEBUG_COIL_INVISIBLE ) )
		m_bDebugInvincibleMode ? m_bDebugInvincibleMode = false : m_bDebugInvincibleMode = true ;
	if( m_bDebugInvincibleMode )
	Debugger::DBGSTR::addStrTop( L"**********  ���G���[�h  **********\n" );
#endif 

	//���U�G�t�F�N�g***********************************
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
	//���S****************************************
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
//// ���l       �F
////            �F
////
void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket ){

	//���U�G�t�F�N�g�̍쐬
	for( int i = 0; i < PARTICLS_NUM; i++ ){
		m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.pD3DDevice, m_vPos,
					float((360/PARTICLS_NUM) * i), m_pDeadTex );
	}

	float	wide	= BASE_CLIENT_WIDTH/2;
	float	height	= BASE_CLIENT_HEIGHT/2;

	m_pDeadChar	= new Dead( i_UpdatePacket.pD3DDevice, m_pDeadCharTex, D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),g_vZero,
					D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),NULL,g_vZero,g_vZero);

	//Continue,Title���S�̍쐬
	m_pSelect	= new Continue( i_UpdatePacket.pD3DDevice, m_pContinueTex, true, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,D3DXVECTOR3( wide-128.0f,height-100.0f,0.0f ),
								Rect( 0,0,256,64 ), g_vZero, g_vZero );
	m_pSelect2	= new Continue( i_UpdatePacket.pD3DDevice, m_pTitleTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,D3DXVECTOR3( wide-64.0f,height,0.0f ),
								Rect( 0,0,128,64 ), g_vZero, g_vZero );

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
void PlayerCoil::Update_StateStart(){
	//if( m_pSound == NULL )
	//	m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));

	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//�}�E�X���W�v�Z
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	vPlayer.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
	vPlayer.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_pPlayer->getMoveY() ) ;
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//�p�x�̍X�V
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//�N���b�N���A��������MOVE��ԂɕύX
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
//// �֐���     �FPlayerCoil::Update_StateMove()
//// �J�e�S��   �F
//// �p�r       �FSTATE_MOVE���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateMove(){
	//�v���C���[���E�Ǝ��@�̔���
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance ){
		m_fMoveDir = MagneticDecision(m_fMoveDir,m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	if( m_pMagneticumObject )
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
	if(m_bIsSuperMode) m_fMovdSpeed = COIL_SPEED_SUPER;
	else			   m_fMovdSpeed = COIL_SPEED;

	if( (m_bIsSuperMode && m_bReadyToSuper) || (!m_bIsSuperMode && !m_bReadyToSuper) ){
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
//// �֐���     �FPlayerCoil::SuperMode()
//// �J�e�S��   �F
//// �p�r       �FSTATE_SUPER���̓���
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////			  �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////			  �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////			  �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////              �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////			  �F
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
	//���G���[�h�ɕϊ����I���܂ł̓Q�[�W������Ȃ�
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

	//�F�̓_��
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

	//���G���[�h�I��
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
//// �֐���     �Fvoid PlayerCoil::Update_StateDead()
//// �J�e�S��   �F
//// �p�r       �FSTATE_DEAD���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
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
//// �֐���     �Fvoid PlayerCoil::Update_StateContinue()
//// �J�e�S��   �F
//// �p�r       �FSTATE_START���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateContinue(){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//�}�E�X���W�v�Z
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	vPlayer.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
	vPlayer.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_pPlayer->getMoveY() ) ;
	fTargetDir = TwoPoint2Degree( vPlayer , m_vPos );
	//�p�x�̍X�V
	m_fMoveDir = fTargetDir;
	if(m_bReadyToStart){
		//�N���b�N���A��������MOVE��ԂɕύX
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
//// �֐���     �Fvoid PlayerCoil::Update_StateStop()
//// �J�e�S��   �F
//// �p�r       �FSTATE_STOP���̓���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F������
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateStop(){
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	//�}�E�X���W�v�Z
	Point MousePos ;
	GetCursorPos( &MousePos ) ;
	ScreenToClient( g_hWnd , &MousePos) ;
	vPlayer.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
	vPlayer.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_pCamera->getPosY() - m_pPlayer->getMoveY() ) ;
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
	if(m_pTexture){
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		m_pSphere->Draw(i_DrawPacket);
		if(m_bIsSuperMode)m_pSuperField->Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		m_pSphere->Draw(i_DrawPacket);
		if(m_bIsSuperMode)m_pSuperField->Draw(i_DrawPacket);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

	//���U
	if( m_pDeadEffect[0] != NULL ){
		for( int i = 0; i < PARTICLS_NUM; i++ ){
			m_pDeadEffect[i]->Draw( i_DrawPacket );
		}
	}

	if( m_pDeadChar != NULL ){
		m_pDeadChar->Draw(i_DrawPacket);
	}

	if( m_bDrawContinue ){
		//���S
		if( m_pSelect != NULL ){
			m_pSelect->Draw(i_DrawPacket);
		}
		if( m_pSelect2 != NULL ){
			m_pSelect2->Draw(i_DrawPacket);
		}
	}
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
