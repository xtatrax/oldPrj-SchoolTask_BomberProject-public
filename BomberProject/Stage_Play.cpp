////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Stage_Pray.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：プレイステージ
//					▼
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "Factory_Main.h"
#include "Factory_Sound.h"
#include "Stage_Play.h"
#include "stage.h"
#include "Factory_Player.h"

namespace wiz{
using namespace bomberobject;




/**************************************************************************
 PlayStage 定義部
****************************************************************************/
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//デバイス
	const Script::MLPHeader& Header,	//	: プレイする楽曲のヘッダーデータ
	const Script::SCORELEVEL Level		//	: プレイするレベル種別
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
PlayStage::PlayStage( LPDIRECT3DDEVICE9 pD3DDevice, DWORD dwStageNum, DWORD dwResumptionCheckPoint, D3DXVECTOR3 vStartPos, Stage* pStage )
	:Stage(pStage)
{
	try{
		FactoryPacket FPac;
		FPac.m_IsDialog =  this->m_IsDialog ;
		FPac.m_pTexMgr  = &this->m_TexMgr   ;
		FPac.m_pVec     = &this->m_Vec      ;
		FPac.pD3DDevice =  pD3DDevice       ;
		D3DXVECTOR3* vp = NULL ;
		if( vStartPos != g_vMax )
			vp = &vStartPos;
	
		Factory_Main mainF( &FPac, dwStageNum, dwResumptionCheckPoint, vp );
		m_dwNowStage = dwStageNum ;
	}
	catch(LoaderException& e){
		throw LoaderException(
				e.what_w(),
				L"↑PlayStage::PlayStage()"
				);
	}
	catch(exception& e){
		Clear();
		//再スロー
		throw e;
	}
	catch(...){
		Clear();
		//再スロー
		throw;
	}
}
/**************************************************************************
PlayStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
PlayStage::~PlayStage(){
	
}
/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：ステージを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void PlayStage::Update(UpdatePacket& i_UpdatePacket){
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )

	//	:  エンターで再スタート
	if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RESTART ) ){
		//	:  Alt+ENTERで再読み込み
		if( GetAsyncKeyState( MYVK_DEBUG_STAGE_RELOAD ) ){
			PlayerCoil* pc = (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL );
			i_UpdatePacket.pCommand->m_Command = GM_OPENDEBUGSTAGE_PLAY_RELOAD ;
			i_UpdatePacket.pCommand->m_Param1 = (DWORD)pc ;

		}else{
			i_UpdatePacket.pCommand->m_Command = GM_OPENSTAGE_PLAY ;
		}
	}
#endif
	Stage::Update( i_UpdatePacket );
}

}
//end of namespace wiz.
