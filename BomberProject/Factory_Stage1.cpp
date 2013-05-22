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

		////カメラのインスタンス初期化
		//float ECXPos = 25.1f;
		//float ECYPos = 10.1f;
		//pVec->push_back(
		//	new Camera(pD3DDevice,D3DXVECTOR3( ECXPos, ECYPos, -55.7f),D3DXVECTOR3(ECXPos,ECYPos,0.0f), 1 ,300.0f,30.0f)
		//);
		////	: ガイドライン
		//pVec->push_back(new Guide( pD3DDevice ) );

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

		float i = 26.0f ;
		MapPartsStatus MapData[] = {//scale								Rot										Pos											Diffuse												Specular														Ambient

			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f, 6.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f,90.0f),			D3DXVECTOR3(37.0f, 7.0f, 0.0f),				getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,15.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f,90.0f),			D3DXVECTOR3( 8.0f,20.0f, 0.0f),				getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,10.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f, 0.0f),			D3DXVECTOR3(16.0f, 5.0f, 0.0f),				getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,32.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f,90.0f),			D3DXVECTOR3(16.0f,20.0f, 0.0f),			getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },

			//追加
			//1
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,20.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(20.0f, 28.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//2
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,20.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(10.0f, 30.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//3
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,20.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(30.0f, 50.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//4
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(30.0f, 40.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//5
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(15.0f, 60.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//6
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(25.0f, 70.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//7
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(15.0f, 110.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//8
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(13.0f, 90.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//9
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,32.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(29.5f, 93.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//10
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,16.5f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(21.0f, 102.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//11
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,5.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(35.0f, 90.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//12
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,30.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(25.0f, 120.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//13
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(10.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//14
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(20.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//15
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,25.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,0.0f), D3DXVECTOR3(30.0f, 140.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//16
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,20.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(30.0f, 145.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//17
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(5.0f, 145.0, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },



			////横下
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,40.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f,90.0f),			D3DXVECTOR3(19.6f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			////縦左壁
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,26.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f, 0.0f),			D3DXVECTOR3(0.0f,13.0f, 0.0f),			getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			////縦右壁
			//{ OBJID_3D_WALL,	 D3DXVECTOR3( 3.0f,26.0f, 0.0f),		D3DXVECTOR3( 0.0f, 0.0f, 0.0f),			D3DXVECTOR3(39.0f,13.0f, 0.0f),			getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),			getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f),			getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },

			//横下
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,40.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f,90.0f), D3DXVECTOR3(19.6f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f),	getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//縦左壁
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*1, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*2, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*3, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*4, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*5, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*6, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,13.0f+i*7, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//縦右壁
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f+i*1, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f+i*2, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f+i*3, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f+i*4, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			{ OBJID_3D_WALL, D3DXVECTOR3( 3.0f,26.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(39.0f,13.0f+i*5, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },




			//{ OBJID_3D_ITEM,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f,0.0f, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
			//{ OBJID_3D_MAGNET,	 D3DXVECTOR3( 2.0f, 2.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3(37.0f, 5.0f, 0.0f), getD3DCOLORVALUE( 0.5f, 0.5f, 0.5f, 0.5f), getD3DCOLORVALUE( 0.0f, 0.0f, 0.0f, 0.0f), getD3DCOLORVALUE( 0.7f, 0.7f, 0.7f, 0.7f) },
		
			{ OBJID_END }
		
		};


		StageLoader loader(pD3DDevice,*pVec,*fpac->m_pTexMgr,MapData);


		//Factory_Player Pfac( fpac );


		////	: スプライト
		//pVec->push_back(
		//	new SpriteObject(
		//		pD3DDevice,
		//		fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"display.png" ),
		//		g_vOne,
		//		g_vZero,
		//		g_vZero,
		//		NULL,
		//		g_vZero,
		//		g_vZero,
		//		0xFFFFFFFF
		//	)
		//);


	}
	catch(...){
		//再throw
		throw;
	}

}

}
//end of namespace wiz.
