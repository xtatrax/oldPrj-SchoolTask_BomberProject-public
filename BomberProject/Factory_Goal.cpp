////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Goal.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class GoalObject ;
//		class Factory_Goal ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Goal.h"
#include "BassItems.h"

namespace wiz{
/**************************************************************************
 GoalObject 定義部
****************************************************************************/
/***************************************************************************
関数名　　：GoalObject(
                   FactoryPacket* fpac,
                   LPDIRECT3DTEXTURE9 pTexture,
                   wiz::OBJID id
              )
カテゴリ　：コンストラクタ
用途　　　：
引数　　　：FactoryPacket* fpac           //デバイスなど
　　　　　：LPDIRECT3DTEXTURE9 pTexture   //テクスチャ―
　　　　　：wiz::OBJID id                 //ID
戻り値　　：
担当者　　：佐藤涼
備考　　　：
****************************************************************************/
GoalObject::GoalObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pCoil(NULL)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//再スロー
		throw;
	}
}

/**************************************************************
関数名　　：void GoalObject::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
<<<<<<< HEAD
引数　　　：DrawPacket &i_DrawPacket   //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
=======
>>>>>>> workspace
***************************************************************/
void	GoalObject::Draw(DrawPacket &i_DrawPacket){
	multimap<float,GoalItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}

/*******************************************************************
<<<<<<< HEAD
関数名　　：void GoalObject::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket  //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
=======
関数名     ：void	 GoalObject::Update(UpdatePacket& i_UpdatePacket)
用途       ：データ更新
>>>>>>> workspace
********************************************************************/
void	GoalObject::Update(UpdatePacket& i_UpdatePacket)
{
	multimap<float,GoalItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		//計算はUpdateで
		//拡大縮小
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it->second->m_vScale.x,it->second->m_vScale.y,it->second->m_vScale.z);
		//回転
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it->second->m_vRot);
		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it->second->m_vPos.x,it->second->m_vPos.y,it->second->m_vPos.z);
		//ミックス行列
		it->second->m_Matrix = mScale * mRot * mMove;
		//マティリアル設定
		m_Material = it->second->m_Material;

		//衝突判定
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec, typeid(PlayerCoil) ) ;
		if( m_pCoil && m_pCoil->HitTestWall( it->second->m_Obb, 0) ){
			//it->second->m_vPos	= g_vMin;
		}

		++it;
	}
}

/*******************************************************************
<<<<<<< HEAD
関数名　　：void GoalObject::addGoal(
                     D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
                     D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
              )
カテゴリ　：関数
用途　　　：ゴールの追加
引数　　　：D3DXVECTOR3 &vScale
　　　　　：D3DXVECTOR3 &vRot
　　　　　：D3DXVECTOR3 &vPos
　　　　　：D3DCOLORVALUE& Diffuse
　　　　　：D3DCOLORVALUE& Specular
　　　　　：D3DCOLORVALUE& Ambient
戻り値　　：
担当者　　：佐藤涼
備考　　　：
=======
関数名     ：void	 GoalObject::addGoal(
						D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
						D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
					)
用途       ：ゴールの追加
>>>>>>> workspace
********************************************************************/
void GoalObject::addGoal(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	GoalItem* pItem = new GoalItem;
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
	pItem->m_Obb.m_Center = vPos;
	pItem->m_Obb.m_Size = vScale * 0.5f;
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixRotationYawPitchRoll(&mRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	pItem->m_Obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
    pItem->m_Obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
    pItem->m_Obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);

	m_ItemMap_All.insert(multimap<float,GoalItem*>::value_type(pItem->m_vPos.y,pItem));	
}

<<<<<<< HEAD
=======
/*****************************************************************
関数名	：void Will::GetOBB( size_t Index, OBB& obb )
用途	：指定のインデックスの現在のOBBを得る
******************************************************************/
void GoalObject::GetOBBList( float Index, list<OBB>& ObbList ){
    //指定の配置オブジェクトを検証
	multimap<float,GoalItem*>::iterator itBegin = m_ItemMap_All.lower_bound( 20.0f ) ;
	multimap<float,GoalItem*>::iterator itEnd	= m_ItemMap_All.upper_bound( 20.0f ) ;
	OBB obb ; 
	for(multimap<float,GoalItem*>::iterator iter = itBegin; iter != itEnd; ++iter){
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

>>>>>>> workspace
/**************************************************************************
 Factory_Goal 定義部
****************************************************************************/
/**************************************************************************
 Factory_Goal::Factory_Goal(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Goal::Factory_Goal(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE GoalDiffuse = {0.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE GoalSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE GoalAmbient = {0.0f,1.0f,0.0f,1.0f};

		GoalObject* gl = new GoalObject(fpac->pD3DDevice,NULL);
<<<<<<< HEAD
		//gl->addGoal(	D3DXVECTOR3( 10.0f, 3.0f, 1.0f ),
		//				g_vZero,
		//				D3DXVECTOR3( 20.0f, 20.0f, 0.0f ),
		//				GoalDiffuse,
		//				GoalSpecular,
		//				GoalAmbient);
=======
		gl->addGoal(	D3DXVECTOR3( 3.0f, 1.0f, 1.0f ),
						g_vZero,
						D3DXVECTOR3( 35.0f, 20.0f, 0.0f ),
						GoalDiffuse,
						GoalSpecular,
						GoalAmbient);
>>>>>>> workspace

		fpac->m_pVec->push_back(gl);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Goal::~Factory_Goal();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Goal::~Factory_Goal(){
    //なにもしない
}

}
//end of namespace wiz.
