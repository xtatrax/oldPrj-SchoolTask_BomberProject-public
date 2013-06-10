////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Enemy.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓��@����
//	�����p��		�F�{�����V
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Enemy ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Wall.h"


namespace wiz{
namespace bomberobject{

const float ENEMY_SPEED = 0.01f;
const float ENEMY_RADIUS = 1.5f;


/**************************************************************************
 EnemySphere ��`��
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveSphere
//
// �S����  : �֓�����
// ���p��  : �{�����V
// �p�r    : �G
//**************************************************************************//	
class EnemySphere : public PrimitiveSphere {
	Camera*					m_pCamera	;
	Sound*					m_pSound;
	ProvisionalPlayer3D*	m_pPlayer	;
	PlayerCoil*				m_pCoil		;
	bool					m_bReset	;
	struct EnemyItem{
		D3DMATERIAL9	m_Material		;
		D3DXMATRIX		m_Matrix		;
		float			m_fMapKey		;
		bool			m_bHidden		;
		D3DXVECTOR3		m_vScale		;
		D3DXVECTOR3		m_vPos			;
		D3DXVECTOR3		m_vStartPos		;
		D3DXQUATERNION	m_vRot			;
		POLE			m_bPole			;
		bool			m_vIsAlive		;
		DeadEffect*		m_pDeadEffect[PARTICLS_NUM_ENEMY]	;
		EnemyItem():m_bHidden(true){}
		virtual ~EnemyItem(){}
	};
	
//map<�I�u�W�F�N�g�̃|�W�V����,EnemyItem>
	//multimap<float,EnemyItem*> m_ItemMap_All;	//�S�Ă�EnemyItem
	//multimap<float,EnemyItem*> m_ItemMap_Target;//�`��Ώۂ�EnemyItem

	//map<�I�u�W�F�N�g�̃|�W�V����,WallItem>
	typedef multimap<float,EnemyItem*>	ALLCONTAINER		;
	typedef list<EnemyItem*>			TARGETCONTAINER		;
	ALLCONTAINER						m_ItemMap_All		;	//�S�Ă�WallItem
	TARGETCONTAINER						m_ItemMap_Target	;	//�`��Ώۂ�WallItem

//std::find

protected:

/////////////////// ////////////////////
//// �p�r       �FUpdateTargetItem()
//// �J�e�S��   �F
//// �p�r       �F�֐�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
	void UpdateTargetItem();

public:

/////////////////// ////////////////////
//// �֐���     �FEnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �FPrimitiveSphere�̔h���^
////           �F
////
	EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0 , wiz::OBJID id = OBJID_3D_ENEMY);

/////////////////// ////////////////////
//// �p�r       �F~EnemySphere();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
	~EnemySphere();

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F�֓�����
//// ���p��     �F �{�����V
//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

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
//// �S����     �F�֓�����
//// ���p��     �F �{�����V
//// ���l       �F
////            �F
////
	void Update( UpdatePacket& i_UpdatePacket );

/////////////////// ////////////////////
//// �p�r       �Fvoid AddEnemy( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FEnemy�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F�֓�����
//// ���p��     �F �{�����V
//// ���l       �F
	void AddEnemy(
		const D3DXVECTOR3 &vScale		,
		const D3DXVECTOR3 &vRot			,
		const D3DXVECTOR3 &vPos			,
		const D3DCOLORVALUE& Diffuse	,
		const D3DCOLORVALUE& Specular	,
		const D3DCOLORVALUE& Ambient
	);

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
void	CreateEffect( UpdatePacket& i_UpdatePacket, TARGETCONTAINER::iterator it );


/////////////////// ////////////////////
//// �p�r       �Fbool HitTestWall( OBB Obb )
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�ǂƂ̏Փ˔���
//// ����       �F  OBB Obb           //  : �����Ώۂ�OBB
//// �ߒl       �F�Փ˂��Ă����true
//// �S����     �F�g�n ��m
//// ���l       �F
void HitTestWall( OBB );


};

/**************************************************************************
class Factory_Enemy;
�p�r: ���C���H��N���X
****************************************************************************/
class Factory_Enemy{
	public:
/**************************************************************************
Factory_Enemy(
LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
TextureManager& TexMgr			//�e�N�X�`���̔z��
);
�p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
�߂�l: �Ȃ�
***************************************************************************/
	Factory_Enemy(FactoryPacket* fpac);
/**************************************************************************
~MyFactory();
�p�r: �f�X�g���N�^
�߂�l: �Ȃ�
***************************************************************************/
	~Factory_Enemy();
};

}//end of namespace bomberobject.
}//end of namespace wiz.
