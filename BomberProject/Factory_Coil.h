////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Coil.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多寛之
//	編集			：曳地大洋
//					：佐藤涼
//	内包データと備考	：プレイヤーコイル関連
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class PlayerCoil : public MagnetField ;
//			class Factory_Coil ;
//	const	float			COIL_SPEED						= 0.08f;
//	const	float			COIL_SPEED_SUPER				= 0.12f;
//	const	float			COIL_ACCELERATION_VALUE			= 0.25f;
//	const	float			COIL_ACCELERATION_DECREASE		= 0.01f;
//	const	float			COIL_BASSROT					= 90.0f;
//	const	float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
//	const	float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
//	const	float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
//	const	float			COIL_SUPER_MODE_TIME			= 5.0f;
//	const	float			COIL_ROTATION_ANGLE				= 15.0f;
//	const	float			COIL_EXPANSION_VALUE_STICK		= 1.5f;
//	const	D3DXVECTOR3		COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
//	const	D3DXVECTOR3		COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//	const	D3DXVECTOR3		COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
//	const	D3DXVECTOR3		COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
//	enum	COIL_STATE{			//自機の状態
//		COIL_STATE_START,		//スタート
//		COIL_STATE_MOVE,		//移動
//		COIL_STATE_STICK,		//吸着
//		//COIL_STATE_SUPER,		//無敵
//		COIL_STATE_DEAD,		//死亡
//		COIL_STATE_CONTINUE,	//コンティニュー
//		COIL_STATE_CLEAR,		//クリア
//		COIL_STATE_STOP			//停止状態
//	};
//
#pragma once

//////////
//	: インクルード
#include "Factory_Magnetic.h"
#include "Factory_DeadEffect.h"
#include "Factory_Cursor.h"
#include "Factory_Player.h"
#include "Factory_Gage.h"
#include "Factory_MagnetField.h"

//#include "Factory_Description.h"
//	: インクルード
//////////


