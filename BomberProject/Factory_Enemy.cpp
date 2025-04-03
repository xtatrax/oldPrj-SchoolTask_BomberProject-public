////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Enemy.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：斎藤　謙吾
//	引き継ぎ		：本多寛之
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
 EnemyModel 定義部
***************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：EnemyModel::EnemyModel(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            ：  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPTATRATEXTURE pTexture = 0);
//// カテゴリ   ：コンストラクタ
//// 用途       ：球体を作成
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
////            ：  D3DCOLORVALUE& Diffuse,         //ディフューズ色
////            ：  D3DCOLORVALUE& Specular,            //スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,          //アンビエント色
////            ：  LPTATRATEXTURE pTexture = 0	//テクスチャを張るときは指定
//// 戻値       ：なし（失敗時は例外をthrow）
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////

//CPPでのコンストラクタの書き方。
EnemyModel::EnemyModel(  BassPacket& Packet,const char *pFileName ,const wiz::OBJID id)
//継承元をこんな感じで書く。型は変数だけ。
//:SimpleCommonMesh(g_vZero,g_vZero,COLOR2D3DCOLORVALUE(-1),COLOR2D3DCOLORVALUE(-1),COLOR2D3DCOLORVALUE(-1),id )
:Object(id)
,m_pCamera( NULL )
,m_pPlayer( NULL )
,m_pCoil( NULL )
,m_pMesh( NULL )
,m_bReset( false )
{
	try{
		// Xファイルからメッシュをロードする 
		//LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		//DWORD dwMQty;
		LPDIRECT3DDEVICE9 pDevice = Packet.GetDevice();
		if(FAILED(D3DXLoadMeshFromXA(pFileName,
								D3DXMESH_MANAGED,
								pDevice,
								NULL,
								NULL,
								NULL,
								NULL,
								&m_pMesh))){
			string	 buf1 = pFileName ;
			wstring  buf2 ;
			TLIB::widen(buf1,buf2);
			wstring msg  = wstring(L"モデルデータ\"") + buf2 + wstring(L"\"を読み込めませんでした");
			// 初期化失敗
            throw BaseException(
				msg.c_str(),
                L"LoadMeshFromX::LoadMeshFromX()"
            );
        }
		//
		//////////
		//	: テクスチャ名をワイド化
		//wstring wsTexName  ;
		//wchar_t* wpTexName = NULL;
		//if(pTexName){
		//	wpTexName = new wchar_t[ strlen(pTexName) +1 ];
		//	size_t ret;
		//	mbstowcs_s(&ret, wpTexName, strlen(pTexName) +1, pTexName, strlen(pTexName) +1);
		//}
		//
		//////////

		//TLIB::widen(sFileDir,wsFileDir);

		//m_pTex = Packet.AddTexture( L"DeadPerticul.png");
		m_pDeadEffect	= new DeadEffect( Packet.GetDevice(), Packet.AddTexture( L"DeadPerticul.png"), g_vOne ); 

		//D3DXMATERIAL d3dxMaterials = *(D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		//m_MaterialItems.init(pD3DDevice,pD3DXMtrlBuffer,dwMQty,TexMgr,g_sDefaultTexturePath.c_str(),wpTexName);
		//m_BassMesh.m_AABB = AABB(m_BassMesh.m_pMesh);
		//delete [] wpTexName;
		//CommonMesh::CreateMeshFormX( pD3DDevice, pFileName, pTexMgr);
		::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
		//ShaderChange( new CookTrance(pD3DDevice) );
	}
    catch(...){
        //コンストラクタ例外発生
        //後始末
        SafeRelease(m_pMesh);
        //再スロー
        throw;
    }

}

/////////////////// ////////////////////
//// 関数名     ：EnemyModel::~EnemyModel();
//// カテゴリ   ：デストラクタ
//// 用途       ：球体を破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ： (山ノ井先生のひな形より)
//// 備考       ：
////            ：
////
EnemyModel::~EnemyModel(){
	m_pCamera	= NULL ;
	m_pPlayer	= NULL ;
	m_pCoil		= NULL ;
	SafeDelete( m_pDeadEffect );

	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
		
	m_ItemMap_Target.clear();
	
	SAFE_RELEASE( m_pMesh );
}

