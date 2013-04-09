////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Command.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：コマンドのてーぎ
//					▼
//	namespace wiz;
//		ゲームメッセージ列挙
//		struct Command ;
//
#pragma once

namespace wiz{

/**************************************************************************
 struct Command;
 用途: シーン内、ステージ内でやり取りされるコマンド
 ＊コマンド内容の定義は、各コンテンツにまかせる
****************************************************************************/
struct Command{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = 0;
	}
	~Command(){
		Clear();
	}
};
}