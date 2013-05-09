////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FBassItems.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
//	�v���~�e�B�u���ӂ��R�m��搶�̃\�[�X���Q�l�ɑ��������! 
//
//	namespace wiz;
//		union Color                :				# DWORD�\�L�J���[���g���₷�����Ă݂�(�g���₷���Ǝv���摽���c)
//		class Camera               : public Object ;		# �J����
//		class Guide                : public Object ;		# �K�C�h���C��
//		class CommonMesh           ;						# ���b�V���������Ƃ��Ɍp������ƕ֗��ȃN���X
//		class MultiCommonMesh      : public CommonMesh ;	# �����悤�ȓ��������قȂ�`��̃��b�V������肽�����Ɍp������ƕ֗��ȃN���X
//		class LoadMeshFromX        : public CommonMesh ;	#
//		class ThinPlate            ;						# �����̂悤�Ȃ��̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveSprite      ;						# 2�����I��UI�����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveBox         : public CommonMesh      ;		# �����̏�̕������Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveMultiBox    : public PrimitiveBox    ;		# �����̎����悤�ȓ�������闧���̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveSphere      : public CommonMesh      ;		# ����̕������Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveMultiSphere : public PrimitiveSphere ;		# �����̎����悤�ȓ�������鋅�̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class BoxObject            : public PrimitiveBox    , public Object          ;		# �ȒP�ȃ{�b�N�X�����N���X
//		class SpriteObject         : public Object          , public PrimitiveSprite ;		# �ȒP�ȃX�v���C�g�����N���X
//
//
#include "StdAfx.h"
#include "BassItems.h"

namespace wiz {

namespace baseitems{

/**************************************************************************
 CommonMesh ����
***************************************************************************/
/**************************************************************************
 ���[�e�B���e�B�֐��istatic�֐��j
****************************************************************************/
/**************************************************************************
 static void PolygonVec2UV(
	float x,	//x�̒l
	float y,	//y�̒l
	float z,	//z�̒l
	float r,	//�|���S���̔��a
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Polygon��Vector����U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::PolygonVec2UV(float x,float y,float z,float r,float& u,float& v){
	u = (x + r ) / (2.0f * r);
	v = 1.0f - (y + r ) / (2.0f * r);
}
/**************************************************************************
 static void CommonMesh::BoxVecNomal2UV(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Box��Vector�Ɩ@������U��V�����o��
 ���ׂĂ̖ʂɓ����e�N�X�`����W�J����ꍇ
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::BoxVecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	if((normal.x < 0 && vec.y > 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z < 0)){
			u = 0;
			v = 0;
	}
	else if((normal.x < 0 && vec.y < 0 &&  vec.z > 0) 
		|| (normal.x > 0 && vec.y < 0 &&  vec.z < 0)
		|| (normal.z < 0 && vec.y < 0 &&  vec.x < 0)
		|| (normal.z > 0 && vec.y < 0 &&  vec.x > 0)
		|| (normal.y > 0 && vec.x < 0 &&  vec.z < 0)
		|| (normal.y < 0 && vec.x < 0 &&  vec.z > 0)){
		u = 0;
		v = 1.0f;
	}
	else if((normal.x < 0 && vec.y > 0 &&  vec.z < 0) 
		|| (normal.x > 0 && vec.y > 0 &&  vec.z > 0)
		|| (normal.z < 0 && vec.y > 0 &&  vec.x > 0)
		|| (normal.z > 0 && vec.y > 0 &&  vec.x < 0)
		|| (normal.y > 0 && vec.x > 0 &&  vec.z > 0)
		|| (normal.y < 0 && vec.x > 0 &&  vec.z < 0)){
		u = 1.0f;
		v = 0.0f;
	}
	else{
		u = 1.0f;
		v = 1.0f;
	}
}

/**************************************************************************
 static void CommonMesh::BoxVecNomal2UV_6_1(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Box��Vector�Ɩ@������U��V�����o��
 �e�N�X�`����1�~6�̉摜�ɂȂ��Ă�ꍇ
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::BoxVecNomal2UV_6_1(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
	float u_prim = 1.0f / 6.0f;
	if(normal.z < 0){ //0��
		if(vec.x < 0 && vec.y > 0 && vec.z < 0){//����
			u = 0.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z < 0){//�E��
			u = u_prim * 1.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z < 0){//�E��
			u = u_prim * 1.0f;
			v = 1.0f;
		}
		else{ //����
			u = 0;
			v = 1.0f;
		}
	}
	if(normal.x > 0){ //1�ʁi�E���ʁj
		if(vec.x > 0 && vec.y > 0 && vec.z < 0){//����
			u = u_prim * 1.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z > 0){//�E��
			u = u_prim * 2.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z > 0){//�E��
			u = u_prim * 2.0f;
			v = 1.0f;
		}
		else{ //����
			u = u_prim * 1.0f;
			v = 1.0f;
		}
	}
	if(normal.z > 0){ //2�ʁi���ʁj
		if(vec.x > 0 && vec.y > 0 && vec.z > 0){//����
			u = u_prim * 2.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y > 0 && vec.z > 0){//�E��
			u = u_prim * 3.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y < 0 && vec.z > 0){//�E��
			u = u_prim * 3.0f;
			v = 1.0f;
		}
		else{ //����
			u = u_prim * 2.0f;
			v = 1.0f;
		}
	}
	if(normal.x < 0){ //3�ʁi�����ʁj
		if(vec.x < 0 && vec.y > 0 && vec.z > 0){//����
			u = u_prim * 3.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y > 0 && vec.z < 0){//�E��
			u = u_prim * 4.0f;
			v = 0.0f;
		}
		else if(vec.x < 0 && vec.y < 0 && vec.z < 0){//�E��
			u = u_prim * 4.0f;
			v = 1.0f;
		}
		else{ //����
			u = u_prim * 3.0f;
			v = 1.0f;
		}
	}
	if(normal.y > 0){ //4�ʁi��ʁj
		if(vec.x < 0 && vec.y > 0 && vec.z > 0){//����
			u = u_prim * 4.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z > 0){//�E��
			u = u_prim * 5.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y > 0 && vec.z < 0){//�E��
			u = u_prim * 5.0f;
			v = 1.0f;
		}
		else{ //����
			u = u_prim * 4.0f;
			v = 1.0f;
		}
	}
	if(normal.y < 0){ //5�ʁi���ʁj
		if(vec.x < 0 && vec.y < 0 && vec.z < 0){//����
			u = u_prim * 5.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z < 0){//�E��
			u = 1.0f; // u_prim * 6.0f;
			v = 0.0f;
		}
		else if(vec.x > 0 && vec.y < 0 && vec.z > 0){//�E��
			u = 1.0f; //u_prim * 6.0f;
			v = 1.0f;
		}
		else{ //����
			u = u_prim * 5.0f;
			v = 1.0f;
		}
	}
}

/**************************************************************************
 static void CommonMesh::SphereVec2UV(
	float x,	//x�̒l
	float y,	//y�̒l
	float z,	//z�̒l
	float r,	//���̔��a
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Sphere��Vector����U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::SphereVec2UV(float x,float y,float z,float r,float& u,float& v){
	float q;
	float q2;
	q = atan2(z,x);
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	q2 = asin(y / r);
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}

/**************************************************************************
 static void CommonMesh::WrapVec2UV(
	float x,	//x�̒l
	float y,	//y�̒l
	float z,	//z�̒l
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v,	//�ϊ�����v�i�e�N�X�`�����V���W�j
	bool IsYWrap = true		//Y���ł���ނ�Z���ł���ނ�
	);
 �p�r: ���b�s���O���ׂ����b�V����Vector����U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::WrapVec2UV(float x,float y,float z,float& u,float& v,bool IsYWrap){
	float q;
	float q2;
	if(IsYWrap){
		q = atan2(z,x);
	}
	else{
		q = atan2(y,x);
	}
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	D3DXVECTOR3 vec(x,y,z);
	FLOAT r = D3DXVec3Length(&vec);
	if(IsYWrap){
		q2 = asin(y / r);
	}
	else{
		q2 = asin(z / r);
	}
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}


/**************************************************************************
 static void CommonMesh::TorusVec2UV(
	float x,	//x�̒l
	float y,	//y�̒l
	float z,	//z�̒l
	float inr,	//�g�[���X�̓��a
	float outr,	//�g�[���X�̊O�a
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Torus��Vector����U��V�����o��
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
void CommonMesh::TorusVec2UV(float x,float y,float z,float inr,float outr,float& u,float& v){
	float q;
	float q2;
	q = atan2(y,x);
	if(q < 0){
		q += 2.0f * D3DX_PI;
	}
	u = q / (2.0f * D3DX_PI);
	//���_����̋������v�Z
	float outr2 = sqrtf(x * x + y * y);
	q2 = acos(z / inr);
	if(outr2 >= outr){
		//�O�`���O��
		q2 = (2 *D3DX_PI) -  q2;
	}
	v = q2 / (D3DX_PI * 2.0f);
	if( u > 1.0f){
		u = 1.0f;
	}
	if( v > 1.0f){
		v = 1.0f;
	}
}
/**************************************************************************
	virtual void CommonMesh::ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void CommonMesh::ReleaseObj(){
    //��n��
    SafeDelete(m_pShadowVolume);
    SafeRelease(m_pMesh);
}


/**************************************************************************
 CommonMesh::CommonMesh();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
CommonMesh::CommonMesh( wiz::OBJID id ):
	Object( id ),
	m_pShadowVolume(0),
	m_pMesh(0),
	m_bWrapMode(true),
	m_bWireFrame(false),
	m_bShadeModeFlat(false)
{
}
/**************************************************************************
 CommonMesh::~CommonMesh();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
CommonMesh::~CommonMesh(){
	ReleaseObj();
}
/**************************************************************************
void CommonMesh::CreateBox(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	D3DXVECTOR3& size,				//�T�C�Y
	bool bTextureActive = false,		//�e�N�X�`�����A�N�e�B�u���ǂ���
	int TexturePtn = PtnUV_1_1	//�e�N�X�`�����L���ȏꍇ�̃p�^�[��
);
 �p�r:Box�I�u�W�F�N�g�̍\�z
 �߂�l: �Ȃ��i��O��throw�j
***************************************************************************/
void CommonMesh::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
   bool bTextureActive,int TexturePtn){
	//�����쐬�ς݂̂Ƃ��̂��߂ɃN���A
	ReleaseObj();
	try{
		//�����̂̍쐬
		//m_Size�̓R���X�g���N�^�Őݒ�ς�
		if(FAILED(D3DXCreateBox(pD3DDevice, 
						size.x,
						size.y,
						size.z,
						&m_pMesh, 
						NULL))){
			// ���������s
			throw BaseException(
				L"Box�̍쐬�Ɏ��s���܂����B",
				L"CommonMesh::CreateBox()"
				);
		}
		//�e�N�X�`��������ꍇ
		if(bTextureActive){
			switch(TexturePtn){
				case PtnUV_YWrap:
				case PtnUV_ZWrap:
					//���b�s���O����
					m_bWrapMode = true;
				break;
				default:
					//PtnUV_1_1,PtnUV_6_1�Ɠ���
					//���b�s���O���Ȃ�
					m_bWrapMode = false;
				break;
			}
			LPD3DXMESH m_pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&m_pMesh2))){
				// ���������s
				throw BaseException(
					L"�e�N�X�`���t��Box�̍쐬�Ɏ��s���܂����B",
					L"CommonMesh::CreateBox()"
					);
			}
			//�������Ƃ̃��b�V���͂���Ȃ��̂ō폜
			SafeRelease(m_pMesh);
			m_pMesh = m_pMesh2;
			m_pMesh2 = 0;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
				//�@���ƒ��_����uv�l�𓾂�
				switch(TexturePtn){
					case PtnUV_1_1:
						BoxVecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
					case PtnUV_6_1:
						BoxVecNomal2UV_6_1(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
					case PtnUV_YWrap:
						WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,pVer[n].tu,pVer[n].tv,true);
					break;
					case PtnUV_ZWrap:
						WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,pVer[n].tu,pVer[n].tv,false);
					break;
					default:
						//PtnUV_1_1�Ɠ���
						BoxVecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
					break;
				}
			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//��n��
		ReleaseObj();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	FLOAT radius,					//���a
	bool bTextureActive = false,		//�e�N�X�`�����A�N�e�B�u���ǂ���
	UINT Slices = 18,	//�厲�̉�]�X���C�X��
	UINT Stacks = 18	//�厲�ɉ������X���C�X��
);
 �p�r:���I�u�W�F�N�g�̍\�z
 �߂�l: �Ȃ��i��O��throw�j
