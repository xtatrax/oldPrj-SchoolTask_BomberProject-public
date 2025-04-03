/**************************************************************************
 Prim.cpp

 アプリケーションクラス
 タイマー、コントローラ、テクスチャ
 シャドウボリューム　実体

****************************************************************************/
#include "StdAfx.h"

namespace wiz{
namespace Avoidance{


///**************************************************************************
// class App;
// 用途: アプリケーションクラス
//****************************************************************************/
//
////Appクラス内のスタティック変数の初期化
//App* App::m_pApp(0);
//
//
///**************************************************************************
// App::App(HINSTANCE hInstance,HWND hWnd);
// 用途: コンストラクタ
// 戻り値: なし
// Singletonで作成するためコンストラクタ、デストラクタはprivat
//***************************************************************************/
//App::App(HINSTANCE hInstance,HWND hWnd)
//:m_hInstance(hInstance),m_hWnd(hWnd)
//{
//	try{
//		//基準ディレクトリの設定
//		//相対パスにすると、ファイルダイアログでカレントパスが狂うので
//		//絶対パス指定
//		wchar_t Modulebuff[MAX_PATH];
//		wchar_t Drivebuff[_MAX_DRIVE];
//		wchar_t Dirbuff[_MAX_DIR];
//		wchar_t FileNamebuff[_MAX_FNAME];
//		wchar_t Extbuff[_MAX_EXT];
//
//		::ZeroMemory( Modulebuff, sizeof(Modulebuff) );  
//		::ZeroMemory( Drivebuff, sizeof(Drivebuff) );
//		::ZeroMemory( Dirbuff, sizeof(Dirbuff) );
//		::ZeroMemory( FileNamebuff,sizeof(FileNamebuff) );
//		::ZeroMemory( Extbuff, sizeof(Extbuff) );
//
//		//モジュール名（プログラムファイル名）を得る
//		if(!::GetModuleFileName(NULL,Modulebuff,sizeof(Modulebuff))){
//			throw BaseException(L"モジュールが取得できません。",
//			L"App::App()");
//		}
//		m_wstrModulePath = Modulebuff;
//		//モジュール名から、各ブロックに分ける
//		_wsplitpath_s(Modulebuff,
//			Drivebuff,_MAX_DRIVE,
//			Dirbuff,_MAX_DIR,
//			FileNamebuff,_MAX_FNAME,
//			Extbuff,_MAX_EXT);
//
//		//ドライブ名の取得
//		m_wstrDir = Drivebuff;
//		//ディレクトリ名の取得
//		m_wstrDir += Dirbuff;
//		m_wstrDataPath = m_wstrDir;
//		m_wstrDataPath += L"..\\media\\";
//	}
//	catch(...){
//		//再スロー
//		throw;
//	}
//}

/**************************************************************************
Timer*  WINAPI GetGlobalTimer();
 用途: グローバルタイマーを得る
 戻り値: グローバルタイマー
 ＊アプリケーション起動時にスタートさせる
***************************************************************************/
Timer* WINAPI  GetGlobalTimer()
{
    // Using an accessor function gives control of the construction order
    static Timer timer;
    return &timer;
}


/**************************************************************************
 Timer::Timer();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Timer::Timer(){
    m_bTimerStopped = true;
    m_llQPFTicksPerSec = 0;

    m_llStopTime = 0;
    m_llLastElapsedTime = 0;
    m_llBaseTime = 0;

    // Use QueryPerformanceFrequency to get the frequency of the counter
    LARGE_INTEGER qwTicksPerSec = { 0 };
    QueryPerformanceFrequency( &qwTicksPerSec );
    m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;
}

/**************************************************************************
 void Timer::Reset();
 用途: タイマーのリセット
 戻り値: なし
 // resets the timer
***************************************************************************/
void Timer::Reset(){
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    m_llBaseTime = qwTime.QuadPart;
    m_llLastElapsedTime = qwTime.QuadPart;
    m_llStopTime = 0;
    m_bTimerStopped = FALSE;
}

/**************************************************************************
 void Timer::Start();  
 用途: タイマーのスタート
 戻り値: なし
// starts the timer
***************************************************************************/
void Timer::Start()
{
    // Get the current time
    LARGE_INTEGER qwTime = { 0 };
    QueryPerformanceCounter( &qwTime );

    if( m_bTimerStopped )
        m_llBaseTime += qwTime.QuadPart - m_llStopTime;
    m_llStopTime = 0;
    m_llLastElapsedTime = qwTime.QuadPart;
    m_bTimerStopped = FALSE;
}

/**************************************************************************
 void Timer::Stop();  
 用途: タイマーのストップ
 戻り値: なし
// stop (or pause) the timer
***************************************************************************/
void Timer::Stop(){
    if( !m_bTimerStopped ){
        LARGE_INTEGER qwTime = { 0 };
        QueryPerformanceCounter( &qwTime );
        m_llStopTime = qwTime.QuadPart;
        m_llLastElapsedTime = qwTime.QuadPart;
        m_bTimerStopped = TRUE;
    }
}


/**************************************************************************
 void Timer::Advance();
 用途: タイマーを0.1秒進める
 戻り値: なし
// advance the timer by 0.1 seconds
***************************************************************************/
void Timer::Advance(){
    m_llStopTime += m_llQPFTicksPerSec / 10;
}

/**************************************************************************
 double Timer::GetAbsoluteTime();
 用途: システムタイマー（パフォーマンスカウンタ時刻）を得る
 戻り値: なし
// get the absolute system time
***************************************************************************/
double Timer::GetAbsoluteTime(){
    LARGE_INTEGER qwTime = { 0 };
    QueryPerformanceCounter( &qwTime );

    double fTime = qwTime.QuadPart / ( double )m_llQPFTicksPerSec;

    return fTime;
}

/**************************************************************************
 double  Timer::GetTime(); 
 用途: カレントの経過時間を得る
 戻り値:カレントの経過時間
// get the current time
***************************************************************************/
double Timer::GetTime(){
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    double fAppTime = ( double )( qwTime.QuadPart - m_llBaseTime ) / ( double )m_llQPFTicksPerSec;

    return fAppTime;
}


/**************************************************************************
 void Timer::GetTimeValues(
 double& rfTime,		//カレント時間
 double& rfAbsoluteTime,	//絶対時間
 float& rfElapsedTime		//前回GetElapsedTimeが呼ばれてからの経過時間
 ); 
 用途: すべてのデータを得る。
 ＊前回GetElapsedTimeが呼ばれてからの経過時間も得る
 戻り値: なし（指定の参照にセット）
// get all time values at once
***************************************************************************/
void Timer::GetTimeValues( double& rfTime, double& rfAbsoluteTime, float& rfElapsedTime ){

    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    float fElapsedTime = ( float )( ( double )( qwTime.QuadPart - m_llLastElapsedTime ) / ( double )
                                    m_llQPFTicksPerSec );
    m_llLastElapsedTime = qwTime.QuadPart;

    // Clamp the timer to non-negative values to ensure the timer is accurate.
    // fElapsedTime can be outside this range if processor goes into a 
    // power save mode or we somehow get shuffled to another processor.  
    // However, the main thread should call SetThreadAffinityMask to ensure that 
    // we don't get shuffled to another processor.  Other worker threads should NOT call 
    // SetThreadAffinityMask, but use a shared copy of the timer data gathered from 
    // the main thread.
    if( fElapsedTime < 0.0f )
        fElapsedTime = 0.0f;

    rfAbsoluteTime = qwTime.QuadPart / ( double )m_llQPFTicksPerSec;
    rfTime = ( qwTime.QuadPart - m_llBaseTime ) / ( double )m_llQPFTicksPerSec;
    rfElapsedTime = fElapsedTime;
}


/**************************************************************************
 float Timer::GetElapsedTime(); 
 用途: 前回GetElapsedTimeが呼ばれてからの経過時間を得る
 戻り値: 経過時間
// get the time that elapsed between GetElapsedTime() calls
***************************************************************************/
float Timer::GetElapsedTime(){
    LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

    double fElapsedTime = ( float )( ( double )( qwTime.QuadPart - m_llLastElapsedTime ) / ( double )
                                     m_llQPFTicksPerSec );
    m_llLastElapsedTime = qwTime.QuadPart;

    // See the explanation about clamping in CDXUTTimer::GetTimeValues()
    if( fElapsedTime < 0.0f )
        fElapsedTime = 0.0f;

    return ( float )fElapsedTime;
}
/**************************************************************************
 LARGE_INTEGER   Timer::GetAdjustedCurrentTime();
 用途: 現在のパフォーマンスカウンタを得る
 戻り値: LARGE_INTEGER。
 ＊もしストップ中ならストップタイムを返す
//--------------------------------------------------------------------------------------
// If stopped, returns time when stopped otherwise returns current time
//--------------------------------------------------------------------------------------
***************************************************************************/
LARGE_INTEGER Timer::GetAdjustedCurrentTime(){
    LARGE_INTEGER qwTime;
    if( m_llStopTime != 0 )
        qwTime.QuadPart = m_llStopTime;
    else
        QueryPerformanceCounter( &qwTime );
    return qwTime;
}

/**************************************************************************
 bool Timer::IsStopped(); 
 用途: タイマーが止まってるかどうかを調べる
 戻り値: タイマーが止まってればtrue
// returns true if timer stopped
***************************************************************************/
bool Timer::IsStopped(){
    return m_bTimerStopped;
}



/**************************************************************************
 ShadowVolume関連
****************************************************************************/
//影ボリュームのFVF定義
const D3DVERTEXELEMENT9 ShadowVolume::SHADOWVERT::Decl[3] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
    D3DDECL_END()
};
/**************************************************************************
 ShadowVolume 定義部
****************************************************************************/

/**************************************************************************
 void ShadowVolume::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void ShadowVolume::Clear(){
    //後始末
    SafeRelease(m_pShadowVolumeMesh);
	SafeRelease(m_pShadowDecl);
}

/**************************************************************************
 void ShadowVolume::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect			//エフェクトへのポインタ
 );
 用途: 影ボリュームを描画
 戻り値: なし。
***************************************************************************/
void ShadowVolume::Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect){
    if(m_pShadowVolumeMesh)
    {
        pD3DDevice->SetVertexDeclaration(m_pShadowDecl) ;
        UINT cPasses;
        pEffect->Begin( &cPasses, 0 );
        for( UINT i = 0; i < cPasses; ++i )
        {
            pEffect->BeginPass( i );
            pEffect->CommitChanges();
            m_pShadowVolumeMesh->DrawSubset( 0 );
            pEffect->EndPass() ;
        }
        pEffect->End();
    }
}

