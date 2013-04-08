////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FScript.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//					��
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
	//	: ���߂̎��
	enum InsType{
		INSTTYPE_END,
		INSTTYPE_SETVARIABLE,	//	: �ϐ��錾
		INSTTYPE_VARIABLE,		//	: �ϐ�
	};
	//	: �ϐ��̎��
	enum VariableType{
		VARIABLETYPE_GROUNDMODEL ,
	};
	//	: �z�u�f�[�^
	struct ObjState{
		D3DXVECTOR3 Scale;
		D3DXVECTOR3	Pos;
		ObjState(){
			Scale = g_vZero;
		}
	};
	//	: �ϐ��̃X�e�[�^�X
	struct VarState{
		VariableType		Type;		//	: �ϐ��̌^
		string				VarName;	//	: �ϐ��̒l
		VarState(VariableType type,string var)
		:Type(type),VarName(var){};
		~VarState(){}

	};


	map<string , InsType> InstructionList;	//	: ���߃��X�g
	map<string , VarState*> VariableList;	//	: �ϐ����X�g
	vector<char*>		m_ErrorStringList;	//	: �G���[���̕\�L�������X�g

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
