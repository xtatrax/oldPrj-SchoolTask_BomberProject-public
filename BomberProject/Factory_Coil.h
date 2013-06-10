////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Coil.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�����V
//	�ҏW			�F�g�n��m
//					�F������
//	�����ް��Ɣ��l	�F�v���C���[�R�C���֘A
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagneticumObject3D ;
//			class Factory_Coil ;
//		const float			COIL_SPEED						= 0.08f;
//		const float			COIL_SPEED_SUPER				= 0.12f;
//		const float			COIL_ACCELERATION_VALUE			= 0.25f;
//		const float			COIL_ACCELERATION_DECREASE		= 0.01f;
//		const float			COIL_BASSROT					= 90.0f;
//		const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
//		const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
//		const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
//		const float			COIL_SUPER_MODE_TIME			= 5.0f;
//		const D3DXVECTOR3	COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
//		const float			COIL_ROTATION_ANGLE				= 15.0f;
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
//		const float			COIL_EXPANSION_VALUE_STICK		= 1.5f;
//		enum COIL_STATE{			//���@�̏��
//			COIL_STATE_START,		//�X�^�[�g
//			COIL_STATE_MOVE,		//�ړ�
//			COIL_STATE_STICK,		//�z��
//			//COIL_STATE_SUPER,		//���G
//			COIL_STATE_DEAD,		//���S
//			COIL_STATE_CONTINUE,	//�R���e�B�j���[
//			COIL_STATE_CLEAR,		//�N���A
//			COIL_STATE_STOP			//��~���
//		};
//
#pragma once

#include "StdAfx.h"
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"
#include "Factory_DeadEffect.h"
#include "Factory_Continue.h"


const float			COIL_SPEED						= 0.08f;
const float			COIL_SPEED_SUPER				= 0.12f;
const float			COIL_ACCELERATION_VALUE			= 0.25f;
const float			COIL_ACCELERATION_DECREASE		= 0.01f;
const float			COIL_BASSROT					= 90.0f;
const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
const float			COIL_SUPER_MODE_TIME			= 5.0f;
const D3DXVECTOR3	COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
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
extern class Continue ;
extern class Dead ;

//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// �S����  : ���� �O
// ���p��  : �{�����V
// �ҏW    : �g�n ��m
//         : ������
// �p�r    : ���[�U�[���U������ΏۂɂȂ镨
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
	friend MagneticumObject3D;
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	//	: �f�o�b�O�p�̃f�[�^
	DrawSphere*		m_pDSPH		;				//	: ���̊E�`��N���X�̃|�C���^
	bool			m_bDebugInvincibleMode;		//	: �f�o�b�O�p���G�t���O
#endif
	Sphere*			m_pSphere			;	//	: �R�A
	D3DXMATRIX		m_Matrix			;	//	: �s��
	D3DXVECTOR3		m_vPos				;	//	: ���W
	D3DXQUATERNION	m_vRot				;	//	: ��]
	D3DXVECTOR3		m_vScale			;	//	: �L�k
	D3DXVECTOR3		m_vOriginScale		;	//	: ���̑傫��
	D3DXVECTOR3		m_vMove				;	//	: �ړ�����
	D3DXVECTOR3		m_vStartPos			;	//	: �ăX�^�[�g�ʒu
	float			m_OBBRadius			;	//	: ����SphereRadius
	float			m_fMoveDir			;	//	: �ړ��p�x
	float			m_fMovdSpeed		;	//	: �ړ����x
	float			m_fAcceleration		;	//	: ����
	float			m_fTurnAngle		;	//	: ��]�p�x?
	bool			m_bLastMouseRB		;	//	: �}�E�X��R�{�^����������Ă��邩
	bool			m_bLastMouseLB		;	//	: �}�E�X��L�{�^����������Ă��邩
	bool			m_bReadyToStart		;	//	: 
	bool			m_bReadyContinue	;	//	:
	bool			m_bIsSuperMode		;	//	: ���G��Ԃ̃t���O (���G��Ԃ͑��̏�ԂƏd�Ȃ�̂�COIL_STATE�ɓ���Ȃ�)
	bool			m_bDrawContinue		;	//	:

	Sound*					m_pSound					;	//	: �����f�[�^�ւ̃|�C���^
	Camera*					m_pCamera					;	//	: Camera�ւ̃|�C���^
	Box*					m_pSuperField				;	//	: ?
	Continue*				m_pSelect					;	//	: 
	Continue*				m_pSelect2					;	//	: 
	Dead*					m_pDeadChar					;	//	: 
	ProvisionalPlayer3D*	m_pPlayer					;	//	: ���[�U�ݒu���E�ւ̃|�C���^
	MagneticumObject3D*		m_pMagneticumObject			;	//	: �����z�u���E�ւ̃|�C���^
	DeadEffect*				m_pDeadEffect[PARTICLS_NUM]	;
	COIL_STATE				m_enumCoilState				;

	LPDIRECT3DTEXTURE9	m_pDeadTex		;	//���U�G�t�F�N�g�̉摜
	LPDIRECT3DTEXTURE9	m_pContinueTex	;
	LPDIRECT3DTEXTURE9	m_pTitleTex		;
	LPDIRECT3DTEXTURE9	m_pDeadCharTex	;