***************************************************************************/
void CommonMesh::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,
	bool bTextureActive,UINT Slices,UINT Stacks){
	//�����쐬�ς݂̂Ƃ��̂��߂ɃN���A
	ReleaseObj();
	try{
		if(radius < 0.0f){
            // ���������s
            throw BaseException(
                L"���̔��a�̎w�肪�͈͊O�ł��B",
                L"CommonMesh::CreateSphere()"
                );
		}
        //���̍쐬
        if(FAILED(D3DXCreateSphere( pD3DDevice, 
                                            radius,
                                            Slices,
                                            Stacks,
                                            &m_pMesh, 
                                            NULL))){
            // ���������s
            throw BaseException(
                L"���̍쐬�Ɏ��s���܂����B",
                L"CommonMesh::CreateSphere()"
                );
        }
		if(bTextureActive){
			//���b�s���O����
			m_bWrapMode = true;
			//�e�N�X�`�����b�V��
			LPD3DXMESH pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// ���������s
				throw BaseException(
					L"�e�N�X�`���t�̋��̍쐬�Ɏ��s���܂����B",
					L"CommonMesh::CreateSphere()"
					);
			}
			//���̒i�K��m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�V�������b�V������
			m_pMesh = pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				float u,v;
				SphereVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,radius,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//��n��
		ReleaseObj();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateTorus(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
    FLOAT InnerRadius,              //�����̔��a�̑傫��
    FLOAT OuterRadius,              //�O���̔��a�̑傫��
	bool bTextureActive = false,		//�e�N�X�`�����A�N�e�B�u���ǂ���
	UINT Sides = 18,	//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT Rings = 18		//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������B 
);
 �p�r:�g�[���X�I�u�W�F�N�g�̍\�z
 �߂�l: �Ȃ��i��O��throw�j
***************************************************************************/
void CommonMesh::CreateTorus(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT InnerRadius,FLOAT OuterRadius,bool bTextureActive,
			UINT Sides,UINT Rings){
	//�����쐬�ς݂̂Ƃ��̂��߂ɃN���A
	ReleaseObj();
	try{
		if(InnerRadius < 0.0f ||
			OuterRadius < 0.0f ||
			Sides < 3 ||
			Rings < 3){
            // ���������s
            throw BaseException(
                L"�g�[���X�̊O�a�A���a�A�T�C�h�A�����O�̎w��̂����ꂩ���͈͊O�ł��B",
                L"CommonMesh::CreateTorus()"
                );
		}
        //�g�[���X�̍쐬
        if(FAILED(D3DXCreateTorus(pD3DDevice, 
                                InnerRadius,
                                OuterRadius,
                                Sides,
                                Rings,
                                &m_pMesh, 
                                NULL))){
            // ���������s
            throw BaseException(
                L"�g�[���X�̍쐬�Ɏ��s���܂����B",
                L"CommonMesh::CreateTorus()"
                );
        }
		if(bTextureActive){
			//���b�s���O����
			m_bWrapMode = true;
			//�e�N�X�`�����b�V��
			LPD3DXMESH pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// ���������s
				throw BaseException(
					L"�e�N�X�`���t�̃g�[���X�̍쐬�Ɏ��s���܂����B",
					L"CommonMesh::CreateTorus()"
					);
			}
			//���̒i�K��m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�V�������b�V������
			m_pMesh = pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				float u,v;
				TorusVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,InnerRadius,OuterRadius,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//��n��
		ReleaseObj();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreateCylinder(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
    FLOAT Radius1,					//z ���̕��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B 
    FLOAT Radius2,					//z ���̐��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B
	FLOAT Length,					//z �������̉~���̒����B
	bool bTextureActive = false,	//�e�N�X�`�����A�N�e�B�u���ǂ���
	UINT Slices = 18,				//�厲����]���Ƃ����X���C�X�̐��B
	UINT Stacks = 18				//�厲�ɉ������X�^�b�N���B  
);
 �p�r:�V�����_�[�I�u�W�F�N�g�̍\�z
 �߂�l: �Ȃ��i��O��throw�j
***************************************************************************/
void CommonMesh::CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
			FLOAT Radius1,FLOAT Radius2,FLOAT Length,bool bTextureActive,
			UINT Slices,UINT Stacks){
	//�����쐬�ς݂̂Ƃ��̂��߂ɃN���A
	ReleaseObj();
	try{
		if(Radius1 < 0.0f ||
			 Radius2 < 0.0f){
            // ���������s
            throw BaseException(
                L"�V�����_�[�̔��a�w��̂����ꂩ���͈͊O�ł��B",
                L"CommonMesh::CreateCylinder()"
                );
		}
        //�V�����_�[�̍쐬
        if(FAILED(D3DXCreateCylinder(pD3DDevice, 
                                Radius1,
                                Radius2,
								Length,
                                Slices,
                                Stacks,
                                &m_pMesh, 
                                NULL))){
            // ���������s
            throw BaseException(
                L"�V�����_�[�̍쐬�Ɏ��s���܂����B",
                L"CommonMesh::CreateCylinder()"
                );
        }
		if(bTextureActive){
			//���b�s���O����
			m_bWrapMode = true;
			//�e�N�X�`�����b�V��
			LPD3DXMESH pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// ���������s
				throw BaseException(
					L"�e�N�X�`���t�̃V�����_�[�̍쐬�Ɏ��s���܂����B",
					L"CommonMesh::CreateCylinder()"
					);
			}
			//���̒i�K��m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�V�������b�V������
			m_pMesh = pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				float u,v;
				WrapVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,u,v,false);
				pVer[n].tu = u;
				pVer[n].tv = v;
			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//��n��
		ReleaseObj();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
void CommonMesh::CreatePolygon(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	FLOAT Length,					//�e�ʂ̒����B
	UINT Sides,						//�|���S���̖ʐ��B�l�� 3 �ȏ�ł���K�v������B
	bool bTextureActive = false,	//�e�N�X�`�����A�N�e�B�u���ǂ���
);
 �p�r:�|���S���I�u�W�F�N�g�̍\�z
 �߂�l: �Ȃ��i��O��throw�j
***************************************************************************/
void CommonMesh::CreatePolygon(LPDIRECT3DDEVICE9 pD3DDevice,
	   FLOAT Length,UINT Sides,bool bTextureActive){
	//�����쐬�ς݂̂Ƃ��̂��߂ɃN���A
	ReleaseObj();
	try{
		if(Sides < 0){
            // ���������s
            throw BaseException(
                L"�|���S���̖ʐ����͈͊O�ł��B",
                L"CommonMesh::CreatePolygon()"
                );
		}
        //�|���S���̍쐬
        if(FAILED(D3DXCreatePolygon(pD3DDevice, 
                                Length,
                                Sides,
                                &m_pMesh, 
                                NULL))){
            // ���������s
            throw BaseException(
                L"�|���S���̍쐬�Ɏ��s���܂����B",
                L"CommonMesh::CreatePolygon()"
                );
        }
		if(bTextureActive){
			//���b�s���O���Ȃ�
			m_bWrapMode = false;
			//�e�N�X�`�����b�V��
			LPD3DXMESH pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,CommonMeshFVF,pD3DDevice,&pMesh2))){
				// ���������s
				throw BaseException(
					L"�e�N�X�`���t�̃|���S���̍쐬�Ɏ��s���܂����B",
					L"CommonMesh::CreatePolygon()"
					);
			}
			//���̒i�K��m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�V�������b�V������
			m_pMesh = pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			CommonMeshVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			//1��ڂ̃p�X�ŁA�|���S���̔��a���v�Z����
			FLOAT r = 0;
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				D3DXVECTOR3 vec(pVer[n].vec.x,pVer[n].vec.y,0);
				FLOAT r2 = D3DXVec3Length(&vec);
				if(r < r2){
					r = r2;
				}
			}
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				float u,v;
				PolygonVec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,r,u,v);
				pVer[n].tu = u;
				pVer[n].tv = v;

			}
			pVB->Unlock();
		}
		//�e�{�����[�����쐬
		m_pShadowVolume = new ShadowVolume(pD3DDevice,m_pMesh);
	}
	catch(...){
		//��n��
		ReleaseObj();
		//�ăX���[
		throw;
	}
}

/////////////////// ////////////////////
//// �֐���     �Fvoid CommonMesh::Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  
//// �ߒl       �F����
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ȃ�ׂ����̊֐��͎g�킸 DrawCommonMesh �֐����g���悤�ɂ��Ă�������
////            �F
////
void CommonMesh::Draw(DrawPacket& i_DrawPacket) {
    //�����`�F�b�N
    if((!m_pMesh) || (!i_DrawPacket.pD3DDevice)){
        throw BaseException(L"�f�o�C�X�����b�V���������ł��B",
        L"CommonMesh::Draw()");
    }
    if(m_Material.Diffuse.a < 1.0f){
        //�����A�����x��1.0�����Ȃ�
        // �A���t�@�����̐ݒ�
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    }
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //�����A�X�y�L�����[���ݒ肵�Ă�����
        // �X�y�L�����[�L���̐ݒ�
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
    }
    // �}�e���A���������_�����O�p�C�v���C���ɐݒ�
    i_DrawPacket.pD3DDevice->SetMaterial( &m_Material);
    //�`��
    m_pMesh->DrawSubset(0);
    if(m_Material.Specular.r > 0.0f
        || m_Material.Specular.g > 0.0f
        || m_Material.Specular.b > 0.0f)
    {
        //�����A�X�y�L�����[���ݒ肵�Ă�����
        // �X�y�L�����[�����ɖ߂�
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
    }
    if(m_Material.Diffuse.a < 1.0f){
        //�����A�����x��1.0�����Ȃ�
        // �A���t�@���������ɖ߂�
        i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    }
}


/**************************************************************************
 void CommonMesh::DrawCommonMesh(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXMATRIX& Matrix,				//�ϊ��s��
	D3DMATERIAL9& Material,			//�}�e�B���A��
	LPDIRECT3DTEXTURE9 pTexture = 0			//�e�N�X�`��
 );
 �p�r: �R�����I�u�W�F�N�g��`��i�h���N���X����Ă΂��j
 �߂�l: �Ȃ��B
***************************************************************************/
 void CommonMesh::DrawCommonMesh(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& Matrix,
	 D3DMATERIAL9& Material,LPDIRECT3DTEXTURE9 pTexture){
    //�����`�F�b�N
    if((!m_pMesh) || (!pD3DDevice)){
		return;
    }
	//�e�N�X�`��������ꍇ
	DWORD wkRap;
	DWORD wkdword;
	if(pTexture){
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//���b�s���O���邩�ǂ���
		if(m_bWrapMode){
			pD3DDevice->GetRenderState(D3DRS_WRAP0,&wkRap);
			//�e�N�X�`���\��t���ŁA0.0��1.0���������Ă���ꍇ�Ƀ��b�s���O���u0�v�̒l�ɂ���
			//D3DWRAPCOORD_0 == u����,D3DWRAPCOORD_1 == v����
			pD3DDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0 | D3DWRAPCOORD_1 );
		}
		//�X�e�[�W�̐ݒ�
		pD3DDevice->SetTexture(0,pTexture);
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetFVF(CommonMeshFVF);
	}
	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &Matrix);
	if(Material.Diffuse.a < 1.0f){
		//�����A�����x��1.0�����Ȃ�
		// �A���t�@�����̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	if(Material.Specular.r > 0.0f
		|| Material.Specular.g > 0.0f
		|| Material.Specular.b > 0.0f)
	{
		//�����A�X�y�L�����[���ݒ肵�Ă�����
		// �X�y�L�����[�L���̐ݒ�
		pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 1);
	}
	//�}�e���A���������_�����O�p�C�v���C���ɐݒ�
	pD3DDevice->SetMaterial(&Material);
	//���C�A�t���[�����ǂ���
	if(m_bWireFrame){
		pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	}
	//����ȊO
	else{
		pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID );
	}
	//�V�F�[�h���[�h
	if(m_bShadeModeFlat){
		//�t���b�g �V�F�[�f�B���O ���[�h
		pD3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT );
	}
	else{
		//�O�[���[ �V�F�[�f�B���O ���[�h
		pD3DDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD );
	}

	//�`��
	m_pMesh->DrawSubset(0);

	if(Material.Specular.r > 0.0f
		|| Material.Specular.g > 0.0f
		|| Material.Specular.b > 0.0f)
	{
		//�����A�X�y�L�����[���ݒ肵�Ă�����
		// �X�y�L�����[�����ɖ߂�
		pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, 0);
	}
	if(Material.Diffuse.a < 1.0f){
		//�����A�����x��1.0�����Ȃ�
		// �A���t�@���������ɖ߂�
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
	}
	if(pTexture){
		//�����e�N�X�`���ݒ肳��Ă�����
		pD3DDevice->SetTexture(0,0);
		if(m_bWrapMode){
			//���b�s���O�����ɖ߂�
			pD3DDevice->SetRenderState(D3DRS_WRAP0,wkRap);
		}
		//�X�e�[�W�����ɖ߂�
		pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
}

