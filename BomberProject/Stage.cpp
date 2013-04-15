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



namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 Stage 定義部
****************************************************************************/
/**************************************************************************
 void Stage::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void Stage::Clear(){
	SafeDelete(m_pChildStage);
	//SafeDelete(m_pParStage);
	SAFE_DELETE_VECTOR(m_Vec);
	m_TexMgr.Release();
}

/**************************************************************************
 Stage::Stage(
 Stage* Par	//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Stage::Stage(Stage* Par)
:m_pParStage(Par),m_pChildStage(0),m_IsDialog(false)
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
,m_bSlow(false)
#endif
/////////////////// ////////////////////

{}
/**************************************************************************
virtual Stage::~Stage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Stage::~Stage(){
	Clear();
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
	i_UpdatePacket.pVec = &m_Vec ;
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
	float fElapsedTime = (float)i_UpdatePacket.pTime->getElapsedTime();
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
	//配置オブジェクトの描画
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->AccessBegin();
		m_Vec[i]->Update(i_UpdatePacket) ;
		if(m_Vec[i]->getDead()){
			//vector<Object*>
			//SAFE_DELETE(*(m_Vec.begin() + i)) ;
			//m_Vec.erase( i-- ) ;
		}
		m_Vec[i]->AccessEnd();
	}
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
void Stage::Draw(DrawPacket& i_DrawPacket)
{
	//配置オブジェクトの描画
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->AccessBegin();
		m_Vec[i]->Draw(i_DrawPacket);
		m_Vec[i]->AccessEnd();
	}
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
:Stage(Par),m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false){
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
	//ボタン配列のみクリアする
	//配置されてるポインタの削除は行なわない
	m_ButtonVec.clear();
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
	if( i_UpdatePacket.pTxMgr == NULL ) i_UpdatePacket.pTxMgr = &m_TexMgr ;
	CONTROLER_STATE	ControllerState1P = i_UpdatePacket.pCntlState[0];
    if(!m_SelectLock){
		//	: 次のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN 
			|| ControllerState1P.Gamepad.sThumbLY < 0){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: 前のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP
			|| ControllerState1P.Gamepad.sThumbLY > 0){
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
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_A&&
			!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setPressed();
			m_SelectLock = true;
		}
	}
	if(!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
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
