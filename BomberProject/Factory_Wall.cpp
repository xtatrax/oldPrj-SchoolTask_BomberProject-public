////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Wall.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Wall ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Wall.h"
#include "BassItems.h"

namespace wiz{

Wall::Wall( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
	D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
	RECT *pRect, D3DXVECTOR3 &vCenter, D3DXVECTOR3 &vOffsetPos,
	Color color , wiz::OBJID id)
	:SpriteObject(pD3DDevice ,pTexture ,vScale ,vRot, vPos, pRect, vCenter, vOffsetPos, color, id)
{
}
	
/**************************************************************************
 Factory_Wall 定義部
****************************************************************************/
/**************************************************************************
 Factory_Wall::Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Wall::Factory_Wall(FactoryPacket* fpac){
	try{
		fpac->m_pVec->push_back(
			new Wall(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"biribiriWall.png"),
				D3DXVECTOR3(1.0f,1.0f,1.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(1.0f,1.0f,1.0f),
				NULL,
				g_vZero,
				g_vZero
				)
		);
	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Wall::~Factory_Wall();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Wall::~Factory_Wall(){
    //なにもしない
}

}
//end of namespace wiz.
