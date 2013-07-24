////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ステージ
//					：ステージはシーンから呼ばれます
//					▼
//	namespace wiz;
//		class StageLoader ;
//		class Stage ;
//		class MenuStage : public Stage ;
//
#include "StdAfx.h"
#include "Stage.h"
#include "BassItems.h"
#include "TL-String.h"
#include "Factory_Wall.h"
#include "Factory_Item.h"
#include "Factory_Magnetic.h"
#include "Object.h"



namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 Stage 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：void Stage::Clear()
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Stage::Clear(){
	//SafeDelete(m_pChildStage);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"Stage::Clear  >  %X 削除開始\n",this);
    
    //  : 親ステージを削除(あとで子ステージに修正する)
	SafeDelete(m_pParStage);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDelete(m_pParStage) 完了\n");
    

	//  : 他で作られたものが入っていただけなのでぬるぽ!
	m_pSound = NULL ;
    //  : 自分用のサウンドを削除
	SafeDelete(m_pMySound);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDelete(m_pMySound)  完了\n");


	//	: ボタンの実体はm_Vecの中にあるためClearのみ
	m_ButtonVec.clear();
	////Debugger::DBGWRITINGLOGTEXT::addStr(L"m_ButtonVec.clear(); 完了\n");
    
	//  : ステージに配置されたオブジェクトをすべて削除
	SafeDeletePointerContainer(m_Vec);
    ////Debugger::DBGWRITINGLOGTEXT::addStr(L"SafeDeletePointerContainer(m_Vec);  完了\n");
	//SefeDeletePointerVector(m_Vec);


	//m_TexMgr.Release();
	////Debugger::DBGWRITINGLOGTEXT::addStr(L"m_TexMgr.Release(); 完了\n",this);
}