/**************************************************************************
	void CommonMesh::DrawCommonShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXMATRIX& AllMatrix,				//�I�u�W�F�N�g�̕ϊ��s��
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j�h���N���X����Ă΂��
 �߂�l: �Ȃ��B
***************************************************************************/
void CommonMesh::DrawCommonShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& AllMatrix,
	LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(m_pShadowVolume){
		//�I�u�W�F�N�g�̃��[���h�s����J���������ɂ��ēo�^
		D3DXMATRIX WorldView;
		WorldView =  AllMatrix * mCameraView;
		pEffect->SetMatrix("g_mWorldView",&WorldView);
		//�J�����̃v���W�F�N�g�܂Ŋ܂񂾍s���o�^
		WorldView = WorldView * mCameraProj;
		pEffect->SetMatrix("g_mWorldViewProjection",&WorldView);
		//�e�{�����[���̕`��
		m_pShadowVolume->Draw(pD3DDevice,pEffect);
	}
}

/**************************************************************************
 class MultiCommonMesh : public CommonMesh;
 �p�r: �����̃R�������b�V���N���X
****************************************************************************/
/**************************************************************************
 virtual void MultiCommonMesh::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::Clear(){
	//�A�C�e���z��̃N���A
	SafeDeletePointerContainer(m_ItemVec);
}
/**************************************************************************
 MultiCommonMesh::MultiCommonMesh(
	bool IsTextureActive = false	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
 ���R���X�g���N�^�ł́A�e�N�X�`�����g�p���邩���Ȃ����w�肷��
***************************************************************************/
MultiCommonMesh::MultiCommonMesh( wiz::OBJID id , bool IsTextureActive )
:CommonMesh( id ),m_IsTextureActive(IsTextureActive)
{
	//�������Ȃ�
}
/**************************************************************************
 virtual MultiCommonMesh::~MultiCommonMesh();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiCommonMesh::~MultiCommonMesh(){
	//��n��
	Clear();
}
/**************************************************************************
 virtual size_t MultiCommonMesh::AddItem(
    D3DXVECTOR3& Scale,               //�X�P�[���i�g��k���̔{���j
    D3DXVECTOR3& Pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& Rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0			//�e�N�X�`��
    );
 �p�r: �A�C�e����ǉ�
 �߂�l: �ǉ������C���f�b�N�X�i���s���͗�O��throw�j
***************************************************************************/
size_t MultiCommonMesh::AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,
		 D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		 bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture){
	CommonItem* pItem = 0;
	try{
		if(m_IsTextureActive){
			if(!pTexture){
				throw BaseException(L"MultiCommonMesh�Ƀe�N�X�`�����K�v�ł����A�w�肳��Ă܂���",
					L"MultiCommonMesh::AddItem()");
			}
		}
		else{
			if(pTexture){
				throw BaseException(L"MultiCommonMesh�Ƀe�N�X�`���͕s�v�ł����A�w�肳��Ă��܂�",
					L"MultiCommonMesh::AddItem()");
			}
		}
		pItem = new CommonItem;
		//�����l�͗L��
		pItem->m_IsActive = true;
		// D3DMATERIAL9�\���̂�0�ŃN���A
		::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
		pItem->m_Material.Diffuse = Diffuse;
		pItem->m_Material.Specular = Specular;
		pItem->m_Material.Ambient = Ambient;
		pItem->m_BaseScale = Scale;
		pItem->m_BasePos = Pos;
		pItem->m_Pos = D3DXVECTOR3(0,0,0);
		//�N�I�[�^�j�I���̏�����
		D3DXQuaternionIdentity(&pItem->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		D3DXQuaternionIdentity(&pItem->m_Qt);
		//�s��̏�����
		D3DXMatrixIdentity(&pItem->m_WorldMatrix);
		//�g��k���p
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			pItem->m_BaseScale.x,pItem->m_BaseScale.y,pItem->m_BaseScale.z);
		//���[�J����]�p
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//���[�J����]
		D3DXMatrixRotationQuaternion(&mtRot,&pItem->m_BaseQt);
		//���[�J���ړ��p
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,pItem->m_BasePos.x,pItem->m_BasePos.y,pItem->m_BasePos.z);

		//���Ή�]�p
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//���Ή�]
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&pItem->m_Qt);

		//���Έړ��p
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//���Έړ�
		D3DXMatrixTranslation(&mtOffsetPos,pItem->m_Pos.x,pItem->m_Pos.y,pItem->m_Pos.z);
		//���ׂă~�b�N�X�s������[���h�s��ɐݒ�
		pItem->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
		//�e��`�悷�邩�ǂ���
		pItem->m_IsShadowActive = IsShadowActive;
		//�e�N�X�`��
		pItem->m_pTexture = pTexture;
		//�A�C�e���̒ǉ�
		size_t ret = m_ItemVec.size();
		m_ItemVec.push_back(pItem);
		//�ǉ������C���f�b�N�X�͒��O�̍��ڐ��ɂȂ�
		return ret;
	}
	catch(...){
		SafeDelete(pItem);
		Clear();
		throw;
	}
}


/**************************************************************************
�@size_t MultiCommonMesh::GetActiveItemCount();
 �p�r: ���݂̗L���ȃA�C�e�����𓾂�
 �߂�l: �A�C�e����
***************************************************************************/
size_t MultiCommonMesh::GetActiveItemCount(){
	size_t ret = 0;
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		if(m_ItemVec[i]->m_IsActive){
			ret++;
		}
	}
	return ret;
}

/**************************************************************************
bool MultiCommonMesh::IsActiveItem(
size_t Index	//�擾�������C���f�b�N�X
);
 �p�r: �w�肵���C���f�b�N�X�̃A�C�e�����L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE�A�C���f�b�N�X���͈͈ȊO�Ȃ��O
***************************************************************************/
bool MultiCommonMesh::IsActiveItem(size_t Index){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_IsActive;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::IsActiveItem()");
	}
	return false;
}

/**************************************************************************
void MultiCommonMesh::SetActiveItem(
size_t Index,	//�Z�b�g�������C���f�b�N�X
bool val		//�������������l�itrue��false�j
);
 �p�r: �w�肵���C���f�b�N�X�̃A�C�e�����L�����ǂ�����ݒ肷��
 �߂�l: �Ȃ��A�C���f�b�N�X���͈͈ȊO�Ȃ��O
***************************************************************************/
void MultiCommonMesh::SetActiveItem(size_t Index,bool val){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_IsActive = val;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetActiveItem()");
	}
}
/**************************************************************************
 void MultiCommonMesh::CopyItem(
	 CommonItem* Dest,	//�R�s�[��
	 size_t Index		//�R�s�[���̃A�C�e���̃C���f�b�N�X
 );
 �p�r:�A�C�e���̃R�s�[
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::CopyItem(CommonItem* Dest,size_t Index){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz && Dest){
		//�R�s�[
		*Dest = *m_ItemVec[Index];
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O���R�s�[�悪�s��ł��B",
			L"MultiCommonMesh::CopyItem()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemMaterial(
	size_t Index,	//�擾����C���f�b�N�X
	D3DMATERIAL9& Material	//���݂̃}�e���A��
  );
 �p�r: �}�e���A�����擾����
 �߂�l: �Ȃ��iMaterial��Index�̃}�e���A����Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Material = m_ItemVec[Index]->m_Material;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemMaterial()");
	}
}

/**************************************************************************
 void MultiCommonMesh::SetItemMaterial(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
  );
 �p�r: �}�e���A����ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Material = Material;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemMaterial()");
	}
}


/**************************************************************************
bool MultiCommonMesh::IsTextureActive();
 �p�r: �e�N�X�`�����L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
 ���e�C���f�b�N�X�̃e�N�X�`����ύX����ꍇ�́A��ɗL�����ǂ����������邱��
***************************************************************************/
bool MultiCommonMesh::IsTextureActive(){
	return m_IsTextureActive;
}
/**************************************************************************
 LPDIRECT3DTEXTURE9 MultiCommonMesh::GetItemTexture(
	size_t Index	//�擾����C���f�b�N�X
  );
 �p�r: �e�N�X�`�����擾����
 �߂�l: ���݂̃e�N�X�`���i�Ȃ��ꍇ��0���Ԃ�j
***************************************************************************/
LPDIRECT3DTEXTURE9 MultiCommonMesh::GetItemTexture(size_t Index){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_pTexture;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemTexture()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemTexture(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	LPDIRECT3DTEXTURE9 pTexture	//�ݒ肷��e�N�X�`��
  );
 �p�r: �e�N�X�`����ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemTexture(size_t Index,LPDIRECT3DTEXTURE9 pTexture){
	if(m_IsTextureActive){
		//�e�N�X�`�����L���Ȃ�0�͐ݒ�ł��Ȃ�
		if(!pTexture){
			throw BaseException(L"���̃I�u�W�F�N�g�̓e�N�X�`�����K�v�ł��B",
				L"MultiCommonMesh::SetItemTexture()");
		}
	}
	else{
		//�e�N�X�`���������Ȃ�0�ȊO�͐ݒ�ł��Ȃ�
		if(pTexture){
			throw BaseException(L"���̃I�u�W�F�N�g�̓e�N�X�`����ݒ�ł��܂���B",
				L"MultiCommonMesh::SetItemTexture()");
		}
	}

    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_pTexture = pTexture;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemTexture()");
	}
}

/**************************************************************************
bool MultiCommonMesh::IsShadowActiveItem(
size_t Index	//�擾�������C���f�b�N�X
);
 �p�r: �w�肵���C���f�b�N�X�̉e���L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE�A�C���f�b�N�X���͈͈ȊO�Ȃ��O
***************************************************************************/
bool MultiCommonMesh::IsShadowActiveItem(size_t Index){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		return m_ItemVec[Index]->m_IsShadowActive;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::IsShadowActiveItem()");
	}
}

/**************************************************************************
void MultiCommonMesh::SetShadowActiveItem(
size_t Index,	//�Z�b�g�������C���f�b�N�X
bool val		//�������������l�itrue��false�j
);
 �p�r: �w�肵���C���f�b�N�X�̉e���L�����ǂ�����ݒ肷��
 �߂�l: �Ȃ��A�C���f�b�N�X���͈͈ȊO�Ȃ��O
***************************************************************************/
void MultiCommonMesh::SetShadowActiveItem(size_t Index,bool val){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_IsShadowActive = val;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetShadowActiveItem()");
	}
}


/**************************************************************************
 void MultiCommonMesh::GetItemWorldPos(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos	//���݂̃��[���h�ʒu
  );
 �p�r: ���[���h�ʒu���擾����
 �߂�l: �Ȃ��iPos��Index�̃��[���h�ʒu��Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemWorldPos(size_t Index,D3DXVECTOR3& Pos){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_BasePos
			+ m_ItemVec[Index]->m_Pos;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorldPos()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Rot	//���݂̃��[���h��]
  );
 �p�r: ���[���h��]���擾����
 �߂�l: �Ȃ��iRot��Index�̃��[���h��]��Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemWorldRot(size_t Index,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//��]
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//Qt����Rot�ɕϊ�
		Math::QtToRot(Qt,Rot);

	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorldRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXQUATERNION& Qt	//���݂̃��[���h��]
  );
 �p�r: ���[���h��]���擾����
 �߂�l: �Ȃ��iQt��Index�̃��[���h��]��Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemWorldQt(size_t Index,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//��]
		Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);

	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorldQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldScale(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale	//���݂̃��[���h�X�P�[��
  );
 �p�r: ���[���h�X�P�[�����擾����
 �����̊֐���GetItemBaseScale�֐��Ɠ���
 �߂�l: �Ȃ��iScale��Index�̃��[���h��]��Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemWorldScale(size_t Index,D3DXVECTOR3& Scale){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�X�P�[�����O��Base�̂ݑ��݂���̂ŁABase�̒l��Ԃ�
		Scale = m_ItemVec[Index]->m_BaseScale;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorldScale()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorld(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//���݂̃��[���h�X�P�[��
	D3DXVECTOR3& Pos,	//���݂̃��[���h�ʒu
	D3DXVECTOR3& Rot,	//���݂̃��[���h��]�i�I�C���[�e�j
	D3DXQUATERNION& Qt	//���݂̃��[���h��]�i�N�I�[�^�j�I���j
  );
 �p�r: ���ׂẴ��[���h�l���擾����
 �߂�l: �Ȃ��i�Q�Ƃ�Index�̃��[���h�l��Ԃ��j
***************************************************************************/
void MultiCommonMesh::GetItemWorld(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�X�P�[�����O��Base�̂ݑ��݂���̂ŁABase�̒l��Ԃ�
		Scale = m_ItemVec[Index]->m_BaseScale;
		//�ʒu
		Pos = m_ItemVec[Index]->m_BasePos
			+ m_ItemVec[Index]->m_Pos;
		//��]
		Qt = m_ItemVec[Index]->m_Qt * m_ItemVec[Index]->m_BaseQt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//Qt����Rot�ɕϊ�
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorld()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemWorldMatrix(
	size_t Index,_	//�擾����C���f�b�N�X
	D3DXMATRIX& mtWorld	//�擾����s��
 );
 �p�r:���[���h�ϊ����擾����
 �߂�l: �Ȃ��BmtWorld�ɕϊ��s����Z�b�g����
***************************************************************************/
void MultiCommonMesh::GetItemWorldMatrix(size_t Index,D3DXMATRIX& mtWorld){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		mtWorld = m_ItemVec[Index]->m_WorldMatrix;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemWorldMatrix()");
	}
}
/**************************************************************************
 void MultiCommonMesh::CalcWorldMatrix();
 �p�r:���ׂẴA�C�e���̃��[���h�ϊ����v�Z����
 �߂�l: �Ȃ��B���݂̕ϊ������ƂɃ��[���h�s����v�Z����
***************************************************************************/
void MultiCommonMesh::CalcWorldMatrix(){
    //�z�u�I�u�W�F�N�g�̍s��̐ݒ�
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//��A�N�e�B�u�Ȃ�v�Z���Ȃ�
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//�g��k���p
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_ItemVec[i]->m_BaseScale.x,m_ItemVec[i]->m_BaseScale.y,m_ItemVec[i]->m_BaseScale.z);
		//���[�J����]�p
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//���[�J����]
		D3DXMatrixRotationQuaternion(&mtRot,&m_ItemVec[i]->m_BaseQt);
		//���[�J���ړ��p
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_ItemVec[i]->m_BasePos.x,m_ItemVec[i]->m_BasePos.y,m_ItemVec[i]->m_BasePos.z);

		//���Ή�]�p
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//���Ή�]
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_ItemVec[i]->m_Qt);

		//���Έړ��p
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//���Έړ�
		D3DXMatrixTranslation(&mtOffsetPos,m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);

		//���ׂă~�b�N�X�s������[���h�s��ɐݒ�
		D3DXMatrixIdentity(&m_ItemVec[i]->m_WorldMatrix);
		m_ItemVec[i]->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
    }
}


