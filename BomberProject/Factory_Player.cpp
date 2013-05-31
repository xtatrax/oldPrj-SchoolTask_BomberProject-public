////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O �g�n��m(�ҏW) �{�����V(�ҏW)
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
#include "Factory_Cursor.h"


namespace wiz{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
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
//ProvisionalPlayer::ProvisionalPlayer(
//	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
//	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
//	D3DXVECTOR3 &vScale,						//	: �L�k
//	D3DXVECTOR3 &vRot,							//	: ��]
//	D3DXVECTOR3 &vPos,							//	: �ʒu
//	RECT* pRect,								//	: �`��͈�
//	Color color ,								//	: �F
//	wiz::OBJID id 								//	: ID
//)
//	:MagneticumObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, color, id )
//{
//}
//
///////////////////// ////////////////////
////// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
////// �J�e�S��   �F
////// �p�r       �F
////// ����       �F
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F
//////            �F
//////
//void ProvisionalPlayer::Update( UpdatePacket& i_UpdatePacket ){
//	if( g_bMouseLB || g_bMouseRB){
//		wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
//		D3DXVECTOR3 vMove = g_vZero ;
//		Point MousePos ;
//		GetCursorPos( &MousePos );
//		ScreenToClient( g_hWnd , &MousePos);
//		m_vPos.x = (float)MousePos.x;
//		m_vPos.y = (float)MousePos.y;	
//
//		if( g_bMouseLB )
//			setPoleN() ;
//		if( g_bMouseRB )
//			setPoleS() ;
//
//		//this->m_vPos += vMove * 15.0f ;
//	
//		D3DXMATRIX mPos , mScale ;
//
//		D3DXMatrixTranslation( &mPos , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
//		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
//		m_mMatrix = mScale * mPos ;
//	}else{
//	
//
//	
//	}
//
//	//g_bMouseLB = false ;
//	//g_bMouseRB = false ;
//};

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
	:MagneticumObject3D( fpac->pD3DDevice, pTexture, id )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_MovePosY(0)
,m_Camera(NULL)
,m_MGage_N(NULL)
,m_MGage_S(NULL)
,m_pSound( NULL )
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bCoilWasStarting(false)
,m_bDrawing(false)
,m_enumCoilState(COIL_STATE_START)
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
	////��]�̏�����
	//D3DXQuaternionRotationYawPitchRoll(&m_Item_Poly.m_vRot,
	//		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
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
	m_Camera = NULL ;
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
	if( m_pSound == NULL )
		m_pSound = (Sound*)SearchObjectFromTypeID(i_DrawPacket.pVec,typeid(Sound));

