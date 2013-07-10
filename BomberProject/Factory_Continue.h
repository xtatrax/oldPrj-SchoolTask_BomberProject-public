////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Continue.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤 涼
//	引き継ぎ		：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：コンテニュー
//					▼
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//
#pragma once

//////////
//	: インクルード
#include "Factory_Coil.h"
#include "Factory_Score.h"
//	: インクルード
//////////

namespace wiz{
namespace bomberobject{
enum CONTINUEBEHAVIORPHASE{
	CONTINUEBEHAVIORPHASE_WAIT				,
	CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE	,
	CONTINUEBEHAVIORPHASE_CONTINUESELECTION	,
	CONTINUEBEHAVIORPHASE_CHECKSELECTION		,

};
///*************************************************************************
//class ContinueButton : public ButtonSprite
//
//担当者：鴫原 徹
//用途　：コンテニュー時のボタン
//*************************************************************************/
class ContinueButton : public ButtonSprite{
	Command			m_IssueCommand	;
	bool			m_bIsOperating	;
public:
	ContinueButton(
		const LPDIRECT3DDEVICE9		pD3DDevice			,
		const LPTATRATEXTURE	pTexture			,
		const D3DXVECTOR3			vScalse				,
		const D3DXVECTOR3			vPos				,
		const Rect*					pRect				,
		const float					fWaitTime			,
		const Command				Com					,
		const wiz::OBJID			id						
	);
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
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ) ;
	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	virtual void Draw( DrawPacket& i_DrawPacket );
	void getIssueCommand(Command& ret){
		if( m_IssueCommand.m_Command != GM_WITHOUT ){
			ret = m_IssueCommand ;
		}
	}
	void OperationStart(){
		m_bIsOperating = true ;
	}
	void OperationEnd(){
		m_bIsOperating = false ;
	}
};
///*************************************************************************
//class ContinueButton : public ButtonSprite
//
//担当者：佐藤 涼
//引継ぎ：鴫原 徹
//用途　：コンティニュー画面の動作を定義しています
//*************************************************************************/
class ContinueBehavior : public Behavior{
	LPTATRATEXTURE			m_pPTContinue		;
	LPTATRATEXTURE			m_pPTReally			;
	SpriteObject*			m_pPageTitle		;
	SpriteObject*			m_pDeadMessage		;
	ContinueButton*			m_pYesButton		;
	ContinueButton*			m_pNoButton			;
	Score*					m_pDeadScore		;
	SpriteObject*			m_pDeadCountChar	;
	PlayerCoil*				m_pCoil				;
	TimeScore*				m_pTime				;
	float					m_fDeadMessageTimeAccumulator	;
	float					m_fFadeOutTimeAccumulator		;
	const float				m_fMessageTime		;
	const float				m_fFadeOutTime		;
	float					m_fDeadMessageAlpha	;
	CONTINUEBEHAVIORPHASE	m_NowBehaviorFaze	;
public:
	ContinueBehavior( FactoryPacket& i_BassPacket);
	~ContinueBehavior();

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
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ) ;
	/////////////////// ////////////////////
	//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：仮想関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	virtual void Draw( DrawPacket& i_DrawPacket );

	void OperationStart(){
		m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE;
		m_fDeadMessageAlpha = 255.0f ;
		m_pDeadMessage->setAlpha(0xFF);
		m_fDeadMessageTimeAccumulator = 0.0f ;
		m_fFadeOutTimeAccumulator = 0.0f ;
		m_pDeadScore->setScore(m_pCoil->getDeadCount()+1);
		m_pDeadScore->setAlpha(0xFF);
		m_pDeadCountChar->setAlpha(0xFF);

	}
	void OperationStop(){
		m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_WAIT;
	}
};


