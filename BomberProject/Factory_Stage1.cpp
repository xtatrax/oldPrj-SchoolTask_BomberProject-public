////////////////////////////// //////////////////////////////
//	プロジェクト	：BomberProject
//	ファイル名		：Factory_Stage1.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：メインファクトリー
//					▼
//	namespace wiz;
//		class Factory_Stage1 ;
//
#include "StdAfx.h"
#include "Stage.h"
#include "Factory_Stage1.h"
#include "Factory_Player.h"

namespace wiz{


/**************************************************************************
 Factory_Stage1 定義部
****************************************************************************/
/**************************************************************************
 Factory_Stage1::Factory_Stage1(
	Factory_Stage1 *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
	vector<Object*>& vec,			//オブジェクトの配列
	TextureManager& TexMgr		//テクスチャの配列
);
 用途: コンストラクタ（サンプルオブジェクトを配列に追加する）
 戻り値: なし
***************************************************************************/
Factory_Stage1::Factory_Stage1(FactoryPacket *fpac){
	try{
		LPDIRECT3DDEVICE9 pD3DDevice	= fpac->pD3DDevice	;
		vector<Object*>*  pVec			= fpac->m_pVec		;

		//カメラのインスタンス初期化
		float ECXPos = 25.1f;
		float ECYPos = 10.1f;
		pVec->push_back(
			new Camera(pD3DDevice,D3DXVECTOR3( ECXPos, ECYPos, -55.7f),D3DXVECTOR3(ECXPos,ECYPos,0.0f), 1 ,300.0f,30.0f)
		);
		//	: ガイドライン
		pVec->push_back(new Guide( pD3DDevice ) );

		/*
			DWORD			enClassid ;	//	wiz::CLASSIDで指定してください
			D3DXVECTOR3		vScale    ;
			D3DXVECTOR3		vRot      ;
			D3DXVECTOR3		vPos      ;
			D3DCOLORVALUE   Diffuse   ;
			D3DCOLORVALUE   Specular  ;
			D3DCOLORVALUE   Ambient   ;
			bool			bPool     ;

			//	: オプション
			wstring			sTexturePath	;

			wstring			sFilePath		;
			DWORD			dwMotionNum		;
			float			fTracSpeed		;

		*/
		MapPartsStatus MapData[] = {
			{ OBJID_3D_WALL,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_ITEM,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_MAGNET,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), g_vZero, g_vZero, getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_END }
		
		};


		StageLoader loader(pD3DDevice,*pVec,*fpac->m_pTexMgr,MapData);


		Factory_Player Pfac( fpac );


		//	: スプライト
		pVec->push_back(
			new SpriteObject(
				pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"display.png" ),
				g_vOne,
				g_vZero,
				g_vZero,
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
			)
		);


	}
	catch(...){
		//再throw
		throw;
	}

}

}
//end of namespace wiz.
