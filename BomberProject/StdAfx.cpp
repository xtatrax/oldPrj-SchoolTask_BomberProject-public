////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：AtdAfx.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：全ソース共通のデータ群
//					▼
//

#include "StdAfx.h"

D3DXVECTOR3 g_vZero = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3 g_vOne  = D3DXVECTOR3(1.0f,1.0f,1.0f);
D3DXVECTOR3 g_vMax  = D3DXVECTOR3(+FLT_MAX,+FLT_MAX,+FLT_MAX);
D3DXVECTOR3 g_vMin  = D3DXVECTOR3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

extern wstring g_sDefaultTexturePath = L"media/Textures/" ;	//	: テクスチャの置き場


wiz::RENDERSTATE_PARAM g_GlobalRenderStates[] = {
	{ D3DRS_CULLMODE     , D3DCULL_NONE },	// 両面描画モードの指定
	{ D3DRS_ZENABLE      , TRUE         },  // Ｚ比較を行なう
	{ D3DRS_DITHERENABLE , TRUE         },  // ディザリングを行なう（高品質描画）
	{ D3DRS_LIGHTING     , TRUE         },  // ライティングモード
	{ D3DRS_FORCE_DWORD  , NULL			}	// 終了宣言
};

HWND g_hWnd ;
bool g_bMouseLB;
bool g_bMouseRB;