//////////
//	: グローバル定数
const float			COIL_SPEED						= 0.08f;
const float			COIL_SPEED_SUPER				= 0.15f;
//const float			COIL_ACCELERATION_VALUE			= 0.0f;
const float			COIL_ACCELERATION_VALUE			= 0.10f;
//const float			COIL_ACCELERATION_VALUE			= 0.25f;
const float			COIL_ACCELERATION_VALUE_MIMUS	= -0.15f;
const float			COIL_ACCELERATION_DECREASE		= 0.01f;
const float			COIL_BASSROT					= 90.0f;
const float			PLAYER_TURN_ANGLE_Lv1			= 1.0f;
const float			PLAYER_TURN_ANGLE_Lv2			= 2.0f;
const float			PLAYER_TURN_ANGLE_Lv3			= 2.5f;
const float			COIL_SUPER_MODE_TIME			= 4.0f;
//const float			COIL_SUPER_MODE_TIME			= 5.0f;
const float			COIL_ROTATION_ANGLE				= 15.35f;
const float			COIL_EXPANSION_VALUE_STICK		= 1.5f;
const D3DXVECTOR3	COIL_SUPER_MODE_FIELD_SCALE		= D3DXVECTOR3(10.0f,10.0f,0.0f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_START		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STOP		= D3DXVECTOR3(0.03f,0.03f,0.03f);
const D3DXVECTOR3	COIL_SCALE_ADD_VALUE_STICK		= D3DXVECTOR3(0.045f,0.045f,0.045f);
const int			MAX_DIGHT_SCORE					= 1000000;
const int			LIMIT_TIME						= 60;

enum COIL_STATE{			//自機の状態
	COIL_STATE_START,		//スタート
	COIL_STATE_MOVE,		//移動
	COIL_STATE_STICK,		//吸着
	COIL_STATE_DEAD,		//死亡
	COIL_STATE_CONTINUE,	//コンティニュー
	COIL_STATE_CLEAR,		//クリア
	COIL_STATE_STOP			//停止状態
};

enum COIL_STATE_SUPER{
	COIL_STATE_SUPER_CHARGE = 10,
	COIL_STATE_SUPER_READY,
	COIL_STATE_SUPER_CHANGING,
	COIL_STATE_SUPER_MOVE
};
//	: グローバル定数
//////////

namespace wiz{
namespace bomberobject{
extern class ProvisionalPlayer3D ;
extern class StartSprite;
extern class SuperGage;
extern class ModeChangeChar;
extern class TimeScore;
extern class ContinueBehavior;
//**************************************************************************//
// class PlayerCoil : public MagneticumObject ;
//
// 担当者  : 鴫原 徹
// 引継ぎ  : 本多寛之
// 編集    : 曳地 大洋
//         : 佐藤涼
// 用途    : ユーザーが誘導する対象になる物
//**************************************************************************//
class PlayerCoil : public Cylinder ,public MagneticObject{
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
	int				m_iDeadCount		;	//	: 死亡回数
	int				m_iMaxPosY			;
	int				m_iScratchTime		;
	int				m_fRecordTime		;
	int				m_iChangeColorInterval;
	float			m_OBBRadius			;	//	: 多分SphereRadius
	float			m_fMoveDir			;	//	: 移動角度
	float			m_fMovdSpeed		;	//	: 移動速度
	float			m_fAcceleration		;	//	: 加速
	float			m_fTurnAngle		;	//	: 回転角度
	float			m_fSuperTimeCount	;
	float			m_fSuperFieldRotZ	;
	float			m_fSuperTimeAccumulator;
	float			m_fLineMovingDistance;
	bool			m_bLastMouseRB		;	//	: マウスのRボタンが押されているか
	bool			m_bLastMouseLB		;	//	: マウスのLボタンが押されているか
	bool			m_bReadyToStart		;	//	: 発射する準備が出来たか
	bool			m_bReadyContinue	;	//	: コンティニューする準備が出来たか
	bool			m_bRestart			;
	bool			m_bModeChangeChar	;
	bool			m_bReDrawing_ChangeChar	;
	bool			m_bStandby			;
	bool			m_bIsFirstDeadLoop	;
	bool			m_bExpanding		;
	bool			m_bIsColorChange	;
	bool			m_bSuperSound		;




	MouseCursor*			m_pCursor					;	//	: カーソルオブジェクトへのポインタ
	Camera*					m_pCamera					;	//	: Cameraへのポインタ
	SuperGage*				m_pSuperGage				;
	Box*					m_pSuperField				;	//	: 無敵時のフィールド
	StartSprite*			m_pReStart					;	//	: 
	ProvisionalPlayer3D*	m_pPlayer					;	//	: ユーザ設置磁界へのポインタ
	StaticMagnetField*		m_pMagneticumObject			;	//	: 初期配置磁界へのポインタ
	DeadEffect*				m_pDeadEffect				;	//	: 死亡時の爆散エフェクトのポインタ
	ModeChangeChar*			m_pModeChangeChar			;	//	: 
	TimeScore*				m_pTime;
	ContinueBehavior*		m_pContinueBehavior			;
	
	Line3D*					m_pLine1					;
	Line3D*					m_pLine2					;
	Line3D*					m_pLine3					;
	Line3D*					m_pLine4					;
	
	COIL_STATE				m_enumCoilState				;	//	: 自分の状態
	COIL_STATE_SUPER		m_enumCoilStateSuper		;	//	: 無敵状態

public:
	/////////////////// ////////////////////
	//// 関数名     ：PlayerCoil::PlayerCoil(
	////            ：    LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
	////            ：    float Radius1,float Radius2,float Lenght,
	////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////            ：    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////            ：    wiz::OBJID id = OBJID_3D_PLAYER)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：  LPDIRECT3DDEVICE9   pD3DDevice   // デバイス
	////            ：  LPTATRATEXTURE  pTexture     // テクスチャ	
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
		LPDIRECT3DDEVICE9	pD3DDevice		,
		float				Radius1			,
		float				Radius2			,
		float				Radius3			,
		float				Lenght			,
		D3DXVECTOR3&		vScale			,
		D3DXVECTOR3&		vRot			,
		D3DXVECTOR3&		vPos			,
		D3DCOLORVALUE&		Diffuse			,
		D3DCOLORVALUE&		Specular		,
		D3DCOLORVALUE&		Ambient			,
		LPTATRATEXTURE		pSuperFieldTex	,
		LPTATRATEXTURE		pModeChangeTex	,
		LPTATRATEXTURE		pDeadTex		,
		wiz::OBJID id						= OBJID_3D_COIL
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
	void Update_StateStart(UpdatePacket& i_UpdatePacket);

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
	void Update_StateMove(UpdatePacket& i_UpdatePacket);

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
	void Update_StateStick(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// 関数名     ：void SPlayerCoil::uperMode()
	//// カテゴリ   ：
	//// 用途       ：STATE_SUPER時の動き
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////			  ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////			  ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////			  ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
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
	void Update_StateDead(UpdatePacket& i_UpdatePacket);

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
	void Update_StateContinue(UpdatePacket& i_UpdatePacket);

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
	void Update_StateStop(UpdatePacket& i_UpdatePacket);

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
	void MagneticDecision( D3DXVECTOR3& i_vMagnetPos, POLE i_bMagnetPole_Field ) ;

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
	//// 関数名     ：Update_Line()
	//// カテゴリ   ：関数
	//// 用途       ：Lineの更新
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void Update_Line();

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

	int	getMaxPos(){
		return m_iMaxPosY;
	}

	//****************************************
	//スクラッチポイントのゲッター、セッター
	//描画用スクラッチ
	int	getScratchTime(){
		return	m_iScratchTime;
	}

	void	ScratchTime_Update(){
		if( m_iScratchTime < MAX_DIGHT_SCORE )
			++m_iScratchTime;
	}

	//結果用スクラッチ
	void	setRecordTime(){
		m_fRecordTime	= m_iScratchTime;
	}

	int		getRecordTime(){
		return	m_fRecordTime;
	}
	//*****************************************

	void	setMaxPos(int iMaxPosY){
		m_iMaxPosY	= iMaxPosY;
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
	void setState( COIL_STATE i_State ){
		m_enumCoilState = i_State; 
		if( m_enumCoilState == COIL_STATE_DEAD ) m_bIsFirstDeadLoop = true;
	};

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

	void	setReadyToStart( bool b ){
		m_bReadyToStart		= b;
	}
	/////////////////// ////////////////////
	//// 関数名     ：COIL_STATE_SUPER getSuperMode() const
	//// カテゴリ   ：ゲッター
	//// 用途       ：無敵状態を獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	COIL_STATE_SUPER getSuperMode() const{
#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION ) 
		if(m_bDebugInvincibleMode) return COIL_STATE_SUPER_MOVE ;
#endif
		return m_enumCoilStateSuper  ;
	}

	/////////////////// ////////////////////
	//// 関数名     ：void setSuperMode(bool i_vFlg)
	//// カテゴリ   ：セッター
	//// 用途       ：
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	void setSuperMode(COIL_STATE_SUPER i_State){
		m_enumCoilStateSuper = i_State;
	}

	/////////////////// ////////////////////
	//// 関数名     ：bool getReadyToSuper()
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_bReadyToSuperを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	bool getReadyToStart() const{
		return m_bReadyToStart;
	}

	bool	getStandby() const{
		return	m_bStandby;
	}
	/////////////////// ////////////////////
	//// 関数名     ：LPTATRATEXTURE getDeadText()
	//// カテゴリ   ：ゲッター
	//// 用途       ：m_pDeadTexを獲得
	//// 引数       ：なし
	//// 戻値       ：なし
	//// 担当       ：本多寛之
	//// 備考       ：
	////            ：
	//LPTATRATEXTURE getDeadText() const{
	//	return m_pDeadTex;
	//}

	/////////////////// ////////////////////
	//// 関数名     ：void PlayerCoil::getDeadCount()
	//// カテゴリ   ：ゲッター
	//// 用途       ：死亡回数の獲得
	//// 引数       ：なし
	//// 戻値       ：死亡回数
	//// 担当       ：佐藤涼
	//// 備考       ：
	////            ：
	int	getDeadCount(){
		return	m_iDeadCount;
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
	Factory_Coil( FactoryPacket* fpac, DWORD dwResumptionCheckPoint , D3DXVECTOR3* vStartPos = NULL );
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
