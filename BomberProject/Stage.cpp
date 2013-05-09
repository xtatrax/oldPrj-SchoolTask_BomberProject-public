////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�X�e�[�W
//					�F�X�e�[�W�̓V�[������Ă΂�܂�
//					��
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



namespace wiz{
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �FStageGenerator����
////            �F
////
void StageLoader::PartsGenerator(ObjeData i_Data, DWORD i_dwHeight, DWORD i_dwWidth){
	//	: �I�u�W�F�^�C�v�ɉ������I�u�W�F�N�g�𐶐�����
	//	: �����̍ۤ�]�v�ȃf�[�^�������Ȃ��悤��
	multimap<OBJID,DWORD>::iterator it;

	D3DCOLORVALUE Diffuse = {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,1.0f};

	//	: ���C�h����}���`��
	string sFilePath;
	TLIB::narrow(i_Data.m_sFilePath, sFilePath);
	// Motion* pMotion = NULL ;
	wiz::OBJID ObjectID ;
	switch(i_Data.m_iObjeType){
		//////////
		//
		case GP_CREATE_NONE:
		default:
			return;
		//
		//////////
		case GP_CREATE_WALL:
			//////////
			//	: ��
			if((it = m_ObjeTypeMap.find(OBJID_2D_WALL)) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast<WallObject*>((*m_pVec)[it->second])->AddWall(
					D3DXVECTOR3(MAP_PARTS_WIDTH,MAP_PARTS_HEIGHT,5.0f),
					g_vZero,
					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
								0.0f),
					Diffuse,
					Specular,
					Ambient
				);
			}else{
				//	: �o�^���Ȃ������ꍇ
				WallObject* mgb = new WallObject(m_pD3DDevice,m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"),OBJID_3D_TESTBOX);
				mgb->AddWall(
					 D3DXVECTOR3(MAP_PARTS_WIDTH, MAP_PARTS_HEIGHT, 5.0f)
					,g_vZero
					,D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
								0.0f)
					,Diffuse
					,Specular
					,Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( OBJID_3D_TESTBOX , m_pVec->size() -1));
			}
			break;

		//case 

//		case GP_CREATE_TESTTIP:
//			//////////
//			//	: �e�X�g�`�b�v
//			if((it = m_ObjeTypeMap.find(OBJID_3D_TESTBOX)) != m_ObjeTypeMap.end()){
//				//	: �o�^���������ꍇ
//				dynamic_cast<MultiGround*>((*m_pVec)[it->second])->Add(
//					D3DXVECTOR3(MAP_PARTS_WIDTH,MAP_PARTS_HEIGHT,5.0f),
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f)
//				);
//			}else{
//				//	: �o�^���Ȃ������ꍇ
//				MultiGround* mgb = new MultiGround(m_pD3DDevice,const_cast<char*>(sFilePath.c_str()),*m_pTexMgr,OBJID_3D_TESTBOX);
//				mgb->Add(
//					D3DXVECTOR3(MAP_PARTS_WIDTH, MAP_PARTS_HEIGHT, 5.0f),
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f)
//				);
//				m_pVec->push_back(mgb);
//				m_ObjeTypeMap.insert( make_pair( OBJID_3D_TESTBOX , m_pVec->size() -1));
//			}
//			break;
//			//
//			//////////
//		case GP_CREATE_FRONTPANEL:
//		case GP_CREATE_GROUND:
//			//////////
//			//	: �n��
//			{
//			bool Generate = false;
//
//			//	: �o�^���������邩
//			DWORD HitQty = m_ObjeTypeMap.count(OBJID_3D_GROUND_FLAT);
//			if( HitQty > 0 ){
//				//	: �o�^��������
//
//				//	: �o�^�t�B���h�C�e���[�^�����炤
//				it = m_ObjeTypeMap.find(OBJID_3D_GROUND_FLAT);
//				for(DWORD i = 0; i < HitQty ;i++){
//					MultiGround* pGround = dynamic_cast<MultiGround*>((*m_pVec)[it->second]) ;
//					if( pGround && pGround->CheckSame(sFilePath) ){
//						pGround->Add(
//							i_Data.m_vScale,
//							g_vZero,
//							D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//										(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//										0.0f),
//							m_pD3DDevice,
//							m_pTexMgr,
//							i_Data.m_sTexturePath.c_str()
//
//						);
//						return;
//					}
//					it++;
//				}
//				Generate = true ;
//			}else
//				Generate = true;
//			if(Generate){
//				//	: �o�^���Ȃ������ꍇ
//				MultiGround* mgb = new MultiGround(m_pD3DDevice,const_cast<char*>(sFilePath.c_str()),*m_pTexMgr,OBJID_3D_GROUND_FLAT);
//				mgb->Add(
//					i_Data.m_vScale,
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f),
//					m_pD3DDevice,
//					m_pTexMgr,
//					i_Data.m_sTexturePath.c_str()
//				);
//				m_pVec->push_back(mgb);
//				DWORD dwVecQty = m_pVec->size() ;
//				m_ObjeTypeMap.insert( make_pair( OBJID_3D_GROUND_FLAT, dwVecQty -1 ));
//			}
//			}
//			break;
//			//
//			//////////
//
//		//////////
//		//	: �G/�M�~�b�N
//		case GP_CREATE_ENEMY:
//			pMotion = new AborigineWalkMotion() ;
//			ObjectID = OBJID_3D_ABORIGINE ;
//			goto GOTO_SL_ENEMY_CREATE_LABEL ;
//		case GP_CREATE_ARROW:
//			pMotion = new JavelinMotion() ;
//			ObjectID = OBJID_3D_ARROW ;
//			goto GOTO_SL_ENEMY_CREATE_LABEL ;
//
//		case GP_CREATE_BIRD:
//			ObjectID = OBJID_3D_BIRD ;
//			pMotion = new BirdFlyMotion() ;
//GOTO_SL_ENEMY_CREATE_LABEL :
//			if((it = m_ObjeTypeMap.find(ObjectID)) != m_ObjeTypeMap.end()){
//				//	: �o�^���������ꍇ
//				dynamic_cast<AnimationEnemy*>((*m_pVec)[it->second])->Add(
//					1.5f,
//					i_Data.m_vScale,
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f),
//					pMotion
//				);
//			}else{
//				//	: �o�^���Ȃ������ꍇ
//				AnimationEnemy* mgb = new AnimationEnemy(m_pD3DDevice,const_cast<char*>(sFilePath.c_str()),g_vOne,g_vZero,g_vZero,0,1,1,OBJID_3D_ABORIGINE);
//				mgb->Add(
//					1.5f,
//					i_Data.m_vScale,
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f),
//					pMotion
//				);
//				m_pVec->push_back(mgb);
//				m_ObjeTypeMap.insert( make_pair( ObjectID, m_pVec->size() -1 ));
//			}
//			 break;
//		//
//		//////////
//
//		case GP_CREATE_CLEAR:
//			{
//			if((it = m_ObjeTypeMap.find(OBJID_SYS_CLEARAREA)) != m_ObjeTypeMap.end() ){
//				//	: �o�^���������ꍇ
//				dynamic_cast<ClearBox*>((*m_pVec)[it->second])->Add(
//					i_Data.m_vScale,
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f)
//				);
//			}else{
//				//	: �o�^���Ȃ������ꍇ
//				ClearBox* mgb = new ClearBox(m_pD3DDevice,const_cast<char*>(sFilePath.c_str()),*m_pTexMgr,OBJID_3D_GROUND_FLAT);
//				mgb->Add(
//					i_Data.m_vScale,
//					g_vZero,
//					D3DXVECTOR3((MAP_PARTS_WIDTH	*	i_dwWidth	)	-	MAP_PARTS_WIDTH		/	2,
//								(MAP_PARTS_HEIGHT	*	i_dwHeight	)	-	MAP_PARTS_HEIGHT	/	2,
//								0.0f)
//				);
//				m_pVec->push_back(mgb);
//				m_ObjeTypeMap.insert( make_pair( OBJID_SYS_CLEARAREA, m_pVec->size() -1 ));
//			}
//			}
//			break;
	}

};

