//////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPointSave.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：チェックポイント通貨でセーブする機能
//					▼
//	namespace wiz;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_CheckPointSave.h"
//	: 基本のインクルード
//////////
//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////


namespace wiz{
namespace bomberbehavior{
CheckPointSave* CheckPointSave::m_pMyInstance = NULL ;
CheckPointSave::CheckPointSave(DWORD dwStageNum)
:Behavior(OBJID_BEHAVIOR_CHECKPOINTSAVE)
,m_pCheckPoint( NULL )
,m_pCoil( NULL )
{
	m_Data.dwStageNum = dwStageNum;

}

/////////////////// ////////////////////
//// 用途       ：void CheckPointSave::Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
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
void CheckPointSave::Update( UpdatePacket& i_UpdatePacket ){
	!m_pCoil		&& (       m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL			) ) ;
	!m_pCheckPoint	&& ( m_pCheckPoint = (CheckPoint*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CHECKPOINT	) ) ;
	if( m_pCheckPoint->getActiveItem() > m_Data.dwCheckPoint){
		m_Data.dwCheckPoint = m_pCheckPoint->getActiveItem();
		m_Data.dwDeadNum	= m_pCoil->getDeadCount();
		TLIB::BinarySave( RCTEXT_SAVEDATA_FILENAME,m_Data);
	}

}


/////////////////// ////////////////////
//// 関数名     ：Factory_CheckPointSave(FactoryPacket* fpac)
//// カテゴリ   ：コンストラクタ
//// 用途       ：チェックポイントでセーブする機能を作成します
//// 引数       ：  FactoryPacket* fpac
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
Factory_CheckPointSave::Factory_CheckPointSave(FactoryPacket* fpac,DWORD dwStageNum){
	fpac->AddObject(
		CheckPointSave::getInstance(dwStageNum)
	);
	
};


}
}