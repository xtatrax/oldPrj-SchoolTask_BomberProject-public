////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Load.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包データと備考	：ロードファクトリー
//					▼
//	namespace wiz;
//		class Load ;
//		class Factory_Load ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Load.h"
#include "BassItems.h"

namespace wiz{
	namespace bomberobject{

/************************************************************************
Load 定義部
************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：Load(LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,DWORD next,
////            ：    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, Rect* pRect,
////            ：    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// カテゴリ   ：コンストラクタ
//// 用途       ：スプライトを描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  LPTATRATEXTURE pTexture     // 貼り付けたいテクスチャ
////            ：  DWORD next                      // 次の画面
////            ：  D3DXVECTOR3 &vScale             // 大きさ
////            ：  D3DXVECTOR3 &vRot               // 三軸回転
////            ：  D3DXVECTOR3 &vPos               // 設置座標
////            ：  Rect* pRect                     // 描画したい範囲(NULLで全体を描画)
////            ：  D3DXVECTOR3& vCenter            // 中心
////            ：  D3DXVECTOR3& vOffsetPos         // オフセット座標
////            ：  Color color = 0xFFFFFFFF        // 色
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
Load::Load(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPTATRATEXTURE	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const Rect*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Command*				Com			,
		const Color					color
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color )
,m_Com(*Com)
,m_vPos( vPos )
,m_iTime( 0 )
,m_fRate( 1.0f )
,m_iPtn( 0 )
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

Load::~Load(){	
}

/////////////////// ////////////////////
//// 関数名     ：void Load::Draw( DrawPacket& i_DrawPacket)
//// カテゴリ   ：関数
//// 用途       ：スプライトを描画
//// 引数       ：DrawPacket& i_DrawPacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Load::Draw(DrawPacket& i_DrawPacket)
{
	//	: 描画は親クラスに任せる
	SpriteObject::Draw(i_DrawPacket);
};

/////////////////// ////////////////////
//// 関数名     ：void Load::Update( UpdatePacket& i_UpdatePacket)
//// カテゴリ   ：関数
//// 用途       ：データの更新
//// 引数       ：UpdatePacket& i_UpdatePacket    //もろもろのデータ
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Load::Update(UpdatePacket& i_UpdatePacket)
{
	m_pRect->top	= m_iPtn	*128;
	m_pRect->bottom	= (m_iPtn+1)*128;

	if( m_iTime%20 == 0 )
	m_iPtn++;
	m_iPtn	%= 4;

	m_iTime++;
	if( m_iTime > 240 ){
		i_UpdatePacket.PushCommand( m_Com );
		//Debugger::DBGWRITINGLOGTEXT::addStr(L"i_UpdatePacket.pCommand = m_Com\n");
	}
};

/**************************************************************************
 Factory_Load 定義部
****************************************************************************/
/**************************************************************************
 Factory_Load::Factory_Load(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Load::Factory_Load(FactoryPacket* fpac,Command* Com){
	try{
		// MANUAL
		//fpac->AddObject(
		//	new SpriteObject( fpac->GetDevice(),
		//			fpac->AddTexture( L"MANUAL2.png" ),
		//			D3DXVECTOR3( 0.8f, 0.8f, 0.0f ),
		//			g_vZero,
		//			D3DXVECTOR3( 100.0f, 50.0f, 0.0f ),					
		//			&Rect( 0, 0, 1024, 512 ),
		//			g_vZero,
		//			g_vZero
		//	)
		//) ;
		//	NOWLOADING
		fpac->AddObject(
			new	Load(
				fpac->GetDevice(),
				fpac->AddTexture( L"NOW_LOADING3.png" ),
				D3DXVECTOR3(0.5f,0.5f,0.0f),
				g_vZero,
				D3DXVECTOR3( 500.0f, 530.0f, 0.0f ),
				&Rect( 0, 0, 1024, 128 ),
				g_vZero,
				g_vZero,
				Com,
				0xFFFFFFFF
			)
		);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Load::~Factory_Load();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Load::~Factory_Load(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
