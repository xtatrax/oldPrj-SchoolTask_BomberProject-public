////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FTATRA-Library
//	�t�@�C����		�FSaveAndLoad.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�Z�[�u�����胍�[�h������
//					��
//	namespace TLIB ;
//		
//

#ifndef TLIB_SAVEANDLOAD
#define TLIB_SAVEANDLOAD

namespace TLIB{
struct BassSaveaPacketDat{
	unsigned long hidentifier;
	unsigned long lidentifier;
	BassSaveaPacketDat(unsigned long IH = 0x41534C54, unsigned long IL = 0x005F4556)
	:hidentifier(IH)//	: TLSAVE
	,lidentifier(IL){};
};
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
template<typename T>
inline void BinarySave( const char* sDataPath, T& SavePacket )
{
	try{
		//////////
		//	: Folder�p�X�̕�������
		size_t	pathLength ;
		char* pFilePath ;
		for(  pathLength = strlen(sDataPath) ; pathLength >= 0 ; pathLength--  )
			if(  sDataPath[ pathLength ] == '/' || sDataPath[ pathLength ] == '\\'  )
				break ;
		pFilePath	= new char[ pathLength + 1 ] ;
		for(  size_t i = 0 ; i < pathLength ; i++  )
			pFilePath[ i ]	= sDataPath[ i ] ;
		pFilePath[ pathLength ]	= '\0' ;
		//	: Folder�p�X�̕�������
		//////////

		//////////
		//	: �t�H���_�̑��݊m�F�Ɛ�������
		wstring wstr ;
		TLIB::widen(string(pFilePath),wstr);
		if(!PathIsDirectory(wstr.c_str())){
			if(!CreateDirectory(wstr.c_str(),NULL)){
				::MessageBoxA(NULL,"�t�H���_���m�ۏo���܂���ł����[><�A\nTLIB::BinarySave()","����[",MB_OK);
			}
		}
		//	: �t�H���_�̑��݊m�F�Ɛ�������
		//////////


		//////////
		//	: �t�@�C���̍쐬�Ə������ݏ���
		FILE* fp;
		if( fopen_s(&fp,sDataPath,"wb") != 0 ){
			return;	//	: ���Ƃ�TLIB�p��O����Ēu��������
		}
		size_t	PacketSize = sizeof(T),
				retSize = fwrite((void*)&SavePacket,PacketSize,1,fp);
		if( retSize == 0 ){
			fclose(fp);
			return ;	//	: ���Ƃ�TLIB�p��O����Ēu��������
		}
		fclose(fp);
		//	: �t�@�C���̍쐬�Ə������ݏ���
		//////////

	}
	catch(...){
		throw;
	}
};
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
template<typename T>
inline void BinaryLoad( const char* sDataPath, T& SavePacket, const char* sFileExtension = "tbs" )
{
	if( !FileExtentionChecker(sDataPath,sFileExtension) ){
		::ZeroMemory( &SavePacket, sizeof(T) );
		return;	//	: ���Ƃ�TLIB�p��O����Ēu��������
	}

	FILE* fp;
	if( fopen_s(&fp,sDataPath,"rb") != 0 ){
		return;	//	: ���Ƃ�TLIB�p��O����Ēu��������
	}
	size_t PacketSize = sizeof(T);
	if( fread_s((void*)&SavePacket,PacketSize,PacketSize,1,fp) != PacketSize ){
		fclose(fp);
		return ;	//	: ���Ƃ�TLIB�p��O����Ēu��������
	}
	fclose(fp);

};
}
//end of namespace TLOB.
#endif