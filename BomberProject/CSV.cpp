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
	void WStrToWStrTokenList(wstring& line,vector<wstring>& wstrvec,wchar_t delimiter){
		wstring::size_type i = 0;
		wstring wks(L"");
		for(i = 0;i < line.size();i++){
			if(line[i] == delimiter){
				wstrvec.push_back(wks);
				wks = L"";
			}
			else{
				wks += line[i];
			}
		}
		wstrvec.push_back(wks);
	}
	void StrToStrTokenList(string& line,vector<string>& strvec,wchar_t delimiter){
		string::size_type i = 0;
		string wks("");
		for(i = 0;i < line.size();i++){
			if(line[i] == delimiter){
				strvec.push_back(wks);
				wks = "";
			}
			else{
				wks += line[i];
			}
		}
		strvec.push_back(wks);
	}

	void readcsv(wstring FileName,vector<vector<wstring>>& vecvecData)
	{
		
		//CSV�̓ǂݍ���
		std::locale loc("japanese");
		std::wfstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV�ǂݍ��݃G���[",L"�G���[",MB_OK);
			return;
		}
		//�ȉ��d�v�I�I�I�I
		//����ɂ��SJIS�t�@�C����UNICODE���ŊJ����B
		//�G���[�`�F�b�N�͂��łɍς�ł�����̂Ƃ���
		ifs.imbue(loc);
		wstring line;
		//�h�L�������g�ɓn��1�s�̔z��
		vector<wstring> wstrvec;
		int w = 0 , h = 0;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//��L�̃��[�e�B���e�B�֐��g�p
			WStrToWStrTokenList(line,wstrvec,L',');
			//list<wstring>::iterator it;
			//for(it = wstrvec.begin();it != wstrvec.end();it++){
				vecvecData.push_back(wstrvec);
			//}
			wstrvec.clear();
		}	
	}
	void readcsv(wstring FileName,vector<vector<string>>& vecvecData)
	{
		
		//CSV�̓ǂݍ���
		std::locale loc("japanese");
		std::fstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"�ǂݍ��݃G���[",L"�G���[",MB_OK);
			return;
		}
		//�ȉ��d�v�I�I�I�I
		//����ɂ��SJIS�t�@�C����UNICODE���ŊJ����B
		//�G���[�`�F�b�N�͂��łɍς�ł�����̂Ƃ���
		ifs.imbue(loc);
		string line;
		//�h�L�������g�ɓn��1�s�̔z��
		vector<string> strvec;
		int w = 0 , h = 0;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//��L�̃��[�e�B���e�B�֐��g�p
			StrToStrTokenList(line,strvec,',');
			//list<wstring>::iterator it;
			//for(it = wstrvec.begin();it != wstrvec.end();it++){
				vecvecData.push_back(strvec);
			//}
			strvec.clear();
		}	
	}
}