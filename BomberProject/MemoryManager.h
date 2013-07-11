////////////////////////////// //////////////////////////////
//	プロジェクト	：TATRA-Library
//	ファイル名		：MemoryManager.h
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
#include <new>
#include <string.h>
#include "DebugFunctions.h"
#if defined( CF_MEMORYMANAGER_ENABLE )

//namespace TLIB{
//**************************************************************************//
// class TMemoryManager ;
// 担当  : 鴫原 徹
// 用途  : プロジェクト内で確保されたメモリを管理します｡
// 備考  : 非常に遅いです 現状ほぼDEBUG用です｡
//       : 終了時等に m_ItemInfo の中身を覗けばリリーズ漏れが起きている
//       : 実体が生成されてた場所が把握出来ます｡
//       : CF_DRAW_DEBUGSTRING と CF_MEMORYOUTPUTPROCESS_ENABLE を有効にすれば
//       : newされた実体の総数と総確保Byteをリアルタイムで見ることができます｡
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
		void*				pPointer;
		size_t				iSize	;
		std::string			sFile	;
		std::string			sFunc	;
		const type_info&	sType	;
		UINT				iLine	;
		DWORD				iGenerateTime ;

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

		#if defined( CF_MEMORYOUTPUTPROCESS_ENABLE )
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
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// データ %d \n"         , i                 );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// ポインタ   : 0x%X \n" , it->pPointer      );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// サイズ     : %d \n"   , it->iSize         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// ファイル名 : %s \n"   , it->sFile.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// 関数       : %s \n"   , it->sFunc.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// 行         : %d \n"   , it->iLine         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "めもり.txt" , "// 時間       : %d \n\n" , it->iGenerateTime );
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
		if( m_ItemInfo.size() != 0 ){
		#if defined( CF_MEMORYLEEKOUTPUT_ENABLE )
			wchar_t cbuf[255];
			wsprintf( cbuf, L"%d", m_ItemInfo.size() );
			wstring buf ;
			buf += cbuf	 ;
			buf += L"個のメモリリークを検出しました。\n";
			buf += L"リーク一覧を";
			buf += Debugger::DBGWRITINGLOGTEXT::GetDefaultLogFolder();
			buf += Debugger::DBGWRITINGLOGTEXT::GetDefaultFileName();
			buf += L"へ出力しました\n";

			
			time_t timer;
			struct tm local;

			/* 現在時刻を取得 */
			timer = time(NULL);

			localtime_s(&local, &timer); /* 地方時に変換 */
			//#define pFileName "LeekMemoryList.txt" 
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"LeekMemoryList.txt" , L"ローカル時間 %4d/%2d/%2d %2d:%2d:%2d %d \n",
				local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour,
				local.tm_min, local.tm_sec, local.tm_isdst );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"LeekMemoryList.txt"  , L"総インスタンス数 : %d\n"		, m_ItemInfo.size()  );
			Debugger::DBGWRITINGLOGTEXT::addStrToFile( L"LeekMemoryList.txt"  , L"確保領域容量     : %d Byte\n"	, m_dwAreaSize       );
			
			DWORD i = 0 ;
		#endif
			std::list<itemInfo>::iterator it ;
			for( it = m_ItemInfo.begin() ; it != m_ItemInfo.end() ; it++ ){
		#if defined( CF_MEMORYLEEKOUTPUT_ENABLE )
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "////////////\n"                              );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// データ %d \n"         , i                 );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// ポインタ   : 0x%X \n" , it->pPointer      );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// サイズ     : %d \n"   , it->iSize         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// ファイル名 : %s \n"   , it->sFile.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// 関数       : %s \n"   , it->sFunc.c_str() );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// 行         : %d \n"   , it->iLine         );
				Debugger::DBGWRITINGLOGTEXT::addStrToFile( "LeekMemoryList.txt"  , "// 時間       : %d \n\n" , it->iGenerateTime );
				i++;
		#endif
				free( it->pPointer );
				it->pPointer = NULL ;
			}
		#if defined( CF_MEMORYLEEKOUTPUT_ENABLE )
				::MessageBox( 0, buf.c_str(), L"警告", MB_OK | MB_ICONWARNING );
				::MessageBox( 0, L"なお、このログは蓄積して、ハードディスクを\n圧迫する可能性があるのでご注意ください", L"警告", MB_OK | MB_ICONWARNING );
		#endif
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
	return TMemoryManager::add(iSize,strrchr(sFile,'\\' ) + 1,sFunc,iLine);
};

inline void operator delete(void* pv,LPCSTR  sFile, LPCSTR  sFunc, UINT iLine){
	return TMemoryManager::remove(pv);
};

