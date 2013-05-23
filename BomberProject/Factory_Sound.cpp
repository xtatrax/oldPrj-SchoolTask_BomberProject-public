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
/**************************************************************************
 Sound 定義部
****************************************************************************/

/**************************************************************************
 void Sound::CreateInctance();
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
void Sound::CreateInctance(){
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
				L"Sound::CreateInctance()"
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
				L"Sound::CreateInctance()"
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
									L"Sound::CreateInctance()"
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
					L"Sound::CreateInctance()"
					);
			}
		}
		//Soundバンクの作成
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
									L"Soundバンクハンドル初期化に失敗しました。",
									L"Sound::CreateInctance()"
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
					//				L"Soundバンクハンドル初期化に失敗しました。",
					//				L"Sound::CreateInctance()"
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
					L"Sound::CreateInctance()"
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
 Sound::Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName = 0,	//Soundバンクのファイル名（オプション）
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//通知用コールバック関数のポインタ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,wiz::OBJID id,
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
				L"Sound::Sound()"
				);
		}
		m_WavBankFileName = pWavBankFileName;
		if( pSoundBankFileName ){
			m_SoundBankFileName = pSoundBankFileName;
		}
		CreateInctance();
	}
	catch(...){
		ReleaseObj();
		//再throw
		throw;
	}
}
/**************************************************************************
 virtual Sound::~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sound::~Sound(){
	ReleaseObj();
}

/**************************************************************************
	virtual void Sound::ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Sound::ReleaseObj(){
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
	virtual void Sound::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
void Sound::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//サウンドは表示デバイスに関係ないので何もしない
}

/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）このクラスでは何もしない
 戻り値: なし。
***************************************************************************/
void Sound::Draw( DrawPacket& i_DrawPacket ){
	//サウンドエンジンに作業時間を与える
	m_pEngine->DoWork();
}
/**************************************************************************
 OneSound 定義部
****************************************************************************/
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id)
:Sound(pWavBankFileName, pSoundBankFileName, id )
{
	if(m_pEngine && m_pWaveBank && m_pSoundBank){
		i_iSoundNum = m_pWaveBank->GetWaveIndex( pSoundName );
	}
}
OneSound::OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id)
:Sound(pWavBankFileName, pSoundBankFileName, id )
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

		fpac->m_pVec->push_back(
			new OneSound(
				L"media/Sound/MagneticaWave.xwb",
				L"media/Sound/MagneticaSound.xsb",
				"bgm001",
				OBJID_SOUND_BGM_TITLE
			)
		);
		fpac->m_pVec->push_back(
			new OneSound(
				L"media/Sound/MagneticaWave.xwb",
				L"media/Sound/MagneticaSound.xsb",
				"bgm002",
				OBJID_SOUND_BGM_PLAY
			)
		);

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


//end of namespace wiz.
