////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FMainFactory.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class MainFactory ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "MainFactory.h"
#include "BassItems.h"

namespace wiz{


	
/**************************************************************************
 MainFactory ��`��
****************************************************************************/
/**************************************************************************
 MainFactory::MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
MainFactory::MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
	try{
		
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 MainFactory::~MainFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MainFactory::~MainFactory(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
