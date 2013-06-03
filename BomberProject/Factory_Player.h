////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O �g�n��m(�ҏW) �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Coil.h"
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const int	PLAYER_RECOVERY_POINT		= 1;
const int	PLAYER_CONSUME_POIMT		= 1;
const int	PLAYER_INVOCATION_POINT		= 40;

namespace wiz{


//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// �S����  : ���� �O
// �p�r    : ���̃��[�U�[�ݒu���E
//**************************************************************************//
//class ProvisionalPlayer : public MagneticumObject{
//public:
//	//	: 
//	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
//		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
//};

// 3D�p
//**************************************************************************//
// class ProvisionalPlayer3D : public MagneticumObject ;
//
// �S����  : �g�n��m
// �p�r    : ���̃��[�U�[�ݒu���E
//**************************************************************************//
class ProvisionalPlayer3D : public MagneticumObject3D{
	Camera*			m_Camera;
	PlayerCoil*		m_pPlayerCoil;
	Sound*			m_pSound;
	MagneticGage_N* m_pMGage_N;
	MagneticGage_S* m_pMGage_S;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_MovePosY;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;
	bool			m_bDrawing;
	COIL_STATE		m_enumCoilState;
	//struct PolyItem{
	//	LPDIRECT3DTEXTURE9 m_pTexture;
	//	D3DMATERIAL9   m_Material;
	//	D3DXMATRIX	   m_Matrix;
	//	D3DXVECTOR3    m_vScale ;
	//	D3DXVECTOR3	   m_vPos ;
	//	D3DXQUATERNION m_vRot;
	//	virtual ~PolyItem(){}
	//};
	//PolyItem				m_Item_Poly;

public:
	//	: 
	ProvisionalPlayer3D( FactoryPacket* fpac, LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DTEXTURE9 pTexture2,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
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
	~ProvisionalPlayer3D();
	//	:
	void Draw( DrawPacket& i_DrawPacket );
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
	D3DXVECTOR3 getPos() const {
		if( g_bMouseLB || g_bMouseRB ){ 
			return m_vPos	;
		}else{
			return g_vMin	;
		}
	}	;

	/////////////////// ////////////////////
	//// �֐���     �Ffloat getMoveY() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �Fm_MovePosY���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	float getMoveY() const { return m_MovePosY	;	}	;

	/****************************************
	�֐����@�Fbool	getDrawing()
	�J�e�S���F�֐�
	�p�r�@�@�F�`��t���O�̎擾
	�����@�@�F�Ȃ�
	�߂�l�@�F�`�悵�Ă��邩�̃t���O
	�S���@�@�F������
	���l�@�@�F
	****************************************/
	bool	getDrawing(){
		return	m_bDrawing;
	}
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setState( COIL_STATE i_State )
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F��Ԃ�ύX
	//// ����       �FCOIL_STATE i_State
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	void setState( COIL_STATE i_State ){ m_enumCoilState = i_State; }	;
};

/************************************************************************
class MagneticField : public Cylinder

�S����	: ������
�p�r	: ���E�͈̔�
************************************************************************/
class	MagneticField : public Cylinder{
	POLE		m_Pole;	//���E�̋ɁFt=S��, f=N��
	bool		m_bEffect;
	D3DXVECTOR3	m_vNormalSize;
	D3DXMATRIX	m_mMatrix;
public:
	MagneticField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,bool bEffect);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPole( POLE pole ){
		m_Pole	= pole;
	}
	POLE	getPole(){
		return	m_Pole;
	}
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
