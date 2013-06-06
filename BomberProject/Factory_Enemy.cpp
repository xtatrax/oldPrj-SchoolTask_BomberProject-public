////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Enemy.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Enemy ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Enemy.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 EnemySphere 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：EnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            ：  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  D3DCOLORVALUE& Diffuse,         //ディフューズ色
////            ：  D3DCOLORVALUE& Specular,            //スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,          //アンビエント色
////            ：  LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////

//CPPでのコンストラクタの書き方。
EnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
//継承元をこんな感じで書く。型は変数だけ。
	: PrimitiveSphere( pD3DDevice,
					   Diffuse,
					   Specular,
					   Ambient,
					   pTexture)
,m_pCamera( NULL )
,m_pPlayer( NULL )
,m_pCoil( NULL )
,m_bReset( false )

{
	
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	
}

/////////////////// ////////////////////
//// 関数名     ：voidEnemySphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：球体を描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
void EnemySphere::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,EnemyItem*>::iterator it = m_ItemMap_Target.begin();
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
//// 担当者     ：斎藤謙吾
//// 備考       
////            ：
////

void EnemySphere::Update( UpdatePacket& i_UpdatePacket){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		
	}
	if( !m_pPlayer ){
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromTypeID( i_UpdatePacket.pVec,typeid(ProvisionalPlayer3D));
	}
	if( !m_pCoil ){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	const float EnemyMove = 0.1f;


	m_ItemMap_Target.clear();

	multimap<float,EnemyItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){

		float DeadLine  = (float)TwoPointToBassLength( it->second->m_vPos, m_pCoil->getPos() ) ;
		//エネミーの座標を磁界の方に持っていく処理
		//if( g_bMouseRB || g_bMouseLB && m_pPlayer){
		if( m_pPlayer && m_pPlayer->getDrawing() ){
			if( m_pPlayer->getMagnetPole() != it->second->m_bPole ){

				float	pole	= 1.0f;
				if( m_pPlayer->getMagnetPole() )
						pole	=  -1.0f;

				float Lng  = (float)TwoPointToBassLength( it->second->m_vPos, m_pPlayer->getPos() ) ;

				if( Lng < MGPRM_MAGNETICUM_QUAD ){
					D3DXVECTOR3	v	= ( it->second->m_vPos - m_pPlayer->getPos() ) / 30 ;

					it->second->m_vPos	+= v * pole;
				}

				//if( it->second->m_vPos.x <= m_pPlayer->getPos().x ){
				//	it->second->m_vPos.x += EnemyMove * pole;
				//}
				//if( it->second->m_vPos.x >= m_pPlayer->getPos().x ){
				//	it->second->m_vPos.x -= EnemyMove * pole;
				//
				//}

				//if( it->second->m_vPos.y <= m_pPlayer->getPos().y ){
				//	it->second->m_vPos.y += EnemyMove * pole;
				//}
				//if( it->second->m_vPos.y > m_pPlayer->getPos().y ){
				//	it->second->m_vPos.y -= EnemyMove * pole;
				//}

			}
		}
		
		if( ( +(it->first - m_pCamera->getEye().y) <= 3000) && ( +(it->first - m_pCamera->getEye().y) >= -3000 ) ){
			
			m_ItemMap_Target.insert(multimap<float,EnemyItem*>::value_type(it->second->m_vPos.y,it->second));
		
		}

		if( DeadLine < 0.5f ){
			m_pCoil->setState(COIL_STATE_DEAD);
			m_bReset	= true;
		}

		++it;
	}


	multimap<float,EnemyItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		if( m_bReset ){
			it2->second->m_vPos	= it2->second->m_vStartPos;
		}
		//計算はUpdateで

		//拡大縮小
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);

		//回転
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);

		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);

		//ミックス行列
		it2->second->m_Matrix = mScale * mRot * mMove;

		//マティリアル設定
		m_Material = it2->second->m_Material;

		++it2;
	}

	m_bReset	= false;
}

/////////////////// ////////////////////
//// 用途       ：void AddEnemy( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：Enemyの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：斎藤謙吾
//// 備考       ：
//////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySphere::AddEnemy(D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, D3DCOLORVALUE &Diffuse,D3DCOLORVALUE &Specular, D3DCOLORVALUE &Ambient){

	EnemyItem* pItem = new EnemyItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos = vPos;
	pItem->m_vStartPos = vPos;
	::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	pItem->m_Material.Diffuse = Diffuse;
	pItem->m_Material.Specular = Specular;
	pItem->m_Material.Ambient = Ambient;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	int	i	= rand()%1000;
	if( i < 500 )	pItem->m_bPole	= POLE_N;
	else		pItem->m_bPole	= POLE_S;

	m_ItemMap_All.insert(multimap<float, EnemyItem*>::value_type(pItem->m_vPos.y,pItem));	
}

/////////////////// ////////////////////
//// 関数名     ：EnemySphere::~EnemySphere();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
EnemySphere::~EnemySphere(){
	m_pCamera	= NULL ;
	m_pPlayer	= NULL ;
	m_pCoil		= NULL ;

	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();
}

/**************************************************************************
 Factory_Enemy 定義部
****************************************************************************/
/**************************************************************************
 Factory_Enemy::Factory_Enemy(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Enemy::Factory_Enemy(FactoryPacket* fpac){
	try{
		//D3DCOLORVALUE EnemyDiffuse = {1.0f,1.0f,1.0f,1.0f};
		//D3DCOLORVALUE EnemySpecular = {1.0f,1.0f,1.0f,1.0f};
		//D3DCOLORVALUE EnemyAmbient = {1.0f,1.0f,1.0f,1.0f};
		//
		//			fpac->m_pVec->push_back(new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,NULL)));
		//EnemySphere* Enemy = new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Enemy.jpg"));
		//for(int i = 0; i < 3; i++){
		//	for(int j = 0; j < 3; j++){
		//		Enemy->AddEnemy(D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),     //スケール
		//						D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),     //角度
		//						D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.3f))+1.5f,
		//									(float(j)*2.75f+float(rand()%100*0.2f))+1.5f,0.0f),   //ポジション
		//						EnemyDiffuse,
		//						EnemySpecular,
		//						EnemyAmbient
		//		);
		//	}
		//}
		//fpac->m_pVec->push_back(Enemy);

	}
	catch(...){
		//再throw
		throw;
	}
}

/**************************************************************************
 Factory_Enemy::~Factory_Enemy();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_Enemy::~Factory_Enemy(){
//なにもしない
	}
}//end of namespace bomberobject.
}//end of namespace wiz.