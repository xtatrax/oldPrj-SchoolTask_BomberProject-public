////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Magnetic.h"

#define  MGPRM_MAGNETICUM	200  /* ���E�̉e�����a( ���ݒP�� pixel ) */
#define  MGPRM_MAGNETICUM_QUAD ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM )
#define  PLAYER_SPEED		(   0.5f ) 
#define  PLAYER_BASSROT		( 270.0f ) 


namespace wiz{



//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// �S����  : ���� �O
// �p�r    : ���̃��[�U�[�ݒu���E
//**************************************************************************//
class ProvisionalPlayer : public MagneticumObject{
public:
	//	: 
	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
};

// 3D�p
//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// �S����  : �g�n��m
// �p�r    : ���̃��[�U�[�ݒu���E
//**************************************************************************//
class ProvisionalPlayer3D : public MagneticumObject3D{
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
public:
	//	: 
	ProvisionalPlayer3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
	//	:
	void Draw( DrawPacket& i_DrawPacket );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
};


//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// �S����  : ���� �O
// �p�r    : �R�C��
//**************************************************************************//
class PlayerCoil : public MagneticumObject{


	//	: �R�C���̕����w�W�p�p�[�c
	SpriteObject*		m_pDirParts		;

	//	: 
	ProvisionalPlayer*	m_pPlayer		;

	float		m_fMoveDir   ;//�p�x
	float       m_fMovdSpeed ;//���x

public:
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
	PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pCoreTexture,			//	: �R�A������Texture
		LPDIRECT3DTEXTURE9 pDirTexture,				//	: ������\���O�p�̂Ă������[
		D3DXVECTOR3 &vScale,						//	: �L�k
		D3DXVECTOR3 &vRot,							//	: ��]
		D3DXVECTOR3 &vPos,							//	: �ʒu
		D3DXVECTOR3 &vDirOffset,					//	: ������\���O�p�̕`��I�t�Z�b�g
		RECT* pCoreRect = NULL,						//	: �`��͈�
		RECT* pDirRect = NULL,						//	: �`��͈�
		wiz::OBJID id = OBJID_3D_COIL				//	: ID
	);

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
	void Update( UpdatePacket& i_UpdatePacket );

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
    void Draw(DrawPacket& i_DrawPacket) ;

};



/**************************************************************************
 class Factory_Player;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Player{
public:
/**************************************************************************
 Factory_Player(
	FactoryPacket* fpac //�p�P�b�g�f�[�^
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Player( FactoryPacket* fpac );
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Player();
};
}
//end of namespace wiz.
