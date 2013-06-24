////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�g�n ��m
//	����			�F�{�� ���V
//	�����ް��Ɣ��l	�F�v���C���[���U�����镨��
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
#include "Factory_Cursor.h"


namespace wiz{
namespace bomberobject{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
extern class WallObject ;
const	float	GAUGE_VANISHRATE	= 0.0f;
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
	FactoryPacket*	fpac,								//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
	LPDIRECT3DTEXTURE9 pTexture2,						//	: �e�N�X�`���[�Q
	D3DXVECTOR3		   &vScale,							//	: �L�k
	D3DXQUATERNION	   &vRot,							//	: ��]
	D3DXVECTOR3	       &vPos,							//	: �ʒu
	wiz::OBJID id 										//	: ID
)
:MagnetField( fpac->pD3DDevice, id )
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
//// �֐���     �F~ProvisionalPlayer3D();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
ProvisionalPlayer3D::~ProvisionalPlayer3D(){
	m_Camera		= NULL ;
	m_pPlayerCoil	= NULL;
	m_pMGage_N		= NULL;
	m_pMGage_S		= NULL;
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
	if(m_Camera == NULL){
		m_Camera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		//m_Camera && (m_MovePosY	= m_Camera->getPosY());
	}
	if( !m_pPlayerCoil	)	m_pPlayerCoil	= (     PlayerCoil* )SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL          );
	if( !m_pMGage_N		)	m_pMGage_N		= ( MagneticGage_N* )SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_MAGNETGAUGE_N );
	if( !m_pMGage_S		)	m_pMGage_S		= ( MagneticGage_S* )SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_MAGNETGAUGE_S );
	if( !m_pCursor		)	m_pCursor		= (    MouseCursor* )SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CURSOR       );

	RECT rc;
	::GetClientRect(wiz::DxDevice::m_hWnd, &rc);
	
	//Suction	: �z��
	//Rebound	: ����
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

						wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
						D3DXVECTOR3 vMove = g_vZero ;
						m_vPos = m_pCursor->get3DPos();

						if(Suction){
							m_MagneticField.setPole(POLE_N);
						}
						else if(Rebound){
							m_MagneticField.setPole(POLE_S);
						}

						if( Suction )
							setPoleN() ;
						if( Rebound )
							setPoleS() ;
					}
				}

				/********************
				L : �R�C���̋ɂƔ��΂̃Q�[�W��Consume
				R : �R�C���̋ɂƓ����Q�[�W��Consume
				********************/

				if( (Suction && m_pMGage_N->getRate() > GAUGE_VANISHRATE) || (Rebound && m_pMGage_S->getRate() > GAUGE_VANISHRATE) ){	
	
					if( Suction  && !Rebound && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !Suction && Rebound  && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !Suction && Rebound  )m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
					if( Suction  && !Rebound )m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);

					//	: �}�E�X�̃t���O
					//Cursor2D::getLButtonState() = false ;
					//Cursor2D::getRButtonState() = false ;
					m_bDrawing	= true;
				}
			}
			else{
				if( m_pPlayerCoil->getState() == COIL_STATE_STICK && (!m_pPlayerCoil->getReadyToStart()) ){
					m_bDrawing	= true;
				}
				else{
					m_bDrawing	= false;					
				}
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
		if( m_pPlayerCoil->getState() == COIL_STATE_STICK ){
			m_bDrawing	= true;
			if( m_pMGage_N && m_pMGage_S && m_bChangeFirst){
				//Rate�̌���************************************
				float	fRate	= 0.0f;
				fRate	= m_pMGage_N->getRate();
				m_pMGage_N->setRate( m_pMGage_S->getRate() );
				m_pMGage_S->setRate( fRate );
				//***********************************************
				//�ʒu�̓���ւ�*******************************
				m_pMGage_N->ChangePos();
				m_pMGage_S->ChangePos();
				//***********************************************
				m_bChangeFirst	= false;
			}
		}else
			m_bDrawing	= false;
	}
	m_bLastMouseLB = Cursor2D::getLButtonState() ;
	m_bLastMouseRB = Cursor2D::getRButtonState() ;


	if(m_pPlayerCoil->getState() == COIL_STATE_CONTINUE){
		if( m_pMGage_N ) m_pMGage_N->ResetGauge();
		if( m_pMGage_S ) m_pMGage_S->ResetGauge();
	}
	MagnetField::Update(i_UpdatePacket);

	//�Q�[�W��3���؂�����A���E��_�ł�����*******************
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

		// 3D�p
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
//end of namespace bomberobject.

}
//end of namespace wiz.
