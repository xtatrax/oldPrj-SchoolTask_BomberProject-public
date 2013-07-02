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
const D3DXVECTOR3 CHECK_POINT_CHAR_SIZE = D3DXVECTOR3(1.0f,1.0f,0.0f);
D3DCOLORVALUE CHECKPOINTCOLOR = { 0.5f, 1.0f, 0.5f, 0.5f } ;
D3DCOLORVALUE CHECKPOINTCOLOR_CHAR = { 1.0f, 1.0f, 1.0f, 1.0f } ;

const	float	CHECKPOINT_CHAR_DOWNSPEED	= 20.0f;
const	float	CHECKPOINT_CHAR_RATE_Y		= (1.0f/CHECK_POINT_CHAR_SIZE.y);
const	float	CHECKPOINT_CHAR_RATE_X		= (1.0f/CHECK_POINT_CHAR_SIZE.x);

namespace wiz{
namespace bomberobject{

///**************************************************************************
// CheckEffect 定義部
//****************************************************************************/
///************************************************************************class MouseCursor : public Box , public  PrimitiveSprite{
//**
// CheckEffect::CheckEffect(
//	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
//	LPTATRATEXTURE pTexture,	//テクスチャ
//	wiz::OBJID id					//オブジェクトの種類
//);
// 用途: コンストラクタ
// 戻り値: なし
// 担当：佐藤涼
//***************************************************************************/
CheckEffect::CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
						D3DXVECTOR3 vPos,
						float		fLength,
						LPTATRATEXTURE pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_bVanish(false)
,m_pCoil( NULL )
,m_vPointScale( g_vZero )
,m_vPointPos( g_vZero )
{
	D3DXMatrixIdentity( &m_Matrix );
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
	SafeRelease( pVB );
	//SafeDelete( pVer );

	for( int i = 0; i < DRAWING_NUMBER; i++ )
		addEffect( float(i*2), vPos.y );
	Debugger::DBGWRITINGLOGTEXT::addStr(L"CheckEffect::CheckEffect OK\n");
}

/********************************
デストラクタ
********************************/
CheckEffect::~CheckEffect(){
	m_pCoil = NULL;
	SafeDeletePointerMap( m_ItemMap_Target );
	m_ItemMap_Target.clear();
}

/*********************************
追加
*********************************/
void	CheckEffect::addEffect( float i_vPosX, float i_vPosY){
	EffectItem*	pItem	= new EffectItem;

	pItem->m_vPos		= D3DXVECTOR3( i_vPosX, i_vPosY, 0.0f );
	pItem->m_vScale		= D3DXVECTOR3( EFFECT_SIZE*4, EFFECT_SIZE, 1.0f );
	pItem->m_fInitPosX	= i_vPosX;
	pItem->m_bStart		= false;

	m_ItemMap_Target.insert(multimap<float,EffectItem*>::value_type(pItem->m_vPos.y,pItem));

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
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
void CheckEffect::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		update( it->second->m_vPos , it->second->m_fInitPosX, it->second->m_vScale, it->second->m_bStart,i_DrawPacket);
		setMatrix( it->second->m_vPos, it->second->m_vScale );
		setTexDraw(i_DrawPacket);
		++it;
	}
}

/*********************************************************************
エフェクトをひとつだけ描画
*********************************************************************/
void	CheckEffect::PointDraw(DrawPacket &i_DrawPacket){
	if( m_vPointScale.x < EFFECT_SIZE*3 )
		Expansion();
	//m_vPointScale.x	= EFFECT_SIZE*3;
	//m_vPointScale.y	= EFFECT_SIZE*3;
	setMatrix( m_vPointPos, m_vPointScale );
	setTexDraw(i_DrawPacket);
}

/**********************************************************
**********************************************************/
void	CheckEffect::setTexDraw(DrawPacket& i_DrawPacket){
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
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_Matrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
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
void CheckEffect::update( D3DXVECTOR3& o_vPos, float i_fInitPosX , D3DXVECTOR3& o_vScale, bool& o_bStart,DrawPacket& i_DrawPacket){

	if( !m_pCoil   ) m_pCoil   = (PlayerCoil*)i_DrawPacket.SearchObjectFromID( OBJID_3D_COIL );
	//スタート位置にエフェクトを出すか
	if( o_bStart ){
		if( o_vScale.x > 0.0f && o_vScale.y > 0.0f ){
			if( m_pCoil != NULL ){
				Pos_Update(o_vPos.x);
			}
			Reduction( o_vScale );	//縮小
			m_bVanish	= false;
		}
		else	ResetState( o_vPos, i_fInitPosX, o_vScale, o_bStart );
	}

}

/*******************************************************
マトリックスの設定
*******************************************************/
void	CheckEffect::setMatrix( const D3DXVECTOR3 i_vPos, const D3DXVECTOR3 i_vScale ){
	//計算はUpdateで
	//拡大縮小
	D3DXMATRIX mScale;
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling( &mScale, i_vScale.x, i_vScale.y, 1.0f );
	//回転
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	//移動用
	D3DXMATRIX mMove;
	D3DXMatrixIdentity(&mMove);
	D3DXMatrixTranslation(&mMove,i_vPos.x,i_vPos.y,i_vPos.z);
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
void	CheckEffect::Pos_Update( float& o_fPosX ){
	float	MigrationRate	= m_pCoil->getStartPos().x - o_fPosX;
	//描画すべき位置を算出
	o_fPosX	+= MigrationRate/10.0f + 0.2f;
	if( MigrationRate > 0.0f ){
		o_fPosX	+= MigrationRate/10.0f + 0.2f;
		if( m_pCoil->getStartPos().x - o_fPosX < 0.0f )
			o_fPosX	= m_pCoil->getStartPos().x;
	}
	else if( MigrationRate < 0.0f ){
		o_fPosX	+= MigrationRate/10.0f - 0.2f;
		if( m_pCoil->getStartPos().x - o_fPosX > 0.0f )
			o_fPosX	= m_pCoil->getStartPos().x;
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
void	CheckEffect::Reduction( D3DXVECTOR3& o_vScale ){
	o_vScale.x	-= 0.2f;
	o_vScale.y	-= 0.05f;
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
	m_vPointScale.x	+= 0.08f;
	m_vPointScale.y	+= 0.08f;
}

/************************************************
もろもろのリセット
************************************************/
void	CheckEffect::ResetState( D3DXVECTOR3& o_vPos, float i_fInitPosX, D3DXVECTOR3& o_vScale, bool& o_bStart ){

	o_bStart		= false;
	m_bVanish		= true;
	o_vScale.x		= EFFECT_SIZE*4 ;
	o_vScale.y		= EFFECT_SIZE;
	m_vPointScale	= g_vZero;
	o_vPos.x		= i_fInitPosX;
	o_vPos.y		= m_fPosY;
}

/************************************************************************
全てのエフェクトにアニメーション開始フラグをたてる
************************************************************************/
void	CheckEffect::setStart( bool i_bStart ){
	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		it->second->m_bStart	= i_bStart;
		++it;
	}
}
/**************************************************************
チェックエフェクトのY座標初期位置
**************************************************************/
void	CheckEffect::setInitPosY(float posY){

	multimap<float,EffectItem*>::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		it->second->m_vPos.y	= posY;
		++it;
	}
}

/******************************************
チェックポイントの描画位置更新（Y座標）
******************************************/
void	CheckEffect::setPosY(float posY){
	m_fPosY	= posY;
}

/****************************************************************************
CheckPoint 定義部
****************************************************************************/
CheckPoint::CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPTATRATEXTURE pTexture,LPTATRATEXTURE pTexture2,LPTATRATEXTURE pTexture3, wiz::OBJID id  )
:Object( id )
,m_Effect(pD3DDevice, g_vZero, fLength, pTexture)
,m_PintMark(pD3DDevice, pTexture2, CHECK_POINT_CHAR_SIZE, g_vZero, g_vZero,&Rect( 0, 0, 512, 64 ), D3DXVECTOR3( 256.0f, 32.0f, 0.0f ), D3DXVECTOR3( 0.0f, -87.0f, 0.0f ))
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_ActiveItem( NULL )
,m_pTime( NULL )
,m_Color( CHECKPOINTCOLOR )
,m_Thicken( 1.0f )
,m_Length( fLength )
,m_pTextureLast( pTexture3 )
,m_bPlayerPass( false )
,m_bFirstRead( true )
{
	Debugger::DBGWRITINGLOGTEXT::addStr(L"CheckPoint::CheckPoint OK\n");
}
CheckPoint::~CheckPoint(){
	m_pCoil		= NULL ;
	m_pCamera	= NULL ;
	m_pTime		= NULL ;
	SafeDeletePointerContainer( m_ItemContainer ) ;
	m_ItemContainer.clear();
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
	if( !m_pTime )		m_pTime	= ( TimeScore* )i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME );
	if( !m_pCoil   )	m_pCoil	= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL	) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}

	float	fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;
	//全てのチェックポイントを通っていなかったら入る
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){

		setTexPos( m_ActiveItem, fTexPosY );

		if( m_bFirstRead ){
			m_Effect.setInitPosY(m_ItemContainer[ m_ActiveItem ]->fPosY);
			m_bFirstRead	= false;
		}

		PlayerPass(i_UpdatePacket);
		//コイルがチェックポイントを通過したか
		if( m_bPlayerPass ){
			if( m_ActiveItem < m_ItemContainer.size() ){
				//エフェクトの更新***********************************************

				m_Effect.setPointPos( m_pCoil->getStartPos() );				//復帰地点の位置を渡す
				m_Effect.setPosY( m_ItemContainer[ m_ActiveItem ]->fPosY );	//チェックポイントの位置を渡す
				m_Effect.setStart( true );									//アニメーションを開始
				
				//******************************************************************
			}
			m_bPlayerPass	= false;
		}

	}
	else{
		setTexPos( m_ActiveItem-1, fTexPosY );	//最後までいったらテクスチャ座標の更新を１つ前で固定
	}

};

