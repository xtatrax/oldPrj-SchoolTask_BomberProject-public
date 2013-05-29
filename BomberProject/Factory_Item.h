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
#include "Factory_Player.h"

const	float	VanishArea	= 1.0f;		//	: �A�C�e���������G���A
const	float	SuctionArea	= 5.0f;		//	: �A�C�e�����z�����͈�
const	float	SpeedRate	= 0.05f;	//	: �A�C�e���̑��������{��
const	int		GAGE_MAX	= 254;
const	int		RECOVERY_POINT	= 5;

namespace wiz{

/******************************************************
class  Item : public PrimitiveSphere

�p�r�@�F�A�C�e��
�S���ҁF������
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
	/////////////////// ////////////////////
	//// �֐���     �F~Item();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�j��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	~Item();

    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void	addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient);
};
/************************************************
class Gage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������
*************************************************/
class Gage : public SpriteObject{
	Rect	m_Rect;
	Rect	m_Rect2;
public:
	Gage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTex,		//	: �R�A������Texture
		D3DXVECTOR3 &vScale,			//	: �L�k
		D3DXVECTOR3 &vRot,				//	: ��]
		D3DXVECTOR3 &vPos,				//	: �ʒu
		D3DXVECTOR3 &vDirOffset,		//	: �`��I�t�Z�b�g
		RECT* vRect  = NULL,				//	: �`��͈�
		RECT* vRect2 = NULL,				//	: �`��͈�
		wiz::OBJID id	=OBJID_UNK		//	: ID
	);

	void	Recovery( int i_iValue );	//	: �G�l���M�[�̉�
	void	Consume( int i_iValue );	//	: �G�l���M�[�̏���
    void	Draw(DrawPacket& i_DrawPacket) ;
	
	RECT getRect2()const{
		return m_Rect2;
	}
};

/************************************************
class SuperGage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������
*************************************************/
class SuperGage : public Gage{
public:
	SuperGage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTex,		//	: �R�A������Texture
		D3DXVECTOR3 &vScale,			//	: �L�k
		D3DXVECTOR3 &vRot,				//	: ��]
		D3DXVECTOR3 &vPos,				//	: �ʒu
		RECT* vRect  = NULL,			//	: �`��͈�
		RECT* vRect2 = NULL,			//	: �`��͈�
		wiz::OBJID id	=OBJID_UNK		//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage : public SpriteObject

�p�r�@�F���E�p�̃Q�[�W
�S���ҁF������
*************************************************/
class MagneticGage : public Gage{
public:
	MagneticGage(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTex,		//	: �R�A������Texture
		D3DXVECTOR3 &vScale,			//	: �L�k
		D3DXVECTOR3 &vRot,				//	: ��]
		D3DXVECTOR3 &vPos,				//	: �ʒu
		RECT* vRect  = NULL,				//	: �`��͈�
		RECT* vRect2 = NULL,				//	: �`��͈�
		wiz::OBJID id	=OBJID_UNK		//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Item;

 �p�r�@�F���C���H��N���X
 �S���ҁF������
****************************************************************************/
class Factory_Item{
public:
/**************************************************************************
 Factory_Item(FactoryPacket* fpac);
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
