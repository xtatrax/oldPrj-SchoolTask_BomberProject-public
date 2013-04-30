/**************************************************************************
 Prim.h

 アプリケーションクラス
 タイマー、コントローラ、テクスチャ
 シャドウボリューム　宣言

****************************************************************************/
#pragma once

#include "StdAfx.h"

namespace wiz{

///**************************************************************************
// class App;
// 用途: アプリケーションクラス
//****************************************************************************/
//class App{
//	//Singletonで利用する自分自身のポインタ
//	static App* m_pApp;
///**************************************************************************
// App(HINSTANCE hInstance,HWND hWnd);
// 用途: コンストラクタ
// 戻り値: なし
// Singletonで作成するためコンストラクタ、デストラクタはprivat
//***************************************************************************/
//	App(HINSTANCE hInstance,HWND hWnd);
///**************************************************************************
// ~App();
// 用途: デストラクタ
// 戻り値: なし
// Singletonで作成するためコンストラクタ、デストラクタはprivat
//***************************************************************************/
//	~App(){}
//public:
//	template<typename T> friend inline void SafeDelete(T*& p);
///**************************************************************************
// static App* GetApp(
// HINSTANCE hInstance = 0,
// HWND hWnd = 0
// );
// 用途: Singletonのためのインスタンス構築（static関数）
// 戻り値: 構築したAppのインスタンス
//***************************************************************************/
//	static App* GetApp(HINSTANCE hInstance = 0,HWND hWnd = 0){
//		//もしAppのインスタンス構築前なら構築
//		if(!m_pApp){
//			m_pApp = new App(hInstance,hWnd);
//		}
//		//Appのインスタンスを返す
//		return m_pApp;
//	}
///**************************************************************************
// static void FreeApp();
// 用途: Singletonのためのインスタンス破棄（static関数）
// 戻り値: なし
//***************************************************************************/
//	static void FreeApp(){
//		//Appインスタンスが構築されていたらdelete
//		SafeDelete(m_pApp);
//	}
///**************************************************************************
//公開変数
//***************************************************************************/
//	//モジュールのインスタンス
//	HINSTANCE m_hInstance;
//	//メインウインドウのハンドル
//	HWND m_hWnd;
//	//モジュール名フルパス
//	wstring m_wstrModulePath;
//	//モジュールがあるディレクトリ
//	wstring m_wstrDir;
//	//メディアディレクトリ
//	wstring m_wstrDataPath;
//};
//
/**************************************************************************
 class Timer;
 用途: タイマー(DXUTのCDXUTTimerを改変)
****************************************************************************/
class Timer{
protected:
/**************************************************************************
 LARGE_INTEGER   GetAdjustedCurrentTime();
 用途: 現在のパフォーマンスカウンタを得る
 戻り値: LARGE_INTEGER。
 ＊もしストップ中ならストップタイムを返す
//--------------------------------------------------------------------------------------
// If stopped, returns time when stopped otherwise returns current time
//--------------------------------------------------------------------------------------
***************************************************************************/
    LARGE_INTEGER   GetAdjustedCurrentTime();
    bool m_bUsingQPF;
    bool m_bTimerStopped;
    LONGLONG m_llQPFTicksPerSec;