/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader::ObjectsLoader(wstring i_sFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�����\�z���܂�
//// ����       �F  wstring i_sFilePath         //
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FPointSearch�֐�����Ă΂�܂�
////            �F
////
void StageLoader::ObjectsLoader(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
	readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

	CSVMATRIX o_CsvMatrix ;
	PointSearch(vvCsvData, o_CsvMatrix);

	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		Line = o_CsvMatrix.Line + i ;
		int		iNumber		=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiNumber    ].c_str(), NULL  , 10);
		int		iType		=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiType      ].c_str(), NULL  , 10);
		DWORD	dwAniNum	=        wcstol( vvCsvData[ Line ][ o_CsvMatrix.Column.uiMotionNum ].c_str(), NULL  , 10);
		float	fTracSpd	= (float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiTracSpeed ].c_str(), NULL );
		wstring sPath		= vvCsvData[ Line ][ o_CsvMatrix.Column.uiPath    ] ;
		wstring sTexPath	= vvCsvData[ Line ][ o_CsvMatrix.Column.uiTexPath ] ;
		D3DXVECTOR3 vScale	= D3DXVECTOR3(
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleX ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleY ].c_str(), NULL),
			(float)wcstod( vvCsvData[ Line ][ o_CsvMatrix.Column.uiScaleZ ].c_str(), NULL)
		);
		m_ObjeMap[iNumber] = ObjeData(iType,sPath,sTexPath,vScale,dwAniNum,fTracSpd);
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader::StageGenerator(wstring i_sStageFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
////
void StageLoader::StageGenerator(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
	readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

	for(UINT i = 0 , isz = vvCsvData.size() ; i < isz ; i++ ){
		for(UINT j = 0 , jsz = vvCsvData[i].size() ; j < jsz ; j++ ){
			UINT PartsType = wcstol( vvCsvData[i][j].c_str() , NULL , 10 ) ;
			if( m_ObjeMap.count( PartsType ) ){
				PartsGenerator(m_ObjeMap[ PartsType ], isz-i, j);
			}
		}
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring    i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
////            �F CSVMATRIX&  o_CsvMatrix				//	�ǂݍ��ނׂ��s�Ɨ�̋l�ߍ��킹
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
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

				//	: �ǂݍ��݈ʒu�̐ݒ�
				if(i_vvCsvData[i][j] == L"Number"	){ o_CsvMatrix.Column.uiNumber		= j ; SearchFlag |= STAGE_NUMBER ; o_CsvMatrix.Line = i ; }
				if(i_vvCsvData[i][j] == L"Type"		){ o_CsvMatrix.Column.uiType		= j ; SearchFlag |= OBJECT_TYPE  ; }
				if(i_vvCsvData[i][j] == L"Path"		){ o_CsvMatrix.Column.uiPath		= j ; SearchFlag |= FILE_PATH    ; }
				if(i_vvCsvData[i][j] == L"TexPath"	){ o_CsvMatrix.Column.uiTexPath		= j ; SearchFlag |= TEX_PATH     ; }
				if(i_vvCsvData[i][j] == L"MotionNum"){ o_CsvMatrix.Column.uiMotionNum	= j ; SearchFlag |= MOTION_NUM   ; }
				if(i_vvCsvData[i][j] == L"TracSpeed"){ o_CsvMatrix.Column.uiTracSpeed	= j ; SearchFlag |= TRAC_SPEED   ; }
				if(i_vvCsvData[i][j] == L"ScaleX"	){ o_CsvMatrix.Column.uiScaleX		= j ; SearchFlag |= SCALE_X      ; }
				if(i_vvCsvData[i][j] == L"ScaleY"	){ o_CsvMatrix.Column.uiScaleY		= j ; SearchFlag |= SCALE_Y      ; }
				if(i_vvCsvData[i][j] == L"ScaleZ"	){ o_CsvMatrix.Column.uiScaleZ		= j ; SearchFlag |= SCALE_Z      ; }
				
				//	: ���ׂĂ̓ǂݍ��݂�����
				if(SearchFlag == ALL_OK) return ;
			}
			//	: �ꕔ�ǂݍ��߂Ȃ��Ă����Ȃ�!
			if(SearchFlag == IS_OK) return ;
		}
//////////
//
//	�����܂Ŕ��ł�����m���ɓǂݍ��݂����s���Ă���
//

//	: �f�b�o�b�O�p�G���[
//#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw BaseException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw BaseException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//#endif

		//	: ��ʌ����G���[
		throw BaseException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��StageLoader::PointSearch()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
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

				//	: Object���X�g��ǂݍ���
				if(i_vvCsvData[i][j] == L"ObjectsCSV" ){ ObjectsLoader(i_vvCsvData[i][j+1]); SearchFlag |= OBJECTS_CSV ; }

				//	: �ǂݍ��݈ʒu�̐ݒ�
				if(i_vvCsvData[i][j] == L"StageNumber"){ o_NumberPoint.x = j ; o_NumberPoint.y = i ; SearchFlag |= STAGE_NUMBER ; }
				if(i_vvCsvData[i][j] == L"FilePath"   ){ o_PathPoint.x   = j ; o_PathPoint.y   = i ; SearchFlag |= FILE_PATH    ; }

				//	: ���ׂĂ̓ǂݍ��݂�����
				if(SearchFlag == ALL_OK) return ;
			}
		}
