////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FBassItems.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
//	namespace wiz;
//		union Color                :				# DWORD�\�L�J���[���g���₷�����Ă݂�(�g���₷���Ǝv���摽���c)����
//		class Camera               : public Object ;		# �J����
//		class Guide                : public Object ;		# �K�C�h���C��
//		class CommonMesh           ;						# ���b�V���������Ƃ��Ɍp������ƕ֗��ȃN���X
//			class MultiCommonMesh      : public CommonMesh ;	# �����悤�ȓ��������قȂ�`��̃��b�V������肽�����Ɍp������ƕ֗��ȃN���X
//		class LoadMeshFromX        : public CommonMesh ;	#
//			class ThinPlate            ;						# �����̂悤�Ȃ��̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveSprite      ;						# 2�����I��UI�����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveBox         : public CommonMesh      ;		# �����̏�̕������Ƃ��Ɍp������ƕ֗��ȃN���X
//			class PrimitiveMultiBox    : public PrimitiveBox    ;		# �����̎����悤�ȓ�������闧���̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//		class PrimitiveSphere      : public CommonMesh      ;		# ����̕������Ƃ��Ɍp������ƕ֗��ȃN���X
//			class PrimitiveMultiSphere : public PrimitiveSphere ;		# �����̎����悤�ȓ�������鋅�̂����Ƃ��Ɍp������ƕ֗��ȃN���X
//			class BoxObject            : public PrimitiveBox    , public Object          ;		# �ȒP�ȃ{�b�N�X�����N���X
//			class SpriteObject         : public Object          , public PrimitiveSprite ;		# �ȒP�ȃX�v���C�g�����N���X
//
//
#pragma once
#include "Object.h"
#include "AnimationModelClass/AnimationModelClass.h"
#include "TL-String.h"
namespace wiz {


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

//**************************************************************************
// class Motion;
//
// �S����  : ���� �O
// �p�r    : ���[�V����
//**************************************************************************
class Motion{
public:
	virtual void Update(D3DXVECTOR3& i_vScale, D3DXVECTOR3& i_vRot, D3DXVECTOR3& i_vPos) = 0;
};


//**************************************************************************
// class Camera : public Object;
//
// �S����  : (�R�m��搶�̂ЂȌ`���)
// �p�r    : �J�����N���X
//**************************************************************************
class Camera : public Object{
    D3DXMATRIX  m_View;     // �J�����̔z�u
    D3DXVECTOR3 m_Eye;      //�J�����̈ʒu
    D3DXVECTOR3 m_At;       //�����_
    FLOAT m_Near;           //�ˉe�̎�O���̋���
    FLOAT m_Far;            //�ˉe�̉����̋���
    FLOAT m_FovY;           //�ˉe�p�x
	//float CameraKyori;
	bool CameraFlg;
public:
/////////////////// ////////////////////
//// �֐���     �FCamera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�J�����̐���������
//// ����       �F  D3DXVECTOR3& Eye,   //�J�����̈ʒu
////            �F  D3DXVECTOR3& At,    //�����_
////            �F  FLOAT Near,         //�ˉe�̎�O���̋���
////            �F  FLOAT Far,          //�ˉe�̉����̋���
////            �F  FLOAT FovY          //�ˉe�p�x
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY,wiz::OBJID id = OBJID_SYS_CAMERA);
/////////////////// ////////////////////
//// �֐���     �F~Camera()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�J�����̔j��������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    virtual ~Camera();
/////////////////// ////////////////////
//// �֐���     �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�J�������X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState	//�R���g���[���̃X�e�[�^�X
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Update(UpdatePacket& i_UpdatePacket);

/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�J������ݒu
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket);

/////////////////// ////////////////////
//// �֐���     �Fvoid setTarget(D3DXVECTOR3 vPos)
//// �J�e�S��   �F�Z�b�^�[
//// �p�r       �F���_��ݒ�
//// ����       �F  D3DXVECTOR3 vPos		//	���_
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	void setTarget(D3DXVECTOR3 vPos,D3DXVECTOR3& vCPos/*,D3DXVECTOR3& vCEPos*/);
/////////////////// ////////////////////
//// �֐���     �FD3DXVECTOR3 getEye()
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F�J�������W���l��
//// ����       �F  D3DXVECTOR3 vPos		//	���_
//// �ߒl       �F�J�����̍��W
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	D3DXVECTOR3 getEye(){return m_Eye;};
};


