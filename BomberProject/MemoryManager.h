////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
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

//namespace TLIB{
class TMemoryManager{
	static DWORD m_dwAreaSize ;
public:
	//	: new されたデータの情報構造
	struct itemInfo{
		void*		pPointer;
		size_t		iSize	;
		std::string	sFile	;
		std::string	sFunc	;
		UINT		iLine	;
		DWORD		iGenerateTime ;

		//	: コンストラクタ
		itemInfo(void* i_pPointer,size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine, DWORD i_iGTime)
			:pPointer(i_pPointer),iSize(i_iSize),sFile(i_sFile), sFunc(i_sFunc), iLine(i_iLine) ,iGenerateTime(i_iGTime)
		{}
		//	: 検索用オーバーライド?
		bool operator () ( const void* other ) const {
			return this->pPointer == other ;
		}
		//	: 検索用オーバーライド?
		bool operator == ( const void* other ) const {
			return this->pPointer == other ;
		}
	};

	//	: newされた情報リスト
	static std::list<itemInfo> m_ItemInfo ;

	//	: 追加
	static void* add(size_t i_iSize,std::string i_sFile, std::string i_sFunc, UINT i_iLine){
		void* pPointer = malloc(i_iSize);
		m_dwAreaSize += i_iSize ;
		m_ItemInfo.push_back(itemInfo( pPointer, i_iSize , i_sFile,  i_sFunc, i_iLine, timeGetTime() ));
		return pPointer ; 
	}

	//	: 削除
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
	
	//	: グラフィカル化する!
	//	: メモリ状態の描画
	static void Draw(){
		//Debugger::DBGSTR::addStr( L" Memory\n├ Area Size = %d Byte\n└ Instance  = %d Q'ty\n", m_dwAreaSize, m_ItemInfo.size() );
		if( GetAsyncKeyState( MYVK_DEBUG_OUTPUT_MEMORY ) ){
			std::list<itemInfo>::iterator it  = m_ItemInfo.begin();
			std::list<itemInfo>::iterator end = m_ItemInfo.end();
			time_t timer;
			struct tm local;

			/* 現在時刻を取得 */
			timer = time(NULL);

			localtime_s(&local, &timer); /* 地方時に変換 */

			/* 地方時 変換後表示 */
			printf("地方時: ");
			printf("%4d/", local.tm_year + 1900);
			printf("%2d/", local.tm_mon + 1);
			printf("%2d ", local.tm_mday);
			printf("%2d:", local.tm_hour);
			printf("%2d:", local.tm_min);
			printf("%2d", local.tm_sec);
			printf(" %d\n", local.tm_isdst);


			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"めもり.txt" , L"ローカル時間 %4d/%2d/%2d %2d:%2d:%2d %d \n",
				local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
				local.tm_min, local.tm_sec, local.tm_isdst );
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
	}

	//////////
	//	: ※危険
	//	: 通常は利用しない
	//	: いままで確保してきたメモリをすべて破棄する
	static void Clear(){
		std::list<itemInfo>::iterator it ;
		for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
			free((*it).pPointer);
		}
		m_ItemInfo.clear();
	}
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

#define ew new(__FILE__, __FUNCTION__, __LINE__)


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