/**************************************************************************
 void MultiCommonMesh::GetItemLocalPos(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos	//���݂̑��Έʒu
  );
 �p�r: ���Έʒu���擾����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemLocalPos(size_t Index,D3DXVECTOR3& Pos){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�ʒu
		Pos = m_ItemVec[Index]->m_Pos;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemLocalPos()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Rot	//���݂̉�]
  );
 �p�r: ���Ή�]���擾����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemLocalRot(size_t Index,D3DXVECTOR3& Rot){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//��]
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//Qt����Rot�ɕϊ�
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemLocalRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
  );
 �p�r: ���Ή�]���擾����i�N�I�[�^�j�I���Łj
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemLocalQt(size_t Index,D3DXQUATERNION& Qt){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//��]
		Qt = m_ItemVec[Index]->m_Qt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemLocalQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalPosQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
  );
 �p�r: ���Βl���擾����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemLocalPosQt(size_t Index,
		D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_Pos;
		Qt = m_ItemVec[Index]->m_Qt;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemLocalPosQt()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemLocalPosRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
  );
 �p�r: ���Βl���擾����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemLocalPosRot(size_t Index,
	 D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Pos = m_ItemVec[Index]->m_Pos;
		//��]
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_Qt;
		//���K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//Qt����Rot�ɕϊ�
		Math::QtToRot(Qt,Rot);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetItemLocalPosRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::SetItemLocalPosQt(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
  );
 �p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�ʒu
		m_ItemVec[Index]->m_Pos = Pos;
		//��]
		m_ItemVec[Index]->m_Qt = Qt;
		//���K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemLocalPosQ()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemLocalPosRot(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//��]
  );
 �p�r: ���Βl��ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemLocalPosRot(size_t Index,
	D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	//�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
	size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�ʒu
		m_ItemVec[Index]->m_Pos = Pos;
		//��]
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//���K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemLocalPosQ()");
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveToPosRot(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXVECTOR3& Rot	//��������]
  );
 �p�r: ���Βl���ړ�����]����
 *���ׂẴI�u�W�F�N�g�ɓK�p�����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	D3DXQUATERNION Qt;
	D3DXQuaternionIdentity(&Qt);
	D3DXQuaternionRotationYawPitchRoll(&Qt,
		Rot.y,Rot.x,Rot.z);
    //�z�u�I�u�W�F�N�g�ւ̓K�p
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos += Pos;
		m_ItemVec[i]->m_Qt *= Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveToPosQt(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXQUATERNION& Qt	//��������]
  );
 �p�r: ���Βl���ړ�����]����(�N�I�[�^�j�I����)
 *���ׂẴI�u�W�F�N�g�ɓK�p�����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�z�u�I�u�W�F�N�g�ւ̓K�p
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos += Pos;
		m_ItemVec[i]->m_Qt *= Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}



/**************************************************************************
 void MultiCommonMesh::MoveToItemPosRot(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
  );
 �p�r: �w��̃����o�̑��Βl���ړ�����]����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveToItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos += Pos;
		D3DXQUATERNION Qt;
		D3DXQuaternionIdentity(&Qt);
		D3DXQuaternionRotationYawPitchRoll(&Qt,
			Rot.y,Rot.x,Rot.z);
		m_ItemVec[Index]->m_Qt *= Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::MoveToItemPosRot()");
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveToItemPosQt(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//��������]
  );
 �p�r: �w��̃����o�̑��Βl���ړ�����]����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveToItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos += Pos;
		m_ItemVec[Index]->m_Qt *= Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::MoveToItemPosQt()");
	}
}


/**************************************************************************
 void MultiCommonMesh::MoveAtPosRot(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
  );
 �p�r: ���Βu���Z�b�g����
 *���ׂẴI�u�W�F�N�g�ɓK�p�����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�z�u�I�u�W�F�N�g�ւ̓K�p
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[i]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[i]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtPosQt(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
  );
 �p�r: ���Βu���Z�b�g����(�N�I�[�^�j�I����)
 *���ׂẴI�u�W�F�N�g�ɓK�p�����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�z�u�I�u�W�F�N�g�ւ̓K�p
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = Pos;
		m_ItemVec[i]->m_Qt = Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[i]->m_Qt,&m_ItemVec[i]->m_Qt);
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtItemPosRot(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
  );
 �p�r: �w��̃����o�̑��Βu���Z�b�g����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::MoveAtItemPosRot()");
	}
}

/**************************************************************************
 void MultiCommonMesh::MoveAtItemPosQt(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
  );
 �p�r: �w��̃����o�̑��Βu���Z�b�g����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = Pos;
		m_ItemVec[Index]->m_Qt = Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::MoveAtItemPosQt()");
	}
}



/**************************************************************************
 void MultiCommonMesh::MoveAtIdentity();
 �p�r: �ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
 *���ׂẴI�u�W�F�N�g�ɓK�p�����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtIdentity(){
    //�z�u�I�u�W�F�N�g�ւ̓K�p
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		m_ItemVec[i]->m_Pos = D3DXVECTOR3(0,0,0);
		D3DXQuaternionIdentity(&m_ItemVec[i]->m_Qt);
	}
}
/**************************************************************************
 void MultiCommonMesh::MoveAtItemIdentity(
	size_t Index	//�ω�������C���f�b�N�X
 );
 �p�r: �w��̃����o�̍ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::MoveAtItemIdentity(size_t Index){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Pos = D3DXVECTOR3(0,0,0);
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::MoveAtItemIdentity()");
	}
}

/**************************************************************************
 void MultiCommonMesh::GetItemBaseScalePosRot(
	size_t Index,		//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXVECTOR3& Rot	//�x�[�X��]�̎Q��
  );
 �p�r: �w��̃C���f�b�N�X�̃x�[�X�̃X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o��
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemBaseScalePosRot(size_t Index,
	 D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Scale = m_ItemVec[Index]->m_BaseScale;
		Pos = m_ItemVec[Index]->m_BasePos;
		D3DXQUATERNION Qt;
		//���݂̃x�[�X�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&Qt,&m_ItemVec[Index]->m_BaseQt);
		//Qt����Rot�ɕϊ�
		Math::QtToRot(Qt,Rot);

	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetBaseScalePosRot()");
	}
}


/**************************************************************************
 void MultiCommonMesh::GetItemBaseScalePosQt(
	size_t Index,		//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXQUATERNION& Qt	//�x�[�X��]�N�I�[�^�j�I���̎Q��
  );
 �p�r: �w��̃C���f�b�N�X�̃x�[�X�̃X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o���i�N�I�[�^�j�I���Łj
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::GetItemBaseScalePosQt(size_t Index,
				D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		Scale = m_ItemVec[Index]->m_BaseScale;
		Pos = m_ItemVec[Index]->m_BasePos;
		Qt = m_ItemVec[Index]->m_BaseQt;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::GetBaseScalePosQt()");
	}
}


/**************************************************************************
 void MultiCommonMesh::SetItemBaseScale(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale	//�V�����x�[�X�X�P�[�����O
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBaseScale(size_t Index,D3DXVECTOR3& Scale){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBaseScale()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBasePos(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Pos	//�V�����x�[�X�ʒu
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�ʒu��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBasePos(size_t Index,D3DXVECTOR3& Pos){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BasePos = Pos;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBasePos()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseRot(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ��]��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBaseRot(size_t Index,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBaseRot()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseQt(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ��]��ύX����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBaseQt(size_t Index,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseQt = Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBaseQt()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseScalePosRot(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBaseScalePosRot(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
		m_ItemVec[Index]->m_BasePos = Pos;
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBaseScalePosRot()");
	}
}
/**************************************************************************
 void MultiCommonMesh::SetItemBaseScalePosQt(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
  );
 �p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void MultiCommonMesh::SetItemBaseScalePosQt(size_t Index,
	D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_BaseScale = Scale;
		m_ItemVec[Index]->m_BasePos = Pos;
		m_ItemVec[Index]->m_BaseQt = Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_BaseQt,&m_ItemVec[Index]->m_BaseQt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiCommonMesh::SetItemBaseScalePosRot()");
	}
}

/**************************************************************************
 virtual void MultiCommonMesh::Transform(
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �`��O�̕ω��B�s��̌v�Z�Ȃǂ��s���i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void MultiCommonMesh::Transform(vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data){
    //�z�u�I�u�W�F�N�g�̍s��̐ݒ�
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//��A�N�e�B�u�Ȃ�v�Z���Ȃ�
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//�g��k���p
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_ItemVec[i]->m_BaseScale.x,m_ItemVec[i]->m_BaseScale.y,m_ItemVec[i]->m_BaseScale.z);
		//���[�J����]�p
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//���[�J����]
		D3DXMatrixRotationQuaternion(&mtRot,&m_ItemVec[i]->m_BaseQt);
		//���[�J���ړ��p
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_ItemVec[i]->m_BasePos.x,m_ItemVec[i]->m_BasePos.y,m_ItemVec[i]->m_BasePos.z);

		//���Ή�]�p
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//���Ή�]
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_ItemVec[i]->m_Qt);

		//���Έړ��p
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//���Έړ�
		D3DXMatrixTranslation(&mtOffsetPos,m_ItemVec[i]->m_Pos.x,m_ItemVec[i]->m_Pos.y,m_ItemVec[i]->m_Pos.z);

		//���ׂă~�b�N�X�s������[���h�s��ɐݒ�
		D3DXMatrixIdentity(&m_ItemVec[i]->m_WorldMatrix);
		m_ItemVec[i]->m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
    }
}


/**************************************************************************
 virtual void MultiCommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void MultiCommonMesh::Draw(DrawPacket& i_DrawPacket){
    //�z�u�I�u�W�F�N�g�̕`��
    vector<CommonItem*>::size_type sz = m_ItemVec.size();
    for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//��A�N�e�B�u�Ȃ�\�����Ȃ�
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//���łɃ��[���h���W�͕ϊ��ς݂ƑO��
		//�R�������b�V���̕`����Ă�
		DrawCommonMesh(i_DrawPacket.pD3DDevice,m_ItemVec[i]->m_WorldMatrix,m_ItemVec[i]->m_Material,
			m_ItemVec[i]->m_pTexture);
    }
}
/**************************************************************************
	virtual void MultiCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void MultiCommonMesh::DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	   D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	//�z�u�I�u�W�F�N�g�̉e�`��
	vector<CommonItem*>::size_type sz = m_ItemVec.size();
	for(vector<CommonItem*>::size_type i = 0;i < sz;i++){
		//��A�N�e�B�u�Ȃ�\�����Ȃ�
		if(!m_ItemVec[i]->m_IsActive){
			continue;
		}
		//���̃A�C�e�����e���L���Ȃ�
		if(m_ItemVec[i]->m_IsShadowActive){
			//�e�`��p�̃}�g���N�X
			D3DXMATRIX mtAllMatrix;
			//�s������o��
			mtAllMatrix = m_ItemVec[i]->m_WorldMatrix;
			mtAllMatrix._42 -=  0.02f;	//Y���W
			mtAllMatrix._11 *= 0.98f;	//X�X�P�[��
			mtAllMatrix._22 *= 0.98f;	//Y�X�P�[��
			mtAllMatrix._33 *= 0.98f;	//Z�X�P�[��
			//�R�������b�V���̉e�`����Ă�
			DrawCommonShadowVolume(pD3DDevice,mtAllMatrix,pEffect,mCameraView,mCameraProj);
		}
	}
}


/**************************************************************************
 class MultiPolygon : public MultiCommonMesh;
 �p�r: �����̃|���S���N���X
****************************************************************************/
/**************************************************************************
 void MultiPolygon::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void MultiPolygon::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�|���S���̍쐬
		//���s�������O��throw�����
		CreatePolygon(pD3DDevice,
		   m_Length,m_Sides,m_IsTextureActive);
    }
    catch(...){
        //�R���X�g���N�^��O����
		//��n��
		Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 MultiPolygon(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT Length,					//�e�ʂ̒����B
    UINT Sides,						//�|���S���̖ʐ��B�l�� 3 �ȏ�ł���K�v������B
	bool IsTextureActive = false	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
 ���R���X�g���N�^�ł́A�e�N�X�`�����g�p���邩���Ȃ�����ݒ肷��
***************************************************************************/
MultiPolygon::MultiPolygon(LPDIRECT3DDEVICE9 pD3DDevice,
	 FLOAT Length,UINT Sides, wiz::OBJID id,bool IsTextureActive)
