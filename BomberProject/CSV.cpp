////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FCSV.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		void WStrToWStrTokenList(wstring& line,list<wstring>&wstrvec,wchar_t delimiter) ;
//		void readcsv(wstring FileName,list<list<wstring>>& vecvecData) ;
//
#include "StdAfx.h"
#include "CSV.h"

namespace wiz{
	/////////////////// ////////////////////
	//// �֐���     �Fvoid WStrToWStrTokenList(wstring& line,vector<wstring>& wstrvec,wchar_t delimiter)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F
	//// ����       �F  wstring& i_line              //  : ��s�̃f�[�^
	////            �F  vector<wstring>& o_wstrvec   //  : �Z�����Ƃɕ������ꂽ�f�[�^
	////            �F  wchar_t delimiter            //  : ��؂蕶��
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	void WStrToWStrTokenList(wstring& line,vector<wstring>& wstrvec,wchar_t delimiter){
		wstring::size_type i = 0;
		wstring wks(L"");
		//	: ���C���̏I���܂Ń��[�v
		for(i = 0;i < line.size();i++){

			if(line[i] == delimiter){
				//	: ��؂蕶���Ȃ炻��܂ł̕�����o�^
				wstrvec.push_back(wks);
				//	: �����ă��[�N��������
				wks = L"";
			}
			else{
				//	: ��؂蕶������Ȃ���΃��[�N�֒ǉ�
				wks += line[i];
			}
		}
		wstrvec.push_back(wks);
	}
	/////////////////// ////////////////////
	//// �֐���     �Fvoid StrToStrTokenList(string& line,vector<string>& strvec,wchar_t delimiter)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F
	//// ����       �F  wstring& i_line              //  : ��s�̃f�[�^
	////            �F  vector<string>& o_wstrvec    //  : �Z�����Ƃɕ������ꂽ�f�[�^
	////            �F  wchar_t delimiter            //  : ��؂蕶��
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	void StrToStrTokenList(string& line,vector<string>& strvec,wchar_t delimiter){
		string::size_type i = 0;
		string wks("");
		//	: ���C���̏I���܂Ń��[�v
		for(i = 0;i < line.size();i++){
			if(line[i] == delimiter){
				//	: ��؂蕶���Ȃ炻��܂ł̕�����o�^
				strvec.push_back(wks);
				//	: �����ă��[�N��������
				wks = "";
			}
			else{
				//	: ��؂蕶������Ȃ���΃��[�N�֒ǉ�
				wks += line[i];
			}
		}
		strvec.push_back(wks);
	}

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
	bool readcsv(wstring FileName,vector<vector<wstring>>& vecvecData)
	{
		
		//CSV�̓ǂݍ���
		std::wfstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV�ǂݍ��݃G���[\n�t�@�C���p�X���m�F���Ă�������",L"�G���[",MB_OK);
			return false;
		}

		//�ȉ��d�v�I�I�I�I
		//����ɂ��SJIS�t�@�C����UNICODE���ŊJ����B
		//�G���[�`�F�b�N�͂��łɍς�ł�����̂Ƃ���
		wstring line;
		//�h�L�������g�ɓn��1�s�̔z��
		vector<wstring> wstrvec;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//��L�̃��[�e�B���e�B�֐��g�p
			WStrToWStrTokenList(line,wstrvec,L',');
			vecvecData.push_back(wstrvec);

			wstrvec.clear();
		}	
		return true ;
	}

	/////////////////// ////////////////////
	//// �֐���     �Fbool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
	//// �J�e�S��   �F�֐�
	//// �p�r       �FCSV�f�[�^��vector<vector<string>>�Ƃ��ēǂݍ��݂܂�
	//// ����       �F  wstring                   i_wsFileName    //  : �ǂݍ��݂���CSV�t�@�C��
	////            �F  vector<vector<string>>&   o_vecvecData    //  : �ǂݍ��񂾃f�[�^
	//// �ߒl       �Ftrue   : �ǂݍ��݂ɐ���
	////            �Ffalse  : �ǂݍ��݂Ɏ��s
	//// �S��       �F���� �O
	//// ���l       �F����񐔂��s�����̃f�[�^��ǂݍ������Ƃ���ƃo�O��܂��̂�
	////            �F�f�[�^���쐬����Ƃ��ɂ͂����ӂ�������
	////
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData)
	{
		
		//CSV�̓ǂݍ���
		std::fstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV�ǂݍ��݃G���[\n�t�@�C���p�X���m�F���Ă�������",L"�G���[",MB_OK);
			return false;
		}

		//�ȉ��d�v�I�I�I�I
		//����ɂ��SJIS�t�@�C����UNICODE���ŊJ����B
		//�G���[�`�F�b�N�͂��łɍς�ł�����̂Ƃ���
		string line;
		//�h�L�������g�ɓn��1�s�̔z��
		vector<string> strvec;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//��L�̃��[�e�B���e�B�֐��g�p
			StrToStrTokenList(line,strvec,',');
			vecvecData.push_back(strvec);
			strvec.clear();
		}	
		return true ;
	}
}