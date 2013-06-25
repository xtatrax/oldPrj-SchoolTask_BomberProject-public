////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Continue.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
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


class ContinueBehavior : public Behavior{
	PlayerCoil*			m_pCoil			;
	ButtonSprite		m_YesButton		;
	ButtonSprite		m_NoButton		;
	SpriteObject		m_PageName		;
	LPDIRECT3DTEXTURE9	m_pDeadTex		;
	LPDIRECT3DTEXTURE9	m_pContinueTex	;
	LPDIRECT3DTEXTURE9	m_pCheckTex		;
	bool				m_bIsCheck		;
public:
	ContinueBehavior(BassPacket& i_BassPacket);
	/////////////////// ////////////////////
	//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトをディスプレイに表示する
	//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
	////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
	////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
	////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
	////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹

	//// 備考       ：
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
	//// カテゴリ   ：関数
	//// 用途       ：オブジェクトを更新
	//// 引数       ：
	//// 戻値       ：無し
	//// 担当者     ：鴫原 徹
	//// 備考       ：
	////            ：
	////
	void Update( UpdatePacket& i_UpdatePacket );

};










/*************************************************************************
class Reply  public SpriteObject

担当者：佐藤涼
用途　：コンテニュー時のボタン
*************************************************************************/
class	Reply	: public SpriteObject{
	D3DXVECTOR3		m_vPos			;
	bool			m_bMark			;
	bool			m_bPushRock		;
	bool			m_bWhichDraw	;
	int				m_iTime			;
	bool			m_bPush			;
	bool			m_bSelect		;
	DWORD			m_dNext			;
	PlayerCoil*		m_pCoil			;

public:
	Reply(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Reply();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
	void	setWhichDraw(bool b){
		m_bWhichDraw	= b;
	}
};

/*************************************************************************
class Dead  public SpriteObject

担当者：佐藤涼
用途　：死亡時に出す文字
*************************************************************************/
class	Dead	: public SpriteObject{
	int				m_iTime;
	Score*			m_pDeadScore;
	SpriteObject*	m_pDeadCountChar;
public:
	Dead(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pDeadCountTex	,
		const LPDIRECT3DTEXTURE9	pCountCharTex	,
		const int					iDeadCount	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Dead();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	BYTE	getAlpha(){
		return m_Color.byteColor.a;
	}
};

/*************************************************************************
class Continue  public SpriteObject

担当者：佐藤涼
用途　：コンテニュー時のボタン
*************************************************************************/
class	Continue	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	bool			m_bPushRock;
	bool			m_bWhichDraw;

	int				m_iTime			;
	bool			m_bPush			;
	bool			m_bSelect		;
	DWORD			m_dNext			;


	PlayerCoil*		m_pCoil;
	Reply*			m_pReply_Yes;
	Reply*			m_pReply_No;
	SpriteObject*	m_pRethinking;
	SpriteObject*	m_pContinueChar				;	//	: コンテニューロゴのポインタ
	TimeScore*		m_pTime;

	LPDIRECT3DTEXTURE9	m_pRethinkingTex;	//Really?
	LPDIRECT3DTEXTURE9	m_pAnswerTex	;	//Yes : No
	LPDIRECT3DTEXTURE9	m_pContinueTex	;	//Yes : No
public:
	Continue(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pTexture_Rethinking	,
		const LPDIRECT3DTEXTURE9	pTexture_Answer		,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Continue();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
};

}
}