:MultiCommonMesh( id , IsTextureActive ),
m_Length(Length),
m_Sides(Sides)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiPolygon::~MultiPolygon();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiPolygon::~MultiPolygon(){
	//��n��
	Clear();
}
/**************************************************************************
	virtual void MultiPolygon::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void MultiPolygon::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiBox : public MultiCommonMesh;
 �p�r: �����̒����̃N���X
****************************************************************************/
/**************************************************************************
 void MultiBox::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void MultiBox::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�����̂̍쐬
		//���s�������O��throw�����
		CreateBox(pD3DDevice,D3DXVECTOR3(m_Size.x,m_Size.y,m_Size.z),
			m_IsTextureActive,m_TexturePtn);
    }
    catch(...){
        //�R���X�g���N�^��O����
		//��n��
		Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 MultiBox::MultiBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3& size,				//�R�������b�V�����쐬����Ƃ��̃T�C�Y
	bool IsTextureActive = false,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
 ���R���X�g���N�^�ł́A�e�N�X�`�����g�p���邩���Ȃ����ƁA
 ���e�N�X�`�����g�p����ꍇ�̓e�N�X�`���p�^�[�����w�肷��
***************************************************************************/
MultiBox::MultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
				   wiz::OBJID id,  bool IsTextureActive,int TexturePtn)
:MultiCommonMesh( id ,IsTextureActive),
m_Size(size),
m_TexturePtn(TexturePtn)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 virtual MultiBox::~MultiBox();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiBox::~MultiBox(){
	//��n��
	Clear();
}



/**************************************************************************
	virtual void MultiBox::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void MultiBox::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
	void MultiBox::GetOBB(
		size_t Index,
		OBB& obb	//�擾����OBB
	);
 �p�r: �w��̃C���f�b�N�X�̌��݂�OBB�𓾂�
 �߂�l: �Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
 �����݂�OBB��������
***************************************************************************/
void MultiBox::GetOBB(size_t Index,OBB& obb){
    //�w��̔z�u�I�u�W�F�N�g������
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		obb.m_Center = m_ItemVec[Index]->m_BasePos + m_ItemVec[Index]->m_Pos;
		obb.m_Size = m_Size;
		obb.m_Size.x *= m_ItemVec[Index]->m_BaseScale.x;
		obb.m_Size.y *= m_ItemVec[Index]->m_BaseScale.y;
		obb.m_Size.z *= m_ItemVec[Index]->m_BaseScale.z;
		obb.m_Size *= 0.5f;
		//�g�[�^���̉�]�𓾂�
		D3DXQUATERNION Qt = m_ItemVec[Index]->m_BaseQt;
		Qt *= m_ItemVec[Index]->m_Qt;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//�N�I�[�^�j�I�������]�s����쐬
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&Qt);
		obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"MultiBox::GetOBB()");
	}
}

/**************************************************************************
class ParallelMultiBox : public MultiBox;
 �p�r: �����̎��ɕ��s�Ȓ����̃N���X
****************************************************************************/

/**************************************************************************
 ParallelMultiBox::ParallelMultiBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3& size,				//�R�������b�V�����쐬����Ƃ��̃T�C�Y
	bool IsTextureActive = false,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
 ���R���X�g���N�^�ł́A�e�N�X�`�����g�p���邩���Ȃ����ƁA
 ���e�N�X�`�����g�p����ꍇ�̓e�N�X�`���p�^�[�����w�肷��
***************************************************************************/
ParallelMultiBox::ParallelMultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,
						wiz::OBJID id ,bool IsTextureActive,int TexturePtn)
:MultiBox(pD3DDevice,size,id,IsTextureActive,TexturePtn)
{
	//�{�͉̂������Ȃ�
}

/**************************************************************************
 virtual ParallelMultiBox::~ParallelMultiBox();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ParallelMultiBox::~ParallelMultiBox(){
	//�������Ȃ�
}


/**************************************************************************
 size_t ParallelMultiBox::AddItem(
    D3DXVECTOR3& Scale,               //�X�P�[���i�g��k���̔{���j
    D3DXVECTOR3& Pos,                //�ŏ��̈ʒu
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0			//�e�N�X�`��
    );
 �p�r: �A�C�e����ǉ�
 ����]�͎󂯂��Ȃ�
 �߂�l: �ǉ������C���f�b�N�X�i���s���͗�O��throw�j
***************************************************************************/
 size_t ParallelMultiBox::AddItem(
    D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,
    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture){
	try{
		D3DXVECTOR3 Rot(0,0,0);				//��]�͌Œ�
		return MultiCommonMesh::AddItem(Scale,Pos,Rot,
				 Diffuse,Specular,Ambient,
				 IsShadowActive,pTexture);

	}
	catch(...){
		//�ăX���[
		throw;
	}
	return 0;
}
/**************************************************************************
	void ParallelMultiBox::GetAABB(
		size_t Index,			//�C���f�b�N�X
		AABB& Tgt	//��`�ϐ�
	);
 �p�r: �w��̃C���f�b�N�X�̌��݋�`�𓾂�
 �߂�l: �Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
***************************************************************************/
void ParallelMultiBox::GetAABB(size_t Index,AABB& Tgt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		D3DXVECTOR3 Pos = m_ItemVec[Index]->m_BasePos + m_ItemVec[Index]->m_Pos;
		AABB aabb(Pos,
			m_Size.x * m_ItemVec[Index]->m_BaseScale.x,
			m_Size.y * m_ItemVec[Index]->m_BaseScale.y,
			m_Size.z * m_ItemVec[Index]->m_BaseScale.z
			);
		Tgt = aabb;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"ParallelMultiBox::GetAABB()");
	}
}


/**************************************************************************
 class MultiSphere : public CommonMesh;
 �p�r: �����̋��N���X
****************************************************************************/
/**************************************************************************
 void MultiSphere::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void MultiSphere::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//���̍쐬
		//���s�������O��throw�����
		CreateSphere(pD3DDevice,m_Radius,m_IsTextureActive,m_Slices,m_Stacks);

    }
    catch(...){
        //�R���X�g���N�^��O����
		//��n��
		Clear();
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 MultiSphere::MultiSphere(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT radius,					//�R�������b�V�����쐬����Ƃ��̔��a
	bool IsTextureActive = false,	//�e�N�X�`�������邩�ǂ���
	UINT Slices = 18,				//�厲�̉�]�X���C�X��
	UINT Stacks = 18				//�厲�ɉ������X���C�X��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MultiSphere::MultiSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,
		wiz::OBJID id,bool IsTextureActive,
		UINT Slices,UINT Stacks)
:MultiCommonMesh(id,IsTextureActive),
m_Radius(radius),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiSphere::~MultiSphere();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiSphere::~MultiSphere(){
    //��n��
	Clear();
}

/**************************************************************************
	virtual void MultiSphere::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void MultiSphere::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiCylinder : public MultiCommonMesh;
 �p�r: �����̃V�����_�[�N���X
****************************************************************************/
/**************************************************************************
 void MultiCylinder::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void MultiCylinder::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�V�����_�[�̍쐬
		CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,m_IsTextureActive,m_Slices,m_Stacks);
    }
    catch(...){
        //�R���X�g���N�^��O����
		//��n��
		Clear();
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 MultiCylinder::MultiCylinder(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    FLOAT Radius1,                   //z ���̕��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B 
    FLOAT Radius2,                   //z ���̐��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B
	FLOAT Length,					//z �������̉~���̒����B
	bool IsTextureActive = false,	//�e�N�X�`�������邩�ǂ���
	UINT Slices = 18,		//�厲����]���Ƃ����X���C�X�̐��B
	UINT Stacks = 18		//�厲�ɉ������X�^�b�N���B
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MultiCylinder::MultiCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT Radius1,FLOAT Radius2,FLOAT Length, wiz::OBJID id,
		bool IsTextureActive,UINT Slices,UINT Stacks)
:MultiCommonMesh(id,IsTextureActive),
m_Radius1(Radius1),
m_Radius2(Radius2),
m_Length(Length),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiCylinder::~MultiCylinder();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiCylinder::~MultiCylinder(){
    //��n��
	Clear();
}
/**************************************************************************
void MultiCylinder::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void MultiCylinder::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class MultiTorus : public MultiCommonMesh;
 �p�r: �����̃g�[���X�N���X
****************************************************************************/
/**************************************************************************
 void MultiTorus::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void MultiTorus::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�g�[���X�̍쐬
		//���s�������O��throw�����
		CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,m_IsTextureActive,m_Sides,m_Rings);
    }
    catch(...){
        //�R���X�g���N�^��O����
		//��n��
		Clear();
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 MultiTorus::MultiTorus(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    FLOAT InnerRadius,              //�h�[�i�b�c�̔��a
    FLOAT OuterRadius,              //���_����h�[�i�b�c���S�܂ł̔��a
	bool IsTextureActive = false,	//�e�N�X�`�������邩�ǂ���
	UINT Sides = 18,					//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT Rings = 18				//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MultiTorus::MultiTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,
					   wiz::OBJID id,bool IsTextureActive,UINT Sides,UINT Rings)
:MultiCommonMesh(id,IsTextureActive),
m_InnerRadius(InnerRadius),
m_OuterRadius(OuterRadius),
m_Sides(Sides),
m_Rings(Rings)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual MultiTorus::~MultiTorus();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MultiTorus::~MultiTorus(){
    //��n��
	Clear();
}
/**************************************************************************
	virtual void MultiTorus::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void MultiTorus::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}

/**************************************************************************
 class SimpleCommonMesh : public CommonMesh;
 �p�r: �P���ȃR�������b�V���N���X
****************************************************************************/
/**************************************************************************
 SimpleCommonMesh::SimpleCommonMesh(
    D3DXVECTOR3& Pos,                //�ʒu
	D3DXVECTOR3& Rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
SimpleCommonMesh::SimpleCommonMesh(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture)
:CommonMesh( id ),
m_IsActive(true),
m_BaseScale(1.0f,1.0f,1.0f),
m_BasePos(Pos),m_Pos(0,0,0),
m_BaseQt(0,0,0,1),m_Qt(0,0,0,1),
m_IsShadowActive(IsShadowActive),
m_pTexture(pTexture)
{
    try{
        //�N�I�[�^�j�I���̏�����
		D3DXQuaternionIdentity(&m_BaseQt);
		D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
			Rot.y,Rot.x,Rot.z);
		D3DXQuaternionIdentity(&m_Qt);
		//�s��̏�����
		D3DXMatrixIdentity(&m_WorldMatrix);
		//�g��k���p
		D3DXMATRIX mtScale;
		D3DXMatrixIdentity(&mtScale);
		D3DXMatrixScaling(&mtScale,
			m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
		//��{��]�p
		D3DXMATRIX mtRot;
		D3DXMatrixIdentity(&mtRot);
		//��{��]
		D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
		//��{�ړ��p
		D3DXMATRIX mtPos;
		D3DXMatrixIdentity(&mtPos);
		D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

		//���Ή�]�p
		D3DXMATRIX mtOffsetRot;
		D3DXMatrixIdentity(&mtOffsetRot);
		//���Ή�]
		D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

		//���Έړ��p
		D3DXMATRIX mtOffsetPos;
		D3DXMatrixIdentity(&mtOffsetPos);
		//���Έړ�
		D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
		//���ׂă~�b�N�X�s��
		m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;

        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
        // ���f���̐F��ݒ�
        m_Material.Diffuse = Diffuse;
        m_Material.Specular = Specular;
        m_Material.Ambient = Ambient;
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual SimpleCommonMesh::~SimpleCommonMesh();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
 SimpleCommonMesh::~SimpleCommonMesh(){
	//�}���`�R�������b�V���z��̃N���A
	 SafeDeletePointerContainer(m_MultiVec);
	//���g�̃��b�V���̃N���A�͐e�N���X�ōs�Ȃ�
 }

/**************************************************************************
 size_t SimpleCommonMesh::AddMultiMesh(
	MultiCommonMesh* pMultiCommonMesh	//�}���`���b�V���̃|�C���^
  );
 �p�r: �}���`���b�V����ǉ�
 �߂�l: �ǉ������z��̃C���f�b�N�X
***************************************************************************/
size_t SimpleCommonMesh::AddMultiMesh(MultiCommonMesh* pMultiCommonMesh){
	size_t ret = m_MultiVec.size();
	m_MultiVec.push_back(pMultiCommonMesh);
	return ret;
}

