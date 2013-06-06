////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Coil.h
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
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"


const float			PLAYER_SPEED					= 0.08f;
const float			PLAYER_SPEED_SUPER				= 0.12f;
const float			PLAYER_BASSROT					= 90.0f;
const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
const float			COIL_SUPER_MODE_TIME			= 5.0f;
const float			COIL_ROTATION_ANGLE				= 15.0f;
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
const float			COIL_EXPANSION_VALUE_STICK		= 1.5f;

enum COIL_STATE{			//自機の状態
	COIL_STATE_START,		//スタート
	COIL_STATE_MOVE,		//移動
	COIL_STATE_STICK,		//吸着
	//COIL_STATE_SUPER,		//無敵
	COIL_STATE_DEAD,		//死亡
	COIL_STATE_CONTINUE,	//コンティニュー
	COIL_STATE_CLEAR,		//クリア
	COIL_STATE_STOP			//停止状態
};

namespace wiz{
namespace bomberobject{
extern class ProvisionalPlayer3D ;

/************************************************************************
class	StartField : public Cylinder

担当者	: 本多寛之
用途	: スタートの範囲
************************************************************************/
//class	StartField : public Cylinder{
//public:
//	StartField(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		float Radius1,
//		float Radius2,
//		float Lenght,
//		D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
//);
//    void	Draw(DrawPacket& i_DrawPacket) ;
//	void	Update(UpdatePacket& i_UpdatePacket);
//};
//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 鴫原 徹 本多寛之
// 用途    : コイル
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	DrawSphere*		m_pDSPH		;
	bool			m_bDebugInvincibleMode;
#endif
	Sphere*			m_pSphere		;
	D3DXMATRIX		m_Matrix		;
	D3DXVECTOR3		m_vPos			;
	D3DXQUATERNION	m_vRot			;
	D3DXVECTOR3		m_vScale		;
	D3DXVECTOR3		m_vOriginScale	;
	D3DXVECTOR3		m_vMove			;
	float			m_OBBRadius		;
	float			m_fMoveDir		;//角度
	float			m_fMovdSpeed	;//速度
	D3DXVECTOR3		m_vStartPos		;
	float			m_fTurnAngle	;
	bool			m_bLastMouseRB	;
	bool			m_bLastMouseLB	;
	bool			m_bReadyToStart ;
	bool			m_bReadyContinue;

	bool			m_bIsSuperMode	;//無敵状態のフラグ (無敵状態は他の状態と重なるのでCOIL_STATEに入れない)

	Sound*					m_pSound;
	ProvisionalPlayer3D*	m_pPlayer;

	MagneticumObject3D*		m_pMagneticumObject;

	Camera*					m_pCamera;
	
	COIL_STATE				m_enumCoilState;

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
	////		      :   float Radius1						//錐の直径1
	////		      :   float Radius2						//錐の直径2
	////		      :   float Radius3						//球の直径
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
		float Radius3,
		float Lenght,
		D3DXVECTOR3 &vScale,	
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Specular,
		D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_COIL
	);

	/////////////////// ////////////////////
	//// 関数名     ：~PlayerCoil()
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ： 鴫原 徹
	//// 備考       ：
	////            ：
	////
	~PlayerCoil();

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
	//// 関数名     ：void Update_StateStick()
	//// カテゴリ   ：
	//// 用途       ：STATE_STICK時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateStick();

	/////////////////// ////////////////////
	//// 関数名     ：void SuperMode()
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
	void SuperMode( UpdatePacket& i_UpdatePacket );

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
	//// 関数名     ：void Update_StateContinue()
	//// カテゴリ   ：
	//// 用途       ：STATE_CONTINUE時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update_StateContinue();

	/////////////////// ////////////////////
	//// 関数名     ：void Update_StateStop()
	//// カテゴリ   ：
	//// 用途       ：STATE_STOP時の動き
	//// 引数       ：
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void Update_StateStop();

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
	float MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, POLE i_bMagnetPole_Field ) const;

	/////////////////// ////////////////////
	//// 用途       ：bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
	//// カテゴリ   ：関数
	//// 用途       ：距離を判定
	//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
	////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
	////　　　　　　：float        i_iBorder           //判定する値
	////　　　　　　：bool　　　　IsPlayer　　　　　//相手がプレイヤーかどうか
	//// 戻値       ：true , false
	//// 担当者     ：本多寛之
	//// 備考       ：
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer );

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
	//// 関数名     ：D3DXVECTOR3 getScale() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：大きさを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getScale() const { return m_vScale;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 getDir() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：向きを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	float getDir() const { return m_fMoveDir;	}	;

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

	///////////////////////////////////////
	//// 関数名     ：D3DXVECTOR3 getStartPos()
	//// カテゴリ   ：ゲッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：座標データ
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getStartPos(){
		return	m_vStartPos;
	}

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
	//// 関数名     ：void setPos(D3DXVECTOR3 i_vPos)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	void setPos(D3DXVECTOR3 i_vPos){
		m_vPos = i_vPos;
	}

	/////////////////// ////////////////////
	//// 関数名     ：void setScale(D3DXVECTOR3 i_vScale)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	void setScale(D3DXVECTOR3 i_vScale){
		m_vScale = i_vScale;
	}

	/////////////////// ////////////////////
	//// 関数名     ：void setDir(float i_vDir)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	void setDir(float i_vDir){
		m_fMoveDir = i_vDir;
	}

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

	void	setReadyContinue( bool b ){
		m_bReadyContinue	= b;
	}
	/////////////////// ////////////////////
	//// 関数名     ：void getSuperMode()
	//// カテゴリ   ：ゲッター
	//// 用途       ：無敵状態を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	bool getSuperMode() const{
		return m_bIsSuperMode;
	}

	/////////////////// ////////////////////
	//// 関数名     ：void setStartPos(float i_fPosY)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setSuperMode(bool i_vFlg){
		m_bIsSuperMode = i_vFlg;
	}

};

/**************************************************************************
 class Factory_Coil;
 用途: メイン工場クラス
****************************************************************************/
class Factory_Coil{
public:
/**************************************************************************
 Factory_Coil(
	FactoryPacket* fpac //パケットデータ
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Coil( FactoryPacket* fpac , D3DXVECTOR3* vStartPos = NULL );
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Coil();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
