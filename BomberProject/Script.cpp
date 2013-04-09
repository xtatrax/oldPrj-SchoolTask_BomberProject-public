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
#include "StdAfx.h"
#include "Script.h"
namespace wiz{
MapLoader::MapLoader(char* i_cFileName,vector<Object*>& i_ObjectVec)
{
	setInstructionList();
	FILE* fp;
	errno_t err;
	if( (err = fopen_s(&fp,i_cFileName,"r+")) != 0 ){
		return ;
	}
	while(HeaderRead(fp,i_ObjectVec) != INSTRUCTION_EOF);;
	fclose(fp);


}

MapLoader::~MapLoader(void)
{
	Clear();
}

string MapLoader::HeaderRead(FILE *fp,vector<Object*>& i_ObjectVec){
	try{
		string Ins;
		do{
			Ins = InstructionSearch(fp);
			if(Ins == INSTRUCTION_EOF) return INSTRUCTION_EOF;
			switch(InstructionList[Ins]){
				case INSTTYPE_SETVARIABLE:
					readVariable(fp,Ins);
					break;
				case INSTTYPE_VARIABLE:
					SetModel(fp,i_ObjectVec);
					break;

			}
		}while(Ins != INSTRUCTION_END);
		return Ins;
	}catch(ERRORenum Error){
		return "Error";
		throw(Error);
	}

}
string MapLoader::InstructionSearch(FILE *fp){
	try{
		string StrBuf;
		int    CharBuf = 0 ;

		/////////
		//	: @�T��
		if((StrBuf += SearchAt(fp)) == INSTRUCTION_EOF) return INSTRUCTION_EOF ;
		//////////

		//////////
		//	: �擪��������
		if((StrBuf += ReadWord(fp)) == INSTRUCTION_EOF ) return INSTRUCTION_EOF ;
		//////////

		return StrBuf;

	}catch(ERRORenum Error){
		throw(Error);
	}
}

void MapLoader::readVariable(FILE* fp,string Ins){
	try{
		string VariableName,Var;
		int    CharBuf = 0 ;

		//////////
		//	: �ϐ����ǂݏo��
		VariableName += ReadWord(fp);
		//////////

		//////////
		//	: ������ǂݏo��
		Var += ReadString(fp);
		//////////
		VariableType vtype;
		if(Ins == INSTRUCTION_VALTYPE_MODEL) vtype = VARIABLETYPE_GROUNDMODEL;
		VariableList[VariableName] = new VarState(vtype,Var);
		InstructionList["@"+VariableName] = INSTTYPE_VARIABLE;
	}catch(ERRORenum Error){
		throw(Error);
	}
}
string MapLoader::ReadString(FILE *fp){
	try{
		string StrBuf;
		int    CharBuf = 0 ;
		//////////
		//	: =�T��
		do{
			CharBuf = fgetc(fp);
			if(CharBuf == EOF ){
				throw ERROR_READ_UNKNOWN_EOF ;	//	: �s����EOF
			}
		}while(CharBuf != '=');
		//////////

		//////////
		//	: "�T��
		do{
			CharBuf = fgetc(fp);
			if(CharBuf == EOF ){
				throw ERROR_READ_UNKNOWN_EOF ;	//	: �s����EOF
			}
		}while(CharBuf != '\"');
		//////////

		CharBuf = fgetc(fp);
		if(CharBuf == EOF ){
			throw ERROR_READ_UNKNOWN_EOF ;	//	: �s����EOF
		}
			
		//////////
		//	: ���ߓǂݏo��
		while(CharBuf != '\"'){

			StrBuf += CharBuf ;
			CharBuf = fgetc(fp);
			
			if(CharBuf == EOF ){
				//�G���[
				throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
			}
		}
		//////////
		return StrBuf;
	}catch(ERRORenum Error){
		throw(Error);
	}
}
string MapLoader::SearchAt(FILE* fp){
	string StrBuf;
	int    CharBuf = 0 ;
	/////////
	//	: @�T��
	do{
		CharBuf = fgetc(fp);
		if(CharBuf == EOF ){
			return INSTRUCTION_EOF ;
		}
	}while(CharBuf != '@');
	//////////
	StrBuf += CharBuf;
	return StrBuf;
}

string MapLoader::SearchInitial(FILE* fp){
	try{
		string StrBuf;
		int    CharBuf = 0 ;
		//////////
		//	: �擪��������
		do{
			CharBuf = fgetc(fp);
			if(CharBuf == EOF ){
				throw ERROR_READ_UNKNOWN_EOF ;	//	: �s����EOF
			}
		}while(CharBuf == ' ' || CharBuf == '	' || CharBuf == '\n');
		//////////

		//////////
		//	: �p�����ǂ���
		if( !isalpha( CharBuf ) ){
			throw ERROR_SYNTAX_INITIALCHARA ;	//	: �\���G���[ : �擪�������p������Ȃ�
		}
		//////////
		StrBuf += CharBuf;
		return StrBuf ;

	}catch(ERRORenum Error){
		throw(Error);
	}

}


string MapLoader::ReadWord(FILE* fp){
	try{
		string StrBuf;
		int    CharBuf = 0 ;

		//////////
		//	: �擪��������
		if((StrBuf += SearchInitial(fp)) == INSTRUCTION_EOF ) return INSTRUCTION_EOF ;
		//////////

		CharBuf = fgetc(fp);	
		if(CharBuf == EOF ){
			//�G���[
			throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
		}

		//////////
		//	: ���ߓǂݏo��
		while(CharBuf != ' ' && CharBuf != '	' && CharBuf != '\n'){
			if( CharBuf == '{') break;
			//	: �p�����ǂ���
			if( !isalnum( CharBuf ) && CharBuf != '_' ){
				throw ERROR_SYNTAX_OTHERTHANALNUM ; //	: �p���ȊO�̕�����
			}

			StrBuf += CharBuf ;
			CharBuf = fgetc(fp);
			
			if(CharBuf == EOF ){
				//�G���[
				throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
			}
		}
		return StrBuf;
		//////////
	}catch(ERRORenum Error){
		throw(Error);
	}

}
void MapLoader::SetModel(FILE *fp,vector<Object*>& i_ObjectVec){
	try{
		while(true){
			ObjState* objeState = new ObjState;
			string VariableType,Var;
			int    CharBuf = 0 ;

			//////////
			//	: �����T��
			do{
				CharBuf = fgetc(fp);

				if(CharBuf == EOF ){
					//�G���[
					throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
				}
				if( CharBuf == '}' ) return;
			}while(!isalpha( CharBuf ));
			//////////
			//	�ϐ��̌^
			VariableType += CharBuf;
			VariableType += ReadWord(fp);

			do{
				CharBuf = fgetc(fp);

				if(CharBuf == EOF ){
					//�G���[
					throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
				}
			}while(CharBuf != '=');

			//////////
			//	: �����T��
			do{
				CharBuf = fgetc(fp);

				if(CharBuf == EOF ){
					//�G���[
					throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
				}
			}while(CharBuf == ' ' || CharBuf == '	' || CharBuf == '\n');
			//////////

			//////////
			//	: �l
			while(isdigit(CharBuf) || CharBuf == '.'){
			
				Var += CharBuf;
				CharBuf = fgetc(fp);

				if(CharBuf == EOF ){
					//�G���[
					throw ERROR_READ_UNKNOWN_EOF ; //	: �s����EOF
				}
			}
			//////////
			//	: �l�̊i�[
			if(VariableType == "SCALE_X" ) objeState->Scale.x = (float)atof(Var.c_str()) ;
			if(VariableType == "SCALE_Y" ) objeState->Scale.y = (float)atof(Var.c_str()) ;
			if(VariableType == "SCALE_Z" ) objeState->Scale.z = (float)atof(Var.c_str()) ;
			if(VariableType == "POS_X" ) objeState->Pos.x = (float)atof(Var.c_str()) ;
			if(VariableType == "POS_Y" ) objeState->Pos.y = (float)atof(Var.c_str()) ;
			if(VariableType == "POS_Z" ) objeState->Pos.z = (float)atof(Var.c_str()) ;


		}
	}catch(ERRORenum Error){
		throw(Error);
	}
}
void MapLoader::setInstructionList(){
	InstructionList[INSTRUCTION_VALTYPE_MODEL] = INSTTYPE_SETVARIABLE;
	InstructionList[INSTRUCTION_END] = INSTTYPE_END;
}


void MapLoader::setErrorList(){
	for(UINT i = 0 ; i < ERROR_UNKNOWN ; i++ ){
		switch(i){
			case ERROR_UNKNOWN:
				m_ErrorStringList.push_back("�s���ȃG���[");
		}
	}
}
void MapLoader::CreateStage(vector<Object*>& i_ObjectVec){
	//vector<ObjState*>::size_type sz = m_ObjList.size(), i = 0 ;
	//while( i < sz ){
	//	vector<Object*>::size_type i = 0 , sz = i_ObjectVec.size();
	//	switch(VariableList[m_ObjList[i]->VarName]->Type){
	//		case VARIABLETYPE_GROUNDMODEL;
	//			break;	
	//	}
	//}
}
void MapLoader::Clear(){
	map<string , VarState*>::iterator it = VariableList.begin();
	while(it != VariableList.end()){
		delete it->second;
	}
	VariableList.clear();

}
}