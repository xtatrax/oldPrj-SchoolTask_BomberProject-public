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
#define CF_SINGLETHREAD					/* シングルスレッドモード  ( 無効にするとマルチスレッド的になりますがバグります )   */
#define DRAW_MOUSE	(false)				/* マウスを描画するかどうか */

#define DEBUG_KEYBORD_ON				/* デバッグ用キーボード操作を有効化 */
#define CF_OVERLORDNEW_ENABLE			/* 自作のnewを強制化(Manager有効時) */
#define CF_MEMORYOUTPUTPROCESS_ENABLE	/* 自作メモリ管理システムにより管理されているアイテムのファイルへの書き出しを可能にする(Manager有効時) */
///#define CF_LOADINGANIMATION			/* ロード画面でアニメーション */
//#define CF_OVERLORDNEW_ENABLE			/* 自作のnewを強制化 */

//#define CF_DEBUG_TIMEDRAW				/* 時間を描画 */
//#define CF_LOADINGANIMATION			/* ロード画面でアニメーション */


#if defined(DEBUG) || defined(_DEBUG)
	//-------------------------------//
	//		デバッグモード定義       //
	//-------------------------------//
	#define ON_DEBUGGINGPROCESS					/* デバックモード             */
	#define DEBUG_STRINGS_ON					/* デバッグ用文字列を有効化 */
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
		//#define CF_FULLSCREEN				/* フルスクリーンモード       */
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

//////////
// マクロ関数

#define TL_SQUARE(n)							((n)*(n))

//
//////////


//////////
//	: グローバルな変数

//	: デファイン定数
#define MAP_PARTS_HEIGHT		(    1.0f)	/*  */
#define MAP_PARTS_WIDTH			(    1.0f)	/*  */
#define BASE_CLIENT_HEIGHT		(  600.0f)	/* 基準になる描画領域の高さ */
#define BASE_CLIENT_WIDTH		( 1024.0f)	/* 基準になる描画領域の幅   */
#if defined(CF_FULLSCREEN)

#define STANDARD_WINDOW_HEIGHT		(  600.0f)	/* 基準になる描画領域の高さ */
#define STANDARD_WINDOW_WIDTH		( 1024.0f)	/* 基準になる描画領域の幅   */

//#define STANDARD_WINDOW_HEIGHT  (  800.0f)	/* ウインドウモードの高さ   */
//#define STANDARD_WINDOW_WIDTH   ( 1280.0f)	/* ウインドウモードの幅     */

//#define STANDARD_WINDOW_HEIGHT  (  768.0f)	/* ウインドウモードの高さ   */
//#define STANDARD_WINDOW_WIDTH   ( 1366.0f)	/* ウインドウモードの幅     */

#else
#define STANDARD_WINDOW_HEIGHT  (  600.0f)	/* ウインドウモードの高さ   */
#define STANDARD_WINDOW_WIDTH   ( 1024.0f)	/* ウインドウモードの幅     */
#endif
//#define BASE_CLIENT_HEIGHT		(  600.0f)	/* 基準になる描画領域の高さ */
//#define BASE_CLIENT_WIDTH		( 1024.0f)	/* 基準になる描画領域の幅   */
//#define STANDARD_WINDOW_HEIGHT  ( 1200.0f)	/* ウインドウモードの高さ   */
//#define STANDARD_WINDOW_WIDTH   ( 1920.0f)	/* ウインドウモードの幅     */
#define DRAW_TOLERANCE			(   20.0f)	/* カメラからの描画距離 */

#define DEFAULT_WINDOW_TITLE		( L"Magnetica" )
#define DEFAULT_WINDOW_CLASS_NAME	( L"MagneticWindow" )

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


