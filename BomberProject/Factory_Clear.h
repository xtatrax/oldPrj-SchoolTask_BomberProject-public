////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Clear.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject;
//		class Factory_Clear ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{
/**************************************************************************
class Factory_Clear;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Clear{
public:
/**************************************************************************
 Factory_Clear(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Clear(FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Clear();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
