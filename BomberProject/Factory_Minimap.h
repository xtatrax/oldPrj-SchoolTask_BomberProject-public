////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Minimap.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Minimap ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Player.h"

namespace wiz{
namespace bomberobject{

class MiniMap : public Object{
	LPDIRECT3DTEXTURE9	m_Texture ;
public:
	
};
/**************************************************************************
 class Factory_Minimap;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Minimap{
public:
/**************************************************************************
 Factory_Minimap(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Minimap(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Minimap();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
