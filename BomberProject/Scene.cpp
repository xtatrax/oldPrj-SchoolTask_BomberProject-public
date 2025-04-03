////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Scene.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：シーン
//					：シーンはデバイスから呼ばれます
//					▼
//	namespace wiz;
//		class Scene ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Debug_Stage.h"
#include "Stage_Title.h"
#include "Stage_Select.h"
#include "Stage_Play.h"
#include "Stage_Clear.h"
#include "Stage_Result.h"
#include "Stage_Load.h"
#include "Stage_Test.h"
#include "Stage_Demo.h"
#include <process.h>
#include "Factory_Player.h"
#include <string.h>

namespace wiz{
using namespace bomberobject;

/**************************************************************************
 Scene 定義部
***************************************************************************/
HANDLE	Scene::m_hLoadingThread				;

/////////////////// ////////////////////
//// 関数名     ：void Clear()
//// カテゴリ   ：関数
//// 用途       ：オブジェクトのクリア
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::setStages(){
}
/////////////////// ////////////////////
//// 関数名     ：void Clear()
//// カテゴリ   ：関数
//// 用途       ：オブジェクトのクリア
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::Clear(){
	SafeDeleteStage(m_pRootStage);
}
/////////////////// ////////////////////
//// 関数名     ：Scene(LPDIRECT3DDEVICE9 pD3DDevice)
//// カテゴリ   ：コンストラクタ
//// 用途       ：シーンを生成
//// 引数       ：LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：失敗したら例外をthrow
////            ：
////
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice,Command* pCommand)
:m_pRootStage(NULL)
,m_pStgBuf(NULL)
,m_pLoadDevice(NULL)
,m_bLoadingComplete(false)
,m_bUpdateThreadSuspendRequest(false)
,m_bUpdateThreadResumeRequest(false)
,m_fStageNotFoundMessageTime(0.0f)
{
	try{
        //無効チェック
        if(!pD3DDevice){
            throw BaseException(L"シーンの初期化に失敗しました。デバイスが無効です。",
            L"Scene::Scene()");
		}
		//////////
		//	: デバッグ用設定
		#if defined(ON_DEBUGGINGPROCESS)
			//ルートのステージにデバッグメニューを設定
			pCommand->m_Command = GM_OPENSTAGE_TITLE ;
			//*pCommand = Command(GM_OPENSTAGE_PLAY,3,0) ;
			//*pCommand = Command(GM_OPENSTAGE_PLAY,100,0) ;
		#else 
		//	: リリース用設定
		//ルートのステージにタイトルメニューを設定
			pCommand->m_Command = GM_OPENSTAGE_TITLE ;

		#endif
		//
		//////////

		//////////
		//	: ロード用スレッド作成
		#ifdef CF_LOADINGANIMATION
		//m_hLoadingThread = (HANDLE) _beginthread(
		//	&Scene::LoadingThread,	// ランチャを起動
		//	0,
		//	this);
		m_hLoadingThread = (HANDLE) _beginthreadex(
			NULL,
			0,
			&Scene::LoadingThread,	// ランチャを起動
			this,
			CREATE_SUSPENDED,
			NULL);
		#endif
		//
		//////////

		SetRenderStateArray(pD3DDevice,g_GlobalRenderStates);

    }
    catch(wiz::BaseException& e){
        //破棄処理
        Clear();
        throw BaseException(
			e.what_w(), 
            L"↑Scene::Scene()"
            );
	}
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/////////////////// ////////////////////
//// 関数名     ：~Scene()
//// カテゴリ   ：デストラクタ
//// 用途       ：シーンを破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
Scene::~Scene()
{
    //破棄処理
    Clear();
}
/////////////////// ////////////////////
//// 関数名     ：void Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.GetTime(),
////            ：      const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：関数
//// 用途       ：シーンを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  const CONTROLER_STATE* pCntlState   // コントローラーのステータス
////            ：  Command& i_DrawPacket.pCommand						// コマンド
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::Update(UpdatePacket& i_UpdatePacket){

	if(m_pRootStage){

		#if defined(ON_DEBUGGINGPROCESS)
		//	:  バックボタンでデバッグメニューへ
		if(i_UpdatePacket.m_pCntlState->Gamepad.wPressedButtons.XConState.BACK)
			i_UpdatePacket.PushCommand( GM_OPENDEBUGSTAGE_DEBUGMENU );
		#endif
		m_pRootStage->getActiveStage()->Update(i_UpdatePacket);
	}
}
/////////////////// ////////////////////
//// 関数名     ：void AnotherTargetRender(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
//// カテゴリ   ：関数
//// 用途       ：ターゲットレンダリング
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Command& i_DrawPacket.pCommand						// コマンド
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：画面以外のバッファーに描画する
////            ：
////
void Scene::Render(RenderPacket& i_RenderPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Render(i_RenderPacket);
	}
}
/////////////////// ////////////////////
//// 関数名     ：void Draw(DrawPacket& i_DrawPacket);
//// カテゴリ   ：関数
//// 用途       ：シーンを描画
//// 引数       ：  DrawPacket& i_DrawPacket 
//// 戻値       ：なし
//// 担当者     ：鴫原 徹(山ノ井先生のひな形より)
//// 備考       ：画面以外のバッファーに描画する
////            ：
////
void Scene::Draw(DrawPacket& i_DrawPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Draw(i_DrawPacket);
	}
	//CommandTranslator(i_DrawPacket);
}

