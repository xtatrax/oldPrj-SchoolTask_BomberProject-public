////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Mouse.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：曳地 大洋
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Mouse ;
//

#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Cursor.h"

namespace wiz{
/**************************************************************************
 MouseCursor 定義部
****************************************************************************/
/**************************************************************************
 MouseCursor::MouseCursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
MouseCursor::MouseCursor(
						 LPDIRECT3DDEVICE9 pD3DDevice,
						 LPDIRECT3DTEXTURE9 pTexture,
						 D3DXVECTOR3	   &vScale,
						 D3DXVECTOR3	   &vPos,
						 wiz::OBJID id)					 
:PrimitiveBox(pD3DDevice,
			  D3DCOLORVALUE(),
			  D3DCOLORVALUE(),
			  D3DCOLORVALUE(),
			  id,
		      pTexture)
,m_pMouseTex( pTexture )
,m_Ptn(0)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_pCamera = NULL;

}

///////////////////// ////////////////////
////// 用途       ：MouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
////// カテゴリ   ：コンストラクタ
////// 用途       ：関数
////// 引数       ：なし
////// 戻値       ：なし
////// 担当者     ：鴫原 徹
////// 備考       ：
//void MouseCursor::UpdateTargetItem(){
	
	
//}

	
//bool MouseCursor::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
//{
//	//float fTH = 150 ;
//	//float fTW =  20 ;
//	//if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
//	//	abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
//	//	return true ;
//	//}
//	return false ;
//}

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
void MouseCursor::Draw(DrawPacket& i_DrawPacket)
{
	//multimap<float,WallItem*>::iterator it = m_ItemMap_Target.begin();
	//while(it != m_ItemMap_Target.end()){
	//	++it;
	//}
	//multimap<float,PolyItem*>::iterator it2 = m_ItemMap_Poly.begin();
	//while(it2 != m_ItemMap_Poly.end()){
	//	//テクスチャがある場合
	//	if(m_pMouseTex){
	//		m_pTexture	= m_pMouseTex;
	//		DWORD wkdword;
	//		//現在のテクスチャステータスを得る
	//		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
	//		//ステージの設定
	//		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
	//		//デフィーズ色とテクスチャを掛け合わせる設定
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	//		//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
	//		// マトリックスをレンダリングパイプラインに設定
	//		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
	//		//コモンメッシュのDraw()を呼ぶ
	//		CommonMesh::Draw(i_DrawPacket);
	//		i_DrawPacket.pD3DDevice->SetTexture(0,0);
	//		//ステージを元に戻す
	//		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	//	}
	//	else{
	//	//テクスチャがない場合
	//		// マトリックスをレンダリングパイプラインに設定
	//		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it2->second->m_Matrix);
	//		//コモンメッシュのDraw()を呼ぶ
	//		CommonMesh::Draw(i_DrawPacket);
	//	}

	//	++it2;
	//}
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
void MouseCursor::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	//if(m_pPlayerCoil == NULL){
	//	m_pPlayerCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	//}

	//m_ItemMap_Target.clear();
	//multimap<float,WallItem*>::iterator it = m_ItemMap_All.begin();
	//while(it != m_ItemMap_All.end()){
	//	if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
	//		m_ItemMap_Target.insert(multimap<float,WallItem*>::value_type(it->second->m_vPos.y,it->second));
	//	}
	//	++it;
	//}

	//multimap<float,CursorItem*>::iterator it2 = m_ItemMap_Target.begin();
	//while(it2 != m_ItemMap_Target.end()){
	//	//計算はUpdateで
	//	//拡大縮小
	//	D3DXMATRIX mScale;
	//	D3DXMatrixIdentity(&mScale);
	//	D3DXMatrixScaling(&mScale,
	//		it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
	//	//回転
	//	D3DXMATRIX mRot;
	//	D3DXMatrixIdentity(&mRot);
	//	D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
	//	//移動用
	//	D3DXMATRIX mMove;
	//	D3DXMatrixIdentity(&mMove);
	//	D3DXMatrixTranslation(&mMove,
	//		it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
	//	//ミックス行列
	//	it2->second->m_Matrix = mScale * mRot * mMove;
	//	//マティリアル設定
	//	m_Material = it2->second->m_Material;

	//	++it2;
	//}

	//multimap<float,PolyItem*>::iterator it3 = m_ItemMap_Poly.begin();
	//while(it3 != m_ItemMap_Poly.end()){
	//	//計算はUpdateで
	//	//拡大縮小
	//	D3DXMATRIX mScale;
	//	D3DXMatrixIdentity(&mScale);
	//	D3DXMatrixScaling(&mScale,
	//		it3->second->m_vScale.x,it3->second->m_vScale.y,0.0f);
	//	//回転
	//	D3DXMATRIX mRot;
	//	D3DXMatrixIdentity(&mRot);
	//	D3DXMatrixRotationQuaternion(&mRot,&it3->second->m_vRot);
	//	//移動用
	//	D3DXMATRIX mMove;
	//	D3DXMatrixIdentity(&mMove);
	//	D3DXMatrixTranslation(&mMove,
	//		it3->second->m_vPos.x,it3->second->m_vPos.y,it3->second->m_vPos.z);
	//	//ミックス行列
	//	it3->second->m_Matrix = mScale * mRot * mMove;
	//	//マティリアル設定
	//	m_Material = it3->second->m_Material;

	//	++it3;
	//}

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
}

/**************************************************************************
 Factory_Cursor 定義部
****************************************************************************/
/**************************************************************************
 Factory_Cursor::Factory_Cursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Cursor::Factory_Cursor(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE MouseDiffuse = {0.7f,0.7f,0.7f,0.0f};
		D3DCOLORVALUE MouseSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE MouseAmbient = {0.5f,0.5f,0.5f,0.0f};

		fpac->m_pVec->push_back(
			new MouseCursor( 
						fpac->pD3DDevice,
						fpac->m_pTexMgr->addTexture(fpac->pD3DDevice, L"MouseCursor.png"),
						D3DXVECTOR3(90.0f,0.0f,0.0f),
						D3DXVECTOR3(10.0f,10.0f,0.0f)
						)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Cursor::~Factory_Cursor();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Cursor::~Factory_Cursor(){
    //なにもしない
}

}
//end of namespace wiz.