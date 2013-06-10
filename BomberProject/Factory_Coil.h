////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Coil.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多寛之
//	編集			：曳地大洋
//					：佐藤涼
//	内包ﾃﾞｰﾀと備考	：プレイヤーコイル関連
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagneticumObject3D ;
//			class Factory_Coil ;
//		const float			COIL_SPEED						= 0.08f;
//		const float			COIL_SPEED_SUPER				= 0.12f;
//		const float			COIL_ACCELERATION_VALUE			= 0.25f;
//		const float			COIL_ACCELERATION_DECREASE		= 0.01f;
//		const float			COIL_BASSROT					= 90.0f;
//		const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
//		const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
//		const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
//		const float			COIL_SUPER_MODE_TIME			= 5.0f;
//		const D3DXVECTOR3	COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
//		const float			COIL_ROTATION_ANGLE				= 15.0f;
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//		const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
//		const float			COIL_EXPANSION_VALUE_STICK		= 1.5f;
//		enum COIL_STATE{			//自機の状態
//			COIL_STATE_START,		//スタート
//			COIL_STATE_MOVE,		//移動
//			COIL_STATE_STICK,		//吸着
//			//COIL_STATE_SUPER,		//無敵
//			COIL_STATE_DEAD,		//死亡
//			COIL_STATE_CONTINUE,	//コンティニュー
//			COIL_STATE_CLEAR,		//クリア
//			COIL_STATE_STOP			//停止状態
//		};
//
#pragma once

#include "StdAfx.h"
#include "Factory_Magnetic.h"
#include "Factory_Gage.h"
#include "Factory_Sound.h"
#include "Factory_DeadEffect.h"
#include "Factory_Continue.h"


const float			COIL_SPEED						= 0.08f;
const float			COIL_SPEED_SUPER				= 0.12f;
const float			COIL_ACCELERATION_VALUE			= 0.25f;
const float			COIL_ACCELERATION_DECREASE		= 0.01f;
const float			COIL_BASSROT					= 90.0f;
const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
const float			COIL_SUPER_MODE_TIME			= 5.0f;
const D3DXVECTOR3	COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
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
extern class Continue ;
extern class Dead ;

//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 引継ぎ  : 本多寛之
// 編集    : 曳地 大洋
//         : 佐藤涼
// 用途    : ユーザーが誘導する対象になる物
//**************************************************************************//
class PlayerCoil : public MagneticumObject3D{
	friend MagneticumObject3D;
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
	//	: デバッグ用のデータ
	DrawSphere*		m_pDSPH		;				//	: 球領界描画クラスのポインタ
	bool			m_bDebugInvincibleMode;		//	: デバッグ用無敵フラグ
#endif
	Sphere*			m_pSphere			;	//	: コア
	D3DXMATRIX		m_Matrix			;	//	: 行列
	D3DXVECTOR3		m_vPos				;	//	: 座標
	D3DXQUATERNION	m_vRot				;	//	: 回転
	D3DXVECTOR3		m_vScale			;	//	: 伸縮
	D3DXVECTOR3		m_vOriginScale		;	//	: 元の大きさ
	D3DXVECTOR3		m_vMove				;	//	: 移動距離
	D3DXVECTOR3		m_vStartPos			;	//	: 再スタート位置
	float			m_OBBRadius			;	//	: 多分SphereRadius
	float			m_fMoveDir			;	//	: 移動角度
	float			m_fMovdSpeed		;	//	: 移動速度
	float			m_fAcceleration		;	//	: 加速
	float			m_fTurnAngle		;	//	: 回転角度?
	bool			m_bLastMouseRB		;	//	: マウスのRボタンが押されているか
	bool			m_bLastMouseLB		;	//	: マウスのLボタンが押されているか
	bool			m_bReadyToStart		;	//	: 
	bool			m_bReadyContinue	;	//	:
	bool			m_bIsSuperMode		;	//	: 無敵状態のフラグ (無敵状態は他の状態と重なるのでCOIL_STATEに入れない)
	bool			m_bDrawContinue		;	//	:

	Sound*					m_pSound					;	//	: 音声データへのポインタ
	Camera*					m_pCamera					;	//	: Cameraへのポインタ
	Box*					m_pSuperField				;	//	: ?
	Continue*				m_pSelect					;	//	: 
	Continue*				m_pSelect2					;	//	: 
	Dead*					m_pDeadChar					;	//	: 
	ProvisionalPlayer3D*	m_pPlayer					;	//	: ユーザ設置磁界へのポインタ
	MagneticumObject3D*		m_pMagneticumObject			;	//	: 初期配置磁界へのポインタ
	DeadEffect*				m_pDeadEffect[PARTICLS_NUM]	;
	COIL_STATE				m_enumCoilState				;

