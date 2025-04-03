////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_BackGround.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包データと備考	：コンテニュー
//					▼
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//
#pragma once

//////////
//	: インクルード
//	: インクルード
//////////

namespace wiz{
namespace bomberobject{


//**************************************************************************//
// class Factory_BG ;
//
// 担当者  : 鴫原 徹
// 用途    : 壁紙
//**************************************************************************//
class BackGround : public Box{
	Camera*		m_pCamera;
	UINT		m_uiYNum;
public:
	BackGround(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 vScalse,LPTATRATEXTURE pTextuer);

	~BackGround();

	/////////////////// ////////////////////
	//// 用途       ：void update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );
};

//**************************************************************************//
// class Factory_BG ;
//
// 担当者  : 鴫原 徹
// 用途    : 壁紙
//**************************************************************************//
class Factory_BG{
public:
	/////////////////// ////////////////////
	//// 関数名     ：Factory_BG( FactoryPacket* fpac );
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：FactoryPacket* fpac
	//// 戻値       ：なし
	//// 担当       ： 鴫原 徹
	//// 備考       ：
	////            ：
	////
	Factory_BG( FactoryPacket* fpac );
};
}
}