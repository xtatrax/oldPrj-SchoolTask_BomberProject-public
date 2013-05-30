////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Gage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F�Q�[�W�t�@�N�g���[
//					��
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

const	int		SUPER_GAGE_MAX		= 512;
const	int		MAGNETIC_GAGE_MAX	= 256;

namespace wiz{

/************************************************
class Gage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������ �{�����V(�ҏW)
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
		wiz::OBJID id	=OBJID_UI_GAUGE	//	: ID
	);

	void	Recovery( int i_iValue, int i_iMaxValue );	//	: �G�l���M�[�̉�
	void	Consume( int i_iValue );	//	: �G�l���M�[�̏���
    void	Draw(DrawPacket& i_DrawPacket) ;
	
	RECT getRect2()const{
		return m_Rect2;
	}

	void setRect2_Right(int i_iValue){
		m_Rect2.right = i_iValue;
	}
};

/************************************************
class SuperGage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������ �{�����V(�ҏW)
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
		wiz::OBJID id	=OBJID_UI_GAUGE		//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_N : public Gage

�p�r�@�FN���E�p�̃Q�[�W
�S���ҁF�{�����V
*************************************************/
class MagneticGage_N : public Gage{
public:
	MagneticGage_N(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex,				//	: �R�A������Texture
		D3DXVECTOR3			&vScale,			//	: �L�k
		D3DXVECTOR3			&vRot,				//	: ��]
		D3DXVECTOR3			&vPos,				//	: �ʒu
		RECT*				vRect	= NULL,		//	: �`��͈�
		RECT*				vRect2	= NULL,		//	: �`��͈�
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_S : public Gage

�p�r�@�FS���E�p�̃Q�[�W
�S���ҁF�{�����V
*************************************************/
class MagneticGage_S : public Gage{
public:
	MagneticGage_S(
		LPDIRECT3DDEVICE9	pD3DDevice,			//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex,				//	: �R�A������Texture
		D3DXVECTOR3			&vScale,			//	: �L�k
		D3DXVECTOR3			&vRot,				//	: ��]
		D3DXVECTOR3			&vPos,				//	: �ʒu
		RECT*				vRect	= NULL,		//	: �`��͈�
		RECT*				vRect2	= NULL,		//	: �`��͈�
		wiz::OBJID			id		= OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Gage;

 �p�r�@�F���C���H��N���X
 �S���ҁF������ 
****************************************************************************/
class Factory_Gage{
	public:
	/**************************************************************************
	 Factory_Item(FactoryPacket* fpac);
	 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
	 �߂�l: �Ȃ�
	***************************************************************************/
		Factory_Gage(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
		~Factory_Gage();
	};
}
//end of namespace wiz.
