////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStructs.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�����ŗ��p�����\���̌S
//					��
//	namespace wiz;
//		struct Command			;
//		struct UpdatePacket		;
//		struct RenderPacket		;
//		struct FactoryPacket	;
//		struct Color			;
//		struct FlexibleVertex	;
//		struct OBB				;
//		struct AABB				;
//		struct Sphere			;
//		struct RENDERSTATE_PARAM	;
//		struct MapPartsStatus			;
//
#pragma once

#include "StdAfx.h"
#include "TextureManager.h"

//#include "DxDevice.h"
namespace wiz{
class  Object ; 
class  Stage ;
class  TextureManager ;
class  StageLoader;
struct CONTROLER_STATE;
class  DxDevice;
namespace system{
class  Sound ;
}
namespace functions {
extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
}
using namespace functions ;
namespace structs{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 struct SaveData : public TLIB::BassSaveaPacketDat;
 �p�r: �Z�[�u�f�[�^
****************************************************************************/
struct SaveData : public TLIB::BassSaveaPacketDat{
private:
	float fDataStructVer ;
public:
	DWORD dwStageNum	;
	DWORD dwCheckPoint	;
	DWORD dwDeadNum		;
	
	SaveData()
	:TLIB::BassSaveaPacketDat(RCVAL_SAVEDATA_IDENTIFIER_H,RCVAL_SAVEDATA_IDENTIFIER_L)
	,fDataStructVer( 0.1f )
	,dwStageNum(0)
	,dwCheckPoint(0)
	,dwDeadNum(0)
	{
		
	}

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 struct Command;
 �p�r: �V�[�����A�X�e�[�W���ł���肳���R�}���h
 ���R�}���h���e�̒�`�́A�e�R���e���c�ɂ܂�����
****************************************************************************/
struct Command{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	DWORD m_Param3;

	Command(DWORD Command = 0, DWORD m_Param1 = 0, DWORD m_Param2 = 0, DWORD m_Param3 = 0)
		:m_Command(Command),m_Param1(m_Param1),m_Param2(m_Param2),m_Param3(m_Param3)

	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = m_Param3 = 0;
	}
	~Command(){
		Clear();
	}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Context;
 �p�r: �V�[���f�[�^�\����
 ���[�U�[�f�[�^�͔h���N���X���쐬���Ďg�p����
****************************************************************************/
class Context{
	DWORD m_Command;	
	DWORD m_Param1;
	DWORD m_Param2;
	//�^�C�}�[�B�o�ߕb���v��
	Avoidance::Timer m_Timer;
	//1��̃^�C���X�p��
	FLOAT m_TimeSpan;
	//�Q�[���g�[�^������
	FLOAT m_TotalTime;
public:
/**************************************************************************
 void ElapsedTime();
 �p�r: �^�C�}�[��i�߂�
 �߂�l: �Ȃ�
***************************************************************************/
	void ElapsedTime(){
		if(m_Timer.IsStopped()){
			//�^�C�}�[���~�܂��Ă����瓮����
			m_Timer.Start();
		}
		else{
			//�^�C�}�[��i�߂�
			m_TimeSpan = m_Timer.GetElapsedTime();
			m_TotalTime += m_TimeSpan;
		}
	}
/**************************************************************************
 FLOAT GetTimeSpan();
 �p�r: �^�C���X�p���𓾂�B
 �߂�l: �^�C���X�p��
***************************************************************************/
	FLOAT GetTimeSpan(){
		return m_TimeSpan;
	}
/**************************************************************************
 FLOAT GetTotalTime();
 �p�r: �g�[�^�����Ԃ𓾂�B
 �߂�l: �g�[�^������
***************************************************************************/
	FLOAT GetTotalTime(){
		return m_TotalTime;
	}
/**************************************************************************
 void StopTimer();
 �p�r: �^�C�}�[���Ƃ߂�
 �߂�l: �Ȃ�
***************************************************************************/
	void StopTimer(){
		if(!m_Timer.IsStopped()){
			m_Timer.Stop();
		}
	}
/**************************************************************************
 Context();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Context():m_Timer(),
		m_TimeSpan(0.001f),m_TotalTime(0){
		m_Timer.Start();
	}
/**************************************************************************
 virtual ~Context();
 �p�r: ���z�f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual~Context(){}

	void operator = ( const Command other ) {
		m_Command = other.m_Command ;
		m_Param1  = other.m_Param1  ;
		m_Param2  = other.m_Param2  ;	
	};

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct UpdatePacket;
//
// �S����  : ���� �O
// �p�r    : �A�b�v�f�[�g�֐��S�ɗ����f�[�^
//**************************************************************************//
struct BassPacket{
	friend class  DxDevice ;
	friend class  wiz::Stage ;
//////////
//	: �v���e�N�g�ϐ�
protected:
	wiz::Stage*				m_pStage		;
	LPDIRECT3DDEVICE9		m_pD3DDevice	;	// �f�o�C�X
	TLIB::Tempus2*			m_pTime			;	// ����
	Command*				m_pCommand		;	// �R�}���h
//////////
//	: �v���e�N�g�֐�
private:
	void SetStage( wiz::Stage* pStage ){ m_pStage = pStage ; }
//////////
//	: ���J�֐�
public:
	/////////////////// ////////////////////
	//// �֐���     �FBassPacket::BassPacket()
	//// �J�e�S��   �F�f�t�H���g�R���X�g���N�^
	//// �p�r       �F���̂𐶐�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	BassPacket()
		:m_pD3DDevice( NULL )
		,m_pTime( NULL )
		,m_pCommand( NULL )
	
	{}
	/////////////////// ////////////////////
	//// �֐���     �FBassPacket::BassPacket(BassPacket& i_OtherPacket)
	//// �J�e�S��   �F�R�s�[�R���X�g���N�^
	//// �p�r       �F���̂𐶐�
	//// ����       �F  BassPacket& i_OtherPacket //  : ���̃p�P�b�g�f�[�^
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	BassPacket(BassPacket& i_OtherPacket)
		:m_pStage(		i_OtherPacket.m_pStage		)
		,m_pD3DDevice(	i_OtherPacket.m_pD3DDevice	)
		,m_pTime(		i_OtherPacket.m_pTime		)
		,m_pCommand(	i_OtherPacket.m_pCommand	)
	
	{}
	/////////////////// ////////////////////
	//// �֐���     �FTLIB::Tempus2* BassPacket::GetTime() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���ԊǗ��N���X�ւ̃|�C���^�[���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F���ԊǗ��N���X�ւ̃|�C���^
	//// ���l       �F
	////            �F
	////
	TLIB::Tempus2* GetTime() const;
	/////////////////// ////////////////////
	//// �֐���     �FLPDIRECT3DDEVICE9 BassPacket::GetDevice() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���݂̃f�o�C�X���l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�f�o�C�X�̃|�C���^
	//// ���l       �F
	////            �F
	////
	LPDIRECT3DDEVICE9 GetDevice() const;
	/////////////////// ////////////////////
	//// �֐���     �FLPTATRATEXTURE AddTexture( const wchar_t* sTextureName )
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�w��̃e�N�X�`���[�ւ̃|�C���^�[��Ԃ��܂�
	//// ����       �F  const wchar_t* sTextureName      //  : �ǂݍ��݂����摜�f�[�^�̃t�@�C����
	//// �ߒl       �F�e�N�X�`���[�ւ̃|�C���^
	//// ���l       �F����̎Q�Ƃ̍ۂ͐V�K�ŉ摜��ǂݍ��݂܂�
	////            �F����ȍ~�����摜��v�����ꂽ�ꍇ�͑O��Ɠ����|�C���^�[��Ԃ��܂�
	////            �F�܂��t�@�C���̓ǂݍ��݂Ɏ��s�����ۂɂ�NULL���A��܂�
	////            �F�t�@�C������"��ƃf�B���N�g��/Media/Textures"����̑��΃p�X�Ŏw��o���܂�
	////            �F
	////
	LPTATRATEXTURE AddTexture( const wchar_t* sTextureName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::AddButton( Object* pButton )
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F�X�e�[�W�Ƀ{�^���I�u�W�F�N�g�Z�b�g���܂�
	//// ����       �F  Object*      pButton         //  : �{�^���I�u�W�F�N�g�ւ̃|�C���^
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void AddButton( Object* pButton );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::AddObject( Object* pObje )
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F�X�e�[�W�ɃI�u�W�F�N�g���Z�b�g���܂�
	//// ����       �F  Object*       pObje          //  : �Z�b�g����I�u�W�F�N�g�ւ̃|�C���^
	//// �ߒl       �F�Ȃ�
	//// ���l       �FObject�N���X���p�����Ă�����̂Ȃ�΂Ȃ�ł�����܂�
	////            �F
	////
	void AddObject( Object* pObje );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::SearchSoundAndPlay( const char* sSoundName )
	//// �J�e�S��   �F�T�E���h�v���C���[
	//// �p�r       �FXACT�ɓo�^����Ă���SOUND�f�[�^���Đ����܂�
	//// ����       �F  const char*    sSoundName          //  : �T�E���h��
	//// �ߒl       �F�Ȃ�
	//// ���l       �FXACT�ɓo�^����Ă�����̂����Đ��o���܂���
	////            �F�T�E���h���Đ�����Ȃ��ꍇ�͈ȉ��̍��ڂ��m�F���Ă�������
	////            �FXACT�ɓo�^����Ă��邩
	////            �FsSoundName �ɓn�������O����������
	////            �F���ʂ������߂��Ȃ���
	////            �F
	////
	void SearchSoundAndPlay( const char* sSoundName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::SearchSoundAndStop( const char* sSoundName )
	//// �J�e�S��   �F�T�E���h�v���C���[
	//// �p�r       �FXACTSOUND�ōĐ�����Ă��鉹���~���܂�
	//// ����       �F  const char*    sSoundName          //  : �T�E���h��
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void SearchSoundAndStop( const char* sSoundName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::SearchWaveAndPlay( const char* sSoundName )
	//// �J�e�S��   �F�T�E���h�v���C���[
	//// �p�r       �FXACT�ɓo�^����Ă���WAVE�f�[�^���Đ����܂�
	//// ����       �F  const char*    sSoundName          //  : �T�E���h��
	//// �ߒl       �F�Ȃ�
	//// ���l       �FXACT�ɓo�^����Ă�����̂����Đ��o���܂���
	////            �F�T�E���h���Đ�����Ȃ��ꍇ�͈ȉ��̍��ڂ��m�F���Ă�������
	////            �FXACT�ɓo�^����Ă��邩
	////            �FsSoundName �ɓn�������O����������
	////            �F���ʂ������߂��Ȃ���
	////            �F
	////
	void SearchWaveAndPlay( const char* sWaveName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::SearchWaveAndStop( const char* sSoundName )
	//// �J�e�S��   �F�T�E���h�v���C���[
	//// �p�r       �FXACTWAVE�ōĐ�����Ă��鉹���~���܂�
	//// ����       �F  const char*    sSoundName          //  : �T�E���h��
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void SearchWaveAndStop( const char* sWaveName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::SoundStop( const char* sSoundName )
	//// �J�e�S��   �F�T�E���h�v���C���[
	//// �p�r       �FXACT�ōĐ�����Ă��鉹��WAVE/SOUND��킸�ɒ�~���܂�
	//// ����       �F  const char*    sSoundName          //  : �T�E���h��
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void SoundStop( const char* sSoundName );
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::PushCommand( const Command Com )
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F�R�}���h���Z�b�g���܂�(���d�l���ϗ\��)
	//// ����       �F  const Command Com          //  : �ǉ�����R�}���h
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void PushCommand( const Command	Com );	//	: �������SetCommand 
	/////////////////// ////////////////////
	//// �֐���     �Fvoid BassPacket::ClearCommand( ) const
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F�R�}���h���N���A���܂�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// ���l       �F
	////            �F
	////
	void ClearCommand( ) const;
	/////////////////// ////////////////////
	//// �֐���     �FCommand BassPacket::PopCommand( ) const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�R�}���h���l�����܂�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�R�}���h
	//// ���l       �F
	////            �F
	////
	Command PopCommand( ) const;

	/////////////////// ////////////////////
	//// �֐���     �FObject* SearchObjectFromID(
	////            �F    DWORD                                i_dwID             ,
	////            �F    vector<Object*>::size_type*          o_Point     = NULL ,
	////            �F    vector<Object*>*                     o_pVec      = NULL ,
	////            �F    vector<vector<Object*>::size_type>*  o_PointList = NULL );
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �FOBJID�����ɃI�u�W�F�N�g��T��
	//// ����       �F  DWORD                                i_dwID      //  :  [IN] �T�������I�u�W�F�N�g��OBJID
	////            �F  vector<Object*>::size_type*          o_Point     //  : [OUT] �������ꏊ
	////            �F  vector<Object*>*                     o_pVec      //  : [OUT] �����������ꍇ�̃I�u�W�F�N�g�ꗗ
	////            �F  vector<vector<Object*>::size_type>*  o_PointList //  : [OUT] �����������ꍇ�̃I�u�W�F�N�g�̏ꏊ�ꗗ
	//// �ߒl       �F��ԍŏ��ɔ��������I�u�W�F�N�g�ւ̃|�C���^
	//// ���l       �F
	////            �F
	////
	Object* SearchObjectFromID( 
				DWORD									i_dwID,
				vector<Object*>::size_type*				o_Point		= NULL,
				vector<Object*>*						o_pVec		= NULL,
				vector<vector<Object*>::size_type>*		o_PointList = NULL
	);

	/////////////////// ////////////////////
	//// �֐���     �FObject* SearchObjectFromID( 
	////            �F    const type_info&         i_typeinfo           ,
	////            �F    vector<Object*>*         o_pVec      = NULL   );
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �FOBJID�����ɃI�u�W�F�N�g��T��
	//// ����       �F  const type_info&           i_typeinfo      //  :  [IN] �T�������I�u�W�F�N�g��type_info
	////            �F  vector<Object*>*           o_pVec          //  : [OUT] �����������ꍇ�̃I�u�W�F�N�g�ꗗ
	//// �ߒl       �F��ԍŏ��ɔ��������I�u�W�F�N�g�ւ̃|�C���^
	//// ���l       �F
	////            �F
	////
	Object* SearchObjectFromTypeID(
				const type_info&						i_typeinfo,
				vector<Object*>*						o_pVec		= NULL
	);
};
//**************************************************************************//
// struct UpdatePacket;
//
// �S����  : ���� �O
// �p�r    : �A�b�v�f�[�g�֐��S�ɗ����f�[�^
//**************************************************************************//
struct UpdatePacket : public BassPacket{
	const CONTROLER_STATE*	m_pCntlState	;
	UpdatePacket::UpdatePacket()
		:m_pCntlState( NULL ){
	};
	UpdatePacket::UpdatePacket( BassPacket& i_BassPacket )
		:BassPacket(i_BassPacket)
		,m_pCntlState( NULL ){}
	;
};
//**************************************************************************//
// struct RenderPacket;
//
// �S����  : ���� �O
// �p�r    : �����_�[�֐��Q�ɗ����f�[�^
//**************************************************************************//
struct RenderPacket : public BassPacket{
};
//**************************************************************************//
// struct DrawPacket;
//
// �S����  : ���� �O
// �p�r    : �h���[�֐��Q�ɗ����f�[�^
//**************************************************************************//
struct DrawPacket : public BassPacket{
};



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct FactoryPacket;
//
// �S����  : ���� �O
// �p�r    : �t�@�N�g���[�ɓn���p�P�b�g�f�[�^
//**************************************************************************//
struct FactoryPacket : public BassPacket{
public:
	//�_�C�A���O�X�e�[�W���ǂ���
	bool m_IsDialog;
public:
	FactoryPacket(		LPDIRECT3DDEVICE9 i_pD3DDevice, bool i_IsDialog, Command* i_pCommand, Stage* i_pStage )
		:m_IsDialog(	i_IsDialog		)
	{

		this->m_IsDialog	= i_IsDialog	;
		this->m_pD3DDevice	= i_pD3DDevice	;
		this->m_pCommand	= i_pCommand	;
		this->m_pStage		= i_pStage		;
		this->m_pTime		= NULL			;

	}
	vector<Object*>* GetObjectVector();
	void SetSound( system::Sound*  pSound  );
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

//**************************************************************************
// union Color;
//
// �S����  : ���� �O
// �p�r    : DWORDColor���Ǘ����₷������
//**************************************************************************
union Color {
	DWORD dwColor;
	struct {BYTE b , g , r , a ;}byteColor;
	Color(){};
	Color(DWORD Color):dwColor(Color){};
	Color(BYTE A ,BYTE R ,BYTE G , BYTE B )
	{ byteColor.a = A;byteColor.r = R;byteColor.g = G;byteColor.b = B;};
	Color& operator = (DWORD other){ dwColor = other ; return *this; };
	operator DWORD(){ return dwColor; }
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct FlexibleVertex;
//
// �S����  : ���� �O
// �p�r    : �t���L�V�u���Ȓ��_������
// ���l    : ���Ȃ�d���Ȃ邱�Ƃ��\�z����܂�
//**************************************************************************//
struct FlexibleVertex{
	D3DXVECTOR3 *pos;
	float       *rhw;
	float		*blend1;
	float		*blend2;
	float		*blend3;
	D3DXVECTOR3 *normal;
	float		*pointSize;
	DWORD		*diffuse;
	DWORD		*specular;
	//D3DXVECTOR4	*TexSet1;
	//D3DXVECTOR4	*TexSet2;
	//D3DXVECTOR4	*TexSet3;
	//D3DXVECTOR4	*TexSet4;
	//D3DXVECTOR4	*TexSet5;
	//D3DXVECTOR4	*TexSet6;
	//D3DXVECTOR4	*TexSet7;
	//D3DXVECTOR4	*TexSet8;
	FlexibleVertex(BYTE* vBuffer,DWORD FVF)
		:pos(NULL),rhw(NULL),blend1(NULL),blend2(NULL),blend3(NULL)
		,normal(NULL),pointSize(NULL),diffuse(NULL),specular(NULL)
	{
		BYTE floatByteNum  = 4;
		BYTE DwordByteNum  = 4;
		BYTE VectorByteNum = floatByteNum*3;
		BYTE Address = 0;

		//////////
		//	: ���_�|�C���^
		pos = ( D3DXVECTOR3* )  vBuffer;
		Address += VectorByteNum;

		//////////
		//	: RHW�|�C���^
		if( FVF & D3DFVF_XYZRHW ){
			rhw = ( float* )( vBuffer + Address );
			Address += VectorByteNum + floatByteNum;
		}

		//////////
		//	: �x�[�^1
		if( FVF & D3DFVF_XYZB1  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: �x�[�^2
		if( FVF & D3DFVF_XYZB2  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: �x�[�^3
		if( FVF & D3DFVF_XYZB3  ){
			blend1 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend2 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
			blend3 = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: �m�[�}��
		if( FVF & D3DFVF_NORMAL ){
			normal = ( D3DXVECTOR3* )( vBuffer + Address );
			Address +=  VectorByteNum;
		}

		//////////
		//	: �|�C���g�T�C�Y
		if( FVF & D3DFVF_PSIZE ){
			pointSize = ( float* )( vBuffer + Address );
			Address +=  floatByteNum;
		}

		//////////
		//	: �f�B�t���[�Y
		if( FVF & D3DFVF_DIFFUSE  ){
			diffuse = ( DWORD* )( vBuffer + Address );
			Address +=  DwordByteNum;
		}

		//////////
		//	: �X�y�L�����[
		if( FVF & D3DFVF_SPECULAR  ){
			specular = ( DWORD* )( vBuffer + Address ); 
			Address +=  DwordByteNum;
		}
	}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct OBB;
//
// �S����  : �Ȃ�(�R�m��搶�̂ЂȌ`���)
// �p�r    : OBB�{�����[�����E
//**************************************************************************//
struct OBB{
    D3DXVECTOR3 m_Center;   //���S�_�̍��W
	D3DXMATRIX	m_mRot;
    D3DXVECTOR3 m_Rot[3];   //XYZ �̊e���W���̌X����\�������x�N�g��
    D3DXVECTOR3 m_Size;     //OBB �̊e���W���ɉ����������̔����i���S�_����ʂ܂ł̒����j
	OBB():m_Center(g_vZero),m_Size(g_vOne){
		m_Rot[0] = g_vZero;
		m_Rot[1] = g_vZero;
		m_Rot[2] = g_vZero;
	};
	OBB(D3DXVECTOR3 vScale,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos){
		//�Փ˔���p��OBB�̏�����
		m_Center = vPos   ;
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(D3DXVECTOR3 vScale,D3DXQUATERNION vQt,D3DXVECTOR3 vPos){
		//�Փ˔���p��OBB�̏�����
		m_Center = vPos   ;
		//m_Size   = vScale ;
		m_Size   = vScale * 0.5f ;
		//vQt		*= vQt ; 
		//D3DXQuaternionNormalize(&vQt,&vQt);

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&vQt);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	OBB(LPD3DXMESH pMesh){
		//�Փ˔���p��OBB�̏�����
		EarnFromMeshOBB(pMesh,m_Center,m_Size);
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	};
	void setRot(D3DXVECTOR3 vRot){
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		m_mRot = mRot ;
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 struct AABB;
 �p�r: AABB�{�����[�����E
****************************************************************************/
struct AABB{
    D3DXVECTOR3 m_Min;     //�������ق��̍��W
    D3DXVECTOR3 m_Max;     //�傫���ق��̍��W
	AABB(){}
	AABB(D3DXVECTOR3& Min,D3DXVECTOR3& Max)
		:m_Min(Min),m_Max(Max){}
	AABB(D3DXVECTOR3& Center,FLOAT XSize,FLOAT YSize,FLOAT ZSize){
		FLOAT xh = XSize / 2.0f;
		FLOAT yh = YSize / 2.0f;
		FLOAT zh = ZSize / 2.0f;

		m_Min.x = Center.x - xh;
		m_Max.x = Center.x + xh;

		m_Min.y = Center.y - yh;
		m_Max.y = Center.y + yh;

		m_Min.z = Center.z - zh;
		m_Max.z = Center.z + zh;
	}
	void GetCenter(D3DXVECTOR3& Pos){
		Pos.x = (m_Min.x + m_Max.x) / 2.0f;
		Pos.y = (m_Min.y + m_Max.y) / 2.0f;
		Pos.z = (m_Min.z + m_Max.z) / 2.0f;
	}
	void Move(D3DXVECTOR3& MoveVec){
		m_Min += MoveVec;
		m_Max += MoveVec;
	}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 struct SPHERE;
 �p�r: ���f�[�^
****************************************************************************/
struct SPHERE
{
    D3DXVECTOR3 m_Center;	//���S�_�̍��W
    float m_Radius;			//���a
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct RENDERSTATE_PARAM;
//
// �S����  : ���� �O
// �p�r    : �����_�[�^�C�v�ƃf�[�^�̃Z�b�g���L�����Ă�������!
//
//**************************************************************************//
struct RENDERSTATE_PARAM{
	D3DRENDERSTATETYPE	renderType;
	DWORD				value;
	//RENDERSTATE_PARAM(){};
	//RENDERSTATE_PARAM(D3DRENDERSTATETYPE i_RenderType, DWORD i_dwValue)
	//	:renderType(i_RenderType), value(i_dwValue){};
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



}//end of namespace structs.
using namespace structs;
}//end of namespace wiz.
