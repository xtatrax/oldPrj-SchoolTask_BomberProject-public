////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStageLoader.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�X�e�[�W
//					�F�X�e�[�W�̓V�[������Ă΂�܂�
//					��
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
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �FStageGenerator����
////            �F
////
void StageLoader::PartsGenerator(MapPartsStatus i_Data){
	//	: �I�u�W�F�^�C�v�ɉ������I�u�W�F�N�g�𐶐�����
	//	: �����̍ۤ�]�v�ȃf�[�^�������Ȃ��悤��
	multimap<OBJID,DWORD>::iterator it;


	//	: ���C�h����}���`��
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
			//	: ��
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< WallObject* >(( *m_pVec )[ it->second ])->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: �o�^���Ȃ������ꍇ
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
			//	: �A�C�e��
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< Item* >(( *m_pVec )[it->second])->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				FactoryPacket fpac;
				fpac.m_pTexMgr  = m_pTexMgr		;
				fpac.m_pVec     = m_pVec		;
				fpac.pD3DDevice = m_pD3DDevice	;
				//	: �o�^���Ȃ������ꍇ
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
			//	: �A�C�e��
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< MagneticumObject3D* >(( *m_pVec )[it->second])->AddMagnetic(
					i_Data.vScale, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: �o�^���Ȃ������ꍇ
				MagneticumObject3D* mgb = new MagneticumObject3D( m_pD3DDevice, m_pTexMgr->addTexture(m_pD3DDevice,L"biribiriWall.png"), ObjectID);
				mgb->AddMagnetic(
					i_Data.vScale, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
				m_pVec->push_back(mgb);
				m_ObjeTypeMap.insert( make_pair( ObjectID , m_pVec->size() -1));
			}
			break;
	}
};

/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader::ObjectsLoader(wstring i_sFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�����\�z���܂�
//// ����       �F  wstring i_sFilePath         //
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FCSV����ǂݎ�����������&�C���X�^���X�����܂�
////            �FPointSearch�֐�����Ă΂�܂�
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
	vector<vector<wstring>> vvCsvData;		//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
	if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSV�f�[�^�̎󂯎��
		throw LoaderException(
			L"�I�u�W�F�N�g��`�t�@�C���̃p�X�����������A�f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::ObjectsLoader()"
		);
	}
	CSVMATRIX o_CsvMatrix ;					//	: �e�p�����[�^�̏����Ă������i�[����\����
	PointSearch(vvCsvData, o_CsvMatrix);	//	: �e�p�����[�^�������Ă���s���l��

	//	: i		> ���݂̃Z��
	//	: vvSz	> �ő�̃Z����
	//	: Line	> ��
	D3DCOLORVALUE Diffuse	= {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular	= {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient	= {0.5f,0.5f,0.5f,1.0f};

	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		
		MapPartsStatus Status ;
		//////////
		//	: ���̂ЂƂ����܂�ň�s
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
		Status.vPos.x		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosX				) ;
		Status.vPos.y		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosY				) ;
		Status.vPos.z		= getCsvFloat(	vvCsvData, Line, o_CsvMatrix.Column.uiPosZ				) ;

		Status.Ambient		= Ambient	;
		Status.Specular		= Specular	;
		Status.Diffuse		= Diffuse	;
		//Status.vRot			= g_vZero	;
		//Status.vPos			= g_vZero	;
		//	: ���̂ЂƂ����܂�ň�s
		//////////
		m_ObjeMap[iNumber] = Status;
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
	//readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��
	if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSV�f�[�^�̎󂯎��
		throw LoaderException(
			L"�X�e�[�W��`�t�@�C���̃p�X�����������A�f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::StageGenerator()"
		);

	}
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

				//	: �ǂݍ��݈ʒu�̐ݒ�
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
				
				//	: ���ׂĂ̓ǂݍ��݂�����
				if(SearchFlag == ALL_OK) return ;
			}
			//	: �ꕔ�ǂݍ��߂Ȃ��Ă����Ȃ�!
			if(SearchFlag & IS_OK) return ;
		}
