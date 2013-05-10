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
		m_vPos.x = (float)MousePos.x;
		m_vPos.y = (float)MousePos.y;	

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

	//g_bMouseLB = false ;
	//g_bMouseRB = false ;
};

// 3D�p
/**************************************************************************
 ProvisionalPlayer3D ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
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
ProvisionalPlayer3D::ProvisionalPlayer3D(
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
	D3DXVECTOR3		   &vScale,							//	: �L�k
	D3DXQUATERNION	   &vRot,							//	: ��]
	D3DXVECTOR3	       &vPos,							//	: �ʒu
	wiz::OBJID id 										//	: ID
)
	:MagneticumObject3D( pD3DDevice, pTexture, id )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	setPoleS();

}


/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////			   �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////			   �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////			   �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////               �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F�g�n ��m
//// ���l       �F
void ProvisionalPlayer3D::Draw(DrawPacket& i_DrawPacket)
{
	//multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_Target.begin();
	//while(it != m_ItemMap_Target.end()){
		//�e�N�X�`��������ꍇ
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &/*it->second->*/m_Matrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &/*it->second->*/m_Matrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		//++it;
	//}
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
void ProvisionalPlayer3D::Update( UpdatePacket& i_UpdatePacket ){
	//m_ItemMap_Target.clear() ;
	//multimap<float, Magnet3DItem*>::iterator it2 = m_ItemMap_Target.begin() ;
	//while(it2 != m_ItemMap_Target.end()){
		if( g_bMouseLB || g_bMouseRB ){
			wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
			D3DXVECTOR3 vMove = g_vZero ;
			Point MousePos ;
			GetCursorPos( &MousePos );
			ScreenToClient( g_hWnd , &MousePos);
			
			//float m_vStage ;
			/*it2->second->*/m_vPos.x = (float)MousePos.x / 20.0f - 0.5f ;
			m_vPos.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - 88.0f ) / 20.0f - 0.5f ;
			///*it2->second->*/m_vPos.x = (float)MousePos.x ;
			//m_vStage = ( STANDARD_WINDOW_HEIGHT - 88.0f ) -(float)MousePos.y + 88.0f ;
			//m_vPos.y = -( m_vStage - (float)MousePos.y ) ;
			//m_vPos.y + 88.0f = ( STANDARD_WINDOW_HEIGHT - 88.0f ) -(float)MousePos.y - 88.0f ;
			//*it2->second->*/m_vPos.y = ((512.0f -  (float)MousePos.y ) / 12.5f ) ;
			///*it2->second->*/m_vPos.y = ((STANDARD_WINDOW_HEIGHT -  (float)MousePos.y ) / 12.5f ) ;
			//m_vPos.y = m_vPos.y - 30.0f ;

			if( g_bMouseLB )
				setPoleN() ;
			if( g_bMouseRB )
				setPoleS() ;

			//this->m_vPos += vMove * 15.0f ;

			/*
			D3DXMATRIX mPos , mScale ;

			D3DXMatrixTranslation( &mPos , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
			//D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
			D3DXMatrixScaling(&mScale,
				it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
			it2->second->m_Matrix = mScale * mPos ;
			*/

					//�g��k��
			D3DXMATRIX mScale;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale,
				/*it2->second->*/m_vScale.x, /*it2->second->*/m_vScale.y,/*it2->second->*/m_vScale.z);
			//��]
			D3DXMATRIX mRot;
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixRotationQuaternion(&mRot,/*it2->second->*/&m_vRot);
			//�ړ��p
			D3DXMATRIX mMove;
			D3DXMatrixIdentity(&mMove);
			D3DXMatrixTranslation(&mMove,
				/*it2->second->*/m_vPos.x, /*it2->second->*/m_vPos.y,/*it2->second->*/m_vPos.z);
			//�~�b�N�X�s��
			/*it2->second->*/m_Matrix = mScale * mRot * mMove;
			//�}�e�B���A���ݒ�
			m_Material = /*it2->second->*/m_Material;

		//}

		g_bMouseLB = false ;
		g_bMouseRB = false ;

		//++it2 ;
	}
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
		//m_fMovdSpeed = 0;
		//ConvertToCartesianCoordinates���g���Ď��@�̃f�J���g���W���o��
		//ThreePoint2Radian�Ńf�J���g���W(1)�A���@�̈ʒu(2)�A���E�̈ʒu(3)�����Ċp�x���o��

		//	: �K�v�ȕϐ��̐錾
		// �ړ��̕��� + ����
		D3DXVECTOR3 vMove = D3DXVECTOR3( 1.0f, 0.0f, 0.0f) ;
		// ���[�U�[���E�̍��W
		D3DXVECTOR3 pPos  = this->m_pPlayer->getPos();

		// �R�C���ƃ��[�U�[���E�̋������Z�o
		float Lng  = (float)TwoPointToBassLength( pPos, m_vPos ) ;
		// �e�X�g�p
		float Lng2 = (float)VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );

		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;

		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", MGPRM_MAGNETICUM_QUAD);

		if( Lng <= MGPRM_MAGNETICUM_QUAD ){
			//���@�Ǝ��E�̊p�x
			float fTargetDir = TwoPoint2Degree( pPos , m_vPos );
			//fTargetDir = 360.0f - fTargetDir;
			Debugger::DBGSTR::addStr( L"fTargetDir : %f\n", fTargetDir);
			//���@�̃f�J���g���W
			D3DXVECTOR3 vDescartes = ConvertToCartesianCoordinates(vMove.x,m_fMoveDir);
			Debugger::DBGSTR::addStr( L"vDescartes : %f\n", vDescartes.x);

			float	fReverse = 0.0f;
			if(m_fMoveDir > 180.0f){
				fReverse = m_fMoveDir - 180.0f;
			}
			else{
				fReverse = m_fMoveDir + 180.0f;
			}

			if(m_pPlayer->getMagnetPole() != this->getMagnetPole()){

				if(m_fMoveDir < fTargetDir){
					if(fTargetDir - m_fMoveDir <= 180.0f){
						m_fMoveDir += 1.0f;
						m_fMoveDir = float(int(m_fMoveDir) % 360);						
					}
					else{
						m_fMoveDir -= 1.0f;
						if(m_fMoveDir < 0.0f){
							m_fMoveDir += 360.0f;
						}
					}
				}
				else if(m_fMoveDir > fTargetDir){
					if(m_fMoveDir - fTargetDir <= 180.0f){
						m_fMoveDir -= 1.0f;
						if(m_fMoveDir < 0.0f){
							m_fMoveDir += 360.0f;
						}
					}
					else{
						m_fMoveDir += 1.0f;
						m_fMoveDir = float(int(m_fMoveDir) % 360);												
					}
				}
			}
			else{
				if(fReverse != fTargetDir){
					if(m_fMoveDir < fTargetDir){
						if(fTargetDir - m_fMoveDir <= 180.0f){
							m_fMoveDir -= 1.0f;
							if(m_fMoveDir < 0.0f){
								m_fMoveDir += 360.0f;
							}
						}
						else{
							m_fMoveDir += 1.0f;
							m_fMoveDir = float(int(m_fMoveDir) % 360);						
						}
					}
					else if(m_fMoveDir > fTargetDir){
						if(m_fMoveDir - fTargetDir <= 180.0f){
							m_fMoveDir += 1.0f;
							m_fMoveDir = float(int(m_fMoveDir) % 360);												
						}
						else{
							m_fMoveDir -= 1.0f;
							if(m_fMoveDir < 0.0f){
								m_fMoveDir += 360.0f;
							}
						}
					}
				}
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

		D3DXVECTOR3 vScale( 1.0f, 1.0f, 1.0f );
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

		// 3D�p
		D3DXVECTOR3 vScale2( 10.0f, 10.0f, 10.0f );
		fpac->m_pVec->push_back(
			new ProvisionalPlayer3D(
				fpac->pD3DDevice,
				//NULL,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleP.png" ),
				vScale,
				D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
		);

		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleC.png" ),
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CoilDir.png" ),
				vScale,
				g_vZero,
				D3DXVECTOR3(100.0f,400.0f,0.0f),
				D3DXVECTOR3( -16.5f, -26.0f,0.0f),
				NULL,
				NULL
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