inline void operator delete(void* pv){
	return TMemoryManager::remove(pv);
};

	//	: 強制new置き換え
	#if defined( CF_OVERLORDNEW_ENABLE )
		#define new new(__FILE__ , __FUNCTION__, __LINE__)
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
		SafeDelete( it->second );
		//it->second = NULL ;
		it++;
	}
	c.clear();
}
/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SefeDeletePointerVector(vector<C*>& Vec)
//// カテゴリ   ：テンプレート関数
//// 用途       ：ポインタの配列（vector）を安全にクリアする
//// 引数       ：  vector<C*>& Vec               //  : C型の配列の参照
//// 戻値       ：なし
//// 担当       ：なし(山ノ井先生のひな形より)
//// 備考       ：
////
template<class C>
void SefeDeletePointerVector(vector<C*>& Vec){
	size_t maxsz = Vec.size();
	for(size_t i = 0;i < maxsz;i++){
		delete Vec[i];
	}
	Vec.clear();
}

namespace Avoid{
inline void widen(const std::string &src, std::wstring &dest) {
	//wchar_t *wcs = new wchar_t[src.length() + 1];
	//size_t ret;
	//mbstowcs_s(&ret, wcs, src.length() + 1, src.c_str(), src.length() + 1);
	//dest = wcs;
	//delete [] wcs;
}
}
/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeDeletePointerContainer(T& c)
//// カテゴリ   ：テンプレート関数
//// 用途       ：コンテナに格納されたポインターを安全にすべてDeleteします
//// 引数       ：  T*& c               // T型のstdコンテナの参照
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：安全にとは言ってももちろん二重削除や
////            ：new以外で生成された実体へのポインターには
////            ：対応できないので注意してください
////            ：==以下の型 "以外" のstdコンテナに有効です==
////            ：std::map
////            ：std::multimap
////
template<typename T>
inline void SafeDeletePointerContainer(T& c){
	try{
/*
		//	: ↓デバッグ用の処理で見難くなっていますが↓
		//	:   ↓中身でやっていることはこんなんです↓

		if( c.empty() )		return;

		T::iterator	it  = c.begin()	;
		while(it != c.end()){
			SafeDelete( *it );
			it++;
		}
		c.clear();
*/
		if( c.empty() ){
			//	: コンテナーが空ならそのまま処理を終了
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個  \n" , c.size()  );
			#endif

			return;
		}
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"\n////////// \n"   );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個 削除開始 \n" , c.size()  );
			DWORD num = 0;
		#endif

		//////////
		//	: イテレータがENDになるまで削除
		T::iterator	it  = c.begin()	,
					end = c.end()	;
		while( it != end ){
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				num++;
				const type_info& yp = typeid(*(*it));
				wstring buf ;
				Avoid::widen( string( yp.name() ), buf);
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > [%d / %d]個 削除開始 ( %s )\n" , num   , c.size() , buf.c_str() );
			#endif

			//	: ポインターの削除
			SafeDelete( *it );
			//*it = NULL ;
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > it++\n" );
			#endif
			it++;
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > [%d / %d]個 削除完了 ( %s )\n" , num , c.size() , buf.c_str() );
			#endif
		}
		//	: 最後にコンテナを空に
		c.clear();
		//
		//////////
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個 削除完了\n" , num  );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"////////// \n"   );
		#endif
	}catch(...){
		throw ;
	}
}

/////////////////// ////////////////////
//// 関数名     ：template<typename T> inline void SafeReleasePointerContainer(T& c)
//// カテゴリ   ：テンプレート関数
//// 用途       ：ポインターを格納したstdコンテナを安全にReleaseする
//// 引数       ：  T*& c               // T型のstdコンテナの参照
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：安全にとは言ってももちろん
////            ：==以下の型 "以外" のstdコンテナに有効です==
////            ：std::map
////            ：std::multimap
////
template<typename T>
inline void SafeReleasePointerContainer(T& c){
	try{
/*
		//	: ↓デバッグ用の処理で見難くなっていますが↓
		//	:   ↓中身でやっていることはこんなんです↓

		if( c.empty() ){
			return;
		}
		T::iterator	it  = c.begin()	;
		while(it != c.end()){
			SafeRelease( *it );
			it++;
		}
		c.clear();
*/
		if( c.empty() ){
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
						//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個  \n" , c.size()  );
			#endif
			return;
		}
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"\n////////// \n"   );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個 削除開始 \n" , c.size()  );
				DWORD num = 0;
		#endif
		T::iterator	it  = c.begin()	;
		while(it != c.end()){
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
						num++;
						const type_info& yp = typeid(*(*it));
						wstring buf ;
						Avoid::widen( string( yp.name() ), buf);
						//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > [%d / %d]個 削除開始 ( %s )\n" , num   , c.size() , buf.c_str() );
			#endif
			SafeRelease( *it );
			//*it = NULL ;
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
						//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > it++\n" );
			#endif
			it++;
			#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
						//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > [%d / %d]個 削除完了 ( %s )\n" , num , c.size() , buf.c_str() );
			#endif
		}
		c.clear();
		#if defined(CF_DEBUGLOGTEXT_OUTPUT_ENABLE)
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(T& c) > %d個 削除完了\n" , num  );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"// \n"  );
				//Debugger::DBGWRITINGLOGTEXT::addStr(L"////////// \n"   );
		#endif
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
inline int SafeRelease(T*& p){
	int ret = 0 ;
    if(p){
		ret = p->Release();
    }
    p = 0;
	return ret ;
}

//};
#endif