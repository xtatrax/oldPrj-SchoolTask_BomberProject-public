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
class wiz::menuobject::Button;
using namespace menuobject ;
//class Button2;
//**************************************************************************
// class StageFactory;
//
// 担当者  : 鴫原 徹
// 用途    : ファクトリーの根底クラス
//**************************************************************************/
class StageFactory{
protected:
	bool m_ONNowLoading ;
public:
	StageFactory():m_ONNowLoading(false){}
	virtual StageLoader* StageCreate( const FactoryPacket fPack ) = 0;

};

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
	map<UINT,MapPartsStatus>		m_ObjeMap;
	multimap<wiz::OBJID,DWORD>		m_ObjeTypeMap;

	TextureManager*		m_pTexMgr;
	vector<Object*>*	m_pVec;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：鴫原 徹
//// 備考       ：
////            ：
////
	void PartsGenerator(MapPartsStatus i_Data);
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者		：鴫原 徹
//// 備考       ：
////            ：
////
	void D2(MapPartsStatus i_Data);
/////////////////// ////////////////////
//// 関数名     ：void ObjectsLoader(wstring i_sFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：オブジェクト情報を構築します
//// 引数       ：  wstring i_sFilePath         //
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：PointSearch関数から呼ばれます
////            ：
////
	void ObjectsLoader(wstring i_sFilePath);
/////////////////// ////////////////////
//// 関数名     ：void StageGenerator(wstring i_sStageFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
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
////            ：
////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);
/////////////////// ////////////////////
//// 関数名     ：void PointSearch( vector<vector<wstring>>& i_vvCsvData ,
////            ：    POINT& o_NumberPoint , POINT& o_PathPoint)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, POINT& o_NumberPoint, POINT& o_PathPoint);
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum);
public:
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
	StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr);

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////
	StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus[]);
}; // StageLoader
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//**************************************************************************
// class StageLoader2;
//
// 担当者  : 鴫原 徹
// 用途    : CSVデータからステージを構築します
//**************************************************************************
class StageLoader2{
	struct CSVMATRIX {
		//	: 行
		UINT Line ;
		//	: 列
		struct {
			UINT	uiClassid			;	//	番号
			UINT	uiPosX				;	//	種類
			UINT	uiPosY				;	//	FILE
			UINT	uiPosZ				;	//	FILE
			UINT	uiScaleX			;	//	テクスチャ
			UINT	uiScaleY			;	//	モーション
			UINT	uiScaleZ			;	//	モーション
			UINT	uiRotX				;	//	モーションの速さ
			UINT	uiRotY				;	//	モーションの速さ
			UINT	uiRotZ				;	//	モーションの速さ
			UINT	uiColor				;	//	X伸縮
		}Column;
	};
	map<UINT,MapPartsStatus>		m_ObjeMap;
	multimap<wiz::OBJID,DWORD>		m_ObjeTypeMap;

	TextureManager*		m_pTexMgr;
	vector<Object*>*	m_pVec;
	LPDIRECT3DDEVICE9	m_pD3DDevice;


/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：StageGeneratorから
////            ：
////

	void PartsGenerator(MapPartsStatus i_Data);


/////////////////// ////////////////////
//// 関数名     ：void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring    i_sStageFilePath         //  ステージの構成ファイルへのパス
////            ： CSVMATRIX&  o_CsvMatrix				//	読み込むべき行と列の詰め合わせ
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
////
	
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);


/////////////////// ////////////////////
//// 関数名     ：void StageLoader2::ObjectsLoader(wstring i_sFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：オブジェクト情報を構築します
//// 引数       ：  wstring i_sFilePath         //
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：CSVから読み取った情報を解析&インスタンス化します
////            ：PointSearch関数から呼ばれます
////

	void ObjectsLoader(wstring i_sFileName);


/////////////////// ////////////////////
//// 関数名     ：void StageLoader2::StageGenerator(wstring i_sStageFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
////

	void StageGenerator(wstring i_sFileName);


/////////////////// ////////////////////
//// 関数名     ：void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
////

	void PointSearch4StageList( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint);


/////////////////// ////////////////////
//// 関数名     ：StageListLoader()
//// カテゴリ   ：コンストラクタ
//// 用途       ：Stages.csvを解析する
//// 引数       ：
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：コンストラクタから呼ばれる
////            ：
////

	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum,vector<wstring>& vsStageConsList);


public:
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////

	StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr);


/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：
////            ：
////

	StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus[]);


}; // StageLoader2
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



}
//end of namespace wiz.
