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
const static BYTE	byGaugeAlpha = 0xFF ;
//const static float	 = 0xA0 ;
//const static float	byGaugeAlpha = 0xA0 ;
namespace wiz{
namespace bomberobject{

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
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTex		,
	const D3DXVECTOR3			&vScale		,
	const D3DXVECTOR3			&vRot		,
	const D3DXVECTOR3			&vPos		,
	const D3DXVECTOR3			&vDirOffset	,
	const RECT					GaugeRect	,		//	: �`��͈�
	const RECT					FrameRect	,		//	: �`��͈�
	const wiz::OBJID			id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	NULL,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_BassRect(  GaugeRect )
,m_GaugeRect( GaugeRect )
,m_FrameRect( FrameRect )
,m_fRate( 0.0f )
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
	m_fRate -= fAddValue ;
	if( m_fRate <= 0.0f ){
		m_fRate = 0.0f ;
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
	m_fRate += fSubValue ;
	if( m_fRate >= 1.0f ){
		m_fRate = 1.0f ;
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
	m_GaugeRect.right  = m_BassRect.left - m_BassRect.right ;
	m_GaugeRect.right *= 1.0f - m_fRate ;
	
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
	//�g�̕`��
	m_pRect	= m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//�Q�[�W�̕`��
	m_pRect	= m_GaugeRect;
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
	GaugeRect,FrameRect,id)
,m_vBassPos(vPos)
,m_vScale( vScale )
,m_vRot( vRot )
,m_pCursor( NULL )
,m_pLineTop( NULL )
,m_pLineLeft( NULL )
,m_pLineBottom( NULL )
,m_pLineRight( NULL )
,m_bAcquired(false)
{
	m_fRate = 0.0f;

	const	D3DXVECTOR3	vDirTop		= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirLeft	= D3DXVECTOR3( cosf( D3DXToRadian(90.0f) ), sinf( D3DXToRadian(90.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirBottom	= D3DXVECTOR3( cosf( D3DXToRadian(0.0f) ), sinf( D3DXToRadian(0.0f) ), 0.0f );
	const	D3DXVECTOR3	vDirRight	= D3DXVECTOR3( cosf( D3DXToRadian(90.0f) ), sinf( D3DXToRadian(90.0f) ), 0.0f );
	const	float	fRangeW	= 100.0f;
	const	float	fRangeH	= 5.0f;
	m_pLineTop		= new Line( g_vZero, vDirTop,	 fRangeW, 0xFF00FFFF );
	m_pLineLeft		= new Line( g_vZero, vDirLeft,	 fRangeH, 0xFF00FFFF );
	m_pLineBottom	= new Line( m_pLineLeft->getEndPos(), vDirBottom, fRangeW, 0xFF00FFFF );
	m_pLineRight	= new Line( m_pLineTop->getEndPos(), vDirRight,	 fRangeH, 0xFF00FFFF );
}

/////////////////// ////////////////////
//// �֐���     �F~SuperGage();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
SuperGage::~SuperGage(){
	m_pCursor = NULL;
	SafeDelete( m_pLineTop );
	SafeDelete( m_pLineLeft );
	SafeDelete( m_pLineBottom );
	SafeDelete( m_pLineRight );
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

	//�g�̕`��
	m_mMatrix = m_Matrix ;
	m_pRect	= m_FrameRect;
	SpriteObject::Draw( i_DrawPacket );
	//�Q�[�W�̕`��
	m_pRect	= m_GaugeRect;
	SpriteObject::Draw( i_DrawPacket );

	if(m_bAcquired){
		m_pLineTop->draw(i_DrawPacket.pD3DDevice);
		m_pLineLeft->draw(i_DrawPacket.pD3DDevice);
		m_pLineBottom->draw(i_DrawPacket.pD3DDevice);
		m_pLineRight->draw(i_DrawPacket.pD3DDevice);
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
void SuperGage::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCursor ) m_pCursor = (MouseCursor*)SearchObjectFromID(i_UpdatePacket.pVec, OBJID_SYS_CURSOR);

	D3DXMATRIX	mPos, mScale, mRot ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x + m_vBassPos.x - m_GaugeRect.right * m_vScale.x;
	vPos.y	= (float)m_pCursor->get2DPos().y + m_vBassPos.y;
	vPos.z	= 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x/2, m_vScale.y, m_vScale.z );
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mRot * mPos ;

	//�A�C�e���l�����̃G�t�F�N�g
	if(m_bAcquired)Update_Line();

	//�Q�[�W�p�ɍ��W�̂ݍČv�Z
	vPos.x		= (float)m_pCursor->get2DPos().x + m_vBassPos.x ;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_Matrix	= mScale * mRot * mPos ;
	//�Q�[�W�̕`��
	m_GaugeRect.right  = /*m_BassRect.left -*/ m_BassRect.right ;
	m_GaugeRect.right *= 0.0f + m_fRate ;
	
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
void SuperGage::Update_Line(){
	D3DXMATRIX		mLineScale, mLinePos;
	D3DXVECTOR3		vLineScale	= D3DXVECTOR3(1.0f,1.0f,0.0f),vLinePos, 
					vBaseLinePos = D3DXVECTOR3((float)m_pCursor->get2DPos().x + m_vBassPos.x/**0.225f*/,
												(float)m_pCursor->get2DPos().y + m_vBassPos.y,0.0f);
	static float	s_fMovingDistance	= 0.0f; 

	D3DXMatrixScaling( &mLineScale, vLineScale.x, vLineScale.y, vLineScale.z );

	//�㕔
	vLineScale;
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y - s_fMovingDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineTop->setMatrix( mLineScale * mLinePos );

	//����
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x - s_fMovingDistance, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineLeft->setMatrix( mLineScale * mLinePos );

	//����
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x, vBaseLinePos.y + s_fMovingDistance, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineBottom->setMatrix( mLineScale * mLinePos );

	//�E��
	vLinePos	= D3DXVECTOR3(vBaseLinePos.x + s_fMovingDistance, vBaseLinePos.y, 0.0f);
	D3DXMatrixTranslation( &mLinePos, vLinePos.x, vLinePos.y, vLinePos.z);
	m_pLineRight->setMatrix( mLineScale * mLinePos );
	
	s_fMovingDistance	+= 0.8f;
	if(s_fMovingDistance >= 6.0f){
		s_fMovingDistance	= 0.0f;
		m_bAcquired = false;
	}	
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
	D3DXVECTOR3			&vScale		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
}
/////////////////// ////////////////////
//// �֐���     �F~MagneticGage_N();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
MagneticGage_N::~MagneticGage_N(){
	m_pCursor  = NULL;
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
	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;
	vPos.x	= (float)m_pCursor->get2DPos().x	;
	vPos.y	= (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	= 0.0f	;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mPos ;

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
	D3DXVECTOR3			&vScale		,
	RECT				GaugeRect	,
	RECT				FrameRect	,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,g_vOne,g_vZero,g_vZero,vPos,
	  GaugeRect,FrameRect,id)
,m_pCursor( NULL )
,m_vScale( vScale )
{
	this->m_Color.byteColor.a = byGaugeAlpha ;
}
/////////////////// ////////////////////
//// �֐���     �F~MagneticGage_N();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
MagneticGage_S::~MagneticGage_S(){
	m_pCursor = NULL;
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
	D3DXMATRIX	mPos, mScale ;
	D3DXVECTOR3 vPos ;
	vPos.x	 = (float)m_pCursor->get2DPos().x	;
	vPos.y	 = (float)m_pCursor->get2DPos().y +  m_GaugeRect.top	;
	vPos.z	 = 0.0f	;
	//vPos	+= m_v;
	D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y/2, m_vScale.z );
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);
	m_mMatrix	= mScale * mPos ;

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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_Super5.png" ),
				D3DXVECTOR3(0.4f,0.25f,0.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				//D3DXVECTOR3(950.0,30.0f,0.0f),
				//D3DXVECTOR3(140.0,-55.0f,0.0f),
				D3DXVECTOR3(38.0f,-35.0f,0.0f),
				Rect(0,32,512,64),
				Rect(0,0,512,32)
			)
		);

		//���EN�p�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_N4.png" ),
				//D3DXVECTOR3( 60.0f,-250.0f,0.0f),
				D3DXVECTOR3( 60.0f,-450.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,32,-300,64),
				Rect(0,0,300,32)
				//Rect(0,32,-300,64),
				//Rect(0,0,256,32)
			)
		);
		//���E�pS�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_S4.png" ),
				//D3DXVECTOR3( 60.0f,-220.0f,0.0f),
				D3DXVECTOR3( 60.0f,-410.0f,0.0f),
				D3DXVECTOR3( 0.4f, 0.4f, 0.0f ),
				Rect(0,32,-300,64),
				Rect(0,0,300,32)
				//Rect(0,32,-256,64),
				//Rect(0,0,256,32)
			)
		);
				//D3DXVECTOR3( 80.0f,-170.0f,0.0f),
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
//end of namespace bomberobject.
}
//end of namespace wiz.
