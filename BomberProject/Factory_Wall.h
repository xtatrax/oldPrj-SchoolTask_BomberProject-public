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

namespace wiz{

extern class PlayerCoil ;

class WallObject : public SpriteObject{
	static PlayerCoil* m_pPlayerCoil ;
	D3DXVECTOR3 m_vPos ;
public:
	WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
			Color color = 0xFFFFFFFF,wiz::OBJID id = OBJID_2D_WALL);

	bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );
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
