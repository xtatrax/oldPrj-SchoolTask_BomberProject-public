////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	引継ぎ			：曳地 大洋
//	└→			：本多 寛之
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Magnetic ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Magnetic.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{


///**************************************************************************
// PlaneCircle 定義部
//****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
MagnetFieldCircle::MagnetFieldCircle(LPDIRECT3DDEVICE9 pD3DDevice,DWORD dwVertexQty){

	m_dwVertexQty	= dwVertexQty  +1 ;
	float iRotSize	= 360.0f / (dwVertexQty -1) ;
	Vertex* m_pVertex;

	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * m_dwVertexQty , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: 頂点データのアドレスを取得するとともに、データへのアクセスを開始する	

	m_pVertex[ 0 ]	= Vertex( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) , 0x3FFFFFFF );

	for ( DWORD i = 1 ; i < m_dwVertexQty  ; i++ ){
		m_pVertex[ i ]	= Vertex( D3DXVECTOR3(  cosf( D3DXToRadian( iRotSize * i ) ) , sinf(D3DXToRadian( iRotSize * i ) ) , 0.0f )	, 0x3FFFFFFF );
	}
	m_pVertexBuffer->Unlock();
	D3DXMatrixScaling( &m_mMatrix, 10.0f, 10.0f, 1.0f );
}

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void MagnetFieldCircle::Draw(DrawPacket& i_DrawPacket){
	 //ワールド変換行列を設定
	i_DrawPacket.pD3DDevice->SetTransform( D3DTS_WORLD , &m_mMatrix );								//変換済み頂点の場合は無視される

	i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
    i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	////頂点アルファを使えるようにするデフォルトでもこのように設定されている
 //   i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);
 //   //上の設定を有効にする
 //   i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE); 

	//	: 頂点バッファを用いてモデルを描画する
	i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	i_DrawPacket.pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: 描画対象となる頂点バッファを設定
	i_DrawPacket.pD3DDevice->SetFVF( Vertex::getFVF() );											//	: 頂点データの形式を設定
	i_DrawPacket.pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN  , 0, m_dwVertexQty  );	//	: 頂点データの描画（描画の仕方、描画開始位置、プリミティブ数）
	i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    //i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_COLORVERTEX, FALSE); 
	i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
}



