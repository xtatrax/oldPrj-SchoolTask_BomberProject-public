////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FBassItems.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
//	�v���~�e�B�u���ӂ��R�m��搶�̃\�[�X���Q�l�ɑ��������! 
//
//	namespace wiz;
//
//
#pragma once
#include "Object.h"
//#include "AnimationModelClass/AnimationModelClass.h"
#include "Bass2DItems.h"
#include "TL-String.h"
namespace wiz {
namespace baseitems{

//////////
//	: ���錾
class CommonMesh;
class SimpleCommonMesh ;
//	: ���錾
//////////

enum SHADING{
	SHADING_COOKTRANCE,
};

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class CustomShader{
protected:
	LPD3DXMESH			pickoutMesh(CommonMesh* pComMesh);
	D3DMATERIAL9		pickoutMaterial(CommonMesh* pComMesh);
	D3DXMATRIX			pickoutMatrix(SimpleCommonMesh* pComMesh);
	LPTATRATEXTURE		pickoutTexture(SimpleCommonMesh* pComMesh);
};
class CookTrance : public CustomShader{
	Camera*			m_pCamera			;
	Light*			m_pLight			;
	LPD3DXEFFECT	m_pEffect			;
	D3DXHANDLE		m_hTech				;
	D3DXHANDLE		m_hWorldViewProj	;
	D3DXHANDLE		m_hWorld			;
	D3DXHANDLE		m_hWIT				;
	D3DXHANDLE		m_hLightDir			;
	D3DXHANDLE		m_hEyePos			;
	D3DXHANDLE		m_hTexture			;
	D3DXHANDLE		m_hDif				;
	D3DXHANDLE		m_hAmb				;
public:
	CookTrance(LPDIRECT3DDEVICE9 pD3DDevice);
	~CookTrance();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���b�V����`��
	//// ����       �F  
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F�Ȃ�ׂ����̊֐��͎g�킸 DrawCommonMesh �֐����g���悤�ɂ��Ă�������
	////            �F
	////
	void Draw(DrawPacket& i_DrawPacket,CommonMesh* i_pComMesh);

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���b�V����`��
	//// ����       �F  
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F�Ȃ�ׂ����̊֐��͎g�킸 DrawCommonMesh �֐����g���悤�ɂ��Ă�������
	////            �F
	////
	void Draw(DrawPacket& i_DrawPacket,SimpleCommonMesh* i_pComMesh);

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���b�V����`��
	//// ����       �F  
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F�Ȃ�ׂ����̊֐��͎g�킸 DrawCommonMesh �֐����g���悤�ɂ��Ă�������
	////            �F
	////
	void Draw(
		DrawPacket&				i_DrawPacket	,
		LPD3DXMESH				i_pMesh			,
		LPTATRATEXTURE		i_pTexture		,
		D3DXMATRIX				i_mMatrix		,
		D3DMATERIAL9			i_Material
	);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/**************************************************************************
class CommonMesh : public Object;
�p�r: �R�������b�V���N���X
****************************************************************************/
class CommonMesh : public Object{
public:
	friend class CustomShader;

	//Box�̃e�N�X�`���p�^�[��
	//�p�^�[���͌Ăяo�����Ŏw�肷��̂ŁA���ꂾ��public�ɂ���
	enum {PtnUV_1_1 = 0, PtnUV_6_1,PtnUV_YWrap,PtnUV_ZWrap, PtnUV_1_4};
protected:
	//�ȉ��͔h���N���X����Ă΂��
	//���b�V��
	LPD3DXMESH m_pMesh;
	//�e�{�����[���N���X
	//ShadowVolume* m_pShadowVolume;
	//���b�s���O�e�N�X�`�����ǂ���
	bool m_bWrapMode;
	//���C�A�[�t���[���\�����邩�ǂ���
	bool m_bWireFrame;
	//�t���b�g���[�h�ɂ��邩�ǂ���
	//�f�t�H���g��false�i�O�[���[ �V�F�[�f�B���O ���[�h�j
	bool m_bShadeModeFlat;

	//CustomShader* m_pShader;
protected:
	//�e�X�g�p
	D3DMATERIAL9	m_Material ;
	DWORD			m_dwDrawSubset;
	
	/**************************************************************************
	struct  CommonMeshVertex;
	�p�r: CommonMesh�̃e�N�X�`��������ꍇ�̒��_�t�H�[�}�b�g�̒�`
	D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	���\���̉����Ă���
	****************************************************************************/
	struct  CommonMeshVertex{
		D3DXVECTOR3 vec;	//���_
		D3DXVECTOR3 normal;	//�@��
		FLOAT       tu,tv;	//UV�l
	};

	//CommonMesh�p��FVF��DirectXAPI�ɓn���Ƃ��̃p�����[�^
	enum { CommonMeshFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };


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
	static void PolygonVec2UV(float x,float y,float z,float r,float& u,float& v);

	/**************************************************************************
	static void BoxVecNomalUV(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
	�p�r: Box��Vector�Ɩ@������U��V�����o��
	�O�ʂ݂̂Ƀe�N�X�`����W�J����ꍇ
	�߂�l: �Ȃ�
	float& u��float& v�ɕϊ���̒l����
	***************************************************************************/
	static void BoxVecNomalUV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);

	/**************************************************************************
	static void BoxVecNomal2UV(
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
	static void BoxVecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);

	/**************************************************************************
	static void BoxVecNomal2UV_6_1(
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
	static void BoxVecNomal2UV_6_1(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);

	/**************************************************************************
	static void BoxVecNomal2UV_1_4(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Box��Vector�Ɩ@������U��V�����o��
 �e�N�X�`����4�~1�̉摜�ɂȂ��Ă�ꍇ
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
				static void BoxVecNomal2UV_1_4(D3DXVECTOR3 vec,D3DXVECTOR3 normal,int ptn,float& u,float& v);
/**************************************************************************
 static void BoxVecNomal2UV_1_2(
	D3DXVECTOR3 vec,	//���_
	D3DXVECTOR3 normal,	//�@��
	float& u,	//�ϊ�����u�i�e�N�X�`�����U���W�j
	float& v	//�ϊ�����v�i�e�N�X�`�����V���W�j
	);
 �p�r: Box��Vector�Ɩ@������U��V�����o��
 �e�N�X�`����2�~1�̉摜�ɂȂ��Ă�ꍇ
 �߂�l: �Ȃ�
 float& u��float& v�ɕϊ���̒l����
***************************************************************************/
				static void BoxVecNomal2UV_1_2(D3DXVECTOR3 vec,D3DXVECTOR3 normal,int ptn,float& u,float& v);
/**************************************************************************
 static void SphereVec2UV(
>>>>>>> workspace
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
	static void SphereVec2UV(float x,float y,float z,float r,float& u,float& v);

	/**************************************************************************
	static void WrapVec2UV(
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
	static void WrapVec2UV(float x,float y,float z,float& u,float& v,bool IsYWrap = true);

	/**************************************************************************
	static void TorusVec2UV(
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
	static void TorusVec2UV(float x,float y,float z,float inr,float outr,float& u,float& v);

	/**************************************************************************
	CommonMesh();
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	CommonMesh( wiz::OBJID id , CustomShader* pShader = NULL );

	/**************************************************************************
	virtual ~CommonMesh();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~CommonMesh();

	/**************************************************************************
	void CreateBox(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	D3DXVECTOR3& size,				//�T�C�Y
	bool bTextureActive = false,		//�e�N�X�`�����A�N�e�B�u���ǂ���
	int TexturePtn = PtnUV_1_1	//�e�N�X�`�����L���ȏꍇ�̃p�^�[��
	);
	�p�r:Box�I�u�W�F�N�g�̍\�z
	�߂�l: �Ȃ��i��O��throw�j
	***************************************************************************/
	void CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,bool bTextureActive = false,int TexturePtn = PtnUV_1_1);

	/**************************************************************************
	void CreateSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	FLOAT radius,					//���a
	bool bTextureActive = false,		//�e�N�X�`�����A�N�e�B�u���ǂ���
	UINT Slices = 18,	//�厲�̉�]�X���C�X��
	UINT Stacks = 18	//�厲�ɉ������X���C�X��
	);
	�p�r:���I�u�W�F�N�g�̍\�z
	�߂�l: �Ȃ��i��O��throw�j
	***************************************************************************/
	void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,bool bTextureActive = false,UINT Slices = 18,UINT Stacks = 18);