/**************************************************************************
 ShadowVolume::ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//デバイス
 LPD3DXMESH pMesh,			//元となるメッシュ
 );
 用途: コンストラクタ（シャドウボリュームを作成する）
 *DXUTのShadowVolumeサンプルから改変して作成
 *GenerateShadowMesh()関数に例外処理を加え実装
 戻り値: なし
***************************************************************************/
ShadowVolume::ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh)
:m_pShadowVolumeMesh(0),
ADJACENCY_EPSILON(0.0001f),
m_pShadowDecl(0)
{

    ID3DXMesh* pInputMesh = 0;
	SHADOWVERT* pVBData = 0;
	DWORD* pdwIBData = 0;

	DWORD* pdwAdj = 0;
	DWORD* pdwPtRep = 0;
	CEdgeMapping* pMapping = 0;

	ID3DXMesh* pNewMesh = 0;
	SHADOWVERT* pNewVBData = 0;
	DWORD* pdwNewIBData = 0;

	ID3DXMesh* pPatchMesh = 0;
	SHADOWVERT* pPatchVBData = 0;
	DWORD* pdwPatchIBData = 0;

	ID3DXMesh* pFinalMesh = 0;
	SHADOWVERT* pFinalVBData = 0;
	WORD* pwFinalIBData = 0;
	try{
		if(!pd3dDevice || !pMesh){
            // 初期化失敗
            throw BaseException(
                L"デバイスか元となるメッシュが不定です",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Convert the input mesh to a format same as the output mesh using 32-bit index.
		if(FAILED(pMesh->CloneMesh( D3DXMESH_32BIT, SHADOWVERT::Decl, pd3dDevice, &pInputMesh))){
            // 初期化失敗
            throw BaseException(
                L"インプットクローンメッシュ作成に失敗しました。",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Generate adjacency information
		pdwAdj = new DWORD[3 * pInputMesh->GetNumFaces()];
		pdwPtRep = new DWORD[pInputMesh->GetNumVertices()];
		if( FAILED(pInputMesh->GenerateAdjacency(ADJACENCY_EPSILON, pdwAdj)))
		{
            // 初期化失敗
            throw BaseException(
                L"インプットメッシュエッジの取得に失敗しました。",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		pInputMesh->ConvertAdjacencyToPointReps( pdwAdj, pdwPtRep );
		//pdwAdjの開放
		SafeDeleteArr(pdwAdj);
		if(FAILED(pInputMesh->LockVertexBuffer( 0, ( LPVOID* )&pVBData ))){
            // 初期化失敗
            throw BaseException(
                L"インプットメッシュ頂点のロックに失敗しました。",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		if(FAILED(pInputMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwIBData ))){
            // 初期化失敗
            throw BaseException(
                L"インプットメッシュインデックスのロックに失敗しました。",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Maximum number of unique edges = Number of faces * 3
		DWORD dwNumEdges = pInputMesh->GetNumFaces() * 3;
		pMapping = new CEdgeMapping[dwNumEdges];
		int nNumMaps = 0;  // Number of entries that exist in pMapping
		// Create a new mesh
		if(FAILED(D3DXCreateMesh( pInputMesh->GetNumFaces() + dwNumEdges * 2,
							 pInputMesh->GetNumFaces() * 3,
							 D3DXMESH_32BIT,
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pNewMesh ))){
			// 初期化失敗
			throw BaseException(
				L"新しいメッシュのマッピングに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);

		}
		if(FAILED(pNewMesh->LockVertexBuffer( 0, ( LPVOID* )&pNewVBData ))){
			// 初期化失敗
			throw BaseException(
				L"新しいメッシュ頂点のロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwNewIBData ))){
			// 初期化失敗
			throw BaseException(
				L"新しいメッシュインデックスのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		// nNextIndex is the array index in IB that the next vertex index value
		// will be store at.
		int nNextIndex = 0;
		ZeroMemory( pNewVBData, pNewMesh->GetNumVertices() * pNewMesh->GetNumBytesPerVertex() );
		ZeroMemory( pdwNewIBData, sizeof( DWORD ) * pNewMesh->GetNumFaces() * 3 );
		// pNextOutVertex is the location to write the next
		// vertex to.
		SHADOWVERT* pNextOutVertex = pNewVBData;
		// Iterate through the faces.  For each face, output new
		// vertices and face in the new mesh, and write its edges
		// to the mapping table.
		for( UINT f = 0; f < pInputMesh->GetNumFaces(); ++f ){
			// Copy the vertex data for all 3 vertices
			CopyMemory( pNextOutVertex, pVBData + pdwIBData[f * 3], sizeof( SHADOWVERT ) );
			CopyMemory( pNextOutVertex + 1, pVBData + pdwIBData[f * 3 + 1], sizeof( SHADOWVERT ) );
			CopyMemory( pNextOutVertex + 2, pVBData + pdwIBData[f * 3 + 2], sizeof( SHADOWVERT ) );

			// Write out the face
			pdwNewIBData[nNextIndex++] = f * 3;
			pdwNewIBData[nNextIndex++] = f * 3 + 1;
			pdwNewIBData[nNextIndex++] = f * 3 + 2;

			// Compute the face normal and assign it to
			// the normals of the vertices.
			D3DXVECTOR3 v1, v2;  // v1 and v2 are the edge vectors of the face
			D3DXVECTOR3 vNormal;
			v1 = *( D3DXVECTOR3* )( pNextOutVertex + 1 ) - *( D3DXVECTOR3* )pNextOutVertex;
			v2 = *( D3DXVECTOR3* )( pNextOutVertex + 2 ) - *( D3DXVECTOR3* )( pNextOutVertex + 1 );
			D3DXVec3Cross( &vNormal, &v1, &v2 );
			D3DXVec3Normalize( &vNormal, &vNormal );

			pNextOutVertex->Normal = vNormal;
			( pNextOutVertex + 1 )->Normal = vNormal;
			( pNextOutVertex + 2 )->Normal = vNormal;

			pNextOutVertex += 3;

			// Add the face's edges to the edge mapping table

			// Edge 1
			int nIndex;
			int nVertIndex[3] =
			{
				pdwPtRep[pdwIBData[f * 3]],
				pdwPtRep[pdwIBData[f * 3 + 1]],
				pdwPtRep[pdwIBData[f * 3 + 2]]
			};
			nIndex = FindEdgeInMappingTable( nVertIndex[0], nVertIndex[1], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// 初期化失敗
				throw BaseException(
					L"エッジ１のマッピングに失敗しました。",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				// No entry for this edge yet.  Initialize one.
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[0];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[1];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 1;

				++nNumMaps;
			}
			else{
				// An entry is found for this edge.  Create
				// a quad and output it.

				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3;      // For clarity
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 1;

				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.

				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
			// Edge 2
			nIndex = FindEdgeInMappingTable( nVertIndex[1], nVertIndex[2], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// 初期化失敗
				throw BaseException(
					L"エッジ２のマッピングに失敗しました。",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[1];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[2];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 1;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 2;

				++nNumMaps;
			}
			else{
				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 1;
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 2;
				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.
				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
			// Edge 3
			nIndex = FindEdgeInMappingTable( nVertIndex[2], nVertIndex[0], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// 初期化失敗
				throw BaseException(
					L"エッジ３のマッピングに失敗しました。",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[2];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[0];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 2;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3;

				++nNumMaps;
			}
			else{
				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 2;
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3;

				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.

				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
		}

		// Now the entries in the edge mapping table represent
		// non-shared edges.  What they mean is that the original
		// mesh has openings (holes), so we attempt to patch them.
		// First we need to recreate our mesh with a larger vertex
		// and index buffers so the patching geometry could fit.

		// Create a mesh with large enough vertex and
		// index buffers.
		// Make enough room in IB for the face and up to 3 quads for each patching face
		if(FAILED(D3DXCreateMesh( nNextIndex / 3 + nNumMaps * 7,
							 ( pInputMesh->GetNumFaces() + nNumMaps ) * 3,
							 D3DXMESH_32BIT,
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pPatchMesh ))){
			// 初期化失敗
			throw BaseException(
				L"パッチメッシュの作成に失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pPatchMesh->LockVertexBuffer( 0, ( LPVOID* )&pPatchVBData ))){
			// 初期化失敗
			throw BaseException(
				L"パッチメッシュのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pPatchMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwPatchIBData ))){
			// 初期化失敗
			throw BaseException(
				L"パッチメッシュのインデックスロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		ZeroMemory( pPatchVBData, sizeof( SHADOWVERT ) * ( pInputMesh->GetNumFaces() + nNumMaps ) *3 );
		ZeroMemory( pdwPatchIBData, sizeof( DWORD ) * ( nNextIndex + 3 * nNumMaps * 7 ) );
		// Copy the data from one mesh to the other
		CopyMemory( pPatchVBData, pNewVBData, sizeof( SHADOWVERT ) * pInputMesh->GetNumFaces() * 3 );
		CopyMemory( pdwPatchIBData, pdwNewIBData, sizeof( DWORD ) * nNextIndex );
		// Replace pNewMesh with the updated one.  Then the code
		// can continue working with the pNewMesh pointer.
		pNewMesh->UnlockVertexBuffer();
		pNewMesh->UnlockIndexBuffer();
		pNewVBData = pPatchVBData;
		pdwNewIBData = pdwPatchIBData;
		pNewMesh->Release();
		pNewMesh = pPatchMesh;
		//パッチはもういらない
		pPatchVBData = 0;
		pdwPatchIBData = 0;
		pPatchMesh = 0;

		// Now, we iterate through the edge mapping table and
		// for each shared edge, we generate a quad.
		// For each non-shared edge, we patch the opening
		// with new faces.

		// nNextVertex is the index of the next vertex.
		int nNextVertex = pInputMesh->GetNumFaces() * 3;

		for( int i = 0; i < nNumMaps; ++i ){
			if( pMapping[i].m_anOldEdge[0] != -1 &&
				pMapping[i].m_anOldEdge[1] != -1 ){
				// If the 2nd new edge indexes is -1,
				// this edge is a non-shared one.
				// We patch the opening by creating new
				// faces.
				if( pMapping[i].m_aanNewEdge[1][0] == -1 ||  // must have only one new edge
					pMapping[i].m_aanNewEdge[1][1] == -1 ){
					// Find another non-shared edge that
					// shares a vertex with the current edge.
					for( int i2 = i + 1; i2 < nNumMaps; ++i2 ){
						if( pMapping[i2].m_anOldEdge[0] != -1 &&       // must have a valid old edge
							pMapping[i2].m_anOldEdge[1] != -1 &&
							( pMapping[i2].m_aanNewEdge[1][0] == -1 || // must have only one new edge
							  pMapping[i2].m_aanNewEdge[1][1] == -1 ) ){
							int nVertShared = 0;
							if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] )
								++nVertShared;
							if( pMapping[i2].m_anOldEdge[1] == pMapping[i].m_anOldEdge[0] )
								++nVertShared;

							if( 2 == nVertShared ){
								// These are the last two edges of this particular
								// opening. Mark this edge as shared so that a degenerate
								// quad can be created for it.

								pMapping[i2].m_aanNewEdge[1][0] = pMapping[i].m_aanNewEdge[0][0];
								pMapping[i2].m_aanNewEdge[1][1] = pMapping[i].m_aanNewEdge[0][1];
								break;
							}
							else if( 1 == nVertShared ){
								// nBefore and nAfter tell us which edge comes before the other.
								int nBefore, nAfter;
								if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] ){
									nBefore = i;
									nAfter = i2;
								}
								else{
									nBefore = i2;
									nAfter = i;
								}
								// Found such an edge. Now create a face along with two
								// degenerate quads from these two edges.
								pNewVBData[nNextVertex] = pNewVBData[pMapping[nAfter].m_aanNewEdge[0][1]];
								pNewVBData[nNextVertex + 1] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][1]];
								pNewVBData[nNextVertex + 2] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][0]];
								// Recompute the normal
								D3DXVECTOR3 v1
									= pNewVBData[nNextVertex + 1].Position - pNewVBData[nNextVertex].Position;
								D3DXVECTOR3 v2
									= pNewVBData[nNextVertex + 2].Position - pNewVBData[nNextVertex + 1].Position;
								D3DXVec3Normalize( &v1, &v1 );
								D3DXVec3Normalize( &v2, &v2 );
								D3DXVec3Cross( &pNewVBData[nNextVertex].Normal, &v1, &v2 );
								pNewVBData[nNextVertex + 1].Normal = pNewVBData[nNextVertex + 2].Normal = pNewVBData[nNextVertex].Normal;
								pdwNewIBData[nNextIndex] = nNextVertex;
								pdwNewIBData[nNextIndex + 1] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 2] = nNextVertex + 2;
								// 1st quad
								pdwNewIBData[nNextIndex + 3] = pMapping[nBefore].m_aanNewEdge[0][1];
								pdwNewIBData[nNextIndex + 4] = pMapping[nBefore].m_aanNewEdge[0][0];
								pdwNewIBData[nNextIndex + 5] = nNextVertex + 1;

								pdwNewIBData[nNextIndex + 6] = nNextVertex + 2;
								pdwNewIBData[nNextIndex + 7] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 8] = pMapping[nBefore].m_aanNewEdge[0][0];
								// 2nd quad
								pdwNewIBData[nNextIndex + 9] = pMapping[nAfter].m_aanNewEdge[0][1];
								pdwNewIBData[nNextIndex + 10] = pMapping[nAfter].m_aanNewEdge[0][0];
								pdwNewIBData[nNextIndex + 11] = nNextVertex;

								pdwNewIBData[nNextIndex + 12] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 13] = nNextVertex;
								pdwNewIBData[nNextIndex + 14] = pMapping[nAfter].m_aanNewEdge[0][0];

								// Modify mapping entry i2 to reflect the third edge
								// of the newly added face.

								if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] ){
									pMapping[i2].m_anOldEdge[0] = pMapping[i].m_anOldEdge[0];
								}
								else{
									pMapping[i2].m_anOldEdge[1] = pMapping[i].m_anOldEdge[1];
								}
								pMapping[i2].m_aanNewEdge[0][0] = nNextVertex + 2;
								pMapping[i2].m_aanNewEdge[0][1] = nNextVertex;

								// Update next vertex/index positions

								nNextVertex += 3;
								nNextIndex += 15;

								break;
							}
						}
					}
				}
				else{
					// This is a shared edge.  Create the degenerate quad.

					// First triangle
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][1];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];

					// Second triangle
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][1];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
				}
			}
		}

////////////////////
		pNewMesh->UnlockVertexBuffer();
		pNewVBData = 0;
		pNewMesh->UnlockIndexBuffer();
		pdwNewIBData = 0;
		bool bNeed32Bit = ( pInputMesh->GetNumFaces() + nNumMaps ) * 3 > 65535;
		if(FAILED(D3DXCreateMesh( nNextIndex / 3,  // Exact number of faces
							 ( pInputMesh->GetNumFaces() + nNumMaps ) * 3,
							 D3DXMESH_WRITEONLY | ( bNeed32Bit ? D3DXMESH_32BIT : 0 ),
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pFinalMesh ))){
			// 初期化失敗
			throw BaseException(
				L"ラストメッシュの作成に失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockVertexBuffer( 0, ( LPVOID* )&pNewVBData ))){
			// 初期化失敗
			throw BaseException(
				L"新メッシュのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwNewIBData ))){
			// 初期化失敗
			throw BaseException(
				L"新メッシュインデックスのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pFinalMesh->LockVertexBuffer( 0, ( LPVOID* )&pFinalVBData ))){
			// 初期化失敗
			throw BaseException(
				L"ラストメッシュのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pFinalMesh->LockIndexBuffer( 0, ( LPVOID* )&pwFinalIBData ))){
			// 初期化失敗
			throw BaseException(
				L"ラストメッシュインデックスのロックに失敗しました。",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		CopyMemory( pFinalVBData, pNewVBData, sizeof( SHADOWVERT ) *
					( pInputMesh->GetNumFaces() + nNumMaps ) * 3 );
		if( bNeed32Bit )
			CopyMemory( pwFinalIBData, pdwNewIBData, sizeof( DWORD ) * nNextIndex );
		else{
			for( int i = 0; i < nNextIndex; ++i )
				pwFinalIBData[i] = ( WORD )pdwNewIBData[i];
		}
		pNewMesh->UnlockVertexBuffer();
		pNewVBData = 0;
		pNewMesh->UnlockIndexBuffer();
		pdwNewIBData = 0;
		SafeRelease(pNewMesh);
		pFinalMesh->UnlockVertexBuffer();
		pFinalVBData = 0;
		pFinalMesh->UnlockIndexBuffer();
		pwFinalIBData = 0;
		m_pShadowVolumeMesh = pFinalMesh;
		pFinalMesh = 0;
		SafeDeleteArr(pMapping);
		SafeDeleteArr(pdwPtRep);
		pInputMesh->UnlockVertexBuffer();
		pVBData = 0;
		pInputMesh->UnlockIndexBuffer();
		pdwIBData = 0;
		SafeRelease(pInputMesh);

		if(FAILED(pd3dDevice->CreateVertexDeclaration( SHADOWVERT::Decl, &m_pShadowDecl  ))){
			// 初期化失敗
			throw BaseException(
				L"頂点定義に失敗しました",
				L"ShadowVolume::ShadowVolume()"
				);
		}

	}
	catch(...){
		if(pFinalVBData && pFinalMesh){
			pFinalMesh->UnlockVertexBuffer();
			pFinalVBData = 0;
		}
		if(pwFinalIBData && pFinalMesh){
			pPatchMesh->UnlockIndexBuffer();
			pwFinalIBData = 0;
		}
        SafeRelease(pFinalMesh);
		if(pPatchVBData && pPatchMesh){
			pPatchMesh->UnlockVertexBuffer();
			pPatchVBData = 0;
		}
		if(pdwPatchIBData && pPatchMesh){
			pPatchMesh->UnlockIndexBuffer();
			pdwPatchIBData = 0;
		}
        SafeRelease(pPatchMesh);
		if(pNewVBData && pNewMesh){
			pNewMesh->UnlockVertexBuffer();
			pNewVBData = 0;
		}
		if( pdwNewIBData && pNewMesh){
			pNewMesh->UnlockIndexBuffer();
			pdwNewIBData = 0;
		}
		SafeRelease(pNewMesh);

		SafeDeleteArr(pMapping);
		SafeDeleteArr(pdwPtRep);
		SafeDeleteArr(pdwAdj);

		if( pVBData && pInputMesh){
			pInputMesh->UnlockVertexBuffer();
			pVBData = 0;
		}
		if( pdwIBData && pInputMesh){
			pInputMesh->UnlockIndexBuffer();
			pdwIBData = 0;
		}
        SafeRelease(pInputMesh);
		Clear();
		//再スロー
		throw;
	}
	
}

/**************************************************************************
 ShadowVolume::~ShadowVolume();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
ShadowVolume::~ShadowVolume(){
		Clear();
}


}
}
//end of namespace base.

