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
namespace bomberobject{

//Camera*	ProvisionalPlayer3D::m_Camera	= NULL;
extern class WallObject ;
const	float	GAUGE_VANISHRATE	= 0.87f;
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
,m_Camera(NULL)
,m_pPlayerCoil(NULL)
,m_pMGage_N(NULL)
,m_pMGage_S(NULL)
,m_pSound( NULL )
,m_vPos(vPos)
,m_vRot(vRot)
,m_vScale(vScale)
,m_MovePosY(0)
,m_bLastMouseRB(false)
,m_bLastMouseLB(false)
,m_bDrawing(false)
,m_bPlaySound(false)
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
	m_Camera		= NULL ;
	m_pPlayerCoil	= NULL;
	m_pSound		= NULL;
	m_pMGage_N		= NULL;
	m_pMGage_S		= NULL;
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

	if( m_pPlayerCoil && ( m_pPlayerCoil->getState() == COIL_STATE_MOVE || m_pPlayerCoil->getState() == COIL_STATE_STICK ) ){
		if( m_bDrawing ){ 
			if( m_pSound && !m_bPlaySound ){
				m_bPlaySound = true ;
				m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_SETFIELD ) ;
			}
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
		else	m_pSound->SoundPause(RCTEXT_SOUND_SE_SETFIELD);
	}else{
		m_bPlaySound = false ;
		m_pSound->SoundPause( RCTEXT_SOUND_SE_SETFIELD );
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
	if( !m_pPlayerCoil ) m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	if( !m_pMGage_N )	 m_pMGage_N		= (MagneticGage_N*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_N));
	if( !m_pMGage_S )	 m_pMGage_S		= (MagneticGage_S*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(MagneticGage_S));

	RECT rc;
	::GetClientRect(wiz::DxDevice::m_hWnd, &rc);

	Debugger::DBGSTR::addStr( L" Pos( %f, %f, %f )\n" , m_vPos.x , m_vPos.y, m_vPos.z ) ;

	if( m_pPlayerCoil->getState() == COIL_STATE_MOVE || m_pPlayerCoil->getState() == COIL_STATE_STICK ){
		if( (g_bMouseLB || g_bMouseRB) && !(g_bMouseLB && g_bMouseRB)){ 
			if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){				
				if( !m_bLastMouseLB && !m_bLastMouseRB){
					if(g_bMouseLB)m_pMGage_N->Consume(PLAYER_INVOCATION_POINT);
					if(g_bMouseRB)m_pMGage_S->Consume(PLAYER_INVOCATION_POINT);
					if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){
						wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
						D3DXVECTOR3 vMove = g_vZero ;
						Point MousePos ;
						GetCursorPos( &MousePos ) ;
						ScreenToClient( wiz::DxDevice::m_hWnd , &MousePos) ;

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
				if( (g_bMouseLB && m_pMGage_N->getRate() < GAUGE_VANISHRATE) || (g_bMouseRB && m_pMGage_S->getRate() < GAUGE_VANISHRATE) ){	

					if( g_bMouseLB  && !g_bMouseRB && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_N->Consume(PLAYER_CONSUME_POIMT);
					if( !g_bMouseLB && g_bMouseRB  && m_pPlayerCoil->getState() != COIL_STATE_STICK )m_pMGage_S->Consume(PLAYER_CONSUME_POIMT);

					if( !g_bMouseLB && g_bMouseRB  )m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
					if( g_bMouseLB  && !g_bMouseRB )m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);

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
			if(m_pPlayerCoil->getState() != COIL_STATE_STICK){
				m_bDrawing	= false;
				if( m_pMGage_N ) m_pMGage_N->Recovery(PLAYER_RECOVERY_POINT);
				if( m_pMGage_S ) m_pMGage_S->Recovery(PLAYER_RECOVERY_POINT);
			}
		}
	}else{
			m_bDrawing	= false;
	}
	m_bLastMouseLB = g_bMouseLB ;
	m_bLastMouseRB = g_bMouseRB ;

	//���E�̃G�t�F�N�g�𓮂���
	m_pMagneticField4->Update(i_UpdatePacket);

	if(m_pPlayerCoil->getState() == COIL_STATE_CONTINUE){
		if( m_pMGage_N ) m_pMGage_N->ResetGauge();
		if( m_pMGage_S ) m_pMGage_S->ResetGauge();
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
	const LPDIRECT3DDEVICE9		pD3DDevice	,						//	: �f�o�C�X
	const LPDIRECT3DTEXTURE9	pTexture	,						//	: �e�N�X�`���[
	const D3DXVECTOR3&			vScale		,						//	: �L�k
	const D3DXQUATERNION&		vRot		,						//	: ��]
	const D3DXVECTOR3&			vPos		,						//	: �ʒu
	const bool					bEffect
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
	Debugger::DBGSTR::addStr(L"���a1 %f\n", m_Radius1);
	Debugger::DBGSTR::addStr(L"���a2 %f\n", m_Radius2);
	D3DXMatrixTranslation(&mMove, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling( &mScale, m_Radius1/m_vNormalSize.x, m_Radius2/m_vNormalSize.y, 1.0f );
	m_mMatrix	= mScale * mMove;

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