//**************************************************************************
// class Guide : public Object;
//
// �S����  ; (�R�m��搶�̂ЂȌ`���)
// �p�r    : �K�C�h�N���X�ix�Ay�Az�����ɐL�т�K�C�h���j
//**************************************************************************
class Guide : public Object{
    IDirect3DVertexBuffer9* m_pVB;
    //�N���X���\����
    //�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };
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
	Guide(LPDIRECT3DDEVICE9 pD3DDevice,wiz::OBJID id = OBJID_SYS_GUIDELINE);
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
    virtual ~Guide();
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
// class CommonMesh ;
//
// �S����  ; (�R�m��搶�̂ЂȌ`���)
// �p�r: �R�������b�V���N���X
//       ���b�V���������Ƃ��Ɍp������ƕ֗�
//**************************************************************************
class CommonMesh {
protected:
    //���b�V��
    LPD3DXMESH   m_pMesh;

    //�}�e���A��
    D3DMATERIAL9 m_Material;

    //���݂̃I�u�W�F�N�g�̃}�g���b�N�X
	D3DXMATRIX   m_mMatrix;

	//�T�u�Z�b�g
	DWORD        m_dwDrawSubset;

/////////////////// ////////////////////
//// �֐���     �FCommonMesh( D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F  D3DXVECTOR3 pos,				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient			//�A���r�G���g�F
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ɨ������I�u�W�F�N�g�����̃R���X�g���N�^
////            �F
////
  CommonMesh( D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/////////////////// ////////////////////
//// �֐���     �FCommonMesh::CommonMesh()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// ���l       �F�}���`�I�u�W�F�N�g�����̃R���X�g���N�^
////            �F
////
  CommonMesh( );
/////////////////// ////////////////////
//// �֐���     �FCommonMesh::~CommonMesh()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�j��������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    virtual ~CommonMesh();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
public:
	LPD3DXMESH getMesh(){ return m_pMesh; };
};
//**************************************************************************
// class LoadMeshFromX : public MultiCommonMesh;
//
// �S����  : ���� �O
// �p�r    : x�t�@�C�������ƂɃ��b�V�����쐬
//             ���f���f�[�^��ǂݍ���Ń��b�V������肽�����Ɍp����ƕ֗�
//	           �����Ȃ�
//**************************************************************************
class LoadMeshFromX : public CommonMesh{
protected:
	//**************************************************************************
	// struct LoadMeshFromX::MaterialItem;
	//
	// �S����  : ���� �O
	// �p�r    : �}�e���A���\����
	//**************************************************************************
	struct MaterialItem{
		LPDIRECT3DTEXTURE9 m_pTexture;	//	: �e�N�X�`���[
		D3DMATERIAL9       m_Material;	//	: �}�e���A��
		void init(LPDIRECT3DDEVICE9 pD3DDevice,D3DXMATERIAL d3dxMaterials,
				TextureManager& TexMgr,const wchar_t* pDirPath,const wchar_t* pFileName = NULL)
		{
			m_Material			= d3dxMaterials.MatD3D;
			m_Material.Ambient	= m_Material.Diffuse; // ?�Ȃɂ���
			m_pTexture			= NULL;

			if(	( pFileName != NULL && lstrlen(pFileName)  > 0 )  ||
				( d3dxMaterials.pTextureFilename != NULL &&
				 lstrlen((LPCWSTR)d3dxMaterials.pTextureFilename) > 0) )
			{
				wstring sFilePath, sFileName;
				if(pFileName)	sFileName = pFileName ;
				else			TLIB::widen(d3dxMaterials.pTextureFilename,sFileName);
				sFilePath		= pDirPath ;
				m_pTexture		= TexMgr.addTexture(pD3DDevice,(sFilePath + sFileName).c_str());
			}
		}
	};
	//**************************************************************************
	// static LoadMeshFromX::MaterialItems;
	//
	// �S����  : ���� �O
	// �p�r    : �s���葽���̃}�e���A����ێ�����
	//**************************************************************************
	struct MaterialItems{		
		DWORD			m_MaterialQty;		//	: �}�e���A������
		MaterialItem*	m_Material;			//	: �}�e���A��
		void init(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXBUFFER pD3DXMtrlBuffer,
				DWORD materialQty,TextureManager& TexMgr,const wchar_t* pDirPath,const wchar_t* pFileName = NULL)
		{
			m_MaterialQty	= materialQty;
			m_Material		= new MaterialItem[m_MaterialQty];
			D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
			for(DWORD i=0; i<m_MaterialQty; i++)
			{
				this->m_Material[i].init(pD3DDevice,d3dxMaterials[i],TexMgr,pDirPath,pFileName);
			}
		}
		~MaterialItems(){
			SafeDeleteArr( m_Material );
		}
	};
	//**************************************************************************
	// static LoadMeshFromX::MaterialItems;
	//
	// �S����  : ���� �O
	// �p�r    : ���b�V���ɕK�v�ȃf�[�^
	//**************************************************************************
	struct MeshItem{
	    //���b�V��
		string				m_sTextureName	;	// �e�N�X�`������
		LPDIRECT3DTEXTURE9	m_pTexture		;	// �}�e���A��
		LPD3DXMESH			m_pMesh			;	// �߂�����
		AABB				m_AABB			;	// OBB
		bool				m_bHidden		;	// �B��
		MeshItem():m_pTexture(NULL){};
		MeshItem(LPDIRECT3DDEVICE9 pD3DDevice, MeshItem& other)
			:m_pTexture(NULL){
			DWORD option = other.m_pMesh->GetOptions() ;
			DWORD fvf    = other.m_pMesh->GetFVF();
			m_bHidden    = true ;
			other.m_pMesh->CloneMeshFVF(option,fvf,pD3DDevice,&this->m_pMesh);
		};
	};
	MaterialItems     m_MaterialItems;	// �}�e���A��
	MeshItem          m_BassMesh;		// �x�[�X�ɂȂ郁�b�V��
	string            m_sFileName;		// �t�@�C���� �f�[�^�̍��v�m�F�Ɏg���܂�
	LPDIRECT3DDEVICE9 pD3DDevice;		// �f�o�C�X(�����ɂ���??)
	vector<MeshItem*> m_MeshItems;		// ���b�V���������ς��͂����Ă�
	LoadMeshFromX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,TextureManager& TexMgr,char *pTexName = NULL);
	virtual ~LoadMeshFromX(){
		SafeDeletePointerContainer( m_MeshItems );
	};
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F���z�����o�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Tempus2* i_DrawPacket.pTime                 // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^
////            �F  vector<Object*>& Vec            // �I�u�W�F�N�g�̔z��
////            �F  Command& i_DrawPacket.pCommand                    // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����		�F���� �O
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
/////////////////// ////////////////////
//// �֐���     �Fvoid subsetDraw( DrawPacket& i_DrawPacket)
//// �J�e�S��   �F���z�����o�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Tempus2* i_DrawPacket.pTime                 // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^
////            �F  vector<Object*>& Vec            // �I�u�W�F�N�g�̔z��
////            �F  Command& i_DrawPacket.pCommand                    // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
    void subsetDraw(DrawPacket& i_DrawPacket) ;
public:
/////////////////// ////////////////////
//// �֐���     �Fvoid Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos)
//// �J�e�S��   �F���J�����o�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  D3DXVECTOR3& vScale
////            �G  D3DXVECTOR3& vRot
////            �F  D3DXVECTOR3& vPos
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual void Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos,
		LPDIRECT3DDEVICE9 pD3DDevice = NULL, TextureManager* pTexMgr = NULL, wstring pTexName = L"");
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
	bool CheckSame(string i_sXFilePath);
};
//**************************************************************************
// class LoadAnimationModel;
//
// �S����  : ���� �O
// �p�r    : x�t�@�C�������ƂɃ��b�V�����쐬
//           ���f���f�[�^��ǂݍ���Ń��b�V������肽�����Ɍp����ƕ֗�
//**************************************************************************
class LoadAnimationModel {
protected:
	AnimationModel* m_pAnmModel;
	D3DXMATRIX		m_mMatrix;
	friend	class LAMEnemy;
public:
	LoadAnimationModel(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,
		D3DXVECTOR3 size,D3DXVECTOR3 rot, D3DXVECTOR3 pos,
		float InitialTracSpeed = 1.0f,DWORD InitialTrac = 0);
	virtual ~LoadAnimationModel(){
		SAFE_RELEASE(m_pAnmModel);
	};
	
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
};

