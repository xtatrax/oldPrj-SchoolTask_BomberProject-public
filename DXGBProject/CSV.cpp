////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：CSV.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
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
		
		//CSVの読み込み
		std::locale loc("japanese");
		std::wfstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV読み込みエラー",L"エラー",MB_OK);
			return;
		}
		//以下重要！！！！
		//これによりSJISファイルがUNICODE環境で開ける。
		//エラーチェックはすでに済んでいるものとする
		ifs.imbue(loc);
		wstring line;
		//ドキュメントに渡す1行の配列
		vector<wstring> wstrvec;
		int w = 0 , h = 0;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//上記のユーティリティ関数使用
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
		
		//CSVの読み込み
		std::locale loc("japanese");
		std::fstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"読み込みエラー",L"エラー",MB_OK);
			return;
		}
		//以下重要！！！！
		//これによりSJISファイルがUNICODE環境で開ける。
		//エラーチェックはすでに済んでいるものとする
		ifs.imbue(loc);
		string line;
		//ドキュメントに渡す1行の配列
		vector<string> strvec;
		int w = 0 , h = 0;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//上記のユーティリティ関数使用
			StrToStrTokenList(line,strvec,',');
			//list<wstring>::iterator it;
			//for(it = wstrvec.begin();it != wstrvec.end();it++){
				vecvecData.push_back(strvec);
			//}
			strvec.clear();
		}	
	}
}