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
						D3DCOLORVALUE(),
						pTexture
	)

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
関数名　　：void Item::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket          // 描画用のもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
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
関数名　　：void Item::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket  // 更新用データもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{
	vector<Object*> Vec	= 	*(i_UpdatePacket.pVec);
	PlayerCoil*	pc	= NULL;
	Bar*		br	= NULL;

	if( !pc ) pc = (PlayerCoil*)SearchObjectFromTypeID(&Vec,typeid(PlayerCoil));
	if( !br ) br = (Bar*)SearchObjectFromTypeID(&Vec,typeid(Bar));

	//コイルの位置取得
	D3DXVECTOR3	cPos	= pc->getPos();

	Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_All.size());
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		//	: 自分から対象までのベクトルを算出
		D3DXVECTOR3	vTargetDir	= cPos - (it->second->m_Pos) ;

		//	: 自分と対象までの距離を求める
		double dirX = vTargetDir.x * vTargetDir.x;
		double dirY = vTargetDir.y * vTargetDir.y;
		it->second->m_fDistance	 = (float)sqrt(dirX + dirY);

		//距離が5以内ならよっていく
		if( it->second->m_fDistance < SuctionArea ){
			it->second->m_Pos	+= vTargetDir/**SpeedRate*/ * pc->getSpeed();

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
関数名　：void Item::addItem(
                      D3DXVECTOR3 pos,
                      D3DXVECTOR3 size,
                      D3DCOLORVALUE Diffuse,
                      D3DCOLORVALUE Specular, 
                      D3DCOLORVALUE Ambient)
カテゴリ：関数
用途　　：アイテムの追加
引数　　：D3DXVECTOR3 pos          //描画位置
　　　　：D3DXVECTOR3 size         //大きさ
　　　　：D3DCOLORVALUE Diffuse    //
　　　　：D3DCOLORVALUE Specular   //
　　　　：D3DCOLORVALUE Ambient    //
戻り値　：
担当者　：佐藤涼
備考　　：
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
                LPDIRECT3DDEVICE9 pD3DDevice,
                LPDIRECT3DTEXTURE9 pTex,
                D3DXVECTOR3 &vScale,
                D3DXVECTOR3 &vRot,
                D3DXVECTOR3 &vPos,
                D3DXVECTOR3 &vDirOffset,
                RECT* vRect,
                wiz::OBJID id
				)
カテゴリ：コンストラクタ
用途　　：LPDIRECT3DDEVICE9 pD3DDevice   // デバイス
引数　　：LPDIRECT3DTEXTURE9 pTex        // テクスチャ―
　　　　：D3DXVECTOR3 &vScale            // 伸縮
　　　　：D3DXVECTOR3 &vRot              // 回転
　　　　：D3DXVECTOR3 &vPos              // 位置
　　　　：D3DXVECTOR3 &vDirOffset        // 描画オフセット
　　　　：RECT* vRect                    // 描画範囲
　　　　：wiz::OBJID id                  // ID
戻り値　：
担当者　：佐藤涼
備考　　：
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
関数名　　：void Bar::Recovery()
カテゴリ　：関数
用途　　　：エネルギー回復
引数　　　：
戻り値　　：
担当者　　：佐藤涼
備考　　　：
*****************************************/
void Bar::Recovery(){
	if(m_pRect->right<500){
		m_pRect->right	+= 5;
		if(m_pRect->right>500)
			m_pRect->right	= 500;
	}
}
/*****************************************
 関数名　　：void Bar::Consume()
 カテゴリ　：関数
 用途　　　：エネルギー消費
 引数　　　：
 戻り値　　：
 担当者　　：佐藤涼
 備考　　　：
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
関数名　　：void Item::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket    //描画用のデータもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
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
関数名　　：Factory_Item::Factory_Item( FactoryPacket* fpac );
カテゴリ　：コンストラクタ
用途　　　：
引数　　　：FactoryPacket* fpac     // もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
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
				D3DXVECTOR3(300.0f,550.0f,0.0f),
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
 関数名　　：Factory_Item::~Factory_Item();
 カテゴリ　：デストラクタ
 用途　　　：
 引数　　　：
 戻り値　　：
 担当者　　：佐藤涼
 備考　　　：
***************************************************************************/
Factory_Item::~Factory_Item(){
    //なにもしない
}

}
//end of namespace wiz.
