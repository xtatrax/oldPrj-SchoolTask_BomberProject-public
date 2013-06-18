////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Result.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：佐藤　涼
//	内包ﾃﾞｰﾀと備考	：アイテムファクトリー
//					▼
//	namespace wiz;
//		class Factory_Result ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Result.h"
#include "BassItems.h"
#include "Factory_Score.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 Factory_Result 定義部
****************************************************************************/
/**************************************************************************
 Factory_Result::Factory_Result(
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Result::Factory_Result(FactoryPacket* fpac, int iDeadCount, int iMaxPosY)
{
	try{
		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"RESULT.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128, 50.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		//死亡回数*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"dead_count1.png" ),
				D3DXVECTOR3( 0.5f, 1.6f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-150, height-20.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		fpac->m_pVec->push_back(
			new Score(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base1.png"),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				D3DXVECTOR3( wide+100, height, 0.0f ),
				iDeadCount,
				&Rect( 0, 0, 512, 64 )
			)
		);

		//最高到達点**************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MAX_RANGE1.png" ),
				D3DXVECTOR3( 0.5f, 1.6f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-150, height+80.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		fpac->m_pVec->push_back(
			new Score(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base2.png"),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				D3DXVECTOR3( wide+100, height+100.0f, 0.0f ),
				iMaxPosY,
				&Rect( 0, 0, 512, 64 )
			)
		);
		//*****************************************************************************

		//system::Sound* pSound = NULL;
		//fpac->SetSound(
		//	pSound = new system::Sound( 
		//		RCTEXT_SOUND_WAVEBANK,
		//		RCTEXT_SOUND_SOUNDBANK,
		//		OBJID_SYS_SOUND
		//	)
		//);
		//pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_CLEAR );

	}
	catch(...){
		//再throw
		throw;
	}

}
/**************************************************************************
 Factory_Result::~Factory_Result();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Factory_Result::~Factory_Result(){
    //なにもしない
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
