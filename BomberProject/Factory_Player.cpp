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

//	: UI�̍���
#define UI_HEIGHT					( 88.0f )
//	: �\����ʂ̔{�� x=800, y=512 : x=40, y=25.6
#define DRAW_CLIENT_MAGNIFICATION	( 20.0f )
//	: ���E�̔��a
#define MAGNETIC_RADIUS				( 0.5f )

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
	}else{
	

	
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
	FactoryPacket*	fpac,								//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
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
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bField(false)
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
	if( g_bMouseLB || g_bMouseRB ){ 

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
		m_bField	= true;
	}
	else	m_bField	= false;
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
		m_MovePosY	= m_Camera->getPosY();
	}
	if( g_bMouseLB || g_bMouseRB ){ 
		if( !m_bLastMouseLB && !m_bLastMouseRB ){
			wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
			D3DXVECTOR3 vMove = g_vZero ;
			Point MousePos ;
			GetCursorPos( &MousePos ) ;
			ScreenToClient( g_hWnd , &MousePos) ;
			
			m_vPos.x = (float)MousePos.x / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS ;
			m_vPos.y = (( STANDARD_WINDOW_HEIGHT - MousePos.y ) - UI_HEIGHT ) / DRAW_CLIENT_MAGNIFICATION - MAGNETIC_RADIUS + ( m_Camera->getPosY() - m_MovePosY ) ;

			if(g_bMouseLB){
				m_pMagneticField->setPole(true);
				m_pMagneticField2->setPole(true);
				m_pMagneticField3->setPole(true);
			}
			else{
				m_pMagneticField->setPole(false);
				m_pMagneticField2->setPole(false);
				m_pMagneticField3->setPole(false);
			}

			m_pMagneticField->SetPos(m_vPos);
			m_pMagneticField->Update(i_UpdatePacket);

			m_pMagneticField2->SetPos(m_vPos);
			m_pMagneticField2->Update(i_UpdatePacket);

			m_pMagneticField3->SetPos(m_vPos);
			m_pMagneticField3->Update(i_UpdatePacket);

			if( g_bMouseLB )
				setPoleN() ;
			if( g_bMouseRB )
				setPoleS() ;
		}

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
	}else{
		
	}
	m_bLastMouseLB = g_bMouseLB ;
	m_bLastMouseRB = g_bMouseRB ;
};

/**************************************************************************
 MagneticField ��`��
****************************************************************************/
/***************************************************************************
<<<<<<< HEAD
�֐���     �FMagneticField( FactoryPacket* fpac,			//	: �f�o�C�X�Ȃ�
					 LPDIRECT3DTEXTURE9 pTexture,	//	: �e�N�X�`���\
					 wiz::OBJID id )				//	: ID
�p�r       �F�R���X�g���N�^
****************************************************************************/
//MagneticField::MagneticField(
//	LPDIRECT3DDEVICE9 pD3DDevice,						//	: �f�o�C�X
//	LPDIRECT3DTEXTURE9 pTexture,						//	: �e�N�X�`���[
//	D3DXVECTOR3		   &vScale,							//	: �L�k
//	D3DXQUATERNION	   &vRot,							//	: ��]
//	D3DXVECTOR3	       &vPos							//	: �ʒu
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
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTexture,
	D3DXVECTOR3		   &vScale,
	D3DXQUATERNION	   &vRot,
	D3DXVECTOR3	       &vPos
)
:Cylinder(pD3DDevice,vScale.x, vScale.y, vScale.z, g_vZero, g_vZero,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE()
	)
,m_Pole(true)
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
<<<<<<< HEAD
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
>>>>>>> workspace
***************************************************************/
void	MagneticField::Draw(DrawPacket &i_DrawPacket){
	Cylinder::Draw(i_DrawPacket);
};

