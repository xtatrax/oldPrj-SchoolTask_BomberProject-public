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
		Object(OBJID id):m_bAccessLock(false),m_bDead(false),m_dwID(id){}
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
///////////////////// ////////////////////
//// 関数名     ：D3DXVECTOR3 getPos() const { return g_vZero; }
//// カテゴリ   ：ゲッター
//// 用途       ：DEAD OR ALIVE
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	D3DXVECTOR3 getPos() const { return g_vZero; }
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
/**************************************************************************
	virtual void ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに最構築時に呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
		//基底クラスでは何もしない
	}

/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
    virtual void Update( UpdatePacket& i_UpdatePacket ){};

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
	virtual void TargetRender( RenderPacket& i_RenderPacket ){};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：
//// 備考       ：継承するものは何れかのレベルで必ず定義をすること｡
////            ：
////
    virtual void Draw( DrawPacket& i_DrawPacket ) = 0;
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

/**************************************************************************
 class Camera : public Object;
 用途: カメラクラス
****************************************************************************/
class Camera : public Object{
protected:
    D3DXMATRIX  m_View;     // カメラの配置
    D3DXMATRIX m_Proj;		// 射影行列
    D3DXVECTOR3 m_Eye;      //カメラの位置
    D3DXVECTOR3 m_At;       //直視点
    FLOAT m_Near;           //射影の手前側の距離
    FLOAT m_Far;            //射影の奥側の距離
    FLOAT m_FovY;           //射影角度

    D3DXVECTOR3 m_Arm;       //視点と直視点の間（腕）のベクトル
	FLOAT m_TotalAngleXZ;	//カメラのXZ回転のラジアン値
	FLOAT m_TotalAngleY;	//カメラのY回転のラジアン値

public:
/**************************************************************************
 Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    D3DXVECTOR3& At,    //直視点
	FLOAT AbsPosZFromAt,//直視点から見た、カメラ位置のZの位置(絶対値指定)
	FLOAT PosYFromAt,	//直視点から見た、カメラ位置のYの位置
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 ＊カメラ位置の初期値は直接は指定できない。
 ＊直視点からみて、Zの手前に引く相対位置とYの相対位置を指定する。Xは0に固定
 ＊Zの手前に引く相対位置（AbsPosZFromAt）は絶対値化されるので、
	マイナスを指定しても意味がない。
 戻り値: なし
***************************************************************************/
 Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& At,FLOAT PosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    D3DXVECTOR3& Eye,    //カメラの位置
    D3DXVECTOR3& At,    //直視点
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);

/**************************************************************************
 virtual ~Camera();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Camera();
/**************************************************************************
 virtual void Draw(
    DrawPacket& i_DrawPacket 
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
/**************************************************************************
 void GetEyeAt(
 D3DXVECTOR3& Eye,	//カメラの位置
 D3DXVECTOR3& At	//注視点
 );
 用途: カメラの現在の位置と注視点を得る
 戻り値: なし。EyeとATに値を代入
***************************************************************************/
	void GetEyeAt(D3DXVECTOR3& Eye,D3DXVECTOR3& At){
		Eye = m_Eye;
		At = m_At;
	}
	D3DXVECTOR3 getEye(){ return m_Eye ; }
	D3DXVECTOR3 getAt(){  return m_At ; }
/**************************************************************************
 void GetMatrix(
 D3DXMATRIX& View,	//ビュー行列
 D3DXMATRIX& Proj	//射影行列
 );
 用途: カメラのビュー行列と射影行列を得る
 戻り値: なし。ViewとProjに値を代入
***************************************************************************/
	void GetMatrix(D3DXMATRIX& View,D3DXMATRIX& Proj){
		View = m_View;
		Proj = m_Proj;
	}
/**************************************************************************
 FLOAT GetFar();
 用途: カメラのFar位置を得る
 戻り値: Far位置
***************************************************************************/
	FLOAT GetFar(){
		return m_Far;
	}
/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
	float getPosY(){ return m_Eye.y ; };
/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
	void setPosY( float i_fYPos ){
		m_Eye.y = m_At.y = i_fYPos ; 
	};
};

/**************************************************************************
 class LookAtCamera : public Camera;
 用途: オブジェクトを注目するカメラクラス
****************************************************************************/
class LookAtCamera : public Camera{
protected:
	Object* m_pObject;
	FLOAT m_LocalY;
public:
/**************************************************************************
 LookAtCamera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 インターフェイスへのポインタ
    Object*	pObj,		//直視点を得るためのオブジェクト
	FLOAT LocalY,		//直視点から調整するY位置
	FLOAT AbsPosZFromAt,//直視点から見た、カメラ位置のZの位置(絶対値指定)
	FLOAT PosYFromAt,	//直視点から見た、カメラ位置のYの位置
    FLOAT Near,         //射影の手前側の距離
    FLOAT Far,          //射影の奥側の距離
    FLOAT FovY          //Y軸射影角度
    );
 用途: コンストラクタ
 ＊カメラ位置の初期値は直接は指定できない。
 ＊直視点からみて、Zの手前に引く相対位置とYの相対位置を指定する。Xは0に固定
 ＊Zの手前に引く相対位置（AbsPosZFromAt）は絶対値化されるので、
	マイナスを指定しても意味がない。
 戻り値: なし
***************************************************************************/
	LookAtCamera(LPDIRECT3DDEVICE9 pD3DDevice,
		Object* pObj,FLOAT LocalY,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
	    FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
 virtual ~LookAtCamera();
 用途: 仮想デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~LookAtCamera();
/**************************************************************************
 virtual void Transform(
	UpdatePacket& i_UpdatePacket
 );
 用途: オブジェクトを変化させる（仮想関数）
 戻り値: なし。
***************************************************************************/
	virtual void Update( UpdatePacket& i_UpdatePacket );
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data);
};

/**************************************************************************
 class Guide : public Object;
 用途: ガイドクラス（x、y、z方向に伸びるガイド線）
****************************************************************************/
class Guide : public Object{
protected:
    IDirect3DVertexBuffer9* m_pVB;
    //クラス内構造体
    //ここでしか使用しないので、内部に持つ
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };
/**************************************************************************
 void CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9インターフェイスへのポインタ
 );
 用途: インスタンスの構築
 戻り値: なし。（例外がthrowされる）
***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
public:
/**************************************************************************
 Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9インターフェイスへのポインタ
    );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
    Guide(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~Guide();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Guide();
/**************************************************************************
	virtual void ReleaseObj();
 用途: デバイス喪失によるリソースの開放（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ReleaseObj();
/**************************************************************************
	virtual void ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
	);
 用途: デバイス喪失による再構築（仮想関数）
 戻り値: なし。
 ＊デバイスが喪失したときに最構築時に呼ばれる。すべてのObjectの派生クラスは、個別に対応をとる
***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Context& Data					//ユーザーデータ
 );
 用途: オブジェクトを描画（純粋仮想関数）
 戻り値: なし。
***************************************************************************/
		virtual void Draw(DrawPacket& i_DrawPacket);
	};


}
//end of namespace wiz.

