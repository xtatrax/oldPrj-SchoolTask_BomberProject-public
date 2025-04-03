////////////////////////////// //////////////////////////////
//	プロジェクト	：Stick Figures
//	ファイル名		：Script.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包データと備考	：
//					▼
//	namespace wiz;
//		class MapLoader
//
#pragma once
#include "Object.h"
#define INSTRUCTION_END    ("@END")
#define INSTRUCTION_EOF    ("@EOF")
#define INSTRUCTION_VALTYPE_MODEL  ("@GROUNDMODEL")


namespace wiz{
class MapLoader
{
	//	: 命令の種類
	enum InsType{
		INSTTYPE_END,
		INSTTYPE_SETVARIABLE,	//	: 変数宣言
		INSTTYPE_VARIABLE,		//	: 変数
	};
	//	: 変数の種類
	enum VariableType{
		VARIABLETYPE_GROUNDMODEL ,
	};
	//	: 配置データ
	struct ObjState{
		D3DXVECTOR3 Scale;
		D3DXVECTOR3	Pos;
		ObjState(){
			Scale = g_vZero;
		}
	};
	//	: 変数のステータス
	struct VarState{
		VariableType		Type;		//	: 変数の型
		string				VarName;	//	: 変数の値
		VarState(VariableType type,string var)
		:Type(type),VarName(var){};
		~VarState(){}

	};


	map<string , InsType> InstructionList;	//	: 命令リスト
	map<string , VarState*> VariableList;	//	: 変数リスト
	vector<char*>		m_ErrorStringList;	//	: エラー時の表記文字リスト

	enum ERRORenum{
		ERROR_READ_UNKNOWN_EOF    ,
		ERROR_SYNTAX_INITIALCHARA ,
		ERROR_SYNTAX_OTHERTHANALNUM ,
		ERROR_UNKNOWN
	};
public:
	MapLoader(char* i_cFileName,vector<Object*>& i_ObjectVec);
	virtual ~MapLoader(void);
	string HeaderRead(FILE* fp,vector<Object*>& i_ObjectVec);
	string InstructionSearch(FILE* fp);
	void   readVariable(FILE* fp,string Ins);
	string ReadString(FILE* fp);
	string ReadWord(FILE* pf);
	string SearchAt(FILE* pf);
	string SearchInitial(FILE* pf);
	string SetVariable(FILE* fp);
	void   SetModel(FILE* fp,vector<Object*>& i_ObjectVec);
	void   setInstructionList();
	void   setErrorList();
	void   CreateStage(vector<Object*>& i_ObjectVec);
	void   Clear();
};

}
