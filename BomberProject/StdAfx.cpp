////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：AtdAfx.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包データと備考	：全ソース共通のデータ群
//					▼
//

#include "StdAfx.h"


float f = 0.5f ;

wiz::RENDERSTATE_PARAM g_GlobalRenderStates[] = {
	//{ D3DRS_CULLMODE     , D3DCULL_NONE },	// 両面描画モードの指定
	{ D3DRS_ZENABLE      , TRUE         },  // Ｚ比較を行なう
	{ D3DRS_DITHERENABLE , TRUE         },  // ディザリングを行なう（高品質描画）
	{ D3DRS_LIGHTING     , TRUE         },  // ライティングモード
	{ D3DRS_ALPHAREF     , 0x00000001	},  // ライティングモード
	{ D3DRS_ALPHATESTENABLE, TRUE				},  // ライティングモード
	{ D3DRS_ALPHAFUNC    , D3DCMP_GREATEREQUAL	},  // ライティングモード
	{ D3DRS_FORCE_DWORD  , NULL			}	// 終了宣言
};

