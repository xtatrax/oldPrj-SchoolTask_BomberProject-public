////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_CheckPoint.h"
#include "Factory_Player.h"
#include "BassItems.h"
const float CHECK_POINT_RADIUS = 0.25f ;
const float EFFECT_SIZE	= 2.0f;
D3DCOLORVALUE CHECKPOINTCOLOR = { 1.0f, 1.0f, 1.0f, 1.0f } ;
namespace wiz{

/**************************************************************************
 CheckEffect 定義部
****************************************************************************/
/**************************************************************************
 CheckEffect::CheckEffect(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
CheckEffect::CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		fLength,
						LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_vPos( vPos )
,m_Num( (int)(fLength) )
,m_fWide( EFFECT_SIZE*4 )
,m_fHight( EFFECT_SIZE )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse = {1.0f,1.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {1.0f,1.0f,0.0f,0.0f};

	m_Material.Diffuse	= Diffuse;
	m_Material.Specular	= Specular;
	m_Material.Ambient	= Ambient;

	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
		//法線と頂点からuv値を得る
		BoxVecNomalUV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();

}

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
//// 担当者     ：佐藤涼
//// 備考       ：
void CheckEffect::Draw(DrawPacket& i_DrawPacket)
{
	for( int i = 1; i <= m_Num; i++ ){
		update( i );

	//テクスチャがある場合
		if(m_pTexture){
			DWORD wkdword;
			//現在のテクスチャステータスを得る
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//ステージの設定
			i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
			//デフィーズ色とテクスチャを掛け合わせる設定
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
	}
}

/////////////////// ////////////////////
//// 用途       ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void CheckEffect::update( int i ){

	m_vPos.x	= float(i*2-1);

	//計算はUpdateで
	//拡大縮小
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, m_fWide, m_fHight, 0.0f );
	//回転
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	//移動用
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,m_vPos.x,m_vPos.y,m_vPos.z);
	//ミックス行列
	m_Matrix	= mScale * mRot * mMove;

	//m_fWide	-= 1;
	if( m_fWide > 0.0f )
		Reduction();
}

/*************************************
関数名　：
用途　　：サイズ変更
カテゴリ：
引数　　：
戻り値　：
担当者　：佐藤涼
備考　　：
*************************************/
void	CheckEffect::Reduction(){
	float	rate = m_fWide / m_fHight;

	m_fWide		-= 0.001f*rate;
	m_fHight	-= 0.001f;
}

/****************************************************************************
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_pEffect( NULL )
, m_ActiveItem( NULL )
, m_Color( CHECKPOINTCOLOR )
, m_Thicken( 1.0f )
, m_Length( fLength )
{
}
CheckPoint::~CheckPoint(){
	SafeDeletePointerContainer( m_ItemContainer ) ;
}
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
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec, typeid(PlayerCoil) );
	if( !m_pCamera ) m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA );
	
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;
		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
			m_ActiveItem++ ;
			m_pEffect	= new CheckEffect( i_UpdatePacket.pD3DDevice, m_pCoil->getPos(),m_Length,
					i_UpdatePacket.pTxMgr->addTexture( i_UpdatePacket.pD3DDevice, L"media/Textures/particle.png") );
			if(m_ActiveItem <= m_ItemContainer.size()) return ;
		}
	}

	if( m_pEffect != NULL ){
		m_pEffect->Update( i_UpdatePacket );
	}

	Blink();
	m_Color.b = 0;
	m_Material.Diffuse	= m_Color;
	m_Material.Ambient	= m_Color;
};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹 本多寛之(編集)
//// 備考       ：
////            ：
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){


		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;
			CalcWorldMatrix();
			Cylinder::Draw( i_DrawPacket );
			
			OBB obb = OBB( m_BasePos, m_BaseQt, m_BaseScale );
			//DrawOBB(i_DrawPacket);
			//m_pCoil->HitTestWall();
		}
	}

	if( m_pEffect != NULL ){
		m_pEffect->Draw( i_DrawPacket );
	}

};

/////////////////// ////////////////////
//// 用途       ：virtual void Blink()
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを明滅する
//// 引数       ：なし　
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void	CheckPoint::Blink(){
	m_Color.a	-=	0.03f * m_Thicken + 0.01f;

	if( m_Color.a < 0.3f ){
		m_Color.a	 =  0.3f;
		m_Thicken	*= -1.0f;
	}
	else if( m_Color.a > 0.9f ){
		m_Color.a	 =  0.9f;
		m_Thicken	*= -1.0f;
	}
}

/**************************************************************************
 Factory_CheckPoint 定義部
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			
			CheckPoint* pcp ;
			fpac->m_pVec->push_back(
				pcp = new CheckPoint( fpac->pD3DDevice, 100.0f)
			);
			pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

		}
		
		catch(...){
			//再throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//なにもしない
	}
}//end of namespace wiz.