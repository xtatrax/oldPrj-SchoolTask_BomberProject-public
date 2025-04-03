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
using namespace menuobject ;
//class Button2;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 struct MapPartsStatus;
 �p�r: 
****************************************************************************/
struct MapPartsStatus{
	DWORD			enClassid ;	//	wiz::CLASSID�Ŏw�肵�Ă�������
	D3DXVECTOR3		vScale    ;
	D3DXVECTOR3		vRot      ;
	D3DXVECTOR3		vPos      ;
	D3DXVECTOR3		vOffset   ;
	D3DCOLORVALUE   Diffuse   ;
	D3DCOLORVALUE   Specular  ;
	D3DCOLORVALUE   Ambient   ;
	POLE			bPool     ;

	//	: �I�v�V����
	wstring			sTexturePath	;

	wstring			sFilePath		;
	DWORD			dwMotionNum		;
	float			fTracSpeed		;

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

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
	//	: CSV����ǂݎ����Data���Ƃ肠�����ۑ����Ă���
	map<UINT,MapPartsStatus>			m_ObjeMap;
	//	: 
	multimap<wiz::OBJID,Object*>		m_ObjeTypeMap;

	FactoryPacket*		m_pFpac;
	/////////////////// ////////////////////
	//// �֐���     �Fvoid StageLoader::PartsGenerator(MapPartsStatus i_Data)
	//// �J�e�S��   �F�W�F�l���[�^
	//// �p�r       �F�t�@�C������ǂݎ�������f�[�^�����ɃI�u�W�F�N�g�����\�z���܂�
	//// ����       �F  MapPartsStatus   i_Data    //  : �t�@�C������ǂ݂Ƃ��p�[�c�̏��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �FStageGenerator����
	////            �F�F
	////
	void PartsGenerator(MapPartsStatus i_Data);
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
	////            �F�D
	////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, CSVMATRIX& o_CsvMatrix);
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
	void ObjectsLoader(wstring i_sFilePath);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid StageLoader::PointSearch( vector<vector<wstring>>& i_vvCsvData , POINT& o_NumberPoint , POINT& o_PathPoint)
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�X�e�[�W���\�z�����܂�
	//// ����       �F  vector<vector<wstring>>&  i_vvCsvData    //  :  [IN]CSV����ǂݎ�����i�}�̃f�[�^
	////            �F  POINT&                    o_NumberPoint  //  : [OUT]
	////            �F  POINT&                    o_PathPoint    //  : [OUT]
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �FStageListLoader�֐�����Ă΂�܂�
	////            �F�B
	////
	void PointSearch( vector<vector<wstring>>& i_vvCsvData, POINT& o_NumberPoint, POINT& o_PathPoint);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid StageLoader::StageListLoader(wstring i_sFileName, BYTE i_byStageNum)
	//// �J�e�S��   �F���[�_�[
	//// �p�r       �F�X�e�[�W���X�g��ǂݍ���
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F�A
	////            �F
	////
	void StageListLoader(wstring i_sFileName, BYTE i_byStageNum);
public:
	/////////////////// ////////////////////
	//// �֐���     �FStageLoader::StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,DWORD i_dwStageNum)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FFILE����StageLoader���\�z���܂�
	//// ����       �F
	//// �ߒl       �F�Ȃ�(���s���͗�O��throw)
	//// �S����     �F���� �O
	//// ���l       �F�@
	////            �F
	////
	StageLoader(FactoryPacket& i_Fpac, wstring i_sFileName,
		DWORD i_dwStageNum);

	/////////////////// ////////////////////
	//// �֐���     �FStageLoader::StageLoader(FactoryPacket& i_Fpac, MapPartsStatus* i_Parts)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F�@'
	////            �F
	////
	StageLoader(FactoryPacket& i_Fpac, MapPartsStatus[]);
}; // StageLoader
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/





}
//end of namespace wiz.