#define MYVK_DEBUG_STOP_UPDATE				( VK_F12     )
#define MYVK_DEBUG_SLOW_UPDATE				( VK_F11     )
#define MYVK_DEBUG_OUTPUT_DBGSTR			( VK_F9      )
#define MYVK_DEBUG_OUTPUT_MEMORY			( VK_F8      )
#define MYVK_DEBUG_OBB_DRAW					( VK_F7      )
#define MYVK_DEBUG_SWITCHING_SOUND			( VK_F6      )
#define MYVK_DEBUG_COIL_INVISIBLE			( VK_CONTROL )
#define MYVK_DEBUG_STAGE_RESTART			( VK_RETURN  )
#define MYVK_DEBUG_STAGE_RESTART_SUBKEY		( VK_SHIFT   )
#define MYVK_DEBUG_STAGE_RELOAD_SUBKEY		( VK_MENU    )
#define MYVK_DEBUG_INVISIBLEGAUGE_MAX		( 'X'     )
#define MYVK_DEBUG_STAGE_RULER				( 'L'        )
#define MYVK_DEBUG_SWITCH_ALPHABLEND		( 'A'        )

#define UI_HEIGHT							( 88.0f )	//	: UIの高さ
#define DRAW_CLIENT_MAGNIFICATION			( 50.0f )	//	: 表示画面の倍率 x=800, y=512 : x=40, y=25.6
#define MAGNETIC_RADIUS						( 0.5f )	//	: 磁界の半径
const float	CURSOR_FIELD_LENGHT				= 10.0f;
const float CURSOR_FIELD_TIME				= 2.0f;		

static ULONG				RCVAL_SAVEDATA_IDENTIFIER_H		= 0x534E4B42 ;	//	: BKNS
static ULONG				RCVAL_SAVEDATA_IDENTIFIER_L		= 0x5F455641 ;	//	: AVE_

static const char*			RCTEXT_SAVEDATA_EXTENSION		= "bkn"  ;
static const char*			RCTEXT_SAVEDATA_FILENAME		= "SaveData/Save.bkn"  ;

static const wchar_t*		RCTEXT_SOUND_WAVEBANK			= L"media/Sound/MagneticaWave.xwb"  ;
static const wchar_t*		RCTEXT_SOUND_SOUNDBANK			= L"media/Sound/MagneticaSound.xsb" ;

static const char*			RCTEXT_SOUND_BGM_CLEAR			= "BGM-CLEAR"			;
static const char*			RCTEXT_SOUND_BGM_GAMEOVER		= "BGM-GAME_OVER"		;
//static const char*			RCTEXT_SOUND_BGM_PLAY		= "BGM-PLAY001"			;
static const char*			RCTEXT_SOUND_BGM_PLAY			= "BGM-PLAY002"			;
static const char*			RCTEXT_SOUND_BGM_TITLE			= "BGM-TITLE"			;
static const char*			RCTEXT_SOUND_SE_ALERT			= "SE-ALERT002"			;
static const char*			RCTEXT_SOUND_SE_BREAKENEMY		= "SE-BLOKEN_ENEMY"		;
static const char*			RCTEXT_SOUND_SE_CHECKPOINT		= "SE-CHACK_POINT"		;
static const char*			RCTEXT_SOUND_SE_CLEAR			= "SE-CLEAR"			;
static const char*			RCTEXT_SOUND_SE_SELECT			= "SE-SELECT"			;
static const char*			RCTEXT_SOUND_SE_ENTER			= "SE-ENTER"			;
static const char*			RCTEXT_SOUND_SE_FIRE			= "SE-FIRE"				;
static const char*			RCTEXT_SOUND_SE_GOAL			= "SE-GOAL"				;
static const char*			RCTEXT_SOUND_SE_PLAYERBLOKEN	= "SE-PLAYER_BLOKEN"	;
static const char*			RCTEXT_SOUND_SE_INVISIBLE		= "SE-INVINGVLE"		;
static const char*			RCTEXT_SOUND_SE_ITEMS			= "SE-ITEMS"			;
static const char*			RCTEXT_SOUND_SE_SUPER_FULL		= "SE-ITEM_FULL"		;
static const char*			RCTEXT_SOUND_SE_SETFIELD		= "SE-MAGNETIC_FIELD"	;
static const char*			RCTEXT_SOUND_SE_SPARK			= "SE-SPARK002"			;
static const char*			RCTEXT_SOUND_SE_SPARK_WARNING	= "SE-SPARK002"			;

