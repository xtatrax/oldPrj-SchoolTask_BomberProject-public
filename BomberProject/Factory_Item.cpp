////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之
//	内包データと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Item ;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Item.h"
//#include "Factory_Player.h"

namespace wiz{
namespace bomberobject{




/**************************************************************************
 Item 定義部
****************************************************************************/
/***************************************************************************
関数名　　　：Item( FactoryPacket* fpac,
                      LPTATRATEXTURE pTexture,
                      wiz::OBJID id )
カテゴリ　　：コンストラクタ
用途　　　　：
引数　　　　：FactoryPacket* fpac           // : デバイスなど
　　　　　　：LPTATRATEXTURE pTexture   // : テクスチャ—
　　　　　　：wiz::OBJID id                 // : ID
戻り値　　　：
担当者　　　：佐藤涼
備考　　　　：
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPTATRATEXTURE pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->GetDevice(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						pTexture,
						id
	)
	,m_pPlayerCoil(NULL)
	,m_pSuperGage(NULL)
	,m_pCamera(NULL)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//再スロー
		throw;
	}
}
/////////////////// ////////////////////
//// 関数名     ：~Item();
//// カテゴリ   ：デストラクタ
//// 用途       ：破棄
//// 引数       ：なし
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
Item::~Item(){
	m_ItemMap_Target.clear();
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
}

/**************************************************************
関数名　　：void Item::Draw(DrawPacket &i_DrawPacket)
カテゴリ　：関数
用途　　　：オブジェクトの描画
引数　　　：DrawPacket &i_DrawPacket          // 描画用のもろもろ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();
	while(it != m_ItemMap_Target.end()){
		
		//PrimitiveSphere::m_WorldMatrix = (*it)->m_mMatrix ;

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
			i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD,&(*it)->m_mMatrix );
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.GetDevice()->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.GetDevice()->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &(*it)->m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}


void Item::setDrawTarget(){

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

/*******************************************************************
関数名　　：void Item::Update(UpdatePacket& i_UpdatePacket)
カテゴリ　：関数
用途　　　：データ更新
引数　　　：UpdatePacket& i_UpdatePacket  // 更新用データもろもろ
戻り値　　：
担当者　　：佐藤涼
編集      ：鴫原 徹
備考　　　：
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{


	if( !m_pPlayerCoil )	m_pPlayerCoil	= (PlayerCoil*)i_UpdatePacket.SearchObjectFromID( OBJID_3D_COIL       );
	if( !m_pSuperGage )		m_pSuperGage	=  (SuperGage*)i_UpdatePacket.SearchObjectFromID( OBJID_UI_SUPERGAUGE );
	if( !m_pCamera )		m_pCamera		=     (Camera*)i_UpdatePacket.SearchObjectFromID( OBJID_SYS_CAMERA    );

	//コイルの位置取得
	D3DXVECTOR3	cPos	= m_pPlayerCoil->getPos();

	setDrawTarget();

	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();

	while(it != m_ItemMap_Target.end()){

		if( (m_pPlayerCoil->getState() == COIL_STATE_MOVE		//	: コイルが移動中
			|| m_pPlayerCoil->getState() == COIL_STATE_STICK )	//	: もしく磁界に吸収中
			&& m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE)					//	: なおかつ	スーパーモードじゃなかったら
		{
			//	: 自分から対象までのベクトルを算出
			D3DXVECTOR3	vTargetDir	= cPos - ((*it)->m_Pos) ;

			//	: 自分と対象までの距離を求める
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			(*it)->m_fDistance	 = (float)sqrt(dirX + dirY);

			//距離が5以内ならよっていく
			if( (*it)->m_fDistance < SuctionArea ){
				(*it)->m_Pos	+= vTargetDir/**SpeedRate*/ * m_pPlayerCoil->getSpeed();

				//プレイヤーと限りなく近くなったら、消滅
				if( (*it)->m_fDistance < VanishArea ){
					i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_ITEMS );
					//m_ItemMap_All.value_comp();
					ALLCONTAINER::size_type		count	= m_ItemMap_All.count((*it)->m_fMapKey) , 
												i		;
					ALLCONTAINER::iterator		ait		= m_ItemMap_All.find((*it)->m_fMapKey);
					//エネルギー回復
					m_pSuperGage->Recovery(-(*it)->m_fRecoveryPoint);
					if(!m_pSuperGage->getAcquired())m_pSuperGage->setAcquired(true);
					(*it)->m_bHidden = true ;
					// SafeDelete( (*it) );
					for( i = 0 ; i < count ; i++ ){
						if( ait->second == (*it) ){
							SafeDelete(ait->second);
							m_ItemMap_All.erase(ait);
							break ;
						}
						ait++ ;
					}
					it = m_ItemMap_Target.erase( it );
					continue;
				}
			}
			////ゲージが最大になったらコイルを無敵状態に
			//if(m_pSuperGage->getRate() <= 0.0f){
			//	m_pPlayerCoil->setSuperMode(COIL_STATE_SUPER_READY);
			//}
		}
		if(m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_READY && !m_pSuperGage->getAcquired()){
				m_pSuperGage->setAcquired(true);
		}
		//移動用
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			(*it)->m_Pos.x,(*it)->m_Pos.y,(*it)->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			(*it)->m_Size.x,(*it)->m_Size.y,(*it)->m_Size.z);

		//マティリアル設定
		m_Material = (*it)->m_Material;
		(*it)->m_mMatrix	= mScale * mMove;

		it++;
	}