/////////////////// ////////////////////
//// 用途       ：WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// カテゴリ   ：コンストラクタ
//// 用途       ：関数
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
void EnemyModel::UpdateTargetItem(){
	//////////
	//	対象外の削除
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin( ),
								TIMend = m_ItemMap_Target.end( );
	while( TIMit != TIMend ){
		if( (*TIMit)->m_vPos.y <= m_pCamera->getPosY()  -DRAWING_RANGE ||
			(*TIMit)->m_vPos.y >= m_pCamera->getPosY()  +DRAWING_RANGE ){
			(*TIMit)->m_bHidden = true ;
			TIMit = m_ItemMap_Target.erase( TIMit );
			continue;
		}
		TIMit++ ;
	}
	//
	//
	//////////
	if(m_bReset){
		ALLCONTAINER::iterator	it  = m_ItemMap_All.begin(),
								end = m_ItemMap_All.end();
		while(it != end){
			it->second->m_vPos = it->second->m_vStartPos;
			it->second->m_bIsAlive = true;
			it++;
		}
	}
	m_bReset = false;
	
	//////////
	//	描画対象の追加
	//
	ALLCONTAINER::iterator	AIMit  = m_ItemMap_All.lower_bound( m_pCamera->getPosY()  -DRAWING_RANGE ),
							AIMend = m_ItemMap_All.upper_bound( m_pCamera->getPosY()  +DRAWING_RANGE );
	while( AIMit != AIMend ){
		if( AIMit->second->m_bHidden == true ){
			AIMit->second->m_bHidden = false ;
			m_ItemMap_Target.push_back( AIMit->second );
		}
		AIMit++ ;
	}
	//
	//
	//////////
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
//// 戻値       ：なし
//// 担当者     ：斎藤謙吾
//// 引き継ぎ   ：本多寛之
//// 備考       
////            ：
////

void EnemyModel::Update( UpdatePacket& i_UpdatePacket){
	if( !m_pCamera )	m_pCamera	=              (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA	) ;		
	if( !m_pPlayer )	m_pPlayer	= (ProvisionalPlayer3D*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_USERMAGNET	) ;
	if( !m_pCoil )		m_pCoil		=          (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL		) ;

	if(m_pCoil->getState() == COIL_STATE_CONTINUE)m_bReset = true;

	UpdateTargetItem();
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		if(m_pPlayer->getDrawing() && m_pCoil->getState() == COIL_STATE_MOVE){
			//	: 自分から対象までのベクトルを算出
			D3DXVECTOR3	vTargetDir	= m_pPlayer->getPos() - ((*it)->m_vPos) ;
			//	: 自分と対象までの距離を求める
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			float  fLng	= (float)sqrt(dirX + dirY);
			if(fLng <= (float)MGPRM_MAGNETICUM){
				float  enemySpeed = 0.0f, SplitLng = MGPRM_MAGNETICUM/3.0f; 
				if(fLng <= SplitLng)			enemySpeed = ENEMY_SPEED_LV3;
				else if(fLng <= SplitLng*2.0f)	enemySpeed = ENEMY_SPEED_LV2;
				else							enemySpeed = ENEMY_SPEED_LV1;
				D3DXVec3Normalize(&vTargetDir,&vTargetDir);
				if((*it)->m_bPole != m_pPlayer->getMagnetPole()){
					(*it)->m_vPos += vTargetDir * enemySpeed;
				}else{
					(*it)->m_vPos -= vTargetDir * enemySpeed;
				}
			}
		}

		float DeadLine  = (float)TwoPointToBassLength( (*it)->m_vPos, m_pCoil->getPos() ) ;
		if( m_pCoil->getState() == COIL_STATE_MOVE && DeadLine < ENEMY_RADIUS && (*it)->m_bIsAlive ){
			if(m_pCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE || m_pCoil->getSuperMode() == COIL_STATE_SUPER_READY){
				m_pCoil->setState(COIL_STATE_DEAD);
			}
			if((*it)->m_bIsAlive)i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			m_pDeadEffect->setPos( (*it)->m_vPos );

			(*it)->m_bIsAlive = false;
		}


		if( !((*it)->m_bIsAlive) ){
	        m_pDeadEffect->Update( i_UpdatePacket );
		}

		//拡大縮小
		//D3DXMATRIX mScale;
		//D3DXMatrixIdentity(&mScale);
		//D3DXMatrixScaling(&mScale,(*it)->m_vScale.x,(*it)->m_vScale.y,(*it)->m_vScale.z);

		//(*it)->m_vRot. += D3DXToRadian( 1.0f );
		
		//回転
		(*it)->m_fRotY += D3DXToRadian( 31.0f );
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationY(&mRot,(*it)->m_fRotY);

		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,(*it)->m_vPos.x,(*it)->m_vPos.y,(*it)->m_vPos.z);

		//ミックス行列
		(*it)->m_Matrix = /*mScale * */mRot * mMove;

		++it;
	}
}