///*************************************************************************
//class Reply  public SpriteObject
//
//担当者：佐藤涼
//用途　：コンテニュー時のボタン
//*************************************************************************/
//class	Reply	: public SpriteObject{
//	D3DXVECTOR3		m_vPos			;
//	bool			m_bMark			;
//	bool			m_bPushRock		;
//	bool			m_bWhichDraw	;
//	int				m_iTime			;
//	bool			m_bPush			;
//	bool			m_bSelect		;
//	DWORD			m_dNext			;
//	PlayerCoil*		m_pCoil			;
//
//public:
//	Reply(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const bool					mark		,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vRot		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const D3DXVECTOR3&			vCenter		,
//		const D3DXVECTOR3&			vOffsetPos	,
//		const Color					color		= 0xFFFFFFFF
//	);
//	~Reply();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//
//	bool	getWhichDraw(){
//		return	m_bWhichDraw;
//	}
//	void	setWhichDraw(bool b){
//		m_bWhichDraw	= b;
//	}
//};
//
///*************************************************************************
//class Continue  public SpriteObject
//
//担当者：佐藤涼
//用途　：コンテニュー時のボタン
//*************************************************************************/
//class	Continue	: public SpriteObject{
//	D3DXVECTOR3		m_vPos;
//	bool			m_bMark;
//	bool			m_bPushRock;
//	bool			m_bWhichDraw;
//
//	int				m_iTime			;
//	bool			m_bPush			;
//	bool			m_bSelect		;
//	DWORD			m_dNext			;
//	bool			m_bDrawing		;
//
//
//	PlayerCoil*		m_pCoil;
//	Reply*			m_pReply_Yes;
//	Reply*			m_pReply_No;
//	SpriteObject*	m_pRethinking;
//	SpriteObject*	m_pContinueChar				;	//	: コンテニューロゴのポインタ
//	TimeScore*		m_pTime;
//
//	LPTATRATEXTURE	m_pRethinkingTex;	//Really?
//	LPTATRATEXTURE	m_pAnswerTex	;	//Yes : No
//	LPTATRATEXTURE	m_pContinueTex	;	//Yes : No
//public:
//	Continue(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const LPTATRATEXTURE	pTexture_Rethinking	,
//		const LPTATRATEXTURE	pTexture_Answer		,
//		const bool					mark		,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const wiz::OBJID			id			,
//		const Color					color		= 0xFFFFFFFF
//	);
//	~Continue();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//
//	bool	getWhichDraw(){
//		return	m_bWhichDraw;
//	}
//	void	setDrawing( bool i_bDrawing ){
//		m_bDrawing	= i_bDrawing;
//	}
//};
//
///*************************************************************************
//class Dead  public SpriteObject
//
//担当者：佐藤涼
//用途　：死亡時に出す文字
//*************************************************************************/
//class	Dead	: public SpriteObject{
//	float			m_fTime;
//	int				m_iDeadCount;
//	bool			m_bDrawing;
//	Score*			m_pDeadScore;
//	SpriteObject*	m_pDeadCountChar;
//	Continue*		m_pSelect_Yes;
//	Continue*		m_pSelect_No;
//public:
//	Dead(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const LPTATRATEXTURE	pDeadCountTex	,
//		const LPTATRATEXTURE	pCountCharTex	,
//		const int					iDeadCount	,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const Color					color		= 0xFFFFFFFF,
//		const wiz::OBJID			id			= OBJID_UI_DEAD_CHAR
//
//	);
//	~Dead();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//	BYTE	getAlpha(){
//		return m_Color.byteColor.a;
//	}
//	void	setDrawing( bool i_bDraw ){
//		m_bDrawing	= i_bDraw;
//	}
//
//	void	setCount( int i_iCount ){
//		m_iDeadCount	= i_iCount;
//	}
//};

/**************************************************************************
class Factory_Continue;

用途　：メイン工場クラス
担当者：佐藤涼
****************************************************************************/
class Factory_Continue{
public:
/**************************************************************************
 Factory_Continue(FactoryPacket* fpac);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_Continue(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Factory_Continue();
};

}
}