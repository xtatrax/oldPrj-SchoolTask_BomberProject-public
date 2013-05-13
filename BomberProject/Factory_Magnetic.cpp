////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Magnetic ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Magnetic.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
Camera*		MagneticumObject3D::m_pCamera = NULL;	

/**************************************************************************
 MagneticumObject 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
MagneticumObject::MagneticumObject(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	RECT* pRect,								//	: 描画範囲
	Color color ,								//	: 色
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos( vPos )
,m_vScale( vScale )
,m_bMagnetPole( POLE_S )
{
}

/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticumObject::Update( UpdatePacket& i_UpdatePacket ){

};



//3D変換用
/**************************************************************************
 MagneticumObject3D 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：MagneticumObject3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：曳地 大洋
//// 備考       ：
////            ：
////
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
	wiz::OBJID id 								//	: ID
)
:PrimitiveCylinder(
				   pD3DDevice,
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   id,
				   pTexture)
,m_bMagnetPole( POLE_S )
,m_fMagneticum(MGPRM_MAGNETICUM_QUAD)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	m_pMagneticField	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 8.0f,8.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
	m_pMagneticField2	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 3.0f,3.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
	m_pMagneticField3	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 1.5f,1.5f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
}

/////////////////// ////////////////////
//// 用途       ：MagneticumObject3D(
////									LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////									float Radius1,float Radius2,float Lenght,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////									D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////									wiz::OBJID id = OBJID_3D_MAGNET) ;
//// カテゴリ   ：コンストラクタ
//// 用途       ：Player用のコンストラクタ
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
////		      :   Radius1						//円の直径1
////		      :   Radius2						//円の直径2
////			  :   Lenght						//高さ
////		      :   D3DXVECTOR3 &vRot				//回転角
////		      :   D3DXVECTOR3 &vPos				//位置
////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
//// 戻値       ：無し
//// 担当者     ：本多寛之
//// 備考       ：
////	
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTexture,
	float Radius1,
	float Radius2,
	float Lenght,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DCOLORVALUE& Diffuse,
	D3DCOLORVALUE& Specular,
	D3DCOLORVALUE& Ambient,
	wiz::OBJID id) 
:PrimitiveCylinder(
		   pD3DDevice,pTexture,
		   Radius1,Radius2,Lenght,
		   vRot,vPos,
		   Diffuse,Specular,Ambient,
		   id)
,m_bMagnetPole( POLE_N )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	m_pMagneticField	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 4.0f,4.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////			   ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////			   ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////			   ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////               ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
void MagneticumObject3D::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
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
		m_pMagneticField->Draw(i_DrawPacket);
		m_pMagneticField2->Draw(i_DrawPacket);
		m_pMagneticField3->Draw(i_DrawPacket);

		++it;
	}
}


/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticumObject3D::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	m_ItemMap_Target.clear();
	multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		if( ((it->first - m_pCamera->getEye().y) <= 13) && ((it->first - m_pCamera->getEye().y) >= -13) /*&&
			((it->first - m_pCamera->getEye().x) <= 15) && ((it->first - m_pCamera->getEye().x) >= -15)*/ ){
			m_ItemMap_Target.insert(multimap<float,Magnet3DItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}
	multimap<float,Magnet3DItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){
		//計算はUpdateで
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

		//m_pMagneticField->Update(i_UpdatePacket);
		
		++it2;
	}
}

/////////////////// ////////////////////
//// 用途       ：void AddMagnetic( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：マグネットの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
void MagneticumObject3D::AddMagnetic(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem = new Magnet3DItem ;
	pItem->m_vScale = vScale ;
	pItem->m_vPos	= vPos ;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9)) ;
	pItem->m_Material.Diffuse  = Diffuse ;
	pItem->m_Material.Specular = Specular ;
	pItem->m_Material.Ambient  = Ambient ;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z)) ;

	m_ItemMap_All.insert(multimap<float,Magnet3DItem*>::value_type(pItem->m_vPos.y,pItem));	
}


/**************************************************************************
 Factory_Magnetic 定義部
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	Factory_Magnetic *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
//Factory_Magnetic::Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
//					 TextureManager& TexMgr){
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
		// シリンダーオブジェクトのマテリアル
		D3DCOLORVALUE MagnetDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		D3DCOLORVALUE MagnetSpecular = { 0.0f, 0.0f, 0.0f, 0.0f } ;
		D3DCOLORVALUE MagnetAmbient  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		// 磁界の表示
		MagneticumObject3D* Magnet = new MagneticumObject3D(
			fpac->pD3DDevice,
			NULL//fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"ddn.jpg")
		);
		fpac->m_pVec->push_back(Magnet);

		//Magnet->AddMagnetic(D3DXVECTOR3(10.0f,10.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(10.0f,10.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(1.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(2.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(3.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(4.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(5.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(6.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(7.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(8.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(9.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(10.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(11.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(12.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(13.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(14.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(15.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(16.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(17.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(18.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(19.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(21.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(22.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(23.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(24.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(25.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(26.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(27.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(28.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(29.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(31.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(32.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(33.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(34.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(35.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(36.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(37.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(38.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(39.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(40.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Magnetic::~Factory_Magnetic();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Magnetic::~Factory_Magnetic(){
    //なにもしない
}

}
//end of namespace wiz.
