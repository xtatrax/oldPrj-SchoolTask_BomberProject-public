////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Player.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹 曳地大洋(編集) 本多寛之(編集)
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Player ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Magnetic.h"

const int	START_EFFECTIVE_RANGE		= 12;
const int 	START_EFFECTIVE_RANGE_QUAD	= (START_EFFECTIVE_RANGE * START_EFFECTIVE_RANGE);
const float PLAYER_SPEED				= 0.08f;
const float PLAYER_BASSROT				= 90.0f;
const float PLAYER_TURN_ANGLE_Lv1		= 1.0f;
const float PLAYER_TURN_ANGLE_Lv2		= 2.0f;
const float PLAYER_TURN_ANGLE_Lv3		= 3.0f;

enum COIL_STATE{			//自機の状態
	COIL_STATE_START,		//スタート
	COIL_STATE_MOVE,		//移動
	COIL_STATE_STOP,		//停止
	COIL_STATE_STICK,		//吸着
	COIL_STATE_SUPER,		//無敵
	COIL_STATE_DEAD			//死亡
};

namespace wiz{



//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
class ProvisionalPlayer : public MagneticumObject{
public:
	//	: 
	ProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
};

// 3D用
//**************************************************************************//
// class ProvisionalPlayer : public MagneticumObject ;
//
// 担当者  : 曳地大洋
// 用途    : 仮のユーザー設置磁界
//**************************************************************************//
class ProvisionalPlayer3D : public MagneticumObject3D{
	Camera*			m_Camera;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	float			m_MovePosY;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;
	bool			m_bCoilWasFired;
	bool			m_bDrawing;
public:
	//	: 
	ProvisionalPlayer3D( FactoryPacket* fpac, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,
		wiz::OBJID id = OBJID_3D_PLAYER );
	//	:
	void Draw( DrawPacket& i_DrawPacket );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const {
		if( g_bMouseLB || g_bMouseRB ){ 
			return m_vPos	;
		}else{
			return g_vMin	;
		}
	}	;

	/////////////////// ////////////////////
	//// 関数名     ：float getMoveY() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_MovePosYを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	float getMoveY() const { return m_MovePosY	;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：void CoilWasFired(bool i_bFlg)
	//// カテゴリ   ：関数
	//// 用途       ：m_bCoilWasFiredに値を入れる
	//// 引数       ：bool i_bFlg
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void CoilWasFired(bool i_bFlg){
		m_bCoilWasFired = i_bFlg;
	}

	/****************************************
	関数名　：bool	getDrawing()
	カテゴリ：関数
	用途　　：描画フラグの取得
	引数　　：なし
	戻り値　：描画しているかのフラグ
	担当　　：佐藤涼
	備考　　：
	****************************************/
	bool	getDrawing(){
		return	m_bDrawing;
	}
};

/************************************************************************
class MagneticField : public Cylinder

担当者	: 佐藤涼
用途	: 磁界の範囲
************************************************************************/
class	MagneticField : public Cylinder{
	bool	m_Pole;	//磁界の極：t=S極, f=N極
	bool		m_bEffect;
	D3DXVECTOR3	m_vNormalSize;
	D3DXMATRIX	m_mMatrix;
public:
	MagneticField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXQUATERNION &vRot, D3DXVECTOR3 &vPos,bool bEffect);
    void	Draw(DrawPacket& i_DrawPacket) ;
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPole( bool pole ){
		m_Pole	= pole;
	}
	bool	getPole(){
		return	m_Pole;
	}
};

//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 鴫原 徹 本多寛之(編集)
// 用途    : コイル
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
#if defined( ON_DEBUGGINGPROCESS )
	DrawSphere*		m_pDSPH ;
#endif
	Cylinder*		m_pCylinder ;
	D3DXMATRIX		m_Matrix ;
	D3DXVECTOR3		m_vPos ;
	D3DXQUATERNION	m_vRot ;
	D3DXVECTOR3		m_vScale ;
	D3DXVECTOR3		m_vMove;
	float			m_fMoveDir   ;//角度
	float			m_fMovdSpeed ;//速度
	D3DXVECTOR3		m_vStartPos;
	float			m_fTurnAngle;
	bool			m_bLastMouseRB;
	bool			m_bLastMouseLB;

	ProvisionalPlayer3D*	m_pPlayer;

	MagneticumObject3D*		m_pMagneticumObject;

	Camera*					m_pCamera;
	
	COIL_STATE		m_enumCoilState;