/*******************************************************************
<<<<<<< HEAD
�֐���     �Fvoid	 MagneticField::Update(UpdatePacket& i_UpdatePacket)
�p�r       �F�f�[�^�X�V
=======
�֐����@�@�Fvoid MagneticField::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket     //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
>>>>>>> workspace
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

	Context ct ;
	Cylinder::Transform(*i_UpdatePacket.pVec,i_UpdatePacket.pCntlState,ct);

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
//// �S��       �F���� �O �{�����V(�C��)
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
					Diffuse,Specular,Ambient)
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_fMoveDir(PLAYER_BASSROT)
,m_fMovdSpeed(PLAYER_SPEED)
,m_pPlayer(NULL)
,m_pCamera(NULL)
,m_enumCoilState(COIL_STATE_START)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	D3DXMatrixIdentity( &m_Matrix ) ;
	m_pCylinder = new Cylinder( pD3DDevice, m_Radius1, m_Radius2, m_Length, m_vPos, g_vZero, Diffuse, Specular, Ambient ) ;
	setPoleN();
	SetBaseRot(vRot);
}
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
	sp.m_Radius = m_pCylinder->getRadius1() ;
	//�ʏ�̏Փ˔���
	D3DXVECTOR3 Vec ;
	if(HitTest::SPHERE_OBB(sp,Obb,Vec)){
		MessageBox( NULL, L"���������I�I", L"Error", NULL) ;
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

	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
	if( !m_pCamera ){ 
		m_pCamera = ( Camera* ) SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ; 
	}
	if( m_pPlayer ){
		// �ړ��̕��� + ����
		D3DXVECTOR3 vMove = D3DXVECTOR3( 1.0f, 0.0f, 0.0f) ;
		// ���[�U�[���E�̍��W
		D3DXVECTOR3 vProvisionalPos  = this->m_pPlayer->getPos();	
		// �R�C���ƃ��[�U�[���E�̋������Z�o
		float Lng  = (float)TwoPointToBassLength( vProvisionalPos, m_vPos ) ;
		// �e�X�g�p
		float Lng2 = (float)VectorLength( D3DXVECTOR3( vProvisionalPos.x - m_vPos.x, vProvisionalPos.y - m_vPos.y ,0) );
		//���@�Ǝ��E�̊p�x
		float fTargetDir = TwoPoint2Degree( vProvisionalPos , m_vPos );
		//���@�̃f�J���g���W (����g���Ă܂���)
		D3DXVECTOR3 vDescartes = ConvertToCartesianCoordinates(vMove.x,m_fMoveDir);

		//�f�o�b�N�p-----------------------------------------------------------
		// ���E���]
		Controller1P.Gamepad.wPressedButtons.XConState.Y && this->ChangePole() ;
		//�e���l��\��
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"fTargetDir : %f\n", fTargetDir);
		Debugger::DBGSTR::addStr( L"vDescartes : %f\n", vDescartes.x);
		//-----------------------------------------------------------------------

		//��Ԃ��Ƃ̏���
		switch(m_enumCoilState){
			case COIL_STATE_START:
				Update_StateStart(fTargetDir);
				break;
			case COIL_STATE_MOVE:
				Update_StateMove(vMove,fTargetDir,Lng);
				break;
			case COIL_STATE_STOP:
				break;
			case COIL_STATE_STICK:
				break;
			case COIL_STATE_SUPER:
				break;
			case COIL_STATE_DEAD:
				break;
			default:
				break;
		}

		if( Lng <= m_pPlayer->getMagneticum() ){
			//���@�Ǝ��E�̊p�x
			float fTargetDir = TwoPoint2Degree( vProvisionalPos , m_vPos );
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

	//�J�������W�ݒ�
	if( m_pCamera && m_pCamera->getPosY() < m_vPos.y ){
		m_pCamera->setPosY( m_vPos.y );
	}

};

/////////////////// ////////////////////
//// �֐���     �Fvoid PlayerCoil::Update_StateStart( float i_fTargetDir )
//// �J�e�S��   �F
//// �p�r       �FSTATE_START���̓���
//// ����       �F
////�@�@�@�@�@�@�F
////�@�@�@�@�@�@�F
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateStart( float i_fTargetDir ){
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
	//���N���b�N�������ꂽ��MOVE��ԂɕύX
	float fLng  = (float)TwoPointToBassLength( vPlayer, m_vPos ) ;
	if(g_bMouseLB && fLng <= START_EFFECTIVE_RANGE_QUAD){
		m_enumCoilState = COIL_STATE_MOVE;
	}
};

/////////////////// ////////////////////
//// �֐���     �FPlayerCoil::Update_StateMove( D3DXVECTOR3 i_vMove, D3DXVECTOR3 i_vProvisionalPos ,float i_fLng )
//// �J�e�S��   �F
//// �p�r       �FSTATE_MOVE���̓���
//// ����       �FD3DXVECTOR3 i_vMove				// �ړ��̕��� + ����
////�@�@�@�@�@�@�Ffloat i_fTargetDir				// ���[�U�[���E�Ƃ̊p�x
////�@�@�@�@�@�@�Ffloat i_fLng					// �R�C���ƃ��[�U�[���E�̋���
//// �ߒl       �F�Ȃ�
//// �S��       �F�{�����V
//// ���l       �F
////            �F
////
void PlayerCoil::Update_StateMove( D3DXVECTOR3 i_vMove, float i_fTargetDir ,float i_fLng ){
	if( i_fLng <= MGPRM_MAGNETICUM_QUAD ){
		float	fReverse = 0.0f;
		if(m_fMoveDir > 180.0f){
			fReverse = m_fMoveDir - 180.0f;
		}
		else{
			fReverse = m_fMoveDir + 180.0f;
		}

		if(m_pPlayer->getMagnetPole() != this->getMagnetPole()){
			if(m_fMoveDir < i_fTargetDir){
				if(i_fTargetDir - m_fMoveDir <= 180.0f){
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
			else if(m_fMoveDir > i_fTargetDir){
				if(m_fMoveDir - i_fTargetDir <= 180.0f){
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
			if(fReverse != i_fTargetDir){
				if(m_fMoveDir < i_fTargetDir){
					if(i_fTargetDir - m_fMoveDir <= 180.0f){
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
				else if(m_fMoveDir > i_fTargetDir){
					if(m_fMoveDir - i_fTargetDir <= 180.0f){
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

	//	: �w������֎w�苗���ړ�
	ArcMove( i_vMove , m_fMovdSpeed, m_fMoveDir);
	//�ړ��������Z
	m_vPos += i_vMove;

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
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}
};


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
				//fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"CircleP.png" ),
				vScale,
				D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
				D3DXVECTOR3(0.0f,0.0f,0.0f))
		);

 		D3DCOLORVALUE CoilDiffuse = {0.7f,0.7f,0.7f,1.0f};
		D3DCOLORVALUE CoilSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE CoilAmbient = {0.5f,0.5f,0.5f,1.0f};
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
