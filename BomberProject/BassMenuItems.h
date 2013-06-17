////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：BassMenuItems.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：
//	内包ﾃﾞｰﾀと備考	：メニューの部品群
//					▼
//	namespace wiz;
//		class Button;
//		class ButtonSprite : public SpriteObject;
//
#pragma once
#include "BassItems.h"
#include "Bass2DItems.h"

namespace wiz{

namespace menuobject{


class ButtonSprite : public SpriteObject{
protected:
	Button	m_ButtonState		;
	Color	m_SelectColor		;
	Color	m_UnSelectColor		;
public:
	ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color dwSelectColor,
		Color dwUnSelectColor,Command Com,DWORD dwIndex);
	virtual ~ButtonSprite();
/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  const CONTROLER_STATE* pCntlState   // コントローラのステータス
////            ：  Command Com                         // コマンド
//// 戻値       ：無し
//// 備考       ：
////            ：
////
    virtual void Update(UpdatePacket& i_UpdatePacket);

/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec)
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  Command Com                         // コマンド
//// 戻値       ：無し
//// 備考       ：
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

	Button* getButtonP(){ return &m_ButtonState;}
} ;
}//end of namespace menuobject.
using namespace menuobject ;
}//end of namespace wiz.
