////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Sound.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包データと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Sound ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace system{

/**************************************************************************
 class Sound: public Object;
 用途: サウンドクラス
****************************************************************************/
class _Sound : public Object{
protected:
	class MyQue{
		XACTINDEX CueNum	;
		IXACT3Cue *m_pCue	;
	};

protected:
	IXACT3Engine* m_pEngine;
	XACT_NOTIFICATION_CALLBACK m_fnNotificationCallback;
	//通知用のコールバック関数
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
	wstring m_WavBankFileName;
	wstring m_SoundBankFileName;


	IXACT3Cue *m_pCue[0xFF];

/**************************************************************************
 void CreateInctance();
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
	void CreateInctance();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wavバンクのファイル名
 const wchar_t* pSoundBankFileName = 0,	//Soundバンクのファイル名（オプション）
 XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0	//通知用コールバック関数のポインタ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	_Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id,
		XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0);
/**************************************************************************
 virtual ~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~_Sound();
/**************************************************************************
	virtual void ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ReleaseObj();
/**************************************************************************
	virtual void ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
    virtual void Draw( DrawPacket& i_DrawPacket );
};
namespace Avoidance{
class OneSound : public _Sound{
	XACTINDEX i_iSoundNum ;
public:
	OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id);
	OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,const XACTINDEX iSoundNum,wiz::OBJID id);
	void PlaySound(BYTE count = 0);

};
}

class Sound : public _Sound{

	typedef  map< PCSTR , XACTINDEX > SOUNDLISTMAP;
	SOUNDLISTMAP  m_SoundMap ;
	SOUNDLISTMAP  m_WaveMap ;
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
	bool SearchSoundMap(PCSTR  pSoundName , XACTINDEX& o_SoundNum);

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
	bool SearchSoundBank(PCSTR  pSoundName , XACTINDEX& o_SoundNum);

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
	bool SearchWaveMap( PCSTR  pWaveName , XACTINDEX& o_WaveNum );

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
	bool SearchWaveBank(PCSTR  pWaveName , XACTINDEX& o_WaveNum);


public:

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
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id);
	
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
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：BGMを再生するときにはこちらを利用してください
	////            ：
	////
	bool SearchSoundAndPlay(PCSTR pSoundName);
	
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
	bool SearchWaveAndPlay(PCSTR pSoundName, BYTE count = 0);

	void SearchSoundAndStop(PCSTR pSoundName);
	void SearchWaveAndStop(PCSTR pSoundName);
	void SoundStop(PCSTR pSoundName);

};

/**************************************************************************
class Factory_Sound;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Sound{
public:
/**************************************************************************
 Factory_Sound(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Sound(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Sound();
};

}
//end of namespace system.
//using namespace system;
}
//end of namespace wiz.