	if( m_bCoilWasStarting ){
		if( m_bDrawing ){ 
			m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_SETFIELD );
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
			m_pMagneticField->Draw(i_DrawPacket);
			m_pMagneticField2->Draw(i_DrawPacket);
			m_pMagneticField3->Draw(i_DrawPacket);
			m_pMagneticField4->Draw(i_DrawPacket);
		}
	}
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
		m_Camera && (m_MovePosY	= m_Camera->getPosY());
	}
	if( !m_MGage_N )	 m_MGage_N	= (MagneticGage_N*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_N));
	if( !m_MGage_S )	 m_MGage_S	= (MagneticGage_S*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_S));

	RECT rc;
	::GetClientRect(g_hWnd, &rc);

	Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_vPos.x , m_vPos.y, m_vPos.z ) ;

	//if((g_bMouseLB && m_MGage_N->getRect2().right >= MAGNETIC_GAGE_MAX) || (g_bMouseRB && m_MGage_S->getRect2().right >= MAGNETIC_GAGE_MAX)){
	//if(g_bMouseLB)m_MGage_N->Consume(MAGNETIC_GAGE_MAX);
	//if(g_bMouseRB)m_MGage_S->Consume(MAGNETIC_GAGE_MAX);
	//if(g_bMouseLB)m_MGage_N->Consume(1);
	//if(g_bMouseRB)m_MGage_S->Consume(1);
	//m_MGage_N->Recovery(1,MAGNETIC_GAGE_MAX);
	//m_MGage_S->Recovery(1,MAGNETIC_GAGE_MAX);

	if( m_bCoilWasStarting ){
		if( (g_bMouseLB || g_bMouseRB) && !(g_bMouseLB && g_bMouseRB)){ 
			if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){				
				if( !m_bLastMouseLB && !m_bLastMouseRB){
					if(g_bMouseLB)m_MGage_N->Consume(PLAYER_INVOCATION_POINT);
					if(g_bMouseRB)m_MGage_S->Consume(PLAYER_INVOCATION_POINT);
					if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){
						wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
						D3DXVECTOR3 vMove = g_vZero ;
						Point MousePos ;
						GetCursorPos( &MousePos ) ;
						ScreenToClient( g_hWnd , &MousePos) ;

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

						//���E�ɕ`��n�_��n��
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
				if( (g_bMouseLB && m_MGage_N->getRect2().right > 0) || (g_bMouseRB && m_MGage_S->getRect2().right > 0) ){	

					if( g_bMouseLB  && !g_bMouseRB )m_MGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !g_bMouseLB && g_bMouseRB  )m_MGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !g_bMouseLB && g_bMouseRB  )m_MGage_N->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
					if( g_bMouseLB  && !g_bMouseRB )m_MGage_S->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);

					//	: �g��k��
					D3DXMATRIX mScale ;
					D3DXMatrixIdentity( &mScale ) ;
					D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z ) ;
					
					//	: ��]
					D3DXMATRIX mRot ;
					D3DXMatrixIdentity( &mRot ) ;
					D3DXMatrixRotationQuaternion( &mRot, &m_vRot ) ;
					
					//	: �ړ��p
					D3DXMATRIX mMove ;
					D3DXMatrixIdentity( &mMove ) ;
					D3DXMatrixTranslation( &mMove, m_vPos.x, m_vPos.y, m_vPos.z ) ;
					
					//	: �~�b�N�X�s��
					m_Matrix = mScale * mRot * mMove ;

					//	: �}�e�B���A���ݒ�
					m_Material = m_Material ;

					//	: �}�E�X�̃t���O
					//g_bMouseLB = false ;
					//g_bMouseRB = false ;
					m_bDrawing	= true;
				}
			}
			else{
				m_bDrawing	= false;
			}
		}else{
			m_bDrawing	= false;
			m_MGage_N->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
			m_MGage_S->Recovery(PLAYER_RECOVERY_POINT,MAGNETIC_GAGE_MAX);
		}
	}else{
			m_bDrawing	= false;
	}
	m_bLastMouseLB = g_bMouseLB ;
	m_bLastMouseRB = g_bMouseRB ;

	//���E�̃G�t�F�N�g�𓮂���
	m_pMagneticField4->Update(i_UpdatePacket);

	if(m_enumCoilState == COIL_STATE_CONTINUE){
		m_MGage_N->setRect2_Right(MAGNETIC_GAGE_MAX);
		m_MGage_S->setRect2_Right(MAGNETIC_GAGE_MAX);
	}
};

