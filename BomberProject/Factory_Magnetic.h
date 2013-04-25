////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

#define  POLE_S true		/* S�� */
#define  POLE_N false		/* N�� */


namespace wiz{

//**************************************************************************//
// class MagneticumObject : public SpriteObject ;
//
// �S����  : ���� �O
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
class MagneticumObject : public SpriteObject{

//////////
//	: ����J
private:
	//	: ���Ƀt���O
	//	: S�� = POLE_S
	//	: N�� = POLE_N
	bool m_bMagnetPole ;

//////////
//	: �v���e�N�g
protected:
	//	: ���W
	D3DXVECTOR3 m_vPos ;
	D3DXVECTOR3 m_vScale ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; m_Color = 0xFF0000FF	; } ;
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	; } ;
/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F����J�A�N�Z�b�T
//// �p�r       �F���ɂ𔽓]������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
////            �F
////
	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: ���J
public:
	MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
/////////////////// ////////////////////
//// �֐���     �FD3DXVECTOR3 getPos() const
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���S���W���l��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;
/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���ɂ��l��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F S�� = POLE_S = false
////            �F N�� = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
	
};


/**************************************************************************
 class Factory_Magnetic;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Magnetic{
public:
/**************************************************************************
 Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Magnetic();
};
}
//end of namespace wiz.
