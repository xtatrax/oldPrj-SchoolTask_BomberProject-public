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
const float CHECK_POINT_RADIUS = 12.35f ;
D3DCOLORVALUE CHECKPOINTCOLOR = { 1.0f, 0.0f, 0.0f, 1.0f } ;
namespace wiz{
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, g_vZero, CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR, id, false, NULL, 2) 
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
	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL    );
	if( !m_pCamera ) m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA );
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
//// �S����     �F
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////            �F
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera ){
		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_Pos.x = m_ItemContainer[ m_ActiveItem ]->fPosY ;

			m_WorldMatrix = MatrixCalculator(m_BaseScale, m_Qt, D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY, 0.0f));
			Cylinder::Draw( i_DrawPacket );
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
				pcp = new CheckPoint( fpac->pD3DDevice, 10.0f)
			);
			pcp->add( 10.0f );


			

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