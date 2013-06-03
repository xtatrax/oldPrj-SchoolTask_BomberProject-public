////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Description.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�����t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Description ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{

/**************************************************************************
class StartSprite;

�p�r�@�F�J�n���̃X�^�[�g��
�S���ҁF������
**************************************************************************/
class StartSprite : public SpriteObject{
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	float		m_vRelayPosY;
	int			m_iTime;
	PlayerCoil*	m_pCoil;
	bool		m_bFirst;
public:
	StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*	Rect	= NULL);

	~StartSprite();
	void	Draw( DrawPacket& i_DrawPacket );
	void	Update( UpdatePacket& i_UpdatePacket );
};

/**************************************************************************
class Description;

�p�r�@�F�������̑}��
�S���ҁF������
**************************************************************************/
class Description : public PrimitiveBox{
	Camera*			m_pCamera;
	PlayerCoil*		m_pCoil;
	struct DescItem{
		D3DMATERIAL9	m_Material;
		D3DXMATRIX		m_Matrix;
		D3DXVECTOR3		m_vScale ;
		D3DXVECTOR3		m_vPos ;
		D3DXQUATERNION	m_vRot;
		COIL_STATE		m_State;
		bool			m_bCanDisplay;
		bool			m_bDisplay;
		virtual ~DescItem(){}
	};

	//map<�I�u�W�F�N�g�̃|�W�V����,WallItem>
	multimap<float,DescItem*> m_ItemMap_Desc;	//�S�Ă�DescItem
	multimap<float,DescItem*> m_ItemMap_Target; //�`��Ώۂ�DescItem
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
	Description(LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

	/////////////////// ////////////////////
	//// �p�r       �F~Description;
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �g�I��
	//// ���l       �F
	~Description();

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
	void AddDesc(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,COIL_STATE state,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

};

/**************************************************************************
class Factory_Description;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Description{
public:
/**************************************************************************
 Factory_Description(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Description(FactoryPacket* fpac);
/**************************************************************************
 ~Factory_Description();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Description();
};

}
//end of namespace wiz.