/**************************************************************************
 MagneticField ��`��
****************************************************************************/
/***************************************************************************
�֐���    �FMagneticField(
                   LPDIRECT3DDEVICE9   pD3DDevice,
                   LPDIRECT3DTEXTURE9  pTexture,
                   D3DXVECTOR3         &vScale,
                   D3DXQUATERNION      &vRot,
                   D3DXVECTOR3         &vPos
              )
�J�e�S���@�F�R���X�g���N�^
�p�r      �F
�����@�@�@�FLPDIRECT3DDEVICE9   pD3DDevice    //�f�o�C�X�Ȃ�
�@�@�@�@�@�FLPDIRECT3DTEXTURE9  pTexture      //�e�N�X�`��
�@�@�@�@�@�FD3DXVECTOR3         &vScale       //�L�k
�@�@�@�@�@�FD3DXQUATERNION      &vRot         //��]
�@�@�@�@�@�FD3DXVECTOR3         &vPos         //�ʒu
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
****************************************************************************/
MagneticField::MagneticField(
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
	D3DXVECTOR3		   &vScale,							//	: �L�k
	D3DXQUATERNION	   &vRot,							//	: ��]
	D3DXVECTOR3	       &vPos,							//	: �ʒu
	bool				bEffect
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
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/**************************************************************
�֐���     �Fvoid	 MagneticField::Draw(DrawPacket &i_DrawPacket)
�p�r       �F�I�u�W�F�N�g�̕`��
=======
�֐����@�@�Fvoid MagneticField::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket     //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void	MagneticField::Draw(DrawPacket &i_DrawPacket){
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
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}
	//Cylinder::Draw(i_DrawPacket);
};

/*******************************************************************
�֐����@�@�Fvoid MagneticField::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket     //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
********************************************************************/
void	MagneticField::Update(UpdatePacket& i_UpdatePacket)
{
	//	: �}�e�B���A���ݒ�
	if(m_Pole){
		//N��
		D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,0.2f};
		D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,0.2f};

		m_Material.Diffuse	= Diffuse;
		m_Material.Specular	= Specular;
		m_Material.Ambient	= Ambient;
	}
	else{
		//S��
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
		//�����̃G�t�F�N�g
		if( m_bEffect ){
			m_Radius1	+= 0.2f;
			m_Radius2	+= 0.2f;

			if( m_Radius1 > MGPRM_MAGNETICUM ){
				m_Radius1	= 0;
				m_Radius2	= 0;
				
			}
			//�ړ��p
			Debugger::DBGSTR::addStr(L"*************************************************\n");
		}
	}
	else{
		//�z���񂹂�G�t�F�N�g
		if( m_bEffect ){
			m_Radius1	-= 0.2f;
			m_Radius2	-= 0.2f;

			if( m_Radius1 < 0 ){
				m_Radius1	= MGPRM_MAGNETICUM;
				m_Radius2	= MGPRM_MAGNETICUM;
				
			}
			//�ړ��p
			Debugger::DBGSTR::addStr(L"*************************************************\n");
		}
	}
	D3DXMatrixTranslation(&mMove, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling( &mScale, m_Radius1/m_vNormalSize.x, m_Radius2/m_vNormalSize.y, 1.0f );
	m_mMatrix	= mScale * mMove;

	//Context ct ;
	//Cylinder::Transform(*i_UpdatePacket.pVec,i_UpdatePacket.pCntlState,ct);

};

/**************************************************************************
 StartField ��`��
****************************************************************************/
/***************************************************************************
�֐���    �FStartField(
                   LPDIRECT3DDEVICE9   pD3DDevice,
                   LPDIRECT3DTEXTURE9  pTexture,
                   D3DXVECTOR3         &vScale,
                   D3DXQUATERNION      &vRot,
                   D3DXVECTOR3         &vPos
              )
�J�e�S���@�F�R���X�g���N�^
�p�r      �F
�����@�@�@�FLPDIRECT3DDEVICE9   pD3DDevice    //�f�o�C�X�Ȃ�
�@�@�@�@�@�FLPDIRECT3DTEXTURE9  pTexture      //�e�N�X�`��
�@�@�@�@�@�FD3DXVECTOR3         &vScale       //�L�k
�@�@�@�@�@�FD3DXQUATERNION      &vRot         //��]
�@�@�@�@�@�FD3DXVECTOR3         &vPos         //�ʒu
			:D3DCOLORVALUE&      Diffuse,
			:D3DCOLORVALUE&      Specular,
			:D3DCOLORVALUE&      bAmbient,
�߂�l�@�@�F
�S���ҁ@�@�F�{�����V
���l�@�@�@�F
****************************************************************************/
StartField::StartField(
	LPDIRECT3DDEVICE9 pD3DDevice,						//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
	float Radius1,
	float Radius2,
	float Lenght,
	D3DXVECTOR3			&vRot,							//	: ��]
	D3DXVECTOR3	       &vPos,							//	: �ʒu
	D3DCOLORVALUE&     Diffuse,
	D3DCOLORVALUE&     Specular,
	D3DCOLORVALUE&     Ambient
)
:Cylinder(pD3DDevice,Radius1,Radius2,Lenght,vPos,vRot,Diffuse,Specular,Ambient)

