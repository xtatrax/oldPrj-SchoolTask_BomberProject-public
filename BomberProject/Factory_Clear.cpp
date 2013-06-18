////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Clear.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Factory_Clear ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Clear.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Clear 定義部
****************************************************************************/
/**************************************************************************
 Factory_Clear::Factory_Clear(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Clear::Factory_Clear(FactoryPacket* fpac)
{
	try{

		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Clear2.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3( 200.0f, 200.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		system::Sound* pSound = NULL;
		fpac->SetSound(
			pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_CLEAR );

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Clear::~Factory_Clear();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Clear::~Factory_Clear(){
    //なにもしない
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