/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
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
			
			//	:　メッセージ？を描画
			m_PintMark.Draw(i_DrawPacket);

		}

		Debugger::DBGSTR::addStr(L"m_ActiveItem = %d\n",m_ActiveItem);
	}
	else/* if(m_ActiveItem == m_ItemContainer.size()-1)*/{
		m_PintMark.Draw(i_DrawPacket);
	}

	//チェックポイントの描画
	m_Effect.Draw( i_DrawPacket );
	//一度でもチェックポイントを通過したら入る
	//復帰地点の描画
	if(m_Effect.getVanish())	m_Effect.PointDraw( i_DrawPacket );
		
};

/*************************************************
コイルがチェックポイントを通過したか
*************************************************/
void	CheckPoint::PlayerPass(UpdatePacket &i_UpdatePacket){

	float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
	float fCoilPosY = m_pCoil->getPos().y;

	if(fPosY <= fCoilPosY){
		m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		m_ActiveItem++;
		m_pCoil->setRecordTime();
		m_pTime->setTime();
		if(m_ActiveItem == m_ItemContainer.size()-1){
			m_PintMark.setTexture(m_pTextureLast);
			m_PintMark.setCenter(D3DXVECTOR3( 128.0f, 32.0f, 0.0f ));
		}
		m_bPlayerPass	= true;	//通過フラグをたてる
		i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
	}
}

/*************************************************
文字テクスチャの座標指定
*************************************************/
void	CheckPoint::setTexPos( size_t i_ActiveItem, float fTexPosY ){
	float	wide	= 0;
	float	height	= 0;
	//CHECK POINT テクスチャ*************************************************************
	wide	= BASE_CLIENT_WIDTH / 50 * m_ItemContainer[ i_ActiveItem ]->vStartPos.x * CHECKPOINT_CHAR_RATE_X;
	height	= ( (m_ItemContainer[ i_ActiveItem ]->vStartPos.y - fTexPosY)
									* CHECKPOINT_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * CHECKPOINT_CHAR_RATE_Y;
	D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,CHECK_POINT_CHAR_SIZE.x,CHECK_POINT_CHAR_SIZE.y,CHECK_POINT_CHAR_SIZE.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
	D3DXMatrixTranslation(&mPos, wide,height,0.0f);
	mTexMatrix	= mPos*mScale*mRot;
	m_PintMark.setMatrix( mTexMatrix );
	//*************************************************************************************
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