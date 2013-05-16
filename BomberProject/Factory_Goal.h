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
#include "Factory_Goal.h"
#include "Factory_Player.h"

namespace wiz{

/******************************************************
<<<<<<< HEAD
class Item : public PrimitiveSphere

�p�r�@�F�A�C�e��
�S���ҁF������
=======
class	Item	: public PrimitiveSphere
�p�r : �A�C�e��
>>>>>>> workspace
*******************************************************/
class	GoalObject	:public PrimitiveBox{
	PlayerCoil*	m_pCoil;
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
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);
	void addGoal(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
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
	~Factory_Goal(){};
//};

	void GetOBBList( float Index, list<OBB>& ObbList );
};


}
//end of namespace wiz.
