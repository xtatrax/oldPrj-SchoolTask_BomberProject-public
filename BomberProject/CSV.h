////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FCSV.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		bool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);
//		bool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
//
#pragma once

namespace wiz{

	/////////////////// ////////////////////
	//// �֐���     �Fbool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);
	//// �J�e�S��   �F�֐�
	//// �p�r       �FCSV�f�[�^��vector<vector<wstring>>�Ƃ��ēǂݍ��݂܂�
	//// ����       �F  wstring                   i_wsFileName    //  : �ǂݍ��݂���CSV�t�@�C��
	////            �F  vector<vector<wstring>>&  o_vecvecData    //  : �ǂݍ��񂾃f�[�^
	//// �ߒl       �Ftrue   : �ǂݍ��݂ɐ���
	////            �Ffalse  : �ǂݍ��݂Ɏ��s
	//// �S��       �F���� �O
	//// ���l       �F����񐔂��s�����̃f�[�^��ǂݍ������Ƃ���ƃo�O��܂��̂�
	////            �F�f�[�^���쐬����Ƃ��ɂ͂����ӂ�������
	////
	bool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);

	/////////////////// ////////////////////
	//// �֐���     �Fbool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
	//// �J�e�S��   �F�֐�
	//// �p�r       �FCSV�f�[�^��vector<vector<wstring>>�Ƃ��ēǂݍ��݂܂�
	//// ����       �F  wstring                   i_wsFileName    //  : �ǂݍ��݂���CSV�t�@�C��
	////            �F  vector<vector<wstring>>&  o_vecvecData    //  : �ǂݍ��񂾃f�[�^
	//// �ߒl       �Ftrue   : �ǂݍ��݂ɐ���
	////            �Ffalse  : �ǂݍ��݂Ɏ��s
	//// �S��       �F���� �O
	//// ���l       �F����񐔂��s�����̃f�[�^��ǂݍ������Ƃ���ƃo�O��܂��̂�
	////            �F�f�[�^���쐬����Ƃ��ɂ͂����ӂ�������
	////
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData);
}
