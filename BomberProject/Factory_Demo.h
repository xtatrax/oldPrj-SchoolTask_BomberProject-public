////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Load ;
//		class Factory_Demo ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Demo.h"
#include "Factory_Sound.h"


namespace wiz{
namespace bomberobject{

/**************************************************************************
class Factory_Demo;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Demo{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Demo(FactoryPacket* fpac,Command* Com);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Demo();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
