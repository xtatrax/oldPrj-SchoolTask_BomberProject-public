////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：DefineValue.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：グローバルなディファイン値群
//					▼
//
#ifndef	__Define_Value__
#define	__Define_Value__
//////////
// マクロ関数

#define TL_SQUARE(n)							((n)*(n))

//
//////////


//////////
//	: コンパイリングフラグ

#define CF_SINGLETHREAD			/* シングルスレッドモード     */
#define DRAW_MOUSE	(true)		
//#define CF_LOADINGANIMATION		/* ロード画面でアニメーション */
#if defined(DEBUG) || defined(_DEBUG)
	#define ON_DEBUGGINGPROCESS			/* デバックモード             */
	#define DEBUG_STRINGS_ON			/* デバッグ用文字列を有効化 */
	
	#define ___MLP_DEBUG_TIMEDRAW_ 
	//#define ON_GUIDELINE
	//#define CF_FULLSCREEN				/* フルスクリーンモード       */

#else
	#define CF_FULLSCREEN				/* フルスクリーンモード       */
#endif
#define DEBUG_KEYBORD_ON			/* デバッグ用キーボード操作を有効化 */

//	: デファイン定数
#define MAP_PARTS_HEIGHT		(    1.0f)	/*  */
#define MAP_PARTS_WIDTH			(    1.0f)	/*  */
#define BASE_CLIENT_HEIGHT		(  600.0f)	/* 基準になる描画領域の高さ */
#define BASE_CLIENT_WIDTH		( 1024.0f)	/* 基準になる描画領域の幅   */
#define STANDARD_WINDOW_HEIGHT  (  600.0f)	/* ウインドウモードの高さ   */
#define STANDARD_WINDOW_WIDTH   ( 1024.0f)	/* ウインドウモードの幅     */
#define DRAW_TOLERANCE			(   20.0f)	/* カメラからの描画距離 */

#define DEFAULT_WINDOW_TITLE		( L"ウインドウタイトル" )
#define DEFAULT_WINDOW_CLASS_NAME	( L"ウインドウクラスネーム" )

//	キーボード定義
#define MYVK_GAMEPAD_A				( 'X' )
#define MYVK_GAMEPAD_B				( 'C' )
#define MYVK_GAMEPAD_X				( 'S' )
#define MYVK_GAMEPAD_Y				( 'D' )

#define MYVK_GAMEPAD_BACK			( 'W' )
#define MYVK_GAMEPAD_START			( 'E' )
#define MYVK_GAMEPAD_LB				( 'A' )
#define MYVK_GAMEPAD_RB				( 'F' )

#define MYVK_GAMEPAD_POV_UP			( VK_UP    )
#define MYVK_GAMEPAD_POV_DOWN 		( VK_DOWN  )
#define MYVK_GAMEPAD_POV_RIGHT		( VK_RIGHT )
#define MYVK_GAMEPAD_POV_LEFT		( VK_LEFT  )

#define MYVK_GAMEPAD_STICK_UP		( 'I' )
#define MYVK_GAMEPAD_STICK_DOWN 	( 'K' )
#define MYVK_GAMEPAD_STICK_RIGHT	( 'L' )
#define MYVK_GAMEPAD_STICK_LEFT		( 'J' )


#define MYVK_DEBUG_STOP_UPDATE		( VK_F12 )
#define MYVK_DEBUG_SLOW_UPDATE		( VK_F11 )
#define MYVK_DEBUG_OUTPUT_DBGSTR	( VK_F9  )
#define MYVK_DEBUG_OUTPUT_MEMORY	( VK_F8  )
#define MYVK_DEBUG_OBB_DRAW			( VK_F7  )

//
//////////

//


//
namespace wiz{
	//	: ゲーム内メセージ
	enum{
		GM_WITHOUT				,
		GM_OPENSTAGE_TITLE		,
		GM_OPENSTAGE_PLAY		,
		GM_OPENSTAGE_RESULT		,
		GM_OPENSTAGE_RANKING	,
		GM_OPENSTAGE_OPTION		,
		GM_OPENSTAGE_GAMECLEAR	,
		GM_OPENSTAGE_GAMEOVER	,
		GM_EXIT					,

		GM_OPENDEBUGSTAGE_DEBUGMENU      ,
		GM_OPENDEBUGSTAGE_STAGELOADERTEST,
		GM_OPENDEBUGSTAGE_TATEAWORKSPACE ,
		GM_OPENDEBUGSTAGE_TOJIWORKSPACE  ,
		GM_OPENDEBUGSTAGE_HSWORKSPACE    ,
		GM_OPENDEBUGSTAGE_STAGECREATE    ,

		//////////
		//	: 
		GM_PLAYOPENING_END	,

	};
	//////	: 
	////enum CLASSID{
	////	/////////
	////	//
	////	//	この列挙型は外部ファイルで使用するので
	////	//	仕様に従い絶対に値を明記すること
	////	//

