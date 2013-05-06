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
	//// 関数名     ：void EnemySphere::Vec2UV(float x,float y,float z,float r,float& u,float& v );
	//// カテゴリ   ：メンバ関数
	//// 用途       ：VectorをUとVにコンバート
	//// 引数       ：  float x     //xの値
	////            ：  float y     //yの値
	////            ：  float z     //zの値
	////            ：  float r     //球の半径
	////            ：  float& u    //変換するu（テクスチャ上のU座標）
	////            ：  float& v    //変換するv（テクスチャ上のV座標）
	//// 戻値       ：なし
	//// 担当者     ： (山ノ井先生のひな形より)
	//// 備考       ：float& uとfloat& vに変換後の値を代入
	////            ：
	////
	void EnemySphere::Vec2UV(float x,float y,float z,float r,float& u,float& v) 
	{
		float q ;
		float q2;
		q = atan2(z,x);
		u = q / (2.0f * D3DX_PI);
		q2 = asin(y / r);
		v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
		if( u > 1.0f)
			u = 1.0f;
	}
	/////////////////// ////////////////////
	//// 関数名     ：void EnemySphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// カテゴリ   ：関数
	//// 用途       ：球を生成
	//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
	//// 戻値       ：なし
	//// 担当者     ：斎藤　謙吾(山ノ井先生のひな形より)
	//// 備考       ：float& uとfloat& vに変換後の値を代入
	////            ：
	////
	void EnemySphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	{
		try
		{
			

		
				//球の作成
			if(
				FAILED(
					D3DXCreateSphere(
						pD3DDevice, 
						30.0f,//球の大きさ
						18,
						18,
						&m_pMesh, 
						NULL
					)
				)
			)
			{
				// 初期化失敗
				throw BaseException(
					L"球の作成に失敗しました。",
					L"EnemySphere::EnemySphere"
					);
			}
			if(m_pTexture)
			{
				//テクスチャメッシュ
				LPD3DXMESH pMesh2 = 0;
				//作成されたメッシュを元に、テクスチャつきのメッシュを作成
				if(FAILED(m_pMesh->CloneMeshFVF(NULL,BallFVF,pD3DDevice,&pMesh2)))
				{
					// 初期化失敗
					throw BaseException(
						L"テクスチャ付の球の作成に失敗しました。",
						L"EnemySphere::EnemySphere"
						);
				}
				//この段階でm_pMeshはいらないから削除
				SafeRelease(m_pMesh);
				//新しいメッシュを代入
				m_pMesh = pMesh2;
				//テクスチャ上の座標をマッピング
				LPDIRECT3DVERTEXBUFFER9 pVB = 0;
				SphereVertex* pVer = 0;
				m_pMesh->GetVertexBuffer(&pVB);
				pVB->Lock(0,0,(VOID**)&pVer,0);
				for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++)
				{ //頂点の数を取得する
					float u,v;
					Vec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,1.0f,u,v);
					pVer[n].tu=u;
					pVer[n].tv=v;
				}
				pVB->Unlock();
			}
			//クオータニオンの初期化
			//D3DXQuaternionRotationYawPitchRoll(&m_Qtn,0,0,0);
		}
		catch(...)
		{
			//コンストラクタ例外発生
			//後始末
			SafeRelease(m_pMesh);
			//再スロー
			throw;
		}
	};

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
	EnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,
			   D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			   LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
		//継承元をこんな感じで書く。型は変数だけ。
		: PrimitiveSphere( pD3DDevice,
			    Diffuse, Specular, Ambient, pTexture)
				,Object(id)
				,m_pTexture(pTexture)
	{
		try
		{
			EnemySphere* Sphere = new EnemySphere( pD3DDevice, Diffuse, Specular, Ambient, pTexture, id);

			CreateSphere(pD3DDevice);
		}
		catch(...)
		{
			//再スロー
			throw;
		}

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
		//テクスチャがあった場合
		if(m_pTexture)
		{
			//テクスチャ描画命令
			DWORD wkdword;
			//現在のテクスチャステータスを得る
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//ステージの設定
			i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
			//デフィーズ色とテクスチャを掛け合わせる設定
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			i_DrawPacket.pD3DDevice->SetFVF(BallFVF);

			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else
		{
			//テクスチャがない場合

			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
	}
}