/////////////////// ////////////////////
//// 関数名     ：void CommandTranslator(BassPacket& i_BassPacket);
//// カテゴリ   ：関数
//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Scene::CommandTranslator(BassPacket& i_BassPacket){

	Command comBuf = i_BassPacket.PopCommand();
	switch(comBuf.m_Command){
		case GM_OPENSTAGE_TITLE:
			//	: タイトル画面
			SafeDeleteStage(m_pRootStage);
			m_pRootStage =
				new
				StageSelect( i_BassPacket.GetDevice() , new TitleStage(i_BassPacket.GetDevice()));
			//strrchr(__FILE__,'\\' );
			break;
		case GM_OPENSTAGE_DEMO:
			//	: タイトル画面
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DemoStage( i_BassPacket.GetDevice() );
			break;
		case GM_OPENSTAGE_LOAD_PLAY:
			comBuf.m_Command = GM_OPENSTAGE_PLAY;
			goto PRGOTO_GM_OPENSTAGE_LOAD;
		case GM_OPENSTAGE_LOAD:
			//	: ロード画面
			PRGOTO_GM_OPENSTAGE_LOAD:
			SafeDeleteStage(m_pRootStage);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  PRGOTO_GM_OPENSTAGE_LOAD  ステージ作成開始  ");
			m_pRootStage = new LoadStage(i_BassPacket.GetDevice(),&comBuf);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  PRGOTO_GM_OPENSTAGE_LOAD  ステージ作成OK  ");
			break;
		case GM_OPENSTAGE_PLAY:
			try{
				//	: ゲームステージ
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  ステージ作成開始  ");
				this->m_pStgBuf = new PlayStage(i_BassPacket.GetDevice(), comBuf.m_Param1, comBuf.m_Param2);
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  ステージ作成完了  ");
				//	: 
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  前ステージ削除開始  ");
				SafeDeleteStage(m_pRootStage);
				////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_PLAY  前ステージ削除終了  ");
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ロード失敗
				::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"エラー",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_BassPacket.GetDevice());
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENDEBUGSTAGE_DEBUGMENU:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugMenu(i_BassPacket.GetDevice());
			break;

		case GM_OPENSTAGE_CLEAR:
			//	: ゲームクリア画面
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  ステージ削除開始  ");
			SafeDeleteStage(m_pRootStage);
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  ステージ削除OK  ");
			m_pRootStage = new ClearStage(i_BassPacket.GetDevice(), comBuf.m_Param1,
														comBuf.m_Param2, comBuf.m_Param3 );
			////Debugger::DBGWRITINGLOGTEXT::addStr(L"Scene::CommandTranslator  >>>>  GM_OPENSTAGE_CLEAR  ステージ作成OK  ");
			break;

		case GM_OPENSTAGE_RESULT:
			//	: リザルト画面
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new ResultStage(i_BassPacket.GetDevice(), comBuf.m_Param1,
														comBuf.m_Param2, comBuf.m_Param3 );
			break;

		case GM_OPENDEBUGSTAGE_PLAY_RELOAD:
			//	: リロード
			try{
				//	: ゲームステージ
				PlayerCoil* pc = (PlayerCoil*)comBuf.m_Param1 ;
				DWORD dwStageNum = m_pRootStage ? ((PlayStage*)m_pRootStage)->getNowStage() : 0 ;
				this->m_pStgBuf = new PlayStage( i_BassPacket.GetDevice(), dwStageNum ,comBuf.m_Param2, pc->getPos() );
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ロード失敗
				::MessageBox(wiz::DxDevice::m_hWnd,e.what_w(),L"エラー",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_BassPacket.GetDevice());
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;

//未対応のステージ

		case GM_OPENSTAGE_RANKING:
			//	: ランキング画面
		case GM_OPENSTAGE_GAMEOVER:
			//	: ゲームオーバー画面
		case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:

		case GM_OPENDEBUGSTAGE_STAGELOADERTEST:


		case GM_OPENDEBUGSTAGE_STAGECREATE:
			m_fStageNotFoundMessageTime          = 3.0f ;
			break ; 

		case GM_EXIT:
			SafeDeleteStage(m_pRootStage);
			wiz::DxDevice::Destroy();

			//::DestroyWindow(wiz::DxDevice::m_hWnd);
			break;
	}
	if(m_bLoadingComplete){
		SafeDeleteStage(m_pRootStage);
		m_pRootStage = m_pStgBuf;
		m_bLoadingComplete = false;
		i_BassPacket.GetTime()->TimeUpdate();
		i_BassPacket.GetTime()->TimeUpdate();
	}
	if( m_fStageNotFoundMessageTime > 0.0f ){
		float f = (float)i_BassPacket.GetTime()->getElapsedTime();
		m_fStageNotFoundMessageTime -= f ;
		Debugger::DBGSTR::addStrTop(L"未対応のシーンです");
	}
	i_BassPacket.ClearCommand();
}
/////////////////// ////////////////////
//// 関数名     ：unsigned __stdcall Scene::LoadingThread(void *args)
//// カテゴリ   ：関数
//// 用途       ：ロード用スレッド処理
//// 引数       ：  void*	args	//	: シーンへのポインタを渡してください
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
unsigned __stdcall Scene::LoadingThread(void *args)
//void Scene::LoadingThread(void* args)
{
	Scene* This = reinterpret_cast<Scene*>(args);
	
	//	: サスペンド実験用ループ
	while(true){
		//switch(This->m_LoadCommand.m_Command){
			//	: ゲームステージ
			//case GM_OPENSTAGE_PLAY:
			//	This->m_pStgBuf = new PlayOpeningStage(This->m_pLoadDevice);
			//	break;


			//	: デバッグステージ
			//case GM_OPENDEBUGSTAGE_STAGECREATE:
			//	SafeDeleteStage();
			//	m_pRootStage = new DevelopStage(i_DrawPacket.GetDevice());
			//	break;
		//}
		This->m_bLoadingComplete = true;
		This->m_pLoadDevice = NULL ;
		This->m_LoadCommand.Clear();
		#ifdef CF_LOADINGANIMATION
			SuspendThread(m_hLoadingThread);
			//CloseHandle(m_hLoadingThread);
			//_endthread();
		#else
			break;
		#endif
	}
	return 0;
}
/////////////////// ////////////////////
//// 関数名     ：void Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand)
//// カテゴリ   ：関数
//// 用途       ：ロード用スレッドのランチャー
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand){

	m_LoadCommand = *pCommand;
	m_pLoadDevice = pD3DDevice ;
#ifdef CF_LOADINGANIMATION
	ResumeThread(m_hLoadingThread);
#else
	LoadingThread(this);
#endif
}
/////////////////// ////////////////////
//// 関数名     ：void SafeDeleteStage()
//// カテゴリ   ：関数
//// 用途       ：ステージを安全に削除する
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::SafeDeleteStage(Stage* &pStage){
	#ifndef CF_SINGLETHREAD
		//	: マルチスレッドモードの場合
		//	: データへアクセス中にいきなり削除されるのを防ぐために
		//	: 一旦アップデートスレッドを休止する
		setUpdateThreadSuspendRequest();
		//	: アップデートスレッドが休止するまで待つ
		while(!getUpdateThreadSuspend()){
			Sleep(1);
		}
	#endif
	//	: シーンを削除
	SafeDelete( pStage );
	pStage = NULL;
	#ifndef CF_SINGLETHREAD
		//	: 休止したスレッドを再開させる
		setUpdateThreadResumeRequest();
	#endif
}


}
//end of namespace wiz.

