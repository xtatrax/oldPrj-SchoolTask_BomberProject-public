////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�g�n ��m
//	����			�F�{�� ���V
//	�����ް��Ɣ��l	�F�v���C���[���U�����镨��
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
#include "Factory_MagnetField.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const float	PLAYER_RECOVERY_POINT		= 0.008f;
const float	PLAYER_CONSUME_POIMT		= 0.006f;
const float	PLAYER_INVOCATION_POINT		= 0.100f;
const float MAGNET_FIELD_ALPHA			= 0.2f;


namespace wiz{
namespace bomberobject{

extern class	MagneticGage_N	;
extern class	MagneticGage_S	;

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
class ProvisionalPlayer3D : public MagnetField{
	MouseCursor*	m_pCursor		;
	Camera*			m_Camera		;
	PlayerCoil*		m_pPlayerCoil	;
	MagneticGage_N* m_pMGage_N		;
	MagneticGage_S* m_pMGage_S		;
	D3DXMATRIX		m_Matrix		;
	bool			m_bLastMouseRB	;
	bool			m_bLastMouseLB	;
	bool			m_bDrawing		;
	bool			m_bPlaySound	;
	bool			m_bChangeFirst	;
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
		wiz::OBJID id = OBJID_3D_USERMAGNET );
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
		if( Cursor2D::pressLorRButton() ){ 
			return m_vPos	;
		}else{
			return g_vMin	;
		}
	}	;

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
//end of namespace bomberobject.
}
//end of namespace wiz.