//**************************************************************************
// class PrimitiveBox : public CommonMesh;
//
// �S����  : (�R�m��搶�̂ЂȌ`���)
// �p�r    : �����̃N���X
//           �����̂̕��̂���肽�����ȂǂɌp������ƕ֗�
//**************************************************************************
class PrimitiveBox : public CommonMesh {
/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveBox::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
//// �J�e�S��   �F�֐�
//// �p�r       �F�{�b�N�X���b�V���𐶐�
//// ����       �F  	LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  	LPDIRECT3DTEXTURE9 pTexture = 0	//	�e�N�X�`��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	void CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture);
protected:
/////////////////// ////////////////////
//// �֐���     �Fvoid VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v)
//// �J�e�S��   �F���z�֐�
//// �p�r       �FVector�Ɩ@������U��V�����o��
//// ����       �F  D3DXVECTOR3 vec,	//���_
////            �F  D3DXVECTOR3 normal,	//�@��
////            �F  float& u,			//�ϊ�����u�i�e�N�X�`�����U���W�j
////            �F  float& v			//�ϊ�����v�i�e�N�X�`�����V���W�j
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
////            �F
////
	void VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v);
	LPDIRECT3DTEXTURE9 m_pTexture;
	//	�e�N�X�`��������ꍇ�̒��_�t�H�[�}�b�g�̒�`
	// D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1
	// ���\���̉����Ă���
	struct  PlateVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 normal;
		FLOAT       tu,tv;
	};
	//PrimitiveBox�p��FVF��DIrectXAPI�ɓn���Ƃ��̃p�����[�^
	enum { PlateFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
/////////////////// ////////////////////
//// �֐���     �FPrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
////            �F  	D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////            �F  	LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ����s���͗�O��throw�j
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ɨ��I�u�W�F�N�g�����R���X�g���N�^
////            �F
////
	PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// �֐���     �FPrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ����s���͗�O��throw�j
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ɨ��I�u�W�F�N�g�����R���X�g���N�^
////            �F
////
    PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// �֐���     �Fvirtual ~PrimitiveBox()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    virtual ~PrimitiveBox();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�����̂�`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

};

