////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FFunction.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���Ȋ֐��Q�̃C�����C����`
//					��
//	namespace wiz;
//		class BaseException : public exception ;
//		template<typename T> inline void SafeDelete(T*& p)    ;
//		template<typename T> inline void SafeDeleteArr(T*& p) ;
//		template<typename T> inline void SafeRelease(T*& p)   ;
//		inline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3) ;
//		inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize);
//		class  HitTest ;
//		inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize)    ;
//		inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize) ;
//		inline void MeshTransformer(LPD3DXBASEMESH i_pMesh,D3DXMATRIX& i_mMatrix) ;
//		inline float Jump(float fHight,float fVTime,float fNowTime); ;
//		inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime) ;
//		class GetClientSize ;
//
#pragma once

#include "StdAfx.h"

namespace wiz{

extern class Object ;

namespace functions{

#define TL_SQUARE(n)							((n)*(n))
#define TL_PI									(3.1415926535897932384626433832795028841971)
#define TL_RAD(degree)							((degree) * TL_PI / 180.0f)
#define TL_DEG(radian)							((radian) * 180.0 / TL_PI)
#define TL_DISTANCE2D(   PointAX, PointAY,   PointBX, PointBY)						sqrt(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY)))
#define TL_SQDISTANCE2D( PointAX, PointAY,   PointBX, PointBY)						 abs(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY)))
#define TL_DISTANCE3D(   PointAX, PointAY, PointAZ,   PointBX, PointBY, PointBZ)	sqrt(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY))  + TL_SQUARE((PointBZ) - (PointAZ)))
#define TL_SQDISTANCE3D( PointAX, PointAY, PointAZ,   PointBX, PointBY, PointBZ)	 abs(TL_SQUARE((PointBX)  - (PointAX))  + TL_SQUARE((PointBY) - (PointAY))  + TL_SQUARE((PointBZ) - (PointAZ)))

//************************************************//
//class BaseException : public exception
//
// �S����  : �Ȃ�(�R�m��搶�̂ЂȌ`���)
// �ړI    : STL��O����h�������N���X
//************************************************//
class BaseException : public exception{
    //���b�Z�[�W�ϐ�
    wstring m_Message;
public:
/////////////////// ////////////////////
//// �֐���     �FBaseException(const wchar_t* m1,const wchar_t* m2)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�R���X�g���N�^
//// ����       �F  const wchar_t* m1,  //��1���b�Z�[�W
////            �F  const wchar_t* m2   //��2���b�Z�[�W
//// �ߒl       �F���b�Z�[�W������̃|�C���^
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    BaseException(const wchar_t* m1,const wchar_t* m2){
        m_Message = m1;
        m_Message += L"\r\n";
        m_Message += m2;
    }
/////////////////// ////////////////////
//// �֐���     �Fconst wchar_t* what_w() const throw()
//// �J�e�S��   �F���J�����o�֐�
//// �p�r       �F���b�Z�[�W�̎擾
//// ����       �F�Ȃ�
//// �ߒl       �F���b�Z�[�W������̃|�C���^
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    const wchar_t* what_w() const throw(){
        return m_Message.c_str();
    }
};

class LoaderException : public BaseException {
public:
	LoaderException(const wchar_t* m1,const wchar_t* m2)
		:BaseException( m1 , m2 )
	{}
	//LoaderException(const LoaderException other)
	//	:BaseException( other.m_Message )
	//{}
	//LoaderException(const wstring other)
	//	:BaseException( other )
	//{}
};


/**************************************************************************
 class Math;
 �p�r: �v�Z�p�̃��[�e�B���e�B
 �@�@�@static�Ăяo��������
****************************************************************************/

class Math{
public:
	static void QtToRot(const D3DXQUATERNION& Qt,D3DXVECTOR3& Rot){
		D3DXQUATERNION tempQt = Qt;
		//���K��
		D3DXQuaternionNormalize(&tempQt,&tempQt);
		//�s��Ɏ��o��
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		D3DXMatrixRotationQuaternion(&mt,&tempQt);
		if(mt._32 == 1.0f){
			Rot.x = D3DX_PI / 2.0f;
			Rot.y = 0;
			Rot.z = -atan2(mt._21,mt._11);
		}
		else if(mt._32 == -1.0f){
			Rot.x = -D3DX_PI / 2.0f;
			Rot.y = 0;
			Rot.z = -atan2(mt._21,mt._11);
		}
		else{
			Rot.x = -asin(mt._32);
			Rot.y = -atan2(-mt._31,mt._33);
			Rot.z = -atan2(-mt._12,mt._22);
		}
	}
	Math(){}
	~Math(){}

};


/////////////////// ////////////////////
//// �֐���     �Finline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�O�����x�N�g���ɍs��ϊ����s��
//// ����       �F  const D3DXMATRIX&  i_m4x4    //  : �v�Z�Ɏg���s��f�[�^
////            �F  const D3DXVECTOR3& i_v1x3    //  : �ϊ������������W�f�[�^
//// �ߒl       �F�ϊ����ꂽ�x�N�g��
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
inline D3DXVECTOR3 MatrixCalculator(const D3DXMATRIX& i_m4x4 ,const D3DXVECTOR3& i_v1x3){
	D3DXVECTOR3 res;

	res.x		= (i_m4x4._11 * i_v1x3.x) + (i_m4x4._21 * i_v1x3.y) + (i_m4x4._31 * i_v1x3.z) + (i_m4x4._41 * 1);
	res.y		= (i_m4x4._12 * i_v1x3.x) + (i_m4x4._22 * i_v1x3.y) + (i_m4x4._32 * i_v1x3.z) + (i_m4x4._42 * 1);
	res.z		= (i_m4x4._13 * i_v1x3.x) + (i_m4x4._23 * i_v1x3.y) + (i_m4x4._33 * i_v1x3.z) + (i_m4x4._43 * 1);
	//float alpha = (i_m4x4._14 * i_v1x3.x) + (i_m4x4._24 * i_v1x3.y) + (i_m4x4._34 * i_v1x3.z) + (i_m4x4._44 * 1);
	
	return res;
};

/////////////////// ////////////////////
//// �֐���     �Finline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�O�����x�N�g���ɍs��ϊ����s��
//// ����       �F  const D3DXMATRIX&  i_m4x4    //  : �v�Z�Ɏg���s��f�[�^
////            �F  const D3DXVECTOR3& i_v1x3    //  : �ϊ������������W�f�[�^
//// �ߒl       �F�ϊ����ꂽ�x�N�g��
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
inline Point MatrixCalculator(const D3DXMATRIX& i_m4x4 ,const Point& i_v1x2){
	Point res;

	res.x		= (LONG)((i_m4x4._11 * i_v1x2.x) + (i_m4x4._21 * i_v1x2.y) + (i_m4x4._31 * 0) + (i_m4x4._41 * 1));
	res.y		= (LONG)((i_m4x4._12 * i_v1x2.x) + (i_m4x4._22 * i_v1x2.y) + (i_m4x4._32 * 0) + (i_m4x4._42 * 1));
	//res.z		= (i_m4x4._13 * i_v1x3.x) + (i_m4x4._23 * i_v1x3.y) + (i_m4x4._33 * 0) + (i_m4x4._43 * 1);
	//float alpha = (i_m4x4._14 * i_v1x3.x) + (i_m4x4._24 * i_v1x3.y) + (i_m4x4._34 * i_v1x3.z) + (i_m4x4._44 * 1);
	
	return res;
};

/////////////////// ////////////////////
//// �֐���     �Finline D3DXVECTOR3 MatrixCalculator(const D3DXVECTOR3& vScale, const D3DXVECTOR3& vRot, const D3DXVECTOR3& vPos)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�O�����x�N�g���ɍs��ϊ����s��
//// ����       �F  const D3DXVECTOR3& vScale
////            �F  const D3DXVECTOR3& vRot
////            �F  const D3DXVECTOR3& vPos
//// �ߒl       �F�ϊ����ꂽ�x�N�g��
//// �S��       �F���� �O
//// ���l       �F���O���Ȃ��悤�ɂ������c
////            �F�������O�v�����Ȃ�><
////
inline D3DXMATRIX MatrixCalculator(const D3DXVECTOR3& vScale, const D3DXVECTOR3& vRot, const D3DXVECTOR3& vPos){
	D3DXMATRIX mScale, mRot, mPos;

	D3DXMatrixScaling( &mScale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationYawPitchRoll( &mRot, vRot.z, vRot.x , vRot.y ) ;
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);

	return mScale * mRot * mPos;
};

/////////////////// ////////////////////
//// �֐���     �Finline D3DXVECTOR3 MatrixCalculator(const D3DXVECTOR3& vScale, const D3DXVECTOR3& vRot, const D3DXVECTOR3& vPos)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�O�����x�N�g���ɍs��ϊ����s��
//// ����       �F  const D3DXVECTOR3& vScale
////            �F  const D3DXVECTOR3& vRot
////            �F  const D3DXVECTOR3& vPos
//// �ߒl       �F�ϊ����ꂽ�x�N�g��
//// �S��       �F���� �O
//// ���l       �F���O���Ȃ��悤�ɂ������c
////            �F�������O�v�����Ȃ�><
////
inline D3DXMATRIX MatrixCalculator(const D3DXVECTOR3& vScale, const D3DXQUATERNION& Qt, const D3DXVECTOR3& vPos){
	D3DXMATRIX mScale, mRot, mPos;

	D3DXMatrixScaling( &mScale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationQuaternion(&mRot,&Qt);
	D3DXMatrixTranslation( &mPos, vPos.x, vPos.y, vPos.z);

	return mScale * mRot * mPos;
};

/////////////////// ////////////////////
//// �֐���     �Finline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,
////            �F      D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F���b�V���f�[�^�̑傫���ƒ��S���W���l������
//// ����       �F  const LPD3DXBASEMESH i_pMesh    //  : ���ɂȂ郁�b�V��
////            �F  D3DXVECTOR3& o_vPos             //  : ���b�V���̒��S�_��Ԃ����߂̃|�C���^
////            �F  D3DXVECTOR3& o_vSize            //  : ���b�V���̑傫����Ԃ����߂̃|�C���^
//// �S��       �F���� �O
//// �ߒl       �F�Ȃ�(����̈����֕Ԃ�)
//// ���l       �FPos  = MaxPos��MinPos�̊Ԃ̓_
////            �FSize = MaxPos����MinPos�̋���/2
////
inline void EarnFromMeshOBB(const LPD3DXBASEMESH i_pMesh,D3DXVECTOR3& o_vPos ,D3DXVECTOR3& o_vSize){
	//���_���o��
	//LPDIRECT3DVERTEXBUFFER9 VertexBuffer;			// ���_�o�b�t�@-
	const DWORD vSize = i_pMesh->GetNumBytesPerVertex();	// ���_�̃o�C�g��
	const DWORD vNum  = i_pMesh->GetNumVertices();		// ���_��
	DWORD fvf   = i_pMesh->GetFVF();				// ���_�t�H�[�}�b�g
	//i_pMesh->GetVertexBuffer(&VertexBuffer);		// �o�b�t�@�[�̊l��
	PBYTE Vertex;
	i_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&Vertex);
	//BYTE* Vertex = new BYTE[vSize*vNum];			// �v�Z�p���_�o�b�t�@-
	//VertexBuffer->Lock(0,0,(void**)&Vertex,0);		// ���_���b�N

	D3DXVECTOR3 Min = g_vMax;		//	: �ő�_�o�b�t�@ 
	D3DXVECTOR3 Max = g_vMin;		//	: �ŏ��_�o�b�t�@
	for(DWORD i = 0 ; i < vNum ; i++){
		FlexibleVertex fvBuf(Vertex+(vSize*i),fvf);			//	: �擪�A�h���X + ( 1���_�̃T�C�Y * ���_�� )
		if(fvBuf.pos->x > Max.x) Max.x = fvBuf.pos->x ;
		if(fvBuf.pos->y > Max.y) Max.y = fvBuf.pos->y ;
		if(fvBuf.pos->z > Max.z) Max.z = fvBuf.pos->z ;
		if(fvBuf.pos->x < Min.x) Min.x = fvBuf.pos->x ;
		if(fvBuf.pos->y < Min.y) Min.y = fvBuf.pos->y ;
		if(fvBuf.pos->z < Min.z) Min.z = fvBuf.pos->z ;
	}
	o_vPos = ( Min + Max ) / 2;
	o_vSize = ( Max - Min ) / 2;
	//VertexBuffer->Unlock();
	//*/

};


/**************************************************************************
 class HitTest;
 �p�r: �Փ˔���p�̃��[�e�B���e�B
 �@�@�@static�Ăяo��������
****************************************************************************/
class HitTest{
public:
	HitTest(){}
	~HitTest(){}
/**************************************************************************
 static void ClosestPtPointOBB(
	const D3DXVECTOR3& point,		//��_
	const OBB& obb,				//OBB
	D3DXVECTOR3& retvec		//�ŋߐړ_��Ԃ��Q��
�@);
 �p�r: point���猩��OBB�̍ŋߐړ_�𓾂�
 �߂�l: �����iretvec�ɍŋߐړ_����������j
***************************************************************************/
	static void ClosestPtPointOBB(const D3DXVECTOR3& point,const OBB& obb, D3DXVECTOR3& retvec){
		D3DXVECTOR3 d = point - obb.m_Center;
		retvec = obb.m_Center;
		float dist;
		for(int i = 0; i < 3; i++)
		{
			dist = D3DXVec3Dot(&d, &obb.m_Rot[i]);
			if(dist > obb.m_Size[i])
			{
				dist = obb.m_Size[i];
			}
			if(dist < -obb.m_Size[i])
			{
				dist = -obb.m_Size[i];
			}
			retvec +=  dist * obb.m_Rot[i];
		}
	}
/**************************************************************************
 static bool SPHERE_SPHERE(
	const SPHERE& sp1,		//���P
	const SPHERE& sp2		//���Q
);
 �p�r: ���Ƌ��Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true
***************************************************************************/
	static bool SPHERE_SPHERE(const SPHERE& sp1,const SPHERE& sp2){
		D3DXVECTOR3 d = sp1.m_Center - sp2.m_Center;
		float dist2 = D3DXVec3Dot(&d,&d);
		float radiussum = sp1.m_Radius + sp2.m_Radius;
		return dist2 <= radiussum * radiussum;
	}
/**************************************************************************
 static void ClosestPtPointAABB(
	const D3DXVECTOR3& p,		//�_
	const AABB& b,		//AABB
	D3DXVECTOR3& retvec	//�ŋߐړ_����������Q��
);
 �p�r: �_��AABB�Ƃ̍ŋߐړ_�𓾂�
 �߂�l: �Ȃ��iretvec�ɍŋߐړ_����������j
***************************************************************************/
	static void ClosestPtPointAABB(const D3DXVECTOR3& p,const AABB& b,
		D3DXVECTOR3& retvec){
		for(int i = 0;i < 3;i++){
			float v = p[i];
			if(v < b.m_Min[i]){
				v = b.m_Min[i];
			}
			if(v > b.m_Max[i]){
				v = b.m_Max[i];
			}
			retvec[i] = v;
		}
	}


/**************************************************************************
 static float SqDistPointAABB(
	const D3DXVECTOR3& p,		//�_
	const AABB& b		//AABB
);
 �p�r: �_��AABB�Ƃ̋����̕����𑪂�
 �߂�l: ����
***************************************************************************/
	static float SqDistPointAABB(const D3DXVECTOR3& p,const AABB& b){
		float sqDist = 0.0f;
		for(int i = 0;i < 3;i++){
			float v = p[i];
			if(v < b.m_Min[i]){
				sqDist += (b.m_Min[i] - v) * (b.m_Min[i] - v);
			}
			if(v > b.m_Max[i]){
				sqDist += (v - b.m_Max[i]) * (v - b.m_Max[i]);
			}
		}
		return sqDist;
	}
/**************************************************************************
 static bool SPHERE_AABB(
	const SPHERE& sp,		//���P
	const AABB& b,		//AABB�Q
	D3DXVECTOR3& retvec	//�ŋߐړ_����������Q��
);
 �p�r: ����AABB�Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true�iretvec�ɍŋߐړ_����������j
***************************************************************************/
	static bool SPHERE_AABB(const SPHERE& sp,const AABB& b,
		D3DXVECTOR3& retvec){
			//�ŋߐړ_�𓾂�
			ClosestPtPointAABB(sp.m_Center,b,retvec);
			//�����̕��������̔��a�̕������Ȃ�true
			if(SqDistPointAABB(sp.m_Center,b) <= (sp.m_Radius * sp.m_Radius)){
				return true;
			}
			return false;
	}

/**************************************************************************
 static bool AABB_AABB(
	const AABB& a,		//AABB�P
	const AABB& b		//AABB�Q
);
 �p�r: AABB��AABB�Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true
***************************************************************************/
	static bool AABB_AABB(const AABB& a,const AABB& b){
		if(a.m_Max.x < b.m_Min.x || a.m_Min.x > b.m_Max.x)
			return false;
		if(a.m_Max.y < b.m_Min.y || a.m_Min.y > b.m_Max.y)
			return false;
		if(a.m_Max.z < b.m_Min.z || a.m_Min.z > b.m_Max.z)
			return false;
		return true;
	}
/**************************************************************************
 static bool AABB_IN_AABB(
	const AABB& a,		//AABB�P
	const AABB& b		//AABB�Q
);
 �p�r: AABB a��AABB ���Ɋ��S�Ɋ܂܂�邩����
 �߂�l: �Փ˂��Ă����true
***************************************************************************/
	static bool AABB_IN_AABB(const AABB& a,const AABB& b){
		if(a.m_Min.x < b.m_Min.x || a.m_Max.x > b.m_Max.x)
			return false;
		if(a.m_Min.y < b.m_Min.y || a.m_Max.y > b.m_Max.y)
			return false;
		if(a.m_Min.z < b.m_Min.z || a.m_Max.z > b.m_Max.z)
			return false;
		return true;
	}
/**************************************************************************
 static bool SPHERE_OBB(
	const SPHERE& sp,		//��
	const OBB& obb,		//OBB
	D3DXVECTOR3& retvec	//�ŋߐړ_����������Q��
);
 �p�r: OBB�Ƌ��Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true�iretvec�ɍŋߐړ_����������j
***************************************************************************/
	static bool SPHERE_OBB(const SPHERE& sp,const OBB& obb,D3DXVECTOR3& retvec){
        ClosestPtPointOBB(sp.m_Center,obb,retvec);
        D3DXVECTOR3 v = retvec - sp.m_Center;
        return D3DXVec3Dot(&v,&v) <= sp.m_Radius * sp.m_Radius;
	}
/**************************************************************************
 static bool OBB_OBB(
 const OBB& obb1,
 const OBB& obb2
 );
 �p�r: OBB��OBB�Ƃ̏Փ˔���
 �߂�l: �Փ˂��Ă����true
***************************************************************************/
	static bool OBB_OBB(const OBB& obb1,const OBB& obb2){
		const float EPSILON = 1.175494e-37f;
		float R[3][3], AbsR[3][3];
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				R[i][j] = D3DXVec3Dot(&obb1.m_Rot[i], &obb2.m_Rot[j]);
				AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
			}
		}
		D3DXVECTOR3 t = obb2.m_Center - obb1.m_Center;
		t = D3DXVECTOR3(D3DXVec3Dot(&t, &obb1.m_Rot[0]),
						D3DXVec3Dot(&t, &obb1.m_Rot[1]),
						D3DXVec3Dot(&t, &obb1.m_Rot[2]));
		//��L=A0, L=A1, L=A2����
		float ra, rb;
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[i];
			rb = obb2.m_Size[0] * AbsR[i][0] + obb2.m_Size[1] * AbsR[i][1] + obb2.m_Size[2] * AbsR[i][2];
			if(fabsf(t[i]) > ra + rb){
				return false;
			}
		}
		//��L=B0, L=B1, L=B2����
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[0] * AbsR[0][i] + obb1.m_Size[1] * AbsR[1][i] + obb1.m_Size[2] * AbsR[2][i];
			rb = obb2.m_Size[i];
			if(fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb){
				return false;
			}
		}
		//��L=A0 X B0����
		ra = obb1.m_Size[1] * AbsR[2][0] + obb1.m_Size[2] * AbsR[1][0];
		rb = obb2.m_Size[1] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][1];
		if(fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb){
			return false;
		}
		//��L=A0 X B1����
		ra = obb1.m_Size[1] * AbsR[2][1] + obb1.m_Size[2] * AbsR[1][1];
		rb = obb2.m_Size[0] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][0];
		if(fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb){
			return false;
		}
		//��L=A0 X B2����
		ra = obb1.m_Size[1] * AbsR[2][2] + obb1.m_Size[2] * AbsR[1][2];
		rb = obb2.m_Size[0] * AbsR[0][1] + obb2.m_Size[1] * AbsR[0][0];
		if(fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb){
			return false;
		}
		//��L=A1 X B0����
		ra = obb1.m_Size[0] * AbsR[2][0] + obb1.m_Size[2] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][1];
		if(fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb){
			return false;
		}
		//��L=A1 X B1����
		ra = obb1.m_Size[0] * AbsR[2][1] + obb1.m_Size[2] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][0];
		if(fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb){
			return false;
		}
		//��L=A1 X B2����
		ra = obb1.m_Size[0] * AbsR[2][2] + obb1.m_Size[2] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[1][1] + obb2.m_Size[1] * AbsR[1][0];
		if(fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb){
			return false;
		}
		//��L=A2 X B0����
		ra = obb1.m_Size[0] * AbsR[1][0] + obb1.m_Size[1] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][1];
		if(fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb){
			return false;
		}
		//��L=A2 X B1����
		ra = obb1.m_Size[0] * AbsR[1][1] + obb1.m_Size[1] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][0];
		if(fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb){
			return false;
		}
		//��L=A2 X B2����
		ra = obb1.m_Size[0] * AbsR[1][2] + obb1.m_Size[1] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[2][1] + obb2.m_Size[1] * AbsR[2][0];
		if(fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb){
			return false;
		}
		return true;
	}
};
/////////////////// ////////////////////
//// �֐���     �Finline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F
//// ����       �F  BYTE* byteBuf
////            �F  BYTE  arraySize
//// �ߒl       �F
//// �S��       �F
//// ���l       �F
////            �F
////
inline DWORD BYTE4toDWORD(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/){
	union BYTE4toDWORD{
		BYTE  uniByte[4];
		DWORD uniDword;
	}buf;
	for(BYTE i = 0; i < arraySize ;i++){
		buf.uniByte[i] = byteBuf[i];
	};
	return buf.uniDword;
};
/////////////////// ////////////////////
//// �֐���     �Finline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F
//// ����       �F  BYTE* byteBuf
////            �F  BYTE  arraySize
//// �ߒl       �F
//// �S��       �F
//// ���l       �F
////            �F
////
inline float BYTE4toFLOATfor(BYTE* byteBuf,BYTE arraySize/* MAX = 4*/){
	union BYTE4toDWORD{
		BYTE  uniByte[4];
		float uniFloat;
	}buf;
	for(BYTE i = 0; i < arraySize ;i++){
		buf.uniByte[i] = byteBuf[i];
	};
	return buf.uniFloat;
};
/////////////////// ////////////////////
//// �֐���     �Finline void MeshTransformer(LPD3DXBASEMESH io_pMesh,D3DXMATRIX& i_mMatrix)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�}�g���b�N�X���g���ă��b�V����ό`������
//// ����       �F  LPD3DXBASEMESH io_pMesh     // �ό`�����������b�V��
////            �F  D3DXMATRIX&    i_mMatrix    // �v�Z�Ɏg���s��
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
inline void MeshTransformer(LPD3DXBASEMESH io_pMesh,D3DXMATRIX& i_mMatrix){
	//���_���o��
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;			// ���_�o�b�t�@-
	const DWORD vSize = io_pMesh->GetNumBytesPerVertex();	// ���_�̃o�C�g��
	const DWORD vNum  = io_pMesh->GetNumVertices();		// ���_��
	DWORD fvf   = io_pMesh->GetFVF();				// ���_�t�H�[�}�b�g
	io_pMesh->GetVertexBuffer(&VertexBuffer);		// �o�b�t�@�[�̊l��
	BYTE* Vertex = new BYTE[vSize*vNum];			// �v�Z�p���_�o�b�t�@-
	VertexBuffer->Lock(0,0,(void**)&Vertex,0);		// ���_���b�N

	for(DWORD i = 0 ; i < vNum ; i++){
		FlexibleVertex fvBuf(Vertex+(vSize*i),fvf);
		*fvBuf.pos = MatrixCalculator(i_mMatrix , *fvBuf.pos);
		int dummy ;
		dummy = 1;
	}
	
	VertexBuffer->Unlock();
	//*/
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	/*��*��*��*��*��*��*                                      *��*��*��*��*��*��*/
	/*��*��*��*��*��*��*                                      *��*��*��*��*��*��*/
	/*��*��*��*��*��*��*       �f���[�g ���Ȃ��Ă����́H      *��*��*��*��*��*��*/
	/*��*��*��*��*��*��*                                      *��*��*��*��*��*��*/
	/*��*��*��*��*��*��*                                      *��*��*��*��*��*��*/
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
	/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
}

