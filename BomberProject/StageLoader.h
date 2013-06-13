////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStageLoader.h
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
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassMenuItems.h"
#include "CSV.h"

namespace wiz{

// ���錾	
class StageLoader ;
class wiz::menuobject::Button;
using namespace menuobject ;
//class Button2;
//**************************************************************************
// class StageFactory;
//
// �S����  : ���� �O
// �p�r    : �t�@�N�g���[�̍���N���X
//**************************************************************************/
class StageFactory{
protected:
	bool m_ONNowLoading ;
public:
	StageFactory():m_ONNowLoading(false){}
	virtual StageLoader* StageCreate( const FactoryPacket fPack ) = 0;

};

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************
// class StageLoader;
//
// �S����  : ���� �O
// �p�r    : CSV�f�[�^����X�e�[�W���\�z���܂�
//**************************************************************************
class StageLoader{
	struct CSVMATRIX {
		//	: �s
		UINT Line ;
		//	: ��
		struct ___ST{
			UINT	uiNumber			;	//	�ԍ�
			UINT	uiType				;	//	���
			UINT	uiPath				;	//	FILE
			UINT	uiTexPath			;	//	�e�N�X�`��
			UINT	uiMotionNum			;	//	���[�V����
			UINT	uiTracSpeed			;	//	���[�V�����̑���
			UINT	uiScaleX			;	//	X�L�k
			UINT	uiScaleY			;	//	Y�L�k
			UINT	uiScaleZ			;	//	Z�L�k
			UINT	uiRotX				;	//	X��]
			UINT	uiRotY				;	//	Y��]
			UINT	uiRotZ				;	//	Z��]
			UINT	uiPosX				;	//	X�ړ�
			UINT	uiPosY				;	//	Y�ړ�
			UINT	uiPosZ				;	//	Z�ړ�
			UINT	uiPool				;	//	Z�ړ�
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
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void PartsGenerator(MapPartsStatus i_Data);
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S����		�F���� �O
//// ���l       �F
////            �F
////
	void D2(MapPartsStatus i_Data);
/////////////////// ////////////////////
//// �֐���     �Fvoid ObjectsLoader(wstring i_sFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�I�u�W�F�N�g�����\�z���܂�
//// ����       �F  wstring i_sFilePath         //
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FPointSearch�֐�����Ă΂�܂�
////            �F
////
	void ObjectsLoader(wstring i_sFilePath);
/////////////////// ////////////////////
//// �֐���     �Fvoid StageGenerator(wstring i_sStageFilePath)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
////
	void StageGenerator(wstring i_sStageFilePath);
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
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);
/////////////////// ////////////////////
//// �֐���     �Fvoid PointSearch( vector<vector<wstring>>& i_vvCsvData ,
////            �F    POINT& o_NumberPoint , POINT& o_PathPoint)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�X�e�[�W���\�z�����܂�
//// ����       �F  wstring i_sStageFilePath         //  �X�e�[�W�̍\���t�@�C���ւ̃p�X
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FStageListLoader�֐�����Ă΂�܂�
////            �F
////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, POINT& o_NumberPoint, POINT& o_PathPoint);
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
	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum);
public:
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
	StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr);

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
	StageLoader(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus[]);
}; // StageLoader
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************
// class StageLoader2;
//
// �S����  : ���� �O
// �p�r    : CSV�f�[�^����X�e�[�W���\�z���܂�
//**************************************************************************
class StageLoader2{
	struct CSVMATRIX {
		//	: �s
		UINT Line ;
		//	: ��
		struct {
			UINT	uiClassid			;	//	�ԍ�
			UINT	uiPosX				;	//	���
			UINT	uiPosY				;	//	FILE
			UINT	uiPosZ				;	//	FILE
			UINT	uiScaleX			;	//	�e�N�X�`��
			UINT	uiScaleY			;	//	���[�V����
			UINT	uiScaleZ			;	//	���[�V����
			UINT	uiRotX				;	//	���[�V�����̑���
			UINT	uiRotY				;	//	���[�V�����̑���
			UINT	uiRotZ				;	//	���[�V�����̑���
			UINT	uiColor				;	//	X�L�k
		}Column;
	};
	map<UINT,MapPartsStatus>		m_ObjeMap;
	multimap<wiz::OBJID,DWORD>		m_ObjeTypeMap;

	TextureManager*		m_pTexMgr;
	vector<Object*>*	m_pVec;
	LPDIRECT3DDEVICE9	m_pD3DDevice;


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

	void PartsGenerator(MapPartsStatus i_Data);


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
	
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);


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

	void ObjectsLoader(wstring i_sFileName);


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

	void StageGenerator(wstring i_sFileName);


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

	void PointSearch4StageList( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint);


/////////////////// ////////////////////
//// �֐���     �FStageListLoader()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FStages.csv����͂���
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F�R���X�g���N�^����Ă΂��
////            �F
////

	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum,vector<wstring>& vsStageConsList);


public:
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

	StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, wstring i_sFileName,
		BYTE i_byStageNum, vector<Object*>& Vec, TextureManager& TexMgr);


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

	StageLoader2(LPDIRECT3DDEVICE9 pD3DDevice, vector<Object*>& Vec, TextureManager& TexMgr, MapPartsStatus[]);


}; // StageLoader2
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



}
//end of namespace wiz.
