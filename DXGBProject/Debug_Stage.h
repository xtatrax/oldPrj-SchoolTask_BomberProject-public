////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FDebug_Stage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�f�o�b�N�p�X�e�[�W
//					��
//	namespace wiz;
//		class DebugStage : public MenuStage;
//		class DebugMenu  : public MenuStage;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
namespace wiz{

/**************************************************************************
 class DebugStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class DebugStage : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


/**************************************************************************
 class DebugMenu : public Stage;
 �p�r: �f�o�b�O�p�X�e�[�W
 �@�@�i������ʂ֒��ڈړ��ł���j
****************************************************************************/
class DebugMenu : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


//end of namespace wiz.
}