/////////////////// ////////////////////
//// �֐���     �Finline float Jump(float fHight,float fVTime,float fNowTime)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F
//// ����       �F
////            �F
//// �ߒl       �F
//// �S��       �F
//// ���l       �F
////            �F
////
inline float Jump(float fHight,float fVTime,float fNowTime){
	return ( fHight / pow( fVTime, 2 ) ) * pow( fNowTime - fVTime, 2) + fHight ;
}
/////////////////// ////////////////////
//// �֐���     �Finline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F
//// ����       �F
////            �F
//// �ߒl       �F
//// �S��       �F
//// ���l       �F
////            �F
////
inline float Jump(float fHight,float fVTime,float fOneOldTime,float fNowTime){
	return Jump(fHight,fVTime,fNowTime) - Jump(fHight,fVTime,fOneOldTime);
}
//**************************************************************************
// class __GetClientSize;
//
// �S����  : 
// �p�r    : 
// �@    �@�@
//****************************************************************************/
class __GetClientSize{
	static Rect				m_MainWindowRect;	// �Q�[����ʂ̕`��̈�
public:
	__GetClientSize(Rect& i_Rect){
		m_MainWindowRect = i_Rect ;
	}
	static Rect getSize(){
		return m_MainWindowRect;
	}
};
inline Rect GetClientSize(){
	return __GetClientSize::getSize();
}

