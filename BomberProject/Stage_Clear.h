////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Result.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�N���A�X�e�[�W
//					��
//	namespace wiz;
//		class ClearStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class ClearStage : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class ClearStage : public Stage{
public:	
/**************************************************************************
 ClearStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	ClearStage(LPDIRECT3DDEVICE9 pD3DDevice, int iDeadCount, int iMaxPosY, Stage* pStage = NULL);
/**************************************************************************
ClearStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~ClearStage();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace wiz.
