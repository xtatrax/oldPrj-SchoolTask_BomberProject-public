////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：SaveAndLoad.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：セーブしたりロードしたり
//					▼
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
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
template<typename T>
inline void BinarySave( const char* sDataPath, T& SavePacket )
{
	try{
		//////////
		//	: Folderパスの分離処理
		size_t	pathLength ;
		char* pFilePath ;
		for(  pathLength = strlen(sDataPath) ; pathLength >= 0 ; pathLength--  )
			if(  sDataPath[ pathLength ] == '/' || sDataPath[ pathLength ] == '\\'  )
				break ;
		pFilePath	= new char[ pathLength + 1 ] ;
		for(  size_t i = 0 ; i < pathLength ; i++  )
			pFilePath[ i ]	= sDataPath[ i ] ;
		pFilePath[ pathLength ]	= '\0' ;
		//	: Folderパスの分離処理
		//////////

		//////////
		//	: フォルダの存在確認と生成処理
		wstring wstr ;
		TLIB::widen(string(pFilePath),wstr);
		if(!PathIsDirectory(wstr.c_str())){
			if(!CreateDirectory(wstr.c_str(),NULL)){
				::MessageBoxA(NULL,"フォルダを確保出来ませんでしたー><、\nTLIB::BinarySave()","えらー",MB_OK);
			}
		}
		//	: フォルダの存在確認と生成処理
		//////////


		//////////
		//	: ファイルの作成と書き込み処理
		FILE* fp;
		if( fopen_s(&fp,sDataPath,"wb") != 0 ){
			return;	//	: あとでTLIB用例外作って置き換える
		}
		size_t	PacketSize = sizeof(T),
				retSize = fwrite((void*)&SavePacket,PacketSize,1,fp);
		if( retSize == 0 ){
			fclose(fp);
			return ;	//	: あとでTLIB用例外作って置き換える
		}
		fclose(fp);
		//	: ファイルの作成と書き込み処理
		//////////

	}
	catch(...){
		throw;
	}
};
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
template<typename T>
inline void BinaryLoad( const char* sDataPath, T& SavePacket, const char* sFileExtension = "tbs" )
{
	if( !FileExtentionChecker(sDataPath,sFileExtension) ){
		::ZeroMemory( &SavePacket, sizeof(T) );
		return;	//	: あとでTLIB用例外作って置き換える
	}

	FILE* fp;
	if( fopen_s(&fp,sDataPath,"rb") != 0 ){
		return;	//	: あとでTLIB用例外作って置き換える
	}
	size_t PacketSize = sizeof(T);
	if( fread_s((void*)&SavePacket,PacketSize,PacketSize,1,fp) != PacketSize ){
		fclose(fp);
		return ;	//	: あとでTLIB用例外作って置き換える
	}
	fclose(fp);

};
}
//end of namespace TLOB.
#endif