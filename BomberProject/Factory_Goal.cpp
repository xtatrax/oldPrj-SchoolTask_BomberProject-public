////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Goal.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：ゴールファクトリー
//					▼
//	namespace wiz;
//		class GoalObject ;
//		class Factory_Goal ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Goal.h"
#include "Factory_Wall.h"
#include "BassItems.h"

const D3DXVECTOR3	GOAL_CHAR_SIZE			= D3DXVECTOR3(1.0f,1.0f,0.0f);
const	float		GOAL_CHAR_RATE_Y		= (1.0f/GOAL_CHAR_SIZE.y);
const	float		GOAL_CHAR_RATE_X		= (1.0f/GOAL_CHAR_SIZE.x);
const	float		GOAL_CHAR_DOWNSPEED		= 20.0f;

namespace wiz{
namespace bomberobject{

/**************************************************************************
 FMemoryTex 定義部
****************************************************************************/
/**************************************************************************
 FMemoryTex::FMemoryTex(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	LPDIRECT3DTEXTURE9 pTexture,	//テクスチャ
	wiz::OBJID id					//オブジェクトの種類
);
 用途: コンストラクタ
 戻り値: なし
 担当：佐藤涼
***************************************************************************/
FMemoryTex::FMemoryTex( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
	,m_pCamera( NULL )
	,m_pCoil( NULL )
	,m_bEnding( false )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_iPtn		= 1;

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
void FMemoryTex::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,mItem*>::iterator it = m_ItemMap_Target.begin();
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
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
//// 担当者     ：佐藤涼
//// 備考       ：
////            ：
////
void FMemoryTex::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera	)	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA	) ;
	if( !m_pCoil	)	m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;

