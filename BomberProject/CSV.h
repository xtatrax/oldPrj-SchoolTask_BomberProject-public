////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FCSV.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		void readcsv(wstring FileName,list<list<wstring>>& listlistData) ;
//
#pragma once

namespace wiz{
	bool readcsv(wstring FileName,vector<vector<wstring>>& vecvecData);
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData);
}
