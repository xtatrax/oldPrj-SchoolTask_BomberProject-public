////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_PlaneCircle.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：
//					▼
//	namespace wiz;
//		namespace bomberobject;
//

//////////
//	: 基本のインクルード
#include "StdAfx.h"
#include "Factory_PlaneCircle.h"
//	: 基本のインクルード
//////////

//////////
//	: 追加のインクルード
//	: 追加のインクルード
//////////



namespace wiz{
namespace bomberobject{


/**************************************************************************
 Factory_PlaneCircle 定義部
****************************************************************************/
/**************************************************************************
 Factory_PlaneCircle::Factory_PlaneCircle(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
	Factory_PlaneCircle::Factory_PlaneCircle(FactoryPacket* fpac){
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
 Factory_PlaneCircle::~Factory_PlaneCircle();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	Factory_PlaneCircle::~Factory_PlaneCircle(){
//なにもしない
	}
}//end of namespace bomberobject.
}//end of namespace wiz.