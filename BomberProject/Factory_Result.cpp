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
#include "Factory_Title.h"
#include "Factory_Cursor.h"
#include "Factory_CustomButtonA.h"

namespace wiz{
namespace bomberobject{

/***********************************************************************
 Rank 定義部
***********************************************************************/
Rank::Rank( LPDIRECT3DDEVICE9	pD3DDevice,
			LPDIRECT3DTEXTURE9	pTex_S,
			LPDIRECT3DTEXTURE9	pTex_A,
			LPDIRECT3DTEXTURE9	pTex_B,
			LPDIRECT3DTEXTURE9	pTex_C,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect,
			wiz::OBJID	id		)
:SpriteObject( pD3DDevice, NULL, vScale, vRot, vPos, Rect, g_vZero, g_vZero, 0xFFFFFFFF, id )
,m_pTex_S( pTex_S )
,m_pTex_A( pTex_A )
,m_pTex_B( pTex_B )
,m_pTex_C( pTex_C )
,m_bDrawing( false )
{
}

Rank::~Rank(){
}

void	Rank::Draw(DrawPacket &i_DrawPacket){
	if( m_bDrawing )
		SpriteObject::Draw(i_DrawPacket);
}

void	Rank::Update(UpdatePacket &i_UpdatePacket){
}

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
Factory_Result::Factory_Result(FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint)
{
	try{
		float	wide	= BASE_CLIENT_WIDTH/2;
		float	height	= BASE_CLIENT_HEIGHT/2;

		//RESULT
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Clear4.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-256, 50.0f, 0.0f ),
				Rect( 0, 128, 512, 256 ),
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

/////////////////////////////////////////////////////////////////////////////////
//                                 BACK                                        //
/////////////////////////////////////////////////////////////////////////////////
		fpac->AddButton(
			new CustomButtonA(
				fpac->pD3DDevice,	
				fpac->AddTexture(L"BACK002.tga"),
				fpac->AddTexture(L"BACK001.tga"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(980.0f, 560.0f, 0.0f),
				Rect(0,0,148,30),
				Rect(0,0,148,30),
				D3DXVECTOR3( 148.0f,15.0f,0.0f ),
				g_vZero,
				0xFF00AA55,
				0xFF008833,
				0xFFFFFFFF,
				0xFFAAAAAA,
				RCTEXT_SOUND_SE_SELECT,
				RCTEXT_SOUND_SE_ENTER,
				0.5f,
				Command( GM_OPENSTAGE_TITLE, 0, 0 ),
				0,
				OBJID_UI_BUTTON_BACK
			)
		);

		//カーソル*************************************************
		float	fLineLength	= 550.0f;
		float	fPointSize	= 0.25f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 

		//Score*****************************************************
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
		//***********************************************************
		// RANK ( S~C )
		fpac->m_pVec->push_back(
			new Rank(
				fpac->pD3DDevice,
				fpac->AddTexture( L"Rank_S.png" ),
				fpac->AddTexture( L"Rank_A.png" ),
				fpac->AddTexture( L"Rank_B.png" ),
				fpac->AddTexture( L"Rank_C.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),
				D3DXVECTOR3( 0.0f, 0.0f, D3DXToRadian(30.0f) ),
				D3DXVECTOR3( 900.0f, 400.0f, 0.0f ),
				&Rect( 0, 0, 128, 128 )
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
