////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Item.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼 本多寛之
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
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
                      LPDIRECT3DTEXTURE9 pTexture,
                      wiz::OBJID id )
カテゴリ　　：コンストラクタ
用途　　　　：
引数　　　　：FactoryPacket* fpac           // : デバイスなど
　　　　　　：LPDIRECT3DTEXTURE9 pTexture   // : テクスチャ―
　　　　　　：wiz::OBJID id                 // : ID
戻り値　　　：
担当者　　　：佐藤涼
備考　　　　：
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						pTexture
	)
	,m_pPlayerCoil(NULL)
	,m_pSuperGage(NULL)
	,m_pSound(NULL)
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
	SafeDeletePointerMap( m_ItemMap_All );	
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
	multimap<float,BallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//ステージを元に戻す
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//テクスチャがない場合
			// マトリックスをレンダリングパイプラインに設定
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_mMatrix);
			//コモンメッシュのDraw()を呼ぶ
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}


void Item::setDrawTarget(){

	//////////
	//	描画対象の追加
	//
	ALLCONTAINER::iterator	AIMit  = m_ItemMap_All.lower_bound( m_pCamera->getPosY()  -20 ),
							AIMend = m_ItemMap_All.upper_bound( m_pCamera->getPosY()  +20 );
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
	DWORD dwSTime = TLIB::Tempus::TimeGetTime();

	vector<Object*>	Vec	= *(i_UpdatePacket.pVec);

	if( !m_pPlayerCoil )	m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromID(&Vec,OBJID_3D_COIL);
	if( !m_pSuperGage )		m_pSuperGage	= (SuperGage*)SearchObjectFromID(&Vec,OBJID_UI_SUPERGAUGE);
	if( !m_pSound )			m_pSound		= (Sound*)SearchObjectFromID(&Vec,OBJID_SYS_SOUND);
	if( !m_pCamera )		m_pCamera		= (Camera*)SearchObjectFromID(&Vec, OBJID_SYS_CAMERA);

	//コイルの位置取得
	D3DXVECTOR3	cPos	= m_pPlayerCoil->getPos();

	setDrawTarget();

	Debugger::DBGSTR::addStr(L"ItemAll = %d\n",m_ItemMap_Target.size());

	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();

	while(it != m_ItemMap_Target.end()){

		if( (m_pPlayerCoil->getState() == COIL_STATE_MOVE		//	: コイルが移動中
			|| m_pPlayerCoil->getState() == COIL_STATE_STICK )	//	: もしくは	アイテムを吸収中
			&& !m_pPlayerCoil->getSuperMode())					//	: なおかつ	スーパーモードじゃなかったら
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
					m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_ITEMS );
					//m_ItemMap_All.value_comp();
					ALLCONTAINER::size_type		count	= m_ItemMap_All.count((*it)->m_fMapKey) , 
												i		;
					ALLCONTAINER::iterator		ait		= m_ItemMap_All.find((*it)->m_fMapKey);
					//エネルギー回復
					m_pSuperGage->Recovery(-RECOVERY_POINT);
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
			//ゲージが最大になったらコイルを無敵状態に
			if(m_pSuperGage->getRate() >= 1.0f){
				m_pPlayerCoil->setSuperMode(true);	
			}
		}
		if( (*it)->m_fMapKey > m_pCamera->getPosY() +20 ||
			(*it)->m_fMapKey < m_pCamera->getPosY() -20 ){
				(*it)->m_bHidden = true ;
				it = m_ItemMap_Target.erase(it);
				continue;
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
	if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && m_pPlayerCoil->getSuperMode()){
		static float s_fTimeTotal = 0.0f;
		s_fTimeTotal += (float)SUPER_GAGE_MAX / (float)COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime();
		if(s_fTimeTotal >= 1.0f){
			m_pSuperGage->Consume( -(1.0f / COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime()) );
			s_fTimeTotal -= (int)s_fTimeTotal;
		}
	}
	DWORD dwETime = TLIB::Tempus::TimeGetTime();
	Debugger::DBGSTR::addStr( L"Item::Update : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));

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
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient)
{
	try{
		BallItem* bItem = new BallItem;
		bItem->m_Pos = pos;
		bItem->m_fMapKey = pos.y ;
		bItem->m_bHidden = true ;
		bItem->m_Size = size;
		bItem->m_fDistance = 6.0f;
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
		Item*	it	=	new	Item(fpac,NULL,OBJID_UNK);

		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 300; j++){
				it->addItem(D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.05f))+1.5f,
										(float(j)*2.75f+float(rand()%100*0.05f))+1.5f,0.0f),
							D3DXVECTOR3(0.5f,0.5f,0.5f),
							BallDiffuse,
							BallSpecular,
							BallAmbient);
			}
		}
		fpac->m_pVec->push_back(it);

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
