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
#include "Object.h"
#include "BassItems.h"
#include "Factory_Magnetic.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const float PLAYER_SPEED				= 0.08f;
const float PLAYER_BASSROT				= 90.0f;
const float PLAYER_TURN_ANGLE_Lv1		= 1.0f;
const float PLAYER_TURN_ANGLE_Lv2		= 2.0f;
const float PLAYER_TURN_ANGLE_Lv3		= 3.0f;

enum COIL_STATE{			//���@�̏��
	COIL_STATE_START,		//�X�^�[�g
	COIL_STATE_MOVE,		//�ړ�
	COIL_STATE_STOP,		//��~
	COIL_STATE_STICK,		//�z��
	COIL_STATE_SUPER,		//���G
	COIL_STATE_DEAD			//���S
};

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
	bool			m_bCoilWasFired;
	bool			m_bDrawing;
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

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CoilWasFired(bool i_bFlg)
	//// �J�e�S��   �F�֐�
	//// �p�r       �Fm_bCoilWasFired�ɒl������
	//// ����       �Fbool i_bFlg
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	void CoilWasFired(bool i_bFlg){
		m_bCoilWasFired = i_bFlg;
	}

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

/************************************************************************
class MagneticField : public Cylinder

�S����	: ������
�p�r	: ���E�͈̔�
************************************************************************/
class	MagneticField : public Cylinder{
	bool	m_Pole;	//���E�̋ɁFt=S��, f=N��
	bool		m_bEffect;
	D3DXVECTOR3	m_vNormalSize;
	D3DXMATRIX	m_mMatrix;
public:
	MagneticField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,bool bEffect);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPole( bool pole ){
		m_Pole	= pole;
	}
	bool	getPole(){
		return	m_Pole;
	}
};

//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// �S����  : ���� �O �{�����V(�ҏW)
// �p�r    : �R�C��
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
#if defined( ON_DEBUGGINGPROCESS )
	DrawSphere*		m_pDSPH ;
#endif
	Cylinder*		m_pCylinder ;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	D3DXVECTOR3		m_vMove;
	float			m_fMoveDir   ;//�p�x
	float			m_fMovdSpeed ;//���x
	D3DXVECTOR3		m_vStartPos;
	float			m_fTurnAngle;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;

	ProvisionalPlayer3D*	m_pPlayer;

	MagneticumObject3D*		m_pMagneticumObject;

	Camera*					m_pCamera;
	
	COIL_STATE		m_enumCoilState;

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

	/////////////////////// ////////////////////
	//////// �p�r       �F	bool HitTestMultiBox(MultiBox* pBox,size_t& Index,D3DXVECTOR3& Vec,D3DXVECTOR3& ElsePos)
	//////// �J�e�S��   �FMultiBox�Ƃ̏Փ˔���
	//////// �p�r       �F�}���`�{�b�N�X�Ƃ̏Փ˔���
	//////// ����       �F  bool HitTestMultiBox
	////////				  MultiBox* pBox,	//�}���`�{�b�N�X
	////////				  size_t& Index,	//�q�b�g���Ă�����C���f�b�N�X���߂�
	////////				  D3DXVECTOR3& Vec,         //�ŋߐړ_
	////////				  D3DXVECTOR3& ElsePos         //��O�̃|�W�V����
	//////// �ߒl       �F�Փ˂��Ă����true
	////////				�q�b�g���Ă���true�i�C���f�b�N�X�ƍŋߐړ_�����j
	//////// �S����     �F�g�n ��m
	//////// ���l       �F
	bool HitTestWall( OBB, float Index );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////			  �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////			  �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update_StateStart()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_START���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateStart();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update_StateMove()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_MOVE���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateMove();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update_StateSuper()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_SUPER���̓���
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////			  �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////			  �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateSuper( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update_StateDead()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_DEAD���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateDead();

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
	//// �֐���     �Ffloat MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F���@�ɑ΂���z���񂹁A�����̏���
	//// ����       �Ffloat i_fCoilDir            //���@�̊p�x
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vMagnetPos   //���E�̈ʒu
	////�@�@�@�@�@�@�Fbool i_bMagnetPole_Field	// ���E�̋�
	//// �ߒl       �F
	//// �S��       �F�{�����V
	//// ���l       �F
	////�@�@�@�@�@�@�F
	float MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field ) const;

	/////////////////// ////////////////////
	//// �p�r       �Fbool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�����𔻒�
	//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
	////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
	//// �ߒl       �Ftrue , false
	//// �S����     �F�{�����V
	//// ���l       �F
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder );

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���S���W���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getPos() const { return m_vPos;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getSpeed() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���x���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	float getSpeed() const { return m_fMovdSpeed;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FCOIL_STATE getState() const 
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F��Ԃ��l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	COIL_STATE getState() const { return m_enumCoilState;	}	;

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

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setStartPos(float i_fPosY)
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	void setStartPos(D3DXVECTOR3 i_vPos){
		m_vStartPos = i_vPos;
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
