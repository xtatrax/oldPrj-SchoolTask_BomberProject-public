////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Demo.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F���[�h�t�@�N�g���[
//					��
//	namespace wiz;
//		class Load ;
//		class Factory_Demo ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Demo.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Demo ��`��
****************************************************************************/
/**************************************************************************
 Factory_Demo::Factory_Demo(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Demo::Factory_Demo(FactoryPacket* fpac,Command* Com){
	try{

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Demo::~Factory_Demo();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Demo::~Factory_Demo(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