/////////////////// ////////////////////
//// 用途       ：Stage::Stage(Stage* Par)
//// カテゴリ   ：コンストラクタ
//// 用途       ：生成処理
//// 引数       ：Stage*		Par		//	: 親ステージへのポインタ
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Stage::Stage(Stage* Par)
:m_pParStage(Par),m_pChildStage(0),m_IsDialog(true)
,m_bUpdate( true )
,m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false)
,m_pMySound( NULL ),m_pSound( NULL )
,m_fActiveTime( 0 )
,m_dwFirstClock( 0 )
#if defined(ON_DEBUGGINGPROCESS)
,m_bSlow(false)
#endif
/////////////////// ////////////////////
{
	m_pParStage && (m_pParStage->m_pChildStage = this) ;
}
/**************************************************************************
virtual Stage::~Stage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Stage::~Stage(){
	Clear();
}
/////////////////// ////////////////////
//// 用途       ：virtual void ButtonUpdateUpdate( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：ボタンを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Stage::ButtonUpdate(UpdatePacket& i_UpdatePacket)
{
	CONTROLER_STATE	ControllerState1P = i_UpdatePacket.m_pCntlState[0];
    if(!m_SelectLock){

		DWORD dwSM = 0;
		if((dwSM = Button::getMouseSelectIndex()) != ULONG_MAX)
			m_SelectIndex = dwSM;

		//	: 次のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons.XConState.DOWN 
			|| ControllerState1P.Gamepad.sThumbLY < 0)
		{
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: 前のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons.XConState.UP
			|| ControllerState1P.Gamepad.sThumbLY > 0)
		{
			if(m_SelectIndex == 0){
				m_SelectIndex = (m_ButtonVec.size() - 1);
			}
			else{
				m_SelectIndex--;
			}
			m_SelectLock = true;
		}


		//選択状態の設定
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//選択が決定された
		if(		ControllerState1P.Gamepad.wPressedButtons.XConState.A
			&&	!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setPressed();
			m_SelectLock = true;
		}


		Debugger::DBGSTR::addStr(L"Button::getMouseSelectIndex() %d\n",dwSM);
		if(	Cursor2D::clickLButtonWithLock() ){
			Debugger::DBGSTR::addStr(L"クリック\n");
			if(	dwSM != ULONG_MAX ){
				if(	!m_ButtonVec.empty() )
				{
					if( m_SelectIndex >= m_ButtonVec.size() ){
						OutputDebugString( L"Stage::ButtonUpdateで無効なINDEXが参照されました。\n" );
						return ;
					}

					m_ButtonVec[m_SelectIndex]->setPressed();
					m_SelectLock = true;
				}
			}
		}
	}
	if( !(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		&&
		ControllerState1P.Gamepad.sThumbLY == 0
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		&& 
		!m_IsAnimetion
		){
		m_SelectLock = false;
	}

}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void Stage::Update(UpdatePacket& i_UpdatePacket)
{

	if( m_dwFirstClock == 0 ) m_dwFirstClock = Tempus::getClock() ;

	m_fActiveTime = Tempus::TwoDwTime2ElapsedTime(m_dwFirstClock,Tempus::getClock()) ;

	i_UpdatePacket.GetTime()->setStageActiveTime(m_fActiveTime);
	//	: 自分にSoundが登録されているかを確認
	//if( !m_pSound )	m_pSound = (Sound*)SearchObjectFromID( &this->m_Vec,OBJID_SYS_SOUND );
	if( !m_pSound ){
		//	: 使えるサウンドの登録がない
		if( m_pMySound ){
			//	: 自分のサウンドを持っている
			m_pSound = m_pMySound ;
			//	: 自分のサウンドを登録
		}else{
			//	: 自分のサウンドもない
			if( m_pParStage && m_pParStage->m_pSound ){
				//	: 親がサウンドを持っている
				m_pSound = m_pParStage->m_pSound ;
			}
		}
	}

	i_UpdatePacket.SetStage( this );

#if defined(ON_DEBUGGINGPROCESS)
	float fElapsedTime = (float)i_UpdatePacket.GetTime()->getElapsedTime();
	if(GetAsyncKeyState( MYVK_DEBUG_STOP_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime ;
		if(m_bUpdate){
			if(s_fTime > 0.05f){
				m_bUpdate = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bUpdate = true ;
				s_fTime   = 0 ;
			}
		}
	}
	static float fSlowAccumulator = 0;
	if(GetAsyncKeyState( MYVK_DEBUG_SLOW_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime;
		if(m_bSlow){
			if(s_fTime > 0.05f){
				m_bSlow = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bSlow = true ;
				s_fTime   = 0 ;
			}
		}
	}
	if( m_bSlow && (fSlowAccumulator += fElapsedTime) < 1.0f ){
		return;
	}
	fSlowAccumulator = 0 ;
#endif

	if(m_bUpdate){
		ButtonUpdate(i_UpdatePacket);
		//clock_t sc = TLIB::Tempus::getClock();
		//配置オブジェクトの描画
		vector<Object*>::iterator it = m_Vec.begin();
		while( it != m_Vec.end() ){
			if(!(*it)->getDead()){
				(*it)->AccessBegin();
				(*it)->Update(i_UpdatePacket) ;
				(*it)->AccessEnd();
			} else {
				//EraseButton( it );
				SAFE_DELETE( (*it) )	;
				it = m_Vec.erase( it )	;
				continue;
			}
			it++;
		}
		//clock_t nc = TLIB::Tempus::getClock();
		//Debugger::DBGSTR::addStr( L" Update時間 : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));
	}
}
/**************************************************************************
 void AddButton(
 Button* pButton	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。これ以外にm_Vecにも必ず入れる
 戻り値: なし
***************************************************************************/
void Stage::EraseButton(vector<Object*>::iterator ObjIt){
	if( (*ObjIt)->getButtonP() ){
		Button		*pTargetButton	= (*ObjIt)->getButtonP(),
					*pNowButton		= NULL;

		DWORD dwIndex = 0;
		vector<Button*>::iterator	it  = m_ButtonVec.begin(),
									end = m_ButtonVec.end();

		//	: サーチループ
		while( it != end ){
			pNowButton = (*it);
			if( pTargetButton == pNowButton ){
				it = m_ButtonVec.erase( it );
				//	: 番号詰めループ
				while( it != end ){
					(*it)->setIndex(dwIndex);
					dwIndex++;
					it++;
				}
				break;
			}
			dwIndex++;
			it++;
		}
	}
}

