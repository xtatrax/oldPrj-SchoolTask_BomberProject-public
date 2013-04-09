////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FDxDevice.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�O���[�o���Ȋ֐��Q�̃C�����C����`
//					��
//	namespace wiz;
//		class DxException : public exception ;
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

//************************************************//
//class DxException : public exception
//
// �S����  : �Ȃ�(�R�m��搶�̂ЂȌ`���)
// �ړI    : STL��O����h�������N���X
//************************************************//
class DxException : public exception{
    //���b�Z�[�W�ϐ�
    wstring m_Message;
public:
/////////////////// ////////////////////
//// �֐���     �FDxException(const wchar_t* m1,const wchar_t* m2)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�R���X�g���N�^
//// ����       �F  const wchar_t* m1,  //��1���b�Z�[�W
////            �F  const wchar_t* m2   //��2���b�Z�[�W
//// �ߒl       �F���b�Z�[�W������̃|�C���^
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    DxException(const wchar_t* m1,const wchar_t* m2){
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



/////////////////// ////////////////////
//// �֐���     �Finline D3DXVECTOR3 MatrixCalculator(D3DXMATRIX& i_m4x4 , D3DXVECTOR3& i_v1x3)
//// �J�e�S��   �F�O���[�o���֐�
//// �p�r       �F�O�����x�N�g���̍s��ϊ����s��
//// ����       �F  const D3DXMATRIX&  i_m4x4    //  : �v�Z�Ɏg���s��f�[�^
////            �F  const D3DXVECTOR3& i_v1x3    //  : �ϊ������������W�f�[�^
//// �ߒl       �F�ϊ����ꂽ�x�N�g��
//// �S��       �F���� �O
//// ���l       �F�G
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


//**************************************************************************
// class HitTest;
//
// �S����  : ���� �O(�R�m��搶�̂ЂȌ`���)
// �p�r    : �Փ˔���p�̃��[�e�B���e�B
// �@    �@�@static�Ăяo��������
//****************************************************************************/
class HitTest{
/////////////////// ////////////////////
//// �֐���     �Fstatic void ClosestPtPointOBB(const D3DXVECTOR3& point,
////            �F    const OBB& obb, D3DXVECTOR3& retvec)
//// �J�e�S��   �F�ÓI����J�����o�֐�
//// �p�r       �Fpoint���猩��OBB�̍ŋߐړ_�𓾂�
//// ����       �F	const D3DXVECTOR3& point,   // ��_
////            �F  const OBB& obb,             // OBB
////            �F  D3DXVECTOR3& retvec         // �ŋߐړ_��Ԃ��Q��
//// �ߒl       �F�Ȃ��iretvec�ɍŋߐړ_����������j
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
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
public:
	HitTest(){}
	~HitTest(){}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool Sphere_Sphere(const Sphere& sp1,const Sphere& sp2)
//// �J�e�S��   �F�ÓI���J�����o�֐�
//// �p�r       �Fpoint���猩��OBB�̍ŋߐړ_�𓾂�
//// ����       �F  const Sphere& sp1       //���P
////            �F  const Sphere& sp2       //���Q
//// �ߒl       �F�Փ˂��Ă����true
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	static bool Sphere_Sphere(const Sphere& sp1,const Sphere& sp2){
		D3DXVECTOR3 d = sp1.m_Center - sp2.m_Center;
		float dist2 = D3DXVec3Dot(&d,&d);
		float radiussum = sp1.m_Radius + sp2.m_Radius;
		return dist2 <= radiussum * radiussum;
	}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool AABB_OBB(const AABB& aabb,const OBB& obb)
//// �J�e�S��   �F�ÓI���J�����o�֐�
//// �p�r       �FAABB��OBB�Ƃ̏Փ˔���
//// ����       �F  const AABB& aabb   // AABB
////            �F  const OBB&  obb    // OBB
//// �ߒl       �F�Փ˂��Ă����true
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
	static bool AABB_OBB(const AABB& aabb,const OBB& obb){
		D3DXVECTOR3 l = aabb.m_Center - obb.m_Center;
		D3DXVECTOR3 s = aabb.m_Size + obb.m_Size;
		if(fabs(l.x) < s.x && fabs(l.y) < s.y && fabs(l.z) < s.z )
			return true ;
		else
			return false ;

	}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool AABB_AABB(const AABB& aabb,const AABB& obb)
//// �J�e�S��   �F�ÓI���J�����o�֐�
//// �p�r       �FAABB��AABB�Ƃ̏Փ˔���
//// ����       �F  const AABB& aabb1   // AABB
////            �F  const AABB& aabb2   // AABB
//// �ߒl       �F�Փ˂��Ă����true
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
	static bool AABB_AABB(const AABB& aabb1,const AABB& aabb2){
		//if(abs(aabb))
		return false ;
	}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool OBB_Sphere(const Sphere& sp,const OBB& obb,D3DXVECTOR3& retvec)
//// �J�e�S��   �F�ÓI���J�����o�֐�
//// �p�r       �FOBB�Ƌ��Ƃ̏Փ˔���
//// ����       �F  const Sphere& sp		// ��
////            �F  const OBB&    obb		// OBB
////            �F  D3DXVECTOR3&  retvec	// �ŋߐړ_����������Q��
//// �ߒl       �F�Փ˂��Ă����true�iretvec�ɍŋߐړ_����������j
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	static bool OBB_Sphere(const Sphere& sp,const OBB& obb,D3DXVECTOR3& retvec){
        ClosestPtPointOBB(sp.m_Center,obb,retvec);
        D3DXVECTOR3 v = retvec - sp.m_Center;
        return D3DXVec3Dot(&v,&v) <= sp.m_Radius * sp.m_Radius;
	}
/////////////////// ////////////////////
//// �֐���     �Fstatic bool OBB_OBB(const OBB& obb1,const OBB& obb2)
//// �J�e�S��   �F�ÓI���J�����o�֐�
//// �p�r       �FOBB��OBB�Ƃ̏Փ˔���
//// ����       �F  const OBB& obb1
////            �F  const OBB& obb2
//// �ߒl       �F�Փ˂��Ă����true
//// �S��       �F�Ȃ�(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
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
/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F
//// �S��       �F
//// ���l       �FD3DXIntersect
////            �F��P  |  �����Ώۂ̃��b�V��
////            �F��Q  |  �L�����N�^�[�̈ʒu(���C�̊J�n�_)
////            �F��R  |  �L�����N�^�[�̈ړ�����(���C�̕���)
////            �F��S  |  �����������ǂ���
////            �F��T  |  ���C�̊J�n�_�ɍł��߂��ʂ̃C���f�b�N�X�ւ̃|�C���^
////            �F��U  |  �d�S�q�b�g���W �� �ւ̃|�C���^
////            �F��V  |  �d�S�q�b�g���W �� �ւ̃|�C���^
////            �F��W  |  �Փ˒n�_�܂ł̒���
////            �F��X  |  �C���t�H??
////            �F��10  |  9�̔z��
////
	static bool Intersect(
		LPD3DXBASEMESH i_pMesh,
        CONST D3DXVECTOR3 *i_pRayPos,
        CONST D3DXVECTOR3 *i_pRayDir, 
        DWORD   *o_pFaceIndex,        // index of closest face intersected
        FLOAT   *o_pU,                // Barycentric Hit Coordinates    
        FLOAT   *o_pV,                // Barycentric Hit Coordinates
        FLOAT   *o_pDist,             // Ray-Intersection Parameter Distance
        LPD3DXBUFFER *o_ppAllHits,    // Array of D3DXINTERSECTINFOs for all hits (not just closest) 
        DWORD   *o_pCountOfHits)
	{
		BOOL flg = false;
		D3DXIntersect(i_pMesh,i_pRayPos,i_pRayDir,&flg,o_pFaceIndex,o_pU,o_pV,o_pDist,o_ppAllHits,o_pCountOfHits);
		return flg == TRUE;
	}
/////////////////// ////////////////////
//// �֐���     �Fbool GetCollisionJudge(LPD3DXMESH mesh,D3DXVECTOR3 point,D3DXVECTOR3 direction,D3DXMATRIX mat,float distance)
//// �J�e�S��   �F
//// �p�r       �F���ʂ̂��郁�b�V���̓����蔻��
//// ����       �F
//// �ߒl       �F
//// �S��       �F�E����(������)
//// ���l       �F
////            �F�܂��g��Ȃ��ł�������
////
	bool GetCollisionJudge(LPD3DXMESH mesh,D3DXVECTOR3 point,D3DXVECTOR3 direction,D3DXMATRIX mat,float distance){
		float dis;
		BOOL judge;
		D3DXMATRIX matI;
		D3DXMatrixInverse(&matI,NULL,&mat);
		D3DXVECTOR3 pointI,directionI;
		D3DXVec3TransformCoord(&pointI,&point,&matI);
		D3DXVec3TransformCoord(&directionI,&direction,&matI);
		D3DXIntersect(mesh,&pointI,&directionI,&judge,NULL,NULL,NULL,&dis,NULL,NULL);
		if(judge){
			if(dis<distance){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
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
	for(WORD i = 0 ; io_pParam[i].renderType != D3DRS_FORCE_DWORD ; i++){
		ChangeRenderState(i_pDevice , io_pParam[i]);
	}
};

inline Object* SearchObjectFromID(const vector<Object*>* Vec,DWORD i_dwID){

	vector<Object*>::size_type	sz = Vec->size(),
								 i = 0 ;
	for( i = 0; i < sz ; i++ ){
		if( (*Vec)[i]->getID() == i_dwID ) {
			return  (*Vec)[i] ;
		}
	}
	return NULL;
};

}
//end of namespace wiz.
