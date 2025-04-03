////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：ComparingFlags.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：コンパイルふらぐ デバッグ用関数を切ったりつけたりそんな感じ
//					▼
//
#ifndef	__Comparing_Flags__
#define	__Comparing_Flags__


//////////
//	: コンパイリングフラグ
#define CF_SINGLETHREAD					/* シングルスレッドモード  ( 無効にするとマルチスレッド的になりますがバグります )   */
#define DRAW_MOUSE	(false)				/* マウスを描画するかどうか */

#define DEBUG_KEYBORD_ON				/* デバッグ用キーボード操作を有効化 */
#define CF_OVERLORDNEW_ENABLE			/* 自作のnewを強制化(Manager有効時) */
#define CF_MEMORYOUTPUTPROCESS_ENABLE	/* 自作メモリ管理システムにより管理されているアイテムのファイルへの書き出しを可能にする(Manager有効時) */
///#define CF_LOADINGANIMATION			/* ロード画面でアニメーション */
//#define CF_OVERLORDNEW_ENABLE			/* 自作のnewを強制化 */

#define CF_DEBUG_TIMEDRAW				/* 時間を描画 */
//#define CF_LOADINGANIMATION			/* ロード画面でアニメーション */


#if defined(DEBUG) || defined(_DEBUG)
	//-------------------------------//
	//		デバッグモード定義       //
	//-------------------------------//
	#define ON_DEBUGGINGPROCESS					/* デバックモード             */
	//#define DEBUG_STRINGS_ON					/* デバッグ用文字列を有効化 */
	//#define CF_DEBUGINFORMATIONWINDOW_ENABLE	/* デバッグ情報表示用ウインドウを有効化 */
	//#define CF_MEMORYMANAGER_ENABLE			/* 自作メモリ管理システムを有効化 */
	//#define CF_FULLSCREEN				/* フルスクリーンモード       */

	//#define ___MLP_DEBUG_TIMEDRAW_ 
	//#define ON_GUIDELINE
#else
	#if defined( PRESENTATION )
	//-------------------------------//
	//		プレゼンモード定義       //
	//-------------------------------//
		//#define DEBUG_STRINGS_ON					/* デバッグ用文字列を有効化 */
		//#define CF_MEMORYMANAGER_ENABLE			/* 自作メモリ管理システムを有効化 */
//		#define CF_FULLSCREEN				/* フルスクリーンモード       */
		//#define DEBUG_STRINGS_ON			/* デバッグ用文字列を有効化 */

	#else
	//-------------------------------//
	//		リリースモード定義       //
	//-------------------------------//

		#define CF_FULLSCREEN				/* フルスクリーンモード       */
	#endif

#endif
//
//////////


#endif