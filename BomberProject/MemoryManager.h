////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：DxDevice.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メモリを管理する子たちの集まり
//					▼
//	namespace TLIB ;
//		class TMemoryManager ;		//	: メモリの管理クラス
//		inline void* operator new( size_t iSize,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine)	;		//	:    new 演算子のオーバーライド関数 メモリを生成した ソースファイル・関数・行番号を同時に獲得する
//		inline void  operator delete(  void* pv,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine)	;		//	: delete 演算子のオーバーライド関数
//		template<typename T> inline void SafeDelete(T*& p)		;	//	: 安全にポインタを削除する
//		template<typename T> inline void SafeDeleteArr(T*& p)	;	//	: 安全に配列を削除する
//		
//

#ifndef TLIB_MEMORYMANAGER
#define TLIB_MEMORYMANAGER

#include "DebugFunctions.h"
#if defined( CF_MEMORYMANAGER_ENABLE )

//namespace TLIB{
//**************************************************************************//
// class TMemoryManager ;
// 担当  : 鴫原 徹
// 用途  : メモリ管理システム
// 備考  : プロジェクト内で確保されたメモリを管理します
//**************************************************************************//
class TMemoryManager{
public:
	//**************************************************************************//
	// struct itemInfo ;
	// 担当  : 鴫原 徹
	// 用途  : new されたデータの情報構造
	// 備考  : newを記憶する
	//**************************************************************************//
	struct itemInfo{
		void*		pPointer;
		size_t		iSize	;
		std::string	sFile	;
		std::string	sFunc	;
		const type_info&  sType	;
		UINT		iLine	;
		DWORD		iGenerateTime ;

