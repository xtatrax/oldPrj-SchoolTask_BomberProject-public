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
//			class PlayerCoil : public MagneticumObject3D ;
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
//#include "Object.h"
//#include "Scene.h"
//#include "BassItems.h"
//#include "Factory_Wall.h"
//#include "Factory_Cursor.h"
//

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
		wiz::OBJID id
	)
:MagneticumObject3D(	pD3DDevice, NULL, Radius1, Radius2, Lenght,
						vRot, vPos, Diffuse, Specular, Ambient, id )
,m_vPos(				vPos								)
,m_vRot(				vRot								)
,m_vScale(				D3DXVECTOR3( 0.0f, 0.0f, 0.0f)		)
,m_vOriginScale(		vScale								)
,m_OBBRadius(			Radius3								)
,m_vMove(				D3DXVECTOR3( 1.0f, 0.0f, 0.0f)		)
,m_fMoveDir(			COIL_BASSROT						)
,m_fMovdSpeed(			COIL_SPEED							)
,m_fAcceleration(		NULL								)
,m_vStartPos(			vPos								)
,m_bLastMouseRB(		false								)
,m_bLastMouseLB(		false								)
,m_bReadyToStart(		false								)
,m_bReadyContinue(		false								)
,m_bDrawContinue(		false								)
,m_bRestart(			true								)
,m_iDeadCount(			0									)
,m_pSuperGage(			NULL								)
,m_pSuperField(			NULL								)
,m_fTurnAngle(			PLAYER_TURN_ANGLE_Lv1				)
,m_pCursor(				NULL								)
,m_pPlayer(				NULL								)
,m_pMagneticumObject(	NULL								)
,m_pCamera(				NULL								)
,m_pReStart(			NULL								)
,m_pTime(				NULL								)
//�e�N�X�`��*********************************************************************
,m_pDeadTex(			m_pTexMgr->addTexture( pD3DDevice, L"DeadPerticul.png"	))
,m_pContinueTex(		m_pTexMgr->addTexture( pD3DDevice, L"CONTINUE4.png"		))
,m_pTitleTex(			m_pTexMgr->addTexture( pD3DDevice, L"GAME_END3.png"		))
,m_pDeadCharTex(		m_pTexMgr->addTexture( pD3DDevice, L"dead6.png"			))
,m_pDeadCountTex(		m_pTexMgr->addTexture( pD3DDevice, L"Number_Base1.png"	))
,m_pRethinkingTex(		m_pTexMgr->addTexture( pD3DDevice, L"REALLY4.png"		))
,m_pAnswerTex(			m_pTexMgr->addTexture( pD3DDevice, L"YESorNO5.png"		))
,m_pCountCharTex(		m_pTexMgr->addTexture( pD3DDevice, L"dead_count1.png"	))
//**********************************************************************************
,m_iMaxPosY(				0								)
,m_iScratchTime(			0								)
,m_fRecordTime(				0								)
,m_bModeChangeChar(			false							)
,m_bReDrawing_ChangeChar(	true							)
,m_enumCoilState(		COIL_STATE_STOP						)
,m_enumCoilStateSuper(	COIL_STATE_SUPER_CHARGE				)
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
,m_pDSPH(				NULL								)
,m_bDebugInvincibleMode(false								)
#endif
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pSphere	  = new Sphere(pD3DDevice,Radius3,vPos,vRot,Diffuse,Specular,Ambient);
	D3DXVECTOR3	v = COIL_SUPER_MODE_FIELD_SCALE;
	m_pSuperField = new Box(pD3DDevice,v,vPos,vRot,Diffuse,Specular,Ambient,OBJID_3D_BOX,false,
									m_pTexMgr->addTexture( pD3DDevice, L"SuperField.png" ) );
	setPoleN();
	SetBaseRot(vRot);

	m_pModeChangeChar	= new ModeChangeChar( pD3DDevice, m_pTexMgr->addTexture( pD3DDevice, L"CHANGE3.png" ),
														D3DXVECTOR3( 0.25f, 0.25f, 0.0f ), &Rect( 0, 0, 512, 128 ) );
	m_pSelect	= NULL;
	m_pSelect2	= NULL;
	m_pDeadChar	= NULL;
	m_pSphere->ShaderChange( new CookTrance(pD3DDevice) );

	const	D3DXVECTOR3	vDirTop		= D3DXVECTOR3( cosf( D3DXToRadian(-45.0f) ), sinf( D3DXToRadian(-45.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirLeft	= D3DXVECTOR3( cosf( D3DXToRadian(-45.0f) ), sinf( D3DXToRadian(45.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirBottom	= D3DXVECTOR3( cosf( D3DXToRadian(45.0f) ), sinf( D3DXToRadian(45.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirRight	= D3DXVECTOR3( cosf( D3DXToRadian(45.0f) ), sinf( D3DXToRadian(-45.0f) ), 0.0f );
	const	float	fRangeW	= 40.0f;
	const	float	fRangeH	= 40.0f;
	m_pLineTop		= new Line( D3DXVECTOR3( -27.5f, -10.0f, 0.0f ), vDirTop,	 fRangeW, 0xFF00FFFF );
	m_pLineLeft		= new Line( m_pLineTop->getEndPos(),		 vDirLeft,	 fRangeH, 0xFF00FFFF );
	m_pLineBottom	= new Line( D3DXVECTOR3( -27.5f, -10.0f, 0.0f ), vDirBottom,	 fRangeW, 0xFF00FFFF );
	m_pLineRight	= new Line( m_pLineBottom->getEndPos(),		 vDirRight,	 fRangeH, 0xFF00FFFF );


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
	m_pSuperGage			= NULL ;
	m_pSuperField			= NULL ;
	m_pReStart				= NULL ;
	
	SAFE_DELETE(m_pModeChangeChar);
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
	if( GetAsyncKeyState( MYVK_DEBUG_COIL_INVISIBLE ) )		m_bDebugInvincibleMode ? m_bDebugInvincibleMode = false : m_bDebugInvincibleMode = true ;
	if( m_bDebugInvincibleMode )							Debugger::DBGSTR::addStrTop( L"**********  ���G���[�h  **********\n" );
	if( !m_pDSPH ){
		SPHERE sp;
		sp.m_Center = g_vMax ;
		sp.m_Radius = 1.0f ;
		m_pDSPH = new DrawSphere( i_UpdatePacket.pD3DDevice, sp );
	}
	if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RULER ) ){
		CheckPoint*		pc		= (CheckPoint*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CHECKPOINT );
		if( pc )		m_vPos	= pc->getLastPosition();
	}
	if( GetAsyncKeyState( MYVK_DEBUG_INVISIBLEGAUGE_MAX ) ){
		m_pSuperGage->Recovery(-1) ;
	}

#endif

	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;

	if( !m_pCursor )			m_pCursor				=        ( MouseCursor* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CURSOR ) ; 
	if( !m_pCamera )			m_pCamera				=             ( Camera* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ; 
	if( !m_pMagneticumObject )	m_pMagneticumObject		= ( MagneticumObject3D* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_STATIC_MAGNET ) ; 
	if( !m_pReStart )			m_pReStart				=		 ( StartSprite* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_START  ) ;
	if( !m_pSuperGage )			m_pSuperGage			=          ( SuperGage* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_UI_SUPERGAUGE );

	if( m_pPlayer ){
		//�f�o�b�N�p-----------------------------------------------------------
		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		if( m_enumCoilState != COIL_STATE_STICK ){
			m_bModeChangeChar		= false;
			m_bReDrawing_ChangeChar	= true;
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
				if( m_pDeadEffect[0] == NULL )
					CreateEffect(i_UpdatePacket);
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
		if(m_pSuperGage && m_pSuperGage->getRate() <= 0.0f && m_enumCoilStateSuper == COIL_STATE_SUPER_CHARGE){
			m_enumCoilStateSuper = COIL_STATE_SUPER_READY;
			i_UpdatePacket.SearchSoundAndPlay(RCTEXT_SOUND_SE_SUPER_FULL);
		}
		//COIL_STATE_SUPER_READY�̊Ԃ�Line���X�V
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY)Update_Line();
		//�z�C�[���N���b�N�Ŗ��G��Ԃ�
		//if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_READY && Cursor2D::getLButtonState() && Cursor2D::getRButtonState())m_enumCoilStateSuper = COIL_STATE_SUPER_CHANGING;
		if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_READY && Cursor2D::getMButtonState())m_enumCoilStateSuper = COIL_STATE_SUPER_CHANGING;
		//���G���
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING)SuperMode(i_UpdatePacket);

		//�f�o�b�N�p-----------------------------------------------------------
		//Debugger::DBGSTR::addStr( L"�p�x = %f\n",m_fMoveDir);
		//Debugger::DBGSTR::addStr( L"��� = %d\n",m_enumCoilState);
		//-----------------------------------------------------------------------

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
		m_pSphere->SetMaterial( m_Material );

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromID( i_UpdatePacket.pVec , OBJID_3D_USERMAGNET );
	}
	//�J�������W�ݒ�
	if( m_pCamera ){
		m_pCamera->setPosY( m_vPos.y );
	}

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
			if( m_pSelect2 != NULL ){
				if( m_pSelect2->getWhichDraw() ){
					m_pSelect->Update(i_UpdatePacket);
				}
			}
		}
		if( m_pSelect2 != NULL ){
			m_pSelect2->Update(i_UpdatePacket);
		}

		if( m_enumCoilState != COIL_STATE_DEAD )
			m_bDrawContinue	= false;
	}
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
//// �S��       �F������, �g�n ��m�i�摜�̔z�u�j
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

	D3DXVECTOR3	vScale	= D3DXVECTOR3( 0.5f, 0.5f, 0.0f );
	D3DXVECTOR3	vPos	= D3DXVECTOR3( (wide-512.0f*vScale.x), (height-256.0f*vScale.y-100), 0.0f );
	m_pDeadChar	= new Dead( i_UpdatePacket.pD3DDevice, m_pDeadCharTex, m_pDeadCountTex, m_pCountCharTex,
							m_iDeadCount, vScale,g_vZero,vPos,NULL,g_vZero,g_vZero);

	//Yes,No�̍쐬
	m_pSelect	= new Continue( i_UpdatePacket.pD3DDevice, m_pAnswerTex, NULL, NULL, true, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,
								D3DXVECTOR3( wide-128.0f,height-50.0f,0.0f ),Rect( 0,0,256,64 ), g_vZero, g_vZero );
	m_pSelect2	= new Continue( i_UpdatePacket.pD3DDevice, m_pAnswerTex, m_pRethinkingTex, m_pContinueTex, false, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero,
								D3DXVECTOR3( wide-128.0f,height+100.0f,0.0f ),Rect( 256,0,512,64 ), g_vZero, g_vZero );

	if( m_iDeadCount < MAX_DIGHT_SCORE )
		m_iDeadCount++;
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
		m_fMoveDir = MagneticDecision(m_fMoveDir,m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
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
	static float	s_fTimeCount		= 0;
	static int		s_iInterval			= 0;
	static bool		s_bIsColorChange	= false;
	static bool		s_bSound			= false;
	static float	s_fSFieldRotZ		= 0.0f;
	float			fScalePercentage;
	
	D3DXMATRIX mPos, mScale, mRotZ;
	//���G���[�h�ɕϊ����I���܂ł̓Q�[�W������Ȃ�
	switch(m_enumCoilStateSuper){
		case COIL_STATE_SUPER_MOVE:
			if( !s_bSound){
				i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_INVISIBLE  );
				s_bSound = true ;
			}
			if(m_enumCoilState == COIL_STATE_MOVE)
				s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();

			s_fSFieldRotZ += 5.0f;
			if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);
			fScalePercentage = 1.0f - s_fTimeCount / COIL_SUPER_MODE_TIME;
			D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
			D3DXMatrixScaling( &mScale, 
								m_vScale.x * fScalePercentage + m_OBBRadius/4, 
								m_vScale.y * fScalePercentage + m_OBBRadius/4, 
								m_vScale.z);
			D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( s_fSFieldRotZ ) ) ;
			break;

		case COIL_STATE_SUPER_CHANGING:
			s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime()*0.7f;
			s_fSFieldRotZ += 5.0f;
			D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
			if(m_vScale.x >= m_vScale.x * s_fTimeCount && m_vScale.y >= m_vScale.y * s_fTimeCount){
				D3DXMatrixScaling( &mScale, 
									m_vScale.x * s_fTimeCount, 
									m_vScale.y * s_fTimeCount, 
									m_vScale.z);
			}else{
				D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
				m_enumCoilStateSuper = COIL_STATE_SUPER_MOVE;
				s_fTimeCount = 0.0f;
				m_fAcceleration = COIL_ACCELERATION_VALUE;
			}
			D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( s_fSFieldRotZ ) ) ;
			break;

		default:
			break;
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

	//�Q�[�W����
	static float s_fTimeAccumulator = 0 ;
	if(m_enumCoilState == COIL_STATE_MOVE && m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE){
		if( ( s_fTimeAccumulator += i_UpdatePacket.pTime->getElapsedTime()) < COIL_SUPER_MODE_TIME ){
			float fOneSecondSub = (1.0f / (float)COIL_SUPER_MODE_TIME);
			float fFrameSub     = fOneSecondSub * (float)i_UpdatePacket.pTime->getElapsedTime();
			m_pSuperGage->Consume( -fFrameSub );	
		}
	}else{
		s_fTimeAccumulator = 0 ;	
	}

	//���G���[�h�I��
	if(s_fTimeCount >= COIL_SUPER_MODE_TIME){
		m_enumCoilStateSuper = COIL_STATE_SUPER_CHARGE;
		if( s_bSound){
			i_UpdatePacket.SoundStop( RCTEXT_SOUND_SE_INVISIBLE  );
			s_bSound = false ;
		}
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
		//CommonMesh::Draw(i_DrawPacket);
		//((CookTrance*)m_pSphere->getShader())->Draw(i_DrawPacket,m_pMesh,m_pTexture,m_Matrix);
		//m_pSphere->Draw(i_DrawPacket);
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING){
			m_pSuperField->Draw(i_DrawPacket);
		}
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
		//((CookTrance*)m_pSphere->getShader())->Draw(i_DrawPacket,m_pSphere->,m_pTexture,m_Matrix,);
		m_pSphere->Draw(i_DrawPacket);
		if(m_enumCoilStateSuper == COIL_STATE_SUPER_MOVE || m_enumCoilStateSuper == COIL_STATE_SUPER_CHANGING){
			m_pSuperField->Draw(i_DrawPacket);
		}
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif
	if(m_enumCoilStateSuper == COIL_STATE_SUPER_READY){
		//m_pLineTop->draw(i_DrawPacket.pD3DDevice);
		//m_pLineLeft->draw(i_DrawPacket.pD3DDevice);
		//m_pLineBottom->draw(i_DrawPacket.pD3DDevice);
		//m_pLineRight->draw(i_DrawPacket.pD3DDevice);
	}

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
			if( m_pSelect2 != NULL ){
				if( m_pSelect2->getWhichDraw() ){
				m_pSelect->Draw(i_DrawPacket);
				}
			}
		}
		if( m_pSelect2 != NULL ){
			m_pSelect2->Draw(i_DrawPacket);
		}
	}

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
					vLinePos,
					vBaseLinePos;
	Point			BaseLinePos  = T3DPointTo2DPoint(m_pCamera,m_vPos);
	static float	s_fMovingDistance	= 0.0f; 
	
	vBaseLinePos = D3DXVECTOR3((float)BaseLinePos.x,(float)BaseLinePos.y,0.0f);
	//vBaseLinePos.y -= 
	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );

	//���㕔
	vLineScale;
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - s_fMovingDistance, 
							  vBaseLinePos.y - s_fMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineTop->setMatrix( mLineScale * mLinePos );
	//�E�㕔
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + s_fMovingDistance,
							  vBaseLinePos.y - s_fMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineLeft->setMatrix( mLineScale * mLinePos );
	//������
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - s_fMovingDistance,
							  vBaseLinePos.y + s_fMovingDistance,
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineBottom->setMatrix( mLineScale * mLinePos );
	//�E����
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + s_fMovingDistance,
							  vBaseLinePos.y + s_fMovingDistance, 
							  0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineRight->setMatrix( mLineScale * mLinePos );
	
	s_fMovingDistance	+= 0.8f;
	if(s_fMovingDistance >= 6.0f){
		s_fMovingDistance	= 0.0f;
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
