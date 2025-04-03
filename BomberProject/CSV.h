////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：CSV.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：
//					▼
//	namespace wiz;
//		bool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);
//		bool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
//
#pragma once

namespace wiz{

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
	bool readcsv(wstring i_wsFileName,vector<vector<wstring>>& o_vecvecData);

	/////////////////// ////////////////////
	//// 関数名     ：bool readcsv(wstring i_wsFileName,vector<vector<string>>& o_vecvecData);
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
	bool readcsv(wstring FileName,vector<vector<string>>& vecvecData);
}