static const char*			RCTEXT_MODEL_ENEMY				= "media/Model/mine.x"	;

static const float			MGPRM_INVISIBLESOUND_TIME		= 0.7f	; /* 磁界の影響半径*/
static const int			MGPRM_MAGNETICUM				= 10	; /* 磁界の影響半径*/
static const int			MGPRM_MAGNETICUM_QUAD			= ( MGPRM_MAGNETICUM * MGPRM_MAGNETICUM );
static const int			DRAWING_RANGE					= 25;
static const D3DXVECTOR3	g_vZero							= D3DXVECTOR3(0.0f,0.0f,0.0f);
static const D3DXVECTOR3	g_vOne							= D3DXVECTOR3(1.0f,1.0f,1.0f);
static const D3DXVECTOR3	g_vMax							= D3DXVECTOR3(+FLT_MAX,+FLT_MAX,+FLT_MAX);
static const D3DXVECTOR3	g_vMin							= D3DXVECTOR3(-FLT_MAX,-FLT_MAX,-FLT_MAX);
static const wstring		g_sDefaultTexturePath			= L"media/Textures/" ;	//	: テクスチャの置き場
      //extern HWND			wiz::DxDevice::m_hWnd			;
static const SIZE			g_GaugeReverseSize				= { 146,67 };


//
//////////

//


//
namespace wiz{
	//	: ゲーム内メセージ
	enum{
		GM_WITHOUT					,	//	: 何もしない
		GM_OPENSTAGE_TITLE			,	//	: タイトル画面を開く
		GM_OPENSTAGE_SELECT			,	//	: セレクト画面を開く
		GM_OPENSTAGE_LOAD			,	//	: ロード画面を開く
		GM_OPENSTAGE_LOAD_PLAY		,	//	: ロード画面を開いた後にプレイ画面を開く
		GM_OPENSTAGE_PLAY			,	//	: プレイ画面を開く
		GM_OPENSTAGE_GAMECLEAR		,	//	: クリア画面を開く
		GM_OPENSTAGE_GAMEOVER		,	//	: ゲームオーバー画面を開く
		GM_OPENSTAGE_CLEAR			,	//	: クリア画面を開く
		GM_OPENSTAGE_RESULT			,	//	: リザルト画面を開く
		GM_OPENSTAGE_RANKING		,	//	: ランキング画面を開く
		GM_OPENSTAGE_OPTION			,	//	: オプション画面を開く
		GM_EXIT						,	//	: ゲームを終了する

		GM_OPENDEBUGSTAGE_DEBUGMENU			,
		GM_OPENDEBUGSTAGE_PLAY_RELOAD		,
		GM_OPENDEBUGSTAGE_STAGELOADERTEST	,
		GM_OPENDEBUGSTAGE_TATEAWORKSPACE	,
		GM_OPENDEBUGSTAGE_STAGECREATE		,


		GM_CHANGE_PARENTSTAGE	,
		GM_CHANGE_CHILDSTAGE	,

		//////////
		//	: 
		GM_PLAYOPENING_END	,

	};
	//	: 
	enum CLASSID{
		/////////
		//
		//	この列挙型は外部ファイルで使用するので
		//	仕様に従い絶対に値を明記すること
		//

		CLASSID_NONE		=    0 ,
		CLASSID_TESTTIP		=    1 ,
		CLASSID_GOAL		=   10 ,
		CLASSID_CHECKPOINT	=   11 ,
		CLASSID_WALL		=   20 ,
		CLASSID_MAGNET		=   30 ,
		CLASSID_ENEMY		=   31 ,
		CLASSID_ITEM		=   40 ,



