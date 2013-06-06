////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：CSV.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		void readcsv(wstring FileName,list<list<wstring>>& listlistData) ;
//
#pragma once

namespace wiz{
	bool readcsv(wstring FileName,vector<vector<wstring>>& vecvecData);
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData);
}