	////	CLASSID_NONE		=    0 ,
	////	CLASSID_TESTTIP		=    1 ,
	////	CLASSID_WALL		=  100 ,
	////	CLASSID_ENEMY		=    3 ,



	////	CLASSID_END			=  0xFFFFFFFFFFFFFFFF ,
	////};

	enum OBJID{
		OBJID_NONE					= 0x0000,	//	: なし
		OBJID_UNK					= 0x0001,	//	: 未定オブジェ

		//	: システム関係
		OBJID_SYS_BEGIN				= 0x1000,
		OBJID_SYS_GUIDELINE			,	//	: XYZガイド線( Debug用 )
		OBJID_SYS_CAMERA			,	//	: カメラ
		OBJID_SYS_LIGHT				,	//	: ライト
		OBJID_SYS_SOUND				,	//	: 音声
		OBJID_SYS_CHECKPOINT		,	//	: チェックポイント
		OBJID_SYS_CLEARAREA			,	//	: クリア領域
		OBJID_SYS_RENDERTARGET		,	//	: レンダーターゲット
		OBJID_SYS_END				,	


		//	:サウンドまわり
		//	:BGM
		OBJID_SOUND_BGM_TITLE		,
		OBJID_SOUND_BGM_PLAY		,
		OBJID_SOUND_BGM_CLEAR		,
		OBJID_SOUND_BGM_GAME_OVER	,

		//	:効果音
		OBJID_SOUND_SE_ALERT		,
		OBJID_SOUND_SE_BLOKEN_ENEMY	,
		OBJID_SOUND_SE_CHACK_POINT	,
		OBJID_SOUND_SE_CLEAR		,
		OBJID_SOUND_SE_ENTER		,
		OBJID_SOUND_SE_FIRE			,
		OBJID_SOUND_SE_GOAL			,
		OBJID_SOUND_SE_HIT_ENEMY	,
		OBJID_SOUND_SE_INVINGVLE	,
		OBJID_SOUND_SE_MAGNETIC_FIELD,
		OBJID_SOUND_SE_SPARK		,


		//	: UI周り
		OBJID_UI_BEGIN				= 0x2000,
		OBJID_UI_SPRITE				,	//	: UIに使うスプライト
		OBJID_UI_SPRITEBUTTON		,	//	: スプライトボタンのUI
		OBJID_UI_LIFE				,	//	: ライフ( 念のため )
		OBJID_UI_GAUGE				,	//	: ゲージ
		OBJID_UI_SCORE				,	//	: スコア
		OBJID_UI_TIME				,	//	: 時間( いる? )
		OBJID_UI_END				,

		//	: 3Dオブジェ
		////
		// プリミティブ系
		OBJID_3D_BEGIN				= 0x3000,
		OBJID_3D_POLYGON			,	//	: とりあえず読み込んだモデルデータ
		OBJID_3D_BOX				,	//	: とりあえず作った箱
		OBJID_3D_BOX_PARALLEL		,	//	: ぱられる?・・・
		OBJID_3D_SPHERE				,	//	: とりあえず作った球体
		OBJID_3D_CYLINDER			,	//	: とりあえず作った円柱円錐

		//	: マルチプリミティブ
		OBJID_3D_MULTI_POLYGON		,	
		OBJID_3D_MULTI_BOX			,
		OBJID_3D_MULTI_BOX_PARALLEL	,
		OBJID_3D_MULTI_SPHERE		,
		OBJID_3D_MULTI_CYLINDER		,
		OBJID_3D_MULTI_TAURUS		,
		// プリミティブ系
		////

		//	: 
		OBJID_3D_MAGNET				,	//	: 磁石
		OBJID_3D_WALL				,	//	: 壁
		OBJID_3D_ITEM				,	//	: アイテム

		//	:
		OBJID_3D_PLAYER				,
		OBJID_3D_USERMAGNET			,	//	: ユーザー
		OBJID_3D_COIL				,	//	: プレイヤー
		OBJID_3D_EFFECT				,	//	: エフェクト
		OBJID_3D_ENEMY				,	//	: 敵

		//	: 
		OBJID_3D_TESTBOX			,	//	: テスト用の箱
		OBJID_3D_DRAWOBB			,
		OBJID_3D_END				,


		//	: 終わり
		OBJID_END					=  0xFFFFFFFFFFFFFFFF ,

	} ;
	enum POLE{
		POLE_S , 		/* S極 */
		POLE_N , 		/* N極 */
	};


}
//
//////////

//////////
//	: グローバルな変数

extern D3DXVECTOR3 g_vZero ;	//	: ゼロベクトル
extern D3DXVECTOR3 g_vOne  ;	//	: 一ベクトル
extern D3DXVECTOR3 g_vMax  ;	//	: 最高ベクトル
extern D3DXVECTOR3 g_vMin  ;	//	: 最低ベクトル

extern wstring g_sDefaultTexturePath ;	//	: テクスチャの置き場

//	
//////////
 
#endif