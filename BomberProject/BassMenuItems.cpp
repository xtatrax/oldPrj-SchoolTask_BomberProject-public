////////////////////////////// //////////////////////////////
//	プロジェクト	：Stick Figures
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
#include "StdAfx.h"
#include "BassMenuItems.h"

namespace wiz{
namespace menuobject{

/**************************************************************************
 Button 定義部
****************************************************************************/
/**************************************************************************
 Button::Button(
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    );
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Button::Button(DWORD Cmd,DWORD Index)
:m_Index(Index),m_IsPressed(false),m_IsSelect(false),m_Command(Cmd)
{
	//もしインデックスが0番なら、初期状態で選択されている
	if(m_Index == 0){
		m_IsSelect = true;
	}
}
/**************************************************************************
 virtual ~Button::Button();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Button::~Button(){

}





ButtonSprite::ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color SelectColor,
		Color UnSelectColor,DWORD dwCom,DWORD dwIndex)
:m_ButtonState(dwCom,dwIndex)
,SpriteObject(pD3DDevice,pTexture,vScalse,vRot,vPos,pRect,vCenter,vOffset,UnSelectColor)
,m_SelectColor(SelectColor)
,m_UnSelectColor(UnSelectColor)
{
	try{
	}
	catch(...){
		//再スロー
		throw;
	}


}
ButtonSprite::~ButtonSprite(){};
/////////////////// ////////////////////
//// 関数名     ：void ButtonSprite::Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            ：      vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  const CONTROLER_STATE* pCntlState   // コントローラのステータス
////            ：  Command i_DrawPacket.pCommand       // コマンド
//// 戻値       ：無し
//// 備考       ：
////            ：
////
void ButtonSprite::Update(UpdatePacket& i_UpdatePacket){

};


/////////////////// ////////////////////
//// 関数名     ：void ButtonSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            ：      vector<Object*>& Vec,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：無し
//// 備考       ：
////            ：
////
void ButtonSprite::Draw(DrawPacket& i_DrawPacket){
	if(m_ButtonState.getSelect()){
		m_Color = m_SelectColor;
		if(m_ButtonState.getPressed()){
			*i_DrawPacket.pCommand = m_ButtonState.CommandIssue();
		}
	}else{
		m_Color = m_UnSelectColor;
	}
	SpriteObject::Draw(i_DrawPacket);
};

}//end of namespace menuobject.
}//end of namespace wiz.