//////////
//
//	�����܂Ŕ��ł�����m���ɓǂݍ��݂����s���Ă���
//

//	: �f�b�o�b�O�p�G���[
//#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader::PointSearch()"
//					);
//#endif

		//	: ��ʌ����G���[
		throw LoaderException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::PointSearch()\nA"
		);
	}
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
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
					throw LoaderException(
						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw LoaderException(
						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: ��ʌ����G���[
		throw LoaderException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::PointSearch()\nB"
		);
	}
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
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
		if( !readcsv(i_sFileName,vvCsvData) ){	//	: CSV�f�[�^�̎󂯎��
			throw LoaderException(
				L"Stages.csv�̃p�X�����������A�f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
				L"StageLoader::StageListLoader()"
			);

		}
		//readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

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
		throw LoaderException(
				L"", 
				L"StageLoader::StageListLoader()"
				);
	}
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
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
//// �p�r       �FFILE����StageLoader���\�z���܂�
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
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader::StageLoader()"
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
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
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
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader::StageLoader()"
				);
	}
	catch(...){
		throw LoaderException(
				L"�}�b�v�f�[�^�z��̍Ō��OBJID_END���w�肵�����m�F���Ă�����", 
				L"��StageLoader::StageLoader()"
				);
		throw;
	}
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
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
void StageLoader2::PartsGenerator(MapPartsStatus i_Data){
	//	: �I�u�W�F�^�C�v�ɉ������I�u�W�F�N�g�𐶐�����
	//	: �����̍ۤ�]�v�ȃf�[�^�������Ȃ��悤��
	multimap<OBJID,DWORD>::iterator it;

	D3DCOLORVALUE Diffuse = {0.7f,0.7f,0.7f,1.0f};
	D3DCOLORVALUE Specular = {0.0f,0.0f,0.0f,0.0f};
	D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,1.0f};


	//	: ���C�h����}���`��
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
			//	: ��
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< WallObject* >(( *m_pVec )[ it->second ])->AddWall(
					i_Data.vScale, i_Data.vRot, i_Data.vPos, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: �o�^���Ȃ������ꍇ
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
			//	: �A�C�e��
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< Item* >(( *m_pVec )[it->second])->addItem(
					i_Data.vPos, i_Data.vScale, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				FactoryPacket fpac;
				fpac.m_pTexMgr  = m_pTexMgr		;
				fpac.m_pVec     = m_pVec		;
				fpac.pD3DDevice = m_pD3DDevice	;
				//	: �o�^���Ȃ������ꍇ
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
			//	: �����z�u���E
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< MagneticumObject3D* >(( *m_pVec )[it->second])->AddMagnetic(
					i_Data.vPos, i_Data.vScale, i_Data.vPos, i_Data.bPool, i_Data.Diffuse, i_Data.Specular, i_Data.Ambient
				);
			}else{
				//	: �o�^���Ȃ������ꍇ
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

				//	: �ǂݍ��݈ʒu�̐ݒ�
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
//					throw LoaderException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader2::PointSearch()"
//					);
//			//	: 
//			if( !(SearchFlag & ( FILE_PATH )) ) 
//					throw LoaderException(
//						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader2::PointSearch()"
//					);
//			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
//					throw LoaderException(
//						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
//						L"StageLoader2::PointSearch()"
//					);
//#endif

		//	: ��ʌ����G���[
		throw LoaderException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader2::PointSearch()"
		);
	}
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader2::PointSearch()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader2::ObjectsLoader(wstring i_sFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�����\�z���܂�
//// ����       �F  wstring i_sFilePath         //
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FCSV����ǂݎ�����������&�C���X�^���X�����܂�
////            �FPointSearch�֐�����Ă΂�܂�
////
void StageLoader2::ObjectsLoader(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
	readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

	CSVMATRIX o_CsvMatrix ;					//	: �e�p�����[�^�̏����Ă������i�[����\����
	PointSearch(vvCsvData, o_CsvMatrix);	//	: �e�p�����[�^�������Ă���s���l��

	//	: i		> ���݂̃Z��
	//	: vvSz	> �ő�̃Z����
	//	: Line	> ��
	for(vector<vector<wstring>>::size_type i = 1 , vvSz = vvCsvData.size() , Line = 0;
		(i + o_CsvMatrix.Line) < vvSz ; i++ )
	{
		
		MapPartsStatus Status ;
		//////////
		//	: ���̂ЂƂ����܂�ň�s
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
		//	: ���̂ЂƂ����܂�ň�s
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
//// �֐���     �Fvoid StageLoader2::StageGenerator(wstring i_sStageFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
////
void StageLoader2::StageGenerator(wstring i_sFileName){
	vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�
	readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

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
//// �֐���     �Fvoid StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
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

				//	: Object���X�g��ǂݍ���
				//if(i_vvCsvData[i][j] == L"ObjectsCSV" ){ ObjectsLoader(i_vvCsvData[i][j+1]); SearchFlag |= OBJECTS_CSV ; }

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
					throw LoaderException(
						L"�t�@�C���p�X�̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
			if( !(SearchFlag & ( STAGE_NUMBER )) ) 
					throw LoaderException(
						L"�X�e�[�W�ԍ��̍s��������܂���ł���\n��CSV�f�[�^���m�F���Ă�������",
						L"StageLoader::PointSearch()"
					);
#endif

		//	: ��ʌ����G���[
		throw LoaderException(
			L"�X�e�[�W�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n���f�[�^���j�����Ă��Ȃ����m�F���Ă�������",
			L"StageLoader::PointSearch()"
		);
	}
	catch(wiz::LoaderException& e){
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader::PointSearch()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F�ǂݍ��ނׂ��X�e�[�W�\���f�[�^���l������
////            �F
////
void StageLoader2::StageListLoader(wstring i_sFileName, BYTE i_byStageNum,vector<wstring>& vsStageConsList){
	try{

		POINT NumberPoint ;		//	: �X�e�[�W�ԍ����������n�߂�s�Ɨ�̃f�[�^
		POINT PathPoint   ;		//	: �X�e�[�W�̍\���f�[�^�t�@�C�����������Ă���s�Ɨ�̃f�[�^

		vector<vector<wstring>> vvCsvData;	//	: CSV�f�[�^���󂯎�邽�߂̕ϐ�

		readcsv(i_sFileName,vvCsvData);		//	: CSV�f�[�^�̎󂯎��

		//	: �X�e�[�W�ԍ��ƍ\���t�@�C���������n�߂�ꏊ���l������
		PointSearch4StageList( vvCsvData , NumberPoint , PathPoint ) ;

		BYTE size = vvCsvData.size();
		do{
			//	: �Ώۂ̃X�e�[�W��T��
			if( wcstol( vvCsvData[NumberPoint.y][NumberPoint.x].c_str() , NULL , 10 ) 
				== i_byStageNum )
			{
				//	: �\���t�@�C���̃��X�g���쐬
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
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader2::StageListLoader()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FFILE����StageLoader���\�z���܂�
//// ����       �F
//// �ߒl       �F�Ȃ�(���s���͗�O��throw)
//// �S����     �F
//// ���l       �F
////            �F
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
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader2::StageLoader2()"
				);
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
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
		//�ăX���[
		throw LoaderException(
				e.what_w(), 
				L"��StageLoader2::StageLoader2()"
				);
	}
	catch(...){
		throw LoaderException(
				L"�}�b�v�f�[�^�z��̍Ō��OBJID_END���w�肵�����m�F���Ă�����", 
				L"��StageLoader2::StageLoader2()"
				);
		throw;
	}
}

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


}
//end of namespace wiz.
