////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Gage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F�Q�[�W�t�@�N�g���[
//					��
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Gage.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"
const static BYTE	byGaugeAlpha = 0x70 ;
//const static float	 = 0xA0 ;
//const static float	byGaugeAlpha = 0xA0 ;
namespace wiz{

/**************************************************************************
 Gage ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FGage::Gage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FD3DXVECTOR3 &vDirOffset        // �`��I�t�Z�b�g
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
Gage::Gage(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vScale		,
	D3DXVECTOR3			&vRot		,
	D3DXVECTOR3			&vPos		,
	D3DXVECTOR3			&vDirOffset	,
	RECT				GaugeRect	,		//	: �`��͈�
	RECT				FrameRect	,		//	: �`��͈�
	wiz::OBJID			id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	NULL,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_BassRect(  GaugeRect )
,m_GaugeRect( GaugeRect )
,m_FrameRect( FrameRect )
,m_fRate( 1.0f )
{
	m_mGaugeMatrix = m_mMatrix ;
}
Gage::~Gage(){
	m_pRect = NULL ;
}
/****************************************
�֐����@�@�Fvoid Gage::Recovery()
�J�e�S���@�F�֐�
�p�r�@�@�@�F�G�l���M�[�[�U
�����@�@�@�Fint i_iValue		//���炷�l
         �@�Fint i_iMaxValue	//�Q�[�W�̍ő�l
�߂�l�@�@�F
�S���ҁ@�@�F������ �{�����V(�ҏW)
���l�@�@�@�F
*****************************************/
void Gage::Recovery( float fAddValue ){
	m_fRate += fAddValue ;
	if( m_fRate >= 1.0f ){
		m_fRate = 1.0f ;
	}
}
/*****************************************
 �֐����@�@�Fvoid Gage::Consume()
 �J�e�S���@�F�֐�
 �p�r�@�@�@�F�G�l���M�[����
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������ �{�����V(�ҏW)
 ���l�@�@�@�F
 *****************************************/
void Gage::Consume( float fSubValue ){
	m_fRate -= fSubValue ;
	if( m_fRate <= 0.0f ){
		m_fRate = 0.0f ;
	}
}
/////////////////// ////////////////////
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void Gage::Update( UpdatePacket& i_UpdatePacket ){
	//�Q�[�W�̕`��
	m_GaugeRect.top  = m_BassRect.bottom - m_BassRect.top ;
	m_GaugeRect.top *= 1.0f - m_fRate ;
	
	Debugger::DBGSTR::addStr( L" Rate = %f \n", m_fRate);
}

/**************************************************************
�֐����@�@�Fvoid Gage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void Gage::Draw(DrawPacket& i_DrawPacket){
	//�Q�[�W�̕`��
	m_pRect	= m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );
	//�g�̕`��
	m_mMatrix = m_mGaugeMatrix ;
	m_pRect	= m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 SuperGage ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FSuperGage::SuperGage(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FD3DXVECTOR3 &vDirOffset        // �`��I�t�Z�b�g
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************************************************/
SuperGage::SuperGage(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vScale		,
	D3DXVECTOR3			&vRot		,
	D3DXVECTOR3			&vPos		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	GaugeRect,FrameRect)
,m_vBassPos(vPos)
{
	m_fRate = 0.0f;
}

/**************************************************************
�֐����@�@�Fvoid SuperGage::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void SuperGage::Draw(DrawPacket& i_DrawPacket){

	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	= m_vBassPos.x	;
	vPos.y	= m_vBassPos.y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 MagneticGage_N ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FMagneticGage_N::MagneticGage_N(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F�{�����V
���l�@�@�F
*************************************************************************/
MagneticGage_N::MagneticGage_N(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vPos		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect)
,m_pCursor( NULL )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
}
/////////////////// ////////////////////
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void MagneticGage_N::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);
	Gage::Update(i_UpdatePacket);
	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x	;
	vPos.y	= (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

}

/**************************************************************
�֐����@�@�Fvoid MagneticGage_N::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F�{�����V
���l�@�@�@�F
***************************************************************/
void MagneticGage_N::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 MagneticGage_S ��`��
***************************************************************************/
/************************************************************************
 �֐���     �FMagneticGage_S::MagneticGage_S(
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
�J�e�S���F�R���X�g���N�^
�p�r�@�@�FLPDIRECT3DDEVICE9 pD3DDevice   // �f�o�C�X
�����@�@�FLPDIRECT3DTEXTURE9 pTex        // �e�N�X�`���\
�@�@�@�@�FD3DXVECTOR3 &vScale            // �L�k
�@�@�@�@�FD3DXVECTOR3 &vRot              // ��]
�@�@�@�@�FD3DXVECTOR3 &vPos              // �ʒu
�@�@�@�@�FRECT* vRect                    // �`��͈�
�@�@�@�@�FRECT* vRect2                   // �`��͈�
�@�@�@�@�Fwiz::OBJID id                  // ID
�߂�l�@�F
�S���ҁ@�F�{�����V
���l�@�@�F
*************************************************************************/
MagneticGage_S::MagneticGage_S(
	LPDIRECT3DDEVICE9	pD3DDevice	,
	LPDIRECT3DTEXTURE9	pTex		,
	D3DXVECTOR3			&vPos		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect)
,m_pCursor( NULL )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
}
/////////////////// ////////////////////
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void MagneticGage_S::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);
	Gage::Update(i_UpdatePacket);
	D3DXMATRIX	mPos ;
	D3DXVECTOR3 vPos ;
	vPos.x	 = (float)m_pCursor->get2DPos().x	;
	vPos.y	 = (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	 = 0.0f	;
	//vPos	+= m_v;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mPos ;

}

/**************************************************************
�֐����@�@�Fvoid MagneticGage_S::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket    //�`��p�̃f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F�{�����V
���l�@�@�@�F
***************************************************************/
void MagneticGage_S::Draw(DrawPacket& i_DrawPacket){
	Gage::Draw( i_DrawPacket );
}

/**************************************************************************
 Factory_Item ��`��
****************************************************************************/
/**************************************************************************
�֐����@�@�FFactory_Item::Factory_Item( FactoryPacket* fpac );
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac     // �������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������ �{�����V(�ҏW)
���l�@�@�@�F
***************************************************************************/
Factory_Gage::Factory_Gage(FactoryPacket* fpac){
	try{
		//�X�[�p�[���[�h�p�Q�[�W
		fpac->m_pVec->push_back(
			new SuperGage(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(950.0,30.0f,0.0f),
				Rect(112,0,143,272),
				Rect(144,0,175,272)
			)
		);

		//���EN�p�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3(-170.0f,-140.0f,0.0f),
				Rect(0,0,113,272),
				Rect(0,0,0,0)
			)
		);
		//���E�pS�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MagnetGauge_Arc.png" ),
				D3DXVECTOR3( +60.0f,-140.0f,0.0f),
				Rect(179,0,290,272),
				Rect(0,0,0,0)
			)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 �֐����@�@�FFactory_Item::~Factory_Item();
 �J�e�S���@�F�f�X�g���N�^
 �p�r�@�@�@�F
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������
 ���l�@�@�@�F
***************************************************************************/
Factory_Gage::~Factory_Gage(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
