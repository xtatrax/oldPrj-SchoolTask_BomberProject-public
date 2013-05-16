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

namespace wiz{
class  Object ; 
class  TextureManager ;
struct CONTROLER_STATE;
namespace functions {
extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
}
using namespace functions ;
namespace structs{
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
	D3DCOLORVALUE   Diffuse   ;
	D3DCOLORVALUE   Specular  ;
	D3DCOLORVALUE   Ambient   ;
	bool			bPool     ;

	//	: �I�v�V����
	wstring			sTexturePath	;

	wstring			sFilePath		;
	DWORD			dwMotionNum		;
	float			fTracSpeed		;
	//MapPartsStatus(){};
	//MapPartsStatus(DWORD i_dwClassID, D3DXVECTOR3 i_vScale, D3DXVECTOR3 i_vRot, D3DXVECTOR3 i_vPos,
	//	wstring i_wsPath = L"", wstring i_wsTexPath = L"",
	//	DWORD i_dwMotionNum = 0, float i_fTracSpeed = 1.0f)
	//{
	//	enClassid		= i_dwClassID	;
	//	vScale			= i_vScale		;
	//	vRot			= i_vRot		;
	//	vPos			= i_vPos		;
	//	sFilePath		= i_wsPath		;
	//	sTexturePath	= i_wsTexPath	;
	//	vScale			= i_vScale		;
	//	dwMotionNum		= i_dwMotionNum	;
	//	fTracSpeed		= i_fTracSpeed	;
	//}


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
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = 0;
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
	Timer m_Timer;
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
	LPDIRECT3DDEVICE9		pD3DDevice	;	// �f�o�C�X
	vector<Object*>*		pVec		;	// �I�u�W�F�R���e�i
	TextureManager*			pTxMgr		;	// �e�N�X�`���Ǘ��N���X
	TLIB::Tempus2*			pTime		;	// ����
	Command*				pCommand	;	// �R�}���h
	BassPacket()
		:pD3DDevice( NULL )
		,pVec( NULL )
		,pTxMgr( NULL )
		,pTime( NULL )
		,pCommand( NULL )
	
	{}

};
//**************************************************************************//
// struct UpdatePacket;
//
// �S����  : ���� �O
// �p�r    : �A�b�v�f�[�g�֐��S�ɗ����f�[�^
//**************************************************************************//
struct UpdatePacket : public BassPacket{
	const CONTROLER_STATE*	pCntlState	;
	UpdatePacket()
		:pCntlState( NULL )
	{
	}

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct RenderPacket;
//
// �S����  : ���� �O
// �p�r    : �����_�[�֐��Q�ɗ����f�[�^
//**************************************************************************//
struct RenderPacket : public BassPacket{
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
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
struct FactoryPacket{
	//Device
	LPDIRECT3DDEVICE9 pD3DDevice ;
	//�_�C�A���O�X�e�[�W���ǂ���
	bool m_IsDialog;
	//�z�u�I�u�W�F�N�g�̃|�C���^�̃x�N�g��
	vector<Object*>* m_pVec;
	//�e�N�X�`���̃|�C���^�̃x�N�g��
	TextureManager* m_pTexMgr;
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
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct FlexibleVertex;
//
// �S����  : ���� �O
// �p�r    : �t���L�V�u���Ȓ��_������
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
