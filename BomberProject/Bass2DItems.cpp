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
//
#include "StdAfx.h"
#include "Bass2DItems.h"
namespace wiz {

namespace base2Dobject{

/**************************************************************************
 class Cursor2D 定義部
****************************************************************************/
Point		Cursor2D::m_vMousePoint      ;
bool		Cursor2D::m_bMouseLB = false ;
bool		Cursor2D::m_bMouseMB = false ;
bool		Cursor2D::m_bMouseRB = false ;
bool		Cursor2D::m_bMouseLBLock = false ;
bool		Cursor2D::m_bMouseMBLock = false ;
bool		Cursor2D::m_bMouseRBLock = false ;
DWORD		Cursor2D::m_tLastTime	= timeGetTime() ;
const float	Cursor2D::m_fLockTime	= 0.3f ;

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Point Cursor2D::getPos(){
	GetCursorPos( &m_vMousePoint ) ;
	ScreenToClient( wiz::DxDevice::m_hWnd , &m_vMousePoint) ;
	return m_vMousePoint ;
}
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Cursor2D::clickLButtonWithLock()
{

	bool ret = false ;
	//	: 前回押されていた 今回はなされた
	if( m_bMouseLBLock && !m_bMouseLB ){
		//	: 前回押された時より0.3秒経過していなかったら無効
		DWORD now = timeGetTime();
		float fTime = (float)TLIB::Tempus::TwoDwTime2ElapsedTime(m_tLastTime,now);
		if( fTime > m_fLockTime ){
			m_tLastTime = TLIB::Tempus::TimeGetTime(); 
			ret = true ;
		}
	}

	//	: 押されている
	if( m_bMouseLB ){
		//	: 押されていた
		m_bMouseLBLock = true ;
	}else{
		//	: 押されていなかった
		m_bMouseLBLock = false ;
	}

	return ret;
};
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Cursor2D::clickMButtonWithLock()
{
	bool ret = false ;
	//	: 前回押されていた 今回はなされた
	if( m_bMouseMBLock && !m_bMouseMB ){
		//	: 前回押された時より0.3秒経過していなかったら無効
		DWORD now = timeGetTime();
		float fTime = (float)TLIB::Tempus::TwoDwTime2ElapsedTime(m_tLastTime,now);
		if( fTime > m_fLockTime ){
			m_tLastTime = TLIB::Tempus::TimeGetTime(); 
			ret = true ;
		}
	}

	//	: 押されている
	if( m_bMouseMB ){
		//	: 押されていた
		m_bMouseMBLock = true ;
	}else{
		//	: 押されていなかった
		m_bMouseMBLock = false ;
	}

	return ret;
};
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Cursor2D::clickRButtonWithLock()
{
	bool ret = false ;
	//	: 前回押されていた 今回はなされた
	if( m_bMouseRBLock && !m_bMouseRB ){
		//	: 前回押された時より0.3秒経過していなかったら無効
		DWORD now = timeGetTime();
		float fTime = (float)TLIB::Tempus::TwoDwTime2ElapsedTime(m_tLastTime,now);
		if( fTime > m_fLockTime ){
			m_tLastTime = TLIB::Tempus::TimeGetTime(); 
			ret = true ;
		}
	}

	//	: 押されている
	if( m_bMouseRB ){
		//	: 押されていた
		m_bMouseRBLock = true ;
	}else{
		//	: 押されていなかった
		m_bMouseRBLock = false ;
	}

	return ret;
};

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：仮想関数
//// 用途       ：カーソルがスプライトに重なっているかどうか
//// 引数       ： const D3DXMATRIX&            i_mMatrix       //  : 
////            ： const D3DXVECTOR3&           i_vPos          //  :
////            ： const D3DXVECTOR3&           i_vCenter       //  :
////            ： const D3DXVECTOR3&           i_vOffsetPos    //  :
////            ： const LPTATRATEXTURE     i_pTexture      //  :
////            ： const Rect*                  i_pRect         //  :
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
bool Cursor2D::isHitSprite(const PrimitiveSprite* i_TargetSprite)
{
	getPos();

	if( !i_TargetSprite )return false ;	//	: ターゲットがNULLだったら計算しようがない!( false )

	Point	poTL	= Point(0,0),
			poBR	;	//	: 計算用の画像の大きさ


	//////////
	//	: 画像サイズの獲得処理
	if( i_TargetSprite->m_pRect ){

		//////////
		//	: スプライトにRectが指定されていればそれを利用
		poBR.x = i_TargetSprite->m_pRect->right  - i_TargetSprite->m_pRect->left ;
		poBR.y = i_TargetSprite->m_pRect->bottom - i_TargetSprite->m_pRect->top  ;

	}else if( i_TargetSprite->m_pTexture ){	//	: Textureはちゃんと指定されているか?

		//////////
		//	: スプライトにRectが指定されていなければ
		//	: Texture自体の大きさを獲得
		D3DSURFACE_DESC desc;

		//////////
		//	: Textureのサイズ獲得に失敗したら
		//	: 計算しようがないのでとりあえず false
		if( FAILED( i_TargetSprite->m_pTexture->getTexture()->GetLevelDesc( 0, &desc ) )){ return false; }

		//////////
		//	: 
		poBR.x = desc.Width;
		poBR.y = desc.Height;
	}else{
		//////////
		//	: RectもTextureも無ければ計算しようが・・・
		return false;
	}
	//	: 画像サイズの獲得処理
	//////////
	
	//////////
	//	: 中心補正
	poTL.x -= (LONG)i_TargetSprite->m_vCenter.x;
	poTL.y -= (LONG)i_TargetSprite->m_vCenter.y;
	poBR.x -= (LONG)i_TargetSprite->m_vCenter.x;
	poBR.y -= (LONG)i_TargetSprite->m_vCenter.y;
	//	: 中心補正
	//////////

	//////////
	//	: 座標補正
	poTL.x += (LONG)i_TargetSprite->m_vOffsetPos.x;
	poTL.y += (LONG)i_TargetSprite->m_vOffsetPos.y;
	poBR.x += (LONG)i_TargetSprite->m_vOffsetPos.x;
	poBR.y += (LONG)i_TargetSprite->m_vOffsetPos.y;
	//	: 座標補正
	///////////

	///////////
	//	: 
	D3DXMATRIX mMatrix = i_TargetSprite->getAspectMatrix();
	poTL = MatrixCalculator(mMatrix,poTL);
	poBR = MatrixCalculator(mMatrix,poBR);
	//	: 
	///////////


	Rect rc(poTL,poBR);

	if( rc.PtInRect( m_vMousePoint ) ) return true ;
	
	return false ;
	
}
/**************************************************************************
 PrimitiveSprite 定義部
***************************************************************************/
LPD3DXSPRITE	PrimitiveSprite::m_pSprite			= NULL	;
DWORD			PrimitiveSprite::m_dwMyInstanceQty	= 0		;

/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,Rect* Rect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
////            ：  LPTATRATEXTURE pTexture,	//	: テクスチャーへのポインタ
////            ：  Rect*			Rect,			//	: テクスチャの描画範囲
////            ：  D3DXVECTOR3&	vCenter,		//	: 中心位置
////            ：  D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
////            ：  D3DCOLOR		color			//	: 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
PrimitiveSprite::PrimitiveSprite(
	const LPDIRECT3DDEVICE9		pD3DDevice		,
	const LPTATRATEXTURE		pTexture		,
	const Rect*					rect			,
	const D3DXVECTOR3&			vCenter			,
	const D3DXVECTOR3&			vOffsetPos		,
	const Color					color			,
	const bool					bApplyAspect
)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_bApplyAspect(bApplyAspect)
	,m_Color(color)
{
	try{
		//Debugger::DBGWRITINGLOGTEXT::addStr(L"PrimitiveSprite::PrimitiveSprite  >>>>  スプライトの実態作成完了これより初期化を行います\n");
		if(rect){
			m_pRect = new Rect(*rect);
		}
		if( !m_pSprite ){
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"PrimitiveSprite::PrimitiveSprite  >>>>  スプライトの新規作成をします\n");
			if( FAILED( D3DXCreateSprite( pD3DDevice, &m_pSprite ) ) ){
				// 初期化失敗
				throw BaseException(
					L"スプライトの作成に失敗しました。",
					L"PrimitiveSprite::PrimitiveSprite()"
				);
			}
		}
		m_dwMyInstanceQty++;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
}
/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,Rect* Rect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
////            ：  LPTATRATEXTURE pTexture,	//	: テクスチャーへのポインタ
////            ：  Rect*			Rect,			//	: テクスチャの描画範囲
////            ：  D3DXVECTOR3&	vCenter,		//	: 中心位置
////            ：  D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
////            ：  D3DCOLOR		color			//	: 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
PrimitiveSprite::PrimitiveSprite(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPTATRATEXTURE		pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const Rect*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		,
		const bool					bApplyAspect
)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_bApplyAspect(bApplyAspect)
	,m_Color(color)
{
	try{
		//Debugger::DBGWRITINGLOGTEXT::addStr(L"PrimitiveSprite::PrimitiveSprite  >>>>  スプライトの実態作成完了これより初期化を行います\n");
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;

		//	: 渡されたRectが自分で管理しても良い物とは限らないためここで新しい実体にコピーする
		if(pRect){
			m_pRect = new Rect(*pRect);
		}

		//	: スプライトのインスタンスはゲーム内で一つのみ
		if( !m_pSprite ){
			//Debugger::DBGWRITINGLOGTEXT::addStr(L"PrimitiveSprite::PrimitiveSprite  >>>>  スプライトの新規作成をします\n");
			if( FAILED( D3DXCreateSprite( pD3DDevice, &m_pSprite ) ) ){
				// 初期化失敗
				throw BaseException(
					L"スプライトの作成に失敗しました。",
					L"PrimitiveSprite::PrimitiveSprite()"
				);
			}
		}
		//	: このクラスのインスタンス数をカウント
		m_dwMyInstanceQty++;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
}

/////////////////// ////////////////////
//// 関数名     ：virtual PrimitiveSprite::~PrimitiveSprite()
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
PrimitiveSprite::~PrimitiveSprite(){
	SafeDelete(m_pRect);
	//SafeRelease(m_pTexture);
	m_dwMyInstanceQty--;

	//	: 自分がこのクラスの最後のインスタンスだったらスプライトを削除
	if( m_dwMyInstanceQty <= 0 ){
		//Debugger::DBGWRITINGLOGTEXT::addStr(L"PrimitiveSprite::~PrimitiveSprite  >>>>  スプライトが不要になりました 削除します\n");
		SafeRelease(m_pSprite);
	}
}



/////////////////// ////////////////////
//// 関数名     ：void PrimitiveSprite::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void PrimitiveSprite::Draw(DrawPacket& i_DrawPacket)
{
	if(m_pSprite && m_pTexture){
		D3DXMATRIX mAll ;
		//if( m_bApplyAspect )	
		mAll = this->getAspectMatrix();
		//else					mAll = m_mMatrix ;
		
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &mAll );
			m_pSprite->Draw(m_pTexture->getTexture(), m_pRect,
				&m_vCenter, &m_vOffsetPos, m_Color.dwColor );
		}
		m_pSprite->End();
	}
}
/**************************************************************************
 SpriteObject 定義部
***************************************************************************/
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
SpriteObject::SpriteObject(
	const LPDIRECT3DDEVICE9		pD3DDevice		,
	const LPTATRATEXTURE		pTexture		,
	const D3DXVECTOR3&			vScale			,
	const D3DXVECTOR3&			vRot			,
	const D3DXVECTOR3&			vPos			,
	const Rect*					pRect			,
	const D3DXVECTOR3&			vCenter			,
	const D3DXVECTOR3&			vOffsetPos		,
	const Color					color			,
	const wiz::OBJID			id				,
	      bool					bApplyAspect
)
	:Object(id)
	,PrimitiveSprite(pD3DDevice,pTexture,vScale,vRot,vPos,pRect,vCenter,vOffsetPos,color,bApplyAspect)
{
	try{
		//	: 初期マトリックスを計算
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}

};
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
SpriteObject::~SpriteObject(){
};
/////////////////// ////////////////////
//// 関数名     ：void SpriteObject::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
void SpriteObject::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	PrimitiveSprite::Draw(i_DrawPacket);
};
/**************************************************************************
  定義部
***************************************************************************/
namespace Avoidance{

RenderTargetSprite::RenderTargetSprite(BassPacket* i_BassPacket, UINT i_Width, UINT i_Height, wiz::OBJID id )
: m_sfRenderTarget( NULL )
, m_sfRenderTargetZ( NULL )
, m_ClientSize(i_Width,i_Height)
, Object(id)
, PrimitiveSprite( i_BassPacket->GetDevice(),  NULL, NULL, g_vZero, g_vZero)
{
	//	: テクスチャを動的に生成する（横６４０ピクセル・縦４８０ピクセル、３２ビットカラー）
	//D3DXCreateTexture( i_BassPacket->pD3DDevice, i_Width, i_Height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture );
	//i_BassPacket->pD3DDevice->CreateDepthStencilSurface( i_Width, i_Height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &m_sfRenderTargetZ, NULL );	//	深度バッファを生成
	//m_pTexture->GetSurfaceLevel( 0, &m_sfRenderTarget );																	//	テクスチャからサーフェイスを取得


}
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
void RenderTargetSprite::TargetRender( RenderPacket& i_RenderPacket ){

	LPDIRECT3DDEVICE9 pd3dDevice = i_RenderPacket.GetDevice() ;
    //	: 現在のレンダーターゲットを保存する
    D3DVIEWPORT9		defaultViewport ;	//	画面の描画領域に関するデータ
    LPDIRECT3DSURFACE9	sfBackBuffer	= NULL,
    					sfBackBufferZ	= NULL ;
    pd3dDevice->GetViewport( &defaultViewport );
    pd3dDevice->GetRenderTarget( 0, &sfBackBuffer );
    pd3dDevice->GetDepthStencilSurface( &sfBackBufferZ );
    
    //	: 新しいレンダーターゲットを設定する
    //		（テクスチャに対する描画に切り替える）
	D3DVIEWPORT9	newViewport	= { 0, 0, m_ClientSize.cx, m_ClientSize.cy, 0.0f, 1.0f } ;	//	画面の左上端から幅640高さ480を描画領域にする
    pd3dDevice->SetViewport( &newViewport );
    pd3dDevice->SetRenderTarget( 0, m_sfRenderTarget );
    pd3dDevice->SetDepthStencilSurface( m_sfRenderTargetZ );

    // Clear the render target and the zbuffer 
    FAILED( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 255, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		//	: モデルの変換行列を設定
		D3DXMATRIX	m ;
		D3DXMatrixIdentity( &m );
		pd3dDevice->SetTransform( D3DTS_WORLD, &m );
		

        FAILED( pd3dDevice->EndScene() );
    }
    
    //	: レンダーターゲットをバックバッファに戻す
    pd3dDevice->SetViewport( &defaultViewport );
    pd3dDevice->SetRenderTarget( 0, sfBackBuffer );
    pd3dDevice->SetDepthStencilSurface( sfBackBufferZ );
    
    //	: バックバッファを戻したので、これらは用済み
    SAFE_RELEASE( sfBackBuffer );
    SAFE_RELEASE( sfBackBufferZ );
};

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
void RenderTargetSprite::Draw(DrawPacket& i_DrawPacket){
	PrimitiveSprite::Draw(i_DrawPacket);
}
}
}//end of namespace	base2Dobject.
}//end of namespace	wiz.