////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：TL-String.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包データ		▼
//
//
//
//
//
#pragma once
#ifndef TLIB_STRING
#define TLIB_STRING

//標準
//#include <stdio.h>
//#include <stdarg.h>
//#include <string.h>

//std
//#include <string>

namespace TLIB{
	//数列の桁差数
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
////：：outSirの後ろにinStrを追加する
////：：メモリ領域も調整される（領域が足りなければ追加、多ければ切り詰めされる）
////
////引数：
////	char **outSir：変更を加えたい文字列へのダブルポインタ
////	char **inStr ：追加したい文字列へのダブルポインタ
////返値：なし
inline void addStr(char **outSir,int addLen,char **inStr){
    //     ◇
	//格納したい文字列数の確認
	int outLine = strlen(*outSir);										//追加先の格納済み文字列数
	if(addLen >=0 ){	outLine  += addLen         +2;}					//	inStrLenに指定があれば(0以上)inStrLen分の文字列をコピーする
	else{           	outLine  += strlen(*inStr) +2;}					//	inStrLenに指定がなければ(!-1)inStrを最後までコピーする

	//古いデータのバックアップ（データへのポインタの保護
	char *strSwp;														//作業用キャラポ型の宣言
	strSwp		= *outSir;												//元の文字をバックアップ

	//再構成（メモリ確保、バックアップのリストア、データの追加、NULL文字の代入
	*outSir		= new char[outLine];									//メモリ領域の再割当て
	strcpy_s(*outSir, outLine, strSwp);									//バッファへコピー
	strncat_s(*outSir, outLine, *inStr, addLen);						//バッファ後部へ追加 
	sprintf_s(*outSir, outLine, "%s\0", *outSir);						//ヌル文字の代入


	delete [] strSwp;													//古い領域の破棄
	strSwp     = NULL;													//ポイ(ノ￣ー￣)ノ :・'.::・◇┏┛焼却炉┗┓
}
inline void copyStr(char **outSir,int cpyLen,char **inStr){
    //     ◇
	//	: 格納したい文字列数の確認
	int outLine = strlen(*outSir);										//	: 追加先の格納済み文字列数
	if(cpyLen >=0 ){	outLine  += cpyLen         +2;}					//	:	inStrLenに指定があれば(0以上)inStrLen分の文字列をコピーする
	else{           	outLine  += strlen(*inStr) +2;}					//	:	inStrLenに指定がなければ(!-1)inStrを最後までコピーする

	//	: 古いデータのバックアップ（データへのポインタの保護
	char *strSwp;														//	: 作業用キャラポ型の宣言
	strSwp		= *outSir;												//	: 元の文字をバックアップ

	//	: 再構成（メモリ確保、バックアップのリストア、データの追加、NULL文字の代入
	*outSir		= new char[outLine];									//	: メモリ領域の再割当て
	strcpy_s(*outSir, outLine, strSwp);									//	: バッファへコピー
	strncat_s(*outSir, outLine, *inStr, cpyLen);						//	: バッファ後部へ追加 
	sprintf_s(*outSir, outLine, "%s\0", *outSir);						//	: ヌル文字の代入


	delete [] strSwp;													//	: 古い領域の破棄
	strSwp     = NULL;													//	: ポイ(ノ￣ー￣)ノ :・'.::・◇┏┛焼却炉┗┓
}
///////// /////////
//void narrow(const std::wstring &src, std::string &dest) 
//
//：：ワイド文字列からマルチバイト文字列
//：：ロケール依存
//
//引数：
//	const std::wstring &src	：変換したい文字列
//	std::string &dest		：変換された文字列
//返値：なし
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
//：：マルチバイト文字列からワイド文字列
//：：ロケール依存
//
//引数：
//	const std::wstring &src	：変換したい文字列
//	std::string &dest		：変換された文字列
//返値：なし
inline void widen(const std::string &src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	size_t ret;
	mbstowcs_s(&ret, wcs, src.length() + 1, src.c_str(), src.length() + 1);
	dest = wcs;
	delete [] wcs;
}
}

#endif