////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{

	class	Item	: public PrimitiveSphere {
	protected:
			struct BallItem{
				//�}�e���A��
				D3DMATERIAL9 m_Material;
				//�}�g���b�N�X
				D3DXMATRIX m_mMatrix;
				//�T�C�Y
				D3DXVECTOR3	m_Size;
				//�I�u�W�F�N�g�̈ʒu(���S)
				D3DXVECTOR3	m_Pos;
				//�h���N���X������Ă�Clear()�֐���
				//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
				virtual ~BallItem(){}
		};
		vector<BallItem*> m_ItemVec;
	public:
		Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id);
		~Item();
		void	Draw(DrawPacket& i_DrawPacket) ;
		void	Update(UpdatePacket& i_UpdatePacket);
		void	addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
		void	Suction();
	};

//////////////////////////////////////////////////
// Bar
//////////////////////////////////////////////////
	class Bar : public SpriteObject{
		int m_Time;
	public:
	/////////////////// ////////////////////
	//// �J�e�S��   �F�R���X�g���N�^
		Bar(
			LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
			LPDIRECT3DTEXTURE9 pTex,				//	: �R�A������Texture
			D3DXVECTOR3 &vScale,						//	: �L�k
			D3DXVECTOR3 &vRot,							//	: ��]
			D3DXVECTOR3 &vPos,							//	: �ʒu
			D3DXVECTOR3 &vDirOffset,					//	: ������\���O�p�̕`��I�t�Z�b�g
			RECT* vRect = NULL,						//	: �`��͈�
			wiz::OBJID id	=OBJID_UNK		//	: ID
		);

		void	Recovery();
		void	Consume();
		void	Draw(DrawPacket& i_DrawPacket) ;
	};


/**************************************************************************
 class Factory_Item;
 �p�r: ���C���H��N���X
****************************************************************************/
	class Factory_Item{
	public:
	/**************************************************************************
	 Factory_Item(
		LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
		vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
		TextureManager& TexMgr		//�e�N�X�`���̔z��
	);
	 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
	 �߂�l: �Ȃ�
	***************************************************************************/
		Factory_Item(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
		~Factory_Item();
	};
}
//end of namespace wiz.