/**************************************************************************
 size_t SimpleCommonMesh::GetMultiMeshCount();
 �p�r: �}���`���b�V���̐���Ԃ�
 �߂�l: �}���`���b�V���z��̐�
***************************************************************************/
size_t SimpleCommonMesh::GetMultiMeshCount(){
	return m_MultiVec.size();
}
/**************************************************************************
 MultiCommonMesh* SimpleCommonMesh::MultiCommonMesh(size_t Index);
 �p�r: �w�肵���C���f�b�N�X�̃}���`���b�V����Ԃ�
 �߂�l: �}���`���b�V���̃|�C���^�i�͈͊O�͗�O�j
***************************************************************************/
MultiCommonMesh* SimpleCommonMesh::GetMultiCommonMesh(size_t Index){
    //�w��̃}���`���b�V���𒲍�
    size_t sz = m_MultiVec.size();
	if(Index < sz){
		return m_MultiVec[Index];
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"impleCommonMesh::GetMultiMesh()");
	}
	return false;
}


/**************************************************************************
bool SimpleCommonMesh::IsActive();
 �p�r: �I�u�W�F�N�g���L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
***************************************************************************/
bool SimpleCommonMesh::IsActive(){
	return m_IsActive;
}
/**************************************************************************
void SimpleCommonMesh::SetActive(
	bool val		//�������������l�itrue��false�j
);
 �p�r:���̃I�u�W�F�N�g���L�����ǂ�����ݒ肷��
 �߂�l: �Ȃ��A
***************************************************************************/
void SimpleCommonMesh::SetActive(bool val){
	m_IsActive = val;
}


/**************************************************************************
 void SimpleCommonMesh::GetMaterial(
	D3DMATERIAL9& Material	//���݂̃}�e���A��
  );
 �p�r: �}�e���A�����擾����
 �߂�l: �Ȃ��iMaterial�Ƀ}�e���A����Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetMaterial(D3DMATERIAL9& Material){
	Material = m_Material;
}
/**************************************************************************
 void SimpleCommonMesh::SetMaterial(
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
  );
 �p�r: �}�e���A����ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetMaterial(D3DMATERIAL9& Material){
	m_Material = Material;
}

/**************************************************************************
bool SimpleCommonMesh::IsTextureActive();
 �p�r: �e�N�X�`�����L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
 ���e�N�X�`����ύX����ꍇ�́A��ɗL�����ǂ����������邱��
***************************************************************************/
bool SimpleCommonMesh::IsTextureActive(){
	if(m_pTexture){
		return true;
	}
	else{
		return false;
	}
}

/**************************************************************************
 LPDIRECT3DTEXTURE9 SimpleCommonMesh::GetTexture();
 �p�r: �e�N�X�`�����擾����
 �߂�l: ���݂̃e�N�X�`���i�Ȃ��ꍇ��0���Ԃ�j
***************************************************************************/
LPDIRECT3DTEXTURE9 SimpleCommonMesh::GetTexture(){
	return m_pTexture;
}
/**************************************************************************
 void SimpleCommonMesh::SetTexture(
	LPDIRECT3DTEXTURE9 pTexture	//�ݒ肷��e�N�X�`��
  );
 �p�r: �e�N�X�`����ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetTexture(LPDIRECT3DTEXTURE9 pTexture){
	//�e�N�X�`��������ꍇ
	if(m_pTexture){
		if(!pTexture){
			throw BaseException(L"���̃I�u�W�F�N�g�̓e�N�X�`�����K�v�ł��B",
				L"SimpleCommonMesh::SetTexture()");
		}
	}
	else{
	//�e�N�X�`�����Ȃ��ꍇ
		if(pTexture){
			throw BaseException(L"���̃I�u�W�F�N�g�̓e�N�X�`�����ݒ�ł��܂���B",
				L"SimpleCommonMesh::SetTexture()");
		}

	}
	m_pTexture = pTexture;
}

/**************************************************************************
bool SimpleCommonMesh::IsShadowActive();
 �p�r: �e���L�����ǂ����𒲂ׂ�
 �߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
***************************************************************************/
bool SimpleCommonMesh::IsShadowActive(){
	return m_IsShadowActive;
}

/**************************************************************************
void SimpleCommonMesh::SetShadowActive(
bool val		//�������������l�itrue��false�j
);
 �p�r: �e���L�����ǂ�����ݒ肷��
 �߂�l: �Ȃ��A
***************************************************************************/
void SimpleCommonMesh::SetShadowActive(bool val){
	m_IsShadowActive = val;
}


