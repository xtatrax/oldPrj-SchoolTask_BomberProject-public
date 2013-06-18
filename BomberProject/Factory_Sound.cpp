////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Sound.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Factory_Sound ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Sound.h"
#include "BassItems.h"

namespace wiz{
namespace system{

/**************************************************************************
 _Sound 定義部
****************************************************************************/

/**************************************************************************
 void _Sound::CreateInctance();
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void _Sound::CreateInctance(){
	ReleaseObj();
	try{
		HANDLE hFile;
		DWORD dwFileSize;
		HANDLE hMapFile;
		//メモリをnewしてデータ作成する場合以下の変数が必要
		//DWORD dwBytesRead;

		//デバッグ時は以下をtrueにする
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// 初期化失敗
			throw BaseException(
				L"サウンドエンジン構築に失敗しました。",
				L"_Sound::CreateInctance()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		//コールバック関数の指定
		if(m_fnNotificationCallback){
			xrParams.fnNotificationCallback = m_fnNotificationCallback;
		}
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// 初期化失敗
			throw BaseException(
				L"サウンドエンジン初期化に失敗しました。",
				L"_Sound::CreateInctance()"
				);
		}
		//Wavバンクの作成
		if(m_WavBankFileName != L""){
			hFile = CreateFile(m_WavBankFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
			if( hFile != INVALID_HANDLE_VALUE ){
				dwFileSize = GetFileSize( hFile, NULL );
				if( dwFileSize != -1 ){
					hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
					if( hMapFile ){
						m_pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
						if(m_pbWaveBank){
							if(FAILED(m_pEngine->CreateInMemoryWaveBank(m_pbWaveBank, dwFileSize, 0,
								0, &m_pWaveBank))){
								CloseHandle( hMapFile );
								CloseHandle( hFile );
								// 初期化失敗
								throw BaseException(
									L"Wavバンクハンドル初期化に失敗しました。",
									L"_Sound::CreateInctance()"
									);
							}
						}
						CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
					}
				}
				CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
			}
			else{
				// 初期化失敗
				throw BaseException(
					L"ウェブバンクファイルの読み込みに失敗しました。",
					L"_Sound::CreateInctance()"
					);
			}
		}
		//_Soundバンクの作成
		if(m_SoundBankFileName != L""){
			hFile = CreateFile(m_SoundBankFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
			if( hFile != INVALID_HANDLE_VALUE )
			{
				dwFileSize = GetFileSize( hFile, NULL );
				if( dwFileSize != -1 )
				{

					hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
					if( hMapFile ){
						m_pbSoundBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
						if(m_pbSoundBank){
							if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
								0, &m_pSoundBank))){
								CloseHandle( hMapFile );
								CloseHandle( hFile );
								// 初期化失敗
								throw BaseException(
									L"_Soundバンクハンドル初期化に失敗しました。",
									L"_Sound::CreateInctance()"
									);
							}
						}
						CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
					}

					// Allocate the data here and free the data when recieving the sound bank destroyed notification
					//以下のようにメモリをnewして作成することもできる（WavBankも同様）
					//m_pbSoundBank = new BYTE[dwFileSize];
					//if(m_pbSoundBank)
					//{
					//	if( 0 != ReadFile( hFile,m_pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
					//	{
					//		if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
					//			0, &m_pSoundBank))){
					//			CloseHandle( hFile );
					//			// 初期化失敗
					//			throw BaseException(
					//				L"_Soundバンクハンドル初期化に失敗しました。",
					//				L"_Sound::CreateInctance()"
					//				);

					//		}
					//	}
					//}


				}
				CloseHandle( hFile );
			}
			else{
				// 初期化失敗
				throw BaseException(
					L"サウンドバンクファイルの読み込みに失敗しました。",
					L"_Sound::CreateInctance()"
					);
			}
		}
	}
	catch(...){
		ReleaseObj();
		//再throw
		throw;
	}
}


/**************************************************************************
 _Sound::_Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName = 0,	//_Soundバンクのファイル名（オプション）
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//通知用コールバック関数のポインタ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
_Sound::_Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,wiz::OBJID id,
		XACT_NOTIFICATION_CALLBACK fnNotificationCallback)
:Object( id ),
m_pEngine(0),m_fnNotificationCallback(fnNotificationCallback),
m_pWaveBank(0),m_pSoundBank(0),m_pbWaveBank(0),m_pbSoundBank(0),
m_WavBankFileName(L""),
m_SoundBankFileName(L"")
{
	try{
		if(!pWavBankFileName){
			// 初期化失敗
			throw BaseException(
				L"WAVバンクファイルが指定されてません。",
				L"_Sound::_Sound()"
				);
		}
		m_WavBankFileName = pWavBankFileName;
		if( pSoundBankFileName ){
			m_SoundBankFileName = pSoundBankFileName;
		}
		CreateInctance();
	}
	catch(exception& e){
		ReleaseObj();
		::MessageBoxA(
			wiz::DxDevice::m_hWnd,
			e.what(),
			"エラー",
			MB_OK);
	}
	catch(...){
		ReleaseObj();

		::MessageBoxA(
			NULL,
			"_Soundで未知のエラー",
			"エラー",
			MB_OK);
		//再throw
	}
}
/**************************************************************************
 virtual _Sound::~_Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
_Sound::~_Sound(){
	ReleaseObj();
}

/**************************************************************************
 virtual void _Sound::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void _Sound::ReleaseObj(){
    if(m_pEngine){
        m_pEngine->ShutDown();
		SafeRelease(m_pEngine);
    }
	//newでデータを取得した場合は以下のようにdeleteする
	//SafeDeleteArr(m_pbSoundBank);
	if(m_pbSoundBank){
        UnmapViewOfFile(m_pbSoundBank);
	}
    m_pbSoundBank = 0;
	if(m_pbWaveBank){
        UnmapViewOfFile(m_pbWaveBank);
	}
    m_pbWaveBank = 0;
}

/**************************************************************************
	virtual void _Sound::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void _Sound::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//サウンドは表示デバイスに関係ないので何もしない
}

/**************************************************************************
 virtual void _Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）このクラスでは何もしない
 戻り値: なし。
***************************************************************************/
void _Sound::Draw( DrawPacket& i_DrawPacket ){
	//サウンドエンジンに作業時間を与える
	m_pEngine && m_pEngine->DoWork();
}

namespace Avoidance{

/**************************************************************************
 OneSound 定義部
****************************************************************************/
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = m_pWaveBank->GetWaveIndex( pSoundName );
	}
}
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = iSoundNum ;
	}
}
void OneSound::PlaySound(BYTE count){
	/*/
	if(m_pWaveBank){
		m_pWaveBank->Play(i_iSoundNum, XACT_FLAG_UNITS_MS,0,count,NULL);
	}
	/*/
	if(m_pSoundBank){
		m_pSoundBank->Play(i_iSoundNum, 0,0 ,NULL );
	}
	//*/
}

}

