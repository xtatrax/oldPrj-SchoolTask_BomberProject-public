////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage_Test.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�e�X�g�p�̃X�e�[�W
//					�F��Scene.cpp Scene::CommandTranslator �֐��Ŏ��̉�����܂�
//					�F��Scene.cpp Scene::Update / AnotherTargetRender / Draw �֐�����Ă΂�܂�
//					��
//	namespace wiz;
//	;
//
#include "Stage.h"
namespace wiz{

/**************************************************************************
 class DebugStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class DebugStage_TATRA : public Stage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugStage_TATRA(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};

/**************************************************************************
 class DebugStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class DebugStage_Loader : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugStage_Loader(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};

};