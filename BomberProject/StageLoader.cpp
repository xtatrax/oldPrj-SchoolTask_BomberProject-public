////////////////////////////// //////////////////////////////
//	プロジェクト	：DirectX Program Bass Project
//	ファイル名		：StageLoader.cpp
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
#include "StdAfx.h"
#include "StageLoader.h"
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
				//	: そのままオブジェクトを追加
				dynamic_cast< WallObject* >(( *m_pVec )[ it->second ])->AddWall(
					i_Data.vScale		,
					i_Data.vRot			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				WallObject* mgb ;
				UINT Num = SOF_NOTFOUND ;
				if( mgb = (WallObject*)SearchObjectFromID(m_pVec,OBJID_3D_WALL,&Num) ){
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , Num ));
				}else{
					//	: インスタンスを生成
					mgb = new WallObject(
						m_pD3DDevice,
						m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"),
						m_pTexMgr->addTexture(m_pD3DDevice,L"Lightning.tga"),
						ObjectID
					);				
					//	: オブジェクトリストへ登録
					m_pVec->push_back(mgb);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
				}
				//	: アイテムの追加
				mgb->AddWall(
					i_Data.vScale	,
					i_Data.vRot		,
					i_Data.vPos		,
					i_Data.Diffuse	,
					i_Data.Specular	,
					i_Data.Ambient
				);

			}
			break;
			//	: 壁
			//////////

		case OBJID_3D_ITEM :
			//////////
			//	: アイテム
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				//	: そのままオブジェクトを追加
				dynamic_cast< Item* >(( *m_pVec )[it->second])->addItem(
					i_Data.vPos			,
					i_Data.vScale		,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				FactoryPacket fpac(m_pD3DDevice,false,m_pVec,m_pTexMgr);

				//	: インスタンスを生成
				Item* mgb = new Item( &fpac, NULL, ObjectID);

				//	: アイテムの追加
				mgb->addItem(
					i_Data.vPos			,
					i_Data.vScale		,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);

				//	: オブジェクトリストへ登録
				m_pVec->push_back(mgb);

				//	: オブジェクトの場所を覚えておく
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
			//	: アイテム
			//////////

		case OBJID_3D_STATIC_MAGNET :
			//////////
			//	: 磁界
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< MagneticumObject3D* >(( *m_pVec )[it->second])->AddMagnetic(
					i_Data.vScale, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: 登録がなかった場合
				MagneticumObject3D* mgb = new MagneticumObject3D( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"), ObjectID);
				mgb->AddMagnetic(
					i_Data.vScale, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
			//	: 磁界
			//////////
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
float	getCsvFloat(	vector<vector<wstring>> vvCsvData, vector<vector<wstring>>::size_type Line, UINT Num, float		Default = 0.0f){
	if( Num == UINT_MAX ) return Default ;
	return (float)wcstod( vvCsvData[ Line ][ Num ].c_str(), NULL);
};
LONG	getCsvLong(		vector<vector<wstring>> vvCsvData, vector<vector<wstring>>::size_type Line, UINT Num, LONG		Default = 0){
	if( Num == UINT_MAX ) return Default ;
	return wcstol( vvCsvData[ Line ][ Num ].c_str(), NULL, 10);
};
wstring	getCsvString(		vector<vector<wstring>> vvCsvData, vector<vector<wstring>>::size_type Line, UINT Num, wstring	Default = L"" ){
	if( Num == UINT_MAX ) return Default ;
	return vvCsvData[ Line ][ Num ] ;
};
void StageLoader::ObjectsLoader(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;		//	: CSVデータを受け取るための変数
	if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSVデータの受け取り
		throw LoaderException(
			L"オブジェクト定義ファイルのパスが正しいか、データが破損していないか確認してください",
			L"StageLoader::ObjectsLoader()"
		);
	}
	CSVMATRIX o_CsvMatrix ;					//	: 各パラメータの書いてある列を格納する構造体
	PointSearch(vvCsvData, o_CsvMatrix);	//	: 各パラメータが書いてある行を獲得

	//	: i		> 現在のセル
	//	: vvSz	> 最大のセル数
	//	: Line	> 列
	D3DCOLORVALUE Diffuse	= {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient	= {0.5f,0.5f,0.5f,1.0f};

	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		
		MapPartsStatus Status ;
		//////////
		//	: このひとかたまりで一行
		Line				= o_CsvMatrix.Line + i ;
		int		iNumber		= getCsvLong(	vvCsvData, Line, o_CsvMatrix.Column.uiNumber			) ;
		Status.enClassid	= getCsvLong(	vvCsvData, Line, o_CsvMatrix.Column.uiType				) ;
		Status.dwMotionNum	= getCsvLong(	vvCsvData, Line, o_CsvMatrix.Column.uiMotionNum			) ;
		Status.fTracSpeed	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiTracSpeed, 1.0f	) ;
		Status.sFilePath	= getCsvString( vvCsvData, Line, o_CsvMatrix.Column.uiPath				) ;
		Status.sTexturePath	= getCsvString( vvCsvData, Line, o_CsvMatrix.Column.uiTexPath			) ;
		Status.vScale.x		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleX			) ;
		Status.vScale.y		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleY			) ;
		Status.vScale.z		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleZ			) ;
		Status.vRot.x		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotX				) ;
		Status.vRot.y		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotY				) ;
		Status.vRot.z		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotZ				) ;
		Status.vOffset.x	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosX				) ;
		Status.vOffset.y	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosY				) ;
		Status.vOffset.z	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosZ				) ;

		Status.Ambient		= Ambient	;
		Status.Specular		= Specular	;
		Status.Diffuse		= Diffuse	;
		//Status.vRot			= g_vZero	;
		//Status.vPos			= g_vZero	;
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
	//readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り
	if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSVデータの受け取り
		throw LoaderException(
			L"ステージ定義ファイルのパスが正しいか、データが破損していないか確認してください",
			L"StageLoader::StageGenerator()"
		);

	}
	//	: 
	for(UINT i = 0 , isz = vvCsvData.size() ; i < isz ; i++ ){
		for(UINT j = 0 , jsz = vvCsvData[i].size() ; j < jsz ; j++ ){
			UINT PartsType = wcstol( vvCsvData[i][j].c_str() , NULL , 10 ) ;
			if( m_ObjeMap.count( PartsType ) ){
				m_ObjeMap[ PartsType ].vPos =
					D3DXVECTOR3(
						(MAP_PARTS_WIDTH	*	isz-i		)	-	MAP_PARTS_WIDTH		/	2,
						(MAP_PARTS_HEIGHT	*	j	)	-	MAP_PARTS_HEIGHT	/	2,
						0.0f
					)
					+ m_ObjeMap[ PartsType ].vOffset;

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
			STAGE_NUMBER	= 0x0001,
			OBJECT_TYPE		= 0x0002,
			FILE_PATH		= 0x0004,
			TEX_PATH		= 0x0008,
			MOTION_NUM		= 0x0010,
			TRAC_SPEED		= 0x0020,
			SCALE_X			= 0x0040,
			SCALE_Y			= 0x0080,
			SCALE_Z			= 0x0100,
			ROT_X			= 0x0200,
			ROT_Y			= 0x0400,
			ROT_Z			= 0x0800,
			POS_X			= 0x1000,
			POS_Y			= 0x2000,
			POS_Z			= 0x4000,
			POOL			= 0x8000,

			IS_OK			= STAGE_NUMBER | OBJECT_TYPE ,
			ALL_OK			= STAGE_NUMBER | OBJECT_TYPE | FILE_PATH | TEX_PATH | MOTION_NUM | TRAC_SPEED | SCALE_X   |  SCALE_Y   | SCALE_Z ,
		};

		WORD  SearchFlag = 0 ;
		for(BYTE i = 1 , Lane = i_vvCsvData.size(); i < Lane ; i++ ){
			for(BYTE j = 0 , Line = i_vvCsvData[i].size() ; j < Line ; j++){

				//	: 読み込み位置の設定
				if(i_vvCsvData[i][j] == L"Number"	){ o_CsvMatrix.Column.uiNumber		= j ; SearchFlag |= STAGE_NUMBER ; o_CsvMatrix.Line = i ; }
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(i_vvCsvData[i][j] == L"Type"		){ o_CsvMatrix.Column.uiType		= j ; SearchFlag |= OBJECT_TYPE  ; }
				if(i_vvCsvData[i][j] == L"Path"		){ o_CsvMatrix.Column.uiPath		= j ; SearchFlag |= FILE_PATH    ; }
				if(i_vvCsvData[i][j] == L"TexPath"	){ o_CsvMatrix.Column.uiTexPath		= j ; SearchFlag |= TEX_PATH     ; }
				if(i_vvCsvData[i][j] == L"MotionNum"){ o_CsvMatrix.Column.uiMotionNum	= j ; SearchFlag |= MOTION_NUM   ; }
				if(i_vvCsvData[i][j] == L"TracSpeed"){ o_CsvMatrix.Column.uiTracSpeed	= j ; SearchFlag |= TRAC_SPEED   ; }
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(i_vvCsvData[i][j] == L"ScaleX"	){ o_CsvMatrix.Column.uiScaleX		= j ; SearchFlag |= SCALE_X      ; }
				if(i_vvCsvData[i][j] == L"ScaleY"	){ o_CsvMatrix.Column.uiScaleY		= j ; SearchFlag |= SCALE_Y      ; }
				if(i_vvCsvData[i][j] == L"ScaleZ"	){ o_CsvMatrix.Column.uiScaleZ		= j ; SearchFlag |= SCALE_Z      ; }
				if(i_vvCsvData[i][j] == L"RotX"		){ o_CsvMatrix.Column.uiRotX		= j ; SearchFlag |= ROT_X        ; }
				if(i_vvCsvData[i][j] == L"RotY"		){ o_CsvMatrix.Column.uiRotY		= j ; SearchFlag |= ROT_Y        ; }
				if(i_vvCsvData[i][j] == L"RotZ"		){ o_CsvMatrix.Column.uiRotZ		= j ; SearchFlag |= ROT_Z        ; }
				if(i_vvCsvData[i][j] == L"PosX"		){ o_CsvMatrix.Column.uiPosX		= j ; SearchFlag |= POS_X        ; }
				if(i_vvCsvData[i][j] == L"PosY"		){ o_CsvMatrix.Column.uiPosX		= j ; SearchFlag |= POS_Y        ; }
				if(i_vvCsvData[i][j] == L"PosZ"		){ o_CsvMatrix.Column.uiPosX		= j ; SearchFlag |= POS_Z        ; }
				if(i_vvCsvData[i][j] == L"Pool"		){ o_CsvMatrix.Column.uiPool		= j ; SearchFlag |= POOL         ; }
				
				//	: すべての読み込みを完了
				if(SearchFlag == ALL_OK) return ;
			}
			//	: 一部読み込めなくても問題なし!
			if(SearchFlag & IS_OK) return ;
		}
//////////
//
//	ここまで飛んできたら確実に読み込みが失敗している
//

//	: デッバッグ用エラー
//#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader::PointSearch()"
//					);
//#endif

		//	: 一般向けエラー
		throw LoaderException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()\nA"
		);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
					throw LoaderException(
						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw LoaderException(
						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: 一般向けエラー
		throw LoaderException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()\nB"
		);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
		if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSVデータの受け取り
			throw LoaderException(
				L"Stages.csvのパスが正しいか、データが破損していないか確認してください",
				L"StageLoader::StageListLoader()"
			);

		}
		//readcsv(i_sFileName,vvCsvData);		//	: CSVデータの受け取り

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
		throw LoaderException(
				L"", 
				L"StageLoader::StageListLoader()"
				);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
//// 用途       ：FILEからStageLoaderを構築します
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
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
				e.what_w(), 
				L"↑StageLoader::StageLoader()"
				);
	}
	catch(...){
		throw LoaderException(
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
		case OBJID_3D_STATIC_MAGNET :
			//////////
			//	: 初期配置磁界
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
//					throw LoaderException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
//						L"StageLoader2::PointSearch()"
//					);
//#endif

		//	: 一般向けエラー
		throw LoaderException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader2::PointSearch()"
		);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
					throw LoaderException(
						L"ファイルパスの行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw LoaderException(
						L"ステージ番号の行が見つかりませんでした\n→CSVデータを確認してください",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: 一般向けエラー
		throw LoaderException(
			L"ステージデータの読み込みに失敗しました\n→データが破損していないか確認してください",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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


		throw LoaderException(
				L"", 
				L"StageLoader2::StageListLoader()"
				);
	}
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
//// 用途       ：FILEからStageLoaderを構築します
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
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
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
	catch(wiz::LoaderException& e){
		//再スロー
		throw LoaderException(
				e.what_w(), 
				L"↑StageLoader2::StageLoader2()"
				);
	}
	catch(...){
		throw LoaderException(
				L"マップデータ配列の最後にOBJID_ENDを指定したか確認してださい", 
				L"↑StageLoader2::StageLoader2()"
				);
		throw;
	}
}

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


}
//end of namespace wiz.
