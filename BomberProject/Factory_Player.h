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

#define  MGPRM_MAGNETICUM	10  /* ���E�̉e�����a( ���ݒP�� pixel ) */
#define  MGPRM_MAGNETICUM_QUAD ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM )
#define  PLAYER_SPEED		(   0.08f ) 
#define  PLAYER_BASSROT		( 90.0f )

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
	Camera*			m_Camera;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_MovePosY;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;
	bool			m_bField;
public:
	//	: 
	ProvisionalPlayer3D( FactoryPacket* fpac, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
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

	bool	FieldDraw(){
		return	m_bField;
	};
};

/************************************************************************
class MagneticField : public Cylinder

�S����	: ������
�p�r	: ���E�͈̔�
************************************************************************/
class	MagneticField : public Cylinder{
	//D3DXMATRIX		m_Matrix ;
	//D3DXVECTOR3		m_vPos ;
	//D3DXQUATERNION	m_vRot ;
	//D3DXVECTOR3		m_vScale ;
public:
	MagneticField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	//void	setPos(D3DXVECTOR3 pos){
	//	m_vPos	= pos;
	//}
};

//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// �S����  : �{�����V
// �p�r    : �R�C��
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{

	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_fMoveDir   ;//�p�x
	float			m_fMovdSpeed ;//���x 
	
	ProvisionalPlayer3D*	m_pPlayer;

	Camera* m_pCamera;


public:
	/////////////////// ////////////////////
	//// �֐���     �FPlayerCoil( 	
	////							LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////							float Radius1,float Radius2,float Lenght,
	////							D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////							D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////							wiz::OBJID id = OBJID_3D_PLAYER)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
	////		      :   float Radius1						//�~�̒��a1
	////		      :   float Radius2						//�~�̒��a2
	////			  :   flaot Lenght						//����
	////			  :   D3DXVECTOR3 &vScale
	////		      :   D3DXVECTOR3 &vRot				//��]�p
	////		      :   D3DXVECTOR3 &vPos				//�ʒu
	////              :   D3DCOLORVALUE& Diffuse,		//�f�B�t���[�Y�F
	////              :   D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////              :   D3DCOLORVALUE& Ambient,		//�A���r�G���g�F
	////			  : wiz::OBJID id = OBJID_2D_PLAYER //ID
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O �{�����V(�C��)
	//// ���l       �F
	////            �F
	////
	PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,
		float Radius2,
		float Lenght,
		D3DXVECTOR3 &vScale,	
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_PLAYER
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

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���S���W���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getPos() const { return m_vPos	;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getSpeed() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���x���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	float getSpeed() const { return m_fMovdSpeed	;	}	;

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
