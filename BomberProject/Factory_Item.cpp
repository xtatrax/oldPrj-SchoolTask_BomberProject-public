////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Item ;
//		class Bar ;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
/**************************************************************************
 Item 定義部
****************************************************************************/
/***************************************************************************
関数名     ：Item( FactoryPacket* fpac,			//	: デバイスなど
					 LPDIRECT3DTEXTURE9 pTexture,	//	: テクスチャ―
					 wiz::OBJID id )				//	: ID
用途       ：コンストラクタ
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),pTexture)

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
関数名     ：void	 Item::Draw(DrawPacket &i_DrawPacket)
用途       ：オブジェクトの描画
***************************************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}

/*******************************************************************
関数名     ：void	 Item::Update(UpdatePacket& i_UpdatePacket)
用途       ：データ更新
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{
	vector<Object*> Vec	= 	*(i_UpdatePacket.pVec);
	PlayerCoil*	pc	= NULL;
	Bar*		br	= NULL;
	vector<Object*>::size_type sz2 = Vec.size();
	//コイルのポインタを取得
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(PlayerCoil)){
			pc = dynamic_cast<PlayerCoil*>(Vec[i]);
			break;
		}
	}
	//バーのポインタを取得
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(Bar)){
			br = dynamic_cast<Bar*>(Vec[i]);
			break;
		}
	}
	//コイルの位置取得
	D3DXVECTOR3	cPos	= pc->getPos();

	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		//	: 自分から対象までのベクトルを算出
		D3DXVECTOR3	vTargetDir	= cPos - (it->second->m_Pos) ;

		//	: 自分と対象までの距離を求める
		double dirX = vTargetDir.x * vTargetDir.x;
		double dirY = vTargetDir.y * vTargetDir.y;
		it->second->m_fDistance	 = (float)sqrt(dirX + dirY);

		//Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_All.size());
		//距離が5以内ならよっていく
		if( it->second->m_fDistance < SuctionArea ){
			it->second->m_Pos	+= vTargetDir*SpeedRate;

			//プレイヤーと限りなく近くなったら、消滅
			if( it->second->m_fDistance < VanishArea ){
				//エネルギー回復
				br->Recovery();
				SafeDelete( it->second );
				it = m_ItemMap_All.erase( it );
			}
		}
		//移動用
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it->second->m_Pos.x,it->second->m_Pos.y,it->second->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			it->second->m_Size.x,it->second->m_Size.y,it->second->m_Size.z);

		//マティリアル設定
		m_Material = it->second->m_Material;
		it->second->m_mMatrix	= mScale * mMove;

		it++;
	}
}

/***********************************************
関数名 : void	Item::addItem(
					D3DXVECTOR3 pos,		//	: 描画位置
					D3DXVECTOR3 size,		//	: 伸縮
					D3DCOLORVALUE Diffuse,	//	: 
					D3DCOLORVALUE Specular,	//	: 
					D3DCOLORVALUE Ambient)	//	: 
用途   : アイテムの追加
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_Size = size;
		bItem->m_fDistance = 6.0f;
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemMap_All.insert(multimap<float,BallItem*>::value_type(bItem->m_Pos.y,bItem));
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
 Bar 定義部
***************************************************************************/
/************************************************************************
 関数名     ：Bar::Bar(
				LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
				LPDIRECT3DTEXTURE9 pTex,		//	: テクスチャ―
				D3DXVECTOR3 &vScale,			//	: 伸縮
				D3DXVECTOR3 &vRot,				//	: 回転
				D3DXVECTOR3 &vPos,				//	: 位置
				D3DXVECTOR3 &vDirOffset,		//	: 描画オフセット
				RECT* vRect,					//	: 描画範囲
				wiz::OBJID id 					//	: ID
				)
用途       ：コンストラクタ
*************************************************************************/
Bar::Bar(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTex,
	D3DXVECTOR3 &vScale,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DXVECTOR3 &vDirOffset,
	RECT* vRect,
	wiz::OBJID id
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id),m_Time(0)

{
}

/****************************************
関数名     ：void Bar::Recovery()
用途       ：エネルギー回復
*****************************************/
void Bar::Recovery(){
	if(m_pRect->right<500){
		m_pRect->right	+= 5;
		if(m_pRect->right>500)
			m_pRect->right	= 500;
	}
}
/*****************************************
 関数名     ：void Bar::Consume()
 用途       ：エネルギー消費
 *****************************************/
void Bar::Consume(){
	if(m_pRect->right > 0){
		m_pRect->right	-= 3;
		if(m_pRect->right > 0){
			m_pRect->right	= 0;
		}
	}
}

/**************************************************************
関数名     ：void	 Item::Draw(DrawPacket &i_DrawPacket)
用途       ：オブジェクトの描画
***************************************************************/
void Bar::Draw(DrawPacket& i_DrawPacket){
	if(m_pRect->right != 500)
		m_Time	+= 1;

	if(m_Time >= 60){
		m_pRect->right	+= 1;
		m_Time	= 0;
	}
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 Factory_Item 定義部
****************************************************************************/
/**************************************************************************
 Factory_Item::Factory_Item(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				it->addItem(D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.05f))+1.5f,
										(float(j)*2.75f+float(rand()%100*0.05f))+1.5f,0.0f),
							D3DXVECTOR3(0.5f,0.5f,0.5f),
							BallDiffuse,
							BallSpecular,
							BallAmbient);
			}
		}
		fpac->m_pVec->push_back(it);

		fpac->m_pVec->push_back(
			new Bar(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"front_bar.png" ),
				D3DXVECTOR3(0.8f,0.8f,1.0f),
				g_vZero,
				D3DXVECTOR3(300.0f,450.0f,0.0f),
				g_vZero,
				Rect(0,0,200,20)
			)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Item::~Factory_Item();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Item::~Factory_Item(){
    //なにもしない
}

}
//end of namespace wiz.
