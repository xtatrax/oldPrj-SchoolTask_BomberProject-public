////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Pray.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�v���C�X�e�[�W
//					��
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
namespace wiz{
class PlayStage;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class PlayStage : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class PlayOpeningStage : public Stage{
public:	
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	PlayOpeningStage(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~PlayOpeningStage();
/**************************************************************************
 void PlayStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_Time,const CONTROLER_STATE* pCntlState,Command& Com);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice, Tempus2 *i_Time, Command &Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class PlayStage : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class PlayStage : public Stage{
	friend class PlayOpeningStage;
public:	
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage = NULL);
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~PlayStage();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace wiz.
