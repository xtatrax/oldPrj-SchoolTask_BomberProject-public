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
#include "Factory_Goal.h"
#include "Factory_Enemy.h"



namespace wiz{
using namespace bomberobject;

/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �FStageGenerator����
////            �F�F
////
void StageLoader::PartsGenerator(MapPartsStatus i_Data){
	//	: �I�u�W�F�^�C�v�ɉ������I�u�W�F�N�g�𐶐�����
	//	: �����̍ۤ�]�v�ȃf�[�^�������Ȃ��悤��
	multimap<OBJID,Object*>::iterator it;


	//	: ���C�h����}���`��
	string sFilePath;
	TLIB::narrow(i_Data.sFilePath, sFilePath);


	switch( (wiz::OBJID)i_Data.enClassid ){

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		//////////
		//
		case CLASSID_NONE:
		default:
			return;
		//
		//////////
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_WALL :	//	: 20
		{
			//////////
			//	: ��

			//	: ���[�����ƁB
			typedef WallObject TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_WALL ;
			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				//	: ���̂܂܃I�u�W�F�N�g��ǉ�
				dynamic_cast< TARGET_CLASS* >( it->second )->AddWall(
					i_Data.vScale		,
					i_Data.vRot			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL���m�ۂ��܂�\n",this);

				//	: �o�^���Ȃ������ꍇ
				WallObject* cp ;

				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID(ObjectID) ){
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> Object�ꗗ��蔭�����܂���\n",this);
					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> Object�ꗗ��蔭���ł��܂���ł��� �V�K�ɍ쐬���܂�\n",this);
					//	: �C���X�^���X�𐶐�
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice(),
						m_pFpac->AddTexture(L"Lightning.png"),
						ObjectID
					);
					//	: �I�u�W�F�N�g���X�g�֓o�^
					m_pFpac->AddObject(cp);

					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp));
				}
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> ����o�^����\n",this);
				//	: �A�C�e���̒ǉ�
				cp->AddWall(
					i_Data.vScale	,
					i_Data.vRot		,
					i_Data.vPos		,
					i_Data.Diffuse	,
					i_Data.Specular	,
					i_Data.Ambient
				);
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_WALL  >>>> ����̒ǉ��s�����������܂�\n",this);
			}
			//	: ��
			//////////
		}
		break;

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_ITEM :	//	: 40
		{
			//////////
			//	: �A�C�e��
			D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
			D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};

			//	: ���[�����ƁB
			typedef Item TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_ITEM ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				//	: ���̂܂܃I�u�W�F�N�g��ǉ�
				dynamic_cast< TARGET_CLASS* >( it->second )->addItem(
					i_Data.vPos			,
					g_vOne				,
					BallDiffuse			,
					BallSpecular		,
					BallAmbient			,
					i_Data.vScale.x
				);
			}else{
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM���m�ۂ��܂�\n",this);
				//	: �o�^���Ȃ������ꍇ
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> Object�ꗗ��蔭�����܂���\n",this);
					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> Object�ꗗ��蔭���ł��܂���ł��� �V�K�ɍ쐬���܂�\n",this);
					//	: �o�^���Ȃ������ꍇ
					//	: �C���X�^���X�𐶐�
					cp  = new Item( m_pFpac, NULL, ObjectID);

					//	: �I�u�W�F�N�g���X�g�֓o�^
					m_pFpac->AddObject(cp);

					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> ����o�^����\n",this);

				//	: �A�C�e���̒ǉ�
				cp->addItem(
					i_Data.vPos			,
					g_vOne				,
					BallDiffuse		,
					BallSpecular		,
					BallAmbient		,
					i_Data.vScale.x
				);
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ITEM  >>>> ����̒ǉ��s�����������܂�\n",this);
			}
			//	: �A�C�e��
			//////////
		}
		break;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_MAGNET :	//	: 30 
		{
			//////////
			//	: ���E

			//	: ���[�����ƁB
			typedef StaticMagnetField TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_STATIC_MAGNET ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< TARGET_CLASS* >( it->second )->AddMagnetic(
					i_Data.vPos			,
					i_Data.bPool		,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient
				);
			}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET���m�ۂ��܂�\n",this);
				//	: �o�^���Ȃ������ꍇ
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID  ) ){
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> Object�ꗗ��蔭�����܂���\n",this);
					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> Object�ꗗ��蔭���ł��܂���ł��� �V�K�ɍ쐬���܂�\n",this);
					//	: �o�^���Ȃ������ꍇ
					//	: �C���X�^���X�𐶐�
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice()	,
						ObjectID
					);

					//	: �I�u�W�F�N�g���X�g�֓o�^
					m_pFpac->AddObject(cp);

					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> ����o�^����\n",this);
				//	: �o�^���Ȃ������ꍇ
				cp->AddMagnetic(
					i_Data.vPos		,
					i_Data.bPool	,
					i_Data.Diffuse	,
					i_Data.Specular	,
					i_Data.Ambient
				);
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_MAGNET  >>>> ����̒ǉ��s�����������܂�\n",this);
			}
			//	: ���E
			//////////
		}
		break;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_ENEMY :	//	: 31
		{
			//////////
			//	: �G(�E�C���X?)

			//	: ���[�����ƁB
			typedef EnemyModel TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_3D_ENEMY ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
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
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY���m�ۂ��܂�\n",this);
				//	: �o�^���Ȃ������ꍇ
				TARGET_CLASS* cp;
				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> Object�ꗗ��蔭�����܂���\n",this);
					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> Object�ꗗ��蔭���ł��܂���ł��� �V�K�ɍ쐬���܂�\n",this);
					//	: �o�^���Ȃ������ꍇ
					D3DCOLORVALUE EnemyDiffuse	= {1.0f,1.0f,1.0f,1.0f};
					D3DCOLORVALUE EnemySpecular	= {1.0f,1.0f,1.0f,1.0f};
					D3DCOLORVALUE EnemyAmbient	= {1.0f,1.0f,1.0f,1.0f};
					//	: �C���X�^���X�𐶐�
					cp = new TARGET_CLASS(
						*m_pFpac,
						RCTEXT_MODEL_ENEMY,
						ObjectID
					);

					//	: �I�u�W�F�N�g���X�g�֓o�^
					m_pFpac->AddObject(cp);

					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> ����o�^����\n",this);
				//	: �o�^���Ȃ������ꍇ
				cp->AddEnemy(
					g_vOne		,
					g_vZero			,
					i_Data.vPos			,
					i_Data.Diffuse		,
					i_Data.Specular		,
					i_Data.Ambient		,
					i_Data.bPool
				);
																			Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_ENEMY  >>>> ����̒ǉ��s�����������܂�\n",this);
			}
			//	: �G(�E�C���X?)
			//////////
		}
		break;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_CHECKPOINT :	//	: 11 
		{
			//////////
			//	: �`�F�b�N�|�C���g

			//	: ���[�����ƁB
			typedef CheckPoint TARGET_CLASS;
			wiz::OBJID ObjectID = OBJID_SYS_CHECKPOINT ;

			if((it = m_ObjeTypeMap.find( ObjectID )) != m_ObjeTypeMap.end()){
				//	: �o�^���������ꍇ
				dynamic_cast< TARGET_CLASS* >( it->second )->add(
					i_Data.vPos
				);
			}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT���m�ۂ��܂�\n",this);
				//	: �o�^���Ȃ������ꍇ
				TARGET_CLASS* cp;

				if( cp = (TARGET_CLASS*)m_pFpac->SearchObjectFromID( ObjectID ) ){
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> Object�ꗗ��蔭�����܂���\n",this);
					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));

				}else{
																Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> Object�ꗗ��蔭���ł��܂���ł��� �V�K�ɍ쐬���܂�\n",this);
					//	: �o�^���Ȃ������ꍇ
					//	: �C���X�^���X�𐶐�
					cp = new TARGET_CLASS(
						m_pFpac->GetDevice()	,
						100.0f			,
						m_pFpac->AddTexture( L"particle.png" ),
						m_pFpac->AddTexture( L"CHECK_POINT1.png" ),
						m_pFpac->AddTexture( L"LAST.png" ),
						ObjectID
					);

					//	: �I�u�W�F�N�g���X�g�֓o�^
					m_pFpac->AddObject(cp);

					//	: �I�u�W�F�N�g�̏ꏊ���o���Ă���
					m_ObjeTypeMap.insert( make_pair( ObjectID , cp ));
				}
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> ����o�^����\n",this);
				//	: �o�^���Ȃ������ꍇ
				cp->add(
					i_Data.vPos
				);
																	Debugger::DBGWRITINGLOGTEXT::addStr(L"StageLoader::PartsGenerator( 0x%X )  >>>>  CLASSID_CHECKPOINT  >>>> ����̒ǉ��s�����������܂�\n",this);
			}
			//	: ���E
			//////////
		}
		break;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		case CLASSID_GOAL :	//:10
			//////////
			//	: �N���A�̈�
			D3DCOLORVALUE MemoryDiffuse = {1.0f,1.0f,1.0f,0.0f};
			D3DCOLORVALUE MemorySpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE MemoryAmbient = {1.0f,1.0f,1.0f,0.0f};

			D3DCOLORVALUE GoalDiffuse = {0.0f,1.0f,1.0f,0.3f};
			D3DCOLORVALUE GoalSpecular = {0.0f,0.0f,0.0f,0.0f};
			D3DCOLORVALUE GoalAmbient = {0.0f,1.0f,1.0f,0.3f};

			wiz::OBJID ObjectID = OBJID_SYS_CLEARAREA ;
			//	: �C���X�^���X�𐶐�
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
			
			//	: �S�[���̒ǉ�
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
			//	: �I�u�W�F�N�g���X�g�֓o�^
			m_pFpac->AddObject( go );
			break;
			//	: �N���A�̈�
			//////////
		}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
};

