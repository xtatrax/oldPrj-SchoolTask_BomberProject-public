////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CustomButtonA.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�FButtonSprite��Custom��
//					�F�^�C�g���Ƃ��Ŏg�p
//					��
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#pragma once

#include "StdAfx.h"


namespace wiz{
namespace bomberobject{

/**************************************************************************
 class Factory_CustomButtonA;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_CustomButtonA{
public:
	/**************************************************************************
	 Factory_CustomButtonA(
		FactoryPacket* fpac //�p�P�b�g�f�[�^
	);
	 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
	 �߂�l: �Ȃ�
	***************************************************************************/
	Factory_CustomButtonA( FactoryPacket* fpac );
	/**************************************************************************
	 ~MyFactory();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
	~Factory_CustomButtonA();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
