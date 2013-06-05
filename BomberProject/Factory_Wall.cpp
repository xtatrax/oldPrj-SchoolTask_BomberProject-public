////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Wall.h"
#include "BassItems.h"


namespace wiz{
//PlayerCoil* WallObject::m_pPlayerCoil = NULL ;
//Camera*		WallObject::m_pCamera = NULL;	

/**************************************************************************
 WallObject 定義部
****************************************************************************/
/**************************************************************************
 WallObject::WallObject(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
WallObject::WallObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,LPDIRECT3DTEXTURE9 pTexture2,
					   LPDIRECT3DTEXTURE9 pTexture3,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pWallTex( pTexture )
,m_pPolyTex( pTexture2 )
,m_pDeadTex( pTexture3 )
,m_Ptn(0)
,m_pSound( NULL )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_pPlayerCoil	= NULL;
	m_pCamera		= NULL;
	for( int i = 0; i < PARTICLS_NUM; i++ )
		m_pDeadEffect[i]	= NULL;
}
/////////////////// ////////////////////
//// 用途       ：~WallObject();
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
WallObject::~WallObject(){
	m_pCamera		= NULL ;
	m_pPlayerCoil	= NULL ;
	for( int i = 0; i < PARTICLS_NUM; i++ )
		m_pDeadEffect[i]	= NULL;

	SafeDeletePointerMap( m_ItemMap_All );
	SafeDeletePointerMap( m_ItemMap_Poly );

	m_ItemMap_All.clear() ;
	m_ItemMap_Target.clear() ;	//	: この子はClearのみ
	m_ItemMap_Poly.clear() ;
}

/////////////////// ////////////////////
//// 用途       ：WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// カテゴリ   ：コンストラクタ
//// 用途       ：関数
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
void WallObject::UpdateTargetItem(){
	
	
}

	
bool WallObject::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
{
	//float fTH = 150 ;
	//float fTW =  20 ;
	//if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
	//	abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
	//	return true ;
	//}
	return false ;
}

/////////////////// ////////////////////
//// 用途       ：void Will::GetOBB( size_t Index, OBB& obb )
//// カテゴリ   ：関数
//// 用途       ：指定のインデックスの現在のOBBを得る
//// 引数       :		size_t Index,
////					OBB& obb	//取得するOBB
//// 戻値       ：なし。インデックスが範囲外なら例外
////				 ＊現在のOBBを代入する
//// 担当者     ：曳地 大洋
//// 備考       ：
void WallObject::GetOBBList( float Index, list<OBB>& ObbList ){
    //指定の配置オブジェクトを検証
	multimap<float,WallItem*>::iterator itBegin = m_ItemMap_Target.lower_bound( 20.0f ) ;
	multimap<float,WallItem*>::iterator itEnd	= m_ItemMap_Target.upper_bound( 20.0f ) ;
	OBB obb ; 
	for(multimap<float,WallItem*>::iterator iter = itBegin; iter != itEnd; ++iter){
		obb.m_Center  = iter->second->m_vPos + iter->second->m_vPos;
		obb.m_Size	  = m_Size;
		obb.m_Size.x *= iter->second->m_vScale.x;
		obb.m_Size.y *= iter->second->m_vScale.y;
		obb.m_Size.z *= iter->second->m_vScale.z;
		obb.m_Size *= 0.5f;
		//トータルの回転を得る
		D3DXQUATERNION Qt = iter->second->m_vRot;
		Qt *= iter->second->m_vRot;
		//クオータニオンを正規化
		D3DXQuaternionNormalize(&Qt,&Qt);
		//クオータニオンから回転行列を作成
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&Qt);
		obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
		ObbList.push_back( obb ) ;
	}
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
//// 担当者     ：本多寛之
//// 備考       ：
void WallObject::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,WallItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		//テクスチャがある場合
		//if(m_pWallTex){
		//	m_pTexture	= m_pWallTex;
		//	DWORD wkdword;
		//	//現在のテクスチャステータスを得る
		//	i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//	//ステージの設定
		//	i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//	//デフィーズ色とテクスチャを掛け合わせる設定
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//	//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		//	// マトリックスをレンダリングパイプラインに設定
		//	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
		//	//コモンメッシュのDraw()を呼ぶ
		//	CommonMesh::Draw(i_DrawPacket);
		//	i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//	//ステージを元に戻す
		//	i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		//}
		//else{
		////テクスチャがない場合
		//	// マトリックスをレンダリングパイプラインに設定
		//	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
		//	//コモンメッシュのDraw()を呼ぶ
		//	CommonMesh::Draw(i_DrawPacket);
		//}
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		if( it->second->m_pDOB ){
			it->second->m_pDOB->Draw(i_DrawPacket);
		}else{
			it->second->m_pDOB = new DrawOBB(i_DrawPacket.pD3DDevice,it->second->m_Obb);
		}
#endif

		++it;
	}
	multimap<float,PolyItem*>::iterator it2 = m_ItemMap_Poly.begin();
	while(it2 != m_ItemMap_Poly.end()){
		//テクスチャがある場合
		if(m_pPolyTex){
			m_pTexture	= m_pPolyTex;
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}

		++it2;
	}

	if( m_pDeadEffect[0] != NULL ){
		for( int i = 0; i < PARTICLS_NUM; i++ ){
			m_pDeadEffect[i]->Draw( i_DrawPacket );
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
//// 担当者     ：本多寛之
//// 備考       ：
////            ：
////
void WallObject::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	if(m_pSound == NULL){
		m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));
	}
	if(m_pPlayerCoil == NULL){
		m_pPlayerCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}

	m_ItemMap_Target.clear();
	multimap<float,WallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,WallItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}

	multimap<float,WallItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){
		//拡大縮小
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
		//回転
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
		//ミックス行列
		it2->second->m_Matrix = mScale * mRot * mMove;
		//マティリアル設定
		m_Material = it2->second->m_Material;

		//衝突判定
		//OBB obb	= OBB( it2->second->m_vScale, it2->second->m_vRot, it2->second->m_vPos ) ;
		//if( m_pPlayerCoil ){
		//	m_pPlayerCoil->HitTestWall( obb, 0 ) ;
		//}

		if( m_pPlayerCoil && m_pPlayerCoil->HitTestWall( it2->second->m_Obb, 0 ) ){
			switch(m_pPlayerCoil->getState()){
				case COIL_STATE_MOVE:
					if(!m_pPlayerCoil->getSuperMode()){
						for( int i = 0; i < PARTICLS_NUM; i++ ){
							SafeDelete( m_pDeadEffect[i] );
							m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.pD3DDevice, m_pPlayerCoil->getPos(),
										float((360/PARTICLS_NUM) * i), m_pDeadTex/*i_UpdatePacket.pTxMgr->addTexture(i_UpdatePacket.pD3DDevice, L"DeadPerticul.png")*/);
						}
						m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
						m_pPlayerCoil->setState(COIL_STATE_DEAD);
					}
					break;
				default:
					break;
			}
		}

		if( m_pDeadEffect[0] != NULL ){
			for( int i = 0; i < PARTICLS_NUM; i++ ){
				m_pDeadEffect[i]->Update( i_UpdatePacket );
				if(m_pDeadEffect[i]->getColor() <= 0.0f){
					SafeDelete( m_pDeadEffect[i] );
					m_pPlayerCoil->setReadyContinue(true);
					break;
				}
			}
		}


		++it2;
	}

	multimap<float,PolyItem*>::iterator it3 = m_ItemMap_Poly.begin();
	while(it3 != m_ItemMap_Poly.end()){
		//拡大縮小
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it3->second->m_vScale.x,it3->second->m_vScale.y,0.0f);
		//回転
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it3->second->m_vRot);
		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it3->second->m_vPos.x,it3->second->m_vPos.y,it3->second->m_vPos.z);
		//ミックス行列
		it3->second->m_Matrix = mScale * mRot * mMove;
		//マティリアル設定
		m_Material = it3->second->m_Material;

		++it3;
	}

	//**************************************************************************************
	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
		//法線と頂点からuv値を得る
		BoxVecNomal2UV_1_4(pVer[n].vec,pVer[n].normal,m_Ptn,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();
	//***********************************************************************************

	++m_Ptn;
	static	int	s_Time	= 0;
	//++s_Time;

	//if( s_Time == 2 ){
	//	++m_Ptn;
	//	if( m_Ptn > 3 )
	//		m_Ptn	%= 4;
	//	s_Time	= 0;
	//}
}