//#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
//	if( GetAsyncKeyState( MYVK_DEBUG_INVISIBLEGAUGE_MAX ) ){
//		m_pSuperGage->Recovery(-1) ;
//	}
//#endif
//	static float s_fTimeAccumulator = 0 ;
//	if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_MOVE){
//		//	: すーぱモードの時
//		//static float s_fTimeTotal = 0.0f;
//		//s_fTimeTotal += (float)SUPER_GAGE_MAX / (float)COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.GetTime()->getElapsedTime();
//		//if(s_fTimeTotal >= 1.0f){
//		//	m_pSuperGage->Consume( -(1.0f / COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.GetTime()->getElapsedTime()) );
//		//	s_fTimeTotal -= (int)s_fTimeTotal;
//		//}
//		if( ( s_fTimeAccumulator += i_UpdatePacket.GetTime()->getElapsedTime()) < COIL_SUPER_MODE_TIME ){
//			float fOneSecondSub = (1.0f / (float)COIL_SUPER_MODE_TIME);
//			float fFrameSub     = fOneSecondSub * (float)i_UpdatePacket.GetTime()->getElapsedTime();
//			Debugger::DBGSTR::addStr(L"fOneSecondSub = %f\n",fOneSecondSub);
//			Debugger::DBGSTR::addStr(L"fFrameSub     = %f\n",fFrameSub);
//			m_pSuperGage->Consume( -fFrameSub );	
//		}
//	}else{
//		s_fTimeAccumulator = 0 ;	
//	}

}

/***********************************************
関数名　：void Item::addItem(
                      D3DXVECTOR3 pos,
                      D3DXVECTOR3 size,
                      D3DCOLORVALUE Diffuse,
                      D3DCOLORVALUE Specular, 
                      D3DCOLORVALUE Ambient)
カテゴリ：関数
用途　　：アイテムの追加
引数　　：D3DXVECTOR3 pos          //描画位置
　　　　：D3DXVECTOR3 size         //大きさ
　　　　：D3DCOLORVALUE Diffuse    //
　　　　：D3DCOLORVALUE Specular   //
　　　　：D3DCOLORVALUE Ambient    //
戻り値　：
担当者　：佐藤涼
備考　　：
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient, float fRecoveryPoint)
{
	try{
		fRecoveryPoint >= 1.0f && (fRecoveryPoint = 1.0f);
		float	sizeRate		= 1.0f;
		BallItem* bItem			= new BallItem;
		bItem->m_Pos			= pos;
		bItem->m_Size			= size * ( sizeRate );
		bItem->m_fMapKey		= pos.y ;
		bItem->m_bHidden		= true ;
		bItem->m_fDistance		= 6.0f;
		//bItem->m_fItemType	= itemType;
		bItem->m_fRecoveryPoint = fRecoveryPoint ;
		//if(itemType == ITEM_TYPE_RECOVETY)				bItem->m_fRecoveryPoint =
		RECOVERY_POINT;
		//if(itemType == ITEM_TYPE_RECOVETY_BIG)bItem->	m_fRecoveryPoint		= RECOVERY_POINT_L;
        // D3DMATERIAL9構造体を0でクリア
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemMap_All.insert(multimap<float,BallItem*>::value_type(bItem->m_Pos.y,bItem));
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
 Factory_Item 定義部
****************************************************************************/
/**************************************************************************
関数名　　：Factory_Item::Factory_Item( FactoryPacket* fpac );
カテゴリ　：コンストラクタ
用途　　　：
引数　　　：FactoryPacket* fpac     // もろもろのデータ
戻り値　　：
担当者　　：佐藤涼
備考　　　：
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_3D_ITEM);

		int ItemQty = 800;
		for(int i = 0; i < ItemQty ; i++){
			it->addItem(
				D3DXVECTOR3( (float)(rand() *i % 50),
							 (float)(rand() *i % 700),
							 0.0f
				),
				ITEM_SCALE,
				BallDiffuse,BallSpecular,BallAmbient);
		}

		//アイテム(小)
		//for(int i = 0; i < 9; i++){
		//	for(int j = 0; j < 80*ItemDiffusionRate; j++){
		//		it->addItem(D3DXVECTOR3((float(i)*6.0f+float(rand()%100*0.05f))+1.5f,
		//								(float(j)*(ItemDiffusionRate)+float(rand()%100*0.05f))+1.5f,0.0f),
		//					ITEM_SCALE,
		//					BallDiffuse,BallSpecular,BallAmbient);
		//	}
		//}

		//アイテム(大)
		it->addItem(D3DXVECTOR3(10.0f,10.0f,0.0f),
					ITEM_SCALE,
					BallDiffuse,BallSpecular,BallAmbient,
					RECOVERY_POINT_L);

		fpac->AddObject(it);

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 関数名　　：Factory_Item::~Factory_Item();
 カテゴリ　：デストラクタ
 用途　　　：
 引数　　　：
 戻り値　　：
 担当者　　：佐藤涼
 備考　　　：
***************************************************************************/
Factory_Item::~Factory_Item(){
    //なにもしない
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
