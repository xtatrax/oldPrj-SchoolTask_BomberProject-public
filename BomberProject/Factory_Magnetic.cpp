////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Magnetic.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
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
#include "BassItems.h"

namespace wiz{

/**************************************************************************
 MagneticumObject 定義部
****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            ：    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            ：    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：なし
//// 担当       ：鴫原 徹
//// 備考       ：
////            ：
////
MagneticumObject::MagneticumObject(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: デバイス
	LPDIRECT3DTEXTURE9 pTexture,				//	: テクスチャー
	D3DXVECTOR3 &vScale,						//	: 伸縮
	D3DXVECTOR3 &vRot,							//	: 回転
	D3DXVECTOR3 &vPos,							//	: 位置
	RECT* pRect,								//	: 描画範囲
	Color color ,								//	: 色
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos( vPos )
,m_bMagnetPole( POLE_S )
{
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
void MagneticumObject::Update( UpdatePacket& i_UpdatePacket ){

};


//class EnemyManager : public Object{
//	list< Enemy* > m_EnemyList ;
//	float Delay ;
//public:
//	EnemyManager()
//		:Object(OBJID_UI_SPRITE)
//		,Delay(0)
//	{}
//	void Update(UpdatePacket& i_UpdatePacket){
//
//		if( ( Delay += i_UpdatePacket.pTime->getElapsedTime() ) >= 0.8f){
//			float x = rand() % 1024 ;
//			float y = rand() % 800 ;
//			m_EnemyList.push_back( 
//				new Enemy(
//					i_UpdatePacket.pD3DDevice,
//					i_UpdatePacket.pTxMgr->addTexture(i_UpdatePacket.pD3DDevice,L"Circle.BMP"),
//					g_vOne,
//					g_vZero,
//					D3DXVECTOR3( x , y ,0.0f),
//					NULL,
//					0xFFFF0000
//				)
//			);
//			Delay = 0 ;
//		}
//
//
//		list< Enemy* >::iterator  it = m_EnemyList.begin() ;
//		list< Enemy* >::iterator end = m_EnemyList.end()   ;
//
//		for(  ; it != end ; it++ ){
//			(*it)->Update( i_UpdatePacket );
//		}
//
//
//	}
//	~EnemyManager(){
//		SafeDeletePointerContainer(m_EnemyList);
//	}
//	virtual void Draw(DrawPacket& i_DrawPacket){
//		list< Enemy* >::iterator  it = m_EnemyList.begin() ;
//		list< Enemy* >::iterator end = m_EnemyList.end()   ;
//
//		for(  ; it != end ; it++ ){
//			(*it)->Draw( i_DrawPacket );
//		}
//
//	};
//
//
//};
//

	
/**************************************************************************
 Factory_Magnetic 定義部
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Magnetic::Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
	try{
		
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
//end of namespace wiz.
