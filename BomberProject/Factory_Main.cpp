////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FMagnetica
//	�t�@�C����		�FFactory_Main.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Main ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Main.h"
#include "BassItems.h"

namespace wiz{


	
/**************************************************************************
 Factory_Main ��`��
****************************************************************************/
/**************************************************************************
 Factory_Main::Factory_Main(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Main::Factory_Main(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
	try{
		
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Main::~Factory_Main();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Main::~Factory_Main(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
