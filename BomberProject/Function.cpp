////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�FFunction.h����`�̈ꕔ�f�[�^�̎��̂��`
//					��
//	namespace wiz;
//		class BaseException : public exception ;
//		template<typename T> inline void SafeDelete(T*& p)    ;
//		template<typename T> inline void SafeDeleteArr(T*& p) ;
//		template<typename T> inline void SafeRelease(T*& p)   ;
//		struct FlexibleVertex ;
//		inline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3) ;
//		inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
//		struct OBB  ;
//		struct AABB  ;
//		struct Sphere ;
//		class  HitTest ;
//		inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize)    ;
//		inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize) ;
//		inline void MeshTransformer(LPD3DXBASEMESH i_pMesh,D3DXMATRIX& i_mMatrix) ;
//		inline float Jump(float fHight,float fVTime,float fNowTime); ;
//		inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime) ;
//		class GetClientSize ;
//
#include "StdAfx.h"
#include "Function.h"

namespace wiz{
namespace functions{
Rect __GetClientSize::m_MainWindowRect  ;
}
}