/**************************************************************************
 void SimpleCommonMesh::GetWorldPos(
	D3DXVECTOR3& Pos	//���݂̃��[���h�ʒu
  );
 �p�r: ���[���h�ʒu���擾����
 �߂�l: �Ȃ��iPos�Ƀ��[���h�ʒu��Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetWorldPos(D3DXVECTOR3& Pos){
	Pos = m_BasePos + m_Pos;
}

/**************************************************************************
 void SimpleCommonMesh::GetWorldRot(
	D3DXVECTOR3& Rot	//���݂̃��[���h��]
  );
 �p�r: ���[���h��]���擾����
 �߂�l: �Ȃ��iRot�Ƀ��[���h��]��Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetWorldRot(D3DXVECTOR3& Rot){
	D3DXQUATERNION Qt = m_BaseQt * m_Qt;
	//���݂̃x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&Qt,&Qt);
	//Qt����Rot�ɕϊ�
	Math::QtToRot(Qt,Rot);

}
/**************************************************************************
 void SimpleCommonMesh::GetWorldQt(
	D3DXQUATERNION& Qt	//���݂̃��[���h��]
  );
 �p�r: ���[���h��]���擾����
 �߂�l: �Ȃ��iQt�Ƀ��[���h��]��Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetWorldQt(D3DXQUATERNION& Qt){
	Qt = m_BaseQt * m_Qt;
}
/**************************************************************************
 void SimpleCommonMesh::GetWorldScale(
	D3DXVECTOR3& Scale	//���݂̃��[���h�X�P�[��
  );
 �p�r: ���[���h�X�P�[�����擾����
 �����̊֐���GetBaseScale�֐��Ɠ���
 �߂�l: �Ȃ��iScale�Ƀ��[���h�X�P�[�����O��Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetWorldScale(D3DXVECTOR3& Scale){
	Scale = m_BaseScale;
}
/**************************************************************************
 void SimpleCommonMesh::GetWorld(
	D3DXVECTOR3& Scale,	//���݂̃��[���h�X�P�[��
	D3DXVECTOR3& Pos,	//���݂̃��[���h�ʒu
	D3DXVECTOR3& Rot,	//���݂̃��[���h��]�i�I�C���[�e�j
	D3DXQUATERNION& Qt	//���݂̃��[���h��]�i�N�I�[�^�j�I���j
  );
 �p�r: ���ׂẴ��[���h�l���擾����
 �߂�l: �Ȃ��i�Q�ƂɃ��[���h�l��Ԃ��j
***************************************************************************/
void SimpleCommonMesh::GetWorld(
		D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt){
	Scale = m_BaseScale;
	Pos = m_BasePos + m_Pos;
	Qt = m_BaseQt * m_Qt;
	//���݂̃x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&Qt,&Qt);
	//Qt����Rot�ɕϊ�
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::GetWorldMatrix(
	D3DXMATRIX& mtWorld
 );
 �p�r:���[���h�ϊ����擾����
 �߂�l: �Ȃ��BmtWorld�ɕϊ��s����Z�b�g����
***************************************************************************/
void SimpleCommonMesh::GetWorldMatrix(D3DXMATRIX& mtWorld){
	mtWorld = m_WorldMatrix;
}

/**************************************************************************
 void SimpleCommonMesh::CalcWorldMatrix();
 �p�r:���[���h�ϊ����v�Z����
 �߂�l: �Ȃ��B���݂̕ϊ������ƂɃ��[���h�s����v�Z����
***************************************************************************/
void SimpleCommonMesh::CalcWorldMatrix(){
	if(!m_IsActive){
		//�A�N�e�B�u�łȂ���Όv�Z���Ȃ�
		return;
	}
	//�g��k���p
	D3DXMATRIX mtScale;
	D3DXMatrixIdentity(&mtScale);
	D3DXMatrixScaling(&mtScale,
		m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
	//��{��]�p
	D3DXMATRIX mtRot;
	D3DXMatrixIdentity(&mtRot);
	//��{��]
	D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
	//��{�ړ��p
	D3DXMATRIX mtPos;
	D3DXMatrixIdentity(&mtPos);
	D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

	//���Ή�]�p
	D3DXMATRIX mtOffsetRot;
	D3DXMatrixIdentity(&mtOffsetRot);
	//���Ή�]
	D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

	//���Έړ��p
	D3DXMATRIX mtOffsetPos;
	D3DXMatrixIdentity(&mtOffsetPos);
	//���Έړ�
	D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
	//���ׂă~�b�N�X�s��
	m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
	//�}���`���b�V���z����̕`��O�̕ω�
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->CalcWorldMatrix();
	}
}

/**************************************************************************
 void SimpleCommonMesh::GetLocalPosQt(
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
  );
 �p�r: ���Βl���擾����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::GetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	Pos = m_Pos;
	Qt = m_Qt;
}
/**************************************************************************
 void GetLocalPosRot(
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
  );
 �p�r: ���Βl���擾����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::GetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	Pos = m_Pos;
	//��]
	D3DXQUATERNION Qt;
	//���݂̃��[�J���N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&Qt,&m_Qt);
	//���K��
	D3DXQuaternionNormalize(&Qt,&Qt);
	//Qt����Rot�ɕϊ�
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::SetLocalPosQt(
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
  );
 �p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos = Pos;
	m_Qt = Qt;
}
/*************************************************************************
 void SimpleCommonMesh::SetLocalPosRot(
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//��]
  );
 �p�r: ���Βl��ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos = Pos;
	D3DXQuaternionIdentity(&m_Qt);
	D3DXQuaternionRotationYawPitchRoll(&m_Qt,
		Rot.y,Rot.x,Rot.z);
}


/**************************************************************************
 void SimpleCommonMesh::MoveToPosRot(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXVECTOR3& Rot	//��������]
  );
 �p�r: ���Βl���ړ�����]����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos += Pos;
	D3DXQUATERNION Qt;
	D3DXQuaternionIdentity(&Qt);
	D3DXQuaternionRotationYawPitchRoll(&Qt,
		Rot.y,Rot.x,Rot.z);
	m_Qt *= Qt;
	//�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveToPosRot(Pos,Rot);
	}
}

/**************************************************************************
 void SimpleCommonMesh::MoveToPosQt(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXQUATERNION& Qt	//��������]
  );
 �p�r: ���Βl���ړ�����]����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos += Pos;
	m_Qt *= Qt;
	//�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveToPosQt(Pos,Qt);
	}
}


/**************************************************************************
 void SimpleCommonMesh::MoveAtPosRot(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
  );
 �p�r: ���Βl��ݒ肵�Ȃ���
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_Pos = Pos;
	D3DXQuaternionIdentity(&m_Qt);
	D3DXQuaternionRotationYawPitchRoll(&m_Qt,
		Rot.y,Rot.x,Rot.z);
	//�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtPosRot(Pos,Rot);
	}
}

/**************************************************************************
 void SimpleCommonMesh::MoveAtPosQt(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
  );
 �p�r: ���Βl��ݒ肵�Ȃ���(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_Pos = Pos;
	m_Qt = Qt;
	//�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_Qt,&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtPosQt(Pos,Qt);
	}
}


/**************************************************************************
 void SimpleCommonMesh::MoveAtIdentity();
 �p�r: �ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::MoveAtIdentity(){
	m_Pos = D3DXVECTOR3(0,0,0);
	D3DXQuaternionIdentity(&m_Qt);
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->MoveAtIdentity();
	}
}
/**************************************************************************
 void SimpleCommonMesh::GetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXVECTOR3& Rot	//�x�[�X��]�̎Q��
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o��
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::GetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	Scale = m_BaseScale;
	Pos = m_BasePos;
	D3DXQUATERNION Qt;
	//���݂̃x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&Qt,&m_BaseQt);
	//Qt����Rot�ɕϊ�
	Math::QtToRot(Qt,Rot);
}

/**************************************************************************
 void SimpleCommonMesh::GetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXQUATERNION& Qt	//�x�[�X��]�N�I�[�^�j�I���̎Q��
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o���i�N�I�[�^�j�I���Łj
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::GetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	Scale = m_BaseScale;
	Pos = m_BasePos;
	Qt = m_BaseQt;
}


/**************************************************************************
 void SimpleCommonMesh::SetBaseScale(
	D3DXVECTOR3& Scale	//�V�����x�[�X�X�P�[�����O
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBaseScale(D3DXVECTOR3& Scale){
	m_BaseScale = Scale;
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}
/**************************************************************************
 void SimpleCommonMesh::SetBasePos(
	D3DXVECTOR3& Pos	//�V�����x�[�X�ʒu
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�ʒu��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBasePos(D3DXVECTOR3& Pos){
	m_BasePos = Pos;
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}
/**************************************************************************
 void SimpleCommonMesh::SetBaseRot(
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
  );
 �p�r: �ŏ��ɍ쐬���ꂽ��]��ύX����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBaseRot(D3DXVECTOR3& Rot){
	D3DXQuaternionIdentity(&m_BaseQt);
	D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
		Rot.y,Rot.x,Rot.z);
	//�x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}

/**************************************************************************
 void SimpleCommonMesh::SetBaseQt(
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
  );
 �p�r: �ŏ��ɍ쐬���ꂽ��]��ύX����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBaseQt(D3DXQUATERNION& Qt){
	m_BaseQt = Qt;
	//�x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}


/**************************************************************************
 void SimpleCommonMesh::SetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	m_BaseScale = Scale;
	m_BasePos = Pos;
	D3DXQuaternionIdentity(&m_BaseQt);
	D3DXQuaternionRotationYawPitchRoll(&m_BaseQt,
		Rot.y,Rot.x,Rot.z);
	//�x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}

/**************************************************************************
 void SimpleCommonMesh::SetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
  );
 �p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMesh::SetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
	m_BaseScale = Scale;
	m_BasePos = Pos;
	m_BaseQt = Qt;
	//�x�[�X�N�I�[�^�j�I���𐳋K��
	D3DXQuaternionNormalize(&m_BaseQt,&m_BaseQt);
	//�܂܂��}���`���b�V���ɂ͓K�p���Ȃ�
}



 /**************************************************************************
virtual void SimpleCommonMesh::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B�i���s���͗�O��throw�j
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void SimpleCommonMesh::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�}���`���b�V���z����̍č\�z
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->ChangeDevice(pD3DDevice);
	}
	//���g�̃f�o�C�X�`�F���W�͔h���N���X�ōs�Ȃ�
}


/**************************************************************************
 virtual void SimpleCommonMesh::Transform(
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �`��O�̕ω��B�s��̌v�Z�Ȃǂ��s���i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMesh::Transform(vector<Object*>& Vec,
	   const CONTROLER_STATE* pCntlState,Context& Data){
	if(!m_IsActive){
		//�A�N�e�B�u�łȂ���Όv�Z���Ȃ�
		return;
	}
	//�g��k���p
	D3DXMATRIX mtScale;
	D3DXMatrixIdentity(&mtScale);
	D3DXMatrixScaling(&mtScale,
		m_BaseScale.x,m_BaseScale.y,m_BaseScale.z);
	//��{��]�p
	D3DXMATRIX mtRot;
	D3DXMatrixIdentity(&mtRot);
	//��{��]
	D3DXMatrixRotationQuaternion(&mtRot,&m_BaseQt);
	//��{�ړ��p
	D3DXMATRIX mtPos;
	D3DXMatrixIdentity(&mtPos);
	D3DXMatrixTranslation(&mtPos,m_BasePos.x,m_BasePos.y,m_BasePos.z);

	//���Ή�]�p
	D3DXMATRIX mtOffsetRot;
	D3DXMatrixIdentity(&mtOffsetRot);
	//���Ή�]
	D3DXMatrixRotationQuaternion(&mtOffsetRot,&m_Qt);

	//���Έړ��p
	D3DXMATRIX mtOffsetPos;
	D3DXMatrixIdentity(&mtOffsetPos);
	//���Έړ�
	D3DXMatrixTranslation(&mtOffsetPos,m_Pos.x,m_Pos.y,m_Pos.z);
	//���ׂă~�b�N�X�s��
	m_WorldMatrix = mtScale * mtRot  *  mtPos * mtOffsetRot * mtOffsetPos;
	//�}���`���b�V���z����̕`��O�̕ω�
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->Transform(Vec,pCntlState,Data);
	}
}



/**************************************************************************
 virtual void SimpleCommonMesh::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMesh::Draw(DrawPacket& i_DrawPacket){
	LPDIRECT3DDEVICE9 pD3DDevice = i_DrawPacket.pD3DDevice ;
	if(!m_IsActive){
		//�A�N�e�B�u�łȂ���Ε\�����Ȃ�
		return;
	}
	//�R�������b�V���̕`����Ă�
	DrawCommonMesh(pD3DDevice,m_WorldMatrix,m_Material,m_pTexture);
	//�}���`���b�V���z����̕`��
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->Draw(i_DrawPacket);
	}
}
/**************************************************************************
	virtual void SimpleCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMesh::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	if(!m_IsActive){
		//�A�N�e�B�u�łȂ���Ε\�����Ȃ�
		return;
	}
	if(m_IsShadowActive){
		//�e�p�̍s��
		D3DXMATRIX mtAllMatrix;
		//�s������o��
		mtAllMatrix = m_WorldMatrix;
		mtAllMatrix._42 -=  0.02f;	//Y���W
		mtAllMatrix._11 *= 0.98f;	//X�X�P�[��
		mtAllMatrix._22 *= 0.98f;	//Y�X�P�[��
		mtAllMatrix._33 *= 0.98f;	//Z�X�P�[��
		//�R�������b�V���̉e�`����Ă�
		DrawCommonShadowVolume(pD3DDevice,mtAllMatrix,pEffect,mCameraView,mCameraProj);
	}
	//�}���`���b�V���z����̉e�`��
	vector<MultiCommonMesh*>::size_type sz = m_MultiVec.size();
	for(vector<MultiCommonMesh*>::size_type i = 0;i < sz;i++){
		m_MultiVec[i]->DrawShadowVolume(pD3DDevice,pEffect,mCameraView,mCameraProj);
	}
}


/**************************************************************************
 class Polygon : public SimpleCommonMesh;
 �p�r: �|���S���N���X
****************************************************************************/
/**************************************************************************
 void Polygon::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Polygon::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�����̂̍쐬
		//���s�������O��throw�����
		if(m_pTexture){
			CreatePolygon(pD3DDevice,m_Length,m_Sides,true);
		}
		else{
			CreatePolygon(pD3DDevice,m_Length,m_Sides);
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 Polygon::Polygon(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT Length,					//�e�ʂ̒���
	UINT Sides,						//�|���S���ʐ�
    D3DXVECTOR3& pos,                //�ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Polygon::Polygon(LPDIRECT3DDEVICE9 pD3DDevice,
	FLOAT Length,UINT Sides,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
    D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	wiz::OBJID id ,
	bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Length(Length),
m_Sides(Sides)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Polygon::~Polygon();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Polygon::~Polygon(){
	//�������Ȃ�
	//�I�u�W�F�N�g�̊J���͐e�N���X�ōs�Ȃ�
}
/**************************************************************************
	virtual void Polygon::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B�i���s���͗�O��throw�j
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Polygon::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
	//�e�N���X��ChangeDevice���Ăԁi�}���`���b�V���z��p�j
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class Box : public SimpleCommonMesh;
 �p�r: �{�b�N�X�N���X
****************************************************************************/
/**************************************************************************
 void Box::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Box::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�����̂̍쐬
		//���s�������O��throw�����
		if(m_pTexture){
			CreateBox(pD3DDevice,m_Size,true,m_TexturePtn);
		}
		else{
			CreateBox(pD3DDevice,m_Size);
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Box::Box(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3& size,               //�傫��
    D3DXVECTOR3& pos,                //�ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Box::Box(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,int TexturePtn)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Size(size),
m_TexturePtn(TexturePtn)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 Box::~Box();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Box::~Box(){
	//�������Ȃ�
	//�I�u�W�F�N�g�̊J���͐e�N���X�ōs�Ȃ�
}

/**************************************************************************
	virtual void Box::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B�i���s���͗�O��throw�j
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Box::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
	//�e�N���X��ChangeDevice���Ăԁi�}���`���b�V���z��p�j
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class ParallelBox : public Box;
 �p�r: ���ɕ��s�Ȓ����̃N���X
****************************************************************************/
/**************************************************************************
 ParallelBox::ParallelBox(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3& size,               //�傫��
    D3DXVECTOR3& pos,                //�ʒu
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
ParallelBox::ParallelBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,D3DXVECTOR3& pos,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,int TexturePtn)
:Box(pD3DDevice,size,pos,
D3DXVECTOR3(0,0,0),	//��]�̂�0�ɂ���
Diffuse,Specular,Ambient,id,
IsShadowActive,pTexture,TexturePtn)
{
	//�������Ȃ�
}
/**************************************************************************
 virtual ~ParallelBox();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ParallelBox::~ParallelBox(){
	//�������Ȃ�
}

/**************************************************************************
	void ParallelBox::GetAABB(
		AABB& Tgt	//��`�ϐ�
	);
 �p�r: ���݋�`�𓾂�
 �߂�l: �Ȃ��B
 �����݂̋�`��������
***************************************************************************/
void ParallelBox::GetAABB(AABB& Tgt){
	D3DXVECTOR3 Pos = m_BasePos + m_Pos;
	FLOAT xh = m_Size.x * m_BaseScale.x / 2.0f;
	FLOAT yh = m_Size.y * m_BaseScale.y / 2.0f;
	FLOAT zh = m_Size.z * m_BaseScale.z / 2.0f;
	//���
	Tgt.m_Min.x = Pos.x - xh;
	Tgt.m_Max.x = Pos.x + xh;

	Tgt.m_Min.y = Pos.y - yh;
	Tgt.m_Max.y = Pos.y + yh;

	Tgt.m_Min.z = Pos.z - zh;
	Tgt.m_Max.z = Pos.z + zh;
}



/**************************************************************************
 class Sphere : public SimpleCommonMesh;
 �p�r: ���N���X
****************************************************************************/
/**************************************************************************
 void Sphere::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Sphere::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//���̍쐬
		//���s�������O��throw�����
		if(m_pTexture){
			CreateSphere(pD3DDevice,m_Radius,true,m_Slices,m_Stacks);
		}
		else{
			CreateSphere(pD3DDevice,m_Radius,false,m_Slices,m_Stacks);
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Sphere::Sphere(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    FLOAT radius,                   //���a�̑傫��
    D3DXVECTOR3& pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	UINT Slices = 18,	//�厲�̉�]�X���C�X��
	UINT Stacks = 18	//�厲�ɉ������X���C�X��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
 Sphere::Sphere(LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT radius,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
		UINT Slices,UINT Stacks)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Radius(radius),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Sphere::~Sphere();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sphere::~Sphere(){
	//�������Ȃ�
	//�I�u�W�F�N�g�̊J���͐e�N���X�ōs�Ȃ�
}

/**************************************************************************
virtual void Sphere::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Sphere::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
	//�e�N���X��ChangeDevice���Ăԁi�}���`���b�V���z��p�j
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}


/**************************************************************************
 class Cylinder : public SimpleCommonMesh;
 �p�r: �V�����_�[�N���X
****************************************************************************/
/**************************************************************************
 void Cylinder::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Cylinder::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�V�����_�[�̍쐬
		//���s�������O��throw�����
		if(m_pTexture){
			CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,true,m_Slices,m_Stacks);
		}
		else{
			CreateCylinder(pD3DDevice,m_Radius1,m_Radius2,m_Length,false,m_Slices,m_Stacks);
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Cylinder::Cylinder(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    FLOAT Radius1,                   //z ���̕��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B 
    FLOAT Radius2,                   //z ���̐��̑��̖ʂ̔��a�B�l�� 0.0f �ȏ�ł���K�v������B
	FLOAT Length,					//z �������̉~���̒����B
    D3DXVECTOR3& pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	UINT Slices = 18,		//�厲����]���Ƃ����X���C�X�̐��B
	UINT Stacks = 18		//�厲�ɉ������X�^�b�N���B
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
 Cylinder::Cylinder(LPDIRECT3DDEVICE9 pD3DDevice,
	 FLOAT Radius1,FLOAT Radius2,FLOAT Length,
	 D3DXVECTOR3& pos,D3DXVECTOR3& rot,
	 D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	 wiz::OBJID id,
	 bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
	 UINT Slices,UINT Stacks)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_Radius1(Radius1),
m_Radius2(Radius2),
m_Length(Length),
m_Slices(Slices),
m_Stacks(Stacks)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Cylinder::~Cylinder();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Cylinder::~Cylinder(){
	//�������Ȃ�
	//�I�u�W�F�N�g�̊J���͐e�N���X�ōs�Ȃ�
}
/**************************************************************************
	virtual void Cylinder::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Cylinder::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
	//�e�N���X��ChangeDevice���Ăԁi�}���`���b�V���z��p�j
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}

/**************************************************************************
 class Torus : public SimpleCommonMesh;
 �p�r: �g�[���X�N���X
****************************************************************************/
/**************************************************************************
 void Torus::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Torus::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
		//�g�[���X�̍쐬
		//���s�������O��throw�����
		if(m_pTexture){
			CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,true,m_Sides,m_Rings);
		}
		else{
			CreateTorus(pD3DDevice,m_InnerRadius,m_OuterRadius,false,m_Sides,m_Rings);
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Torus::Torus(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    FLOAT InnerRadius,              //�h�[�i�b�c�̔��a
    FLOAT OuterRadius,              //���_����h�[�i�b�c���S�܂ł̔��a
    D3DXVECTOR3& pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
    D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
    D3DCOLORVALUE& Specular,            //�X�y�L�����F
    D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPDIRECT3DTEXTURE9 pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	UINT Sides = 18,	//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT Rings = 18		//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������B     
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Torus::Torus(
		LPDIRECT3DDEVICE9 pD3DDevice,
		FLOAT InnerRadius,FLOAT OuterRadius,D3DXVECTOR3& pos,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id,
		bool IsShadowActive,LPDIRECT3DTEXTURE9 pTexture,
		UINT Sides,UINT Rings)
:SimpleCommonMesh(pos,rot,Diffuse,Specular,Ambient,id,IsShadowActive,pTexture),
m_InnerRadius(InnerRadius),
m_OuterRadius(OuterRadius),
m_Sides(Sides),
m_Rings(Rings)
{
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 virtual Torus::~Torus();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Torus::~Torus(){
	//�������Ȃ�
	//�I�u�W�F�N�g�̊J���͐e�N���X�ōs�Ȃ�
}

/**************************************************************************
virtual void Torus::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Torus::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//�C���X�^���X�̍\�z
	//��O�͌Ăяo�����֐����瓊������̂�
	//�����ɂ͋L�q���Ȃ��ėǂ�
	CreateInctance(pD3DDevice);
	//�e�N���X��ChangeDevice���Ăԁi�}���`���b�V���z��p�j
	SimpleCommonMesh::ChangeDevice(pD3DDevice);
}


/**************************************************************************
 class SimpleCommonMeshGroup : public Object;
 �p�r: �O���[�v�����ꂽ�R�������b�V��������ɃO���[�v������
 ���h���N���X�Ƃ��č쐬����̂ł͂Ȃ��A
 SimpleCommonMesh���܊֌W�ɂĎ�荞��
****************************************************************************/
/**************************************************************************
 SimpleCommonMeshGroup::SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh)
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw����j
 �����炩���ߍ쐬�����V���v���R�������b�V����n���B

***************************************************************************/
SimpleCommonMeshGroup::SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh,wiz::OBJID id )
:m_pSimpleCommonMesh(pSimpleCommonMesh)
,Object(OBJID_UNK)
{
}
/**************************************************************************
 virtual SimpleCommonMeshGroup::~SimpleCommonMeshGroup();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
SimpleCommonMeshGroup::~SimpleCommonMeshGroup(){
	//�O���[�v�z��̃N���A
	SafeDeletePointerContainer(m_ItemVec);
	//SimpleCommonMesh�̃N���A
	SafeDelete(m_pSimpleCommonMesh);
}
/**************************************************************************
	virtual void SimpleCommonMeshGroup::ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void SimpleCommonMeshGroup::ReleaseObj(){
	if(m_pSimpleCommonMesh){
		m_pSimpleCommonMesh->ReleaseObj();
	}
}
/**************************************************************************
	void SimpleCommonMeshGroup::SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
 �p�r: �V���v���R�������b�V���̐ݒ�
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMeshGroup::SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh){
	m_pSimpleCommonMesh = pSimpleCommonMesh;
}

/**************************************************************************
 const SimpleCommonMesh* SimpleCommonMeshGroup::GetSimpleCommonMesh() const;
 �p�r: ��ƂȂ�R�������b�V����Ԃ�
 �߂�l: ��ƂȂ�R�������b�V���̃|�C���^
***************************************************************************/
const SimpleCommonMesh* SimpleCommonMeshGroup::GetSimpleCommonMesh() const{
	return m_pSimpleCommonMesh;
}


/**************************************************************************
	size_t SimpleCommonMeshGroup::AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
 �p�r: �A�C�e���̓o�^
 �߂�l: �ǉ������C���f�b�N�X
***************************************************************************/
size_t SimpleCommonMeshGroup::AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
	GroupItem* pItem = 0;
	try{
		pItem = new GroupItem;
		//�V���v���R�������b�V��������΁A��������}�e���A�����擾
		if(m_pSimpleCommonMesh){
			m_pSimpleCommonMesh->GetMaterial(pItem->m_Material);
		}
		else{
			D3DCOLORVALUE def = {0.0f,0.0f,0.0f,0.0f};
			pItem->m_Material.Diffuse = def;
			pItem->m_Material.Specular = def;
			pItem->m_Material.Ambient = def;
		}
		pItem->m_Pos = Pos;
		//��]
		D3DXQuaternionIdentity(&pItem->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//���K��
		D3DXQuaternionNormalize(&pItem->m_Qt,&pItem->m_Qt);
		//�A�C�e���̒ǉ�
		size_t ret = m_ItemVec.size();
		m_ItemVec.push_back(pItem);
		//�ǉ������C���f�b�N�X�͒��O�̍��ڐ��ɂȂ�
		return ret;
	}
	catch(...){
		SafeDelete(pItem);
		throw;
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::GetItemMaterial(
	size_t Index,	//�擾����C���f�b�N�X
	D3DMATERIAL9& Material	//���݂̃}�e���A��
  );
 �p�r: �}�e���A�����擾����
 �߂�l: �Ȃ��iMaterial��Index�̃}�e���A����Ԃ��j
***************************************************************************/
void SimpleCommonMeshGroup::GetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Material = m_ItemVec[Index]->m_Material;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::GetItemMaterial()");
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::SetItemMaterial(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
  );
 �p�r: �}�e���A����ݒ肷��
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMeshGroup::SetItemMaterial(size_t Index,D3DMATERIAL9& Material){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		m_ItemVec[Index]->m_Material = Material;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::SetItemMaterial()");
	}
}

