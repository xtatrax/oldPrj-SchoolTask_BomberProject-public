////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：Stage.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：鴫原 徹
//	内包ﾃﾞｰﾀと備考	：ステージ
//					：ステージはシーンから呼ばれます
//					▼
//	namespace wiz;
//		class StageLoader ;
//		class Stage ;
//		class MenuStage : public Stage ;
//
#include "StdAfx.h"
#include "Stage.h"
#include "BassItems.h"
#include "TL-String.h"
#include "Factory_Wall.h"
#include "Factory_Item.h"
#include "Factory_Magnetic.h"



namespace wiz{
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
void StageLoader::PartsGenerator(MapPartsStatus i_Data){
	//	: オブジェタイプに応じたオブジェクトを生成する
	//	: 生成の際､余計なデータが増えないように
	multimap<OBJID,DWORD>::iterator it;

	D3DCOLORVALUE Diffuse = {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,1.0f};


	//	: ワイドからマルチへ
	string sFilePath;
	TLIB::narrow(i_Data.sFilePath, sFilePath);

	wiz::OBJID ObjectID = (wiz::OBJID)i_Data.enClassid;

	switch( ObjectID ){
		//////////
		//
		case OBJID_NONE:
		default:
			return;
		//
		//////////
		case OBJID_3D_WALL :
			//////////
			//	: 壁
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< WallObject* >(( *m_pVec )[ it->second ])->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				WallObject* mgb = new WallObject( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"),
														m_pTexMgr->addTexture(m_pD3DDevice,L"Lightning.tga"), ObjectID);
				mgb->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
		case OBJID_3D_ITEM :
			//////////
			//	: アイテム
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< Item* >(( *m_pVec )[it->second])->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				FactoryPacket fpac;
				fpac.m_pTexMgr  = m_pTexMgr		;
				fpac.m_pVec     = m_pVec		;
				fpac.pD3DDevice = m_pD3DDevice	;
				//	: 登録がなかった場合
				Item* mgb = new Item( &fpac, NULL, ObjectID);
				mgb->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
		case OBJID_3D_MAGNET :
			//////////
			//	: アイテム
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< MagneticumObject3D* >(( *m_pVec )[it->second])->AddMagnetic(
					i_Data.vPos, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				MagneticumObject3D* mgb = new MagneticumObject3D( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"), ObjectID);
				mgb->AddMagnetic(
					i_Data.vPos, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
	}
};

/////////////////// ////////////////////
//// 関数名     ：void StageLoader::ObjectsLoader(wstring i_sFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：オブジェクト情報を構築します
//// 引数       ：  wstring i_sFilePath         //
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：CSVから読み取った情報を解析&インスタンス化します
////            ：PointSearch関数から呼ばれます
////
void StageLoader::ObjectsLoader(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数
	readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

	CSVMATRIX o_CsvMatrix ;					//	: 各パラメータの書いてある列を格納する構造体
	PointSearch(vvCsvData, o_CsvMatrix);	//	: 各パラメータが書いてある行を獲得

	//	: i		> 現在のセル
	//	: vvSz	> 最大のセル数
	//	: Line	> 列
	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		
		MapPartsStatus Status ;
		//////////
		//	: このひとかたまりで一行
		Line				= o_CsvMatrix.Line + i ;
		int		iNumber		=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiNumber    ].c_str(), NULL  , 10);
		Status.enClassid	=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiType      ].c_str(), NULL  , 10);
		Status.dwMotionNum	=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiMotionNum ].c_str(), NULL  , 10);
		Status.fTracSpeed	= (float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiTracSpeed ].c_str(), NULL );
		Status.sFilePath	= vvCsvData[ Line ][ o_CsvMatrix.Column.uiPath    ] ;
		Status.sTexturePath	= vvCsvData[ Line ][ o_CsvMatrix.Column.uiTexPath ] ;
		Status.vScale		= D3DXVECTOR3(
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleX ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleY ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleZ ].c_str(), NULL)
		);
		Status.vRot			= g_vZero ;
		Status.vPos			= g_vZero ;
		//	: このひとかたまりで一行
		//////////
		m_ObjeMap[iNumber] = Status;
	}
}
/////////////////// ////////////////////
//// 関数名     ：void StageLoader::StageGenerator(wstring i_sStageFilePath)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：
////
void StageLoader::StageGenerator(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数
	readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

	//	: 
	for(UINT i = 0 , isz = vvCsvData.size() ; i < isz ; i++ ){
		for(UINT j = 0 , jsz = vvCsvData[i].size() ; j < jsz ; j++ ){
			UINT PartsType = wcstol( vvCsvData[i][j].c_str() , NULL , 10 ) ;
			if( m_ObjeMap.count( PartsType ) ){
				m_ObjeMap[ PartsType ].vPos =
					D3DXVECTOR3((MAP_PARTS_WIDTH	*	j		)	-	MAP_PARTS_WIDTH		/	2,
								(MAP_PARTS_HEIGHT	*	isz-i	)	-	MAP_PARTS_HEIGHT	/	2,
								0.0f);

				PartsGenerator(m_ObjeMap[ PartsType ]);
			}
		}
	}
}
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
void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
{
	try{
		enum{
			STAGE_NUMBER = 0x0001,
			OBJECT_TYPE  = 0x0002,
			FILE_PATH    = 0x0004,
			TEX_PATH     = 0x0008,
			MOTION_NUM   = 0x0010,
			TRAC_SPEED   = 0x0020,
			SCALE_X      = 0x0040,
			SCALE_Y      = 0x0080,
			SCALE_Z      = 0x0100,
			IS_OK        = STAGE_NUMBER | OBJECT_TYPE | FILE_PATH | TEX_PATH | MOTION_NUM | TRAC_SPEED ,
			ALL_OK       = STAGE_NUMBER | OBJECT_TYPE | FILE_PATH | TEX_PATH | MOTION_NUM | TRAC_SPEED | SCALE_X   |  SCALE_Y   | SCALE_Z ,
		};
		WORD  SearchFlag = 0 ;
		for(BYTE i = 1 , Lane = i_vvCsvData.size(); i < Lane ; i++ ){
			for(BYTE j = 0 , Line = i_vvCsvData[i].size() ; j < Line ; j++){

				//	: 読み込み位置の設定
				if(i_vvCsvData[i][j] == L"Number"	){ o_CsvMatrix.Column.uiNumber		= j ; SearchFlag |= STAGE_NUMBER ; o_CsvMatrix.Line = i ; }
				if(i_vvCsvData[i][j] == L"Type"		){ o_CsvMatrix.Column.uiType		= j ; SearchFlag |= OBJECT_TYPE  ; }
				if(i_vvCsvData[i][j] == L"Path"		){ o_CsvMatrix.Column.uiPath		= j ; SearchFlag |= FILE_PATH    ; }
				if(i_vvCsvData[i][j] == L"TexPath"	){ o_CsvMatrix.Column.uiTexPath		= j ; SearchFlag |= TEX_PATH     ; }
				if(i_vvCsvData[i][j] == L"MotionNum"){ o_CsvMatrix.Column.uiMotionNum	= j ; SearchFlag |= MOTION_NUM   ; }
				if(i_vvCsvData[i][j] == L"TracSpeed"){ o_CsvMatrix.Column.uiTracSpeed	= j ; SearchFlag |= TRAC_SPEED   ; }
				if(i_vvCsvData[i][j] == L"ScaleX"	){ o_CsvMatrix.Column.uiScaleX		= j ; SearchFlag |= SCALE_X      ; }
				if(i_vvCsvData[i][j] == L"ScaleY"	){ o_CsvMatrix.Column.uiScaleY		= j ; SearchFlag |= SCALE_Y      ; }
				if(i_vvCsvData[i][j] == L"ScaleZ"	){ o_CsvMatrix.Column.uiScaleZ		= j ; SearchFlag |= SCALE_Z      ; }
				
				//	: すべての読み込みを完了
				if(SearchFlag == ALL_OK) return ;
			}
			//	: 一部読み込めなくても問題なし!
			if(SearchFlag == IS_OK) return ;
		}
//////////
//
//	ここまで飛んできたら確実に読み込みが失敗している
//

//	: デッバッグ用エラー
//#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//#endif

		//	: 一般向けエラー
		throw BaseException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::PointSearch()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}

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
void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint){
	try{
		enum{
			OBJECTS_CSV  = 0x01,
			STAGE_NUMBER = 0x02,
			FILE_PATH    = 0x04,
			ALL_OK       = OBJECTS_CSV | STAGE_NUMBER | FILE_PATH ,
		};
		BYTE  SearchFlag = 0 ;
		for(BYTE i = 1 , Lane = i_vvCsvData.size(); i < Lane ; i++ ){
			for(BYTE j = 0 , Line = i_vvCsvData[i].size() ; j < Line ; j++){

				//	: Objectリストを読み込み
				if(i_vvCsvData[i][j] == L"ObjectsCSV" ){ ObjectsLoader(i_vvCsvData[i][j+1]); SearchFlag |= OBJECTS_CSV ; }

				//	: 読み込み位置の設定
				if(i_vvCsvData[i][j] == L"StageNumber"){ o_NumberPoint.x = j ; o_NumberPoint.y = i ; SearchFlag |= STAGE_NUMBER ; }
				if(i_vvCsvData[i][j] == L"FilePath"   ){ o_PathPoint.x   = j ; o_PathPoint.y   = i ; SearchFlag |= FILE_PATH    ; }

				//	: すべての読み込みを完了
				if(SearchFlag == ALL_OK) return ;
			}
		}
//////////
//
//	ここまで飛んできたら確実に読み込みが失敗している
//

//	: デッバッグ用エラー
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
			//	: 
			if( !(SearchFlag & ( FILE_PATH )) ) 
					throw BaseException(
						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw BaseException(
						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: 一般向けエラー
		throw BaseException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::PointSearch()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}
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
void StageLoader::StageListLoader(wstring i_sFileName, BYTE i_byStageNum){
	try{

		vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数
		readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

		POINT NumberPoint ;		//	: ステージ番号が書いてある行と列のデータ
		POINT PathPoint   ;		//	: ステージの構成データファイル名が書いてある行と列のデータ
		PointSearch( vvCsvData , NumberPoint , PathPoint ) ;
		BYTE size = vvCsvData.size();
		do{
			if( wcstol( vvCsvData[NumberPoint.y][NumberPoint.x].c_str() , NULL , 10 ) 
				== i_byStageNum )
			{
				StageGenerator(vvCsvData[NumberPoint.y][NumberPoint.x +1]);
				return;
			}
		}while(size > ++NumberPoint.y);
		throw BaseException(
				L"", 
				L"StageLoader::StageListLoader()"
				);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::StageListLoader()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：FILEからStageを構築します
//// 引数       ：
//// 戻値       ：なし(失敗時は例外をthrow)
//// 担当者     ：
//// 備考       ：
////            ：
////
StageLoader::StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr){
	try{
		m_pD3DDevice	= pD3DDevice;
		m_pVec			= (&Vec);
		m_pTexMgr		= (&TexMgr);


			
		StageListLoader(i_sFileName, i_byStageNum);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::StageLoader()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}
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
StageLoader::StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus* i_Parts)
{
	try{
		m_pD3DDevice	= pD3DDevice;
		m_pVec			= (&Vec);
		m_pTexMgr		= (&TexMgr);


		for( DWORD num = 0 ; i_Parts[num].enClassid != OBJID_END ; num++ ){
			PartsGenerator(i_Parts[num]);
		}
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::StageLoader()"
				);
	}
	catch(...){
		throw BaseException(
				L"マップデータ配列の最後にOBJID_ENDを指定したか確認してださい", 
				L"↑StageLoader::StageLoader()"
				);
		throw;
	}
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
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
void StageLoader2::PartsGenerator(MapPartsStatus i_Data){
	//	: オブジェタイプに応じたオブジェクトを生成する
	//	: 生成の際､余計なデータが増えないように
	multimap<OBJID,DWORD>::iterator it;

	D3DCOLORVALUE Diffuse = {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,1.0f};


	//	: ワイドからマルチへ
	string sFilePath;
	TLIB::narrow(i_Data.sFilePath, sFilePath);

	wiz::OBJID ObjectID = (wiz::OBJID)i_Data.enClassid;

	switch( ObjectID ){
		//////////
		//
		case OBJID_NONE:
		default:
			return;
		//
		//////////
		case OBJID_3D_WALL :
			//////////
			//	: 壁
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< WallObject* >(( *m_pVec )[ it->second ])->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				WallObject* mgb = new WallObject( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"), m_pTexMgr->addTexture(m_pD3DDevice,L"Lightning.tga"), ObjectID);
				mgb->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
		case OBJID_3D_ITEM :
			//////////
			//	: アイテム
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< Item* >(( *m_pVec )[it->second])->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				FactoryPacket fpac;
				fpac.m_pTexMgr  = m_pTexMgr		;
				fpac.m_pVec     = m_pVec		;
				fpac.pD3DDevice = m_pD3DDevice	;
				//	: 登録がなかった場合
				Item* mgb = new Item( &fpac, NULL, ObjectID);
				mgb->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
		case OBJID_3D_MAGNET :
			//////////
			//	: アイテム
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< MagneticumObject3D* >(( *m_pVec )[it->second])->AddMagnetic(
					i_Data.vPos, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				MagneticumObject3D* mgb = new MagneticumObject3D( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"), ObjectID);
				mgb->AddMagnetic(
					i_Data.vPos, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
	}
};
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

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
void StageLoader2::PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
{
	try{
		enum{
			OBJECT_TYPE		= 0x0001,
			SCALE_X			= 0x0002,
			SCALE_Y			= 0x0004,
			SCALE_Z			= 0x0008,
			ROT_X			= 0x0010,
			ROT_Y			= 0x0020,
			ROT_Z			= 0x0040,
			POS_X			= 0x0080,
			POS_Y			= 0x0100,
			POS_Z			= 0x0200,
			IS_OK			= OBJECT_TYPE |   POS_X |   POS_Y ,
			ALL_OK			= OBJECT_TYPE | SCALE_X | SCALE_Y | SCALE_Z | ROT_X | ROT_Y | ROT_Z | POS_X | POS_Y | POS_Z,
		};
		WORD  SearchFlag = 0 ;
		for(BYTE i = 1 , Lane = i_vvCsvData.size(); i < Lane ; i++ ){
			for(BYTE j = 0 , Line = i_vvCsvData[i].size() ; j < Line ; j++){

				//	: 読み込み位置の設定
				if(i_vvCsvData[i][j] == L"Classid"	){ o_CsvMatrix.Column.uiClassid		= j ; SearchFlag |= OBJECT_TYPE      ; }

				if(i_vvCsvData[i][j] == L"ScaleX"	){ o_CsvMatrix.Column.uiScaleX		= j ; SearchFlag |= SCALE_X      ; }
				if(i_vvCsvData[i][j] == L"ScaleY"	){ o_CsvMatrix.Column.uiScaleY		= j ; SearchFlag |= SCALE_Y      ; }
				if(i_vvCsvData[i][j] == L"ScaleZ"	){ o_CsvMatrix.Column.uiScaleZ		= j ; SearchFlag |= SCALE_Z      ; }
				
				if(i_vvCsvData[i][j] == L"RotX"		){ o_CsvMatrix.Column.uiRotX		= j ; SearchFlag |= ROT_X      ; }
				if(i_vvCsvData[i][j] == L"RotY"		){ o_CsvMatrix.Column.uiRotY		= j ; SearchFlag |= ROT_Y      ; }
				if(i_vvCsvData[i][j] == L"RotZ"		){ o_CsvMatrix.Column.uiRotZ		= j ; SearchFlag |= ROT_Z      ; }
				
				if(i_vvCsvData[i][j] == L"PosX"		){ o_CsvMatrix.Column.uiPosX		= j ; SearchFlag |= POS_X      ; }
				if(i_vvCsvData[i][j] == L"PosY"		){ o_CsvMatrix.Column.uiPosY		= j ; SearchFlag |= POS_Y      ; }
				if(i_vvCsvData[i][j] == L"PosZ"		){ o_CsvMatrix.Column.uiPosZ		= j ; SearchFlag |= POS_Z      ; }
				
				//	: すべての読み込みを完了
				if(SearchFlag == ALL_OK) return ;
			}
			//	: 一部読み込めなくても問題なし!
			if(SearchFlag == IS_OK) return ;
		}
//////////
//
//	ここまで飛んできたら確実に読み込みが失敗している
//

//	: デッバッグ用エラー
//#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//#endif

		//	: 一般向けエラー
		throw BaseException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader2::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader2::PointSearch()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

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
void StageLoader2::ObjectsLoader(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数
	readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

	CSVMATRIX o_CsvMatrix ;					//	: 各パラメータの書いてある列を格納する構造体
	PointSearch(vvCsvData, o_CsvMatrix);	//	: 各パラメータが書いてある行を獲得

	//	: i		> 現在のセル
	//	: vvSz	> 最大のセル数
	//	: Line	> 列
	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		
		MapPartsStatus Status ;
		//////////
		//	: このひとかたまりで一行
		Line				= o_CsvMatrix.Line + i ;
		int		iNumber		=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiClassid    ].c_str(), NULL  , 10);
		Status.enClassid	=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiClassid      ].c_str(), NULL  , 10);
		Status.vScale		= D3DXVECTOR3(
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleX ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleY ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleZ ].c_str(), NULL)
		);
		Status.vRot			= D3DXVECTOR3(
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiRotX ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiRotY ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiRotZ ].c_str(), NULL)
		);
		Status.vPos			= D3DXVECTOR3(
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiPosX ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiPosY ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiPosZ ].c_str(), NULL)
		);
		Status.vRot			= g_vZero ;
		Status.vPos			= g_vZero ;
		//	: このひとかたまりで一行
		//////////
		m_ObjeMap[iNumber] = Status;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

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
void StageLoader2::StageGenerator(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数
	readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

	//	: 
	for(UINT i = 0 , isz = vvCsvData.size() ; i < isz ; i++ ){
		for(UINT j = 0 , jsz = vvCsvData[i].size() ; j < jsz ; j++ ){
			UINT PartsType = wcstol( vvCsvData[i][j].c_str() , NULL , 10 ) ;
			if( m_ObjeMap.count( PartsType ) ){
				m_ObjeMap[ PartsType ].vPos =
					D3DXVECTOR3((MAP_PARTS_WIDTH	*	j		)	-	MAP_PARTS_WIDTH		/	2,
								(MAP_PARTS_HEIGHT	*	isz-i	)	-	MAP_PARTS_HEIGHT	/	2,
								0.0f);

				PartsGenerator(m_ObjeMap[ PartsType ]);
			}
		}
	}
}


/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

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
void StageLoader2::PointSearch4StageList( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint){
	try{
		enum{
			STAGE_NUMBER	= 0x01,
			FILE_PATH		= 0x02,
			ALL_OK			= STAGE_NUMBER | FILE_PATH ,
		};
		BYTE  SearchFlag = 0 ;
		for(BYTE i = 1 , Lane = i_vvCsvData.size(); i < Lane ; i++ ){
			for(BYTE j = 0 , Line = i_vvCsvData[i].size() ; j < Line ; j++){

				//	: Objectリストを読み込み
				//if(i_vvCsvData[i][j] == L"ObjectsCSV" ){ ObjectsLoader(i_vvCsvData[i][j+1]); SearchFlag |= OBJECTS_CSV ; }

				//	: 読み込み位置の設定
				if(i_vvCsvData[i][j] == L"StageNumber"){ o_NumberPoint.x = j ; o_NumberPoint.y = i ; SearchFlag |= STAGE_NUMBER ; }
				if(i_vvCsvData[i][j] == L"FilePath"   ){ o_PathPoint.x   = j ; o_PathPoint.y   = i ; SearchFlag |= FILE_PATH    ; }

				//	: すべての読み込みを完了
				if(SearchFlag == ALL_OK) return ;
			}
		}
//////////
//
//	ここまで飛んできたら確実に読み込みが失敗している
//

//	: デッバッグ用エラー
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
			//	: 
			if( !(SearchFlag & ( FILE_PATH )) ) 
					throw BaseException(
						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw BaseException(
						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: 一般向けエラー
		throw BaseException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader::PointSearch()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：読み込むべきステージ構成データを獲得する
////            ：
////
void StageLoader2::StageListLoader(wstring i_sFileName, BYTE i_byStageNum,vector<wstring>& vsStageConsList){
	try{

		POINT NumberPoint ;		//	: ステージ番号を書書き始める行と列のデータ
		POINT PathPoint   ;		//	: ステージの構成データファイル名が書いてある行と列のデータ

		vector<vector<wstring>> vvCsvData;	//	: CSVデータを受け取るための変数

		readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

		//	: ステージ番号と構成ファイルを書き始める場所を獲得する
		PointSearch4StageList( vvCsvData , NumberPoint , PathPoint ) ;

		BYTE size = vvCsvData.size();
		do{
			//	: 対象のステージを探す
			if( wcstol( vvCsvData[NumberPoint.y][NumberPoint.x].c_str() , NULL , 10 ) 
				== i_byStageNum )
			{
				//	: 構成ファイルのリストを作成
				for(DWORD i = 1 ; i < vvCsvData[NumberPoint.y].size() ; i++ ){
					StageGenerator(vvCsvData[NumberPoint.y][NumberPoint.x +i]);
				}
				return;
			}
		}while(size > ++NumberPoint.y);


		throw BaseException(
				L"", 
				L"StageLoader2::StageListLoader()"
				);
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader2::StageListLoader()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：コンストラクタ
//// 用途       ：FILEからStageを構築します
//// 引数       ：
//// 戻値       ：なし(失敗時は例外をthrow)
//// 担当者     ：
//// 備考       ：
////            ：
////
StageLoader2::StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr){
	try{
		m_pD3DDevice	= pD3DDevice;
		m_pVec			= (&Vec);
		m_pTexMgr		= (&TexMgr);

		vector<wstring> vsStageConsList ;
		StageListLoader(i_sFileName, i_byStageNum,vsStageConsList);

			
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader2::StageLoader2()"
				);
	}
	catch(...){
		//再スロー
		throw;
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

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
StageLoader2::StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus* i_Parts)
{
	try{
		m_pD3DDevice	= pD3DDevice;
		m_pVec			= (&Vec);
		m_pTexMgr		= (&TexMgr);


		for( DWORD num = 0 ; i_Parts[num].enClassid != OBJID_END ; num++ ){
			//PartsGenerator(i_Parts[num]);
		}
	}
	catch(wiz::BaseException& e){
		//再スロー
		throw BaseException(
				e.what_w(), 
				L"↑StageLoader2::StageLoader2()"
				);
	}
	catch(...){
		throw BaseException(
				L"マップデータ配列の最後にOBJID_ENDを指定したか確認してださい", 
				L"↑StageLoader2::StageLoader2()"
				);
		throw;
	}
}

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 Stage 定義部
****************************************************************************/
/**************************************************************************
 void Stage::Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
void Stage::Clear(){
	SafeDelete(m_pChildStage);
	//SafeDelete(m_pParStage);
	SafeDeletePointerContainer(m_Vec);
	m_TexMgr.Release();
}

/**************************************************************************
 Stage::Stage(
 Stage* Par	//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
Stage::Stage(Stage* Par)
:m_pParStage(Par),m_pChildStage(0),m_IsDialog(false)
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
,m_bSlow(false)
#endif
/////////////////// ////////////////////

{}
/**************************************************************************
virtual Stage::~Stage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Stage::~Stage(){
	Clear();
}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void Stage::Update(UpdatePacket& i_UpdatePacket)
{
	i_UpdatePacket.pVec = &m_Vec ;
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
	float fElapsedTime = (float)i_UpdatePacket.pTime->getElapsedTime();
	if(GetAsyncKeyState( MYVK_DEBUG_STOP_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime ;
		if(m_bUpdate){
			if(s_fTime > 0.05f){
				m_bUpdate = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bUpdate = true ;
				s_fTime   = 0 ;
			}
		}
	}
	static float fSlowAccumulator = 0;
	if(GetAsyncKeyState( MYVK_DEBUG_SLOW_UPDATE )){
		static float s_fTime = 0;
		s_fTime += fElapsedTime;
		if(m_bSlow){
			if(s_fTime > 0.05f){
				m_bSlow = false ;
				s_fTime   = 0 ;
			}
		}else{
			if(s_fTime > 0.05f){
				m_bSlow = true ;
				s_fTime   = 0 ;
			}
		}
	}
	if( m_bSlow && (fSlowAccumulator += fElapsedTime) < 1.0f ){
		return;
	}
	fSlowAccumulator = 0 ;
#endif
	if(m_bUpdate){
	//配置オブジェクトの描画
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		if(!m_Vec[i]->getDead()){
			m_Vec[i]->AccessBegin();
			m_Vec[i]->Update(i_UpdatePacket) ;
			m_Vec[i]->AccessEnd();
		}
	}
	}
}
/////////////////// ////////////////////
//// 関数名     ：void Render(RenderPacket& i_RenderPacket);
//// カテゴリ   ：関数
//// 用途       ：ターゲットレンダリング
//// 引数       ：  RenderPacket& i_RenderPacket        // レンダー処理に流すデータの集合体
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：画面以外のバッファーに描画する
////            ：
////
void Stage::Render(RenderPacket& i_RenderPacket){
	i_RenderPacket.pVec = &m_Vec ;
	//配置オブジェクトの描画
	vector<Object*>::iterator it = m_Vec.begin();
	while( it != m_Vec.end() ){
		if(!(*it)->getDead()){
			(*it)->AccessBegin();
			(*it)->TargetRender(i_RenderPacket);
			(*it)->AccessEnd();
		} else {
			
			SAFE_DELETE( (*it) ) ;
			it = m_Vec.erase( it ) ;
			continue;
		}
		it++;
	}
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void Stage::Draw(DrawPacket& i_DrawPacket)
{
	try{
		i_DrawPacket.pVec = &m_Vec ;
		//配置オブジェクトの描画
		vector<Object*>::size_type sz = m_Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			m_Vec[i]->AccessBegin();
			m_Vec[i]->Draw(i_DrawPacket);
			m_Vec[i]->AccessEnd();
		}
	}
	catch(exception& e){
        throw;
	}
    catch(...){
        throw;
    }
}
/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
void Stage::TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget){

}

/////////////////// ////////////////////
//// 用途       ：
//// カテゴリ   ：関数
//// 用途       ：オブジェクトをディスプレイに表示する
//// 引数       ：
//// 戻値       ：無し
//// 担当者     ：鴫原 徹
//// 備考       ：
void Stage::DefaultRender(){

}

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/**************************************************************************
 MenuStage 定義部
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par),m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false){
	m_pChildStage = 0;
	try{
        // ライティングモード
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //ライトのインスタンス初期化
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        m_Vec.push_back(
			new DirectionalLight(
				pD3DDevice,
				Diffuse,
				Specular,
				Ambient,
				D3DXVECTOR3(0.4f, -1.0f, 0.4f)
			)
		);
        //カメラのインスタンス初期化
        m_Vec.push_back(
			new Camera(
				pD3DDevice,
				D3DXVECTOR3( 0.0f, 2.0f, -30.0f),
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				1.0f,
				100.0f,
				60.0f
			)
		);

	}
	catch(...){
		//親クラスのClear()を呼ぶ
		Clear();
		//再スロー
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MenuStage::~MenuStage(){
	//ボタン配列のみクリアする
	//配置されてるポインタの削除は行なわない
	m_ButtonVec.clear();
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void MenuStage::Update(UpdatePacket& i_UpdatePacket)
{
	if( i_UpdatePacket.pTxMgr == NULL ) i_UpdatePacket.pTxMgr = &m_TexMgr ;
	CONTROLER_STATE	ControllerState1P = i_UpdatePacket.pCntlState[0];
    if(!m_SelectLock){
		//	: 次のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN 
			|| ControllerState1P.Gamepad.sThumbLY < 0){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: 前のボタンへ
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP
			|| ControllerState1P.Gamepad.sThumbLY > 0){
			if(m_SelectIndex == 0){
				m_SelectIndex = (m_ButtonVec.size() - 1);
			}
			else{
				m_SelectIndex--;
			}
			m_SelectLock = true;
		}
		//選択状態の設定
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//選択が決定された
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_A&&
			!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setPressed();
			m_SelectLock = true;
		}
	}
	if(!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		&&
		ControllerState1P.Gamepad.sThumbLY == 0
		&&
		!(ControllerState1P.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		&& 
		!m_IsAnimetion
		){
		m_SelectLock = false;
	}
	Stage::Update(i_UpdatePacket);
}


/**************************************************************************
 void MenuStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& i_DrawPacket.pCommand					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void MenuStage::Draw(DrawPacket& i_DrawPacket){
	Stage::Draw(i_DrawPacket);
}

}
//end of namespace wiz.
