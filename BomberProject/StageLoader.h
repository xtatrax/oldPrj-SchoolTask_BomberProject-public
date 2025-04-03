////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：StageLoader.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ステージ
//					：ステージはシーンから呼ばれます
//					▼
//	namespace wiz;
//		class StageLoader ;
//		class StageLoader ;
//		class MenuStage : public StageLoader ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassMenuItems.h"
#include "CSV.h"

namespace wiz{

// 仮宣言	
class StageLoader ;
using namespace menuobject ;
//class Button2;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 struct MapPartsStatus;
 用途: 
****************************************************************************/
struct MapPartsStatus{
	DWORD			enClassid ;	//	wiz::CLASSIDで指定してください
	D3DXVECTOR3		vScale    ;
	D3DXVECTOR3		vRot      ;
	D3DXVECTOR3		vPos      ;
	D3DXVECTOR3		vOffset   ;
	D3DCOLORVALUE   Diffuse   ;
	D3DCOLORVALUE   Specular  ;
	D3DCOLORVALUE   Ambient   ;
	POLE			bPool     ;

	//	: オプション
	wstring			sTexturePath	;

	wstring			sFilePath		;
	DWORD			dwMotionNum		;
	float			fTracSpeed		;

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************
// class StageLoader;
//
// 担当者  : 鴫原 徹
// 用途    : CSVデータからステージを構築します
//**************************************************************************
class StageLoader{
	struct CSVMATRIX {
		//	: 行
		UINT Line ;
		//	: 列
		struct ___ST{
			UINT	uiNumber			;	//	番号
			UINT	uiType				;	//	種類
			UINT	uiPath				;	//	FILE
			UINT	uiTexPath			;	//	テクスチャ
			UINT	uiMotionNum			;	//	モーション
			UINT	uiTracSpeed			;	//	モーションの速さ
			UINT	uiScaleX			;	//	X伸縮
			UINT	uiScaleY			;	//	Y伸縮
			UINT	uiScaleZ			;	//	Z伸縮
			UINT	uiRotX				;	//	X回転
			UINT	uiRotY				;	//	Y回転
			UINT	uiRotZ				;	//	Z回転
			UINT	uiPosX				;	//	X移動
			UINT	uiPosY				;	//	Y移動
			UINT	uiPosZ				;	//	Z移動
			UINT	uiPool				;	//	Z移動
			___ST(){
				uiNumber	=
				uiType		=
				uiPath		=
				uiTexPath	=
				uiMotionNum	=
				uiTracSpeed	=
				uiScaleX	=
				uiScaleY	=
				uiScaleZ	=
				uiRotX		=
				uiRotY		=
				uiRotZ		=
				uiPosX		=
				uiPosY		=
				uiPosZ		=
				uiPool		= UINT_MAX	;
			}
		}Column;
	};
	//	: CSVから読み取ったDataをとりあえず保存しておく
	map<UINT,MapPartsStatus>			m_ObjeMap;
	//	: 
	multimap<wiz::OBJID,Object*>		m_ObjeTypeMap;

	FactoryPacket*		m_pFpac;
	/////////////////// ////////////////////
	//// 関数名     ：void StageLoader::PartsGenerator(MapPartsStatus i_Data)
	//// カテゴリ   ：ジェネレータ
	//// 用途       ：ファイルから読み取っったデータを元にオブジェクト情報を構築します
	//// 引数       ：  MapPartsStatus   i_Data    //  : ファイルから読みとたパーツの情報
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：StageGeneratorから
	////            ：⑦
	////
	void PartsGenerator(MapPartsStatus i_Data);
	/////////////////// ////////////////////
	//// 関数名     ：void StageLoader::StageGenerator(wstring i_sStageFilePath)
	//// カテゴリ   ：メンバ関数
	//// 用途       ：ステージを構築すします
	//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：StageListLoader関数から呼ばれます
	////            ：⑥
	////
	void StageGenerator(wstring i_sStageFilePath);
	/////////////////// ////////////////////
	//// 関数名     ：void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
	//// カテゴリ   ：メンバ関数
	//// 用途       ：ステージを構築すします
	//// 引数       ：  wstring    i_sStageFilePath         //  ステージの構成ファイルへのパス
	////            ： CSVMATRIX&  o_CsvMatrix				//	読み込むべき行と列の詰め合わせ
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：StageListLoader関数から呼ばれます
	////            ：⑤
	////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);
	/////////////////// ////////////////////
	//// 関数名     ：void StageLoader::ObjectsLoader(wstring i_sFilePath)
	//// カテゴリ   ：メンバ関数
	//// 用途       ：オブジェクト情報を構築します
	//// 引数       ：  wstring i_sFilePath         //
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：CSVから読み取った情報を解析&インスタンス化します
	////            ：PointSearch関数から呼ばれます
	////            ：④
	////
	void ObjectsLoader(wstring i_sFilePath);
	/////////////////// ////////////////////
	//// 関数名     ：void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
	//// カテゴリ   ：メンバ関数
	//// 用途       ：ステージを構築すします
	//// 引数       ：  vector<vector<wstring>>&  i_vvCsvData    //  :  [IN]CSVから読み取ったナマのデータ
	////            ：  POINT&                    o_NumberPoint  //  : [OUT]
	////            ：  POINT&                    o_PathPoint    //  : [OUT]
	//// 戻値       ：なし
	//// 担当者     ：鴫原 徹
	//// 備考       ：StageListLoader関数から呼ばれます
	////            ：③
	////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, POINT& o_NumberPoint, POINT& o_PathPoint);
	/////////////////// ////////////////////
	//// 関数名     ：void StageLoader::StageListLoader(wstring i_sFileName, BYTE i_byStageNum)
	//// カテゴリ   ：ローダー
	//// 用途       ：ステージリストを読み込む
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：②
	////            ：
	////
	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum);
public:
	/////////////////// ////////////////////
	//// 関数名     ：StageLoader::StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,DWORD i_dwStageNum)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：FILEからStageLoaderを構築します
	//// 引数       ：
	//// 戻値       ：なし(失敗時は例外をthrow)
	//// 担当者     ：鴫原 徹
	//// 備考       ：①
	////            ：
	////
	StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,
		DWORD i_dwStageNum);

	/////////////////// ////////////////////
	//// 関数名     ：StageLoader::StageLoader(FactoryPacket& i_Fpac, MapPartsStatus* i_Parts)
	//// カテゴリ   ：コンストラクタ
	//// 用途       ：
	//// 引数       ：
	//// 戻値       ：
	//// 担当者     ：鴫原 徹
	//// 備考       ：①'
	////            ：
	////
	StageLoader(FactoryPacket& i_Fpac, MapPartsStatus[]);
}; // StageLoader
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/





}
//end of namespace wiz.