//**************************************************************************
// class PrimitiveSphere : public CommonMesh;
//
// �S����  : (�R�m��搶�̂ЂȌ`���)
// �p�r    : ���̃N���X
//**************************************************************************
class PrimitiveSphere : public CommonMesh {
	// D3DFVF_XYZ | D3DFVF_TEX1
	// ���\���̉����Ă���
	struct  SphereVertex{
		D3DXVECTOR3 vec;
		D3DXVECTOR3 n;
		FLOAT       tu,tv;
	};
	//PrimitiveSphere�p��FVF��DIrectXAPI�ɓn���Ƃ��̃p�����[�^
	enum { BallFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
		LPDIRECT3DTEXTURE9 m_pTexture;
/////////////////// ////////////////////
//// �֐���     �Fvoid Vec2UV(float x,float y,float z,float r,float& u,float& v );
//// �J�e�S��   �F�����o�֐�
//// �p�r       �FVector��U��V�ɃR���o�[�g
//// ����       �F  float x     //x�̒l
////            �F  float y     //y�̒l
////            �F  float z     //z�̒l
////            �F  float r     //���̔��a
////            �F  float& u    //�ϊ�����u�i�e�N�X�`�����U���W�j
////            �F  float& v    //�ϊ�����v�i�e�N�X�`�����V���W�j
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O(�R�m��搶�̂ЂȌ`���)
//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
////            �F
////
	void Vec2UV(float x,float y,float z,float r,float& u,float& v);
/////////////////// ////////////////////
//// �֐���     �Fvoid CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
//// �J�e�S��   �F�֐�
//// �p�r       �F���𐶐�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
////            �F
////
	void CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice);
protected:
/////////////////// ////////////////////
//// �֐���     �FPrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);

/////////////////// ////////////////////
//// �֐���     �FPrimitiveSphere( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture = 0);
/////////////////// ////////////////////
//// �֐���     �F~PrimitiveSphere();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F���̂�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    virtual ~PrimitiveSphere();

/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���̂�`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;
};
//**************************************************************************
// class PrimitiveSprite ;
//
// �S����  : ���� �O
// �p�r    : �QD���̃X�v���C�g�N���X
//**************************************************************************
class PrimitiveSprite {
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;	//	: �`�悷��e�N�X�`��
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	D3DXMATRIX		m_mMatrix;		//	: �}�g���b�N�X (�h���N���X�͂����ɍ��W�f�[�^������)
	D3DXVECTOR3		m_vOffsetPos;	//	: �e�N�X�`���[�̕`��I�t�Z�b�g(��{�͂O�l�_);
	D3DXVECTOR3		m_vCenter;		//	: �e�N�X�`���[�̒��S
	RECT*			m_pRect;		//	: �e�N�X�`���[�̕`��̈�
	Color			m_Color;
public:
/////////////////// ////////////////////
//// �֐���     �FPrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,D3DCOLOR color = 0xFFFFFFFF);
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
////            �F  LPDIRECT3DTEXTURE9 pTexture,	//	: �e�N�X�`���[�ւ̃|�C���^
////            �F  RECT*			Rect,			//	: �e�N�X�`���̕`��͈�
////            �F  D3DXVECTOR3&	vCenter,		//	: ���S�ʒu
////            �F  D3DXVECTOR3&	vOffsetPos,		//	: ���[�J�����W
////            �F  D3DCOLOR		color			//	: �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
/////////////////// ////////////////////
//// �֐���     �Fvirtual ~PrimitiveSprite()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual ~PrimitiveSprite();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual void Draw(DrawPacket& i_DrawPacket);
};

//**************************************************************************
// class SpriteObject : public Object ,public PrimitiveSprite ;
//
// �S����  : ���� �O
// �p�r    : �X�v���C�g���Ƃ肠�����`�悷�邽�߂̃N���X
//           ���̓�������Ȃ��Ƃ肠�����X�v���C�g��`�悵�������ɂ�������
//**************************************************************************
class SpriteObject : public Object ,public PrimitiveSprite{
public:
/////////////////// ////////////////////
//// �֐���     �FSpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture     // �\��t�������e�N�X�`��
////            �F  D3DXVECTOR3 &vScale             // �傫��
////            �F  D3DXVECTOR3 &vRot               // �O����]
////            �F  D3DXVECTOR3 &vPos               // �ݒu���W
////            �F  RECT* pRect                     // �`�悵�����͈�(NULL�őS�̂�`��)
////            �F  D3DXVECTOR3& vCenter            // ���S
////            �F  D3DXVECTOR3& vOffsetPos         // �I�t�Z�b�g���W
////            �F  Color color = 0xFFFFFFFF        // �F
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF,
			wiz::OBJID id = OBJID_UI_SPRITE);
/////////////////// ////////////////////
//// �֐���     �F~SpriteObject();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual ~SpriteObject();
/////////////////// ////////////////////
//// �֐���     �Fvoid Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	virtual void Draw(DrawPacket& i_DrawPacket);
};
/**************************************************************************
 class Sound: public Object;
 �p�r: �T�E���h�N���X
****************************************************************************/
class Sound : public Object{
protected:
	IXACT3Engine* m_pEngine;
	IXACT3WaveBank* m_pWaveBank;
	IXACT3SoundBank* m_pSoundBank;
	VOID* m_pbWaveBank; // Handle to wave bank data.  Its memory mapped so call UnmapViewOfFile() upon cleanup to release file
	VOID* m_pbSoundBank; // Pointer to sound bank data.  Call delete on it when the sound bank is destroyed
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName);
/**************************************************************************
 virtual ~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Sound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/**************************************************************************
 class ZapSound: public Sound;
 �p�r: Zap�T�E���h�N���X
****************************************************************************/
class ZapSound : public Sound{
	XACTINDEX m_iZap;
	XACTINDEX m_iFire;
	XACTINDEX m_iBGM;
	XACTINDEX m_iBS;
	XACTINDEX m_iGET;
	XACTINDEX m_iHANAB1;
	XACTINDEX m_iHANAB2;
public:
/**************************************************************************
 ZapSound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 const char* pZapKey				//�������̃L�[
 const char* pFireKey				//���ˉ��̃L�[
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
		const char* pZapKey,const char* pFireKey,const char* BGM,const char* BS,const char* GET,const char* HANAB1,const char* HANAB2);
/**************************************************************************
 virtual ~ZapSound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~ZapSound();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
	void Draw(DrawPacket& i_DrawPacket){};
/**************************************************************************
 void PlayZap();
 �p�r: ������炷
 �߂�l: �Ȃ��B
***************************************************************************/
    void PlayZap();
/**************************************************************************
 void PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
    void PlayFire();
/**************************************************************************
 void BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
    void BGM();
/**************************************************************************
 void PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
    void BS();
/**************************************************************************
 void BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
    void GET();

/**************************************************************************
 void BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
    void HANAB1();
/**************************************************************************
 void BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
    void HANAB2();
};
}