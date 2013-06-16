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

/**************************************************************************
 class Button ;
 用途: ボタン根底クラス
 用法: もしButtonPlateから派生しないクラスをボタンにしたい時は以下のようにす
	ることによってボタン化することができます
	まずこのクラスをクラス内に宣言してください
		例)
		    class foo{
		    private:
		       Button m_ButtonPrm;
		       ・
		       ・
		       ・
	次にオブジェクト配列追加する際、StageクラスのButton用配列にこのクラスの
	インスタンスへのポインターを追加してください
		例)	m_vec.push_back(pButtonPlate);
			m_ButtonVec.push_back(&pButtonPlate->m_ButtonPrm);
 ****************************************************************************/
class Button {
protected:
	static DWORD m_MouseSelectIndex;
	DWORD	m_Index;				//メニュー上のインデックス
	bool	m_IsSelect;				//選択フラグ
	bool	m_IsMouseSelect;		//マウスによって選択されている
	bool	m_IsPressed;			//決定フラグ
	Command	m_Command;				//コマンド
	
public:
/**************************************************************************
 Button(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Button(Command Cmd,DWORD Index);
/**************************************************************************
 virtual ~Button();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Button();
/**************************************************************************
 void setSelect(
	bool select	//選択状態
 );
 用途: 選択状態を設定
 戻り値: なし。
***************************************************************************/
	void setSelect(bool select){
		m_IsSelect = select;
	}
/**************************************************************************
 void setSelect(
	bool select	//選択状態
 );
 用途: 選択状態を設定
 戻り値: なし。
***************************************************************************/
	void setMouseSelect(bool select){
		if(m_IsSelect = m_IsMouseSelect = select)
			m_MouseSelectIndex = m_Index ;
	}
/**************************************************************************
 void setPressed();
 用途: 決定フラグをセットする
 戻り値: なし。
***************************************************************************/
	void setPressed(){
		m_IsPressed = true;
	}
/**************************************************************************
 bool getSelect();
 用途: 選択されてるかどうか
 戻り値: 0 非選択 / 1 選択
***************************************************************************/
	bool getSelect(){
		return m_IsSelect;
	}
/**************************************************************************
 void setSelect(
	bool select	//選択状態
 );
 用途: 選択状態を設定
 戻り値: なし。
***************************************************************************/
	static DWORD getMouseSelectIndex(){
		DWORD ret = m_MouseSelectIndex;
		m_MouseSelectIndex = ULONG_MAX ;
		return ret;
	}
/**************************************************************************
 bool getPressed();
 用途: 決定されたかどうか
 戻り値: 0 非決定 / 1 決定
***************************************************************************/
	bool getPressed(){
		if( m_IsPressed ){
			m_IsPressed = false ;
			return true  ;
		}else{
			return false ;
		}
	}
/**************************************************************************
 void setSelect();
 用途: コマンドの発行
 戻り値: 発行されたコマンド
***************************************************************************/
	Command CommandIssue(){
		m_IsPressed		= false;
		return m_Command;
	}
/**************************************************************************
 void getIndex();
 用途: 自分が何番目のボタンかを返す
 戻り値: 自分の番号
***************************************************************************/
	DWORD getIndex(){
		return m_Index;
	}
};

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