public:
	/////////////////// ////////////////////
	//// �֐���     �FPlayerCoil::PlayerCoil(
	////            �F    LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////            �F    float Radius1,float Radius2,float Lenght,
	////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////            �F    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////            �F    wiz::OBJID id = OBJID_3D_PLAYER)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F  LPDIRECT3DDEVICE9   pD3DDevice   // �f�o�C�X
	////            �F  LPDIRECT3DTEXTURE9  pTexture     // �e�N�X�`��	
	////            �F  float               Radius1      // ���̒��a1
	////            �F  float               Radius2      // ���̒��a2
	////            �F  float               Radius3      // ���̒��a
	////            �F  flaot               Lenght       // ����
	////            �F  D3DXVECTOR3&        vScale       // �L�k
	////            �F  D3DXVECTOR3&        vRot         // ��]�p
	////            �F  D3DXVECTOR3&        vPos         // �ʒu
	////            �F  D3DCOLORVALUE&      Diffuse      // �f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE&      Specular     // �X�y�L�����F
	////            �F  D3DCOLORVALUE&      Ambient      // �A���r�G���g�F
	////            �F  wiz::OBJID          id = OBJID_3D_COIL //ID
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���p��     �F�{�����V
	//// ���l       �F
	////            �F
	////
	PlayerCoil(
		LPDIRECT3DDEVICE9	pD3DDevice			,
		LPDIRECT3DTEXTURE9	pTexture			,
		LPDIRECT3DTEXTURE9	pTexture_Super		,
		LPDIRECT3DTEXTURE9	pTexture_Dead		,
		LPDIRECT3DTEXTURE9	pTexture_Continue	,
		LPDIRECT3DTEXTURE9	pTexture_Title		,
		LPDIRECT3DTEXTURE9	pTexture_DeadChar	,
		float				Radius1				,
		float				Radius2				,
		float				Radius3				,
		float				Lenght				,
		D3DXVECTOR3&		vScale				,	
		D3DXVECTOR3&		vRot				,
		D3DXVECTOR3&		vPos				,
		D3DCOLORVALUE&		Diffuse				,
		D3DCOLORVALUE&		Specular			,
		D3DCOLORVALUE&		Ambient				,
		wiz::OBJID			id					= OBJID_3D_COIL
	);

	/////////////////// ////////////////////
	//// �֐���     �FPlayerCoil::~PlayerCoil()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F ���� �O
	//// ���l       �F
	////            �F
	////
	~PlayerCoil();

	/////////////////// ////////////////////
	//// �p�r       �Fbool PlayerCoil::HitTestWall( OBB Obb )
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�ǂƂ̏Փ˔���
	//// ����       �F  OBB Obb           //  : �����Ώۂ�OBB
	//// �ߒl       �F�Փ˂��Ă����true
	//// �S����     �F�g�n ��m
	//// ���l       �F
	bool HitTestWall( OBB );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid PlayerCoil::Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F  UpdatePacket& i_UpdatePacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���p��     �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	////
	void	CreateEffect( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvoid PlayerCoil::Update_StateStart()
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
	//// �֐���     �Fvoid PlayerCoil::Update_StateMove()
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
	//// �֐���     �Fvoid PlayerCoil::Update_StateStick()
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
	//// �֐���     �Fvoid SPlayerCoil::uperMode()
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
	//// �֐���     �Fvoid PlayerCoil::Update_StateDead()
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
	//// �֐���     �Fvoid PlayerCoil::Update_StateContinue()
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
	//// �֐���     �Fvoid PlayerCoil::Update_StateStop()
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
	//// �p�r       �Fvirtual void PlayerCoil::Draw( DrawPacket& i_DrawPacket )
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
	//// �֐���     �Ffloat PlayerCoil::MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
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
	//// �p�r       �Fbool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�����𔻒�
	//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
	////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
	////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
	////�@�@�@�@�@�@�Fbool�@�@�@�@IsPlayer�@�@�@�@�@//���肪�v���C���[���ǂ���
	//// �ߒl       �Ftrue , false
	//// �S����     �F�{�����V
	//// ���l       �F
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, float i_iBorder, bool IsPlayer );

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 gPlayerCoil::etPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���S���W���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getPos() const { return m_vPos;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 PlayerCoil::getScale() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�傫�����l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	D3DXVECTOR3 getScale() const { return m_vScale;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 PlayerCoil::getDir() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�������l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F������
	//// ���l       �F
	////            �F
	float getDir() const { return m_fMoveDir;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 gPlayerCoil::etSpeed() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���x���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	float getSpeed() const { return m_fMovdSpeed;	}	;

	/////////////////// ////////////////////
	//// �֐���     �FCOIL_STATE PlayerCoil::getState() const 
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F��Ԃ��l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	COIL_STATE getState() const { return m_enumCoilState;	}	;

	///////////////////////////////////////
	//// �֐���     �FD3DXVECTOR3 PlayerCoil::getStartPos()
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
	//// �֐���     �Fvoid PlayerCoil::setState( COIL_STATE i_State )
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F��Ԃ�ύX
	//// ����       �FCOIL_STATE i_State
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�{�����V
	//// ���l       �F
	////            �F
	void setState( COIL_STATE i_State ){ m_enumCoilState = i_State; }	;

	/////////////////// ////////////////////
	//// �֐���     �Fvoid PlayerCoil::setPos(D3DXVECTOR3 i_vPos)
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
	//// �֐���     �Fvoid PlayerCoil::setScale(D3DXVECTOR3 i_vScale)
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
	//// �֐���     �Fvoid PlayerCoil::setDir(float i_vDir)
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
	//// �֐���     �Fvoid PlayerCoil::setStartPos(float i_fPosY)
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
	//// �֐���     �Fvoid PlayerCoil::getSuperMode()
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
	//// �֐���     �Fvoid PlayerCoil::setStartPos(float i_fPosY)
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
