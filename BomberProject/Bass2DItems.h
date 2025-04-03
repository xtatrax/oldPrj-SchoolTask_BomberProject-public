////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：BassI2Dtems.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包データと備考	：主にUI周りの基本となる2D的クラス
//					▼
//	namespace wiz;
//
//
#pragma once
#include "Object.h"
#include "TL-String.h"
namespace wiz {

namespace base2Dobject{
class PrimitiveSprite;
extern LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern class MouseUtilityCushion ;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class Cursor2D{
	
	static Point		m_vMousePoint	;
	static DWORD		m_tLastTime		;
	const static float	m_fLockTime		;
public:
    static bool			m_bMouseLB		;
    static bool			m_bMouseRB		;
    static bool			m_bMouseMB		;
    static bool			m_bMouseLBLock	;
    static bool			m_bMouseRBLock	;
    static bool			m_bMouseMBLock	;
public:
	friend class DxDevice;
	friend class MouseUtilityCushion ;
	friend static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static Point getPos();
	static bool getLButtonState(){return m_bMouseLB;};
	static bool getMButtonState(){return m_bMouseMB;};
	static bool getRButtonState(){return m_bMouseRB;};
	static bool pressLorRButton(){return m_bMouseRB || m_bMouseLB;};
	static bool clickLButtonWithLock();
	static bool clickMButtonWithLock();
	static bool clickRButtonWithLock();
	static bool clickLorRButtonWithLock(){return clickLButtonWithLock() || clickRButtonWithLock();};
	static bool isHitSprite(const PrimitiveSprite* i_TargetSprite);
};



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


//**************************************************************************
// class PrimitiveSprite ;
//
// 担当者  : 鴫原 徹
// 用途    : ２D環境のスプライトクラス
//**************************************************************************
class PrimitiveSprite {
	friend class Cursor2D;
protected:
	static LPD3DXSPRITE	m_pSprite			;	//	: 描画するためのスプライト
	static DWORD		m_dwMyInstanceQty	;	//	: このクラスのインスタンス数
	LPTATRATEXTURE		m_pTexture			;	//	: 描画するテクスチャ
	D3DXMATRIX			m_mMatrix			;	//	: マトリックス (派生クラスはここに座標データを入れる)
	D3DXVECTOR3			m_vOffsetPos		;	//	: テクスチャーの描画オフセット(基本は０値点);
	D3DXVECTOR3			m_vCenter			;	//	: テクスチャーの中心
	Rect*				m_pRect				;	//	: テクスチャーの描画領域
	Color				m_Color				;
	bool				m_bApplyAspect		;
	//仮
	PrimitiveSprite(){};
public:
	D3DXMATRIX getAspectMatrix() const{
		D3DXMATRIX mAll;
		if( m_bApplyAspect ){
			D3DXMATRIX mAspectRate;
			D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
			D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
			D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		}else{
			mAll = m_mMatrix;
		}
		return mAll ; 
	}
	void setMatrix( D3DXMATRIX i_mMatrix ){ m_mMatrix = i_mMatrix ; }
	D3DXMATRIX getMatrix(  ){ return m_mMatrix  ; }
/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,Rect* Rect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを作成
//// 引数       ：  const LPDIRECT3DDEVICE9     pD3DDevice       //  : Device
////            ：  const LPTATRATEXTURE        pTexture         //  : テクスチャー
////            ：  const Rect*                 pRect            //  : 描画したい範囲の矩形
////            ：  const D3DXVECTOR3&          vCenter          //  : 中心になる点の座標
////            ：  const D3DXVECTOR3&          vOffsetPos       //  : オフセット
////            ：  const Color                 color            //  : 色
////            ：  const bool                  bApplyAspect     //  : [※通常は必ずtrueにしてください!]自動で解像度変更に適応するかどうか
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：x0 y0の位置に簡単にものを描画したいときにべんり。
////            ：bApplyAspectは通常時は必ずtrueにしておいてください
////            ：
////
	PrimitiveSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPTATRATEXTURE		pTexture	,
		const Rect*					Rect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF,
		const bool					bApplyAspect= true
	);
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
////            ：  LPTATRATEXTURE pTexture,	//	: テクスチャーへのポインタ
////            ：  Rect*			Rect,			//	: テクスチャの描画範囲
////            ：  D3DXVECTOR3&	vCenter,		//	: 中心位置
////            ：  D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
////            ：  D3DCOLOR		color			//	: 色
////            ：  const bool      bApplyAspect    //  : [※通常は必ずtrueにしてください!]自動で解像度変更に適応するかどうか
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：とりあえず適当にUIを描画したい時とかにべんり。
////            ：bApplyAspectは通常時は必ずtrueにしておいてください
////            ：
////
	PrimitiveSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPTATRATEXTURE		pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const Rect*					Rect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF,
		const bool					bApplyAspect= true
	);

/////////////////// ////////////////////
//// 関数名     ：virtual ~PrimitiveSprite()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual ~PrimitiveSprite();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual void Draw(DrawPacket& i_DrawPacket);

	void	setAlpha( BYTE	alpha ){
		m_Color.byteColor.a	= alpha;
	}
	void	setColor( Color	color ){
		m_Color	= color;
	}

	void setCenter(D3DXVECTOR3 i_vCenter){
		m_vCenter = i_vCenter;
	}
};

//**************************************************************************
// class SpriteObject : public Object ,public PrimitiveSprite ;
//
// 担当者  : 鴫原 徹
// 用途    : スプライトをとりあえず描画するためのクラス
//           何の動作もしないとりあえずスプライトを描画したい時におすすめ
//**************************************************************************
class SpriteObject : public Object ,public PrimitiveSprite{
public:
/////////////////// ////////////////////
//// 関数名     ：SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPTATRATEXTURE pTexture     // 貼り付けたいテクスチャ
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  Rect* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	SpriteObject(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPTATRATEXTURE		pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const Rect*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF		,
		const wiz::OBJID			id			= OBJID_UI_SPRITE	,
		      bool					bApplyAspect= true
	);
/////////////////// ////////////////////
//// 関数名     ：~SpriteObject();
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual ~SpriteObject();
/////////////////// ////////////////////
//// 関数名     ：void Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	virtual void Draw(DrawPacket& i_DrawPacket);

	void setTexture(LPTATRATEXTURE	i_pTexture){
		m_pTexture = i_pTexture;
	}
};

namespace Avoidance{

//**************************************************************************
// 
//
// 担当者  : 鴫原 徹
// 用途    : 
//           
//**************************************************************************
class RenderTargetSprite : public PrimitiveSprite, public Object{
	LPDIRECT3DSURFACE9	m_sfRenderTarget	,	//	色データ
						m_sfRenderTargetZ	;	//	Ｚ値
	Size				m_ClientSize		;
public:
	RenderTargetSprite(BassPacket* i_BassPacket, UINT i_Width, UINT i_Height, wiz::OBJID id = OBJID_SYS_RENDERTARGET);
/////////////////// ////////////////////
//// 用途       ：virtual void TargetRender( LPDIRECT3DDEVICE9 pD3DDevice
////            ：      vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,               // オブジェクトの配列
////            ：  Command i_DrawPacket.pCommand                         // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
	virtual void TargetRender( RenderPacket& i_RenderPacket );
/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
	void Draw(DrawPacket& i_DrawPacket);
};
}
}//end of namespace base2Dobject.
using namespace base2Dobject;
}//end of namespace wiz.