/**************************************************************************
 void SimpleCommonMeshGroup::GetItemLocalPosQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
  );
 �p�r: ���Βl���擾����(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMeshGroup::GetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Pos = m_ItemVec[Index]->m_Pos;
		 Qt = m_ItemVec[Index]->m_Qt;
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::GetItemLocalPosQt()");
	}
}
/**************************************************************************
 void SimpleCommonMeshGroup::GetItemLocalPosRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
  );
 �p�r: ���Βl���擾����
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMeshGroup::GetItemLocalPosRot(size_t Index,
	D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		 Pos = m_ItemVec[Index]->m_Pos;
		//���K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
		//�s��Ɏ��o��
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		D3DXMatrixRotationQuaternion(&mt,&m_ItemVec[Index]->m_Qt);
		//�s�񂩂��]���������o��
		Rot.x = atan2(mt._32,mt._33);
		Rot.y = asin(-mt._13);
		Rot.z = atan2(mt._21,mt._11);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::GetItemLocalPosRot()");
	}

}
/**************************************************************************
 void SimpleCommonMeshGroup::SetItemLocalPosQt(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
  );
 �p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
void SimpleCommonMeshGroup::SetItemLocalPosQt(size_t Index,
	D3DXVECTOR3& Pos,D3DXQUATERNION& Qt){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�ʒu
		 m_ItemVec[Index]->m_Pos = Pos;
		//��]
		 m_ItemVec[Index]->m_Qt = Qt;
		//���K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::SetItemLocalPosQt()");
	}
}

/**************************************************************************
 void SimpleCommonMeshGroup::SetItemLocalPosRot(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//���Ή�]
  );
 �p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
 �߂�l: �Ȃ�
***************************************************************************/
 void SimpleCommonMeshGroup::SetItemLocalPosRot(size_t Index,
	 D3DXVECTOR3& Pos,D3DXVECTOR3& Rot){
    //�w��̔z�u�I�u�W�F�N�g�ւ̓K�p
    size_t sz = m_ItemVec.size();
	if(Index < sz){
		//�ʒu
		m_ItemVec[Index]->m_Pos = Pos;
		//��]
		D3DXQuaternionIdentity(&m_ItemVec[Index]->m_Qt);
		D3DXQuaternionRotationYawPitchRoll(&m_ItemVec[Index]->m_Qt,
			Rot.y,Rot.x,Rot.z);
		//���K��
		D3DXQuaternionNormalize(&m_ItemVec[Index]->m_Qt,&m_ItemVec[Index]->m_Qt);
	}
	else{
		throw BaseException(L"�C���f�b�N�X���͈͊O�ł��B",
			L"SimpleCommonMeshGroup::SetItemLocalPosRot()");
	}
}



/**************************************************************************
	virtual void SimpleCommonMeshGroup::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɍō\�z���ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void SimpleCommonMeshGroup::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	if(m_pSimpleCommonMesh){
		((Object*)m_pSimpleCommonMesh)->ChangeDevice(pD3DDevice);
	}
}
/**************************************************************************
 virtual void SimpleCommonMeshGroup::Transform(
 vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
 const CONTROLER_STATE* pCntlState,	//�R���g���[���̏��
 Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��ω�������i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMeshGroup::Transform(vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data){
}

/**************************************************************************
 virtual void SimpleCommonMeshGroup::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMeshGroup::Draw(DrawPacket& i_DrawPacket){
	 if(!m_pSimpleCommonMesh){
		 return;
	 }
	GroupItem TmpItem;
	//���[�J���ϊ����e���|�����I�u�W�F�N�g�Ɏ擾
	m_pSimpleCommonMesh->GetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->GetLocalPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
    //�O���[�v�z��̕`��
    vector<GroupItem*>::size_type sz = m_ItemVec.size();
    for(vector<GroupItem*>::size_type i = 0;i < sz;i++){
		m_pSimpleCommonMesh->SetMaterial(m_ItemVec[i]->m_Material);
		m_pSimpleCommonMesh->MoveAtPosQt(m_ItemVec[i]->m_Pos,m_ItemVec[i]->m_Qt);
		m_pSimpleCommonMesh->CalcWorldMatrix();
		//�`��
		m_pSimpleCommonMesh->Draw(i_DrawPacket);
	}
	//���ɖ߂�
	m_pSimpleCommonMesh->SetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->MoveAtPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
}
/**************************************************************************
	virtual void SimpleCommonMeshGroup::DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void SimpleCommonMeshGroup::DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj){
	 if(!m_pSimpleCommonMesh){
		 return;
	 }
	GroupItem TmpItem;
	//���[�J���ϊ����e���|�����I�u�W�F�N�g�Ɏ擾
	m_pSimpleCommonMesh->GetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->GetLocalPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
    //�O���[�v�z��̕`��
    vector<GroupItem*>::size_type sz = m_ItemVec.size();
    for(vector<GroupItem*>::size_type i = 0;i < sz;i++){
		m_pSimpleCommonMesh->SetMaterial(m_ItemVec[i]->m_Material);
		m_pSimpleCommonMesh->MoveAtPosQt(m_ItemVec[i]->m_Pos,m_ItemVec[i]->m_Qt);
		m_pSimpleCommonMesh->CalcWorldMatrix();
		//�`��
		m_pSimpleCommonMesh->DrawShadowVolume(pD3DDevice,pEffect,mCameraView,mCameraProj);
	}
	//���ɖ߂�
	m_pSimpleCommonMesh->SetMaterial(TmpItem.m_Material);
	m_pSimpleCommonMesh->MoveAtPosQt(TmpItem.m_Pos,TmpItem.m_Qt);
}


}//end of namespace	baseobject.
}//end of namespace	wiz.