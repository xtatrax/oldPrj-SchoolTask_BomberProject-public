////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_PlaneCircle.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		namespace bomberobject;
//
#pragma once
//////////
//	: インクルード
//	: インクルード
//////////
namespace wiz{
namespace bomberobject{

/**************************************************************************
 class Factory_PlaneCircle;
 用途: メイン工場クラス
****************************************************************************/
class Factory_PlaneCircle{
public:
/**************************************************************************
 Factory_PlaneCircle(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr			//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_PlaneCircle(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_PlaneCircle();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
