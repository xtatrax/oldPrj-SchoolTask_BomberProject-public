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
	/////////////////// ////////////////////
	//// 関数名     ：void WStrToWStrTokenList(wstring& line,vector<wstring>& wstrvec,wchar_t delimiter)
	//// カテゴリ   ：関数
	//// 用途       ：
	//// 引数       ：  wstring& i_line              //  : 一行のデータ
	////            ：  vector<wstring>& o_wstrvec   //  : セルごとに分解されたデータ
	////            ：  wchar_t delimiter            //  : 区切り文字
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void WStrToWStrTokenList(wstring& line,vector<wstring>& wstrvec,wchar_t delimiter){
		wstring::size_type i = 0;
		wstring wks(L"");
		//	: ラインの終わりまでループ
		for(i = 0;i < line.size();i++){

			if(line[i] == delimiter){
				//	: 区切り文字ならそれまでの文字を登録
				wstrvec.push_back(wks);
				//	: そしてワークを初期化
				wks = L"";
			}
			else{
				//	: 区切り文字じゃなければワークへ追加
				wks += line[i];
			}
		}
		wstrvec.push_back(wks);
	}
	/////////////////// ////////////////////
	//// 関数名     ：void StrToStrTokenList(string& line,vector<string>& strvec,wchar_t delimiter)
	//// カテゴリ   ：関数
	//// 用途       ：
	//// 引数       ：  wstring& i_line              //  : 一行のデータ
	////            ：  vector<string>& o_wstrvec    //  : セルごとに分解されたデータ
	////            ：  wchar_t delimiter            //  : 区切り文字
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void StrToStrTokenList(string& line,vector<string>& strvec,wchar_t delimiter){
		string::size_type i = 0;
		string wks("");
		//	: ラインの終わりまでループ
		for(i = 0;i < line.size();i++){
			if(line[i] == delimiter){
				//	: 区切り文字ならそれまでの文字を登録
				strvec.push_back(wks);
				//	: そしてワークを初期化
				wks = "";
			}
			else{
				//	: 区切り文字じゃなければワークへ追加
				wks += line[i];
			}
		}
		strvec.push_back(wks);
	}

	/////////////////// ////////////////////
	//// 関数名     ：bool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);
	//// カテゴリ   ：関数
	//// 用途       ：CSVデータをvector<vector<wstring>>として読み込みます
	//// 引数       ：  wstring                   i_wsFileName    //  : 読み込みたいCSVファイル
	////            ：  vector<vector<wstring>>&  o_vecvecData    //  : 読み込んだデータ
	//// 戻値       ：true   : 読み込みに成功
	////            ：false  : 読み込みに失敗
	//// 担当       ：鴫原 徹
	//// 備考       ：現状列数が不揃いのデータを読み込もうとするとバグりますので
	////            ：データを作成するときにはご注意ください
	////
	bool readcsv(wstring FileName,vector<vector<wstring>>& vecvecData)
	{
		
		//CSVの読み込み
		std::wfstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV読み込みエラー\nファイルパスを確認してください",L"エラー",MB_OK);
			return false;
		}

		//以下重要！！！！
		//これによりSJISファイルがUNICODE環境で開ける。
		//エラーチェックはすでに済んでいるものとする
		wstring line;
		//ドキュメントに渡す1行の配列
		vector<wstring> wstrvec;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//上記のユーティリティ関数使用
			WStrToWStrTokenList(line,wstrvec,L',');
			vecvecData.push_back(wstrvec);

			wstrvec.clear();
		}	
		return true ;
	}

	/////////////////// ////////////////////
	//// 関数名     ：bool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
	//// カテゴリ   ：関数
	//// 用途       ：CSVデータをvector<vector<string>>として読み込みます
	//// 引数       ：  wstring                   i_wsFileName    //  : 読み込みたいCSVファイル
	////            ：  vector<vector<string>>&   o_vecvecData    //  : 読み込んだデータ
	//// 戻値       ：true   : 読み込みに成功
	////            ：false  : 読み込みに失敗
	//// 担当       ：鴫原 徹
	//// 備考       ：現状列数が不揃いのデータを読み込もうとするとバグりますので
	////            ：データを作成するときにはご注意ください
	////
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData)
	{
		
		//CSVの読み込み
		std::fstream ifs;
		ifs.open(FileName.c_str());
		if(!ifs){
			::MessageBox(NULL,L"CSV読み込みエラー\nファイルパスを確認してください",L"エラー",MB_OK);
			return false;
		}

		//以下重要！！！！
		//これによりSJISファイルがUNICODE環境で開ける。
		//エラーチェックはすでに済んでいるものとする
		string line;
		//ドキュメントに渡す1行の配列
		vector<string> strvec;
		while(getline(ifs,line)){
			if( line.size() == 0 ){
				break;
			}
			//上記のユーティリティ関数使用
			StrToStrTokenList(line,strvec,',');
			vecvecData.push_back(strvec);
			strvec.clear();
		}	
		return true ;
	}
}