/////////////////// ////////////////////
//// �֐���     �Finline void SetRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& i_Param)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�����_�[�ݒ�̏�������
//// ����       �F    const LPDIRECT3DDEVICE9 i_pDevice      //  �f�o�C�X
////            �F    RENDERSTATE_PARAM&      io_Param       //  �����_�[�^�C�v�ƃf�[�^
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �Fio_Param �̒l��ݒ�
////            �F
////
inline void SetRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& i_Param) {
	i_pDevice->SetRenderState(i_Param.renderType,i_Param.value);
};
/////////////////// ////////////////////
//// �֐���     �Finline void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& io_Param)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�����_�[�ݒ�̏��������ƕێ�
//// ����       �F    const LPDIRECT3DDEVICE9 i_pDevice      //  �f�o�C�X
////            �F    RENDERSTATE_PARAM&      io_Param       //  �����_�[�^�C�v�ƃf�[�^
//// �ߒl       �F�Ȃ�(io_Param�ɒl��Ԃ�)
//// �S��       �F���� �O
//// ���l       �Fio_Param �̒l��ݒ�
////            �F���̒l�� io_Param�֑�����ĕԂ�
////
inline void ChangeRenderState(const LPDIRECT3DDEVICE9 i_pDevice, RENDERSTATE_PARAM& io_Param){
	DWORD		dwSaveState;
	i_pDevice->GetRenderState(io_Param.renderType,&dwSaveState);
	i_pDevice->SetRenderState(io_Param.renderType,io_Param.value);
	io_Param.value = dwSaveState;
};