/////////////////// ////////////////////
//// 用途       ：void AddWall( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：Wallの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：本多寛之
////				曳地 大洋
//// 備考       ：
void WallObject::AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	WallItem* pItem = new WallItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos	= vPos;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	pItem->m_Material.Diffuse = Diffuse;
	pItem->m_Material.Specular = Specular;
	pItem->m_Material.Ambient = Ambient;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	//衝突判定用のOBBの初期化
	pItem->m_Obb = OBB( vScale, pItem->m_vRot, vPos ) ;
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixRotationYawPitchRoll(&mRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_All.insert(multimap<float,WallItem*>::value_type(pItem->m_vPos.y,pItem));
//********************************************************************************************
	PolyItem* pPoly = new PolyItem;
	pPoly->m_vScale.x = vScale.x;
	pPoly->m_vScale.y = vScale.y;
	pPoly->m_vScale.z = 0.0f;
	pPoly->m_vPos	= vPos;
    ::ZeroMemory(&pPoly->m_Material,sizeof(D3DMATERIAL9));
	pPoly->m_Material.Diffuse = Diffuse;
	pPoly->m_Material.Specular = Specular;
	pPoly->m_Material.Ambient = Ambient;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pPoly->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Poly.insert(multimap<float,PolyItem*>::value_type(pPoly->m_vPos.y,pPoly));
}