/**************************************************************************
 Sound 定義部
****************************************************************************/
//-----------//
//	非公開   //
//-----------//

/////////////////// ////////////////////
//// 用途       ：bool Sound::SearchSoundMap( PCSTR  i_pSoundName , XACTINDEX& o_SoundNum ) ;
//// カテゴリ   ：サーチャー
//// 用途       ：サウンドマップから指定された音を探し出す
//// 引数       ：  PCSTR         i_pSoundName        //  : [ IN  ]音声名
////            ：  XACTINDEX&    o_SoundNum          //  : [ OUT ]発見した音声番号
//// 戻値       ：true   : 発見した
////            ：false  : 出来なかった
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchSoundMap( PCSTR  pSoundName , XACTINDEX& o_SoundNum ) {
	if( m_SoundMap.count(  pSoundName ) ){	//	: マップ内にすでに登録はあるか
		o_SoundNum = m_SoundMap[ pSoundName ] ;
		return true ;
	}
	return false ;
}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchSoundBank(PCSTR  pSoundName , XACTINDEX& o_SoundNum){
	//	: サウンドファイル内には登録されているか
	XACTINDEX SoundNum = m_pSoundBank->GetCueIndex( pSoundName ) ;
	if( SoundNum != XACTINDEX_INVALID ){
		//	: サウンドマップへ登録
		m_SoundMap.insert( SOUNDLISTMAP::value_type( pSoundName, SoundNum) );
		o_SoundNum = SoundNum ;
		return true ;

	}
	return false ;
}


