////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多 寛之
//	編集			：佐藤 涼
//	内包ﾃﾞｰﾀと備考	：チェックポイント
//					▼
//	namespace wiz;
//		namespace bomberobject;
//			class CheckEffect         : public PrimitiveBox	;
//			class CheckPoint          : public Cylinder		;
//			class Factory_CheckPoint  ;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_CheckPoint.h"
//	: 基本のインクルード
//////////

//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////



const float CHECK_POINT_RADIUS = 0.25f ;
const float EFFECT_SIZE	= 2.0f;
const D3DXVECTOR3 CHECK_POINT_CHAR_SIZE = D3DXVECTOR3(1.0f,1.0f,0.0f);
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.5f, 1.0f, 0.5f, 0.5f } ;
D3DCOLORVALUE CHECKPOINTCOLOR_CHAR = { 1.0f, 1.0f, 1.0f, 1.0f } ;

const	float	CHECKPOINT_CHAR_DOWNSPEED	= 20.0f;
const	float	CHECKPOINT_CHAR_RATE_Y		= (1.0f/CHECK_POINT_CHAR_SIZE.y);
const	float	CHECKPOINT_CHAR_RATE_X		= (1.0f/CHECK_POINT_CHAR_SIZE.x);

namespace wiz{
namespace bomberobject{

/**************************************************************************
 CheckEffect 定義部
****************************************************************************/
/************************************************************************class MouseCursor : public Box , public  PrimitiveSprite{
**
 CheckEffect::CheckEffect(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
CheckEffect::CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		fLength,
						LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_vPos( vPos )
,m_Num( (int)(fLength) )
,m_fWide( EFFECT_SIZE*4 )
,m_fHight( EFFECT_SIZE )
,m_bMark( false )
,m_bStart( false )
,m_bCreating( true )
,m_pCoil( NULL )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

	D3DCOLORVALUE Diffuse	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient	= {0.5f,1.0f,0.5f,0.0f};

	m_Material.Diffuse	= Diffuse;
	m_Material.Specular	= Specular;
	m_Material.Ambient	= Ambient;

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

	for( int i = 0; i < DRAWING_NUMBER; i++ ){
		m_fPosXArr[i]	= float(i*2);
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
//// 担当者     ：佐藤涼
//// 備考       ：
void CheckEffect::Draw(DrawPacket& i_DrawPacket)
{
	//描画する個数を設定
	int	num	= 0;
	if( m_bMark )
		num	= 1;
	else
		num	= DRAWING_NUMBER;

	for( int i = 0; i < num; i++ ){
		//updateで描画位置を決定
		update( i ,i_DrawPacket);

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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
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
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void CheckEffect::update( int i ,DrawPacket& i_DrawPacket){

	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)SearchObjectFromID( i_DrawPacket.pVec, OBJID_3D_COIL );
	//スタート位置にエフェクトを出すか
	if( !m_bMark ){
		if( m_fWide > 0.0f ){
			if( m_bStart ){
				if( m_pCoil != NULL ){
					Pos_Update(i);
				}
				Reduction();
			}
		}
		else{
			m_bMark	= true;
			m_Material.Ambient.r	= 0;
			m_Material.Ambient.g	= 0;
			m_Material.Ambient.b	= 0;
		}
		m_vPos.x	= m_fPosXArr[i];
	}
	else{
		if( m_pCoil != NULL )
			m_vPos	= m_pCoil->getStartPos();
		if( m_fWide < EFFECT_SIZE*3 )
			Expansion();
	}
	//計算はUpdateで
	//拡大縮小
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, m_fWide, m_fHight, 0.0f );
	//回転
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	//移動用
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,m_vPos.x,m_vPos.y,m_vPos.z);
	//ミックス行列
	m_Matrix	= mScale * mRot * mMove;

}

/************************************
関数名　：void Pos_Update( int i )
用途　　：描画位置の更新
カテゴリ：
引数　　：int i     //変更したいエフェクトの指定
戻り値　：
担当者　：佐藤涼
備考　　：
************************************/
void	CheckEffect::Pos_Update( int i ){
	float	MigrationRate	= m_pCoil->getStartPos().x - m_fPosXArr[i];
	//描画すべき位置を算出
	m_fPosXArr[i]	+= MigrationRate/10.0f + 0.2f;
	if( MigrationRate > 0.0f ){
		m_fPosXArr[i]	+= MigrationRate/10.0f + 0.2f;
		if( m_pCoil->getStartPos().x - m_fPosXArr[i] < 0.0f )
			m_fPosXArr[i]	= m_pCoil->getStartPos().x;
	}
	else if( MigrationRate < 0.0f ){
		m_fPosXArr[i]	+= MigrationRate/10.0f - 0.2f;
		if( m_pCoil->getStartPos().x - m_fPosXArr[i] > 0.0f )
			m_fPosXArr[i]	= m_pCoil->getStartPos().x;
	}
}

/*************************************
関数名　：void	CheckEffect::Reduction()
用途　　：サイズ縮小
カテゴリ：関数
引数　　：なし
戻り値　：なし
担当者　：佐藤涼
備考　　：
*************************************/
void	CheckEffect::Reduction(){
	float	rate = m_fWide / m_fHight;

	m_fWide		-= 0.002f*rate;
	m_fHight	-= 0.002f;
}

/*************************************
関数名　：void	CheckEffect::Expansion()
用途　　：サイズ拡大（拡大率は縦横等価）
カテゴリ：関数
引数　　：なし
戻り値　：なし
担当者　：佐藤涼
備考　　：
*************************************/
void	CheckEffect::Expansion(){
	m_fWide		+= 0.08f;
	m_fHight	+= 0.08f;

	//float rate	= (EFFECT_SIZE*3) / 0.04f;

	//m_Material.Ambient.r	+= rate;
	//m_Material.Ambient.g	+= rate;
	//m_Material.Ambient.b	+= rate;
	m_Material.Ambient		=  CHECKPOINTCOLOR;
}

/****************************************************************************
CheckPoint 定義部
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPDIRECT3DTEXTURE9 pTexture,LPDIRECT3DTEXTURE9 pTexture2,LPDIRECT3DTEXTURE9 pTexture3, wiz::OBJID id  )
: Cylinder( pD3DDevice, CHECK_POINT_RADIUS, CHECK_POINT_RADIUS, fLength, g_vZero, D3DXVECTOR3( 0.0f,D3DXToRadian( 90.0f )
		   , 0.0f ), CHECKPOINTCOLOR_CHAR, D3DCOLORVALUE(), CHECKPOINTCOLOR_CHAR, id, false, NULL, 18) 
, m_pCoil( NULL )
, m_pCamera( NULL )
, m_ActiveItem( NULL )
, m_pTime( NULL )
, m_Color( CHECKPOINTCOLOR )
, m_Thicken( 1.0f )
, m_Length( fLength )
, m_pTexture( pTexture )
,m_pTexturePoint( pTexture2 )
, m_pTextureLast( pTexture3 ) 
{
	m_pEffect	= new CheckEffect( pD3DDevice, g_vZero, fLength, pTexture );
	m_pEffect2	= NULL;
	//m_pPintMark = new Box(pD3DDevice,CHECK_POINT_CHAR_SIZE,g_vZero,g_vZero,CHECKPOINTCOLOR, D3DCOLORVALUE(), CHECKPOINTCOLOR,OBJID_3D_BOX,false,pTexture2);
	m_pPintMark = new SpriteObject( pD3DDevice, pTexture2, CHECK_POINT_CHAR_SIZE, g_vZero, g_vZero,
									Rect( 0, 0, 512, 64 ), D3DXVECTOR3( 256.0f, 32.0f, 0.0f ), D3DXVECTOR3( 0.0f, -87.0f, 0.0f ));
}
CheckPoint::~CheckPoint(){
	m_pCoil		= NULL ;
	m_pCamera	= NULL ;
	m_pTime		= NULL ;
	SAFE_DELETE( m_pEffect );
	SAFE_DELETE( m_pEffect2 );
	m_pPintMark	= NULL;
	SafeDeletePointerContainer( m_ItemContainer ) ;
}
/////////////////// ////////////////////
//// 用途       ：virtual void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：仮想関数
//// 用途       ：オブジェクトを更新
//// 引数       ：  UpdatePacket& i_UpdatePacket     // アップデート時に必要なデータ群 ↓内容下記
////            ：  ├       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├       Tempus2*           pTime           // 時間を管理するクラスへのポインター
////            ：  ├       vector<Object*>&   Vec,            // オブジェクトの配列
////            ：  ├ const CONTROLER_STATE*   pCntlState      // コントローラのステータス
////            ：  └       Command            pCommand        // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pTime )		m_pTime	= ( TimeScore* )SearchObjectFromID( i_UpdatePacket.pVec, OBJID_UI_TIME );
	if( !m_pCoil   )	m_pCoil	= (PlayerCoil*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_3D_COIL	) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}
	//if( m_ActiveItem >= m_ItemContainer.size() ){
	//	m_ActiveItem = m_ItemContainer.size() -1;
	//}
	float	wide	= 0;
	float	height	= 0;
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		float fCoilPosY = m_pCoil->getPos().y;

		float	fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;

		//CHECK POINT テクスチャ*************************************************************
		//float	wide;
		//if(m_ActiveItem == m_ItemContainer.size()-1){
		//	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		//}else{
		//	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		//}
		wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		height	= ( (m_ItemContainer[ m_ActiveItem ]->vStartPos.y - fTexPosY)
										* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
		Debugger::DBGSTR::addStr(L" なう%d\n",m_ActiveItem);
		Debugger::DBGSTR::addStr(L" まっくす%d\n",m_ItemContainer.size());
		D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
		D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
		D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
		D3DXMatrixTranslation(&mPos, wide,height,0.0f);
		mTexMatrix	= mPos*mScale*mRot;
		m_pPintMark->setMatrix( mTexMatrix );
		//*************************************************************************************

		if(fPosY <= fCoilPosY){
			m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
			m_ActiveItem++;
			m_pCoil->setRecordTime();
			m_pTime->setTime();
			if(m_ActiveItem == m_ItemContainer.size()-1){
				m_pPintMark->setTexture(m_pTextureLast);
				m_pPintMark->setCenter(D3DXVECTOR3( 128.0f, 32.0f, 0.0f ));
			}
			if( m_pEffect != NULL ){
				if( m_pEffect2 != NULL ){
					if( m_pEffect->getMark() ){
						m_pEffect2->setStart(true);
					}
					else{
						m_pEffect->setStart(true);
					}
				}
				else{
					m_pEffect->setStart(true);
				}
			}
			i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
			if(m_ActiveItem >= m_ItemContainer.size()) return ;
			fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
		}


		D3DXVECTOR3	pos	= D3DXVECTOR3(0.0f,m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f);
		if( m_pEffect != NULL ){
			if( !(m_pEffect->getStart()) ){
				m_pEffect->setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );
		}else{
				if( m_pEffect->getCreating() ){
					m_pEffect2	= new CheckEffect( i_UpdatePacket.pD3DDevice, 
								pos, m_Length, m_pTexture);
					m_pEffect->setCreating( false );
				}
			}
			m_pEffect->Update( i_UpdatePacket );
		}

		if( m_pEffect2 != NULL ){
			if( !(m_pEffect2->getStart()) )
				m_pEffect2->setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );
			else{
				if( m_pEffect2->getCreating() ){
					m_pEffect	= new CheckEffect( i_UpdatePacket.pD3DDevice, 
								pos, m_Length, m_pTexture);
					m_pEffect2->setCreating( false );
				}
			}
			m_pEffect2->Update( i_UpdatePacket );
		}
	}
	else{
		wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ m_ActiveItem-1 ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
		height	= ( (m_ItemContainer[ m_ActiveItem-1 ]->vStartPos.y - (m_pCamera->getPosY() - m_fInitPosY))
										* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
		D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
		D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
		D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
		D3DXMatrixTranslation(&mPos, wide,height,0.0f);
		mTexMatrix	= mPos*mScale*mRot;
		m_pPintMark->setMatrix( mTexMatrix );

	}

	//Blink();
};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：鴫原 徹 本多寛之(編集)
//// 備考       ：
////            ：
////
void CheckPoint::Draw( DrawPacket& i_DrawPacket ){
	if( m_pCamera && m_ActiveItem < m_ItemContainer.size()){
		//	: カメラがある
		//	: 描画対象がいる
		float DrawBeginLength = m_pCamera->getPosY() + DRAW_TOLERANCE ;
		if( DrawBeginLength > m_ItemContainer[ m_ActiveItem ]->fPosY ){
			//	: 画面の中にいる
			
			//	
			m_BasePos = D3DXVECTOR3( m_pCamera->getAt().x, m_ItemContainer[ m_ActiveItem ]->fPosY,0.0f) ;

			//	:　メッセージ？を描画
			m_pPintMark->Draw(i_DrawPacket);

			//	:　Matrixの計算
			CalcWorldMatrix();
			//Cylinder::Draw( i_DrawPacket );
		}

		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
	}
	else/* if(m_ActiveItem == m_ItemContainer.size()-1)*/{
		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
		Debugger::DBGSTR::addStr(L"らすと");
		m_pPintMark->Draw(i_DrawPacket);
	}

