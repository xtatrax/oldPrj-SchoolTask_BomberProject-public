////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Scene.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：シーン
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
#include "Stage_Play.h"
#include "Stage_Result.h"
#include "Stage_Test.h"
#include <process.h>
#include "Factory_Player.h"


namespace wiz{
using namespace bomberobject;

/**************************************************************************
 Scene 定義部
***************************************************************************/
HANDLE	Scene::m_hLoadingThread				;
//Stage*	Scene::m_pStgBuf			= NULL	;
//bool	Scene::m_bLoadingComplete	= false	;
/////////////////// ////////////////////
//// 関数名     ：void Clear()
//// カテゴリ   ：関数
//// 用途       ：オブジェクトのクリア
//// 引数       ：無し
//// 戻値       ：無し
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
//// 引数       ：無し
//// 戻値       ：無し
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
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：失敗したら例外をthrow
////            ：
////
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pRootStage(NULL)
,m_pStgBuf(NULL)
,m_bLoadingComplete(false)
,m_bUpdateThreadSuspendRequest(false)
,m_bUpdateThreadResumeRequest(false)
,m_pD3DDevice(pD3DDevice)
,m_fStageNotFoundMessageTime(0.0f)
{
    try{
        //無効チェック
        if(!pD3DDevice){
            throw BaseException(L"シーンの初期化に失敗しました。デバイスが無効です。",
            L"Scene::Scene()");
        }
		m_pD3DDevice = pD3DDevice;
//////////
//	: デバッグ用設定
#if defined(DEBUG) || defined(_DEBUG) || defined(ON_DEBUGGINGPROCESS)
		try{
			//ルートのステージにデバッグメニューを設定
			m_pRootStage	= new PlayStage(pD3DDevice);
			//m_pRootStage	= new TitleStage(pD3DDevice);
			//m_pRootStage	= new ResultStage(pD3DDevice);
		}
		catch(LoaderException& e){
			//	: ロード失敗
			::MessageBox(g_hWnd,e.what_w(),L"エラー",MB_OK);
			if( !m_pRootStage ) m_pRootStage = new TitleStage(pD3DDevice);
			//SafeDeleteStage(this->m_pStgBuf);
		}
		catch(...){
			throw ;
		}

#else 
//	: リリース用設定
		//ルートのステージにタイトルメニューを設定
		m_pRootStage = new TitleStage(pD3DDevice);

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
//// 引数       ：無し
//// 戻値       ：無し
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
//// 関数名     ：void Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            ：      const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：関数
//// 用途       ：シーンを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  const CONTROLER_STATE* pCntlState   // コントローラーのステータス
////            ：  Command& i_DrawPacket.pCommand						// コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::Update(UpdatePacket& i_UpdatePacket){

	if(m_pRootStage){

#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
		//	:  バックボタンでデバッグメニューへ
		if(i_UpdatePacket.pCntlState->Gamepad.wPressedButtons.XConState.BACK)
			i_UpdatePacket.pCommand->m_Command = GM_OPENDEBUGSTAGE_DEBUGMENU;
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
//// 戻値       ：無し
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
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Command& i_DrawPacket.pCommand						// コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：画面以外のバッファーに描画する
////            ：
////
void Scene::Draw(DrawPacket& i_DrawPacket){
	if(m_pRootStage){
		m_pRootStage->getActiveStage()->Draw(i_DrawPacket);
	}
	CommandTranslator(i_DrawPacket);
}

/////////////////// ////////////////////
//// 関数名     ：void CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
//// カテゴリ   ：関数
//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Command& i_DrawPacket.pCommand						// コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：
////            ：
////
void Scene::CommandTranslator(DrawPacket& i_DrawPacket){

	switch(i_DrawPacket.pCommand->m_Command){
		case GM_OPENSTAGE_TITLE:
			//	: タイトル画面
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
			break;
		case GM_OPENSTAGE_PLAY:
			try{
				//	: ゲームステージ

				this->m_pStgBuf = new PlayStage(i_DrawPacket.pD3DDevice);
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ロード失敗
				::MessageBox(g_hWnd,e.what_w(),L"エラー",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENSTAGE_PLAY_RELOAD:
			try{
				//	: ゲームステージ
				PlayerCoil* pc = (PlayerCoil*)i_DrawPacket.pCommand->m_Param1 ;
				this->m_pStgBuf = new PlayStage( i_DrawPacket.pD3DDevice, pc->getPos() );
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ロード失敗
				::MessageBox(g_hWnd,e.what_w(),L"エラー",MB_OK);
				if( !m_pRootStage ) m_pRootStage = new TitleStage(i_DrawPacket.pD3DDevice);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}

			break;
		case GM_OPENDEBUGSTAGE_DEBUGMENU:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugMenu(i_DrawPacket.pD3DDevice);
			break;

		case GM_OPENSTAGE_RESULT:
			//	: ゲームクリア画面
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new ResultStage(i_DrawPacket.pD3DDevice);
			break;


		case GM_OPENSTAGE_RANKING:
			//	: ランキング画面
		case GM_OPENSTAGE_GAMEOVER:
			//	: ゲームオーバー画面



		//case GM_OPENDEBUGSTAGE_STAGECREATE:
		//	SafeDeleteStage();
		//	m_pRootStage = new DevelopStage(i_DrawPacket.pD3DDevice);
		//	break;
			m_fStageNotFoundMessageTime          = 3.0f ;
			break ; 
		//	: デバッグステージ
		case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:
			try{
				//	: ゲームステージ
				this->m_pStgBuf = new DebugStage_TATRA(i_DrawPacket.pD3DDevice);
				//	: 
				SafeDeleteStage(m_pRootStage);
				m_pRootStage = this->m_pStgBuf;
				this->m_pStgBuf = NULL ;
			}
			catch(LoaderException& e){
				//	: ロード失敗
				::MessageBox(g_hWnd,e.what_w(),L"エラー",MB_OK);
				SafeDeleteStage(this->m_pStgBuf);
			}
			catch(...){
				throw ;
			}
			//SafeDeleteStage(m_pRootStage);
			//m_pRootStage = new DebugStage_TATRA(i_DrawPacket.pD3DDevice);
			break;

		case GM_OPENDEBUGSTAGE_STAGELOADERTEST:
			SafeDeleteStage(m_pRootStage);
			m_pRootStage = new DebugStage_Loader(i_DrawPacket.pD3DDevice);
			break;
		case GM_EXIT:
			::DestroyWindow(g_hWnd);
			break;
	}
	if(m_bLoadingComplete){
		SafeDeleteStage(m_pRootStage);
		m_pRootStage = m_pStgBuf;
		m_bLoadingComplete = false;
		i_DrawPacket.pTime->TimeUpdate();
		i_DrawPacket.pTime->TimeUpdate();
	}
	if( m_fStageNotFoundMessageTime > 0.0f ){
		float f = (float)i_DrawPacket.pTime->getElapsedTime();
		m_fStageNotFoundMessageTime -= f ;
		Debugger::DBGSTR::addStrTop(L"未対応のシーンです");
	}
	i_DrawPacket.pCommand->m_Command = GM_WITHOUT ;
	i_DrawPacket.pCommand->m_Param1  = 0 ;
	i_DrawPacket.pCommand->m_Param2  = 0 ;

}
unsigned __stdcall Scene::LoadingThread(void *args)
//void Scene::LoadingThread(void* args)
{
	Scene* This = reinterpret_cast<Scene*>(args);
	while(true){
		//switch(This->m_LoadCommand.m_Command){
		//	//	: ゲームステージ
		//	case GM_OPENSTAGE_PLAY:
		//		This->m_pStgBuf = new PlayOpeningStage(This->m_pD3DDevice);
		//		break;


		//	//	: デバッグステージ
		//	case GM_OPENDEBUGSTAGE_TOJIWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_TojimaWorkSpace(This->m_pD3DDevice);
		//		break;
		//	case GM_OPENDEBUGSTAGE_HSWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_HSWorkSpace(This->m_pD3DDevice);
		//		break;
		//	case GM_OPENDEBUGSTAGE_TATEAWORKSPACE:
		//		This->m_pStgBuf = new DebugStage_TatraWorkSpace(This->m_pD3DDevice);
		//		break;
		//	//case GM_OPENDEBUGSTAGE_STAGECREATE:
		//	//	SafeDeleteStage();
		//	//	m_pRootStage = new DevelopStage(i_DrawPacket.pD3DDevice);
		//	//	break;
		//}
		//This->m_bLoadingComplete = true;
		//#ifdef CF_LOADINGANIMATION
		//	SuspendThread(m_hLoadingThread);
		//	//CloseHandle(m_hLoadingThread);
		//	//_endthread();
		//#else
		//	break;
		//#endif
	}
	return 0;
}

void Scene::LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand){

	m_LoadCommand = *pCommand;
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
//// 引数       ：無し
//// 戻値       ：無し
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