	/**************************************************************************
	void CreateTorus(
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
	void CreateTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,bool bTextureActive = false,UINT Sides = 18,UINT Rings = 18);

	/**************************************************************************
	void CreateCylinder(
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
	void CreateCylinder(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Radius1,FLOAT Radius2,FLOAT Length,bool bTextureActive = false,UINT Slices = 18,UINT Stacks = 18);

	/**************************************************************************
	void CreatePolygon(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	FLOAT Length,					//�e�ʂ̒����B
	UINT Sides,						//�|���S���̖ʐ��B�l�� 3 �ȏ�ł���K�v������B
	bool bTextureActive = false,	//�e�N�X�`�����A�N�e�B�u���ǂ���
	);
	�p�r:�|���S���I�u�W�F�N�g�̍\�z
	�߂�l: �Ȃ��i��O��throw�j
	***************************************************************************/
	void CreatePolygon(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Length,UINT Sides,bool bTextureActive = false);

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommonMesh::CreateMeshFormX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,TextureManager& TexMgr)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F���b�V��X�t�@�C������ǂݍ���
	//// ����       �F  LPDIRECT3DDEVICE9	pD3DDevice
	////            �F  char*				pFileName
	////            �F  TextureManager&		TexMgr
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void CreateMeshFormX(
		const LPDIRECT3DDEVICE9 pD3DDevice,
		const char *pFileName,
		const TextureManager* pTexMgr
	);
	
	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommonMesh::Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F���b�V����`��
	//// ����       �F  
	//// �ߒl       �F�Ȃ�
	//// �S����     �F (�R�m��搶�̂ЂȌ`���)
	//// ���l       �F�Ȃ�ׂ����̊֐��͎g�킸 DrawCommonMesh �֐����g���悤�ɂ��Ă�������
	////            �F
	////
	void Draw(DrawPacket& i_DrawPacket,RENDERSTATE_PARAM* pParam = NULL);
	/**************************************************************************
	void DrawCommonMesh(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXMATRIX& Matrix,			//�ϊ��s��
	D3DMATERIAL9& Material,		//�}�e�B���A��
	LPTATRATEXTURE pTexture = 0			//�e�N�X�`��
	);
	�p�r: �R�����I�u�W�F�N�g��`��i�h���N���X����Ă΂��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	void DrawCommonMesh(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& Matrix,D3DMATERIAL9& Material,LPTATRATEXTURE pTexture = 0,RENDERSTATE_PARAM* pParam = NULL);
	/**************************************************************************
	void DrawCommonShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXMATRIX& AllMatrix,				//�I�u�W�F�N�g�̕ϊ��s��
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
	�p�r: �e�{�����[����`��i���z�֐��j�h���N���X����Ă΂��
	�߂�l: �Ȃ��B
	***************************************************************************/
	void DrawCommonShadowVolume( LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATRIX& AllMatrix, LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
public:
	void ShaderChange( CustomShader* pShader ){
	//	SafeDelete( m_pShader );
	//	m_pShader = pShader;
	}
	CustomShader* getShader(){
		return NULL;//m_pShader;
	}

	/**************************************************************************
	void SetWireFrame(
	bool Value	//���C�A�t���[���ɂ��邩�ǂ���
	);
	�p�r: ���C�A�t���[���̏ꍇ��true�A����ȊO��false��ݒ肷��
	�߂�l: �Ȃ��B
	***************************************************************************/
	void SetWireFrame(bool Value){ m_bWireFrame = Value; }
	/**************************************************************************
	void SetShadeModeFlat(
	bool Value	//�V�F�[�_�[���t���b�g���[�h�ɂ��邩�ǂ���
	);
	�p�r: �V�F�[�_�[���t���b�g���[�h�̏ꍇ��true�A
	����ȊO�i�O�[���[ �V�F�[�f�B���O ���[�h��false��ݒ肷��
	�߂�l: �Ȃ��B
	***************************************************************************/
	void SetShadeModeFlat(bool Value){ m_bShadeModeFlat = Value;}

	//�ȉ��̓f�o�C�X�r�����ɊO������Ă΂��
	/**************************************************************************
	virtual void ReleaseObj();
	�p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ReleaseObj();
};


/**************************************************************************
 class MultiCommonMesh : public CommonMesh;
 �p�r: �����̃R�������b�V���N���X
****************************************************************************/
class MultiCommonMesh : public CommonMesh{
protected:
	//�e�N�X�`�������ǂ���
	bool m_IsTextureActive;
	struct CommonItem{
		//���̃A�C�e���͗L�����ǂ���
		bool m_IsActive;
		//�}�e���A��
		D3DMATERIAL9 m_Material;
		//�����̃X�P�[��
		D3DXVECTOR3 m_BaseScale;
		//�����ʒu�̃I�u�W�F�N�g�̒��S
		D3DXVECTOR3 m_BasePos;
		//��]�p�̃N�I�[�^�j�I��
		D3DXQUATERNION m_BaseQt;
		//���݂̏����ʒu����̑��Έʒu
		D3DXVECTOR3 m_Pos;
		//���݂̏����ʒu����̉�]�p�̃N�I�[�^�j�I��
		D3DXQUATERNION m_Qt;
		//�`�掞�Ɏg�p����郏�[���h�ϊ��s��
		D3DXMATRIX m_WorldMatrix;
		//�e��`�悷�邩�ǂ���
		bool m_IsShadowActive;
		//�e�N�X�`��
		LPTATRATEXTURE m_pTexture;
		//�h���N���X������Ă�Clear()�֐���
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~CommonItem(){}
	};
	//CommonItem�̔z��
	vector<CommonItem*> m_ItemVec;
	/**************************************************************************
	virtual void Clear();
	�p�r:�I�u�W�F�N�g�̔j��
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual void Clear();
	/**************************************************************************
	MultiCommonMesh(
	bool IsTextureActive = false	//�e�N�X�`���𒣂�Ƃ��͎w��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	���R���X�g���N�^�ł́A�e�N�X�`�����g�p���邩���Ȃ����w�肷��
	***************************************************************************/
	MultiCommonMesh( wiz::OBJID id , bool IsTextureActive = false );
public:
	/**************************************************************************
	virtual ~MultiCommonMesh();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiCommonMesh();
	/**************************************************************************
	virtual size_t AddItem(
	D3DXVECTOR3& Scale,               //�X�P�[���i�g��k���̔{���j
	D3DXVECTOR3& Pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& Rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0			//�e�N�X�`��
	);
	�p�r: �A�C�e����ǉ�
	�߂�l: �ǉ������C���f�b�N�X�i���s���͗�O��throw�j
	***************************************************************************/
	virtual size_t AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,bool IsShadowActive = false,LPTATRATEXTURE pTexture = 0);
	/**************************************************************************
	size_t GetItemCount();
	�p�r: ���݂̃A�C�e�����𓾂�
	�߂�l: �A�C�e����
	***************************************************************************/
	size_t GetItemCount(){return  m_ItemVec.size();}
	/**************************************************************************
	size_t GetActiveItemCount();
	�p�r: ���݂̗L���ȃA�C�e�����𓾂�
	�߂�l: �A�C�e����
	***************************************************************************/
	size_t GetActiveItemCount();
	/**************************************************************************
	bool IsActiveItem(
	size_t Index	//�擾�������C���f�b�N�X
	);
	�p�r: �w�肵���C���f�b�N�X�̃A�C�e�����L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE�A�C���f�b�N�X���͈͈ȊO�Ȃ��O
	***************************************************************************/
	bool IsActiveItem(size_t Index);

	/**************************************************************************
	void SetActiveItem(
	size_t Index,	//�Z�b�g�������C���f�b�N�X
	bool val		//�������������l�itrue��false�j
	);
	�p�r: �w�肵���C���f�b�N�X�̃A�C�e�����L�����ǂ�����ݒ肷��
	�߂�l: �Ȃ��A�C���f�b�N�X���͈͈ȊO�Ȃ��O
	***************************************************************************/
	void SetActiveItem(size_t Index,bool val);
	/**************************************************************************
	void CopyItem(
	CommonItem* Dest,	//�R�s�[��
	size_t Index		//�R�s�[���̃A�C�e���̃C���f�b�N�X
	);
	�p�r:�A�C�e���̃R�s�[
	�߂�l: �Ȃ�
	***************************************************************************/
	void CopyItem(CommonItem* Dest,size_t Index);
	/**************************************************************************
	void GetItemMaterial(
	size_t Index,	//�擾����C���f�b�N�X
	D3DMATERIAL9& Material	//���݂̃}�e���A��
	);
	�p�r: �}�e���A�����擾����
	�߂�l: �Ȃ��iMaterial��Index�̃}�e���A����Ԃ��j
	***************************************************************************/
	void GetItemMaterial(size_t Index,D3DMATERIAL9& Material);
	/**************************************************************************
	void SetItemMaterial(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
	);
	�p�r: �}�e���A����ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemMaterial(size_t Index,D3DMATERIAL9& Material);

	/**************************************************************************
	bool IsTextureActive();
	�p�r: �e�N�X�`�����L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
	���e�C���f�b�N�X�̃e�N�X�`����ύX����ꍇ�́A��ɗL�����ǂ����������邱��
	***************************************************************************/
	bool IsTextureActive();

	/**************************************************************************
	LPTATRATEXTURE GetItemTexture(
	size_t Index	//�擾����C���f�b�N�X
	);
	�p�r: �e�N�X�`�����擾����
	�߂�l: ���݂̃e�N�X�`���i�Ȃ��ꍇ��0���Ԃ�j
	***************************************************************************/
	LPTATRATEXTURE GetItemTexture(size_t Index);
	/**************************************************************************
	void SetItemTexture(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	LPTATRATEXTURE pTexture	//�ݒ肷��e�N�X�`��
	);
	�p�r: �e�N�X�`����ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemTexture(size_t Index,LPTATRATEXTURE pTexture);

	/**************************************************************************
	bool IsShadowActiveItem(
	size_t Index	//�擾�������C���f�b�N�X
	);
	�p�r: �w�肵���C���f�b�N�X�̉e���L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE�A�C���f�b�N�X���͈͈ȊO�Ȃ��O
	***************************************************************************/
	bool IsShadowActiveItem(size_t Index);

	/**************************************************************************
	void SetShadowActiveItem(
	size_t Index,	//�Z�b�g�������C���f�b�N�X
	bool val		//�������������l�itrue��false�j
	);
	�p�r: �w�肵���C���f�b�N�X�̉e���L�����ǂ�����ݒ肷��
	�߂�l: �Ȃ��A�C���f�b�N�X���͈͈ȊO�Ȃ��O
	***************************************************************************/
	void SetShadowActiveItem(size_t Index,bool val);


	/**************************************************************************
	void GetItemWorldPos(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos	//���݂̃��[���h�ʒu
	);
	�p�r: ���[���h�ʒu���擾����
	�߂�l: �Ȃ��iPos��Index�̃��[���h�ʒu��Ԃ��j
	***************************************************************************/
	void GetItemWorldPos(size_t Index,D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetItemWorldRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Rot	//���݂̃��[���h��]
	);
	�p�r: ���[���h��]���擾����
	�߂�l: �Ȃ��iRot��Index�̃��[���h��]��Ԃ��j
	***************************************************************************/
	void GetItemWorldRot(size_t Index,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetItemWorldQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXQUATERNION& Qt	//���݂̃��[���h��]
	);
	�p�r: ���[���h��]���擾����
	�߂�l: �Ȃ��iQt��Index�̃��[���h��]��Ԃ��j
	***************************************************************************/
	void GetItemWorldQt(size_t Index,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemWorldScale(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale	//���݂̃��[���h�X�P�[��
	);
	�p�r: ���[���h�X�P�[�����擾����
	�����̊֐���GetItemBaseScale�֐��Ɠ���
	�߂�l: �Ȃ��iScale��Index�̃��[���h��]��Ԃ��j
	***************************************************************************/
	void GetItemWorldScale(size_t Index,D3DXVECTOR3& Scale);
	/**************************************************************************
	void GetItemWorld(
	size_t Index,_	//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//���݂̃��[���h�X�P�[��
	D3DXVECTOR3& Pos,	//���݂̃��[���h�ʒu
	D3DXVECTOR3& Rot,	//���݂̃��[���h��]�i�I�C���[�e�j
	D3DXQUATERNION& Qt	//���݂̃��[���h��]�i�N�I�[�^�j�I���j
	);
	�p�r: ���ׂẴ��[���h�l���擾����
	�߂�l: �Ȃ��i�Q�Ƃ�Index�̃��[���h�l��Ԃ��j
	***************************************************************************/
	void GetItemWorld(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemWorldMatrix(
	size_t Index,_	//�擾����C���f�b�N�X
	D3DXMATRIX& mtWorld	//�擾����s��
	);
	�p�r:���[���h�ϊ����擾����
	�߂�l: �Ȃ��BmtWorld�ɕϊ��s����Z�b�g����
	***************************************************************************/
	void GetItemWorldMatrix(size_t Index,D3DXMATRIX& mtWorld);
	/**************************************************************************
	void CalcWorldMatrix();
	�p�r:���ׂẴA�C�e���̃��[���h�ϊ����v�Z����
	�߂�l: �Ȃ��B���݂̕ϊ������ƂɃ��[���h�s����v�Z����
	***************************************************************************/
	void CalcWorldMatrix();
	/**************************************************************************
	void GetItemLocalPos(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos	//���݂̑��Έʒu
	);
	�p�r: ���Έʒu���擾����
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalPos(size_t Index,D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetItemLocalRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Rot	//���݂̉�]
	);
	�p�r: ���Ή�]���擾����
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalRot(size_t Index,D3DXVECTOR3& Rot);

	/**************************************************************************
	void GetItemLocalQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
	);
	�p�r: ���Ή�]���擾����i�N�I�[�^�j�I���Łj
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalQt(size_t Index,D3DXQUATERNION& Qt);

	/**************************************************************************
	void GetItemLocalPosQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
	);
	�p�r: ���Βl���擾����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemLocalPosRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
	);
	�p�r: ���Βl���擾����
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void SetItemLocalPosQt(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
	);
	�p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemLocalPosRot(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//��]
	);
	�p�r: ���Βl��ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void MoveToPosRot(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXVECTOR3& Rot	//��������]
	);
	�p�r: ���Βl���ړ�����]����
	*���ׂẴI�u�W�F�N�g�ɓK�p�����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToPosQt(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXQUATERNION& Qt	//��������]
	);
	�p�r: ���Βl���ړ�����]����(�N�I�[�^�j�I����)
	*���ׂẴI�u�W�F�N�g�ɓK�p�����
	�߂�l: �Ȃ�
	***************************************************************************/
		void MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void MoveToItemPosRot(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
	);
	�p�r: �w��̃����o�̑��Βl���ړ�����]����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveToItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToItemPosQt(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//��������]
	);
	�p�r: �w��̃����o�̑��Βl���ړ�����]����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveToItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtPosRot(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
	);
	�p�r: ���Βu���Z�b�g����
	*���ׂẴI�u�W�F�N�g�ɓK�p�����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtPosQt(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
	);
	�p�r: ���Βu���Z�b�g����(�N�I�[�^�j�I����)
	*���ׂẴI�u�W�F�N�g�ɓK�p�����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtItemPosRot(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
	);
	�p�r: �w��̃����o�̑��Βu���Z�b�g����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtItemPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtItemPosQt(
	size_t Index,	//�ω�������C���f�b�N�X
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
	);
	�p�r: �w��̃����o�̑��Βu���Z�b�g����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtItemPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtIdentity();
	�p�r: �ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
	*���ׂẴI�u�W�F�N�g�ɓK�p�����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtIdentity();
	/**************************************************************************
	void MoveAtItemIdentity(
	size_t Index	//�ω�������C���f�b�N�X
	);
	�p�r: �w��̃����o�̍ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtItemIdentity(size_t Index);
	/**************************************************************************
	void GetItemBaseScalePosRot(
	size_t Index,		//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXVECTOR3& Rot	//�x�[�X��]�̎Q��
	);
	�p�r: �w��̃C���f�b�N�X�̃x�[�X�̃X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o��
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemBaseScalePosRot(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetItemBaseScalePosQt(
	size_t Index,		//�擾����C���f�b�N�X
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXQUATERNION& Qt	//�x�[�X��]�N�I�[�^�j�I���̎Q��
	);
	�p�r: �w��̃C���f�b�N�X�̃x�[�X�̃X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o���i�N�I�[�^�j�I���Łj
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemBaseScalePosQt(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void SetItemBaseScale(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale	//�V�����x�[�X�X�P�[�����O
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBaseScale(size_t Index,D3DXVECTOR3& Scale);
	/**************************************************************************
	void SetItemBasePos(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Pos	//�V�����x�[�X�ʒu
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�ʒu��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBasePos(size_t Index,D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetItemBaseRot(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ��]��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBaseRot(size_t Index,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemBaseQt(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ��]��ύX����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBaseQt(size_t Index,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemBaseScalePosRot(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBaseScalePosRot(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemBaseScalePosQt(
	size_t Index,		//�ݒ肷��C���f�b�N�X
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
	);
	�p�r: �w��̃C���f�b�N�X�̍ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemBaseScalePosQt(size_t Index,D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��ω�������i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��`��i�������z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
	�p�r: �e�{�����[����`��i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};



/**************************************************************************
 class MultiPolygon : public MultiCommonMesh;
 �p�r: �����̃|���S���N���X
****************************************************************************/
class MultiPolygon : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Length;	//�e�ʂ̒����B
	UINT m_Sides;	//�|���S���̖ʐ��B�l�� 3 �ȏ�ł���K�v������B
public:
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
	MultiPolygon(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Length,UINT Sides,wiz::OBJID id = OBJID_3D_MULTI_POLYGON,bool IsTextureActive = false);
	/**************************************************************************
	virtual ~MultiPolygon();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiPolygon();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
class MultiBox : public MultiCommonMesh;
�p�r: �����̒����̃N���X
****************************************************************************/
class MultiBox : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//�e�N�X�`���p�^�[��
	int m_TexturePtn;
	//�R�������b�V���̃T�C�Y
	D3DXVECTOR3 m_Size;
public:
	/**************************************************************************
	MultiBox(
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
	MultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,wiz::OBJID id = OBJID_3D_MULTI_BOX,bool IsTextureActive = false,int TexturePtn = PtnUV_1_1);
	/**************************************************************************
	virtual ~MultiBox();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiBox();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
	/**************************************************************************
	void GetOBB(
	size_t Index,
	OBB& obb	//�擾����OBB
	);
	�p�r: �w��̃C���f�b�N�X�̌��݂�OBB�𓾂�
	�߂�l: �Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
	�����݂�OBB��������
	***************************************************************************/
	void GetOBB(size_t Index,OBB& obb);
};

/**************************************************************************
class ParallelMultiBox : public MultiBox;
�p�r: �����̎��ɕ��s�Ȓ����̃N���X
****************************************************************************/
class ParallelMultiBox : public MultiBox{
public:
	/**************************************************************************
	ParallelMultiBox(
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
	ParallelMultiBox(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& size,wiz::OBJID id = OBJID_3D_MULTI_BOX_PARALLEL,bool IsTextureActive = false,int TexturePtn = PtnUV_1_1);
	/**************************************************************************
	virtual ~ParallelMultiBox();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~ParallelMultiBox();
	/**************************************************************************
	size_t AddItem(
	D3DXVECTOR3& Scale,               //�X�P�[���i�g��k���̔{���j
	D3DXVECTOR3& Pos,                //�ŏ��̈ʒu
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0			//�e�N�X�`��
	);
	�p�r: �A�C�e����ǉ�
	����]�͎󂯂��Ȃ�
	�߂�l: �ǉ������C���f�b�N�X�i���s���͗�O��throw�j
	***************************************************************************/
	size_t AddItem(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,bool IsShadowActive = false,LPTATRATEXTURE pTexture = 0);
	/**************************************************************************
	void GetAABB(
	size_t Index,			//�C���f�b�N�X
	AABB& Tgt	//��`�ϐ�
	);
	//�p�r: �w��̃C���f�b�N�X�̌��݋�`�𓾂�
	�߂�l: �Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
	***************************************************************************/
	void GetAABB(size_t Index,AABB& Tgt);
};

/**************************************************************************
 class MultiSphere : public MultiCommonMesh;
 �p�r: �����̋��N���X
****************************************************************************/
class MultiSphere : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Radius;	//���a
	//�厲�̉�]�X���C�X��
	UINT m_Slices;
	//�厲�ɉ������X���C�X��
	UINT m_Stacks;
public:
	/**************************************************************************
	MultiSphere(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT radius,					//�R�������b�V�����쐬����Ƃ��̔��a
	bool IsTextureActive = false,	//�e�N�X�`�������邩�ǂ���
	UINT Slices = 18,				//�厲�̉�]�X���C�X��
	UINT Stacks = 18				//�厲�ɉ������X���C�X��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	MultiSphere(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT radius,wiz::OBJID id = OBJID_3D_MULTI_SPHERE,bool IsTextureActive = false,UINT Slices = 18,UINT Stacks = 18);
	/**************************************************************************
	virtual ~MultiSphere();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiSphere();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class MultiCylinder : public MultiCommonMesh;
 �p�r: �����̃V�����_�[�N���X
****************************************************************************/
class MultiCylinder : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
	protected:
		FLOAT m_Radius1;	//z ���̕��̑��̖ʂ̔��a�B
		FLOAT m_Radius2;	//z ���̐��̑��̖ʂ̔��a�B
		FLOAT m_Length;		//z �������̉~���̒����B
		//�厲����]���Ƃ����X���C�X�̐��B
		UINT m_Slices;
		//�厲�ɉ������X�^�b�N���B
		UINT m_Stacks;	
	public:
	/**************************************************************************
	MultiCylinder(
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
	MultiCylinder(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT Radius1,FLOAT Radius2,FLOAT Length,wiz::OBJID id = OBJID_3D_MULTI_CYLINDER,bool IsTextureActive = false,UINT Slices = 18,UINT Stacks = 18);
	/**************************************************************************
	virtual ~MultiCylinder();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiCylinder();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class MultiTorus : public MultiCommonMesh;
 �p�r: �����̃g�[���X�N���X
****************************************************************************/
class MultiTorus : public MultiCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//�h�[�i�b�c�̔��a
	FLOAT m_InnerRadius;
	//���_����h�[�i�b�c���S�܂ł̔��a
	FLOAT m_OuterRadius;
	//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT m_Sides;
	//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������
	UINT m_Rings;		
public:
	/**************************************************************************
	MultiTorus(
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
	MultiTorus(LPDIRECT3DDEVICE9 pD3DDevice,FLOAT InnerRadius,FLOAT OuterRadius,wiz::OBJID id = OBJID_3D_MULTI_TAURUS ,bool IsTextureActive = false,UINT Sides = 18,UINT Rings = 18);
	/**************************************************************************
	virtual ~MultiTorus();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~MultiTorus();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
 class SimpleCommonMesh : public CommonMesh;
 �p�r: �P���ȃR�������b�V���N���X
****************************************************************************/
class SimpleCommonMesh : public CommonMesh{
	friend class CustomShader;
protected:
	//���̃I�u�W�F�N�g�͗L�����ǂ���
	bool m_IsActive;
	//�\���̃X�P�[�����O
	//�ʏ�͕ω������Ȃ�
	D3DXVECTOR3 m_BaseScale;
	//�����ʒu�̃I�u�W�F�N�g�̒��S
	D3DXVECTOR3 m_BasePos;
	//��]�p�̃N�I�[�^�j�I��
	D3DXQUATERNION m_BaseQt;
	//���݂̏����ʒu����̑��Έʒu
	D3DXVECTOR3 m_Pos;
	//���݂̏����ʒu����̉�]�p�̃N�I�[�^�j�I��
	D3DXQUATERNION m_Qt;
	//�`�掞�Ɏg�p����郏�[���h�ϊ��s��
	D3DXMATRIX m_WorldMatrix;
	//�}�e���A��
	//D3DMATERIAL9 m_Material;
	//�e��`�悷�邩�ǂ���
	bool m_IsShadowActive;
	//�e�N�X�`��
	LPTATRATEXTURE m_pTexture;
	//�O���[�v������ꍇ�̃}���`���b�V���̃|�C���^�̔z��
	vector<MultiCommonMesh*> m_MultiVec;
	/**************************************************************************
	SimpleCommonMesh(
	D3DXVECTOR3& Pos,                //�ʒu
	D3DXVECTOR3& Rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	SimpleCommonMesh(
		const D3DXVECTOR3&			Pos				,
		const D3DXVECTOR3&			Rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				,
		const bool					IsShadowActive	= false	,
		const LPTATRATEXTURE		pTexture		= 0
	);
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B�i���s���͗�O��throw�j
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	/**************************************************************************
	virtual D3DXVECTOR3 GetPos();
	�p�r: ���݂̃|�W�V������Ԃ�
	�߂�l: ���݂̃|�W�V����
	***************************************************************************/
	virtual D3DXVECTOR3 GetPos(){ return m_BasePos + m_Pos;}
	/**************************************************************************
	virtual ~SimpleCommonMesh();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~SimpleCommonMesh();
	/**************************************************************************
	size_t AddMultiMesh(
	MultiCommonMesh* pMultiCommonMesh	//�}���`���b�V���̃|�C���^
	);
	�p�r: �}���`���b�V����ǉ�
	�߂�l: �ǉ������z��̃C���f�b�N�X
	***************************************************************************/
	size_t AddMultiMesh(MultiCommonMesh* pMultiCommonMesh);
	/**************************************************************************
	size_t GetMultiMeshCount();
	�p�r: �}���`���b�V���̐���Ԃ�
	�߂�l: �}���`���b�V���z��̐�
	***************************************************************************/
	size_t GetMultiMeshCount();
	/**************************************************************************
	MultiCommonMesh* GetMultiCommonMesh(size_t Index);
	�p�r: �w�肵���C���f�b�N�X�̃}���`���b�V����Ԃ�
	�߂�l: �}���`���b�V���̃|�C���^�i�͈͊O�͗�O�j
	***************************************************************************/
	MultiCommonMesh* GetMultiCommonMesh(size_t Index);
	/**************************************************************************
	bool IsActive();
	�p�r: �I�u�W�F�N�g���L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
	***************************************************************************/
	bool IsActive();
	/**************************************************************************
	void SetActive(
	bool val		//�������������l�itrue��false�j
	);
	�p�r:���̃I�u�W�F�N�g���L�����ǂ�����ݒ肷��
	�߂�l: �Ȃ��A
	***************************************************************************/
	void SetActive(bool val);
	/**************************************************************************
	void GetMaterial(
	D3DMATERIAL9& Material	//���݂̃}�e���A��
	);
	�p�r: �}�e���A�����擾����
	�߂�l: �Ȃ��iMaterial�Ƀ}�e���A����Ԃ��j
	***************************************************************************/
	void GetMaterial(D3DMATERIAL9& Material);
	/**************************************************************************
	void SetMaterial(
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
	);
	�p�r: �}�e���A����ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetMaterial(D3DMATERIAL9& Material);

	/**************************************************************************
	bool IsTextureActive();
	�p�r: �e�N�X�`�����L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
	���e�N�X�`����ύX����ꍇ�́A��ɗL�����ǂ����������邱��
	***************************************************************************/
	bool IsTextureActive();

	/**************************************************************************
	LPTATRATEXTURE GetTexture();
	�p�r: �e�N�X�`�����擾����
	�߂�l: ���݂̃e�N�X�`���i�Ȃ��ꍇ��0���Ԃ�j
	***************************************************************************/
	LPTATRATEXTURE GetTexture();
	/**************************************************************************
	void SetTexture(
	LPTATRATEXTURE pTexture	//�ݒ肷��e�N�X�`��
	);
	�p�r: �e�N�X�`����ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetTexture(LPTATRATEXTURE pTexture);

	/**************************************************************************
	bool IsShadowActive();
	�p�r: �e���L�����ǂ����𒲂ׂ�
	�߂�l: �L���Ȃ�TRUE�A�����Ȃ�FALSE
	***************************************************************************/
	bool IsShadowActive();

	/**************************************************************************
	void SetShadowActive(
	bool val		//�������������l�itrue��false�j
	);
	�p�r: �e���L�����ǂ�����ݒ肷��
	�߂�l: �Ȃ��A
	***************************************************************************/
	void SetShadowActive(bool val);

	/**************************************************************************
	void GetWorldPos(
	D3DXVECTOR3& Pos	//���݂̃��[���h�ʒu
	);
	�p�r: ���[���h�ʒu���擾����
	�߂�l: �Ȃ��iPos�Ƀ��[���h�ʒu��Ԃ��j
	***************************************************************************/
	void GetWorldPos(D3DXVECTOR3& Pos);

	/**************************************************************************
	void GetWorldRot(
	D3DXVECTOR3& Rot	//���݂̃��[���h��]
	);
	�p�r: ���[���h��]���擾����
	�߂�l: �Ȃ��iRot�Ƀ��[���h��]��Ԃ��j
	***************************************************************************/
	void GetWorldRot(D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetWorldQt(
	D3DXQUATERNION& Qt	//���݂̃��[���h��]
	);
	�p�r: ���[���h��]���擾����
	�߂�l: �Ȃ��iQt�Ƀ��[���h��]��Ԃ��j
	***************************************************************************/
	void GetWorldQt(D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetWorldScale(
	D3DXVECTOR3& Scale	//���݂̃��[���h�X�P�[��
	);
	�p�r: ���[���h�X�P�[�����擾����
	�����̊֐���GetBaseScale�֐��Ɠ���
	�߂�l: �Ȃ��iScale�Ƀ��[���h�X�P�[�����O��Ԃ��j
	***************************************************************************/
	void GetWorldScale(D3DXVECTOR3& Scale);
	/**************************************************************************
	void GetWorld(
	D3DXVECTOR3& Scale,	//���݂̃��[���h�X�P�[��
	D3DXVECTOR3& Pos,	//���݂̃��[���h�ʒu
	D3DXVECTOR3& Rot,	//���݂̃��[���h��]�i�I�C���[�e�j
	D3DXQUATERNION& Qt	//���݂̃��[���h��]�i�N�I�[�^�j�I���j
	);
	�p�r: ���ׂẴ��[���h�l���擾����
	�߂�l: �Ȃ��i�Q�ƂɃ��[���h�l��Ԃ��j
	***************************************************************************/
	void GetWorld(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetWorldMatrix(
	D3DXMATRIX& mtWorld
	);
	�p�r:���[���h�ϊ����擾����
	�߂�l: �Ȃ��BmtWorld�ɕϊ��s����Z�b�g����
	***************************************************************************/
	void GetWorldMatrix(D3DXMATRIX& mtWorld);
	/**************************************************************************
	void CalcWorldMatrix();
	�p�r:���[���h�ϊ����v�Z����
	�߂�l: �Ȃ��B���݂̕ϊ������ƂɃ��[���h�s����v�Z����
	***************************************************************************/
	void CalcWorldMatrix();
	/**************************************************************************
	void SimpleCommonMesh::CalcMatrix(D3DXMATRIX mPos , D3DXMATRIX mScale , D3DXMATRIX mRotZ);
	�p�r:���[���h�ϊ����v�Z����
	�߂�l: �Ȃ��B���݂̕ϊ������ƂɃ��[���h�s����v�Z����
	***************************************************************************/
	void CalcMatrix(D3DXMATRIX mPos , D3DXMATRIX mScale , D3DXMATRIX mRot);
	/**************************************************************************
	void GetLocalPosQt(
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
	);
	�p�r: ���Βl���擾����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetLocalPosRot(
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
	);
	�p�r: ���Βl���擾����
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	void SetLocalPosQt(
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
	);
	�p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetLocalPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetLocalPosRot(
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//��]
	);
	�p�r: ���Βl��ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetLocalPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);


	/**************************************************************************
	void MoveToPosRot(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXVECTOR3& Rot	//��������]
	);
	�p�r: ���Βl���ړ�����]����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveToPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveToPosQt(
	D3DXVECTOR3& Pos,	//���������Έʒu
	D3DXQUATERNION& Qt	//��������]
	);
	�p�r: ���Βl���ړ�����]����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveToPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);

	/**************************************************************************
	void MoveAtPosRot(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXVECTOR3& Rot	//�V������]
	);
	�p�r: ���Βl��ݒ肵�Ȃ���
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtPosRot(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void MoveAtPosQt(
	D3DXVECTOR3& Pos,	//�V�������Έʒu
	D3DXQUATERNION& Qt	//�V������]
	);
	�p�r: ���Βl��ݒ肵�Ȃ���(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtPosQt(D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void MoveAtIdentity();
	�p�r: �ŏ��ɍ쐬���ꂽ�ʒu����̎w�肷�鑊�Έʒu���N���A����
	�߂�l: �Ȃ�
	***************************************************************************/
	void MoveAtIdentity();
	/**************************************************************************
	void GetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXVECTOR3& Rot	//�x�[�X��]�̎Q��
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o��
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetBaseScalePosRot(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void GetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//�X�P�[�����O�̎Q��
	D3DXVECTOR3& Pos,	//�x�[�X�ʒu�̎Q��
	D3DXQUATERNION& Qt	//�x�[�X��]�N�I�[�^�j�I���̎Q��
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��Ɏ��o���i�N�I�[�^�j�I���Łj
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetBaseScale(
	D3DXVECTOR3& Scale	//�V�����x�[�X�X�P�[�����O
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBaseScale(D3DXVECTOR3& Scale);
	/**************************************************************************
	void SetBasePos(
	D3DXVECTOR3& Pos	//�V�����x�[�X�ʒu
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�ʒu��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBasePos(D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetPos(
	D3DXVECTOR3& Pos	//�V�����x�[�X�ʒu
	);
	�p�r: �ʒu��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetPos(D3DXVECTOR3& Pos);
	/**************************************************************************
	void SetBaseRot(
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
	);
	�p�r: �ŏ��ɍ쐬���ꂽ��]��ύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBaseRot(D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetBaseQt(
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
	);
	�p�r: �ŏ��ɍ쐬���ꂽ��]��ύX����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBaseQt(D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetBaseScalePosRot(
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXVECTOR3& Rot	//�V�����x�[�X��]
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBaseScalePosRot(const D3DXVECTOR3& Scale,const D3DXVECTOR3& Pos,const D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetBaseScalePosQt(
	D3DXVECTOR3& Scale,	//�V�����x�[�X�X�P�[�����O
	D3DXVECTOR3& Pos,	//�V�����x�[�X�ʒu
	D3DXQUATERNION& Qt	//�V�����x�[�X��]
	);
	�p�r: �ŏ��ɍ쐬���ꂽ�X�P�[�����O�ƈʒu�Ɖ�]�𓯎��ɕύX����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetBaseScalePosQt(D3DXVECTOR3& Scale,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��ω�������i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��`��i�������z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
	�p�r: �e�{�����[����`��i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

/**************************************************************************
class Polygon : public SimpleCommonMesh;
�p�r: �P���ȃ|���S���N���X
****************************************************************************/
class Polygon : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Length;	//�e�ʂ̒����B
	UINT m_Sides;	//�|���S���̖ʐ��B�l�� 3 �ȏ�ł���K�v������B
public:
	/**************************************************************************
	Polygon(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT Length,					//�e�ʂ̒���
	UINT Sides,						//�|���S���ʐ�
	D3DXVECTOR3& pos,                //�ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	Polygon(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					Length			,
		const UINT					Sides			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_POLYGON	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE		pTexture		= 0
	);
	/**************************************************************************
	virtual ~Polygon();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Polygon();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B�i���s���͗�O��throw�j
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};



/**************************************************************************
class Box : public SimpleCommonMesh;
�p�r: �{�b�N�X�N���X
****************************************************************************/
class Box : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	D3DXVECTOR3 m_Size;  //�傫��
	int m_TexturePtn;	//�e�N�X�`���p�^�[��
public:
	/**************************************************************************
	Box(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3& size,               //�傫��
	D3DXVECTOR3& pos,                //�ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	Box(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const D3DXVECTOR3&			size			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_BOX	,
		const bool					IsShadowActive	= false			,
		const LPTATRATEXTURE		pTexture		= 0				,
		const int					TexturePtn		= PtnUV_1_1
	);
	/**************************************************************************
	virtual ~Box();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Box();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B�i���s���͗�O��throw�j
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class ParallelBox : public Box;
 �p�r: ���ɕ��s�Ȓ����̃N���X
****************************************************************************/
class ParallelBox : public Box{
public:
	/**************************************************************************
	ParallelBox(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3& size,               //�傫��
	D3DXVECTOR3& pos,                //�ʒu
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	int TexturePtn = PtnUV_1_1		//�e�N�X�`���̃p�^�[��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	ParallelBox(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const D3DXVECTOR3&			size			,
		const D3DXVECTOR3&			pos				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_BOX_PARALLEL		,
		const bool					IsShadowActive	= false						,
		const LPTATRATEXTURE		pTexture		= 0							,
		const int					TexturePtn		= PtnUV_1_1
	);
	/**************************************************************************
	virtual ~ParallelBox();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~ParallelBox();
	/**************************************************************************
	void GetAABB(
	AABB& Tgt	//��`�ϐ�
	);
	�p�r: ���݋�`�𓾂�
	�߂�l: �Ȃ��B
	�����݂̋�`��������
	***************************************************************************/
	void GetAABB(AABB& Tgt);
};



/**************************************************************************
class Sphere : public SimpleCommonMesh;
�p�r: ���N���X
****************************************************************************/
class Sphere : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//���a
	FLOAT m_Radius;
	//�厲�̉�]�X���C�X��
	UINT m_Slices;
	//�厲�ɉ������X���C�X��
	UINT m_Stacks;
public:
	/**************************************************************************
	Sphere(
	LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT radius,                   //���a�̑傫��
	D3DXVECTOR3& pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	UINT Slices = 18,	//�厲�̉�]�X���C�X��
	UINT Stacks = 18	//�厲�ɉ������X���C�X��
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	Sphere(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					radius			,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_SPHERE	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE		pTexture		= 0					,
		const UINT					Slices			= 18				,
		const UINT					Stacks			= 18
	);
	/**************************************************************************
	virtual ~Sphere();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Sphere();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};


/**************************************************************************
 class Cylinder : public SimpleCommonMesh;
 �p�r: �V�����_�[�N���X
****************************************************************************/
class Cylinder : public SimpleCommonMesh{
	/**************************************************************************
	 void CreateInctance(
	 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	 );
	 �p�r: �C���X�^���X�̍\�z
	 �߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	FLOAT m_Radius1;
	FLOAT m_Radius2;
	FLOAT m_Length;
	//�厲����]���Ƃ����X���C�X�̐��B
	UINT m_Slices;
	//�厲�ɉ������X�^�b�N���B
	UINT m_Stacks;	
public:
	/**************************************************************************
	 Cylinder(
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
		LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
		UINT Slices = 18,		//�厲����]���Ƃ����X���C�X�̐��B
		UINT Stacks = 18		//�厲�ɉ������X�^�b�N���B
		);
	 �p�r: �R���X�g���N�^
	 �߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	Cylinder(
		const LPDIRECT3DDEVICE9 pD3DDevice			,
		const FLOAT Radius1							,
		const FLOAT Radius2							,
		const FLOAT Length							,
		const D3DXVECTOR3& pos						,
		const D3DXVECTOR3& rot						,
		const D3DCOLORVALUE& Diffuse				,
		const D3DCOLORVALUE& Specular				,
		const D3DCOLORVALUE& Ambient				,
		const wiz::OBJID id = OBJID_3D_CYLINDER		,
		const bool IsShadowActive = false			,
		const LPTATRATEXTURE pTexture = 0		,
		const UINT Slices = 18						,
		const UINT Stacks = 18
	);
	/**************************************************************************
	virtual ~Cylinder();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Cylinder();
	/**************************************************************************
		virtual void ChangeDevice(
		LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		);
	 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	 �߂�l: �Ȃ��B
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);

	///////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �FDEAD OR ALIVE
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�{�����V
	//// ���l       �F
	////            �F
	////
	D3DXVECTOR3 getPos() const;

	///////////////////// ////////////////////
	//// �֐���     �FFLOAT getRaduis1() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �FRadius1
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////            �F
	////
	FLOAT getRadius1() const ;
	///////////////////// ////////////////////
	//// �֐���     �FFLOAT getRaduis2() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �FRadius2
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////            �F
	////
	FLOAT getRadius2() const ;
};

/**************************************************************************
 class Torus : public SimpleCommonMesh;
 �p�r: �g�[���X�N���X
****************************************************************************/
class Torus : public SimpleCommonMesh{
	/**************************************************************************
	void CreateInctance(
	LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �C���X�^���X�̍\�z
	�߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
	//�h�[�i�b�c�̔��a
	FLOAT m_InnerRadius;
	//���_����h�[�i�b�c���S�܂ł̔��a
	FLOAT m_OuterRadius;
	//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT m_Sides;
	//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������
	UINT m_Rings;		
public:
	/**************************************************************************
	Torus(
	LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	FLOAT InnerRadius,              //�h�[�i�b�c�̔��a
	FLOAT OuterRadius,              //���_����h�[�i�b�c���S�܂ł̔��a
	D3DXVECTOR3& pos,                //�ŏ��̈ʒu
	D3DXVECTOR3& rot,				//��](���W�A���P��)
	D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
	D3DCOLORVALUE& Specular,            //�X�y�L�����F
	D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
	bool IsShadowActive = false,	//�e��`�悷�邩�ǂ���
	LPTATRATEXTURE pTexture = 0,	//�e�N�X�`���𒣂�Ƃ��͎w��
	UINT Sides = 18,	//���f�ʂ̕ӂ̐��B�l�� 3 �ȏ�ł���K�v������B
	UINT Rings = 18		//�g�[���X���\������̐��B�l�� 3 �ȏ�ł���K�v������B     
	);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
	Torus(
		const LPDIRECT3DDEVICE9		pD3DDevice		,
		const FLOAT					InnerRadius		,
		const FLOAT					OuterRadius		,
		const D3DXVECTOR3&			pos				,
		const D3DXVECTOR3&			rot				,
		const D3DCOLORVALUE&		Diffuse			,
		const D3DCOLORVALUE&		Specular		,
		const D3DCOLORVALUE&		Ambient			,
		const wiz::OBJID			id				= OBJID_3D_SPHERE	,
		const bool					IsShadowActive	= false				,
		const LPTATRATEXTURE	pTexture		= 0					,
		const UINT					Sides			= 18				,
		const UINT					Rings			= 18
	);
	/**************************************************************************
	virtual ~Torus();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Torus();
	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
};

/**************************************************************************
 class SimpleCommonMeshGroup : public Object;
 �p�r: �O���[�v�����ꂽ�R�������b�V��������ɃO���[�v������
 ���h���N���X�Ƃ��č쐬����̂ł͂Ȃ��A
 SimpleCommonMesh���܊֌W�ɂĎ�荞��
****************************************************************************/
class SimpleCommonMeshGroup : public Object{
protected:
	//���ƂȂ�V���v���R�������b�V��
	SimpleCommonMesh* m_pSimpleCommonMesh;
	struct GroupItem{
		//�}�e���A��
		D3DMATERIAL9 m_Material;
		//���݂̏����ʒu����̑��Έʒu
		D3DXVECTOR3 m_Pos;
		//���݂̏����ʒu����̉�]�p�̃N�I�[�^�j�I��
		D3DXQUATERNION m_Qt;
		//�h���N���X������Ă�
		//�폜�ł���悤�ɉ��z�f�X�g���N�^�ɂ��Ă���
		virtual ~GroupItem(){}
	};
	//GroupItem�̔z��
	vector<GroupItem*> m_ItemVec;
public:
	/**************************************************************************
	SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh = 0)
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw����j
	�����炩���ߍ쐬�����V���v���R�������b�V����n���B
	***************************************************************************/
	SimpleCommonMeshGroup(SimpleCommonMesh* pSimpleCommonMesh = 0,wiz::OBJID id = OBJID_UNK);
	/**************************************************************************
	virtual ~SimpleCommonMeshGroup();
	�p�r: �f�X�g���N�^
	�߂�l: �Ȃ�
	***************************************************************************/
	virtual ~SimpleCommonMeshGroup();
	/**************************************************************************
	virtual void ReleaseObj();
	�p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ReleaseObj();
	/**************************************************************************
	void SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
	�p�r: �V���v���R�������b�V���̐ݒ�
	�߂�l: �Ȃ��B
	***************************************************************************/
	void SetSimpleCommonMesh(SimpleCommonMesh* pSimpleCommonMesh);
	/**************************************************************************
	const SimpleCommonMesh* GetSimpleCommonMesh() const;
	�p�r: ��ƂȂ�R�������b�V����Ԃ�
	�߂�l: ��ƂȂ�R�������b�V���̃|�C���^
	***************************************************************************/
	const SimpleCommonMesh* GetSimpleCommonMesh() const;
	/**************************************************************************
	size_t AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	�p�r: �A�C�e���̓o�^
	�߂�l: �ǉ������C���f�b�N�X
	***************************************************************************/
	size_t AddItem(D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	size_t GetItemCount();
	�p�r: ���݂̃A�C�e�����𓾂�
	�߂�l: �A�C�e����
	***************************************************************************/
	size_t GetItemCount(){return  m_ItemVec.size();}
	/**************************************************************************
	void GetItemMaterial(
	size_t Index,	//�擾����C���f�b�N�X
	D3DMATERIAL9& Material	//���݂̃}�e���A��
	);
	�p�r: �}�e���A�����擾����
	�߂�l: �Ȃ��iMaterial��Index�̃}�e���A����Ԃ��j
	***************************************************************************/
	void GetItemMaterial(size_t Index,D3DMATERIAL9& Material);
	/**************************************************************************
	void SetItemMaterial(
	size_t Index,	//�ݒ肷��C���f�b�N�X
	D3DMATERIAL9& Material	//�ݒ肷��}�e���A��
	);
	�p�r: �}�e���A����ݒ肷��
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemMaterial(size_t Index,D3DMATERIAL9& Material);

	/**************************************************************************
	void GetItemLocalPosQt(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXQUATERNION& Qt	//���݂̑��Ή�]
	);
	�p�r: ���Βl���擾����(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void GetItemLocalPosRot(
	size_t Index,	//�擾����C���f�b�N�X
	D3DXVECTOR3& Pos,	//���݂̑��Έʒu
	D3DXVECTOR3& Rot	//���݂̉�]
	);
	�p�r: ���Βl���擾����
	�߂�l: �Ȃ�
	***************************************************************************/
	void GetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);
	/**************************************************************************
	void SetItemLocalPosQt(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXQUATERNION& Qt	//���Ή�]
	);
	�p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemLocalPosQt(size_t Index,D3DXVECTOR3& Pos,D3DXQUATERNION& Qt);
	/**************************************************************************
	void SetItemLocalPosRot(
	size_t Index,	//�C���f�b�N�X
	D3DXVECTOR3& Pos,	//���Έʒu
	D3DXVECTOR3& Rot	//���Ή�]
	);
	�p�r: ���Βl��ݒ肷��(�N�I�[�^�j�I����)
	�߂�l: �Ȃ�
	***************************************************************************/
	void SetItemLocalPosRot(size_t Index,D3DXVECTOR3& Pos,D3DXVECTOR3& Rot);

	/**************************************************************************
	virtual void ChangeDevice(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	�p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	�߂�l: �Ȃ��B
	���f�o�C�X���r�������Ƃ��ɍō\�z���ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice);
	/**************************************************************************
	virtual void Transform(
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,	//�R���g���[���̏��
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��ω�������i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Transform(vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Context& Data);
	/**************************************************************************
	virtual void Draw(
	LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
	const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
	);
	�p�r: �I�u�W�F�N�g��`��i�������z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	virtual void DrawShadowVolume(
	LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
	�p�r: �e�{�����[����`��i���z�֐��j
	�߂�l: �Ȃ��B
	***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

class PrimitiveCylinder : public Cylinder{
	
public:
	PrimitiveCylinder(LPDIRECT3DDEVICE9 pD3DDevice,
          D3DCOLORVALUE& Diffuse,
		  D3DCOLORVALUE& Specular,
		  D3DCOLORVALUE& Ambient,
		  wiz::OBJID id = OBJID_3D_CYLINDER,
		  LPTATRATEXTURE pTexture = 0 )
	:Cylinder(pD3DDevice, 0.5, 0.5, 1, g_vZero, g_vZero, Diffuse, Specular, Ambient,id, false, pTexture)
	{
		
	}

	/////////////////// ////////////////////
	//// �p�r       �FPrimitiveCylinder(
	////									LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,
	////									float Radius1,float Radius2,float Lenght,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
	////									D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
	////									wiz::OBJID id = OBJID_3D_MAGNET)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FPlayer�p�̃R���X�g���N�^
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPTATRATEXTURE pTexture,  //�e�N�X�`��	
	////		      :   float Radius1						//�~�̒��a1
	////		      :   float Radius2						//�~�̒��a2
	////			  :   float Lenght						//����
	////		      :   D3DXVECTOR3 &vRot				//��]�p
	////		      :   D3DXVECTOR3 &vPos				//�ʒu
	////              :   D3DCOLORVALUE& Diffuse,		//�f�B�t���[�Y�F
	////              :   D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////              :   D3DCOLORVALUE& Ambient,		//�A���r�G���g�F
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�{�����V
	//// ���l       �F
	////	
	PrimitiveCylinder(
			LPDIRECT3DDEVICE9 pD3DDevice,
			LPTATRATEXTURE pTexture,
			float Radius1,
			float Radius2,
			float Lenght,
			D3DXVECTOR3 &vRot,
			D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,
			D3DCOLORVALUE& Specular,
			D3DCOLORVALUE& Ambient,
			wiz::OBJID id = OBJID_3D_CYLINDER)
    :Cylinder(pD3DDevice, Radius1, Radius2, Lenght,
			  vPos, vRot, Diffuse, Specular, Ambient,id, false, pTexture)
	{
		
	}
	
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class PrimitiveBox : public Box {
public:
	PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		wiz::OBJID id = OBJID_3D_BOX,
		LPTATRATEXTURE pTexture = 0)
		:Box( pD3DDevice, g_vOne, g_vZero, g_vZero, Diffuse, Specular, Ambient, id, false, pTexture, PtnUV_1_4)
	{
	}


};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class PrimitiveSphere : public Sphere {
	public:
		PrimitiveSphere(
			const LPDIRECT3DDEVICE9		pD3DDevice	,
			const D3DCOLORVALUE&		Diffuse		,
			const D3DCOLORVALUE&		Specular	,
			const D3DCOLORVALUE&		Ambient		,
			const LPTATRATEXTURE		pTexture	= 0,
			const wiz::OBJID			id			= OBJID_3D_SPHERE
		)
			:Sphere( pD3DDevice,0.5f, g_vZero, g_vZero,Diffuse, Specular, Ambient,id, false, pTexture ,18, 18){}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class PrimitivePlate {
protected:
	LPTATRATEXTURE		m_pTexture	;
	D3DXMATRIX				m_mMatrix	;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	D3DXVECTOR3				m_vPos;
	float					m_vCameraY;

	//	: ���_�f�[�^�̒�`
	struct	Vertex
	{
		D3DXVECTOR3	vPos ;		//	: ���_�́A�ʒu���W�f�[�^������
		DWORD		dwColor ;	//	: ���_�́A�F�f�[�^������
		D3DXVECTOR2	vTex ;		//	: ���_�́A�e�N�X�`�����W������

		//	: �f�t�H���g�R���X�g���N�^
		Vertex()
		{}
		//	: ���������ȗ������邽�߂̈����t���R���X�g���N�^
		Vertex( const D3DXVECTOR3& i_vPos, DWORD i_dwColor, const D3DXVECTOR2& i_vTex )
			: vPos( i_vPos ), dwColor( i_dwColor ), vTex( i_vTex )
		{}
		//	: �f�X�g���N�^
		~Vertex()
		{}

		//	: ���̒��_�f�[�^�̌`����Ԃ�
		static DWORD	getFVF()
		{
			return D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ;
		}

		//	: ���̒��_�f�[�^�̃f�[�^�T�C�Y��Ԃ�
		static int		getSize()
		{
			return sizeof( Vertex );
		}
	};
	Vertex	*v ;	//	: ���_�o�b�t�@������钸�_�f�[�^�ւ̃|�C���^���i�[���邽�߂̃|�C���^

public:
	PrimitivePlate(LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE i_pTexture = NULL, Color i_Color = 0xFFFF0000);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�K�C�h���C����`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �FObject�N���X�̏������z�֐�
	////            �F
	////
	virtual void Draw(DrawPacket& i_DrawPacket) ;
	virtual void Update(int i_iPtn) ;
	void setMatrix(D3DXMATRIX& i_mMatrix){
		m_mMatrix = i_mMatrix ;
	}

	D3DXVECTOR3	getPos(){
		return	v->vPos;
	}
	void setMatrixPos( D3DXVECTOR3 i_vPos ){
		D3DXMATRIX	mPos;
		D3DXMatrixTranslation( &mPos, i_vPos.x, i_vPos.y, i_vPos.x );
		m_mMatrix = mPos ;
	}
};

//***********************************************
class PlateObject : public PrimitivePlate, Object{
public:
	PlateObject(LPDIRECT3DDEVICE9 pD3DDevice, LPTATRATEXTURE i_pTexture = NULL, Color i_Color = 0xFFFF0000)
		:PrimitivePlate( pD3DDevice, i_pTexture, i_Color)
		,Object( OBJID_UNK )
	{
	}
};

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
inline D3DXVECTOR3 T2DPointTo3DPoint(Camera* i_pCamera,Point po){
	if( !i_pCamera ) return g_vZero ;
	float fXMagnification		= 50.0f / STANDARD_WINDOW_WIDTH ;		//	: �L�k�䗦
	float fXHalfCorrection		= po.x - (STANDARD_WINDOW_WIDTH /2) ;	//	: 

	float fYMagnification		= 28.3f / STANDARD_WINDOW_HEIGHT;		//	: �L�k�䗦
	float fYReverseCoordinate	= (STANDARD_WINDOW_HEIGHT /2)  -po.y ;	//	: �n�[�t���W��
	//	: �}�E�X���W�̂R�c�ϊ�
	return D3DXVECTOR3( 
		(    fXHalfCorrection * fXMagnification ) + i_pCamera->getEye().x ,
		( fYReverseCoordinate * fYMagnification ) + i_pCamera->getEye().y ,
		0.0f
	);
}
inline Point T3DPointTo2DPoint(Camera* i_pCamera,D3DXVECTOR3 po){
	if( !i_pCamera ) return Point(0,0) ;
	float fXMagnification		= 50.0f / STANDARD_WINDOW_WIDTH ;		//	: �L�k�䗦
	float fXHalfCorrection		= po.x  / fXMagnification - i_pCamera->getEye().x / fXMagnification ;

	float fYMagnification		= 28.3f / STANDARD_WINDOW_HEIGHT;		//	: �L�k�䗦
	float fYReverseCoordinate	= po.y  / fYMagnification - i_pCamera->getEye().y / fYMagnification ;

	float x =    fXHalfCorrection     +  (STANDARD_WINDOW_WIDTH /2) ;
	float y =    -fYReverseCoordinate + (STANDARD_WINDOW_HEIGHT /2) ;
	return Point( (int)x , (int)y );

}
class Cursor3D : public Cursor2D{
	static D3DXVECTOR3	m_vMousePos;
public:
	static D3DXVECTOR3 getPos(Camera* i_pCamera);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************
// class DrawSphere : public Object;
//
// �S����  ; ���� �O
// �p�r    : Sphere�̉���
//**************************************************************************
class DrawSphere : public Sphere{
	IDirect3DVertexBuffer9* m_pVB;
	//�N���X���\����
	//�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
	SPHERE m_TargetSphere ;
	static bool isEnableDraw ;
public:
	/////////////////// ////////////////////
	//// �֐���     �FDrawSphere(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FSphere
	//// ����       �F  
	//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	DrawSphere(LPDIRECT3DDEVICE9 pD3DDevice, SPHERE i_Sphere, Color i_Color = 0xFF0000FF, wiz::OBJID id = OBJID_3D_DRAWOBB);

	/////////////////// ////////////////////
	//// �֐���     �FDrawSphere::~DrawSphere()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�K�C�h���C���j��������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	virtual ~DrawSphere();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�K�C�h���C����`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �FObject�N���X�̏������z�֐�
	////            �F
	////
	virtual void Draw(DrawPacket& i_DrawPacket) ;

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	////            �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	void UpdateSPHERE( SPHERE i_SPHERE){
		m_TargetSphere = i_SPHERE ;
		SetBaseScale( g_vOne * i_SPHERE.m_Radius );
		SetBasePos( m_TargetSphere.m_Center );
	}
};


//**************************************************************************
// class DrawOBB : public Object;
//
// �S����  ; ���� �O
// �p�r    : OBB�̉���
//**************************************************************************
class DrawOBB : public Object{
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	float	m_fTimeAccumulator;

	//�N���X���\����
	//�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 vec;
		DWORD color;
	};
	OBB m_TargetObb ;
	static bool isEnableDraw ;
public:
	/////////////////// ////////////////////
	//// �֐���     �FGuide(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�K�C�h���C������������
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	DrawOBB(LPDIRECT3DDEVICE9 pD3DDevice, OBB i_OBB, Color i_Color = 0xFFFF0000, wiz::OBJID id = OBJID_3D_DRAWOBB);
	/////////////////// ////////////////////
	//// �֐���     �FGuide::~Guide()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�K�C�h���C���j��������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	virtual ~DrawOBB();
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�K�C�h���C����`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �FObject�N���X�̏������z�֐�
	////            �F
	////
	virtual void Draw(DrawPacket& i_DrawPacket) ;


};
//**************************************************************************
// class DrawOBBLite : public Object;
//
// �S����  ; ���� �O
// �p�r    : OBB�̉���
//**************************************************************************
class DrawOBBLite : public Object{
	IDirect3DVertexBuffer9* m_pVB;
	float m_fTimeAccumulator;
	//�N���X���\����
	//�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 vec;
		DWORD color;
	};
	OBB m_TargetObb ;
	static bool isEnableDraw ;
	/////////////////// ////////////////////
	//// �֐���     �FGuide(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�K�C�h���C������������
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	DrawOBBLite(LPDIRECT3DDEVICE9 pD3DDevice, OBB i_OBB, Color i_Color, wiz::OBJID id = OBJID_3D_DRAWOBB);
public:
	/////////////////// ////////////////////
	//// �֐���     �FGuide::~Guide()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�K�C�h���C���j��������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	virtual ~DrawOBBLite();
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�K�C�h���C����`��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �FObject�N���X�̏������z�֐�
	////            �F
	////
	virtual void Draw(DrawPacket& i_DrawPacket) ;

	static void Add(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec, OBB i_OBB, Color i_Color = 0xFFFF0000){
		#ifdef ON_DEBUGGINGPROCESS
			if( isEnableDraw ){
				Vec.push_back( new DrawOBBLite(pD3DDevice, i_OBB, i_Color) );
			}
		#endif
	}

};

	}//end of namespace baseitems.
	using namespace baseitems;
}//end of namespace wiz.