/////////////////// ////////////////////
//// �֐���     �Finline void SetRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* i_pParam)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�����_�[�ݒ�Q�̏�������
//// ����       �F    const LPDIRECT3DDEVICE9 i_pDevice      //  �f�o�C�X
////            �F    RENDERSTATE_PARAM*      i_pParam       //  �����_�[�^�C�v�ƃf�[�^�̔z��
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �Fi_pParam �̍Ō�ɂ͕K�� { D3DRS_FORCE_DWORD , NULL } ���w�肵�Ă�������
////            �F
inline void SetRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* i_pParam){
	if( !i_pParam ) return ;
	for(WORD i = 0 ; i_pParam[i].renderType != D3DRS_FORCE_DWORD ; i++){
		SetRenderState(i_pDevice , i_pParam[i]);
	}
};

/////////////////// ////////////////////
//// �֐���     �Finline void ChangeRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* io_pParam)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�����_�[�ݒ�Q�̏��������ƕێ�
//// ����       �F    const LPDIRECT3DDEVICE9 i_pDevice      //  �f�o�C�X
////            �F    RENDERSTATE_PARAM*      io_Param       //  �����_�[�^�C�v�ƃf�[�^�̔z��
//// �ߒl       �F�Ȃ�(io_pParam�ɒl��Ԃ�)
//// �S��       �F���� �O
//// ���l       �Fio_pParam �̒l��ݒ�
////            �F���̒l�� io_Param�֑�����ĕԂ�
//// ���l       �Fi_pParam �̍Ō�ɂ͕K�� { D3DRS_FORCE_DWORD , NULL } ���w�肵�Ă�������
////            �F
inline void ChangeRenderStateArray(const LPDIRECT3DDEVICE9 i_pDevice,RENDERSTATE_PARAM* io_pParam){
	if( !io_pParam ) return ;
	for(WORD i = 0 ; io_pParam[i].renderType != D3DRS_FORCE_DWORD ; i++){
		ChangeRenderState(i_pDevice , io_pParam[i]);
	}
};


