////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage.h
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
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassMenuItems.h"
#include "CSV.h"

namespace wiz{

// ���錾	
class Stage ;
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
	virtual Stage* StageCreate( const FactoryPacket fPack ) = 0;

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
		struct {
			UINT	uiNumber			;	//	�ԍ�
			UINT	uiType				;	//	���
			UINT	uiPath				;	//	FILE
			UINT	uiTexPath			;	//	�e�N�X�`��
			UINT	uiMotionNum			;	//	���[�V����
			UINT	uiTracSpeed			;	//	���[�V�����̑���
			UINT	uiScaleX			;	//	X�L�k
			UINT	uiScaleY			;	//	Y�L�k
			UINT	uiScaleZ			;	//	Z�L�k
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



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Stage;
 �p�r: �Q�[�����X�e�[�W�P�ʂŊǗ�����N���X
****************************************************************************/
class Stage{
protected:
	//	: ���j���[���̉�ʂւ̃|�C���^���Ƃ��Ă���
	Stage* m_pParStage;		//�e�X�e�[�W
	Stage* m_pChildStage;	//�q�X�e�[�W

	//�_�C�A���O�X�e�[�W���ǂ���
	bool m_IsDialog;
	bool m_bUpdate;
    //�z�u�I�u�W�F�N�g�̃|�C���^�̃x�N�g��
    vector<Object*> m_Vec;
    //�e�N�X�`���̃|�C���^�̃x�N�g��
    TextureManager m_TexMgr;
#if defined(DEBUG) | defined(_DEBUG) | defined(ON_DEBUGGINGPROCESS)
	bool m_bSlow;
#endif
/////////////////// ////////////////////
//// �֐���     �Fvoid Clear()
//// �J�e�S��   �F�֐�
//// �p�r       �F����f�[�^��j������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F�f�X�g���N�^�Ő�ΌĂ΂�܂�
////            �F
////
	void Clear();
public:
/////////////////// ////////////////////
//// �֐���     �FStage(Stage* Par = NULL)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�f�t�H���g�̍\�z����
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
	Stage(Stage* Par = NULL);
/**************************************************************************
virtual ~Stage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Stage();
/////////////////// ////////////////////
//// �֐���     �Fconst Stage* getNextStage() 
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���̃X�e�[�W���\�z����
//// ����       �F
//// �ߒl       �F
//// �S����     �F
//// ���l       �F
////            �F
////
	const Stage* getNextStage() {
		return m_pParStage;
	}
/**************************************************************************
Stage* getPar();
 �p�r: �e�X�e�[�W�𓾂�
 �߂�l: �e�X�e�[�W�̃|�C���^
***************************************************************************/
	const Stage* getPar() const{
		return m_pParStage;
	}
/**************************************************************************
Stage* geChild();
 �p�r: �q�X�e�[�W�𓾂�
 �߂�l: �q�X�e�[�W�̃|�C���^
***************************************************************************/
	Stage* geChild(){
		return m_pChildStage;
	}
/**************************************************************************
Stage* getLastStage();
 �p�r: ��ԍŌ���̎q�X�e�[�W�𓾂�
 �߂�l: ��ԍŌ���̎q�X�e�[�W�̃|�C���^
***************************************************************************/
	Stage* getLastStage(){
		if(m_pChildStage){
			return m_pChildStage->getLastStage();
		}
		else{
			return this;
		}
	}
/**************************************************************************
Stage* getActiveStage();
 �p�r: ���A�A�N�e�B�u�ȃX�e�[�W�𓾂�
 �߂�l: �A�N�e�B�u�ȃX�e�[�W�̃|�C���^
 ���Ō���̎q���_�C�A���O�^�C�v�������ꍇ
 �@���̃_�C�A���O��ێ�����X�e�[�W�𓾂�
***************************************************************************/
	Stage* getActiveStage(){
		Stage* ret = getLastStage();
		while(ret->m_IsDialog){
			ret = ret->m_pParStage;
		}
		return ret;
	}
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState	//�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void Update(UpdatePacket& i_UpdatePacket);
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
    void Render(RenderPacket& i_RenderPacket);
	
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket) ;
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
	void TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget);
/////////////////// ////////////////////
//// �p�r       �F
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
	void DefaultRender();

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class MenuStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class MenuStage : public Stage{
protected:
	vector<Button*> m_ButtonVec;
	//�{�^���I�u�W�F�N�g�݂̂̔z��i�J�����Ȃǂ͓���Ȃ��j
	vector<Button*>::size_type m_SelectIndex;
	bool m_SelectLock;
	bool m_IsAnimetion;
/**************************************************************************
 void AddButton(
 Button* pButton	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
 �߂�l: �Ȃ�
***************************************************************************/
	void AddButton(Object* pButton);
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MenuStage();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState	//�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,  //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class MenuStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class MenuStage2 : public Stage{
protected:
	vector<Button*> m_Button2Vec;
	//�{�^���I�u�W�F�N�g�݂̂̔z��i�J�����Ȃǂ͓���Ȃ��j
	vector<Button*>::size_type m_SelectIndex;
	bool m_SelectLock;
	bool m_IsAnimetion;
/**************************************************************************
 void AddButton2(
 Button2* pButton2	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
 �߂�l: �Ȃ�
***************************************************************************/
	void AddButton2(Object* pButton2);
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	MenuStage2(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MenuStage2();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,	//�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace wiz.
