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
	LPTATRATEXTURE pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
DeadEffect::DeadEffect(LPDIRECT3DDEVICE9	pD3DDevice,
						LPTATRATEXTURE	pTexture,
						D3DXVECTOR3			vPos,
						wiz::OBJID			id	)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
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

	for( int i = 0; i < PARTICLS_NUM; i++ ){
		this->addEffect( vPos, i*(360.0f/PARTICLS_NUM) );
	}

}

/*********************************
デストラクタ
*********************************/
DeadEffect::~DeadEffect(){
	SafeDeletePointerMap( m_ItemMap_Target );
	m_ItemMap_Target.clear();
}

/*********************************
追加
*********************************/
void	DeadEffect::addEffect( D3DXVECTOR3 vPos, float fDir){
	EffectItem*	pItem	= new EffectItem();

	pItem->m_vPos	= vPos;
	pItem->m_fDir	= fDir;

	m_ItemMap_Target.insert(multimap<float,EffectItem*>::value_type(pItem->m_vPos.y,pItem));

}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
void DeadEffect::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		setMatrix( it->second->m_vPos );
		PrimitiveBox::CalcWorldMatrix();
		PrimitiveBox::Draw(i_DrawPacket);

		++it;
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

	const float ColorRate	= 0.003f;

	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		float	fDirZ	= it->second->m_fDir;
		if( fDirZ >= 180.0f ){
			fDirZ	-= 180.0f;
		}
		it->second->m_vPos.x	+= cosf( it->second->m_fDir )*2;
		it->second->m_vPos.y	+= sinf( it->second->m_fDir )*2;
		it->second->m_vPos.z	+= cosf( fDirZ )*5;

		it++;
	}

	if( m_Material.Ambient.r > 0 ){
		m_Material.Ambient.r	-= ColorRate;
		m_Material.Ambient.g	-= ColorRate;
		m_Material.Ambient.b	-= ColorRate;
	}
	else{
		m_Material.Ambient.r	= 0;
		m_Material.Ambient.g	= 0;
		m_Material.Ambient.b	= 0;
	}
}

/****************************************************
マトリックスの設定
****************************************************/
void	DeadEffect::setMatrix( D3DXVECTOR3 vPos ){

	PrimitiveBox::SetBasePos(vPos);
	D3DXVECTOR3 vScale(0.8f, 0.8f, 0.0f);
	PrimitiveBox::SetBaseScale(vScale);
}

/****************************************************
座標の設定
****************************************************/
void	DeadEffect::setPos( D3DXVECTOR3 i_vPos ){
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){

		it->second->m_vPos	= i_vPos;
		++it;
	}

	m_Material.Ambient.r	= 255;
	m_Material.Ambient.g	= 255;
	m_Material.Ambient.b	= 255;
}

/**************************************************************************
 Factory_DeadEffct 定義部
****************************************************************************/
/**************************************************************************
 Factory_DeadEffct::Factory_DeadEffct(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_DeadEffect::Factory_DeadEffect(FactoryPacket* fpac)
{
	try{

		//float	wide	= BASE_CLIENT_WIDTH/2;
		//float	height	= BASE_CLIENT_HEIGHT/2;

		//D3DXVECTOR3	vScale	= D3DXVECTOR3( 0.5f, 0.5f, 0.0f );
		//D3DXVECTOR3	vPos	= D3DXVECTOR3( (wide-512.0f*vScale.x), (height-256.0f*vScale.y-100), 0.0f );
		//LPTATRATEXTURE pTex;
		//pTex = fpac->AddTexture(L"DeadPerticul.png");
		//DeadEffect* dEffect	=	new DeadEffect( fpac->GetDevice(), pTex, g_vZero );
		////for( int i = 0; i < PARTICLS_NUM; i++ ){
		////	dEffect->addEffect( i*(360.0f/PARTICLS_NUM) );
		////}
		//fpac->AddObject(dEffect);


	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_DeadEffct::~Factory_DeadEffct();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_DeadEffect::~Factory_DeadEffect(){
    //なにもしない
}

}
}