	m_ItemMap_Target.clear();
	multimap<float,mItem*>::iterator it = m_ItemMap_Memory.begin();
	while(it != m_ItemMap_Memory.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,mItem*>::value_type(it->second->vPos.y,it->second));
		}
		++it;
	}


	multimap<float,mItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		if( m_pCoil->getState() == COIL_STATE_CLEAR ){
			OrientGoal( i_UpdatePacket );
		}

		//計算はUpdateで
		//拡大縮小
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->vScale.x,it2->second->vScale.y,it2->second->vScale.z);
		//回転
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->vRot);
		//移動用
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->vPos.x,it2->second->vPos.y,it2->second->vPos.z);
		//ミックス行列
		it2->second->mMatrix = mScale * mRot * mMove;
		//マティリアル設定
		m_Material = it2->second->mMaterial;

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
//// 戻値       ：無し
//// 担当者     ：佐藤涼
//// 備考       ：
void FMemoryTex::AddMemory(const D3DXVECTOR3 &vScale,const D3DXVECTOR3 &vRot,const D3DXVECTOR3 &vPos,
			const D3DCOLORVALUE& Diffuse,const D3DCOLORVALUE& Specular,const D3DCOLORVALUE& Ambient)
{
	mItem* pItem = new mItem;
	pItem->vScale = vScale;
	pItem->vPos	= vPos;
    ::ZeroMemory(&pItem->mMaterial,sizeof(D3DMATERIAL9));
	pItem->mMaterial.Diffuse = Diffuse;
	pItem->mMaterial.Specular = Specular;
	pItem->mMaterial.Ambient = Ambient;
	//回転の初期化
	D3DXQuaternionRotationYawPitchRoll(&pItem->vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Memory.insert(multimap<float,mItem*>::value_type(pItem->vPos.y,pItem));

	m_vPos		= vPos;
	m_vScale	= vScale;
}

/****************************************************
関数名　：void	OrientGoal(UpdatePacket& i_UpdatePacket)
カテゴリ：関数
用途　　：クリア後プレーヤーを動かす
引数　　：なし
戻り値　：なし
担当者　：佐藤涼
備考　　：
****************************************************/
void FMemoryTex::OrientGoal(UpdatePacket& i_UpdatePacket){
	//コイルの現在の情報を得る
	D3DXVECTOR3	move		= m_pCoil->getPos();	//位置
	D3DXVECTOR3	scale		= m_pCoil->getScale();	//大きさ
	float		dir			= m_pCoil->getDir();	//進行方向

	const float	rate		= 0.1f;			//移動する速さ
	const float	ScaleRate	= rate*rate;	//大きさの変化率
	const float DirRate		= rate*60;		//角度の変化率
	const float	OrientPos	= m_vPos.x + (m_vScale.x / 2 - 4) -7.3f ;	//向かうべき位置

	int			dirPtn		= 1;		//向くべき角度を示す
	const float	TopDir		= 90.0f;	//上を向いた時のの角度
	const float	RightDir	= 0.0f;		//右を向いた時のの角度
	const float	LeftDir		= 180.0f;	//左を向いた時のの角度

	static float LeastScale	= 0.3f;	//最も縮小した時の大きさ

	//****************************
	//大きさの変更
	if( scale.x > LeastScale ){
		scale.x	-= ScaleRate;
		scale.y	-= ScaleRate;
		scale.z	-= ScaleRate;
	}
	else{
		scale.x	= LeastScale;
		scale.y	= LeastScale;
		scale.z	= LeastScale;

		if( scale.x == 0 )	m_bEnding	= true;
	}
	//****************************
	//位置の変更
	switch( m_iPtn ){
		case 1:	if( m_vPos.y-1.0f >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 2;
				break;
		case 2:	if( OrientPos > move.x ){
					move.x	+= rate;
					dirPtn	= 2;	//右
					if( OrientPos < move.x )
						move.x	= OrientPos;
				}
				else if( OrientPos < move.x ){
					move.x	-= rate;
					dirPtn	= 3;	//左
					if( OrientPos > move.x )
						move.x	= OrientPos;
				}
				else	m_iPtn	= 3;
				break;
		case 3:	if( m_vPos.y + 1.4 >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 4;
				dirPtn	= 1;
				break;
		case 4:	if( m_vPos.x <= move.x ){
					move.x	-= rate;
					dirPtn	 = 3;
				}
				else{
					m_iPtn		= 5;
					LeastScale	= 0;
				}
				break;
		default:
				break;
	}
	//****************************
	//角度の変更
	switch( dirPtn ){
		case 1:	//上
			if( dir > TopDir )
				dir	-= DirRate;
			else if( dir < TopDir )
				dir	+= DirRate;
			break;

		case 2:	//右
			if( dir > RightDir )
				dir	-= DirRate;
			else if( dir < RightDir )
				dir	+= DirRate;
			break;

		case 3:	//左
			if( dir > LeftDir )
				dir	-= DirRate;
			else if( dir < LeftDir )
				dir	+= DirRate;
			break;
	}
	//**************************************************

	if( !m_bEnding ){
		m_pCoil->setPos(move);
		m_pCoil->setScale(scale);
		m_pCoil->setDir(dir);
	}
	else{ 
		static float s_fTimeCount = 0.0f;
		s_fTimeCount += (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeCount >= 0.5f){
			i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_CLEAR;
			i_UpdatePacket.pCommand->m_Param1	= m_pCoil->getDeadCount();
			i_UpdatePacket.pCommand->m_Param2	= m_pCoil->getMaxPos();
			i_UpdatePacket.pCommand->m_Param3	= m_pCoil->getScratchTime();
			s_fTimeCount = 0.0f;
			LeastScale	 = 0.3f;
		}
	}
}

/**************************************************************************
 GoalObject 定義部
****************************************************************************/
/***************************************************************************
関数名　　：GoalObject(
                   FactoryPacket* fpac,
                   LPDIRECT3DTEXTURE9 pTexture,
                   wiz::OBJID id
              )
カテゴリ　：コンストラクタ
用途　　　：
引数　　　：FactoryPacket* fpac           //デバイスなど
　　　　　：LPDIRECT3DTEXTURE9 pTexture   //テクスチャ―
　　　　　：wiz::OBJID id                 //ID
戻り値　　：
担当者　　：佐藤涼
備考　　　：
****************************************************************************/
GoalObject::GoalObject( LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 vPos , LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DTEXTURE9 pGoakCharTex,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pCoil( NULL )
,m_pCamera( NULL )
,m_bPlaySound( true )
,m_pGoalCharTex( pGoakCharTex )
,m_fInitPosY( 0 )
{
	try{
		D3DXVECTOR3		vScale = D3DXVECTOR3( 100.0f, 1.0f, 0.0f) ;
		SetBasePos(		vPos	);
		SetBaseScale(	vScale	);

		m_Obb = OBB( vScale, g_vZero, vPos );
		this->CalcWorldMatrix();
        // D3DMATERIAL9構造体を0でクリア
		m_Material.Diffuse	= COLOR2D3DCOLORVALUE(0xFFFFFF00);
		m_Material.Specular	= COLOR2D3DCOLORVALUE(0xFFFFFF00);
		m_Material.Ambient	= COLOR2D3DCOLORVALUE(0xFFFFFF00);

		m_pGoalChar	= 	new SpriteObject( pD3DDevice, m_pGoalCharTex, GOAL_CHAR_SIZE, g_vZero, g_vZero,
									Rect( 0, 0, 256, 64 ), D3DXVECTOR3( 128.0f, 32.0f, 0.0f ), D3DXVECTOR3( 100.0f, -87.0f, 0.0f ));

	}
	catch(...){
		//再スロー
		throw;
	}
}
GoalObject::~GoalObject(){
	
	m_pCoil		= NULL ;
	m_pGoalChar	= NULL;
	m_pCamera	= NULL;
	//SafeDeletePointerMap( m_ItemMap_All ) ;


}
/**************************************************************
関数名　　：void GoalObject::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket   //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************/
void	GoalObject::Draw(DrawPacket &i_DrawPacket){
	PrimitiveBox::Draw( i_DrawPacket );
	m_pGoalChar->Draw( i_DrawPacket );
}

/*******************************************************************
関数名　　：void GoalObject::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket  //もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
関数名     ：void	 GoalObject::Update(UpdatePacket& i_UpdatePacket)
用途       ：データ更新
********************************************************************/
void	GoalObject::Update(UpdatePacket& i_UpdatePacket)
{
	if( !m_pCoil  ) m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;
	if( !m_pCamera ){
		m_pCamera = (    Camera*)SearchObjectFromID( i_UpdatePacket.pVec, OBJID_SYS_CAMERA ) ;
		m_fInitPosY	= 	m_pCamera->getPosY();
	}


	//衝突判定
	if( m_pCoil && m_pCoil->HitTestWall( m_Obb ) ){
		m_pCoil->setState( COIL_STATE_CLEAR );
		m_pCoil->setSuperMode(COIL_STATE_SUPER_CHARGE);
		if( m_bPlaySound ){
			i_UpdatePacket.SearchSoundAndPlay( RCTEXT_SOUND_SE_GOAL );
			m_bPlaySound	= false;
		}
	}

	//*****************************************************************************************************
	//ゴールの文字
	float	fTexPosY	= 0.0f;
	if( m_pCamera )
		fTexPosY	= m_pCamera->getPosY() - m_fInitPosY;

	D3DXVECTOR3	p;
	GetWorldPos(p);
	float	m_fGoalPosX = p.x;
	float	m_fGoalPosY = p.y;

	float	wide	= BASE_CLIENT_WIDTH / 50 * m_fGoalPosX * GOAL_CHAR_RATE_X;
	float	height	= ( (m_fGoalPosY - fTexPosY)
								* GOAL_CHAR_DOWNSPEED - BASE_CLIENT_HEIGHT ) * (-1.0f) * GOAL_CHAR_RATE_Y;

	D3DXMATRIX mTexMatrix, mScale, mRot, mPos;
	D3DXMatrixScaling(&mScale,GOAL_CHAR_SIZE.x,GOAL_CHAR_SIZE.y,GOAL_CHAR_SIZE.z);
	D3DXMatrixRotationZ(&mRot,D3DXToRadian(0));
	D3DXMatrixTranslation(&mPos, wide,height,0.0f);
	mTexMatrix	= mPos*mScale*mRot;
	m_pGoalChar->setMatrix( mTexMatrix );

}


/**************************************************************************
 Factory_Goal 定義部
****************************************************************************/
/**************************************************************************
 Factory_Goal::Factory_Goal(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Goal::Factory_Goal(FactoryPacket* fpac){
	try{
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Goal::~Factory_Goal();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Goal::~Factory_Goal(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
