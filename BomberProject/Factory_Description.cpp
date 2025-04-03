////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Description.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包データと備考	：説明ファクトリー
//					▼
//	namespace wiz;
//		class Factory_Description ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Description.h"
#include "Factory_Wall.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 ModeChangeChar 定義部
**************************************************************************/
/**************************************************************************
 ModeChangeChar(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ModeChangeChar::ModeChangeChar(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				Rect*		Rect		)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, g_vZero, Rect, g_vZero, g_vZero, 0xFFFFFFFF, OBJID_UI_SPRITE )
,m_bAllDraw( false )
,m_bAnimeDir( true )
,m_fInterval( 0 )
,m_BaseRect( Rect )
{
}

/**************************************************************************
 ~ModeChangeChar()
 用途　：デストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
ModeChangeChar::~ModeChangeChar()
{
}

/**************************************************************************
 関数名：Draw( DrawPacket& i_DrawPacket )
 用途　：描画
 引数　：DrawPacket& i_DrawPacket
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
void	ModeChangeChar::Draw( DrawPacket& i_DrawPacket )
{
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 関数名：Update( UpdatePacket& i_UpdatePacket )
 用途　：更新
 引数　：UpdatePacket& i_UpdatePacket
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
void	ModeChangeChar::Update( UpdatePacket& i_UpdatePacket )
{
	const	int		iTransRect	= 30;		//一度に変化させるRECTの値
	const	float	fMovePos	= 15.0f;	//RECTの描画に合わせた変化させる座標の値
	const	float	fStopTime	= 0.5f;		//画像が全描画になった時、止めておく時間（秒）

	if( !m_bAllDraw ){
		if( m_bAnimeDir ){
			m_pRect->right	+= iTransRect;
			m_vOffsetPos.x	-= fMovePos;
		}
		else
			m_pRect->right	-= iTransRect;
	}
	else{
		m_fInterval += (float)i_UpdatePacket.GetTime()->getElapsedTime();
		if( m_fInterval >= fStopTime ){
			m_bAllDraw	= false;
			m_bAnimeDir	= false;
		}
	}

	if( (m_pRect->right >= m_BaseRect.right) && m_bAnimeDir ){
		m_pRect->right	= m_BaseRect.right;
		m_bAllDraw	= true;
	}

	if( m_pRect->right <= m_BaseRect.left )
		m_pRect->right	= m_BaseRect.left;

}

/**************************************************************************
 StartSprite 定義部
**************************************************************************/
/**************************************************************************
 StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	vScale,
				D3DXVECTOR3	vPos,
				Rect		rect,
				D3DXVECTOR3	vCenter)
 用途　：コンストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
StartSprite::StartSprite(LPDIRECT3DDEVICE9	pD3DDevice,
				LPTATRATEXTURE	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect)
:SpriteObject( pD3DDevice, pTexture, vScale, g_vZero, vPos, Rect, g_vZero, g_vZero, 0x00FFFFFF, OBJID_SYS_START )
,m_vPos( vPos )
,m_vStartPos( vPos )
,m_vScale( vScale )
,m_vRelayPosY( vPos.y + 40.0f )
,m_iTime( 0 )
,m_bFirst( true )
,m_bSecond( true )
,m_pCoil( NULL )
,m_State(COIL_STATE_START)
{
}

/**************************************************************************
 ~StartSprite()
 用途　：デストラクタ
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
StartSprite::~StartSprite()
{
	m_pCoil	= NULL;
}

/**************************************************************************
 関数名：Draw( DrawPacket& i_DrawPacket )
 用途　：描画
 引数　：DrawPacket& i_DrawPacket
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
void	StartSprite::Draw( DrawPacket& i_DrawPacket )
{
	SpriteObject::Draw( i_DrawPacket );
}

/**************************************************************************
 関数名：Update( UpdatePacket& i_UpdatePacket )
 用途　：更新
 引数　：UpdatePacket& i_UpdatePacket
 戻り値：なし
 担当者：佐藤涼
***************************************************************************/
void	StartSprite::Update( UpdatePacket& i_UpdatePacket )
{
	if( !m_pCoil )	m_pCoil = (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

	int		rate	= 0;
	BYTE	ChangeAlpha	= (255/40);

	if( m_vRelayPosY > m_vPos.y ){
		m_vPos.y	+= 1.0f;
		rate		 = 1;
	}
	else if( m_vRelayPosY == m_vPos.y ){
		rate	= 0;
		++m_iTime;
		if( m_iTime > 20 )
			m_vPos.y	+= 1.0f;
	}
	else if( m_vRelayPosY < m_vPos.y ){
		rate	= -1;
		m_vPos.y	+= 1.0f;
	}

	if( rate == 1 ){
		if( m_Color.byteColor.a >= 250 )
			m_Color.byteColor.a	 = 255;
		else
			m_Color.byteColor.a	+= ChangeAlpha;
	}
	else if( rate == -1 ){
		if( m_Color.byteColor.a <= 5 ){
			m_Color.byteColor.a	 = 0;
			++m_iTime;
			if( m_iTime > 40 ){
				if( m_bFirst ){
					m_pCoil->setState( m_State );
					m_bFirst	= false;
				}
				if( m_bSecond ){
					m_pCoil->setReadyToStart( true );
					m_bSecond	= false;
				}
			}
		}
		else
			m_Color.byteColor.a	-= ChangeAlpha;
	}

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixScaling(&mScale,m_vScale.x,m_vScale.y,m_vScale.z);
	D3DXMatrixTranslation(&mPos,m_vPos.x,m_vPos.y,m_vPos.z);
	m_mMatrix = mScale * mPos ;
}

/**************************************************************************
 Description 定義部
****************************************************************************/
/**************************************************************************
 Description::Description(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPTATRATEXTURE pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
Description::Description( LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE pTexture, wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
	,m_pCamera( NULL )
	,m_pCoil( NULL )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //頂点の数を取得する
		//法線と頂点からuv値を得る
		BoxVecNomalUV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();

}
/////////////////// ////////////////////
//// 用途       ：~Description;
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 トオル
//// 備考       ：
Description::~Description(){
	m_pCamera  = NULL ;
	m_pCoil    = NULL ;
	SafeDeletePointerMap( m_ItemMap_Desc );
	m_ItemMap_Desc.clear();
	m_ItemMap_Target.clear();
}

/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
void Description::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,DescItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		if(it->second->m_bDisplay){
			//テクスチャがある場合
			if(m_pTexture){
				DWORD wkdword;
				//現在のテクスチャステータスを得る
				i_DrawPacket.GetDevice()->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
				//ステージの設定
				i_DrawPacket.GetDevice()->SetTexture(0,m_pTexture->getTexture());
				//デフィーズ色とテクスチャを掛け合わせる設定
				i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
				i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

				//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
				// マトリックスをレンダリングパイプラインに設定
				i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(i_DrawPacket);
				i_DrawPacket.GetDevice()->SetTexture(0,0);
				//ステージを元に戻す
				i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{
			//テクスチャがない場合
				// マトリックスをレンダリングパイプラインに設定
				i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
				//コモンメッシュのDraw()を呼ぶ
				CommonMesh::Draw(i_DrawPacket);
			}
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
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void Description::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera )	m_pCamera	=     (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA);
	if( !m_pCoil   )	m_pCoil		= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL);

	m_ItemMap_Target.clear();
	multimap<float,DescItem*>::iterator it = m_ItemMap_Desc.begin();
	while(it != m_ItemMap_Desc.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,DescItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}

	multimap<float,DescItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		//*******************************************************
		//描画するか否か
		COIL_STATE Buf = m_pCoil->getState() ;
		if( ( Buf == it2->second->m_State )
							&& it2->second->m_bCanDisplay ){
			it2->second->m_bDisplay	= true;
		}
		else if( it2->second->m_bDisplay ){
			it2->second->m_bDisplay		= false;
			it2->second->m_bCanDisplay	= false;
		}
		//********************************************************

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

		++it2;
	}
}

/////////////////// ////////////////////
//// 用途       ：void AddDesc( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：Descの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：なし
//// 担当者     ：佐藤涼
//// 備考       ：
void Description::AddDesc(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,COIL_STATE state,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	DescItem* pItem = new DescItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos	= vPos;
	pItem->m_State	= state;
	pItem->m_bCanDisplay	= true;
	pItem->m_bDisplay		= false;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	pItem->m_Material.Diffuse = Diffuse;
	pItem->m_Material.Specular = Specular;
	pItem->m_Material.Ambient = Ambient;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Desc.insert(multimap<float,DescItem*>::value_type(pItem->m_vPos.y,pItem));
}

/**************************************************************************
 Factory_Result 定義部
****************************************************************************/
/**************************************************************************
 Factory_Result::Factory_Description(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Description::Factory_Description(FactoryPacket* fpac){
	try{
 		D3DCOLORVALUE DescDiffuse = {1.0f,1.0f,1.0f,0.0f};
		D3DCOLORVALUE DescSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE DescAmbient = {1.0f,1.0f,1.0f,0.0f};

		//Description* Desc = new Description(fpac->GetDevice(),
		//	fpac->m_pTexMgr->addTexture(fpac->GetDevice(),L"setumei_Start.png"));

		//Desc->AddDesc(D3DXVECTOR3(10.0f,4.0f,0.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(10.0f,16.0f,-0.5f),
		//			  COIL_STATE_START,
		//			  DescDiffuse,
		//			  DescSpecular,
		//			  DescAmbient);

		//fpac->AddObject(Desc);

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;


		//スタートロゴ
		fpac->AddObject(
			new StartSprite(
					fpac->GetDevice(),
					fpac->AddTexture( L"START2.png" ),
					D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
					D3DXVECTOR3( wide-256.0f, height-100.0f, 0.0f ),
					&Rect( 0, 0, 512, 128 )
			)	
		);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Result::~Factory_Description();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Description::~Factory_Description(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
