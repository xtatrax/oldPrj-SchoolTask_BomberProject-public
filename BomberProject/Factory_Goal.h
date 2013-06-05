////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Goal.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject;
//		class Factory_Goal ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
class FMemoryTex;

�p�r�@�F�������̑}��
�S���ҁF������
**************************************************************************/
class FMemoryTex : public PrimitiveBox{
	Camera*			m_pCamera;
	PlayerCoil*		m_pCoil;
	D3DXVECTOR3		m_vScale ;
	D3DXVECTOR3		m_vPos ;
	int				m_iPtn;
	struct mItem{
		D3DMATERIAL9	mMaterial;
		D3DXMATRIX		mMatrix;
		D3DXVECTOR3		vScale ;
		D3DXVECTOR3		vPos ;
		D3DXQUATERNION	vRot;
		virtual ~mItem(){}
	};

	//map<�I�u�W�F�N�g�̃|�W�V����,WallItem>
	multimap<float,mItem*> m_ItemMap_Memory;	//�S�Ă�DescItem
	multimap<float,mItem*> m_ItemMap_Target; //�`��Ώۂ�DescItem
public:
	/////////////////// ////////////////////
	//// �p�r       �FDescription(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	FMemoryTex(LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

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
	//// �S����     �F������
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
	//// �S����     �F������
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid AddDesc( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �FDesc�̒ǉ�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////		    �F  D3DXVECTOR3 &vScale				//�g��k��
	////		    �F  D3DXVECTOR3 &vRot				//��]�p
	////		    �F  D3DXVECTOR3 &vPos				//�ʒu
	////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	void AddMemory(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

/****************************************************
�֐����@�Fvoid	OrientGoal()
�J�e�S���F�֐�
�p�r�@�@�F�N���A��v���[���[�𓮂���
�����@�@�F�Ȃ�
�߂�l�@�F�Ȃ�
�S���ҁ@�F������
���l�@�@�F
****************************************************/
	void	OrientGoal(UpdatePacket& i_UpdatePacket);
};

/******************************************************
class Item : public PrimitiveSphere

�p�r�@�F�A�C�e��
�S���ҁF������
*******************************************************/
class	GoalObject	:public PrimitiveBox{
	PlayerCoil*	m_pCoil;
	Sound*		m_pSound;
	bool		m_bPlaySound;
	struct GoalItem{
		D3DMATERIAL9 m_Material;
		D3DXMATRIX	m_Matrix;
		D3DXVECTOR3 m_vScale ;
		D3DXVECTOR3 m_vPos ;
		D3DXQUATERNION m_vRot;
		OBB			m_Obb;
		virtual ~GoalItem(){}
	};
	//map<�I�u�W�F�N�g�̃|�W�V����,GoalItem>
	multimap<float,GoalItem*> m_ItemMap_All;	//�S�Ă�GoalItem

public:
	GoalObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
	/////////////////// ////////////////////
	//// �֐���     �F~GoalObject();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�j��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	~GoalObject();
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void	addGoal(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
				D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
};

/**************************************************************************
class Factory_Goal;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Goal{
public:
/**************************************************************************
 Factory_Goal(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Goal(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Goal();
//};

	void GetOBBList( float Index, list<OBB>& ObbList );
};


}
//end of namespace bomberobject.
}
//end of namespace wiz.
