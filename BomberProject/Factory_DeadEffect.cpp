////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_DeadEffect.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤涼
//	内包ﾃﾞｰﾀと備考	：爆散エフェクト
//					▼
//	namespace wiz;
//		class DeadEffect ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Wall.h"
namespace wiz{
namespace bomberobject{

/**************************************************************************
 DeadEffect 定義部
****************************************************************************/
/**************************************************************************
 DeadEffect::DeadEffect(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
DeadEffect::DeadEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		vDir,
						LPDIRECT3DTEXTURE9 pTexture,
						wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_vPos(vPos)
,m_fLife(5.0f)
,m_fDir(vDir)
,m_fSpeed( float(rand()%100)+300 )
,m_fAccele( -(m_fSpeed / 200) )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {1.0f,1.0f,1.0f,1.0f};

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

	m_iDirZ	= rand()%100;
	if( m_iDirZ < 50 )
		m_iDirZ	= 1;
	else
		m_iDirZ	= -1;

}

/*********************************
デストラクタ
*********************************/
DeadEffect::~DeadEffect(){
	m_pCoil		= NULL;
	m_pCamera	= NULL;
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
void DeadEffect::Draw(DrawPacket& i_DrawPacket)
{
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
void DeadEffect::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera )	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	const float MoveRate	= 0.003f;
	const float ColorRate	= 0.003f;
	m_vPos.x	+= cosf( m_fDir )*MoveRate*m_fSpeed;
	m_vPos.y	+= sinf( m_fDir )*MoveRate*m_fSpeed;
	m_vPos.z	+= cosf( m_fDir )*MoveRate*m_fSpeed*5*m_iDirZ;

	m_fSpeed	+= m_fAccele;
	if( m_fSpeed < 0.0f )
		m_fSpeed	= 0.0f;

	if( m_Material.Ambient.r >= 0 ){
		m_Material.Ambient.r	-= ColorRate;
		m_Material.Ambient.g	-= ColorRate;
		m_Material.Ambient.b	-= ColorRate;
	}
	//計算はUpdateで
	//拡大縮小
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, 0.8f, 0.8f, 0.0f );
	//移動用
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,m_vPos.x,m_vPos.y,m_vPos.z);
	//ミックス行列
	m_Matrix = mScale * mMove;
}

}
}