/////////////////// ////////////////////
//// �֐���     �Fvoid StageLoader::StageGenerator(wstring i_sStageFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F�E
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
//// �֐���     �Fvoid PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring    i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
////            �F CSVMATRIX&  o_CsvMatrix				//	�ǂݍ��ނׂ��s�Ɨ�̋l�ߍ��킹
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F�D
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
//// �֐���     �Fvoid StageLoader::ObjectsLoader(wstring i_sFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�����\�z���܂�
//// ����       �F  wstring i_sFilePath         //
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FCSV����ǂݎ�����������&�C���X�^���X�����܂�
////            �FPointSearch�֐�����Ă΂�܂�
////            �F�C
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
		//	: ���̂ЂƂ����܂�ň�s
		//////////
		m_ObjeMap[iNumber] = Status;
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
////            �F�B
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
//// ���l       �F�A
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
//// ���l       �F�@
////            �F
////
StageLoader::StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,DWORD i_dwStageNum)
:m_pFpac( &i_Fpac )
{
	try{

		//DWORD dwSTime = TLIB::Tempus::TimeGetTime();
			
		StageListLoader(i_sFileName, (BYTE)i_dwStageNum);

		//DWORD dwETime = TLIB::Tempus::TimeGetTime();
		//Debugger::DBGWRITINGLOGTEXT::addStr( L"StageLoader::StageLoader(���[�h�S��) : %f\n", TLIB::Tempus::TwoDwTime2ElapsedTime(dwSTime,dwETime));
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
//// ���l       �F�@'
////            �F
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


}
//end of namespace wiz.