//////////
//
//	�����܂Ŕ��ł�����m���ɓǂݍ��݂����s���Ă���
//

//	: �f�b�o�b�O�p�G���[
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
			//	: 
			if( !(SearchFlag & ( FILE_PATH )) ) 
					throw BaseException(
						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw BaseException(
						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: ��ʌ����G���[
		throw BaseException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::BaseException& e){
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��StageLoader::PointSearch()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
void StageLoader::StageListLoader(wstring i_sFileName, BYTE i_byStageNum){
	try{

		vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
		readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

		POINT NumberPoint ;		//	: �X�e�[�W�ԍ��������Ă���s�Ɨ�̃f�[�^
		POINT PathPoint   ;		//	: �X�e�[�W�̍\���f�[�^�t�@�C�����������Ă���s�Ɨ�̃f�[�^
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
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��StageLoader::StageListLoader()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FFILE����Stage���\�z���܂�
//// ����       �F
//// �ߒl       �F�Ȃ�(���s���͗�O��throw)
//// �S����     �F
//// ���l       �F
////            �F
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
		//�ăX���[
		throw BaseException(
				e.what_w(), 
				L"��StageLoader::StageLoader()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 Stage ��`��
****************************************************************************/
/**************************************************************************
 void Stage::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Stage::Clear(){
	SafeDelete(m_pChildStage);
	//SafeDelete(m_pParStage);
	SAFE_DELETE_VECTOR(m_Vec);
	m_TexMgr.Release();
}

/**************************************************************************
 Stage::Stage(
 Stage* Par	//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
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
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Stage::~Stage(){
	Clear();
}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
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
	//�z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->AccessBegin();
		m_Vec[i]->Update(i_UpdatePacket) ;
		if(m_Vec[i]->getDead()){
			//vector<Object*>
			//SAFE_DELETE(*(m_Vec.begin() + i)) ;
			//m_Vec.erase( i-- ) ;
		}
		m_Vec[i]->AccessEnd();
	}
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Render(RenderPacket& i_RenderPacket);
//// �J�e�S��   �F�֐�
//// �p�r       �F�^�[�Q�b�g�����_�����O
//// ����       �F  RenderPacket& i_RenderPacket        // �����_�[�����ɗ����f�[�^�̏W����
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
////            �F
////
void Stage::Render(RenderPacket& i_RenderPacket){
	i_RenderPacket.pVec = &m_Vec ;
	//�z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->AccessBegin();
		m_Vec[i]->TargetRender(i_RenderPacket);
		m_Vec[i]->AccessEnd();
	}
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Stage::Draw(DrawPacket& i_DrawPacket)
{
	i_DrawPacket.pVec = &m_Vec ;
	//�z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->AccessBegin();
		m_Vec[i]->Draw(i_DrawPacket);
		m_Vec[i]->AccessEnd();
	}
}
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
void Stage::TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget){

}

/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
void Stage::DefaultRender(){

}

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/**************************************************************************
 MenuStage ��`��
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par),m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false){
	m_pChildStage = 0;
	try{
        // ���C�e�B���O���[�h
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //���C�g�̃C���X�^���X������
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
        //�J�����̃C���X�^���X������
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
		//�e�N���X��Clear()���Ă�
		Clear();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MenuStage::~MenuStage(){
	//�{�^���z��̂݃N���A����
	//�z�u����Ă�|�C���^�̍폜�͍s�Ȃ�Ȃ�
	m_ButtonVec.clear();
}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MenuStage::Update(UpdatePacket& i_UpdatePacket)
{
	if( i_UpdatePacket.pTxMgr == NULL ) i_UpdatePacket.pTxMgr = &m_TexMgr ;
	CONTROLER_STATE	ControllerState1P = i_UpdatePacket.pCntlState[0];
    if(!m_SelectLock){
		//	: ���̃{�^����
		if(ControllerState1P.Gamepad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN 
			|| ControllerState1P.Gamepad.sThumbLY < 0){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: �O�̃{�^����
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
		//�I����Ԃ̐ݒ�
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//�I�������肳�ꂽ
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
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MenuStage::Draw(DrawPacket& i_DrawPacket){
	Stage::Draw(i_DrawPacket);
}

}
//end of namespace wiz.