    LONGLONG m_llStopTime;
    LONGLONG m_llLastElapsedTime;
    LONGLONG m_llBaseTime;
public:
/**************************************************************************
 Timer();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Timer();
/**************************************************************************
 ~Timer();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Timer(){}
/**************************************************************************
 void Reset();
 用途: タイマーのリセット
 戻り値: なし
 // resets the timer
***************************************************************************/
    void Reset();
/**************************************************************************
 void Start();  
 用途: タイマーのスタート
 戻り値: なし
// starts the timer
***************************************************************************/
    void Start();
/**************************************************************************
 void Stop();  
 用途: タイマーのストップ
 戻り値: なし
// stop (or pause) the timer
***************************************************************************/
    void Stop();  
/**************************************************************************
 void Advance();
 用途: タイマーを0.1秒進める
 戻り値: なし
// advance the timer by 0.1 seconds
***************************************************************************/
    void Advance(); 
/**************************************************************************
 double GetAbsoluteTime();
 用途: システムタイマー（パフォーマンスカウンタ時刻）を得る
 戻り値: システムタイマー（パフォーマンスカウンタ時刻）
// get the absolute system time
***************************************************************************/
    double GetAbsoluteTime(); 
/**************************************************************************
 double GetTime(); 
 用途: カレントの経過時間を得る
 戻り値:カレントの経過時間
// get the current time
***************************************************************************/
    double GetTime(); 
/**************************************************************************
 float GetElapsedTime(); 
 用途: 前回GetElapsedTimeが呼ばれてからの経過時間を得る
 戻り値: 経過時間
// get the time that elapsed between GetElapsedTime() calls
***************************************************************************/
    float GetElapsedTime(); 
/**************************************************************************
 void GetTimeValues(
 double& rfTime,		//カレント時間
 double& rfAbsoluteTime,	//絶対時間
 float& rfElapsedTime		//前回GetElapsedTimeが呼ばれてからの経過時間
 ); 
 用途: すべてのデータを得る。
 ＊前回GetElapsedTimeが呼ばれてからの経過時間も得る
 戻り値: なし（指定の参照にセット）
// get all time values at once
***************************************************************************/
    void GetTimeValues( double& rfTime, double& rfAbsoluteTime, float& rfElapsedTime ); 
/**************************************************************************
 bool IsStopped(); 
 用途: タイマーが止まってるかどうかを調べる
 戻り値: タイマーが止まってればtrue
// returns true if timer stopped
***************************************************************************/
    bool IsStopped(); 
};



/**************************************************************************
 class ShadowVolume;
 用途: シャドウボリュームクラス
 ＊DXUTサンプルをベースに作成
****************************************************************************/
class ShadowVolume{
protected:
	/**************************************************************************
	 struct SHADOWVERT;
	 用途: 影のFVFデータ
	 ＊DXUTより引用
	****************************************************************************/
	struct SHADOWVERT
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		const static D3DVERTEXELEMENT9 Decl[3];
	};
	/**************************************************************************
	 struct CEdgeMapping;
	 用途: エッジマッピングクラス
	 ＊DXUTより引用
	****************************************************************************/
	struct CEdgeMapping
	{
		int m_anOldEdge[2];  // vertex index of the original edge
		int m_aanNewEdge[2][2]; // vertex indexes of the new edge
		// First subscript = index of the new edge
		// Second subscript = index of the vertex for the edge
	public:
			CEdgeMapping()
			{
				FillMemory( m_anOldEdge, sizeof( m_anOldEdge ), -1 );
				FillMemory( m_aanNewEdge, sizeof( m_aanNewEdge ), -1 );
			}
	};
	const FLOAT ADJACENCY_EPSILON;
	LPD3DXMESH m_pShadowVolumeMesh;
	IDirect3DVertexDeclaration9*    m_pShadowDecl;
	/**************************************************************************
	 int FindEdgeInMappingTable()関数
	 用途: エッジマッピング関数
	 ＊DXUTより引用
	****************************************************************************/
	//--------------------------------------------------------------------------------------
	// Takes an array of CEdgeMapping objects, then returns an index for the edge in the
	// table if such entry exists, or returns an index at which a new entry for the edge
	// can be written.
	// nV1 and nV2 are the vertex indexes for the old edge.
	// nCount is the number of elements in the array.
	// The function returns -1 if an available entry cannot be found.  In reality,
	// this should never happens as we should have allocated enough memory.
	int FindEdgeInMappingTable( int nV1, int nV2, CEdgeMapping* pMapping, int nCount )
	{
		for( int i = 0; i < nCount; ++i )
		{
			// If both vertex indexes of the old edge in mapping entry are -1, then
			// we have searched every valid entry without finding a match.  Return
			// this index as a newly created entry.
			if( ( pMapping[i].m_anOldEdge[0] == -1 && pMapping[i].m_anOldEdge[1] == -1 ) ||

				// Or if we find a match, return the index.
				( pMapping[i].m_anOldEdge[1] == nV1 && pMapping[i].m_anOldEdge[0] == nV2 ) )
			{
				return i;
			}
		}

		return -1;  // We should never reach this line
	}
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//デバイス
 LPD3DXMESH pMesh			//元となるメッシュ
 );
 用途: コンストラクタ（シャドウボリュームを作成する）
 戻り値: なし
***************************************************************************/
	ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh);
/**************************************************************************
 ~ShadowVolume();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~ShadowVolume();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect			//エフェクトへのポインタ
 );
 用途: 影ボリュームを描画
 戻り値: なし。
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect);
};

}
//end of namespace base

