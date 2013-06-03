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
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DXVECTOR3 &vDirOffset,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id)
,m_Rect( vRect )
,m_Rect2( vRect2 )

{
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
void Gage::Recovery( int i_iValue, int i_iMaxValue ){
	if(m_Rect2.right < i_iMaxValue){
		m_pRect->right	+= i_iValue;
		if( m_Rect2.right > i_iMaxValue )
			m_pRect->right	= i_iMaxValue;
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
void Gage::Consume( int i_iValue ){
	if(m_Rect2.right > 0){
		m_Rect2.right	-= i_iValue;
		if(m_Rect2.right < 0){
			m_Rect2.right	= 0;
		}
	}
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
	m_pRect	= m_Rect;
	SpriteObject::Draw( i_DrawPacket );
	//�Q�[�W�̕`��
	m_pRect	= m_Rect2;
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
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	RECT* vRect,
	RECT* vRect2,
	wiz::OBJID id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	vRect,vRect2)
{
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
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
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
	LPDIRECT3DDEVICE9	pD3DDevice,
	LPDIRECT3DTEXTURE9	pTex,
	D3DXVECTOR3			&vScale,
	D3DXVECTOR3			&vRot,
	D3DXVECTOR3			&vPos,
	RECT*				vRect,
	RECT*				vRect2,
	wiz::OBJID			id
)
:Gage(pD3DDevice,pTex,vScale,vRot,vPos,g_vZero,
	  vRect,vRect2)

{
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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_Super.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(144.0f,550.0f,0.0f),
				Rect(0,0,512,32),
				Rect(0,32,0,256)
			)
		);

		//���EN�p�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_N(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_N.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(120.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
			)
		);
		//���E�pS�Q�[�W
		fpac->m_pVec->push_back(
			new MagneticGage_S(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Gauge_S.png" ),
				D3DXVECTOR3(1.0f,1.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(420.0f,500.0f,0.0f),
				Rect(0,0,256,32),
				Rect(0,32,256,64)
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
