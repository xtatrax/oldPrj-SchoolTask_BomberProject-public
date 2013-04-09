////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FTL-String.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	����f�[�^		��
//
//
//
//
//
#pragma once
#ifndef TLIB_STRING
#define TLIB_STRING

//�W��
//#include <stdio.h>
//#include <stdarg.h>
//#include <string.h>

//std
//#include <string>

namespace TLIB{
	//����̌�����
inline int numlen(int i){
	int len = 0;
	if(i < 0) len++;
	len++;
	while(abs(i) >= 10){
		i /= 10;
		len++;
	}
	return len;
}





/////////// /////////
////void addStr(char **outSir,char **inStr)
////
////�F�FoutSir�̌���inStr��ǉ�����
////�F�F�������̈�����������i�̈悪����Ȃ���Βǉ��A������ΐ؂�l�߂����j
////
////�����F
////	char **outSir�F�ύX����������������ւ̃_�u���|�C���^
////	char **inStr �F�ǉ�������������ւ̃_�u���|�C���^
////�Ԓl�F�Ȃ�
inline void addStr(char **outSir,int addLen,char **inStr){
    //     ��
	//�i�[�����������񐔂̊m�F
	int outLine = strlen(*outSir);										//�ǉ���̊i�[�ςݕ�����
	if(addLen >=0 ){	outLine  += addLen         +2;}					//	inStrLen�Ɏw�肪�����(0�ȏ�)inStrLen���̕�������R�s�[����
	else{           	outLine  += strlen(*inStr) +2;}					//	inStrLen�Ɏw�肪�Ȃ����(!-1)inStr���Ō�܂ŃR�s�[����

	//�Â��f�[�^�̃o�b�N�A�b�v�i�f�[�^�ւ̃|�C���^�̕ی�
	char *strSwp;														//��Ɨp�L�����|�^�̐錾
	strSwp		= *outSir;												//���̕������o�b�N�A�b�v

	//�č\���i�������m�ہA�o�b�N�A�b�v�̃��X�g�A�A�f�[�^�̒ǉ��ANULL�����̑��
	*outSir		= new char[outLine];									//�������̈�̍Ċ�����
	strcpy_s(*outSir, outLine, strSwp);									//�o�b�t�@�փR�s�[
	strncat_s(*outSir, outLine, *inStr, addLen);						//�o�b�t�@�㕔�֒ǉ� 
	sprintf_s(*outSir, outLine, "%s\0", *outSir);						//�k�������̑��


	delete [] strSwp;													//�Â��̈�̔j��
	strSwp     = NULL;													//�|�C(�m�P�[�P)�m :�E'.::�E�������ċp�F����
}
inline void copyStr(char **outSir,int cpyLen,char **inStr){
    //     ��
	//	: �i�[�����������񐔂̊m�F
	int outLine = strlen(*outSir);										//	: �ǉ���̊i�[�ςݕ�����
	if(cpyLen >=0 ){	outLine  += cpyLen         +2;}					//	:	inStrLen�Ɏw�肪�����(0�ȏ�)inStrLen���̕�������R�s�[����
	else{           	outLine  += strlen(*inStr) +2;}					//	:	inStrLen�Ɏw�肪�Ȃ����(!-1)inStr���Ō�܂ŃR�s�[����

	//	: �Â��f�[�^�̃o�b�N�A�b�v�i�f�[�^�ւ̃|�C���^�̕ی�
	char *strSwp;														//	: ��Ɨp�L�����|�^�̐錾
	strSwp		= *outSir;												//	: ���̕������o�b�N�A�b�v

	//	: �č\���i�������m�ہA�o�b�N�A�b�v�̃��X�g�A�A�f�[�^�̒ǉ��ANULL�����̑��
	*outSir		= new char[outLine];									//	: �������̈�̍Ċ�����
	strcpy_s(*outSir, outLine, strSwp);									//	: �o�b�t�@�փR�s�[
	strncat_s(*outSir, outLine, *inStr, cpyLen);						//	: �o�b�t�@�㕔�֒ǉ� 
	sprintf_s(*outSir, outLine, "%s\0", *outSir);						//	: �k�������̑��


	delete [] strSwp;													//	: �Â��̈�̔j��
	strSwp     = NULL;													//	: �|�C(�m�P�[�P)�m :�E'.::�E�������ċp�F����
}
///////// /////////
//void narrow(const std::wstring &src, std::string &dest) 
//
//�F�F���C�h�����񂩂�}���`�o�C�g������
//�F�F���P�[���ˑ�
//
//�����F
//	const std::wstring &src	�F�ϊ�������������
//	std::string &dest		�F�ϊ����ꂽ������
//�Ԓl�F�Ȃ�
inline void narrow(const std::wstring &src, std::string &dest) {
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	size_t ret;
	wcstombs_s(&ret, mbs, src.length() * MB_CUR_MAX + 1, src.c_str(), src.length() * MB_CUR_MAX + 1);
	dest = mbs;
	delete [] mbs;
}
///////// /////////
//void widen(const std::string &src, std::wstring &dest) 
//
//�F�F�}���`�o�C�g�����񂩂烏�C�h������
//�F�F���P�[���ˑ�
//
//�����F
//	const std::wstring &src	�F�ϊ�������������
//	std::string &dest		�F�ϊ����ꂽ������
//�Ԓl�F�Ȃ�
inline void widen(const std::string &src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	size_t ret;
	mbstowcs_s(&ret, wcs, src.length() + 1, src.c_str(), src.length() + 1);
	dest = wcs;
	delete [] wcs;
}
}

#endif