//3D変換用
/**************************************************************************
 MagneticumObject3D 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：MagneticumObject3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：曳地 大洋
//// 備考       ：
////            ：
////
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	wiz::OBJID id 								//	: ID
)
:PrimitiveCylinder(
				   pD3DDevice,
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   id,
				   NULL)
,m_bMagnetPole( POLE_S )
,m_fMagneticum((float)MGPRM_MAGNETICUM)
,m_MagneticField( pD3DDevice, 32 )
,m_pCoil(	NULL )
,m_pCamera(	NULL )
,m_fEffectSizeRate(0)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
}
/////////////////// ////////////////////
//// 用途       ：MagneticumObject3D(
////									LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////									float Radius1,float Radius2,float Lenght,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////									D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////									wiz::OBJID id = OBJID_3D_MAGNET) ;
//// カテゴリ   ：コンストラクタ
//// 用途       ：Player用のコンストラクタ
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
////			  :   LPDIRECT3DTEXTURE9 pTexture,  //テクスチャ	
////		      :   Radius1						//円の直径1
////		      :   Radius2						//円の直径2
////			  :   Lenght						//高さ
////		      :   D3DXVECTOR3 &vRot				//回転角
////		      :   D3DXVECTOR3 &vPos				//位置
////              :   D3DCOLORVALUE& Diffuse,		//ディフューズ色
////              :   D3DCOLORVALUE& Specular,		//スペキュラ色
////              :   D3DCOLORVALUE& Ambient,		//アンビエント色
////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
//// 戻値       ：無し
//// 担当者     ：本多寛之
//// 備考       ：
////	
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTexture,
	float Radius1,
	float Radius2,
	float Lenght,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DCOLORVALUE& Diffuse,
	D3DCOLORVALUE& Specular,
	D3DCOLORVALUE& Ambient,
	wiz::OBJID id) 
:PrimitiveCylinder(
		   pD3DDevice,pTexture,
		   Radius1,Radius2,Lenght,
		   vRot,vPos,
		   Diffuse,Specular,Ambient,
		   id)
,m_bMagnetPole( POLE_N )
,m_MagneticField( pD3DDevice, 32 )
,m_pCoil(NULL)
,m_pCamera(	NULL )
,m_fEffectSizeRate(0)

{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
}
/////////////////// ////////////////////
//// 用途       ：  ~MagneticumObject3D()
//// カテゴリ   ：コンストラクタ
//// 用途       ：Player用のコンストラクタ
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////	
MagneticumObject3D::~MagneticumObject3D(){
	//磁界　外側
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();

}

void MagneticumObject3D::setDrawTarget(){

	//////////
	//	描画対象外の削除
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin(),
								TIMend = m_ItemMap_Target.end(  );
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


/////////////////// ////////////////////
//// 関数名     ：void Update( UpdatePacket& i_UpdatePacket )
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
void MagneticumObject3D::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera )	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA	) ;
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;

	setDrawTarget();

	m_fEffectSizeRate += i_UpdatePacket.pTime->getElapsedTime() / MGPRM_EFFECTINTERVAL ;
	Debugger::DBGSTR::addStr(L"m_fEffectSizeRate = %f\n",m_fEffectSizeRate);
	m_fEffectSizeRate >= 1.0f && ( m_fEffectSizeRate = 0 ) ;

}
/////////////////// ////////////////////
//// 用途       ：void Draw( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：  DrawPacket& i_DrawPacket             // 画面描画時に必要なデータ群 ↓内容下記
////			   ：  ├ LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 インターフェイスへのポインタ
////			   ：  ├ vector<Object*>&    Vec                     // オブジェクトの配列
////			   ：  ├ Tempus2*            i_DrawPacket.pTime	   // 時間を管理するクラスへのポインター
////               ：  └ Command             i_DrawPacket.pCommand   // コマンド
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
void MagneticumObject3D::Draw(DrawPacket& i_DrawPacket)
{
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);

		//	: 色の決定
		m_MagneticField.setPole(pNowItem->m_bMagnetPole);

		//////////
		//	: 基本Matrixの準備
		D3DXMATRIX mAll, mScale, mMove;

		D3DXMatrixTranslation(&mMove,
			pNowItem->m_vPos.x,
			pNowItem->m_vPos.y,
			pNowItem->m_vPos.z-0.2f
		);
		//	: 基本Matrixの準備
		//////////

		//////////
		//	: 範囲の描画

		//	: 分割数
		BYTE byPartitionQty = 3 ;

		float fCircleSize ;
		for( BYTE i = byPartitionQty ; i >= 1 ; i-- ){
			fCircleSize = (float)MGPRM_MAGNETICUM * ( (float)i/(float)byPartitionQty ) ;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.0f);
			mAll = mScale * mMove;
			m_MagneticField.setMatrix(mAll) ;
			m_MagneticField.Draw(i_DrawPacket);
		}
		//	: 範囲の描画
		//////////


		//////////
		//	: エフェクトの描画
		if( pNowItem->m_bMagnetPole == m_pCoil->getMagnetPole() )
			fCircleSize =(float)MGPRM_MAGNETICUM * m_fEffectSizeRate;
		else
			fCircleSize =(float)MGPRM_MAGNETICUM * (1.0f-m_fEffectSizeRate);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.0f);
		mAll = mScale * mMove;
		m_MagneticField.setMatrix(mAll) ;
		m_MagneticField.Draw(i_DrawPacket);
		//	: エフェクトの描画
		//////////

		++it;
	}
}

/////////////////// ////////////////////
//// 用途       ：void AddMagnetic( DrawPacket& i_DrawPacket )
//// カテゴリ   ：関数
//// 用途       ：マグネットの追加
//// 引数       ：  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
////		    ：  D3DXVECTOR3 &vScale				//拡大縮小
////		    ：  D3DXVECTOR3 &vRot				//回転角
////		    ：  D3DXVECTOR3 &vPos				//位置
////            ：  D3DCOLORVALUE& Diffuse,			//ディフューズ色
////            ：  D3DCOLORVALUE& Specular,		//スペキュラ色
////            ：  D3DCOLORVALUE& Ambient,			//アンビエント色
//// 戻値       ：無し
//// 担当者     ：曳地 大洋
//// 備考       ：
void MagneticumObject3D::AddMagnetic(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,POLE vPole,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem			= new Magnet3DItem	;
	pItem->m_bHidden			= true				;
	pItem->m_vPos				= vPos				;
	pItem->m_fMapKey			= vPos.y			;
	pItem->m_bMagnetPole		= vPole				;


	m_ItemMap_All.insert(multimap<float,Magnet3DItem*>::value_type(pItem->m_vPos.y,pItem));	
}
void MagneticumObject3D::HitTest(){
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);
		if(m_pCoil->CheckDistance(pNowItem->m_vPos ,(float)MGPRM_MAGNETICUM_QUAD, false))
			m_pCoil->m_fMoveDir = m_pCoil->MagneticDecision(m_pCoil->m_fMoveDir,pNowItem->m_vPos,pNowItem->m_bMagnetPole);
		it++;
	}
}
/////////////////// ////////////////////
//// 用途       ：bool MagneticumObject3D::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
//// カテゴリ   ：関数
//// 用途       ：距離を判定
//// 引数       ：D3DXVECTOR3& i_vMagneticFieldPos //磁界の位置 
////　　　　　　：D3DXVECTOR3& i_vCoilPos          //コイルの位置
////　　　　　　：float        i_iBorder           //判定する値
//// 戻値       ：true , false
//// 担当者     ：本多寛之
//// 備考       ：
//bool MagneticumObject3D::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const{
//	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, i_vCoilPos ) ;
//	if( Lng <= i_iBorder ){
//		return true;
//	}
//	else{
//		return false;
//	}
//}

/**************************************************************************
 Factory_Magnetic 定義部
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	Factory_Magnetic *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
		// シリンダーオブジェクトのマテリアル
		D3DCOLORVALUE MagnetDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		D3DCOLORVALUE MagnetSpecular = { 0.0f, 0.0f, 0.0f, 0.0f } ;
		D3DCOLORVALUE MagnetAmbient  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		// 磁界の表示
		//MagneticumObject3D* Magnet = new MagneticumObject3D(
		//	fpac->pD3DDevice,
		//	NULL,//fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"ddn.jpg")
		//);
		//fpac->m_pVec->push_back(Magnet);

		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,10.0f,0.0f),
		//			  POLE_N,
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);

		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,30.0f,0.0f),
		//			  POLE_S,
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Magnetic::~Factory_Magnetic();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Magnetic::~Factory_Magnetic(){
    //なにもしない
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
