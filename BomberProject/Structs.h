////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���Ȋ֐��Q�̃C�����C����`
//					��
//	namespace wiz;
//		struct FlexibleVertex ;
//		struct OBB  ;
//		struct AABB      ;
//		struct Sphere        ;
//		struct RENDERSTATE_PARAM ;
//		struct ObjeData    ;
//
#pragma once

#include "StdAfx.h"

namespace wiz{
class Object ; 
class TextureManager ;

extern void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
namespace structs{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct FactoryPacket;
//
// �S����  : ���� �O
// �p�r    : �t�@�N�g���[�ɓn���p�P�b�g�f�[�^
//**************************************************************************//
struct FactoryPacket{
	//�_�C�A���O�X�e�[�W���ǂ���
	bool m_IsDialog;
	//�z�u�I�u�W�F�N�g�̃|�C���^�̃x�N�g��
	vector<Object*> m_Vec;
	//�e�N�X�`���̃|�C���^�̃x�N�g��
	TextureManager* m_pTexMgr;
};
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
		m_Size   = vScale ;
		D3DXMATRIX mRot   ;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
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
		m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct AABB;
//
// �S����  : ���� �O
// �p�r    : AABB�{�����[�����E
//**************************************************************************//
struct AABB{
    D3DXVECTOR3 m_Center;     //���S�_�̍��W
    D3DXVECTOR3 m_Size;       //OBB �̊e���W���ɉ����������̔����i���S�_����ʂ܂ł̒����j
	AABB():m_Center(g_vZero),m_Size(g_vOne){
	};
	AABB(D3DXVECTOR3 vScale,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos){
		//�Փ˔���p��OBB�̏�����
		m_Center = vPos   ;
		m_Size   = vScale ;
	};
	AABB(LPD3DXMESH pMesh){
		EarnFromMeshOBB(pMesh,m_Center,m_Size);
	};
	
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// struct Sphere;
//
// �S����  : �Ȃ�(�R�m��搶�̂ЂȌ`���)
// �p�r    : ���f�[�^
//**************************************************************************//
struct Sphere
{
    D3DXVECTOR3 m_Center;
    float m_Radius;
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

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Stage;
 �p�r: �Q�[�����X�e�[�W�P�ʂŊǗ�����N���X
****************************************************************************/
struct ObjeData{
	int			m_iObjeType		;
	wstring		m_sFilePath		;
	wstring		m_sTexturePath	;
	D3DXVECTOR3	m_vScale		;
	DWORD		m_dwMotionNum	;
	float		m_fTracSpeed	;
	ObjeData(){};
	ObjeData(int iType, wstring wsPath, wstring wsTexPath,
		D3DXVECTOR3 vScale, DWORD dwMotionNum, float fTracSpeed)
	{
		m_iObjeType		= iType			;
		m_sFilePath		= wsPath		;
		m_sTexturePath	= wsTexPath		;
		m_vScale		= vScale		;
		m_dwMotionNum	= dwMotionNum	;
		m_fTracSpeed	= fTracSpeed	;
	}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


}//end of namespace structs.
using namespace structs;
}//end of namespace wiz.