/////////////////// ////////////////////
//// 関数名     ：voidEnemyModel::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// カテゴリ   ：仮想関数
//// 用途       ：球体を描画
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
////            ：  vector<Object*>& Vec,				//オブジェクトの配列
//// 戻値       ：なし
//// 担当者     ：斎藤謙吾
//// 引き継ぎ   ：本多寛之
//// 備考       ：
////            ：
////
void EnemyModel::Draw(DrawPacket& i_DrawPacket)
{
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		if((*it)->m_bIsAlive){
			//マティリアル設定
			this->m_WorldMatrix = (*it)->m_Matrix   ;	
			this->m_Material = ((*it)->m_Material)	;
			//((CookTrance*)this->m_pShader)->Draw(i_DrawPacket,this);

			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);


			//無効チェック
			if((!m_pMesh) || (!i_DrawPacket.GetDevice())){
				throw BaseException(L"デバイスかメッシュが無効です。",
				L"CommonMesh::Draw()");
			}
			if(m_Material.Diffuse.a < 1.0f){
				//もし、透明度が1.0未満なら
				// アルファ合成の設定
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			}
			if(m_Material.Specular.r > 0.0f
				|| m_Material.Specular.g > 0.0f
				|| m_Material.Specular.b > 0.0f)
			{
				//もし、スペキュラーが設定していたら
				// スペキュラー有効の設定
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, 1);
			}

			//ChangeRenderStateArray(i_DrawPacket.GetDevice(),pParam);
			// マテリアルをレンダリングパイプラインに設定
			i_DrawPacket.GetDevice()->SetMaterial( &m_Material);
			//描画
			m_pMesh->DrawSubset(0);
			//ChangeRenderStateArray(i_DrawPacket.GetDevice(),pParam);
			if(m_Material.Specular.r > 0.0f
				|| m_Material.Specular.g > 0.0f
				|| m_Material.Specular.b > 0.0f)
			{
				//もし、スペキュラーが設定していたら
				// スペキュラーを元に戻す
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, 0);
			}
			if(m_Material.Diffuse.a < 1.0f){
				//もし、透明度が1.0未満なら
				// アルファ合成を元に戻す
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
			}
		}

		if( !((*it)->m_bIsAlive) )m_pDeadEffect->Draw( i_DrawPacket );
		//爆散
		//if( (*it)->m_pDeadEffect[0] != NULL ){
		//	for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
		//		(*it)->m_pDeadEffect[i]->Draw( i_DrawPacket );
		//	}
		//}

		++it;
	}
			
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
//// 戻値       ：なし
//// 担当者     ：斎藤謙吾
//// 引き継ぎ   ：本多寛之
//// 備考       ：
////
void EnemyModel::AddEnemy(
		const D3DXVECTOR3&		vScale		,
		const D3DXVECTOR3&		vRot		,
		const D3DXVECTOR3&		vPos		,
		const D3DCOLORVALUE&	Diffuse		,
		const D3DCOLORVALUE&	Specular	,
		const D3DCOLORVALUE&	Ambient		,
		const POLE				Pole

	)
{

	EnemyItem* pItem = new EnemyItem;
	//pItem->m_vScale = vScale;
	pItem->m_fRotY =0;
	pItem->m_vPos = vPos;
	pItem->m_vStartPos = vPos;
	pItem->m_bIsAlive = true;
	//爆散エフェクトのポインタ
	//0(m_pD3DDevice,L"DeadPerticul.png",&m_pTex);
	//for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ )pItem->m_pDeadEffect[i] = NULL;
	::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	//回転の初期化
	//D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	int	i	= rand()%10;
	if( Pole == POLE_N ){
		pItem->m_bPole	= POLE_N;
		pItem->m_Material.Ambient.a = 1.0f ; pItem->m_Material.Ambient.b = 0.0f ; pItem->m_Material.Ambient.g = 0.0f ; pItem->m_Material.Ambient.r = 1.0f ;
		pItem->m_Material.Specular.a = 0.0f ; pItem->m_Material.Specular.b = 0.0f ; pItem->m_Material.Specular.g = 0.0f ; pItem->m_Material.Specular.r = 0.0f ;
		pItem->m_Material.Diffuse.a = 1.0f ; pItem->m_Material.Diffuse.b = 1.0f ; pItem->m_Material.Diffuse.g = 1.0f ; pItem->m_Material.Diffuse.r = 1.0f ;	
	}else{
		pItem->m_bPole	= POLE_S;
		pItem->m_Material.Ambient.a = 1.0f ; pItem->m_Material.Ambient.b = 1.0f ; pItem->m_Material.Ambient.g = 0.0f ; pItem->m_Material.Ambient.r = 0.0f ;
		pItem->m_Material.Specular.a = 0.0f ; pItem->m_Material.Specular.b = 0.0f ; pItem->m_Material.Specular.g = 0.0f ; pItem->m_Material.Specular.r = 0.0f ;
		pItem->m_Material.Diffuse.a = 1.0f ; pItem->m_Material.Diffuse.b = 1.0f ; pItem->m_Material.Diffuse.g = 1.0f ; pItem->m_Material.Diffuse.r = 1.0f ;	
	}

	m_ItemMap_All.insert(ALLCONTAINER::value_type(vPos.y,pItem));	
}