		/////////////////// ////////////////////
		//// 関数名     ：itemInfo( void* i_pPointer, size_t i_iSize, std::string i_sFile,
		////            ：    std::string i_sFunc, UINT i_iLine, DWORD i_iGTime )
		//// カテゴリ   ：コンストラクタ
		//// 用途       ：インスタンスの生成
		//// 引数       ：  void*          i_pPointer
		////            ：  size_t         i_iSize
		////            ：  std::string    i_sFile
		////            ：  std::string    i_sFunc
		////            ：  UINT           i_iLine
		////            ：  DWORD          i_iGTime
		//// 戻値       ：なし
		//// 担当       ：鴫原 徹
		//// 備考       ：
		////            ：
		////
		itemInfo(
			void* i_pPointer,
			size_t i_iSize,
			std::string i_sFile,
			std::string i_sFunc,
			UINT i_iLine,
			DWORD i_iGTime
		)
		:pPointer(i_pPointer)
		,iSize(i_iSize)
		,sFile(i_sFile)
		,sFunc(i_sFunc)
		,iLine(i_iLine)
		,iGenerateTime(i_iGTime)
		,sType(typeid( i_pPointer ))
		{
		}
		/////////////////// ////////////////////
		//// 関数名     ：bool operator () ( const void* other ) const 
		//// カテゴリ   ：オペレータ
		//// 用途       ：()の機能のオーバーロード
		//// 引数       ：  const void* other
		//// 戻値       ：なし
		//// 担当       ：鴫原 徹
		//// 備考       ：じつわよくわかってなかったり／(・ × ・)＼
		////            ：
		////
		bool operator () ( const void* other ) const {
			return this->pPointer == other ;
		}
		/////////////////// ////////////////////
		//// 関数名     ：bool operator == ( const void* other ) const 
		//// カテゴリ   ：オペレータ
		//// 用途       ：==の機能のオーバーロード
		//// 引数       ：  const void* other
		//// 戻値       ：なし
		//// 担当       ：鴫原 徹
		//// 備考       ：じつわよくわかってなかったり／(・ × ・)＼
		////            ：
		////
		bool operator == ( const void* other ) const {
			return this->pPointer == other ;
		}
	};
private:
	//	: 確保したメモリ全体のサイズ(Byte?)
	static DWORD m_dwAreaSize ;
	//	: newされた情報リスト
	static std::list<itemInfo> m_ItemInfo ;
public:
	/////////////////// ////////////////////
	//// 関数名     ：static void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine)
	//// カテゴリ   ：メンバ関数
	//// 用途       ：メモリの生成とリストへの追加
	//// 引数       ：  size_t          i_iSize     //  : 確保するメモリのサイズ
	////            ：  std::string     i_sFile     //  : 生成処理の書かれたファイルの名前
	////            ：  std::string     i_sFunc     //  : 生成処理の書かれた関数の名前
	////            ：  UINT            i_iLine     //  : 生成処理の書かれている行番号
	//// 戻値       ：確保したメモリへのポインタ
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine){
		void* pPointer = malloc(i_iSize);
		m_dwAreaSize += i_iSize ;
		m_ItemInfo.push_back(itemInfo( pPointer, i_iSize , i_sFile,  i_sFunc, i_iLine, timeGetTime() ));
		return pPointer ; 
	}

	/////////////////// ////////////////////
	//// 関数名     ：static void remove( void* i_pPointer )
	//// カテゴリ   ：メンバ関数
	//// 用途       ：メモリの開放とリストからの削除
	//// 引数       ：  void* i_pPointer    //  : 削除対象のポインタ
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	static void remove( void* i_pPointer ){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			if( it->pPointer == i_pPointer ){
				m_dwAreaSize -= it->iSize ;
				free(it->pPointer);
				it->pPointer = NULL;
				it = m_ItemInfo.erase( it );
				return;
			}
		}
	}
	
	/////////////////// ////////////////////
	//// 関数名     ：static void Draw()
	//// カテゴリ   ：メンバ関数
	//// 用途       ：メモリの状態をリアルタイムに描画( とかできたらいいな～… )
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：現バージョンではデバッグ時以外に意味をなしません
	////            ：
	////
	static void Draw(){
<<<<<<< HEAD
		#if defined( CF_MEMORYOUTPUTPROCESS_ENABLE )
=======
>>>>>>> workspace
		Debugger::DBGSTR::addStr( L" Memory\n├ Area Size = %d Byte\n└ Instance  = %d Q'ty\n", m_dwAreaSize, m_ItemInfo.size() );
		if( GetAsyncKeyState( MYVK_DEBUG_OUTPUT_MEMORY ) ){
			std::list<itemInfo>::iterator it  = m_ItemInfo.begin();
			std::list<itemInfo>::iterator end = m_ItemInfo.end();
			time_t timer;
			struct tm local;

			/* 現在時刻を取得 */
			timer = time(NULL);

			localtime_s(&local, &timer); /* 地方時に変換 */

			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"めもり.txt" , L"ローカル時間 %4d/%2d/%2d %2d:%2d:%2d %d \n",
				local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
				local.tm_min, local.tm_sec, local.tm_isdst );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"めもり.txt" , L"総インスタンス数 : %d\n"		, m_ItemInfo.size()  );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"めもり.txt" , L"確保領域容量     : %d Byte\n"	, m_dwAreaSize       );
			
			DWORD i = 0 ;
			for(  ; it != end ; it++ ){
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "////////////\n"                           );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "データ %d \n"         , i                 );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "ポインタ   : 0x%X \n" , it->pPointer      );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "サイズ     : %d \n"   , it->iSize         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "ファイル名 : %s \n"   , it->sFile.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "関数       : %s \n"   , it->sFunc.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "行         : %d \n"   , it->iLine         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "時間       : %d \n\n" , it->iGenerateTime );
				i ++ ;
			}
		}
		#endif
	}

	/////////////////// ////////////////////
	//// 関数名     ：static void Clear()
	//// カテゴリ   ：メンバ関数
	//// 用途       ：いままで確保してきたメモリをすべて破棄する
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：※危険
	////            ：通常はこの関数を呼び出さないでください
	////            ：確実にバグります
	////            ：プログラム終了時の最後の最後でのみこの関数を呼び出してください
	////
	static void Clear(){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			free((*it).pPointer);
			(*it).pPointer = NULL ;
		}
		m_ItemInfo.clear();
	}
	/////////////////// ////////////////////
	//// 関数名     ：~TMemoryManager()
	//// カテゴリ   ：デストラクタ
	//// 用途       ：クラスを破棄
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////
	~TMemoryManager(){
		Clear();
	}

};