{
	try{
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/**************************************************************
�֐����@�@�Fvoid StartField::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket     //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F�{�����V
���l�@�@�@�F
***************************************************************/
void	StartField::Draw(DrawPacket &i_DrawPacket){
	Cylinder::Draw(i_DrawPacket);
};

/*******************************************************************
�֐����@�@�Fvoid StartField::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket     //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F�{�����V
���l�@�@�@�F
********************************************************************/
void	StartField::Update(UpdatePacket& i_UpdatePacket)
{
	//D3DXMATRIX mMove, mScale;
	//D3DXMatrixIdentity(&mMove);
	//D3DXMatrixIdentity(&mScale);
	this->SetBaseScale(D3DXVECTOR3(m_Radius1,m_Radius2,1.0f));
	this->CalcWorldMatrix();
};

/**************************************************************************
 PlayerCoil ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPlayerCoil::PlayerCoil( 	
////							LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////							float Radius1,float Radius2,float Lenght,
////							D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////							D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////							wiz::OBJID id = OBJID_3D_PLAYER)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
////		      :   float Radius1						//�~�̒��a1
////		      :   float Radius2						//�~�̒��a2
////			  :   flaot Lenght						//����
////			  :   D3DXVECTOR3 &vScale
////		      :   D3DXVECTOR3 &vRot				//��]�p
////		      :   D3DXVECTOR3 &vPos				//�ʒu
////              :   D3DCOLORVALUE& Diffuse,		//�f�B�t���[�Y�F
////              :   D3DCOLORVALUE& Specular,		//�X�y�L�����F
////              :   D3DCOLORVALUE& Ambient,		//�A���r�G���g�F
////			  : wiz::OBJID id = OBJID_2D_PLAYER //ID
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O �{�����V
//// ���l       �F
////            �F
////
PlayerCoil::PlayerCoil(

		LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,float Radius2,float Lenght,
		D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id
	)
:MagneticumObject3D(pD3DDevice,pTexture,
					Radius1,Radius2,Lenght,vRot,vPos,
					Diffuse,Specular,Ambient,id)
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_vMove(D3DXVECTOR3( 1.0f, 0.0f, 0.0f))
,m_fMoveDir(PLAYER_BASSROT)
,m_fMovdSpeed(PLAYER_SPEED)
,m_vStartPos(vPos)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bIsSuperMode(false)
,m_fTurnAngle(PLAYER_TURN_ANGLE_Lv1)
,m_pPlayer(NULL)
,m_pMagneticumObject(NULL)
,m_pCamera(NULL)
,m_pSound( NULL )
,m_enumCoilState(COIL_STATE_START)
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
,m_pDSPH(NULL)
,m_bDebugInvincibleMode( false )
#endif
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pCylinder = new Cylinder( pD3DDevice, m_Radius1, m_Radius2, m_Length, m_vPos, g_vZero, Diffuse, Specular, Ambient ) ;
	m_pStartField = new StartField(pD3DDevice,NULL,
									3.45f,3.45f,1.0f,
									g_vZero,D3DXVECTOR3(vPos.x,vPos.y,2.0f),
									Diffuse,Specular,Ambient);
	setPoleN();
	SetBaseRot(vRot);
}
/////////////////// ////////////////////
//// �֐���     �F~PlayerCoil()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F ���� �O
//// ���l       �F
////            �F
////
PlayerCoil::~PlayerCoil(){

#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	SafeDelete( m_pDSPH );
#endif

	SafeDelete( m_pCylinder );
	SafeDelete( m_pStartField );

	m_pPlayer				= NULL ;
	m_pMagneticumObject		= NULL ;
	m_pCamera				= NULL ;
	
};

/////////////////////// ////////////////////
//////// �p�r       �Fbool PlayerCoil::HitTestWall( SPHERE& Coil )
//////// �J�e�S��   �FMultiBox�Ƃ̏Փ˔���
//////// �p�r       �F�}���`�{�b�N�X�Ƃ̏Փ˔���
//////// ����       �F  bool HitTestMultiBox
////////				  MultiBox* pBox,	//�}���`�{�b�N�X
////////				  size_t& Index,	//�q�b�g���Ă�����C���f�b�N�X���߂�
////////				  D3DXVECTOR3& Vec,         //�ŋߐړ_
////////				  D3DXVECTOR3& ElsePos         //��O�̃|�W�V����
//////// �ߒl       �F�Փ˂��Ă����true
//////// �S����     �F�g�n ��m
//////// ���l       �F
bool PlayerCoil::HitTestWall( OBB Obb, float Index ){
	D3DXVECTOR3 Pos = GetPos();
	SPHERE sp;
	sp.m_Center = m_vPos;
	sp.m_Radius = m_pCylinder->getRadius2() ;
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
		m_pMagneticumObject = ( MagneticumObject3D* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_STATIC_MAGNET) ; 
	}
	if( m_pPlayer ){
		//�f�o�b�N�p-----------------------------------------------------------
		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//-----------------------------------------------------------------------

		//��Ԃ��Ƃ̏���
		switch(m_enumCoilState){
			case COIL_STATE_START:
				Update_StateStart();
				break;
			case COIL_STATE_MOVE:
				Update_StateMove();
				break;
			case COIL_STATE_STICK:
				Update_StateStick();
				break;
			case COIL_STATE_DEAD:
				Update_StateDead();
				break;
			case COIL_STATE_CONTINUE:
				Update_StateContinue();
				break;
			case COIL_STATE_CLEAR:
				break;
			default:
				break;
		}

		if(m_bIsSuperMode){
			SuperMode(i_UpdatePacket);
			m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_INVISIBLE );
		}

		//�f�o�b�N�p-----------------------------------------------------------
		Debugger::DBGSTR::addStr( L"�p�x = %f\n",m_fMoveDir);
		//-----------------------------------------------------------------------

		//�}�g���N�X�v�Z
		D3DXMATRIX mPos, mScale, mRotZ, mRotX;
		D3DXMatrixTranslation( &mPos  , m_vPos.x , m_vPos.y , m_vPos.z ) ;
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationZ( &mRotZ, D3DXToRadian( m_fMoveDir - PLAYER_BASSROT ) ) ;
		D3DXMatrixRotationX( &mRotX, D3DXToRadian( m_vRot.x ) );
		m_Matrix = mScale * (mRotX*mRotZ) * mPos ;

	} else {
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer3D) );
	}
	m_pPlayer->setState(m_enumCoilState);
	if(m_enumCoilState == COIL_STATE_START || m_enumCoilState == COIL_STATE_CONTINUE){
		m_pStartField->SetBasePos(D3DXVECTOR3(m_vStartPos.x,m_vStartPos.y,1.0f));
		m_pStartField->Update(i_UpdatePacket);
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
	//���N���b�N�������A��������MOVE��ԂɕύX
	float fLng  = (float)TwoPointToBassLength( vPlayer, m_vPos ) ;
	if(g_bMouseLB && fLng <= START_EFFECTIVE_RANGE_QUAD){
		m_bLastMouseLB = true;
	}
	if(!g_bMouseLB && m_bLastMouseLB){
		m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_FIRE );
		m_enumCoilState = COIL_STATE_MOVE;
		m_bLastMouseLB = false;
		m_pPlayer->CoilWasFired(true);
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
	bool bCheckDistance = CheckDistance( m_pPlayer->getPos(), m_vPos, (float)MGPRM_MAGNETICUM_QUAD, true );
	if( m_pPlayer->getDrawing() && bCheckDistance ){
		m_fMoveDir = MagneticDecision(m_fMoveDir,m_pPlayer->getPos(),m_pPlayer->getMagnetPole());
	}

	//�ݒu���E�Ǝ��@�̔���
	multimap<float, Magnet3DItem*> ItemMap_Target = m_pMagneticumObject->getMapTarget();
	multimap<float,Magnet3DItem*>::iterator it = ItemMap_Target.begin();
	while(it != ItemMap_Target.end()){
		bool bCheckDistance = CheckDistance( it->second->m_vPos, m_vPos, (float)MGPRM_MAGNETICUM_QUAD, false );
		if( bCheckDistance ){
			m_fMoveDir = MagneticDecision(m_fMoveDir,it->second->m_vPos,it->second->m_bMagnetPole);
		}
		++it;
	}

	//���x�w��
	if(m_bIsSuperMode) m_fMovdSpeed = PLAYER_SPEED_SUPER;
	else			   m_fMovdSpeed = PLAYER_SPEED;
	//�w������֎w�苗���ړ�
	ArcMove( m_vMove , m_fMovdSpeed, m_fMoveDir);
	//�ړ��������Z
	m_vPos += m_vMove;

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
	D3DXVECTOR3 vPlayer = g_vZero;
	float		fTargetDir = NULL;
	m_fMoveDir += 5.0f;
	if(m_fMoveDir > 360.0f)m_fMoveDir = float(int(m_fMoveDir) % 360);

	//���ˎ��ɋɂ�ς���
	switch(getMagnetPole()){
		case POLE_S:
			if(!g_bMouseLB || !m_pPlayer->getDrawing()){
				setPoleN();
				m_enumCoilState = COIL_STATE_MOVE;
			}
			break;
		case POLE_N:
			if(!g_bMouseRB || !m_pPlayer->getDrawing()){
				setPoleS();
				m_enumCoilState = COIL_STATE_MOVE;
			}
			break;
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
	static float s_fTimeCount		= 0;
	static int	s_iInterval			= 0;
	static bool s_bIsColorChange	= false;

	if(m_enumCoilState == COIL_STATE_MOVE)
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
	
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
	if(s_iInterval >= 5) s_iInterval = 0;

	//���G���[�h�I��
	if(s_fTimeCount >= COIL_SUPER_MODE_TIME){
		m_bIsSuperMode = false;
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
	m_enumCoilState = COIL_STATE_CONTINUE;
	m_vPos = m_vStartPos;
	m_pCamera->setPosY(m_vStartPos.y);
	m_pPlayer->CoilWasFired(false);
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
	//���N���b�N�������A��������MOVE��ԂɕύX
	float fLng  = (float)TwoPointToBassLength( vPlayer, m_vPos ) ;
	if(g_bMouseLB && fLng <= START_EFFECTIVE_RANGE_QUAD){
		m_bLastMouseLB = true;
	}
	if(!g_bMouseLB && m_bLastMouseLB){
		m_enumCoilState = COIL_STATE_MOVE;
		m_bLastMouseLB = false;
		m_pPlayer->CoilWasFired(true);
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
	}
	if(m_enumCoilState == COIL_STATE_START || m_enumCoilState == COIL_STATE_CONTINUE){
		m_pStartField->Draw(i_DrawPacket);
	}
#if defined( ON_DEBUGGINGPROCESS )
	if( m_pDSPH ) m_pDSPH->Draw( i_DrawPacket );
#endif

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
bool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer ){
	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, i_vCoilPos ) ;
	if( Lng <= i_iBorder ){
		float fBorderLv = i_iBorder/3;
		if(m_enumCoilState == COIL_STATE_MOVE
						&& getMagnetPole() != m_pPlayer->getMagnetPole()
								&& Lng <= fBorderLv/30
									&& IsPlayer){
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

 		D3DCOLORVALUE CoilDiffuse = {1.0f,1.0f,0.0f,0.5f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {1.0f,1.0f,0.0f,0.5f};
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleC.png" ),
				NULL,
				0.0f,1.0f,3.0f,vScale,D3DXVECTOR3(90.0f,0.0f,0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f),
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
Factory_Player::~Factory_Player(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
