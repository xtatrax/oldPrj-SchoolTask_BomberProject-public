////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Item;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"

const	float		VanishArea			= 1.5f;		//	: �A�C�e���������G���A
const	float		SuctionArea			= 5.0f;		//	: �A�C�e�����z�����͈�
const	float		SpeedRate			= 0.05f;	//	: �A�C�e���̑��������{��
const	float		RECOVERY_POINT		= 0.01f;
const	float		RECOVERY_POINT_L	= 0.10f;

const	float		ITEM_TYPE_NULL		= 0.0f;
const	D3DXVECTOR3 ITEM_SCALE			= D3DXVECTOR3(0.5f,0.5f,0.5f);		
const   float		ItemDiffusionRate	= 1.0f;
//enum ITEM_TYPE{
//	ITEM_TYPE_NULL,
//	ITEM_TYPE_RECOVETY,
//	ITEM_TYPE_RECOVETY_BIG
//};

namespace wiz{
namespace bomberobject{

/******************************************************
class  Item : public PrimitiveSphere

�p�r�@�F�A�C�e��
�S���ҁF������
�ҏW  �F���� �O
*******************************************************/
class	Item	: public PrimitiveSphere {
protected:
	PlayerCoil*	m_pPlayerCoil	;
	SuperGage*	m_pSuperGage	;
	Camera*		m_pCamera		;
	struct BallItem{
		D3DMATERIAL9	m_Material	;		//�}�e���A��
		D3DXMATRIX		m_mMatrix	;		//�}�g���b�N�X
		D3DXVECTOR3		m_Size		;		//�T�C�Y
		float			m_fDistance	;		//�ΏۂƂ̋���
		D3DXVECTOR3		m_Pos		;		//�I�u�W�F�N�g�̈ʒu(���S)
		float			m_fMapKey	;
		bool			m_bHidden	;
		//float			m_fItemType ;
		float			m_fRecoveryPoint;
		//�h���N���X������Ă�Clear()�֐���
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~BallItem(){}
	};
	typedef multimap<float,BallItem*>	ALLCONTAINER	;
	typedef list<BallItem*>				TARGETCONTAINER ;
	ALLCONTAINER		m_ItemMap_All		;	//�S�Ă�BallItem
	TARGETCONTAINER		m_ItemMap_Target	;	//�`��Ώۂ̃A�C�e��
	void	setDrawTarget();
public:
	Item(FactoryPacket* fpac,LPTATRATEXTURE pTexture, wiz::OBJID id);
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
					D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,
					float itemType = RECOVERY_POINT);
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
//end of namespace bomberobject.
}
//end of namespace wiz.
