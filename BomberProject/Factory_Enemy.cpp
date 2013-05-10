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
#include "BassItems.h"

namespace wiz
{
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
	EnemySphere::~EnemySphere()
	{
		//後始末
		SafeRelease(m_pMesh);
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
//// 備考       ：
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void EnemySphere::AddEnemy(D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, D3DCOLORVALUE &Diffuse,D3DCOLORVALUE &Specular, D3DCOLORVALUE &Ambient)
	{
		EnemyItem* pItem = new EnemyItem;
		pItem->m_vScale = vScale;
		pItem->m_vPos = vPos;
		::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
		pItem->m_Material.Diffuse = Diffuse;
		pItem->m_Material.Specular = Specular;
		pItem->m_Material.Ambient = Ambient;

	//回転の初期化
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

		m_ItemMap_All.insert(multimap<float, EnemyItem*>::value_type(pItem->m_vPos.y,pItem));	
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
		D3DCOLORVALUE EnemyDiffuse = {1.0f,1.0f,1.0f,1.0f};
		D3DCOLORVALUE EnemySpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE EnemyAmbient = {1.0f,1.0f,1.0f,1.0f};
		
//		fpac->m_pVec->push_back(new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,NULL)));
		EnemySphere* Enemy = new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Enemy.jpg"));
		Enemy->AddEnemy(D3DXVECTOR3( 0.2f, 0.2f, 0.2f ),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXVECTOR3( 200.0f, 200.0f, 0.0f ),
					  EnemyDiffuse,
					  EnemySpecular,
					  EnemyAmbient);
	
		fpac->m_pVec->push_back(Enemy);
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
}
//end of namespace wiz.