/////////////////// ////////////////////
//// 関数名     ：void	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：なし
//// 担当       ：佐藤涼
//// 備考       ：
////            ：
////
void	EnemyModel::CreateEffect( UpdatePacket& i_UpdatePacket, TARGETCONTAINER::iterator it ){
	//爆散エフェクトの作成
	//for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
	//	(*it)->m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.GetDevice(), (*it)->m_vPos,
	//		float((360/PARTICLS_NUM_ENEMY) * i), m_pCoil->getDeadText() );
	//}
};

/////////////////// ////////////////////
//// 用途       ：bool PlayerCoil::HitTestWall( OBB Obb )
//// カテゴリ   ：メンバ関数
//// 用途       ：壁との衝突判定
//// 引数       ：  OBB Obb           //  : 検査対象のOBB
//// 戻値       ：衝突していればtrue
//// 担当者     ：曳地 大洋
//// 備考       ：
void EnemyModel::HitTestWall( OBB Obb, UpdatePacket& i_UpdatePacket ){
	SPHERE sp;
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		sp.m_Center = (*it)->m_vPos;
		sp.m_Radius = ENEMY_RADIUS/2;
		//通常の衝突判定
		D3DXVECTOR3 Vec ;
		if(HitTest::SPHERE_OBB(sp,Obb,Vec)){
			//MessageBox( NULL, L"当たった！！", L"当たり判定", NULL) ;
			if( (*it)->m_bIsAlive){
    			m_pDeadEffect->setPos( (*it)->m_vPos );
			    i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			}
			    
			(*it)->m_bIsAlive = false;
		}
		it++;
	}
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
		//EnemyModel* Enemy = new EnemyModel(
		//	fpac->GetDevice(),
		//	RCTEXT_MODEL_ENEMY,
		//	fpac->m_pTexMgr
		//);
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
		//fpac->AddObject(Enemy);

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