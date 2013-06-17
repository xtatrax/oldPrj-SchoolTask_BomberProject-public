////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPointSave.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：チェックポイント通貨でセーブする機能
//					▼
//	namespace wiz;
//
#pragma once

//////////
//	: インクルード
#include "Factory_CheckPoint.h"
//	: インクルード
//////////

namespace wiz{
using namespace bomberobject ;
namespace bomberbehavior{
class CheckPointSave : public Behavior{
	static CheckPointSave*	m_pMyInstance	;
	       CheckPoint*		m_pCheckPoint	;
		   PlayerCoil*		m_pCoil			;
		   SaveData			m_Data			;
	/////////////////// ////////////////////
	//// 用途       ：CheckPointSave::CheckPointSave();
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	CheckPointSave(DWORD dwStageNum);
public:
	static CheckPointSave* getInstance(DWORD dwStageNum){
		if( m_pMyInstance )return m_pMyInstance;
		return new CheckPointSave(dwStageNum);
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
	void Update( UpdatePacket& i_UpdatePacket );

};

//**************************************************************************//
// class Factory_CheckPointSave ;
//
// 担当  : 鴫原 徹
// 用途  : チェックポイントでセーブを行う機能を作成します
//**************************************************************************//
class Factory_CheckPointSave{
public:
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
	Factory_CheckPointSave(FactoryPacket* fpac,DWORD dwStageNum);
	~Factory_CheckPointSave(){};
};

}
using namespace bomberbehavior ;
}