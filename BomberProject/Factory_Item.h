////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Item;
//		class Bar;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

const	float	VanishArea	= 0.2f;		//	: �A�C�e���������G���A
const	float	SuctionArea	= 5.0f;		//	: �A�C�e�����z�����͈�
const	float	SpeedRate	= 0.05f;	//	: �A�C�e���̑��������{��

namespace wiz{

/******************************************************
class	Item	: public PrimitiveSphere
�p�r : �A�C�e��
*******************************************************/
class	Item	: public PrimitiveSphere {
protected:
	struct BallItem{
		//�}�e���A��
		D3DMATERIAL9 m_Material;
		//�}�g���b�N�X
		D3DXMATRIX m_mMatrix;
		//�T�C�Y
		D3DXVECTOR3	m_Size;
		//�ΏۂƂ̋���
		float	m_fDistance;
		//�I�u�W�F�N�g�̈ʒu(���S)
		D3DXVECTOR3	m_Pos;
		//�h���N���X������Ă�Clear()�֐���
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~BallItem(){}
	};
	multimap<float,BallItem*> m_ItemMap_All;	//�S�Ă�BallItem
public:
	Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void	addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
};
/************************************************
class Bar : public SpriteObject
�p�r : �G�l���M�[�o�[
*************************************************/
class Bar : public SpriteObject{
	int m_Time;
public:
	Bar(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTex,		//	: �R�A������Texture
		D3DXVECTOR3 &vScale,			//	: �L�k
		D3DXVECTOR3 &vRot,				//	: ��]
		D3DXVECTOR3 &vPos,				//	: �ʒu
		D3DXVECTOR3 &vDirOffset,		//	: �`��I�t�Z�b�g
		RECT* vRect = NULL,				//	: �`��͈�
		wiz::OBJID id	=OBJID_UNK		//	: ID
	);

	void	Recovery();	//	: �G�l���M�[�̉�
	void	Consume();	//	: �G�l���M�[�̏���
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
