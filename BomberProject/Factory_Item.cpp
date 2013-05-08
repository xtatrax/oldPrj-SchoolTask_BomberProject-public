////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Item.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{

	Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),pTexture)

{
	try{
		D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//再スロー
		throw;
	}
}

Item::~Item(){
}

/********************************************
	用途：描画
********************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	// マトリックスをレンダリングパイプラインに設定
	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
	CommonMesh::Draw(i_DrawPacket);
}

void	Item::Update(UpdatePacket& i_UpdatePacket){
	//コイルのポインタを取得
	vector<Object*> Vec	= 	*(i_UpdatePacket.pVec);
	PlayerCoil*	pc	= NULL;
	Bar*		br	= NULL;
	vector<Object*>::size_type sz2 = Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(PlayerCoil)){
			pc = dynamic_cast<PlayerCoil*>(Vec[i]);
			break;
		}
	}
	for(vector<Object*>::size_type i = 0;i < sz2;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(Bar)){
			br = dynamic_cast<Bar*>(Vec[i]);
			break;
		}
	}

	D3DXVECTOR3	cPos	= pc->getPos();	//コイルの位置取得

	vector<BallItem>::size_type sz = m_ItemVec.size();
	for(vector<BallItem>::size_type i = 0; i < sz; i++){

		D3DXVECTOR3	vTargetDir	= cPos - m_ItemVec[i]->m_Pos ;		//	: 自分から対象までのベクトルを算出

		double dirX = vTargetDir.x * vTargetDir.x;
		double dirY = vTargetDir.y * vTargetDir.y;
		float fDistance	 = (float)sqrt(dirX + dirY);	//	: 自分と対象までの距離を求める

		//距離が100いないならよっていく
		if( fDistance < 100.0f ){
			m_ItemVec[i]->m_Pos	+= vTargetDir*0.0005f;

			if( m_ItemVec[i]->m_Pos == cPos ){
				br->Recovery();
				SAFE_DELETE( this->m_ItemVec[i] );
			}
		}
		//移動用
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			m_ItemVec[i]->m_Size.x,m_ItemVec[i]->m_Size.y,m_ItemVec[i]->m_Size.z);

		//マティリアル設定
		m_Material = m_ItemVec[i]->m_Material;
		m_mMatrix	= mScale * mMove;
	}
}

/***********************************************
	用途：追加
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_Size = size;
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemVec.push_back(bItem);
	}
	catch(...){
		throw;
	}
}

/***************************************
	用途：コイルに吸い付く
***************************************/
void	Item::Suction(){
}

/**************************************************************************
 Bar 定義部
***************************************************************************/
Bar::Bar(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pTex,			//	: コア部分のTexture
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	D3DXVECTOR3 &vDirOffset,					//	: 方向を表す三角の描画オフセット
	RECT* vRect,							//	: 描画範囲
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTex,vScale,vRot,vPos,
	vRect,g_vZero,vDirOffset,0xFFFFFFFF,id),m_Time(0)

{
}

void Bar::Recovery(){
	if(m_pRect->right<500){
		m_pRect->right	+= 5;
		if(m_pRect->right>500)
			m_pRect->right	= 500;
	}
}

void Bar::Consume(){
	if(m_pRect->right > 0){
		m_pRect->right	-= 3;
		if(m_pRect->right > 0){
			m_pRect->right	= 0;
		}
	}
}

void Bar::Draw(DrawPacket& i_DrawPacket){
	//Recovery();
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
        D3DCOLORVALUE BallDiffuse = {1.0f,1.0f,1.0f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.5f,0.5f,0.0f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);

		it->addItem(D3DXVECTOR3(-1.0f,0.0f,0.0f),
					D3DXVECTOR3(1.0f,1.0f,1.0f),
					BallDiffuse,
					BallSpecular,
					BallAmbient);
		fpac->m_pVec->push_back(it);

		fpac->m_pVec->push_back(
			new Bar(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"front_bar.png" ),
				D3DXVECTOR3(0.8f,0.8f,1.0f),
				g_vZero,
				D3DXVECTOR3(300.0f,450.0f,0.0f),
				g_vZero,
				Rect(0,0,200,50)
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
