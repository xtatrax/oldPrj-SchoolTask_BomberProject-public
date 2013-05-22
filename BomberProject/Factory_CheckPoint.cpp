////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_CheckPoint.h"
#include "Factory_Player.h"
#include "BassItems.h"
const float CHECK_POINT_RADIUS = 0.25f ;
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.0f, 1.0f, 0.0f, 1.0f } ;
namespace wiz{
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_ActiveItem( NULL )
{
	
}
CheckPoint::~CheckPoint(){
	SafeDeletePointerContainer( m_ItemContainer ) ;
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec, typeid(PlayerCoil) );
	if( !m_pCamera ) m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA );
	
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){

		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;
		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->fPosY);
		}
	}
};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O �{�����V(�ҏW)
//// ���l       �F
////            �F
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){

		float DrawEndLength = m_pCamera->getPosY() - DRAW_TOLERANCE ;
		if(  DrawEndLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_ActiveItem++ ;
			if(m_ActiveItem <= m_ItemContainer.size()) return ;
		}

		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;
			CalcWorldMatrix();
			Cylinder::Draw( i_DrawPacket );
			
			OBB obb = OBB( m_BasePos, m_BaseQt, m_BaseScale );
			//DrawOBB(i_DrawPacket);
			//m_pCoil->HitTestWall();
		}
	}
};

/**************************************************************************
 Factory_CheckPoint ��`��
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,1.0f,1.0f,1.0f};
			
			CheckPoint* pcp ;
			fpac->m_pVec->push_back(
				pcp = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp->add( 30.0f );

			CheckPoint* pcp2 ;
			fpac->m_pVec->push_back(
				pcp2 = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp2->add( 40.0f );

		}
		
		catch(...){
			//��throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace wiz.