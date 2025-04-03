////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
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
#include "Factory_Sound.h"

namespace wiz{

namespace menuobject{


class ButtonSprite : public SpriteObject{
protected:
	Button			m_ButtonState			;
	Color			m_SelectColor			;
	Color			m_UnSelectColor			;
	const char*		m_sSelectSound			;
	const char*		m_sDecisionSound		;
	float			m_fWaitTime				;
	float			m_fTimeAccumulator		;
	bool			m_bIsSelectWait			;
	bool			m_bIsPlaySelectSound	;
	bool			m_bKillAfterIssuing		;
public:
	ButtonSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice			,
		const LPTATRATEXTURE	pTexture			,
		const D3DXVECTOR3			vScalse				,
		const D3DXVECTOR3			vRot				,
		const D3DXVECTOR3			vPos				,
		const Rect*					pRect				,
		const D3DXVECTOR3			vCenter				,
		const D3DXVECTOR3			vOffset				,
		const Color					dwSelectColor		,
		const Color					dwUnSelectColor		,
		const char*					sSelectSound		,
		const char*					sDecisionSound		,
		const float					fWaitTime			,
		const Command				Com					,
		const wiz::OBJID			id					= OBJID_UI_SPRITEBUTTON	,
		const bool					bKillAfterIssuing	= false					,
		const bool					bApplyAspect		= true
	);
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
//// 戻値       ：なし
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
//// 戻値       ：なし
//// 備考       ：
////            ：
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

	Button* getButtonP(){ return &m_ButtonState;}
	void setWaitTime( float fTime ){
		m_fWaitTime = fTime ;
	}

} ;
}//end of namespace menuobject.
using namespace menuobject ;
}//end of namespace wiz.
