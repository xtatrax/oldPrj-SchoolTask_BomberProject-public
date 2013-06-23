////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FStage_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�^�C�g���X�e�[�W
//					��
//	namespace wiz;
//		class TitleStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Stage.h"
#include "Scene.h"
#include "Factory_Title.h"

namespace wiz{
namespace stage{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class TitleStage : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class TitleStage : public MenuStage{
public:	
/**************************************************************************
 TitleStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	TitleStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage = NULL);
/**************************************************************************
TitleStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~TitleStage();
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace stage.
}
//end of namespace wiz.