/**************************************************************************
 Factory_Wall 定義部
****************************************************************************/
/**************************************************************************
 Factory_Wall::Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Wall::Factory_Wall(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE WallDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE WallSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE WallAmbient = {0.5f,0.5f,0.5f,0.0f};

 	//	D3DCOLORVALUE Wall2Diffuse = {1.0f,1.0f,1.0f,1.0f};
		//D3DCOLORVALUE Wall2Specular = {0.0f,0.0f,0.0f,0.0f};
		//D3DCOLORVALUE Wall2Ambient = {1.0f,1.0f,1.0f,1.0f};

		//fpac->m_pVec->push_back(
		//	new Polygon( fpac->pD3DDevice,
		//					1.0f,
		//					4,
		//					D3DXVECTOR3(38.0f,12.0f,0.0f),
		//					D3DXVECTOR3(0.0f,0.0f,0.0f),
		//					Wall2Diffuse,
		//					Wall2Specular,
		//					Wall2Ambient,
		//					OBJID_3D_POLYGON,
		//					false,
		//					fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"biribiriWall.png")));

		WallObject* Wall = new WallObject(fpac->pD3DDevice,
			fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"biribiriWall.png"),
			fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Lightning.tga"),
			fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"DeadPerticul.png"));
		//お試し
		//Wall->AddWall(D3DXVECTOR3(10.0f,25.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,20.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//右横
		Wall->AddWall(D3DXVECTOR3(2.0f,26.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,0.0f),
					  D3DXVECTOR3(38.5f,12.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//左横
		//Wall->AddWall(D3DXVECTOR3(2.0f,26.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(0.5f,12.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//お試し上
		//Wall->AddWall(D3DXVECTOR3(40.0f,2.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,24.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//下
		Wall->AddWall(D3DXVECTOR3(2.0f,40.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(20.0f,0.5f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//真ん中縦
		Wall->AddWall(D3DXVECTOR3(2.0f,10.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,0.0f),
					  D3DXVECTOR3(20.0f,6.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//お試し
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(20.0f,10.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//下
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,120.0f),
					  D3DXVECTOR3(20.0f,20.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		// 左横向き
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(7.0f,14.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//お試し
		Wall->AddWall(D3DXVECTOR3(2.0f,20.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,45.0f),
					  D3DXVECTOR3(20.0f,20.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		Wall->AddWall(D3DXVECTOR3(2.0f,5.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,45.0f),
					  D3DXVECTOR3(30.0f,15.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		Wall->AddWall(D3DXVECTOR3(2.0f,4.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,-45.0f),
					  D3DXVECTOR3(20.0f,17.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		fpac->m_pVec->push_back(Wall);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Wall::~Factory_Wall();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Wall::~Factory_Wall(){
    //なにもしない
}

}
//end of namespace wiz.
