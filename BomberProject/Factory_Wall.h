////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Wall.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Player.h"

namespace wiz{

extern class PlayerCoil ;

const int DRAWING_RANGE = 20;


/**************************************************************************
 WallObject ��`��
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveBox
//
// �S����  : �{�����V
//            �g�n ��m
// �p�r    : ��
//**************************************************************************//
class WallObject : public PrimitiveBox{
	PlayerCoil* m_pPlayerCoil ;
	Camera*	    m_pCamera;
	struct WallItem{
		D3DMATERIAL9   m_Material;
		D3DXMATRIX	   m_Matrix;
		D3DXVECTOR3    m_vScale ;
		D3DXVECTOR3	   m_vPos ;
		D3DXQUATERNION m_vRot;
		OBB			   m_Obb;
#if defined( ON_DEBUGGINGPROCESS ) 
		DrawOBB*       m_pDOB ;
#endif 
		WallItem()
#if defined( ON_DEBUGGINGPROCESS )
		:m_pDOB()
#endif
		{}
	};
	//map<�I�u�W�F�N�g�̃|�W�V����,WallItem>
	multimap<float,WallItem*> m_ItemMap_All;	//�S�Ă�WallItem
	multimap<float,WallItem*> m_ItemMap_Target; //�`��Ώۂ�WallItem
	//std::find
protected:

/////////////////// ////////////////////
//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�֐�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
	void UpdateTargetItem();

public:
	/////////////////// ////////////////////
	//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

	bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );

	

	///////////////////// ////////////////////
	////// �p�r       �Fvoid GetOBB( size_t Index, OBB& obb )
	////// �J�e�S��   �F�֐�
	////// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	////// ����       �F float Index,
	//////				 OBB& obb			//�擾����OBB
	////// �ߒl       �F�Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
	//////				�����݂�OBB��������
	////// �S����     �F�g�n ��m
	////// ���l       �F
	void GetOBBList( float Index, list<OBB>& ObbList );


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
	//// �S����     �F�{�����V
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
	//// �S����     �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid AddWall( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �FWall�̒ǉ�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////		    �F  D3DXVECTOR3 &vScale				//�g��k��
	////		    �F  D3DXVECTOR3 &vRot				//��]�p
	////		    �F  D3DXVECTOR3 &vPos				//�ʒu
	////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	void AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);


	bool HitTest3DAddWall( MultiBox* pBox, size_t& Index, D3DXVECTOR3& Vec, D3DXVECTOR3& ElsePos );

};

//class WallManager {
//	typedef multimap< float, Wall > WALLCONTAINER ;
//	WALLCONTAINER m_Walls ;
//
//public:
//	WallManager();
//
//};
//
/**************************************************************************
 class Factory_Wall;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Wall{
public:
/**************************************************************************
 Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Wall(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Wall();
};
}
//end of namespace wiz.
