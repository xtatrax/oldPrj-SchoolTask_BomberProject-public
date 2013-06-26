////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Wall.h"
#include "BassItems.h"


namespace wiz{
namespace bomberobject{

//PlayerCoil* WallObject::m_pPlayerCoil = NULL ;
//Camera*		WallObject::m_pCamera = NULL;	

/**************************************************************************
 Warning 定義部
****************************************************************************/
/**************************************************************************
 WallObject::WallObject(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
Warning::Warning( LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
:PrimitiveBox(pD3DDevice,Diffuse,Specular,Ambient,id,pTexture)
,m_Plate( pD3DDevice, pTexture, 0xFFFFFFFF )
,m_iPtn(0)
,m_pTexture(pTexture)
,m_vPos(D3DXVECTOR3(0.0f,0.0f,0.0f))
,m_vRot(D3DXVECTOR3(0.0f,0.0f,0.0f))
,m_vScale(D3DXVECTOR3(2.0f,2.0f,0.0f))
,m_bToDraw(false)
,m_fDrawTime( 0 )
,m_pCoil( NULL )
,m_bIsPlaySound( false )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	D3DXMATRIX mScalse, mRot, mPos;
	D3DXMatrixIdentity(&mScalse);
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mPos);
	D3DXMatrixScaling(&mScalse,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixRotationZ(&mRot,m_vRot.z);
	D3DXMatrixTranslation(&mPos, m_vScale.x,m_vScale.y,m_vScale.z);
	m_Matrix = mScalse * mRot * mPos ;
	m_Material.Ambient = Ambient ;
	m_Material.Diffuse = Diffuse ;
	m_Material.Specular = Specular ;


}
/////////////////// ////////////////////
//// 用途       ：~WallObject();
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
Warning::~Warning(){
	m_pCoil = NULL;
}
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
void Warning::Draw(DrawPacket& i_DrawPacket)
{
	if(m_bToDraw){
		if(!m_bIsPlaySound){
			i_DrawPacket.SearchSoundAndPlay(RCTEXT_SOUND_SE_SPARK_WARNING);
			m_bIsPlaySound = true;
		}
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);

			//田村T透過案
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATEREQUAL);
			//float	f	= 0.5f ;
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHAREF,*(DWORD*)&f);
			//コモンメッシュのDraw()を呼ぶ
			RENDERSTATE_PARAM pParam[] = {
				{ D3DRS_ALPHABLENDENABLE	, TRUE					},
				{ D3DRS_BLENDOP				, D3DBLENDOP_ADD		},
				{ D3DRS_SRCBLEND			, D3DBLEND_SRCALPHA		},
				{ D3DRS_DESTBLEND			, D3DBLEND_ONE			},
				{ D3DRS_FORCE_DWORD			, NULL					}
			};
			CommonMesh::Draw(i_DrawPacket,pParam);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);

			D3DXMATRIX m ;
			//D3DXMatrixScale( &m, );
			//D3DXVECTOR3	v	= MatrixCalculator( (*it)->m_Matrix, m_Plate.getPos() );
			//m_Plate.setMatrixPos( v );
			//m_Plate.setMatrix((*it)->m_Matrix);
			//m_Plate.Draw(i_DrawPacket);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
	}else{
		if(m_bIsPlaySound){
			i_DrawPacket.SoundStop(RCTEXT_SOUND_SE_SPARK_WARNING);
			m_bIsPlaySound = false ;
		}
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
//// 担当者     ：本多寛之
//// 備考       ：
////            ：
////
void Warning::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCoil )	m_pCoil	= (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL	) ;
	if(m_bToDraw){
		D3DXMATRIX mScalse, mRot, mPos;
		D3DXMatrixScaling(&mScalse,m_vScale.x,m_vScale.y,m_vScale.z);
		D3DXMatrixRotationZ(&mRot,D3DXToRadian(m_vRot.z));
		D3DXMatrixTranslation(&mPos, m_vPos.x,m_vPos.y,m_vPos.z);
		m_Matrix = mScalse * mRot * mPos ;

		const int  WARNING_INTERVAL = 2;
		static int s_iInterval = 0;
		if(s_iInterval >= WARNING_INTERVAL){
			//**************************************************************************************
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
				//法線と頂点からuv値を得る
				BoxVecNomal2UV_1_2(pVer[n].vec,pVer[n].normal,m_iPtn,pVer[n].tu,pVer[n].tv);
			}
			pVB->Unlock();
			//***********************************************************************************
			++m_iPtn;
			m_Plate.Update( m_iPtn );
		}
		if(s_iInterval >= WARNING_INTERVAL)s_iInterval = 0;
		s_iInterval++;

		m_fDrawTime	+= (float)i_UpdatePacket.pTime->getElapsedTime();
		if( m_fDrawTime > 0.01f ){
			m_pCoil->ScratchTime_Update();
			m_fDrawTime	= 0;
		}
	}
}

/**************************************************************************
 WallObject 定義部
****************************************************************************/
/**************************************************************************
 WallObject::WallObject(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：本多寛之
***************************************************************************/
WallObject::WallObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
:PrimitiveBox(pD3DDevice,
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		D3DCOLORVALUE(),
		id,
		pTexture)
,m_pWallTex( pTexture )
,m_Ptn(0)
,m_Plate( pD3DDevice, pTexture, 0xFFFFFFFF )
,m_pWarning( NULL )
,m_pPlayerCoil(NULL)
,m_pCamera(NULL)
,m_pEnemy(NULL)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_Material.Ambient	= getD3DCOLORVALUE(0.0f,0.5f,0.5f,0.5f);
	m_Material.Diffuse	= getD3DCOLORVALUE(0.0f,0.7f,0.7f,0.7f);
	m_Material.Specular	= getD3DCOLORVALUE(0.0f,0.0f,0.0f,0.0f);

}
/////////////////// ////////////////////
//// 用途       ：~WallObject();
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
WallObject::~WallObject(){
	m_pCamera		= NULL ;
	m_pPlayerCoil	= NULL ;
	m_pEnemy		= NULL;
	m_pWarning		= NULL;
	SafeDeletePointerMap( m_ItemMap_All );

	m_ItemMap_All.clear() ;
	m_ItemMap_Target.clear() ;	//	: この子はClearのみ
}

/////////////////// ////////////////////
//// 用途       ：WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// カテゴリ   ：コンストラクタ
//// 用途       ：関数
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
void WallObject::UpdateTargetItem(){
	//////////
	//	対象外の削除
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin( ),
								TIMend = m_ItemMap_Target.end( );
	while( TIMit != TIMend ){
		if( (*TIMit)->m_fMapKey <= m_pCamera->getPosY()  -DRAWING_RANGE ||
			(*TIMit)->m_fMapKey >= m_pCamera->getPosY()  +DRAWING_RANGE ){
			(*TIMit)->m_bHidden = true ;
			TIMit = m_ItemMap_Target.erase( TIMit );
			continue;
		}
		TIMit++ ;
	}
	//
	//
	//////////
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

	
bool WallObject::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
{
	//float fTH = 150 ;
	//float fTW =  20 ;
	//if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
	//	abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
	//	return true ;
	//}
	return false ;
}

/////////////////// ////////////////////
//// 用途       ：void Will::GetOBB( size_t Index, OBB& obb )
//// カテゴリ   ：関数
//// 用途       ：指定のインデックスの現在のOBBを得る
//// 引数       :		size_t Index,
////					OBB& obb	//取得するOBB
//// 戻値       ：なし。インデックスが範囲外なら例外
////				 ＊現在のOBBを代入する
//// 担当者     ：曳地 大洋
//// 備考       ：
void WallObject::GetOBBList( float Index, list<OBB>& ObbList ){
    //指定の配置オブジェクトを検証
	TARGETCONTAINER::iterator itBegin	= m_ItemMap_Target.begin( ) ;
	TARGETCONTAINER::iterator itEnd		= m_ItemMap_Target.end( ) ;
	OBB obb ; 
	for(TARGETCONTAINER::iterator iter = itBegin; iter != itEnd; ++iter){
		ObbList.push_back( (*iter)->m_Obb ) ;
		ObbList.push_back( (*iter)->m_Obb_W ) ;
	}
}


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
void WallObject::Draw(DrawPacket& i_DrawPacket)
{
	m_pTexture = m_pWallTex ;
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		//テクスチャがある場合
		if(m_pWallTex){
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_Matrix);

			//田村T透過案
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATEREQUAL);
			//float	f	= 0.5f ;
			//i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHAREF,*(DWORD*)&f);
			//コモンメッシュのDraw()を呼ぶ
			RENDERSTATE_PARAM pParam[] = {
				{ D3DRS_ALPHABLENDENABLE	, TRUE					},
				{ D3DRS_BLENDOP				, D3DBLENDOP_ADD		},
				{ D3DRS_SRCBLEND			, D3DBLEND_SRCALPHA		},
				{ D3DRS_DESTBLEND			, D3DBLEND_ONE			},
				{ D3DRS_FORCE_DWORD			, NULL					}
			};
			CommonMesh::Draw(i_DrawPacket,pParam);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);

