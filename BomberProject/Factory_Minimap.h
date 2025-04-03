////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Minimap.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 本多寛之(編集)
//	内包データと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Minimap ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Player.h"

namespace wiz{
namespace bomberobject{

class MiniMap : public Object{
	LPDIRECT3DTEXTURE9	m_Texture ;
public:
	
};
/**************************************************************************
 class Factory_Minimap;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Minimap{
public:
/**************************************************************************
 Factory_Minimap(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Minimap(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Minimap();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
