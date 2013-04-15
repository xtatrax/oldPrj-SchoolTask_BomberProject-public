////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Object.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		class Object ;
//		class Light  ;
//		class DirectionalLight : public Light , public Object ;
//
#pragma once

#include "StdAfx.h"
#include "TextureManager.h"
#include "Tempus/Tempus.h"
#include "Controller/Controller.h"

namespace wiz{

extern class Object;

struct UpdatePacket{
	const CONTROLER_STATE*	pCntlState	;
	LPDIRECT3DDEVICE9		pD3DDevice	;
	vector<Object*>*		pVec		;
	TextureManager*			pTxMgr		;
	TLIB::Tempus2*			pTime		;
	Command*				pCommand	;
	UpdatePacket()
		:pCntlState( NULL )
		,pD3DDevice( NULL )
		,pVec( NULL )
		,pTxMgr( NULL )
		,pTime( NULL )
		,pCommand( NULL )
	{
	}

};
struct RenderPacket{
	LPDIRECT3DDEVICE9	pD3DDevice	;
	vector<Object*>*	pVec		;
	Command*			pCommand	;
};
struct DrawPacket{
	LPDIRECT3DDEVICE9	pD3DDevice	;
	vector<Object*>*	pVec		;
	TLIB::Tempus2*		pTime		;
	Command*			pCommand	;
};



//**************************************************************************
// class Object;
//
// 担当者  :
// 用途    : シーン配置オブジェクトの基底クラス（抽象クラス）
//**************************************************************************
class Object{
private:
	bool	m_bAccessLock;
	bool	m_bDead;
	OBJID	m_dwID;
public:
	Object(OBJID id):m_bAccessLock(false),m_dwID(id){}
    virtual ~Object(){}
/////////////////// ////////////////////
//// 関数名     ：void getID()
//// カテゴリ   ：セッター
//// 用途       ：死亡フラグを設定
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	DWORD getID() const { return m_dwID ; }
/////////////////// ////////////////////
//// 関数名     ：void setDead()
//// カテゴリ   ：セッター
//// 用途       ：死亡フラグを設定
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	void setDead(){	m_bDead = true ; }
/////////////////// ////////////////////
//// 関数名     ：bool getDead()
//// カテゴリ   ：ゲッター
//// 用途       ：DEAD OR ALIVE
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	bool getDead() const { return m_bDead; }
/////////////////// ////////////////////
//// 関数名     ：void AccessBegin()
//// カテゴリ   ：メンバ関数
//// 用途       ：データへのアクセスを開始
//// 引数       ：なし
//// 戻値       ：あし
//// 担当者     ：鴫原 徹
//// 備考       ：マルチスレッドを利用する際に複数のスレッドが同時にデータを書き換えるのを防ぐ
////            ：下記の関数 ( void AccessEnd() ) とセット
////
	void AccessBegin(){	while(m_bAccessLock){ Sleep(1); } m_bAccessLock = true; };
/////////////////// ////////////////////
//// 関数名     ：void AccessEnd()
//// カテゴリ   ：メンバ関数
//// 用途       ：データへのアクセスを終了
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：マルチスレッドを利用する際に複数のスレッドが同時にデータを書き換えるのを防ぐ
////            ：上記の関数 ( void AccessBegin() ) とセット
////
	void AccessEnd(){ m_bAccessLock = false; }
/////////////////// ////////////////////
//// 関数名     ：virtual bool HitTest(D3DXVECTOR3 Pos)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  D3DXVECTOR3 Pos      //
//// 戻値       ：false
//// 担当者     ：
//// 備考       ：派生先で必要ならば書く
////            ：  
////
    virtual bool HitTest(D3DXVECTOR3 Pos){ return false; }
/////////////////// ////////////////////
//// 用途       ：virtual bool HitTest(Object* other)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：Object* other      // 他のオブジェのポインタ
//// 戻値       ：false 
//// 担当者     ：
//// 備考       ：派生先で必要ならば書く
////            ：
////
    virtual bool HitTest(Object* other){ return false; }
/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：      vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  Tempus2* i_DrawPacket.pTime                     // 時間を管理するクラスへのポインター
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  const CONTROLER_STATE* pCntlState   // コントローラのステータス
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
    virtual void Update(UpdatePacket& i_UpdatePacket){};

/////////////////// ////////////////////
//// 用途       ：virtual void TargetRender( LPDIRECT3DDEVICE9 pD3DDevice
////            ：      vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
	virtual void TargetRender(RenderPacket& i_RenderPacket){};

/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec)
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec                // オブジェクトの配列
////            ：  Tempus2* i_DrawPacket.pTime                     // 時間を管理するクラスへのポインター
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) = 0;
};

//**************************************************************************
// class Light;
//
// 担当者  : 
// 用途    : ライトクラス
//**************************************************************************
class Light{
protected:
    D3DLIGHT9   m_Light;
/////////////////// ////////////////////
//// 用途       ：Light()
//// カテゴリ   ：こんすとらくた
//// 用途       ：プロテクトコンストラクタ
//// 引数       ：なし
//// 戻値       ：なし 
//// 担当者     ：
//// 備考       ：直接構築できないように、プロテクトにする
////            ：
////
    Light();
/////////////////// ////////////////////
//// 用途       ：Light()
//// カテゴリ   ：ですとらくた
//// 用途       ：プロテクトデストラクタ（仮想デストラクタ）
//// 引数       ：なし
//// 戻値       ：なし 
//// 担当者     ：
//// 備考       ：直接構築できないように、プロテクトにする
////            ：
////
    virtual ~Light();
};

//**************************************************************************
// class DirectionalLight : public Light , public Object;
//
// 担当者  : 
// 用途    : ディレクショナルライトクラス
//**************************************************************************
class DirectionalLight : public Light , public Object{
public:
/////////////////// ////////////////////
//// 用途       ：DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
////            ：    D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,
////            ：    D3DCOLORVALUE Ambient,D3DXVECTOR3 Direction)
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：  LPDIRECT3DDEVICE9 pD3DDevice,   //デバイス
////            ：  D3DCOLORVALUE Diffuse,          //ディフューズ色
////            ：  D3DCOLORVALUE Specular,         //スペキュラ色
////            ：  D3DCOLORVALUE Ambient,          //アンビエント色
////            ：  D3DXVECTOR3 Direction           //ワールド空間で光が指す方向
//// 担当者     ：
//// 備考       ：ディレクショナルライトを構築する
////            ：
////
    DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE Diffuse,
        D3DCOLORVALUE Specular,
        D3DCOLORVALUE Ambient,
        D3DXVECTOR3 Direction,
		wiz::OBJID id = OBJID_SYS_LIGHT);
/////////////////// ////////////////////
//// 用途       ：virtual ~DirectionalLight()
//// カテゴリ   ：セストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：
//// 備考       ：
////            ：
////
    virtual ~DirectionalLight();
/////////////////// ////////////////////
//// 用途       ：virtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            ：  vector<Object*>& Vec)
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：無し
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
	virtual void Draw(DrawPacket& i_DrawPacket){};


};






}
//end of namespace wiz.