/////////////////// ////////////////////
//// �֐���     �Finline Object* SearchObjectFromID(vector<Object*>* i_pVec,DWORD i_dwID, vector<Object*>* o_pVec = NULL)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �FOBJID�����ɃI�u�W�F�N�g��T��
//// ����       �F    vector<Object*>*   i_pVec     //   [in] �ΏۃI�u�W�F�N�g���i�[����Ă���vector<>�ւ̃|�C���^
////            �F    DWORD              i_dwID     //   [in] �����Ώۂ�ID
////            �F    vector<Object*>*   o_pVec	    //  [out] (Option) ���������I�u�W�F�N�g�ꗗ ( 
//// �ߒl       �F��ԍŏ��ɔ��������I�u�W�F�N�g�ւ̃|�C���^
//// �S��       �F���� �O
//// ���l       �F����SearchObjectFromTypeID�ł������悤�Ȃ��Ƃ͂ł��܂�������SearchObjectFromID�𗘗p���Ă�������
////            �F
////            �F
////            �F
#define SOF_NOTFOUND ( UINT_MAX )
inline Object* SearchObjectFromID(vector<Object*>* i_pVec, DWORD i_dwID, vector<Object*>::size_type* o_Point = NULL, vector<Object*>* o_pVec = NULL, vector<vector<Object*>::size_type>* o_PointList = NULL){
	if( !i_pVec ) return NULL ;
	vector<Object*>::size_type	sz = i_pVec->size(),
								 i = 0 ;

	for( i = 0; i < sz ; i++ ){
		const DWORD id = (*i_pVec)[i]->getID() ;

		//	: ID�ƈ�v����I�u�W�F�N�g�𔭌�
		if( id == i_dwID ) {

			//	: �����q�b�g���X�g��v�����ꂽ��
			//	: ���X�g�ɓo�^���Ď�������
			//	: �Ȃ���Ό������I�u�W�F�N�g��Ԃ�
			if( o_pVec ){
				if( o_PointList ) o_PointList->push_back(i) ;
				o_pVec->size() == 0 && o_Point && ( *o_Point = i ) ;
				(*o_pVec).push_back( (*i_pVec)[i] );
			}
			else{
				o_Point && ( *o_Point = i ) ;
				return  (*i_pVec)[i] ;
			}
		}
	}

	if( o_pVec && o_pVec->size() ){
		return (*o_pVec)[0] ;
	}else{
		o_Point && ( *o_Point = SOF_NOTFOUND ) ;
		return NULL;
	}
};

