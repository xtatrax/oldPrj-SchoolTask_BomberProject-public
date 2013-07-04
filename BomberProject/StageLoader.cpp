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
#include "Factory_Goal.h"
#include "Factory_Enemy.h"



namespace wiz{
using namespace bomberobject;

/////////////////// ////////////////////
//// 関数名     ：
//// カテゴリ   ：
//// 用途       ：
//// 引数       ：
//// 戻値       ：
//// 担当者     ：
//// 備考       ：StageGeneratorから
////            ：⑦
////
void StageLoader::PartsGenerator(MapPartsStatus i_Data){
	//	: オブジェタイプに応じたオブジェクトを生成する
	//	: 生成の際､余計なデータが増えないように
	multimap<OBJID,Object*>::iterator it;


	//	: ワイドからマルチへ
	string sFilePath;
	TLIB::narrow(i_Data.sFilePath, sFilePath);


	switch( (wiz::OBJID)i_Data.enClassid ){

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		//////////
		//
		case CLASSID_NONE:
		default:
			return;
		//
		//////////
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_WALL :	//	: 20
		{
			//////////
			//	: 壁

			//	: たーげっと。
			typedef WallObject TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_WALL ;
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				//	: そのままオブジェクトを追加
				dynamic_cast< TARGET_CLASS* >( it->second )->AddWall(
					i_Data.vScale		,
					i_Data.vRot			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALLを確保します\n",this);

				//	: 登録がなかった場合
				WallObject* cp ;

				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID(ObjectID) ){
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> Object一覧より発見しました\n",this);
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> Object一覧より発見できませんでした 新規に作成します\n",this);
					//	: インスタンスを生成
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice(),
						m_pFpac->AddTexture(L"Lightning.png"),
						ObjectID
					);
					//	: オブジェクトリストへ登録
					m_pFpac->AddObject(cp);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp));
				}
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> 初回登録完了\n",this);
				//	: アイテムの追加
				cp->AddWall(
					i_Data.vScale	,
					i_Data.vRot		,
					i_Data.vPos		,
					i_Data.Diffuse	,
					i_Data.Specular	,
					i_Data.Ambient
				);
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> 初回の追加行動を完了します\n",this);
			}
			//	: 壁
			//////////
		}
		break;

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_ITEM :	//	: 40
		{
			//////////
			//	: アイテム
			D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
			D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};

			//	: たーげっと。
			typedef Item TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_ITEM ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				//	: そのままオブジェクトを追加
				dynamic_cast< TARGET_CLASS* >( it->second )->addItem(
					i_Data.vPos			,
					g_vOne				,
					BallDiffuse			,
					BallSpecular		,
					BallAmbient			,
					i_Data.vScale.x
				);
			}else{
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEMを確保します\n",this);
				//	: 登録がなかった場合
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> Object一覧より発見しました\n",this);
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> Object一覧より発見できませんでした 新規に作成します\n",this);
					//	: 登録がなかった場合
					//	: インスタンスを生成
					cp  = new Item( m_pFpac, NULL, ObjectID);

					//	: オブジェクトリストへ登録
					m_pFpac->AddObject(cp);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> 初回登録完了\n",this);

				//	: アイテムの追加
				cp->addItem(
					i_Data.vPos			,
					g_vOne				,
					BallDiffuse		,
					BallSpecular		,
					BallAmbient		,
					i_Data.vScale.x
				);
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> 初回の追加行動を完了します\n",this);
			}
			//	: アイテム
			//////////
		}
		break;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_MAGNET :	//	: 30 
		{
			//////////
			//	: 磁界

			//	: たーげっと。
			typedef StaticMagnetField TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_STATIC_MAGNET ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< TARGET_CLASS* >( it->second )->AddMagnetic(
					i_Data.vPos			,
					i_Data.bPool		,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNETを確保します\n",this);
				//	: 登録がなかった場合
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID  ) ){
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> Object一覧より発見しました\n",this);
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> Object一覧より発見でいませんでした 新規に作成します\n",this);
					//	: 登録がなかった場合
					//	: インスタンスを生成
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice()	,
						ObjectID
					);

					//	: オブジェクトリストへ登録
					m_pFpac->AddObject(cp);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> 初回登録完了\n",this);
				//	: 登録がなかった場合
				cp->AddMagnetic(
					i_Data.vPos		,
					i_Data.bPool	,
					i_Data.Diffuse	,
					i_Data.Specular	,
					i_Data.Ambient
				);
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> 初回の追加行動を完了します\n",this);
			}
			//	: 磁界
			//////////
		}
		break;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_ENEMY :	//	: 31
		{
			//////////
			//	: 敵(ウイルス?)

			//	: たーげっと。
			typedef EnemyModel TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_ENEMY ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< TARGET_CLASS* >( it->second )->AddEnemy(
					g_vOne		,
					g_vZero			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient		,
					i_Data.bPool
				);
			}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMYを確保します\n",this);
				//	: 登録がなかった場合
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> Object一覧より発見しました\n",this);
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> Object一覧より発見でいませんでした 新規に作成します\n",this);
					//	: 登録がなかった場合
					D3DCOLORVALUE EnemyDiffuse	= {1.0f,1.0f,1.0f,1.0f};
					D3DCOLORVALUE EnemySpecular	= {1.0f,1.0f,1.0f,1.0f};
					D3DCOLORVALUE EnemyAmbient	= {1.0f,1.0f,1.0f,1.0f};
					//	: インスタンスを生成
					cp = new TARGET_CLASS(
						*m_pFpac,
						RCTEXT_MODEL_ENEMY,
						ObjectID
					);

					//	: オブジェクトリストへ登録
					m_pFpac->AddObject(cp);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> 初回登録完了\n",this);
				//	: 登録がなかった場合
				cp->AddEnemy(
					g_vOne		,
					g_vZero			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient		,
					i_Data.bPool
				);
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> 初回の追加行動を完了します\n",this);
			}
			//	: 敵(ウイルス?)
			//////////
		}
		break;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_CHECKPOINT :	//	: 11 
		{
			//////////
			//	: チェックポイント

			//	: たーげっと。
			typedef CheckPoint TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_SYS_CHECKPOINT ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: 登録を見つけた場合
				dynamic_cast< TARGET_CLASS* >( it->second )->add(
					i_Data.vPos
				);
			}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINTを確保します\n",this);
				//	: 登録がなかった場合
				TARGET_CLASS* cp;

				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> Object一覧より発見しました\n",this);
					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> Object一覧より発見でいませんでした 新規に作成します\n",this);
					//	: 登録がなかった場合
					//	: インスタンスを生成
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice()	,
						100.0f			,
						m_pFpac->AddTexture( L"particle.png" ),
						m_pFpac->AddTexture( L"CHECK_POINT1.png" ),
						m_pFpac->AddTexture( L"LAST.png" ),
						ObjectID
					);

					//	: オブジェクトリストへ登録
					m_pFpac->AddObject(cp);

					//	: オブジェクトの場所を覚えておく
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> 初回登録完了\n",this);
				//	: 登録がなかった場合
				cp->add(
					i_Data.vPos
				);
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> 初回の追加行動を完了します\n",this);
			}
			//	: 磁界
			//////////
		}
		break;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
		case CLASSID_GOAL :	//:10
			//////////
			//	: クリア領域
			D3DCOLORVALUE MemoryDiffuse = {1.0f,1.0f,1.0f,0.0f};
			D3DCOLORVALUE MemorySpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE MemoryAmbient = {1.0f,1.0f,1.0f,0.0f};

			D3DCOLORVALUE GoalDiffuse = {0.0f,1.0f,1.0f,0.3f};
			D3DCOLORVALUE GoalSpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE GoalAmbient = {0.0f,1.0f,1.0f,0.3f};

			wiz::OBJID ObjectID = OBJID_SYS_CLEARAREA ;
			//	: インスタンスを生成
			GoalObject* go = new GoalObject(
				m_pFpac->GetDevice()	,
				D3DXVECTOR3(20.0f, i_Data.vPos.y,  0.0f),
				NULL			,
				m_pFpac->AddTexture( L"GOAL.png" ),
				ObjectID
			);
			FMemoryTex* mt = new FMemoryTex(
				m_pFpac->GetDevice(),
				m_pFpac->AddTexture( L"USB.png" )
			);
			
			//	: ゴールの追加
			//mgb->addGoal(
			//	D3DXVECTOR3( 100.0f,  2.0f, 0.0f )			,
			//	D3DXVECTOR3(  0.0f,  0.0f, 0.0f )			,
			//	D3DXVECTOR3( 20.0f, i_Data.vPos.y,  0.0f )	,
			//	GoalDiffuse		,
			//	GoalSpecular	,
			//	GoalAmbient
			//);
			mt->AddMemory(
				D3DXVECTOR3(8.0f,32.0f,0.0f),
				g_vZero			,
				D3DXVECTOR3(28.0f,i_Data.vPos.y + 2.0f ,0.0f),
				MemoryDiffuse		,
				MemorySpecular	,
				MemoryAmbient
			);

			m_pFpac->AddObject( mt );
			//	: オブジェクトリストへ登録
			m_pFpac->AddObject( go );
			break;
			//	: クリア領域
			//////////
		}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
};

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
						(MAP_PARTS_WIDTH	*	j		)	-	MAP_PARTS_WIDTH		/	2 + 1.0f,
						(MAP_PARTS_HEIGHT	*	/*isz-*/i	)	-	MAP_PARTS_HEIGHT	/	2,
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
////            ：⑤
////
void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
{
	DWORD dwSTime = TLIB::Tempus::TimeGetTime();
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
POLE getCsvPOLE(		vector<vector<wstring>> vvCsvData, vector<vector<wstring>>::size_type Line, UINT Num, POLE	Default = POLE_N ){
	if( Num == UINT_MAX ) return Default ;
	if( vvCsvData[ Line ][ Num ] == L"N" )	return POLE_N ;
	else									return POLE_S ;
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
		Status.sFilePath	= getCsvString(	vvCsvData, Line, o_CsvMatrix.Column.uiPath				) ;
		Status.sTexturePath	= getCsvString(	vvCsvData, Line, o_CsvMatrix.Column.uiTexPath			) ;
		Status.vScale.x		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleX			) ;
		Status.vScale.y		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleY			) ;
		Status.vScale.z		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiScaleZ			) ;
		Status.vRot.x		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotX				) ;
		Status.vRot.y		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotY				) ;
		Status.vRot.z		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiRotZ				) ;
		Status.vOffset.x	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosX				) ;
		Status.vOffset.y	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosY				) ;
		Status.vOffset.z	= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosZ				) ;
		Status.bPool		= getCsvPOLE(	vvCsvData, Line, o_CsvMatrix.Column.uiPool				) ;

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
//// 関数名     ：void StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
//// カテゴリ   ：メンバ関数
//// 用途       ：ステージを構築すします
//// 引数       ：  wstring i_sStageFilePath         //  ステージの構成ファイルへのパス
//// 戻値       ：なし
//// 担当者     ：鴫原 徹
//// 備考       ：StageListLoader関数から呼ばれます
////            ：③
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
//// 備考       ：②
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

		{
		DWORD dwSTime = TLIB::Tempus::TimeGetTime();
		PointSearch( vvCsvData , NumberPoint , PathPoint ) ;
		DWORD dwETime = TLIB::Tempus::TimeGetTime();
		Debugger::DBGWRITINGLOGTEXT::addStr( L"StageLoader::StageListLoader >> PointSearch : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));
		}
		BYTE size = vvCsvData.size();
		DWORD dwETime = TLIB::Tempus::TimeGetTime();

		do{
			if( wcstol( vvCsvData[NumberPoint.y][NumberPoint.x].c_str() , NULL , 10 ) 
				== i_byStageNum )
			{
				DWORD dwSTime = TLIB::Tempus::TimeGetTime();
				StageGenerator(vvCsvData[NumberPoint.y][NumberPoint.x +1]);
				DWORD dwETime = TLIB::Tempus::TimeGetTime();
				Debugger::DBGWRITINGLOGTEXT::addStr( L"StageLoader::StageListLoader >> StageGenerator : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));
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
//// 備考       ：①
////            ：
////
StageLoader::StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,DWORD i_dwStageNum)
:m_pFpac( &i_Fpac )
{
	try{

		//DWORD dwSTime = TLIB::Tempus::TimeGetTime();
			
		StageListLoader(i_sFileName, (BYTE)i_dwStageNum);

		//DWORD dwETime = TLIB::Tempus::TimeGetTime();
		//Debugger::DBGWRITINGLOGTEXT::addStr( L"StageLoader::StageLoader(ロード全体) : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));
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
//// 備考       ：①'
////            ：
////
StageLoader::StageLoader(FactoryPacket& i_Fpac, MapPartsStatus* i_Parts)
:m_pFpac( &i_Fpac )
{
	try{


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


}
//end of namespace wiz.
