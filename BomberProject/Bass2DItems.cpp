////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：BassItems.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：ゲームのベースになるアイテム群の宣言
//					▼
//	プリミティブ周辺を山ノ井先生のソースを参考に大改造する! 
//
//	namespace wiz;
//
#include "StdAfx.h"
#include "Bass2DItems.h"
namespace wiz {

namespace base2Dobject{
/**************************************************************************
 PrimitiveSprite 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// カテゴリ   ：仮想関数
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
////            ：  LPDIRECT3DTEXTURE9 pTexture,	//	: テクスチャーへのポインタ
////            ：  RECT*			Rect,			//	: テクスチャの描画範囲
////            ：  D3DXVECTOR3&	vCenter,		//	: 中心位置
////            ：  D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
////            ：  D3DCOLOR		color			//	: 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, RECT* rect,
	D3DXVECTOR3& vCenter, D3DXVECTOR3& vOffsetPos, Color color)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_Color(color)
{
	try{
		if(rect){
			m_pRect = new RECT(*rect);
		}
		if(
			FAILED(
				D3DXCreateSprite(
					pD3DDevice,
					&m_pSprite
				)
			)
		){
			// 初期化失敗
			throw BaseException(
				L"スプライトの作成に失敗しました。",
				L"PrimitiveSprite::PrimitiveSprite()"
			);
		}
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
	SAFE_DELETE(m_pRect);
	SafeRelease(m_pSprite);
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
		D3DXMATRIX mAspectRate,mAll;
		D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
		D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
	    D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &mAll );
			m_pSprite->Draw(m_pTexture, m_pRect,
				&m_vCenter, &m_vOffsetPos, m_Color.dwColor );
		}
		m_pSprite->End();
	}
}
/**************************************************************************
 SpriteObject 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPDIRECT3DTEXTURE9 pTexture     // 貼り付けたいテクスチャ
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  RECT* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
SpriteObject::SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			RECT *pRect, D3DXVECTOR3 &vCenter, D3DXVECTOR3 &vOffsetPos, Color color,
			wiz::OBJID id)
			:Object(id)
			,PrimitiveSprite(pD3DDevice,pTexture,pRect,vCenter,vOffsetPos,color)
{
	try{
		//	: 初期マトリックスを計算
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
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

RenderTargetSprite::RenderTargetSprite(BassPacket& i_BassPacket, UINT i_Width, UINT i_Height){
	//	: テクスチャを動的に生成する（横６４０ピクセル・縦４８０ピクセル、３２ビットカラー）
	//D3DXCreateTexture( i_BassPacket.pD3DDevice, i_Width, i_Height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture );
	//pd3dDevice->CreateDepthStencilSurface( i_Width, i_Height, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &g_sfRenderTargetZ, NULL );	//	深度バッファを生成
	//g_pTexture->GetSurfaceLevel( 0, &g_sfRenderTarget );																	//	テクスチャからサーフェイスを取得


}

}//end of namespace	base2Dobject.
}//end of namespace	wiz.