////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
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
 ProvisionalPlayer ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
ProvisionalPlayer::ProvisionalPlayer(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
	D3DXVECTOR3 &vScale,						//	: �L�k
	D3DXVECTOR3 &vRot,							//	: ��]
	D3DXVECTOR3 &vPos,							//	: �ʒu
	RECT* pRect,								//	: �`��͈�
	Color color ,								//	: �F
	wiz::OBJID id 								//	: ID
)
	:MagneticumObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, color, id )


{
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
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
 PlayerCoil ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPlayerCoil( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
PlayerCoil::PlayerCoil(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pCoreTexture,			//	: �R�A������Texture
	LPDIRECT3DTEXTURE9 pDirTexture,				//	: ������\���O�p�̂Ă������[
	D3DXVECTOR3 &vScale,						//	: �L�k
	D3DXVECTOR3 &vRot,							//	: ��]
	D3DXVECTOR3 &vPos,							//	: �ʒu
	D3DXVECTOR3 &vDirOffset,					//	: ������\���O�p�̕`��I�t�Z�b�g
	RECT* pCoreRect,							//	: �`��͈�
	RECT* pDirRect,								//	: �`��͈�
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
//// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
void PlayerCoil::Update( UpdatePacket& i_UpdatePacket ){

	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;

	if( m_pPlayer ){


		//	: �K�v�ȕϐ��̐錾
		// �ړ��̕��� + ����
		D3DXVECTOR3 vMove = D3DXVECTOR3( 1.0f, 0.0f, 0.0f) ;
		// ���[�U�[���E�̍��W
		D3DXVECTOR3 pPos  = this->m_pPlayer->getPos();

		// �R�C���ƃ��[�U�[���E�̋������Z�o
		float Lng  = TwoPointToBassLength( pPos, m_vPos ) ;
		// �e�X�g�p
		float Lng2 = VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );

		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;

		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", MGPRM_MAGNETICUM_QUAD);

		if( Lng <= MGPRM_MAGNETICUM_QUAD ){

			//	: �p�x�̎Z�o
			m_fMoveDir = TwoPoint2Degree( m_vPos, pPos );

			//	: ��������
			//	: �������E���Ɣ�������
			if( m_pPlayer->getMagnetPole() != this->getMagnetPole() ){
				TurnAngle( &m_fMoveDir , -180.0f ) ;
			}
		}

		Debugger::DBGSTR::addStr( L"�p�x = %f",m_fMoveDir);

		//	: �w������֎w�苗���ړ�
		ArcMove( vMove , m_fMovdSpeed, m_fMoveDir);

		this->m_vPos += vMove ;

		WallObject* pWall = (WallObject*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_2D_WALL ) ;
		if( pWall && pWall->HitTest2DRectAndCircle( m_vPos, 32.0f) ){
			m_vPos = D3DXVECTOR3( 300, 300, 0 );
		}
		if( m_vPos.x <= 0 || m_vPos.x >= 800 || m_vPos.y <= 0 || m_vPos.y >= 500 ){
			m_vPos = D3DXVECTOR3( 100, 500, 0 );
		}
		//	: �ړ��̊m��
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
	if( m_pDirParts ) m_pDirParts->Draw( i_DrawPacket ) ;
	else ;

	MagneticumObject::Draw( i_DrawPacket );
}


/**************************************************************************
 Factory_Player ��`��
****************************************************************************/
/**************************************************************************
 Factory_Player::Factory_Player(
	FactoryPacket* fpac		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
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
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Player::~Factory_Player();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Player::~Factory_Player(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