/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchWaveMap( PCSTR  pWaveName , XACTINDEX& o_WaveNum ) {
	if( m_WaveMap.count(  pWaveName ) ){	//	: マップ内にすでに登録はあるか
		o_WaveNum = m_WaveMap[ pWaveName ] ;
		return true ;
	}
	return false ;
}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchWaveBank(PCSTR  pWaveName , XACTINDEX& o_WaveNum){
	//	: サウンドファイル内には登録されているか
	XACTINDEX WaveNum = m_pWaveBank->GetWaveIndex( pWaveName ) ;
	if( WaveNum != XACTINDEX_INVALID ){
		//	: サウンドマップへ登録
		m_WaveMap.insert( SOUNDLISTMAP::value_type( pWaveName, WaveNum) );
		o_WaveNum = WaveNum ;
		return true ;

	}
	return false ;
}


//-----------//
//	 公開    //
//-----------//

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id)
:_Sound(pWavBankFileName, pSoundBankFileName, id )
{
}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Sound::Update( UpdatePacket& i_UpdatePacket ){
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	if( GetAsyncKeyState( MYVK_DEBUG_SWITCHING_SOUND ) )
		DxDevice::SwitchingSoundOnOff();
	if( DxDevice::getIsPlaySound() )
		Debugger::DBGSTR::addStrTop( L"[F6]Sound ON\n" );
	else
		Debugger::DBGSTR::addStrTop( L"[F6]Sound OFF\n" );
	
#endif
}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchSoundAndPlay(PCSTR pSoundName){

	//	: ぬるぽ->ガッ
	if( this != NULL && DxDevice::getIsPlaySound() && m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pSoundName, SoundNum ) || SearchSoundBank( pSoundName, SoundNum ) ){
			m_pSoundBank->Play( SoundNum, 0,0 ,NULL );
			return true ;
		}
	}

	return false ;
}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Sound::SearchWaveAndPlay(PCSTR pWaveName, BYTE count){

	//	: ぬるぽ->ガッ
	if( DxDevice::getIsPlaySound() && m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Play( WaveNum, XACT_FLAG_UNITS_MS, 0, count, NULL );
		}
	}

	return false ;
}

void	Sound::SearchSoundAndStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pWaveName, SoundNum ) || SearchSoundBank( pWaveName, SoundNum ) ){
			m_pSoundBank->Stop( SoundNum, true );
		}
	}
}

void	Sound::SearchWaveAndStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Stop( WaveNum, true );
		}
	}
}

void	Sound::SoundStop(PCSTR pWaveName){
	if( m_pEngine && m_pWaveBank && m_pSoundBank ){
		XACTINDEX WaveNum ;
		if(SearchWaveMap( pWaveName, WaveNum ) || SearchWaveBank( pWaveName, WaveNum ) ){
			m_pWaveBank->Stop( WaveNum, true );
		}
		XACTINDEX SoundNum ;
		if(SearchSoundMap( pWaveName, SoundNum ) || SearchSoundBank( pWaveName, SoundNum ) ){
			m_pSoundBank->Stop( SoundNum, true );
		}
	}
}

/**************************************************************************
 Factory_Sound 定義部
****************************************************************************/
/**************************************************************************
 Factory_Sound::Factory_Sound(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Sound::Factory_Sound(FactoryPacket* fpac){
	try{
		//	:BGM-TITLE----------:タイトル画面で流れるBGM

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Sound::~Factory_Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Sound::~Factory_Sound(){
    //なにもしない
}

}
//end of namespace system.
//using namespace system;
}
//end of namespace wiz.