			D3DXMATRIX m ;
			//D3DXMatrixScale( &m, );
			//D3DXVECTOR3	v	= MatrixCalculator( (*it)->m_Matrix, m_Plate.getPos() );
			//m_Plate.setMatrixPos( v );
			//m_Plate.setMatrix((*it)->m_Matrix);
			//m_Plate.Update( m_Ptn );
			//m_Plate.Draw(i_DrawPacket);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		if( (*it)->m_pDOB ){
			(*it)->m_pDOB->Draw(i_DrawPacket);
		}else{
			(*it)->m_pDOB = new DrawOBB(i_DrawPacket.pD3DDevice,(*it)->m_Obb);
		}
#endif

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
//// 担当者     ：本多寛之
//// 備考       ：
////            ：
////
void WallObject::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera     )	m_pCamera		=     (Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA	) ;
	if( !m_pPlayerCoil )	m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL		) ;
	if( !m_pEnemy      )	m_pEnemy		= (EnemyModel*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_ENEMY		) ;
	if( !m_pWarning    )	m_pWarning		=    (Warning*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_WARNING		) ;

	UpdateTargetItem();
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	m_pWarning->setToDraw(false);
	while(it != end){
		if( m_pPlayerCoil && m_pPlayerCoil->HitTestWall( (*it)->m_Obb_W ) ){
			switch(m_pPlayerCoil->getState()){
				case COIL_STATE_MOVE:
					if(m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE || m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_READY){
						m_pWarning->setToDraw(true);
						D3DXVECTOR3 vColiPos = m_pPlayerCoil->getPos(),
									vWallPos = (*it)->m_Obb_W.m_Center,
									vWallSiz = (*it)->m_Obb_W.m_Size,
									vWarning = vColiPos;
						float		fRotZ	 = (*it)->m_fRotZ;
						if(fRotZ < 90.0f){
							if(vWallPos.y - vWallSiz.y > vColiPos.y){
								vWarning.x = vWallPos.x;
								m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,180.0f));
							}else if(vWallPos.y + vWallSiz.y < vColiPos.y){
								vWarning.x = vWallPos.x;
								m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,0.0f));								
							}else{
								if(vWallPos.x <= vColiPos.x){
									vWarning.x = vWallPos.x + 1.0f;
									m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,-90.0f));
								}
								else{
									vWarning.x = vWallPos.x - 1.0f;
									m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,90.0f));
								}
							}
						}else{
							if(vWallPos.x - vWallSiz.y > vColiPos.x){
								vWarning.y = vWallPos.y;
								m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,90.0f));
								
							}else if(vWallPos.x + vWallSiz.y < vColiPos.x){
								vWarning.y = vWallPos.y;
								m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,-90.0f));								
							}else{
								if(vWallPos.y <= vColiPos.y){
									vWarning.y = vWallPos.y + 1.0f;
									m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,0.0f));
								}
								else{
									vWarning.y = vWallPos.y - 1.0f;
									m_pWarning->setRot(D3DXVECTOR3(0.0f,0.0f,180.0f));
								}
							}
						}
						vWarning.z = -1.0f;
						m_pWarning->setPos(vWarning);					
					}
					break;
				default:
					break;
			}
		}
		if( m_pPlayerCoil && m_pPlayerCoil->HitTestWall( (*it)->m_Obb ) ){
			switch(m_pPlayerCoil->getState()){
				case COIL_STATE_MOVE:
					if(m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE || m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_READY){
						i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
						m_pPlayerCoil->setState(COIL_STATE_DEAD);
					}
					break;
				default:
					break;
			}
		}
		if(m_pEnemy){
			m_pEnemy->HitTestWall( (*it)->m_Obb, i_UpdatePacket );
		}

		//**************************************************************************************
		LPDIRECT3DVERTEXBUFFER9 pVB = 0;
		CommonMeshVertex* pVer = 0;
		m_pMesh->GetVertexBuffer(&pVB);
		pVB->Lock(0,0,(VOID**)&pVer,0);
		DWORD vsize = m_pMesh->GetNumVertices();
		for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
			//法線と頂点からuv値を得る
			BoxVecNomal2UV_1_4(pVer[n].vec,pVer[n].normal,(*it)->m_iPtn,pVer[n].tu,pVer[n].tv);
		}
		pVB->Unlock();
		//***********************************************************************************

		(*it)->m_iPtn++;
		(*it)->m_iPtn	%= 4;
		//m_Plate.Update( (*it)->m_iPtn );

		++it;
	}


	//static	int	s_Time	= 0;

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
////				曳地 大洋
//// 備考       ：
void WallObject::AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	WallItem* pItem = new WallItem(vScale,vRot,vPos,m_Ptn,Diffuse,Specular,Ambient);
	m_ItemMap_All.insert(ALLCONTAINER::value_type(vPos.y,pItem));

	m_Ptn++;
	m_Ptn	%= 4;
}


/**************************************************************************
 Factory_Wall 定義部
****************************************************************************/
/**************************************************************************
 Factory_Wall::Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Wall::Factory_Wall(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE WallDiffuse = {0.7f,0.7f,0.7f,1.0f};
		D3DCOLORVALUE WallSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE WallAmbient = {0.5f,0.5f,0.5f,1.0f};
		fpac->m_pVec->push_back( new Warning(fpac->pD3DDevice,WallDiffuse,WallSpecular,WallAmbient,
												fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Warning.png" )));
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Wall::~Factory_Wall();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Wall::~Factory_Wall(){
    //なにもしない
}

}
//end of namespace bomberobject.

}
//end of namespace wiz.