/////////////////// ////////////////////
//// �֐���     �Finline Object* SearchObjectFromTypeID(vector<Object*>* i_pVec,DWORD i_dwID, vector<Object*>* o_pVec = NULL)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �FOBJID�����ɃI�u�W�F�N�g��T��
//// ����       �F    vector<Object*>*   i_pVec     //   [in] �ΏۃI�u�W�F�N�g���i�[����Ă���vector<>�ւ̃|�C���^
////            �F    DWORD              i_dwID     //   [in] �����Ώۂ�ID
////            �F    vector<Object*>*   o_pVec	    //  [out] (Option) ���������I�u�W�F�N�g�ꗗ ( 
//// �ߒl       �F��ԍŏ��ɔ��������I�u�W�F�N�g�ւ̃|�C���^
//// �S��       �F���� �O
//// ���l       �F
////            �F
////            �F
////            �F
inline Object* SearchObjectFromTypeID(vector<Object*>* i_pVec,const type_info& i_typeinfo, vector<Object*>* o_pVec = NULL){

	vector<Object*>::size_type	sz = i_pVec->size(),
								 i = 0 ;
	for( i = 0; i < sz ; i++ ){
		const type_info& info = typeid( *( *i_pVec )[ i ] );
		if( info == i_typeinfo ) {
			if( o_pVec )
				(*o_pVec).push_back( (*i_pVec)[i] );
			else
				return  (*i_pVec)[i] ;
		}
	}
	if( o_pVec && o_pVec->size() ){
		return (*o_pVec)[0] ;
	}else{
		return NULL;
	}
};



inline D3DCOLORVALUE getD3DCOLORVALUE(float a, float r, float g, float b){
	D3DCOLORVALUE c = { a, r, g, b } ;
	return c ;
}

