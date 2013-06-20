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
#include "Factory_Score.h"
#include "Factory_Title.h"
#include "Factory_Cursor.h"

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
Factory_Clear::Factory_Clear(FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint)
{
	try{

		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		//CLEAR
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Clear3.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-256, 50.0f, 0.0f ),
				Rect( 0, 0, 512, 128 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		//最高到達点**************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"MAX_RANGE1.png" ),
				D3DXVECTOR3( 0.5f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-200, height-140.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		//掠めた回数*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"SCRATCH_TIME2.png" ),
				D3DXVECTOR3( 0.5f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-200, height-60.0f, 0.0f ),
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
				D3DXVECTOR3( 0.5f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-200, height+20.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

		//トータルポイント*****************************************************************
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TOTAL_POINT2.png" ),
				D3DXVECTOR3( 0.6f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-128-250, height+100.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);
		//*****************************************************************************
		//Please Click
		fpac->m_pVec->push_back(
			new Title_Select(
					fpac->pD3DDevice,
					fpac->AddTexture( L"Click_Please1.png" ),
					GM_OPENSTAGE_TITLE,
					D3DXVECTOR3(1.0f,1.0f,0.0f),
					g_vZero,
					D3DXVECTOR3( wide-256.0f, 500.0f, 0.0f ),
					Rect( 0, 0, 512, 64 ),
					g_vZero,
					g_vZero,
					0xFFFFFFFF
				)
		);

		//カーソル*************************************************
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 

		//Score**********************************************
		fpac->m_pVec->push_back(
			new ResultScore(
				fpac->pD3DDevice,
				fpac->AddTexture(L"Number_Base1.png"),
				fpac->AddTexture(L"Number_Base2.png"),
				fpac->AddTexture(L"Rate_Number.png"),
				fpac->AddTexture(L"Rate_Number2.png"),
				fpac->AddTexture(L"Rate_Number3.png"),
				D3DXVECTOR3( 0.8f, 0.8f, 0.0f ),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
				iDeadCount,
				iMaxPosY,
				iScratchPoint,
				&Rect( 0, 0, 512, 64 )
			)
		);
		//***************************************************

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
