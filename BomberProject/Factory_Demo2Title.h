////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Demo2Title.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：
//					▼
//	namespace wiz;
//
#pragma once

//////////
//	: インクルード
//	: インクルード
//////////

namespace wiz{
namespace bomberbehavior{
	class Demo2Titre : public Behavior{
		/////////////////// ////////////////////
		//// 用途       ：virtual void Demo2Titre::Update( UpdatePacket& i_UpdatePacket )
		//// カテゴリ   ：仮想関数
		//// 用途       ：オブジェクトを更新
		//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
		////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
		////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
		////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
		////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
		////            ：  └       Command            pCommand        // コマンド
		//// 戻値       ：なし
		//// 担当者     ：鴫原 徹
		//// 備考       ：継承したものでも必ずとも定義をしなくても良い
		////            ：
		////
		virtual void Update( UpdatePacket& i_UpdatePacket );
	};
}
using namespace bomberbehavior ;
}