inline D3DCOLORVALUE COLOR2D3DCOLORVALUE(Color i_Color, float i_fRate = 1.0f){
	
	D3DCOLORVALUE c = {
		(float)i_Color.byteColor.r / (float)UCHAR_MAX ,
		(float)i_Color.byteColor.g / (float)UCHAR_MAX ,
		(float)i_Color.byteColor.b / (float)UCHAR_MAX ,
		(float)i_Color.byteColor.a / (float)UCHAR_MAX
	};
	return c ;
}

inline D3DCOLORVALUE COLOR2DIFFUSE(Color i_Color, float i_fRate = 0.7f){
	return COLOR2D3DCOLORVALUE(i_Color,i_fRate) ;
}

inline D3DCOLORVALUE COLOR2AMBIENT(Color i_Color, float i_fRate = 0.3f){
	return COLOR2D3DCOLORVALUE(i_Color,i_fRate) ;
}
// �X�N���[�����W�����[���h���W�ɕϊ�
inline D3DXVECTOR3* CalcScreenToWorld(
   D3DXVECTOR3* pout,
   int Sx,  // �X�N���[��X���W
   int Sy,  // �X�N���[��Y���W
   float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   // �e�s��̋t�s����Z�o
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}
//�X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o�i CalcScreenToXZ�֐� �j
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
inline D3DXVECTOR3* CalcScreenToXZ(
   D3DXVECTOR3* pout,
   int Sx,
   int Sy,
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // ���Ƃ̌������N���Ă���ꍇ�͌�_��
   // �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
   if( ray.y <= 0 ) {
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}



////////////////////////////////////////
////// Non-environment-dependent ///////
////////////////////////////////////////



///////// /////////
//BOOL ArcMove(float *x ,float *y , float Distance, float Degree);
//
//��_(x,y)����Degree�x,Distance�������ꂽ�Ƃ����
//�|�C���g(x,y)���ړ�������
//
//�����F
//	float *x�F�ړ���������x���W
//	float *y�F�ړ���������y���W
//	float Distance�F
//
inline bool ArcMove( D3DXVECTOR3& Pos , float Distance, float Degree){
    Pos.x = Distance  *  cosf((float)TL_RAD(Degree)) ;
    Pos.y = Distance  *  sinf((float)TL_RAD(Degree)) ;

    return true;
}



///////// /////////
//float TurnAngle(float *Angle, float Turn);
//
//Angle��0���`360���Ɏ��܂�悤��Turn�x���ύX����
//
//�����F
//	float *Angle�F	�ύX���ׂ��f�[�^�ւ̃|�C���^
//	float Turn�F	�ύX�������p�x
//
//�Ԃ�l�F�ύX��̊p�x(�����l���������ɂ��Ԃ����)
//
//�I�[�o�[�h�~�Ɉꉞ
//
inline float TurnAngle(float *Angle, float Turn){
    if(*Angle +Turn >= 360){
        *Angle = (*Angle +Turn)  - 360;		//360�x�𒴂�����
        while(*Angle >= 360) *Angle -= 360;	//�p�x�͈͓̔��Ɏ��܂�悤�Ɉ����������
    }
    else if(*Angle +Turn < 0){
        *Angle = (*Angle +Turn)+360;		//0�x�����������
        while(*Angle <= 0) *Angle += 360;	//�p�x�͈͓̔��Ɏ��܂�悤�Ɉ�����𑫂�
    }else{
        *Angle += Turn;//
    }
    return *Angle;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
inline double TwoPointToBassLength( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	return TL_SQUARE( i_Vec2.x - i_Vec1.x )  + TL_SQUARE( i_Vec2.y - i_Vec1.y ) ;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
inline double VectorLength( D3DXVECTOR3& i_Vec1 ){
	double ret = ( i_Vec1.x * i_Vec1.x ) + ( i_Vec1.y * i_Vec1.y ) ;
	return pow( ret , 0.5 );
}

///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
inline double VectorProduct( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	return i_Vec1.x * i_Vec2.x + i_Vec1.y * i_Vec2.y ;
}
///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
//
inline double GetCosineTheta( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	double buf1 = VectorProduct( i_Vec1 , i_Vec2 ) ;
	double buf2 = VectorLength( i_Vec1 ) ;
	double buf3 = VectorLength( i_Vec2 ) ;
	double ret  = buf1 / ( buf2 * buf3 ) ;
	return ret ;
}
///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
//
inline D3DXVECTOR3 TwoPoint2Vector( D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2 ){
	D3DXVECTOR3 ret ( i_Vec2.x - i_Vec1.x , i_Vec2.y - i_Vec1.y , 0 );
	return  ret ;
}

///////// /////////
//double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y);
//
//�����F
//	double P1x�F�_�P�̂w���W�l
//	double P1y�F�_�P�̂x���W�l
//	double P2x�F�_�Q�̂w���W�l
//	double P2y�F�_�Q�̂x���W�l
//	double P3x�F�_�R�̂w���W�l
//	double P3y�F�_�R�̂x���W�l
//�߂�l�F��P1P2P3�̃��W�A���p
//
inline double ThreePoint2Radian(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2, D3DXVECTOR3& i_Vec3){
	//double vAx , vAy , vBx, vBy ;
	//TwoPoint2Vector( vAx , vAy, P2x, P2y, P1x, P1y);
	//TwoPoint2Vector( vBx , vBy, P2x, P2y, P3x, P3y);
	D3DXVECTOR3 vPosA = TwoPoint2Vector( i_Vec2 , i_Vec1 ) ;
	D3DXVECTOR3 vPosB = TwoPoint2Vector( i_Vec2 , i_Vec3 ) ;
	double buf = GetCosineTheta( vPosA , vPosB ) ;
	double ret = acos( buf );
    return ret ;
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//	float P3x�F�_�R�̂w���W�l
//	float P3y�F�_�R�̂x���W�l
//�߂�l�F��P1P2P3�̃f�B�O���[�p
//
inline float ThreePoint2Degree(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2, D3DXVECTOR3& i_Vec3){
	float ret = (float)TL_DEG(ThreePoint2Radian( i_Vec1, i_Vec2, i_Vec3));
    return ret ;
};


///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//�߂�l�F��P1P2P3�̃��W�A���p
//
inline double TwoPoint2Radian(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2){
	double ret =  ThreePoint2Radian( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) );
    return ret ;
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//�߂�l�F��P1P2P3�̃f�B�O���[�p
//
inline float TwoPoint2Degree(D3DXVECTOR3& i_Vec1, D3DXVECTOR3& i_Vec2){

	float ret = 0 ; 
	if( i_Vec1.y >= i_Vec2.y )
		ret = ThreePoint2Degree( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) ) ;
	else
	    ret = ( 180 - ThreePoint2Degree( i_Vec1, i_Vec2, D3DXVECTOR3( i_Vec2.x + 1 , i_Vec2.y , 0 ) ) ) + 180;
	return ret;
};




///////// /////////
//inline double TwoPointToBassLength( double P1x,double P1y,double P2x,double P2y );
// ���[�g�����O�̓�_�Ԃ̋������v�Z
//
inline double TwoPointToBassLength( double P1x,double P1y,double P2x,double P2y ){
	return TL_SQUARE( P2x - P1x )  + TL_SQUARE( P2y * P1y ) ;
}

///////// /////////
//inline float VectorLength( float X, float Y );
// �x�N�g���̒������v�Z����
//
inline double VectorLength( double X, double Y ){
	return pow( ( X * X ) + ( Y * Y ), 0.5 );
}

///////// /////////
//inline double VectorProduct(double P1x,double P1y,double P2x,double P2y);
// �x�N�g���̓��ς��v�Z����
//
inline double VectorProduct(double P1x,double P1y,double P2x,double P2y){
	return P1x * P2x + P1y * P2y ;
}
///////// /////////
//inline double GetCosineTheta(double P1x,double P1y,double P2x,double P2y);
// �����acos()����Ɗp�x���o��
//
//
inline double GetCosineTheta(double P1x,double P1y,double P2x,double P2y){
	return VectorProduct(P1x,P1y,P2x,P2y) / ( VectorLength(P1x,P1y) * VectorLength(P2x,P2y) ) ;
}
///////// /////////
//inline float ConvertToCartesianCoordinates( float X, float Y );
// �ɍ��W���f�J���g���W�ɕϊ�
//
inline D3DXVECTOR3 ConvertToCartesianCoordinates(float Move, float Direction ){
	float CosBuffer = NULL, SinBuffer = NULL;
	D3DXVECTOR3 Descartes = D3DXVECTOR3(0.0f,0.0f,0.0f);
	CosBuffer = cos(Direction * D3DX_PI / 180.0f);
	SinBuffer = sin(Direction * D3DX_PI / 180.0f);
	Descartes.x = Move * CosBuffer;
	Descartes.y = Move * SinBuffer;
	return 	Descartes;
}
///////// /////////
//inline void TwoPoint2Vector( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y);
// �x�N�g���̒������v�Z����
//
//
inline void TwoPoint2Vector( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y){
	retX = P2x - P1x;
	retY = P2y - P1y;
}
///////// /////////
//inline void TwoPointLength( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y);
// �x�N�g���̒������v�Z����
//
//
inline void TwoPointLength( double &retX, double &retY, double P1x,double P1y,double P2x,double P2y){
	retX = P2x - P1x;
	retY = P2y - P1y;
}

///////// /////////
//double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y);
//
//�����F
//	double P1x�F�_�P�̂w���W�l
//	double P1y�F�_�P�̂x���W�l
//	double P2x�F�_�Q�̂w���W�l
//	double P2y�F�_�Q�̂x���W�l
//	double P3x�F�_�R�̂w���W�l
//	double P3y�F�_�R�̂x���W�l
//�߂�l�F��P1P2P3�̃��W�A���p
//
inline double ThreePoint2Radian(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y){
	double vAx , vAy , vBx, vBy ;
	TwoPoint2Vector( vAx , vAy, P2x, P2y, P1x, P1y);
	TwoPoint2Vector( vBx , vBy, P2x, P2y, P3x, P3y);
    return acos(GetCosineTheta(vAx , vAy , vBx, vBy));
};

///////// /////////
//float ThreePoint2Degree(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//	float P3x�F�_�R�̂w���W�l
//	float P3y�F�_�R�̂x���W�l
//�߂�l�F��P1P2P3�̃f�B�O���[�p
//
inline float ThreePoint2Degree(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y){
    return (float)TL_DEG(ThreePoint2Radian( P1x, P1y, P2x, P2y, P3x, P3y));
};


///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//�߂�l�F��P1P2P3�̃��W�A���p
//
inline double TwoPoint2Radian(double P1x,double P1y,double P2x,double P2y){
    return ThreePoint2Radian( P1x, P1y, P2x, P2y, P2x + 1 , P2y );
};

///////// /////////
//float ThreePoint2Radian(float P1x,float P1y,float P2x,float P2y,float P3x,float P3y);
//
//�����F
//	float P1x�F�_�P�̂w���W�l
//	float P1y�F�_�P�̂x���W�l
//	float P2x�F�_�Q�̂w���W�l
//	float P2y�F�_�Q�̂x���W�l
//�߂�l�F��P1P2P3�̃f�B�O���[�p
//
inline float TwoPoint2Degree(float P1x,float P1y,float P2x,float P2y){
	if( P1y >= P2y )
	    return ThreePoint2Degree( P1x, P1y, P2x, P2y, P2x - 1 , P2y );
	else
	    return ( 180 - ThreePoint2Degree( P1x, P1y, P2x, P2y, P2x - 1 , P2y ) ) + 180;
};


}//end of namespace functions.
using namespace functions ;
}//end of namespace wiz.
