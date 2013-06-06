////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Coil.h
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
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"


const float			PLAYER_SPEED					= 0.08f;
const float			PLAYER_SPEED_SUPER				= 0.12f;
const float			PLAYER_BASSROT					= 90.0f;
const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
const float			COIL_SUPER_MODE_TIME			= 5.0f;
const float			COIL_ROTATION_ANGLE				= 15.0f;
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
const float			COIL_EXPANSION_VALUE_STICK		= 1.5f;

enum COIL_STATE{			//���@�̏��
	COIL_STATE_START,		//�X�^�[�g
	COIL_STATE_MOVE,		//�ړ�
	COIL_STATE_STICK,		//�z��
	//COIL_STATE_SUPER,		//���G
	COIL_STATE_DEAD,		//���S
	COIL_STATE_CONTINUE,	//�R���e�B�j���[
	COIL_STATE_CLEAR,		//�N���A
	COIL_STATE_STOP			//��~���
};

namespace wiz{
namespace bomberobject{
extern class ProvisionalPlayer3D ;

/************************************************************************
class	StartField : public Cylinder

�S����	: �{�����V
�p�r	: �X�^�[�g�͈̔�
************************************************************************/
//class	StartField : public Cylinder{
//public:
//	StartField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		float Radius1,
//		float Radius2,
//		float Lenght,
//		D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
//);
//    void	Draw(DrawPacket& i_DrawPacket) ;
//	void	Update(UpdatePacket& i_UpdatePacket);
//};
//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// �S����  : ���� �O �{�����V
// �p�r    : �R�C��
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	DrawSphere*		m_pDSPH		;
	bool			m_bDebugInvincibleMode;
#endif
	Sphere*			m_pSphere		;
	D3DXMATRIX		m_Matrix		;
	D3DXVECTOR3		m_vPos			;
	D3DXQUATERNION	m_vRot			;
	D3DXVECTOR3		m_vScale		;
	D3DXVECTOR3		m_vOriginScale	;
	D3DXVECTOR3		m_vMove			;
	float			m_OBBRadius		;
	float			m_fMoveDir		;//�p�x
	float			m_fMovdSpeed	;//���x
	D3DXVECTOR3		m_vStartPos		;
	float			m_fTurnAngle	;
	bool			m_bLastMouseRB	;
	bool			m_bLastMouseLB	;
	bool			m_bReadyToStart ;
	bool			m_bReadyContinue;

	bool			m_bIsSuperMode	;//���G��Ԃ̃t���O (���G��Ԃ͑��̏�ԂƏd�Ȃ�̂�COIL_STATE�ɓ���Ȃ�)

	Sound*					m_pSound;
	ProvisionalPlayer3D*	m_pPlayer;

	MagneticumObject3D*		m_pMagneticumObject;

	Camera*					m_pCamera;
	
	COIL_STATE				m_enumCoilState;

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
	////		      :   float Radius1						//���̒��a1
	////		      :   float Radius2						//���̒��a2
	////		      :   float Radius3						//���̒��a
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
		float Radius3,
		float Lenght,
		D3DXVECTOR3 &vScale,	
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_COIL
	);

	/////////////////// ////////////////////
	//// �֐���     �F~PlayerCoil()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F ���� �O
	//// ���l       �F
	////            �F
	////
	~PlayerCoil();

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
	//// �֐���     �Fvoid Update_StateStick()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_STICK���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateStick();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid SuperMode()
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
	void SuperMode( UpdatePacket& i_UpdatePacket );

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
	//// �֐���     �Fvoid Update_StateContinue()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_CONTINUE���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update_StateContinue();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update_StateStop()
	//// �J�e�S��   �F
	//// �p�r       �FSTATE_STOP���̓���
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	////
	void Update_StateStop();

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
	float MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, POLE i_bMagnetPole_Field ) const;

	/////////////////// ////////////////////
	//// �p�r       �Fbool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�����𔻒�
	//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
	////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
	////�@�@�@�@�@�@�Fbool�@�@�@�@IsPlayer�@�@�@�@�@//���肪�v���C���[���ǂ���
	//// �ߒl       �Ftrue , false
	//// �S����     �F�{�����V
	//// ���l       �F
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer );

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
	//// �֐���     �FD3DXVECTOR3 getScale() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�傫�����l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getScale() const { return m_vScale;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getDir() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�������l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	float getDir() const { return m_fMoveDir;	}	;

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

	///////////////////////////////////////
	//// �֐���     �FD3DXVECTOR3 getStartPos()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F���W�f�[�^
	//// �S��       �F������
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getStartPos(){
		return	m_vStartPos;
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

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setPos(D3DXVECTOR3 i_vPos)
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	void setPos(D3DXVECTOR3 i_vPos){
		m_vPos = i_vPos;
	}

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setScale(D3DXVECTOR3 i_vScale)
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	void setScale(D3DXVECTOR3 i_vScale){
		m_vScale = i_vScale;
	}

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setDir(float i_vDir)
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	void setDir(float i_vDir){
		m_fMoveDir = i_vDir;
	}

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

	void	setReadyContinue( bool b ){
		m_bReadyContinue	= b;
	}
	/////////////////// ////////////////////
	//// �֐���     �Fvoid getSuperMode()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���G��Ԃ��l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	bool getSuperMode() const{
		return m_bIsSuperMode;
	}

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setStartPos(float i_fPosY)
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	void setSuperMode(bool i_vFlg){
		m_bIsSuperMode = i_vFlg;
	}

};

/**************************************************************************
 class Factory_Coil;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Coil{
public:
/**************************************************************************
 Factory_Coil(
	FactoryPacket* fpac //�p�P�b�g�f�[�^
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Coil( FactoryPacket* fpac , D3DXVECTOR3* vStartPos = NULL );
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Coil();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