		CLASSID_END			=  0xFFFFFFFFFFFFFFFF ,
	};
/**/
	//////////////////////////////////////////////////
	//                                              //
	//                                              //
	//   オブジェクト識別するために利用知るのID     //
	//                                              //
	//   追加の際はすべて大文字で記述してください   //
	//                                              //
	//                                              //
	//////////////////////////////////////////////////
	enum OBJID{
		OBJID_NONE					= 0x0000,	//	: なし
		OBJID_UNK					= 0x0001,	//	: 未定オブジェ

		//	: システム関係
		OBJID_SYS_BEGIN				= 0x1000,
		OBJID_SYS_GUIDELINE			,	//	: XYZガイド線( Debug用 )
		OBJID_SYS_CAMERA			,	//	: カメラ
		OBJID_SYS_LIGHT				,	//	: ライト
		OBJID_SYS_DIRECTIONAL		,	//	: 方向性ライト
		OBJID_SYS_CURSOR			,	//	: カーソル
		OBJID_SYS_SOUND				,	//	: 音声
		OBJID_SYS_CHECKPOINT		,	//	: チェックポイント
		OBJID_SYS_CLEARAREA			,	//	: クリア領域
		OBJID_SYS_RENDERTARGET		,	//	: レンダーターゲット
		OBJID_SYS_END				,	
		OBJID_SYS_START				,	

		OBJID_BEHAVIOR_TEST					,
		OBJID_BEHAVIOR_CHECKPOINTSAVE		,

		//	:サウンドまわり
		//	:BGM
		//OBJID_SOUND_BGM_TITLE			,
		//OBJID_SOUND_BGM_PLAY			,
		//OBJID_SOUND_BGM_CLEAR			,
		//OBJID_SOUND_BGM_GAME_OVER		,

		//	:効果音
		//OBJID_SOUND_SE_ALERT			,
		//OBJID_SOUND_SE_BLOKEN_ENEMY		,
		//OBJID_SOUND_SE_CHACK_POINT		,
		//OBJID_SOUND_SE_CLEAR			,
		//OBJID_SOUND_SE_ENTER			,
		//OBJID_SOUND_SE_FIRE				,
		//OBJID_SOUND_SE_GOAL				,
		//OBJID_SOUND_SE_PLAYER_BLOKEN	,
		//OBJID_SOUND_SE_INVINGVLE		,
		//OBJID_SOUND_SE_ITEMS			,
		//OBJID_SOUND_SE_MAGNETIC_FIELD	,
		//OBJID_SOUND_SE_SPARK			,


		//	: UI周り
		OBJID_UI_BEGIN				= 0x2000,
		OBJID_UI_SPRITE				,	//	: UIに使うスプライト
		OBJID_UI_SPRITEBUTTON		,	//	: スプライトボタンのUI
		OBJID_UI_BUTTON_NORMAL		,	//	:
		OBJID_UI_BUTTON_HARD		,	//	:
		OBJID_UI_BUTTON_EXTRA		,	//	:
		OBJID_UI_BUTTON_BACK		,	//	:
		OBJID_UI_SELECTINFORMATION	,	//	:
		OBJID_UI_CHECKPOINT_CHAR	,	//	: チェックポイント
		OBJID_UI_LIFE				,	//	: ライフ( 念のため )
		OBJID_UI_SUPERGAUGE			,	//	: ゲージ
		OBJID_UI_MAGNETGAUGE_N		,	//	: N極ゲージ
		OBJID_UI_MAGNETGAUGE_S		,	//	: S極ゲージ
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
		//OBJID_3D_MAGNET			,	//	: 磁石
		OBJID_3D_WALL				,	//	: 壁
		OBJID_3D_ITEM				,	//	: アイテム


		//	:
		//OBJID_3D_PLAYER				,
		OBJID_3D_USERMAGNET			,	//	: ユーザー
		OBJID_3D_COIL				,	//	: プレイヤー
		OBJID_3D_STATIC_MAGNET		,	//	: 磁石
		OBJID_3D_EFFECT				,	//	: エフェクト
		OBJID_3D_WARNING			,	//	: 警告
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

 
#endif