//void* operator new(size_t iSize,LPCTSTR sFile, LPCTSTR sFunc, UINT iLine){
//	return NULL;//TMemoryManager::add(iSize,sFile,sFunc,iLine);
//};
////////
//	: operator new のオーバーライド
//inline void* operator new(size_t iSize,LPCSTR  sFile =  "" , LPCSTR  sFunc = "" , UINT iLine = 0)

inline void* operator new(size_t iSize,LPCSTR  sFile  , LPCSTR  sFunc  , UINT iLine )
{
	return TMemoryManager::add(iSize,sFile,sFunc,iLine);
};

inline void operator delete(void* pv,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine){
	return TMemoryManager::remove(pv);
};

inline void operator delete(void* pv){
	return TMemoryManager::remove(pv);
};

	//	: 強制new置き換え
	#if defined( CF_OVERLORDNEW_ENABLE )
		#define new new(__FILE__, __FUNCTION__, __LINE__)
	#endif

	#define NEW new(__FILE__, __FUNCTION__, __LINE__)

#else /* CF_MEMORYMANAGER_ENABLE */
	#define NEW new
#endif

//////////
// DXUT互換マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{	if (p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{	if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{	if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_VECTOR
#define SAFE_DELETE_VECTOR(v)	{	for( DWORD i = 0 , L = v.size() ; L > i ; i++)	\
										SAFE_DELETE(v[i]) ;							\
									v.clear();										}
#endif    
//
//////////


/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeDelete(T*& p)
//// カテゴリ   ：テンプレート関数
//// 用途       ：安全にポインタをdeleteする
//// 引数       ：  T*& p               // T型のポインタの参照
//// 戻値       ：なし
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
template<typename T>
inline void SafeDelete(T*& p){
    if(p){
        delete p;
    }
    p = 0;
}

/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeDeleteArr(T*& p)
//// カテゴリ   ：テンプレート関数
//// 用途       ：安全に配列をdeleteする
//// 引数       ：  T*& p               // T型のポインタの参照
//// 戻値       ：なし
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
template<typename T>
inline void SafeDeleteArr(T*& p){
    if(p){
        delete [] p;
    }
    p = 0;
}

/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeDeletePointerMap(T& c)
//// カテゴリ   ：テンプレート関数
//// 用途       ：ポインターを格納したstdコンテナを安全にdeleteする
//// 引数       ：  T*& c               // T型のstdコンテナの参照
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：==有効な型==
////            ：std::map
////            ：std::multimap
////
template<typename T>
inline void SafeDeletePointerMap(T& c){
	T::iterator	it  = c.begin()	;
	while(it != c.end()){
		delete it->second ;
		it->second = NULL ;
		it++;
	}
	c.clear();
}
/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeDeletePointerContainer(T& c)
//// カテゴリ   ：テンプレート関数
//// 用途       ：ポインターを格納したstdコンテナを安全にdeleteする
//// 引数       ：  T*& c               // T型のstdコンテナの参照
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：==以下の型以外のコンテナに有効です==
////            ：std::map
////            ：std::multimap
////
template<typename T>
inline void SafeDeletePointerContainer(T& c){
	try{
		T::iterator	it  = c.begin()	;
		while(it != c.end()){
			SafeDelete( *it );
			//*it = NULL ;
			it++;
		}
		c.clear();
	}catch(...){
		throw ;
	}
}

/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeRelease(T*& p)
//// カテゴリ   ：テンプレート関数
//// 用途       ：安全にインターフェイスをreleaseする
//// 引数       ：  T*& p               // T型のインターフェイスのポインタの参照
//// 戻値       ：なし
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
template<typename T>
inline void SafeRelease(T*& p){
    if(p){
        p->Release();
    }
    p = 0;
}

//};
#endif