////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_CheckPoint.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：本多 寛之
//	編集			：佐藤 涼
//	内包データと備考	：チェックポイント
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
/****************************************************************************
RestartPoint 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
RestartPoint::RestartPoint(
	const LPDIRECT3DDEVICE9	pD3DDevice	,
	const LPTATRATEXTURE	pPointTex
)
:Box( pD3DDevice, g_vOne, D3DXVECTOR3( -10.0f, 0.0f, 0.0f ), g_vZero, CHECKPOINTCOLOR, CHECKPOINTCOLOR, CHECKPOINTCOLOR, OBJID_SYS_RESTARTPOINT, false, pPointTex)
,m_fSize(0.0f)
{
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
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void RestartPoint::Update(UpdatePacket &i_UpdatePacket){
	if( m_fSize < EFFECT_SIZE ){
		m_fSize += 0.1f;
	}else{
		m_fSize = EFFECT_SIZE ;
	}
	m_BaseScale = g_vOne * m_fSize ;
	m_BaseScale.z = 0;
	CalcWorldMatrix();
}
/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
//// 担当者     ：鴫原 徹 本多寛之(編集)
//// 備考       ：
////            ：
////
void RestartPoint::Draw( DrawPacket& i_DrawPacket ){
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
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
	}
		
};

/****************************************************************************
CheckPoint 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
CheckPoint::CheckPoint(
		LPDIRECT3DDEVICE9	pD3DDevice				,
		float				fLength					,
		LPTATRATEXTURE		pLineTex				,
		LPTATRATEXTURE		pCheckPointStringTex	,
		LPTATRATEXTURE		pLastStingTex			,
		wiz::OBJID			id
)
:Box( pD3DDevice, D3DXVECTOR3(1.0f,1.0f,0.0f),g_vZero, g_vZero, CHECKPOINTCOLOR, CHECKPOINTCOLOR, CHECKPOINTCOLOR, id, false, pLineTex )
,m_pTxLine( pLineTex )
,m_pTxCheckString( pCheckPointStringTex )
,m_pTxLastString(  pLastStingTex )
,m_enumNowState( BEHAVIORSTATE_WAIT )
,m_fBassLength( fLength )
,m_fReductionTime(0.7f)
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_pRestartPoint( NULL )
,m_ActiveItem( NULL )
,m_pTime( NULL )
,m_vLineScale(1.0f,2.0f,0.0f)
,m_vStringScale(1.0f,2.0f,0.0f)
{
	m_vLineScale.x		= fLength ;
	m_vStringScale.x	= fLength / 4;
	Box::m_BasePos.x	= 25 ;
}
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：デストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
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
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：継承したものでも必ずとも定義をしなくても良い
////            ：
////
void CheckPoint::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pTime         )	m_pTime			= (   TimeScore*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_TIME			) ;
	if( !m_pCoil         )	m_pCoil			= (  PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL			) ;
	if( !m_pCamera       )	m_pCamera		= (      Camera*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA		) ;
	if( !m_pRestartPoint )	m_pRestartPoint	= (RestartPoint*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_RESTARTPOINT	) ;


	//全てのチェックポイントを通っていなかったら入る
	if( m_pCoil && m_ActiveItem < m_ItemContainer.size()){
		//	: もし待機状態だったら プレイヤーが通過したか確認する
		switch( m_enumNowState ){
			case BEHAVIORSTATE_WAIT :
				//	: コイルの通過を待機
				PlayerPass(i_UpdatePacket);
				break ;
			case BEHAVIORSTATE_REDUCTION :
				//	: 縮小エフェクト
				Reduction(i_UpdatePacket);
				break;
		}
	}
	
};
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：プレイヤー通過時の動作
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
void	CheckPoint::PlayerPass(UpdatePacket &i_UpdatePacket){

	float fPosY		= m_ItemContainer[ m_ActiveItem ]->fPosY;
	float fCoilPosY = m_pCoil->getPos().y;

	if(fPosY <= fCoilPosY){
		m_enumNowState = BEHAVIORSTATE_REDUCTION ;
		m_pCoil->setStartPos(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		//m_ActiveItem++;
		m_pCoil->setRecordTime();
		m_pTime->setTime();

		i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_CHECKPOINT );
	}
}
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：プレイヤー通過時の動作
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
CheckPoint::WORKSTATE CheckPoint::Reduction(UpdatePacket &i_UpdatePacket){
	m_vLineScale.x		-= m_fBassLength / m_fReductionTime * (float)i_UpdatePacket.GetTime()->getElapsedTime() ;
	if(!ActiveIsLast()){
		m_vStringScale.x	-= m_fBassLength / 4 / m_fReductionTime * (float)i_UpdatePacket.GetTime()->getElapsedTime() ;
		m_vStringScale.y	-= 2 / m_fReductionTime * (float)i_UpdatePacket.GetTime()->getElapsedTime() ;
	}
	if( m_vLineScale.x >= 0.0f ){
		return WORKSTATE_UNFINSHED ;
	}
	else{
		if( m_pRestartPoint ) m_pRestartPoint->ChangePoint(m_ItemContainer[ m_ActiveItem ]->vStartPos);
		if( ActiveIsLast() ){
			m_enumNowState = BEHAVIORSTATE_LAST ;
			m_vLineScale = g_vZero ;
			return WORKSTATE_COMPLETION ;
		}
		m_ActiveItem++;
		if( m_ActiveItem >= m_ItemContainer.size()){
			m_enumNowState = BEHAVIORSTATE_LAST ;
		}else{
			m_vLineScale.x = m_fBassLength ;
			m_vStringScale.x = m_fBassLength /4 ;
			m_vStringScale.y = 2;
			m_BasePos.y = m_ItemContainer[ m_ActiveItem ]->fPosY ;
			m_enumNowState = BEHAVIORSTATE_WAIT;
		}
		return WORKSTATE_COMPLETION ;
	}
}
/////////////////// ////////////////////
//// 用途       ：virtual void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：純粋仮想関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////            ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////            ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////            ：  ├ Tempus2*            i_DrawPacket.GetTime()	   // 時間を管理するクラスへのポインター
////            ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：なし
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
			//////////
			//	: 
			m_pTexture = m_pTxLine ;
			Box::m_BasePos.y	= m_ItemContainer[ m_ActiveItem ]->fPosY;
			Box::m_BaseScale	= m_vLineScale;
			Box::CalcWorldMatrix();
			DrawLine(i_DrawPacket);
			//	: 
			//////////

		}
	}
		
};

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
void CheckPoint::DrawLine( DrawPacket& i_DrawPacket ){
	if(m_pTexture){
		DWORD wkdword;
		//現在のテクスチャステータスを得る
		i_DrawPacket.GetDevice()->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);

		//////////
		//
		//ステージの設定
		i_DrawPacket.GetDevice()->SetTexture(0,m_pTexture->getTexture());
		//デフィーズ色とテクスチャを掛け合わせる設定
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_ADD );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
		//
		//////////
		//////////
		//	: テキストの描画
		Box::m_BaseScale	= m_vStringScale;
		//m_pTexture = m_pTxCheckString ;
		Box::CalcWorldMatrix();

		if(ActiveIsLast()){
			i_DrawPacket.GetDevice()->SetTexture(0,m_pTxLastString->getTexture());
		}else{
			i_DrawPacket.GetDevice()->SetTexture(0,m_pTxCheckString->getTexture());
		}
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.GetDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//i_DrawPacket.GetDevice()->SetFVF(PlateFVF);
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);

		//	: テキストの描画
		//////////

		i_DrawPacket.GetDevice()->SetTexture(0,0);
		//ステージを元に戻す
		i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
	//テクスチャがない場合
		// マトリックスをレンダリングパイプラインに設定
		i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
		//コモンメッシュのDraw()を呼ぶ
		CommonMesh::Draw(i_DrawPacket);
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
			fpac->AddObject( new RestartPoint( fpac->GetDevice(), fpac->AddTexture(L"particle.png") ) );
			//D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			//D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			//D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			//
			//CheckPoint* pcp ;
			//fpac->AddObject(
			//	pcp = new CheckPoint( fpac->GetDevice(), 100.0f, fpac->AddTexture( L"particle.png" ),)
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