	if( m_pEffect != NULL ){
		m_pEffect->Draw( i_DrawPacket );
	}
	if( m_pEffect2 != NULL ){
		m_pEffect2->Draw( i_DrawPacket );
	}
};

/////////////////// ////////////////////
//// 用途       ：virtual void Blink()
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトを明滅する
//// 引数       ：なし　
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void	CheckPoint::Blink(){
	m_Color.a	-=	0.03f * m_Thicken + 0.01f;

	if( m_Color.a < 0.3f ){
		m_Color.a	 =  0.3f;
		m_Thicken	*= -1.0f;
	}
	else if( m_Color.a > 0.9f ){
		m_Color.a	 =  0.9f;
		m_Thicken	*= -1.0f;
	}
}

/**************************************************************************
 Factory_CheckPoint 定義部
****************************************************************************/
/**************************************************************************
 Factory_CheckPoint::Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::Factory_CheckPoint(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			
			//CheckPoint* pcp ;
			//fpac->m_pVec->push_back(
			//	pcp = new CheckPoint( fpac->pD3DDevice, 100.0f, fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"particle.png" ),)
			//);
			//pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			//pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

		}
		
		catch(...){
			//再throw
			throw;
		}
	}

/**************************************************************************
 Factory_CheckPoint::~Factory_CheckPoint();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_CheckPoint::~Factory_CheckPoint(){
//なにもしない
	}
}//end of namespace bomberobject.
}//end of namespace wiz.