////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FCommand.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�R�}���h�̂ā[��
//					��
//	namespace wiz;
//		�Q�[�����b�Z�[�W��
//		struct Command ;
//
#pragma once

namespace wiz{

/**************************************************************************
 struct Command;
 �p�r: �V�[�����A�X�e�[�W���ł���肳���R�}���h
 ���R�}���h���e�̒�`�́A�e�R���e���c�ɂ܂�����
****************************************************************************/
struct Command{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = 0;
	}
	~Command(){
		Clear();
	}
};
}