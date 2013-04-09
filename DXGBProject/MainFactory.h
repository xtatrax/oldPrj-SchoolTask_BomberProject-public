////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FMainFactory.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class MainFactory ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

namespace wiz{




/**************************************************************************
 class MainFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
class MainFactory{
public:
/**************************************************************************
 MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~MainFactory();
};
}
//end of namespace wiz.
