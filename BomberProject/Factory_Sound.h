////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Sound.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject;
//		class Factory_Sound ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Sound.h"

namespace wiz{
/**************************************************************************
 class Sound: public Object;
 用途: サウンドクラス
****************************************************************************/
class Sound : public Object{
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
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName ,wiz::OBJID id,
		XACT_NOTIFICATION_CALLBACK fnNotificationCallback = 0);
/**************************************************************************
 virtual ~Sound();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Sound();
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
class OneSound : public Sound{
	XACTINDEX i_iSoundNum ;
public:
	OneSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,PCSTR pSoundName,wiz::OBJID id);
	void PlaySound(BYTE count = 0);

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
//end of namespace wiz.
