////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Minimap.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Minimap ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Minimap.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{


/**************************************************************************
 Factory_Minimap ��`��
****************************************************************************/
/**************************************************************************
 Factory_Minimap::Factory_Minimap(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Minimap::Factory_Minimap(FactoryPacket* fpac){
		try{
		}
		catch(...){
			//��throw
			throw;
		}
	}

/**************************************************************************
 Factory_Minimap::~Factory_Minimap();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Minimap::~Factory_Minimap(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace bomberobject.
}//end of namespace wiz.