	LPDIRECT3DTEXTURE9	m_pDeadTex		;	//爆散エフェクトの画像
	LPDIRECT3DTEXTURE9	m_pContinueTex	;
	LPDIRECT3DTEXTURE9	m_pTitleTex		;
	LPDIRECT3DTEXTURE9	m_pDeadCharTex	;
public:
	/////////////////// ////////////////////
	//// 関数名     ：PlayerCoil::PlayerCoil(
	////            ：    LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
	////            ：    float Radius1,float Radius2,float Lenght,
	////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////            ：    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////            ：    wiz::OBJID id = OBJID_3D_PLAYER)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9   pD3DDevice   // デバイス
	////            ：  LPDIRECT3DTEXTURE9  pTexture     // テクスチャ	
	////            ：  float               Radius1      // 錐の直径1
	////            ：  float               Radius2      // 錐の直径2
	////            ：  float               Radius3      // 球の直径
	////            ：  flaot               Lenght       // 高さ
	////            ：  D3DXVECTOR3&        vScale       // 伸縮
	////            ：  D3DXVECTOR3&        vRot         // 回転角
	////            ：  D3DXVECTOR3&        vPos         // 位置
	////            ：  D3DCOLORVALUE&      Diffuse      // ディフューズ色
	////            ：  D3DCOLORVALUE&      Specular     // スペキュラ色
	////            ：  D3DCOLORVALUE&      Ambient      // アンビエント色
	////            ：  wiz::OBJID          id = OBJID_3D_COIL //ID
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 引継ぎ     ：本多寛之
	//// 備考       ：
	////            ：
	////
	PlayerCoil(
		LPDIRECT3DDEVICE9	pD3DDevice			,
		LPDIRECT3DTEXTURE9	pTexture			,
		LPDIRECT3DTEXTURE9	pTexture_Super		,
		LPDIRECT3DTEXTURE9	pTexture_Dead		,
		LPDIRECT3DTEXTURE9	pTexture_Continue	,
		LPDIRECT3DTEXTURE9	pTexture_Title		,
		LPDIRECT3DTEXTURE9	pTexture_DeadChar	,
		float				Radius1				,
		float				Radius2				,
		float				Radius3				,
		float				Lenght				,
		D3DXVECTOR3&		vScale				,	
		D3DXVECTOR3&		vRot				,
		D3DXVECTOR3&		vPos				,
		D3DCOLORVALUE&		Diffuse				,
		D3DCOLORVALUE&		Specular			,
		D3DCOLORVALUE&		Ambient				,
		wiz::OBJID			id					= OBJID_3D_COIL
	);

	/////////////////// ////////////////////
	//// 関数名     ：PlayerCoil::~PlayerCoil()
	//// カテゴリ   ：デストラクタ
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ： 鴫原 徹
	//// 備考       ：
	////            ：
	////
	~PlayerCoil();

	/////////////////// ////////////////////
	//// 用途       ：bool PlayerCoil::HitTestWall( OBB Obb )
	//// カテゴリ   ：メンバ関数
	//// 用途       ：壁との衝突判定
	//// 引数       ：  OBB Obb           //  : 検査対象のOBB
	//// 戻値       ：衝突していればtrue
	//// 担当者     ：曳地 大洋
	//// 備考       ：
	bool HitTestWall( OBB );

	/////////////////// ////////////////////
	//// 関数名     ：void PlayerCoil::Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：  UpdatePacket& i_UpdatePacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 引継ぎ     ：本多寛之
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
	//// カテゴリ   ：
	//// 用途       ：
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
	////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
	////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
	////            ：  └       Command            pCommand        // コマンド
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	////
	void	CreateEffect( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// 関数名     ：void PlayerCoil::Update_StateStart()
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
	//// 関数名     ：void PlayerCoil::Update_StateMove()
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
	//// 関数名     ：void PlayerCoil::Update_StateStick()
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
	//// 関数名     ：void SPlayerCoil::uperMode()
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
	//// 関数名     ：void PlayerCoil::Update_StateDead()
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
	//// 関数名     ：void PlayerCoil::Update_StateContinue()
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
	//// 関数名     ：void PlayerCoil::Update_StateStop()
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
	//// 用途       ：virtual void PlayerCoil::Draw( DrawPacket& i_DrawPacket )
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
	//// 関数名     ：float PlayerCoil::MagneticDecision( float i_fCoilDir, D3DXVECTOR3& i_vMagnetPos, bool i_bMagnetPole_Field )
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
	//// 用途       ：bool PlayerCoil::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder, bool IsPlayer )
	//// カテゴリ   ：関数
	//// 用途       ：距離を判定
	//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
	////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
	////　　　　　　：float        i_iBorder           //判定する値
	////　　　　　　：bool　　　　IsPlayer　　　　　//相手がプレイヤーかどうか
	//// 戻値       ：true , false
	//// 担当者     ：本多寛之
	//// 備考       ：
	bool CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, float i_iBorder, bool IsPlayer );

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 gPlayerCoil::etPos() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：中心座標を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：鴫原 徹
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getPos() const { return m_vPos;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 PlayerCoil::getScale() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：大きさを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	D3DXVECTOR3 getScale() const { return m_vScale;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 PlayerCoil::getDir() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：向きを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	float getDir() const { return m_fMoveDir;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：D3DXVECTOR3 gPlayerCoil::etSpeed() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：速度を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	float getSpeed() const { return m_fMovdSpeed;	}	;

	/////////////////// ////////////////////
	//// 関数名     ：COIL_STATE PlayerCoil::getState() const 
	//// カテゴリ   ：ゲッター
	//// 用途       ：状態を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	COIL_STATE getState() const { return m_enumCoilState;	}	;

	///////////////////////////////////////
	//// 関数名     ：D3DXVECTOR3 PlayerCoil::getStartPos()
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
	//// 関数名     ：void PlayerCoil::setState( COIL_STATE i_State )
	//// カテゴリ   ：セッター
	//// 用途       ：状態を変更
	//// 引数       ：COIL_STATE i_State
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setState( COIL_STATE i_State ){ m_enumCoilState = i_State; }	;

	/////////////////// ////////////////////
	//// 関数名     ：void PlayerCoil::setPos(D3DXVECTOR3 i_vPos)
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
	//// 関数名     ：void PlayerCoil::setScale(D3DXVECTOR3 i_vScale)
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
	//// 関数名     ：void PlayerCoil::setDir(float i_vDir)
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
	//// 関数名     ：void PlayerCoil::setStartPos(float i_fPosY)
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
	//// 関数名     ：void PlayerCoil::getSuperMode()
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
	//// 関数名     ：void PlayerCoil::setStartPos(float i_fPosY)
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