public:
	/////////////////// ////////////////////
	//// 関数名     ：PlayerCoil( 	
	////							LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////							float Radius1,float Radius2,float Lenght,
	////							D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////							D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////							wiz::OBJID id = OBJID_3D_PLAYER)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
	////		      :   float Radius1						//円の直径1
	////		      :   float Radius2						//円の直径2
	////			  :   flaot Lenght						//高さ
	////			  :   D3DXVECTOR3 &vScale
	////		      :   D3DXVECTOR3 &vRot				//回転角
	////		      :   D3DXVECTOR3 &vPos				//位置
	////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
	////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
	////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
	////			  : wiz::OBJID id = OBJID_2D_PLAYER //ID
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹 本多寛之(修正)
	//// 備考       ：
	////            ：
	////
	PlayerCoil(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		float Radius1,
		float Radius2,
		float Lenght,
		D3DXVECTOR3 &vScale,	
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_PLAYER
	);

	/////////////////////// ////////////////////
	//////// 用途       ：	bool HitTestMultiBox(MultiBox* pBox,size_t& Index,D3DXVECTOR3& Vec,D3DXVECTOR3& ElsePos)
	//////// カテゴリ   ：MultiBoxとの衝突判定
	//////// 用途       ：マルチボックスとの衝突判定
	//////// 引数       ：  bool HitTestMultiBox
	////////				  MultiBox* pBox,	//マルチボックス
	////////				  size_t& Index,	//ヒットしていたらインデックスが戻る
	////////				  D3DXVECTOR3& Vec,         //最近接点
	////////				  D3DXVECTOR3& ElsePos         //一つ前のポジション
	//////// 戻値       ：衝突していればtrue
	////////				ヒットしてたらtrue（インデックスと最近接点を代入）
	//////// 担当者     ：曳地 大洋
	//////// 備考       ：
	bool HitTestWall( OBB, float Index );

	/////////////////// ////////////////////
	//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			  ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////			  ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////			  ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////              ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：void Update_StateStart()
	//// カテゴリ   ：
	//// 用途       ：STATE_START時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateStart();

	/////////////////// ////////////////////
	//// 関数名     ：void Update_StateMove()
	//// カテゴリ   ：
	//// 用途       ：STATE_MOVE時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateMove();

	/////////////////// ////////////////////
	//// 関数名     ：void Update_StateSuper()
	//// カテゴリ   ：
	//// 用途       ：STATE_SUPER時の動き
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			  ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////			  ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////			  ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////              ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateSuper( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：void Update_StateDead()
	//// カテゴリ   ：
	//// 用途       ：STATE_DEAD時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateDead();

	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    void Draw(DrawPacket& i_DrawPacket) ;

	/////////////////// ////////////////////
	//// 関数名     ：float MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
	//// カテゴリ   ：関数
	//// 用途       ：自機に対する吸い寄せ、反発の処理
	//// 引数       ：float i_fCoilDir            //自機の角度
	////　　　　　　：D3DXVECTOR3& i_vMagnetPos   //磁界の位置
	////　　　　　　：bool i_bMagnetPole_Field	// 磁界の極
	//// 戻値       ：
	//// 担当       ：本多寛之
	//// 備考       ：
	////　　　　　　：
	float MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field ) const;

	/////////////////// ////////////////////
	//// 用途       ：bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
	//// カテゴリ   ：関数
	//// 用途       ：距離を判定
	//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
	////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
	////　　　　　　：float        i_iBorder           //判定する値
	//// 戻値       ：true , false
	//// 担当者     ：本多寛之
	//// 備考       ：
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder );

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const { return m_vPos;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getSpeed() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：速度を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	float getSpeed() const { return m_fMovdSpeed;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：COIL_STATE getState() const 
	//// カテゴリ   ：ゲッター
	//// 用途       ：状態を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	COIL_STATE getState() const { return m_enumCoilState;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：void setState( COIL_STATE i_State )
	//// カテゴリ   ：セッター
	//// 用途       ：状態を変更
	//// 引数       ：COIL_STATE i_State
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setState( COIL_STATE i_State ){ m_enumCoilState = i_State; }	;

	/////////////////// ////////////////////
	//// 関数名     ：void setStartPos(float i_fPosY)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setStartPos(D3DXVECTOR3 i_vPos){
		m_vStartPos = i_vPos;
	}
};



/**************************************************************************
 class Factory_Player;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Player{
public:
/**************************************************************************
 Factory_Player(
	FactoryPacket* fpac //パケットデータ
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Player( FactoryPacket* fpac );
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Player();
};
}
//end of namespace wiz.
