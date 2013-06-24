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
			LPDIRECT3DTEXTURE9	pRankTex,
			LPDIRECT3DTEXTURE9	pFrameTex,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect,
			wiz::OBJID	id		)
:SpriteObject( pD3DDevice, NULL, vScale, vRot, vPos, Rect, g_vZero, g_vZero, 0xFFFFFFFF, id )
,m_bDrawing( false )
,m_pRankTex( pRankTex )
,m_pFrameTex( pFrameTex )
,m_ResultRank( Rank_C )
,m_vScale( vScale )
,m_vRot( vRot )
,m_vPos( vPos )
{
}

Rank::~Rank(){
}

void	Rank::Draw(DrawPacket &i_DrawPacket){
	if( m_bDrawing ){

		D3DXMATRIX	mMatrix, mPos, mScale, mRot;

		D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );

		//フレーム******************************
		D3DXMatrixScaling( &mScale, m_vScale.x, m_vScale.y, m_vScale.z );
		D3DXMatrixTranslation( &mPos, m_vPos.x, m_vPos.y, m_vPos.z );
		mMatrix = mScale * mRot * mPos ;
		SpriteObject::setMatrix(mMatrix);

		setRect( Rank_S );	//128x128
		m_pTexture	= m_pFrameTex;
		SpriteObject::Draw(i_DrawPacket);
		//****************************************

		//ランク**********************************************
		D3DXMatrixScaling( &mScale, m_vScale.x-0.2f, m_vScale.y-0.2f, m_vScale.z-0.2f );
		D3DXMatrixTranslation( &mPos, m_vPos.x+15.0f, m_vPos.y+20.0f, m_vPos.z );
		mMatrix = mScale * mRot * mPos ;
		SpriteObject::setMatrix(mMatrix);

		setRect( m_ResultRank );
		m_pTexture	= m_pRankTex;
		SpriteObject::Draw(i_DrawPacket);
		//*****************************************************

	}
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

		//Frame
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Frame_Clear3.png" ),
				D3DXVECTOR3( 1.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 53.0f, 150.0f, 0.0f ),
				Rect( 0, 0, 512, 256 ),
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		);

		//RESULT
		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Clear4.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-256, 20.0f, 0.0f ),
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
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, 135.0f, 0.0f ),
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
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, height-90.0f, 0.0f ),
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
				D3DXVECTOR3( 0.8f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( 80.0f, height-15.0f, 0.0f ),
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
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"TOTAL_POINT.png" ),
				D3DXVECTOR3( 1.0f, 1.5f, 0.0f ),
				g_vZero,
				D3DXVECTOR3( wide-430.0f, height+85.0f, 0.0f ),
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
				fpac->AddTexture(L"BACK002.png"),
				fpac->AddTexture(L"BACK001.png"),
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
				OBJID_UI_BUTTON_BACK
			)
		);

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
				fpac->AddTexture( L"RANK_ver1.png" ),
				fpac->AddTexture( L"RANK_Base2.png" ),
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f/*D3DXToRadian(30.0f)*/ ),
				D3DXVECTOR3( 830.0f, 400.0f, 0.0f ),
				&Rect( 0, 0, 128, 128 )
			)
		);

		//カーソル*************************************************
		float	fLineLength	= 550.0f;
		float	fPointSize	= 1.0f;
		Factory_Cursor	MCfac( fpac, fLineLength, fPointSize )  ; 


		//*****************************************************************************
		system::Sound* pSound = NULL;
		fpac->SetSound(
			pSound = new system::Sound( 
				RCTEXT_SOUND_WAVEBANK,
				RCTEXT_SOUND_SOUNDBANK,
				OBJID_SYS_SOUND
			)
		);
		pSound->SearchSoundAndPlay( RCTEXT_SOUND_BGM_GAMEOVER );

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