/////////////////// ////////////////////
//// 関数名     ：void Render(RenderPacket& i_RenderPacket);
//// カテゴリ   ：関数
//// 用途       ：ターゲットレンダリング
//// 引数       ：  RenderPacket& i_RenderPacket        // レンダー処理に流すデータの集合体
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：画面以外のバッファーに描画する
////            ：
////
void Stage::Render(RenderPacket& i_RenderPacket){

	i_RenderPacket.SetStage( this );

	//clock_t sc = TLIB::Tempus::getClock();
	//配置オブジェクトの描画
	vector<Object*>::iterator it = m_Vec.begin();
	while( it != m_Vec.end() ){
		if(!(*it)->getDead()){
			(*it)->AccessBegin();
			(*it)->TargetRender(i_RenderPacket);
			(*it)->AccessEnd();
		}
		it++;
	}
	//clock_t nc = TLIB::Tempus::getClock();
	//Debugger::DBGSTR::addStr( L" Render時間 : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));

}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void Stage::Draw(DrawPacket& i_DrawPacket)
{
	try{

		i_DrawPacket.SetStage( this );

		//clock_t sc = TLIB::Tempus::getClock();
		//配置オブジェクトの描画
		vector<Object*>::size_type sz = m_Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			m_Vec[i]->AccessBegin();
			m_Vec[i]->Draw(i_DrawPacket);
			m_Vec[i]->AccessEnd();
		}
		CommandTranslator(i_DrawPacket);
		//clock_t nc = TLIB::Tempus::getClock();
		//Debugger::DBGSTR::addStr( L"   Draw時間 : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(sc,nc));
	}
	catch(exception& e){
        throw e;
	}
    catch(...){
        throw;
    }
}
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
void Stage::TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget){

}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
void Stage::DefaultRender(){

}
/////////////////// ////////////////////
//// 関数名     ：void CommandTranslator(DrawPacket& i_DrawPacket);
//// カテゴリ   ：関数
//// 用途       ：コマンドを解釈してステージの切り替えなどを行う
//// 引数       ：  DrawPacket& i_DrawPacket                       // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()  // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void Stage::CommandTranslator(DrawPacket& i_DrawPacket){
	switch(i_DrawPacket.PopCommand().m_Command){
		case GM_CHANGE_CHILDSTAGE:
		{
			if( m_pChildStage )
				m_pChildStage->m_IsDialog = false ;
			break ;
		}
		case GM_CHANGE_PARENTSTAGE:
		{
			m_IsDialog = true ;
			break ;
		}
	}
};
void Stage::AddButton(wiz::Object* pButton){
	Button* pb = pButton->getButtonP();
	pb->setIndex(m_ButtonVec.size());
	m_ButtonVec.push_back( pb );
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





/**************************************************************************
 MenuStage 定義部
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par){
	m_pChildStage = 0;
	try{
        // ライティングモード
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //ライトのインスタンス初期化
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        m_Vec.push_back(
			new DirectionalLight(
				pD3DDevice,
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3(0.4f, -1.0f, 0.4f)
			)
		);
        //カメラのインスタンス初期化
        m_Vec.push_back(
			new Camera(
				pD3DDevice,
				D3DXVECTOR3( 0.0f, 2.0f, -30.0f),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				1.0f,
				100.0f,
				60.0f
			)
		);

	}
	catch(...){
		//親クラスのClear()を呼ぶ
		Clear();
		//再スロー
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MenuStage::~MenuStage(){
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void MenuStage::Update(UpdatePacket& i_UpdatePacket)
{
	Stage::Update(i_UpdatePacket);
}


/**************************************************************************
 void MenuStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void MenuStage::Draw(DrawPacket& i_DrawPacket){
	Stage::Draw(i_DrawPacket);
}

}
//end of namespace wiz.
