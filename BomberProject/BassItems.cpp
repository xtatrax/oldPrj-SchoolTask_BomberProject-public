////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FMagnetica
//	�t�@�C����		�FBassItems.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F�Q�[���̃x�[�X�ɂȂ�A�C�e���Q�̐錾
//					��
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

namespace baseobject{

/**************************************************************************
 Camera ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FCamera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY)
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
Camera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,FLOAT Near,FLOAT Far,FLOAT FovY,wiz::OBJID id)
:Object(id),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)/*,CameraKyori(0.0f)*/,CameraFlg(true)
{
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
}
/////////////////// ////////////////////
//// �֐���     �FCamera::~Camera()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�J�����̔j��������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
Camera::~Camera(){
}
/////////////////// ////////////////////
//// �֐���     �Fvirtual voidCamera:: Update( LPDIRECT3DDEVICE9 pD3DDevice
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
void Camera::Update(UpdatePacket& i_UpdatePacket
	){

#ifdef DEBUG_KEYMOVE_CAMERA_ON
	if(pCntlState[0].Gamepad.fThumbLX > 0){
		CameraFlg = true;
	}

	if(pCntlState[0].Gamepad.fThumbLX < 0){
		CameraFlg = false;
	}

    if(pCntlState[0].bConnected){
		//D�p�b�h��
		//�����_Y����
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP){
			m_Eye.y += 0.1f;
			//MAX5.0
            //if(m_Eye.y > 5.0f){
            //    m_Eye.y = 5.0f;
            //}
        }
		//D�p�b�h��
		//�����_Y����
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN){
			m_Eye.y -= 0.1f;
			//MIN0.0
            //if(m_Eye.y < 0.0f){
            //    m_Eye.y = 0.0f;
            //}
        }
		////�J�����ʒu�ƒ����_�̊Ԃ̃x�N�g�����Z�o
		//D3DXVECTOR3 span = m_Eye - m_At;
		////���K��
		//D3DXVec3Normalize(&span,&span);
		////����
		//span = span * 0.1f;
		//D�p�b�h��
		//�J����������
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT){
			//�J�����ʒu������
			m_Eye.z += 0.1f;
			//MAX5.0
            //if(m_Eye.z > 50.0f){
            //    m_Eye.z= 50.0f;
            //}
        }
		//D�p�b�h�E
		//�J���������
        if(pCntlState[0].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT){
			//�J�����ʒu�����
			m_Eye.z -= 0.1f;
			//MAX5.0
            //if(m_Eye.z < -50.0f){
            //    m_Eye.z= -50.0f;
            //}
        }
		//D�p�b�h��
		//�J����������
		if(pCntlState[0].Gamepad.bLeftTrigger){
			//�J�����ʒu������
			m_Eye.x += 0.1f;
			//MAX5.0
            //if(m_Eye.x > 50.0f){
            //    m_Eye.x= 50.0f;
            //}
        }
		//D�p�b�h�E
		//�J���������
		if(pCntlState[0].Gamepad.bRightTrigger ){
			//�J�����ʒu�����
			m_Eye.x -= 0.1f;
			//MAX5.0
            //if(m_Eye.x < -50.0f){
            //    m_Eye.x= -50.0f;
            //}
        }
    }
#endif
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Camera::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�J������ݒu
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
void Camera::Draw(DrawPacket& i_DrawPacket) {
    // �r���[�|�[�g�̎擾
    D3DVIEWPORT9 vp;
    if(FAILED(i_DrawPacket.pD3DDevice->GetViewport(&vp))){
        return;
    }
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));

    // �A�X�y�N�g��̌v�Z
    float AspectRate;
    AspectRate = (float)vp.Width / (float)vp.Height;
    // �ˉe�s��̏�����
    D3DXMATRIX mProj;
    D3DXMatrixIdentity(&mProj);
    D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(m_FovY), AspectRate,m_Near,m_Far);
    // �ˉe�s��̐ݒ�
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_PROJECTION,&mProj);
    // �J�����̐ݒ�
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}
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
void Camera::setTarget(D3DXVECTOR3 vPos,D3DXVECTOR3& vCPos/*,D3DXVECTOR3& vCEPos*/){

	if(CameraFlg == true && m_Eye.x < vPos.x){
	m_Eye.x = m_At.x = vPos.x;
	}
	//CameraKyori = m_Eye.x - 7.0f;
	//if(vPos.x <= CameraKyori){
	//	vPos.x = CameraKyori;
	//}
	vCPos = this->m_Eye;
	//vCEPos = this->m_Eye;
}

/**************************************************************************
 class Guide ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FGuide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�K�C�h���C������������
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
//// �ߒl       �F�����i���s���͗�O��throw�j
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice,wiz::OBJID id)
    :Object(id),m_pVB(0)
{
    try{
        CUSTOMVERTEX Vertices[] = 
        {
            {D3DXVECTOR3(-1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(0.0,-1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,0.0,-1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)},
            {D3DXVECTOR3(0.0,0.0,1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)}
        };
        if(FAILED(pD3DDevice->CreateVertexBuffer( 6 * sizeof( CUSTOMVERTEX ),
                                    0,D3DFVF_XYZ|D3DFVF_DIFFUSE,
                                    D3DPOOL_DEFAULT, &m_pVB, NULL)))
        {
            // ���������s
            throw DxException(
                L"���_�o�b�t�@�̍쐬�Ɏ��s���܂����B",
                L"Guide::Guide()"
                );
        }
        //�o�b�t�@�����b�N
        VOID* pVertices;
        if(FAILED( m_pVB->Lock( 0, sizeof(Vertices),( void** )&pVertices, 0 ))){
            // ���������s
            throw DxException(
                L"���_�o�b�t�@�̃��b�N�Ɏ��s���܂����B",
                L"Guide::Guide()"
                );
        }
        //���_�f�[�^���璸�_�o�b�t�@�ɓ]��
        memcpy( pVertices,Vertices, sizeof(Vertices) );
        //���_�o�b�t�@���A�����b�N
        m_pVB->Unlock();
    }
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pVB);
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �֐���     �FGuide::~Guide()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�K�C�h���C���j��������
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
Guide::~Guide(){
    SafeRelease(m_pVB);
}
/////////////////// ////////////////////
//// �֐���     �Fvoid Guide::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�K�C�h���C����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F����
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
void Guide::Draw(DrawPacket& i_DrawPacket) {
    D3DXMATRIX  wm;
    //���W�ϊ�����
    D3DXMatrixIdentity(&wm);
    // �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    i_DrawPacket.pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    i_DrawPacket.pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    i_DrawPacket.pD3DDevice->LightEnable( 0, FALSE );
    i_DrawPacket.pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    i_DrawPacket.pD3DDevice->LightEnable( 0, TRUE );
}



/**************************************************************************
 CommonMesh ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FCommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F  D3DXVECTOR3 pos,				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient			//�A���r�G���g�F
//// �ߒl       �F�����i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ɨ������I�u�W�F�N�g�����̃R���X�g���N�^
////            �F
////
CommonMesh::CommonMesh(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
:m_pMesh(0)     //�|�C���^�͂O������
,m_dwDrawSubset(0)
{
    try{
		D3DXMatrixIdentity( &m_mMatrix );
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
/////////////////// ////////////////////
//// �֐���     �FCommonMesh::CommonMesh()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F����
//// �ߒl       �F�����i���s���͗�O��throw�j
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// ���l       �F�}���`�I�u�W�F�N�g�����̃R���X�g���N�^
////            �F
////
CommonMesh::CommonMesh()
:m_pMesh(0)     //�|�C���^�͂O������
,m_dwDrawSubset(0)
{
    try{
		D3DXMatrixIdentity( &m_mMatrix );
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));

        D3DCOLORVALUE dDiffuse = {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE dSpecular = {0.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE dAmbient = {0.5f,0.5f,0.5f,1.0f};

        // ���f���̐F��ݒ�
        m_Material.Diffuse  = dDiffuse;
        m_Material.Specular = dSpecular;
        m_Material.Ambient  = dAmbient;
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �֐���     �FCommonMesh::~CommonMesh()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�C���X�^���X�j��������
//// ����       �F����
//// �ߒl       �F����
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
CommonMesh::~CommonMesh(){
    //��n��
	//�h���N���X�ł�Release�Y��΍�
    SafeRelease(m_pMesh);
}
/////////////////// ////////////////////
//// �֐���     �Fvoid CommonMesh::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F����
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
void CommonMesh::Draw(DrawPacket& i_DrawPacket) {
    //�����`�F�b�N
    if((!m_pMesh) || (!i_DrawPacket.pD3DDevice)){
        throw DxException(L"�f�o�C�X�����b�V���������ł��B",
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
    m_pMesh->DrawSubset(m_dwDrawSubset);
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
 LoadMeshFromX ��`��
****************************************************************************/
LoadMeshFromX::LoadMeshFromX(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName ,TextureManager& TexMgr,char *pTexName)
{
    try{
		D3DXMatrixIdentity(&m_mMatrix);
		//string sFileDir ;
		m_sFileName = pFileName;

		//size_t	pathLength ;
		//for(  pathLength = strlen(pFileName) ; pathLength >= 0 ; pathLength--  )
		//	if(  pFileName[ pathLength ] == '/' || pFileName[ pathLength ] == '\\'  )
		//		break ;
		//for(  size_t i = 0 ; i < pathLength ; i++  )
		//	sFileDir	+= pFileName[ i ] ;

        //���̍쐬
		// X�t�@�C�����烁�b�V�������[�h���� 
		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		DWORD dwMQty;
		if(FAILED(D3DXLoadMeshFromXA(pFileName,
								D3DXMESH_SYSTEMMEM,
								pD3DDevice,
								NULL,
								&pD3DXMtrlBuffer,
								NULL,
								&dwMQty,
								&m_BassMesh.m_pMesh))){
			string	 buf1 = pFileName ;
			wstring  buf2 ;
			TLIB::widen(buf1,buf2);
			wstring msg  = wstring(L"���f���f�[�^\"") + buf2 + wstring(L"\"��ǂݍ��߂܂���ł���");
			// ���������s
            throw DxException(
				msg.c_str(),
                L"LoadMeshFromX::LoadMeshFromX()"
                );
        }
		//
		//////////
		//	: �e�N�X�`���������C�h��
		wstring wsTexName  ;
		wchar_t* wpTexName = NULL;
		if(pTexName){
			wpTexName = new wchar_t[ strlen(pTexName) +1 ];
			size_t ret;
			mbstowcs_s(&ret, wpTexName, strlen(pTexName) +1, pTexName, strlen(pTexName) +1);
		}
		//
		//////////

		//TLIB::widen(sFileDir,wsFileDir);


		//D3DXMATERIAL d3dxMaterials = *(D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		this->pD3DDevice = pD3DDevice;
		m_MaterialItems.init(pD3DDevice,pD3DXMtrlBuffer,dwMQty,TexMgr,g_sDefaultTexturePath.c_str(),wpTexName);
		m_BassMesh.m_AABB = AABB(m_BassMesh.m_pMesh);
		delete [] wpTexName;
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pMesh);
        //�ăX���[
        throw;
    }

}
/////////////////// ////////////////////
//// �֐���     �Fvoid LoadMeshFromX::Draw( DrawPacket& i_DrawPacket)
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
void LoadMeshFromX::Draw(DrawPacket& i_DrawPacket){
	vector<MeshItem*>::size_type i = 0, sz = m_MeshItems.size();
	while(i < sz){
		m_pMesh = m_MeshItems[i]->m_pMesh;
		m_MaterialItems.m_Material[0].m_pTexture = m_MeshItems[i]->m_pTexture;
		subsetDraw(i_DrawPacket);
		i++;
	}
}
/////////////////// ////////////////////
//// �֐���     �Fvoid LoadMeshFromX::subsetDraw( LPDIRECT3DDEVICE9 pD3DDevice,
////            �F    Tempus2* i_DrawPacket.pTime,vector<Object*>& Vec,Command& i_DrawPacket.pCommand)
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
void LoadMeshFromX::subsetDraw(DrawPacket& i_DrawPacket){
	DWORD i = 0, dwLoop = m_MaterialItems.m_MaterialQty;
	while(i < dwLoop){
		m_dwDrawSubset = i;
		m_Material     = m_MaterialItems.m_Material[i].m_Material;
		LPDIRECT3DTEXTURE9  pTexture = m_MaterialItems.m_Material[i].m_pTexture;
		//�e�N�X�`��������ꍇ
		if(pTexture){
			DWORD wkdword;
			//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
			i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
			//�X�e�[�W�̐ݒ�
			i_DrawPacket.pD3DDevice->SetTexture(0,pTexture);
			//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		i++;
	}
}
/////////////////// ////////////////////
//// �֐���     �FvoidLoadMeshFromX:: Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos)
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
void LoadMeshFromX::Add(D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DXVECTOR3& vPos
		, LPDIRECT3DDEVICE9 pD3DDevice , TextureManager* pTexMgr , wstring pTexName )
{
	D3DXMATRIX mScale , mRot , mPos , mAll ;
	D3DXMatrixIsIdentity(&mScale);
	D3DXMatrixIsIdentity(&mRot);
	D3DXMatrixIsIdentity(&mPos);
	D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
	D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
	D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
	MeshItem* item = new MeshItem(this->pD3DDevice,m_BassMesh);
	mAll = (mScale*mRot*mPos) ;
	MeshTransformer(item->m_pMesh,mAll);
	item->m_AABB = AABB(item->m_pMesh);
	item->m_pTexture = m_BassMesh.m_pTexture;
	(pD3DDevice && pTexMgr && pTexName != L"" && (item->m_pTexture = pTexMgr->addTexture( pD3DDevice,wstring( g_sDefaultTexturePath + pTexName ).c_str() ) ) );
	m_MeshItems.push_back(item);
}
/////////////////// ////////////////////
//// �֐���     �Fbool LoadMeshFromX::CheckSame(string i_sXFilePath)
//// �J�e�S��   �F�`�F�b�J�[�Y
//// �p�r       �F�������f���f�[�^�����ׂ�
//// ����       �F  string i_sXFilePath       //  : �t�@�C���p�X
//// �ߒl       �F true  : ��v
////            �F false : �s��v
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
bool LoadMeshFromX::CheckSame(string i_sXFilePath){
	return (m_sFileName == i_sXFilePath);
}

/**************************************************************************
 LoadAnimationModel ��`��
****************************************************************************/
LoadAnimationModel::LoadAnimationModel(LPDIRECT3DDEVICE9 pD3DDevice,char *pFileName,
		D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR3 pos,
		float InitialTracSpeed ,DWORD InitialTrac )
{
	m_pAnmModel = new AnimationModel(pD3DDevice,pFileName);
	for( int i = 0 ; i < m_pAnmModel->getNumTracks() ; i++ )
		m_pAnmModel->setTrackSpeed( i, InitialTracSpeed );
	m_pAnmModel->setTrack(InitialTrac);

	D3DXMATRIX mScale,mRot,mPos;
	D3DXMatrixIdentity(&m_mMatrix);
	D3DXMatrixIdentity(&mScale);
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mPos);
	D3DXMatrixScaling(&mScale,size.x,size.y,size.z);
	D3DXMatrixRotationYawPitchRoll(&mRot,rot.y,rot.x,rot.z);
	D3DXMatrixTranslation(&mPos,pos.x,pos.y,pos.z);
	m_mMatrix = mScale * mRot * mPos;


}
/////////////////// ////////////////////
//// �֐���     �Fvoid LoadAnimationModel::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���b�V����`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �FObject�N���X�̏������z�֐�
////            �F
////
void LoadAnimationModel::Draw(DrawPacket& i_DrawPacket){

	m_pAnmModel->SetTransform( &m_mMatrix );
	m_pAnmModel->draw( i_DrawPacket.pD3DDevice, (float)i_DrawPacket.pTime->getElapsedTime() );

}





/**************************************************************************
 PrimitiveBox ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveBox::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v)
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
void PrimitiveBox::VecNomal2UV(D3DXVECTOR3 vec,D3DXVECTOR3 normal,float& u,float& v){
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
void PrimitiveBox::CreateBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture){
    try{
		SafeRelease(m_pMesh);
		//���̍쐬
		if(
			FAILED(
				D3DXCreateBox(
					pD3DDevice, 
					g_vOne.x,
					g_vOne.y,
					g_vOne.z,
					&m_pMesh, 
					NULL
				)
			)
		){
			// ���������s
			throw DxException(
				L"���̍쐬�Ɏ��s���܂����B",
				L"PrimitiveBox::PrimitiveBox()"
				);
		}
		//�e�N�X�`��������ꍇ
		if(m_pTexture){
			//�e�N�X�`���Ȃ��̃��b�V��
			LPD3DXMESH m_pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,PlateFVF,pD3DDevice,&m_pMesh2))){
				// ���������s
				throw DxException(
					L"�e�N�X�`���t�̕��̍쐬�Ɏ��s���܂����B",
					L"PrimitiveBox::PrimitiveBox()"
					);
			}
			//���̒i�K�Ńe�N�X�`�����Ȃ�m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�e�N�X�`�������郁�b�V������
			m_pMesh = m_pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			PlateVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			DWORD vsize = m_pMesh->GetNumVertices();
			for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
				//�@���ƒ��_����uv�l�𓾂�
				VecNomal2UV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
			}
			pVB->Unlock();
		}
    }
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pMesh);
        //�ăX���[
        throw;
    }

};
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
PrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(Diffuse,Specular,Ambient),m_pTexture(pTexture)
{
    try{
		CreateBox(pD3DDevice,pTexture);
	}
    catch(...){
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �֐���     �FPrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�C���X�^���X����������
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ����s���͗�O��throw�j
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F�Ɨ��I�u�W�F�N�g�����R���X�g���N�^
////            �F
////
PrimitiveBox::PrimitiveBox(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(),m_pTexture(pTexture)
{
    try{
		CreateBox(pD3DDevice,pTexture);
	}
    catch(...){
        //�ăX���[
        throw;
    }
}
/////////////////// ////////////////////
//// �֐���     �Fvirtual PrimitiveBox::~PrimitiveBox()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// �ߒl       �F�Ȃ�
//// �S����     �F(�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
PrimitiveBox::~PrimitiveBox(){
    //��n���i���b�V����Release��
	//CommonMesh�ōs�Ȃ��̂ŁA�{���͂��Ȃ��Ă��ǂ��B
	//���Ă����Ȃ�
    SafeRelease(m_pMesh);
}
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
void PrimitiveBox::Draw(DrawPacket& i_DrawPacket) {

	//�e�N�X�`��������ꍇ
	if(m_pTexture){
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}

}
/**************************************************************************
 PrimitiveSphere ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveSphere::Vec2UV(float x,float y,float z,float r,float& u,float& v );
//// �J�e�S��   �F�����o�֐�
//// �p�r       �FVector��U��V�ɃR���o�[�g
//// ����       �F  float x     //x�̒l
////            �F  float y     //y�̒l
////            �F  float z     //z�̒l
////            �F  float r     //���̔��a
////            �F  float& u    //�ϊ�����u�i�e�N�X�`�����U���W�j
////            �F  float& v    //�ϊ�����v�i�e�N�X�`�����V���W�j
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
////            �F
////
void PrimitiveSphere::Vec2UV(float x,float y,float z,float r,float& u,float& v){
	float q;
	float q2;
	q = atan2(z,x);
	u = q / (2.0f * D3DX_PI);
	q2 = asin(y / r);
	v = (1.0f - q2 / (D3DX_PI / 2.0f)) / 2.0f;
	if( u > 1.0f)
		u = 1.0f;
}
/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveSphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice)
//// �J�e�S��   �F�֐�
//// �p�r       �F���𐶐�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O(�R�m��搶�̂ЂȌ`���)
//// ���l       �Ffloat& u��float& v�ɕϊ���̒l����
////            �F
////
void PrimitiveSphere::CreateSphere(LPDIRECT3DDEVICE9 pD3DDevice){
    try{
        //���̍쐬
        if(
			FAILED(
				D3DXCreateSphere(
					pD3DDevice, 
					1.0f,
					18,
					18,
					&m_pMesh, 
					NULL
				)
			)
		){
            // ���������s
            throw DxException(
                L"���̍쐬�Ɏ��s���܂����B",
                L"PrimitiveSphere::PrimitiveSphere"
                );
        }
		if(m_pTexture){
			//�e�N�X�`�����b�V��
			LPD3DXMESH pMesh2 = 0;
			//�쐬���ꂽ���b�V�������ɁA�e�N�X�`�����̃��b�V�����쐬
			if(FAILED(m_pMesh->CloneMeshFVF(NULL,BallFVF,pD3DDevice,&pMesh2))){
				// ���������s
				throw DxException(
					L"�e�N�X�`���t�̋��̍쐬�Ɏ��s���܂����B",
					L"PrimitiveSphere::PrimitiveSphere"
					);
			}
			//���̒i�K��m_pMesh�͂���Ȃ�����폜
			SafeRelease(m_pMesh);
			//�V�������b�V������
			m_pMesh = pMesh2;
			//�e�N�X�`����̍��W���}�b�s���O
			LPDIRECT3DVERTEXBUFFER9 pVB = 0;
			SphereVertex* pVer = 0;
			m_pMesh->GetVertexBuffer(&pVB);
			pVB->Lock(0,0,(VOID**)&pVer,0);
			for(DWORD n = 0;n < m_pMesh->GetNumVertices();n++){ //���_�̐����擾����
				float u,v;
				Vec2UV(pVer[n].vec.x,pVer[n].vec.y,pVer[n].vec.z,1.0f,u,v);
				pVer[n].tu=u;
				pVer[n].tv=v;
			}
			pVB->Unlock();
		}
        //�N�I�[�^�j�I���̏�����
        //D3DXQuaternionRotationYawPitchRoll(&m_Qtn,0,0,0);
    }
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pMesh);
        //�ăX���[
        throw;
    }
};

/////////////////// ////////////////////
//// �֐���     �FPrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
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
PrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice,
           D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		   LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh(Diffuse,Specular,Ambient)
	,m_pTexture(pTexture)
{
    try{
		CreateSphere(pD3DDevice);
    }
    catch(...){
        //�ăX���[
        throw;
    }

}

/////////////////// ////////////////////
//// �֐���     �FPrimitiveSphere::PrimitiveSphere( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
PrimitiveSphere::PrimitiveSphere(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture)
    :CommonMesh()
	,m_pTexture(pTexture)
{
    try{
		CreateSphere(pD3DDevice);
    }
    catch(...){
        //�ăX���[
        throw;
    }

}

/////////////////// ////////////////////
//// �֐���     �FPrimitiveSphere::~PrimitiveSphere();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F���̂�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
PrimitiveSphere::~PrimitiveSphere(){
    //��n��
    SafeRelease(m_pMesh);
}
/////////////////// ////////////////////
//// �֐���     �FvoidPrimitiveSphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���̂�`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
void PrimitiveSphere::Draw(DrawPacket& i_DrawPacket){
	//�e�N�X�`�����������ꍇ
	if(m_pTexture){
		//�e�N�X�`���`�施��
		DWORD wkdword;
		//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//�X�e�[�W�̐ݒ�
		i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		i_DrawPacket.pD3DDevice->SetFVF(BallFVF);
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
		i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//�X�e�[�W�����ɖ߂�
		i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
	}
	else{
		//�e�N�X�`�����Ȃ��ꍇ
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(i_DrawPacket);
	}
}
/**************************************************************************
 PrimitiveSprite ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,RECT* Rect,
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
PrimitiveSprite::PrimitiveSprite(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, RECT* rect,
	D3DXVECTOR3& vCenter, D3DXVECTOR3& vOffsetPos, Color color)
	:m_pTexture(pTexture)
	,m_vOffsetPos(vOffsetPos)
	,m_vCenter(vCenter)
	,m_pRect(NULL)
	,m_Color(color)
{
	try{
		if(rect){
			m_pRect = new RECT(*rect);
		}
		if(
			FAILED(
				D3DXCreateSprite(
					pD3DDevice,
					&m_pSprite
				)
			)
		){
			// ���������s
			throw DxException(
				L"�X�v���C�g�̍쐬�Ɏ��s���܂����B",
				L"PrimitiveSprite::PrimitiveSprite()"
			);
		}
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
}

/////////////////// ////////////////////
//// �֐���     �Fvirtual PrimitiveSprite::~PrimitiveSprite()
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
PrimitiveSprite::~PrimitiveSprite(){
	SAFE_DELETE(m_pRect);
	SafeRelease(m_pSprite);
}



/////////////////// ////////////////////
//// �֐���     �Fvoid PrimitiveSprite::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void PrimitiveSprite::Draw(DrawPacket& i_DrawPacket)
{
	if(m_pSprite && m_pTexture){
		D3DXMATRIX mAspectRate,mAll;
		D3DXVECTOR2 AspectRate = DxDevice::getAspectRate();
		D3DXMatrixScaling(&mAspectRate,AspectRate.x,AspectRate.y,1.0f);
	    D3DXMatrixMultiply(&mAll,&m_mMatrix,&mAspectRate);
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &mAll );
			m_pSprite->Draw(m_pTexture, m_pRect,
				&m_vCenter, &m_vOffsetPos, m_Color.dwColor );
		}
		m_pSprite->End();
	}
}
/**************************************************************************
 SpriteObject ��`��
***************************************************************************/
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
SpriteObject::SpriteObject(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			RECT *pRect, D3DXVECTOR3 &vCenter, D3DXVECTOR3 &vOffsetPos, Color color,
			wiz::OBJID id)
			:Object(id)
			,PrimitiveSprite(pD3DDevice,pTexture,pRect,vCenter,vOffsetPos,color)
{
	try{
		//	: �����}�g���b�N�X���v�Z
		D3DXMATRIX mScale,mRot,mPos;
		D3DXMatrixScaling(&mScale,vScale.x,vScale.y,vScale.z);
		D3DXMatrixRotationYawPitchRoll(&mRot,vRot.y,vRot.x,vRot.z);
		D3DXMatrixTranslation(&mPos,vPos.x,vPos.y,vPos.z);
		m_mMatrix = mScale * mRot * mPos ;
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}

};
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
SpriteObject::~SpriteObject(){
};
/////////////////// ////////////////////
//// �֐���     �Fvoid SpriteObject::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�X�v���C�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
void SpriteObject::Draw(DrawPacket& i_DrawPacket)
{
	//	: �`��͐e�N���X�ɔC����
	PrimitiveSprite::Draw(i_DrawPacket);
};


/**************************************************************************
 Sound ��`��
****************************************************************************/
/**************************************************************************
 void Sound::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Sound::Clear(){
    if(m_pEngine){
        m_pEngine->ShutDown();
		SafeRelease(m_pEngine);
    }
	SafeDeleteArr(m_pbSoundBank);
	if(m_pbWaveBank){
        UnmapViewOfFile(m_pbWaveBank);
	}
    m_pbWaveBank = 0;
    CoUninitialize();
}
/**************************************************************************
 Sound::Sound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::Sound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName)
:m_pEngine(0),m_pWaveBank(0),m_pSoundBank(0),m_pbWaveBank(0),m_pbSoundBank(0)
,Object(OBJID_SYS_SOUND)
{
	try{
		HANDLE hFile;
		DWORD dwFileSize;
		DWORD dwBytesRead;
		HANDLE hMapFile;

		if(FAILED(CoInitializeEx( NULL, COINIT_MULTITHREADED))){
			// ���������s
			throw DxException(
				L"i_DrawPacket.pCommand�������Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}


		//�f�o�b�O���͈ȉ���true�ɂ���
		bool bDebugMode = false;
		DWORD dwCreationFlags = 0;
		if( bDebugMode ) dwCreationFlags |= XACT_FLAG_API_DEBUG_MODE;
		if(FAILED(XACT3CreateEngine( dwCreationFlags, &m_pEngine ))){
			// ���������s
			throw DxException(
				L"�T�E���h�G���W���\�z�Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}
		// Initialize & create the XACT runtime 
		XACT_RUNTIME_PARAMETERS xrParams = {0};
		xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
		if(FAILED(m_pEngine->Initialize( &xrParams ))){
			// ���������s
			throw DxException(
				L"�T�E���h�G���W���������Ɏ��s���܂����B",
				L"Sound::Sound()"
				);
		}

		hFile = CreateFile(pWavBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE ){
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 ){
				hMapFile = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL );
				if( hMapFile ){
					m_pbWaveBank = MapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
					if(m_pbWaveBank){
						if(FAILED(m_pEngine->CreateInMemoryWaveBank(m_pbWaveBank, dwFileSize, 0,
							0, &m_pWaveBank))){
							CloseHandle( hMapFile );
							CloseHandle( hFile );
							// ���������s
							throw DxException(
								L"Wav�o���N�n���h���������Ɏ��s���܂����B",
								L"Sound::Sound()"
								);
						}
					}
					CloseHandle( hMapFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
				}
			}
			CloseHandle( hFile ); // pbWaveBank maintains a handle on the file so close this unneeded handle
		}
		hFile = CreateFile(pSoundBankFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile != INVALID_HANDLE_VALUE )
		{
			dwFileSize = GetFileSize( hFile, NULL );
			if( dwFileSize != -1 )
			{
				// Allocate the data here and free the data when recieving the sound bank destroyed notification
				m_pbSoundBank = new BYTE[dwFileSize];
				if(m_pbSoundBank)
				{
					if( 0 != ReadFile( hFile,m_pbSoundBank, dwFileSize, &dwBytesRead, NULL ) )
					{
						if(FAILED(m_pEngine->CreateSoundBank(m_pbSoundBank, dwFileSize, 0,
							0, &m_pSoundBank))){
							CloseHandle( hFile );
							// ���������s
							throw DxException(
								L"Sound�o���N�n���h���������Ɏ��s���܂����B",
								L"Sound::Sound()"
								);

						}
					}
				}
			}
			CloseHandle( hFile );
		}

	}
	catch(...){
		Clear();
		//��throw
		throw;
	}
}
/**************************************************************************
 virtual Sound::~Sound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Sound::~Sound(){
	Clear();
}
/**************************************************************************
 virtual void Sound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �e��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Sound::Draw(DrawPacket& i_DrawPacket){
}

/**************************************************************************
 ZapSound ��`��
****************************************************************************/
/**************************************************************************
 ZapSound::ZapSound(
 const wchar_t* pWavBankFileName,		//Wav�o���N�̃t�@�C����
 const wchar_t* pSoundBankFileName	//Sound�o���N�̃t�@�C����
 const char* pZapKey,				//Zap�̃L�[
 const char* pFireKey				//���ˉ��̃L�[
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ZapSound::ZapSound(const wchar_t* pWavBankFileName,const wchar_t* pSoundBankFileName,
				   const char* pZapKey,const char* pFireKey,const char* pBGM,const char* pBS,const char* pGET,const char* pHANAB1,const char* pHANAB2)
:Sound(pWavBankFileName,pSoundBankFileName),m_iZap(0),m_iFire(0),m_iBGM(0),m_iBS(0),m_iGET(0),m_iHANAB1(0),m_iHANAB2(0)
{
	try{
		if(m_pSoundBank){
			m_iZap = m_pSoundBank->GetCueIndex(pZapKey);
			m_iFire = m_pSoundBank->GetCueIndex(pFireKey);
			m_iBGM = m_pSoundBank->GetCueIndex(pBGM);
			m_iBS = m_pSoundBank->GetCueIndex(pBS);
			m_iGET = m_pSoundBank->GetCueIndex(pGET);
			m_iHANAB1 = m_pSoundBank->GetCueIndex(pHANAB1);
			m_iHANAB2 = m_pSoundBank->GetCueIndex(pHANAB2);
		}
	}
	catch(...){
		Clear();
		//��throw
		throw;
	}
}
/**************************************************************************
 virtual ~ZapSound();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ZapSound::~ZapSound(){
	//Clear()�͐e�N���X���Ă�
}
/**************************************************************************
 virtual void ZapSound::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& i_DrawPacket.pCommand					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��i�T�E���h�Ȃ̂łȂɂ����Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
//void ZapSound::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
//		  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand){
//}
/**************************************************************************
 void PlayZap();
 �p�r: Zap��炷
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::PlayZap(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iZap, 5, 0, NULL );	
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::PlayFire(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iFire, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::BGM(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iBGM, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::PlayFire();
 �p�r: ���ˉ���炷
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::BS(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iBS, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::GET(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iGET, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::HANAB1(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iHANAB1, 0, 0, NULL );
	}
}
/**************************************************************************
 void ZapSound::BGM();
 �p�r: �Q�[������BGM
 �߂�l: �Ȃ��B
***************************************************************************/
void ZapSound::HANAB2(){
	if(m_pSoundBank){
		m_pSoundBank->Play(m_iHANAB2, 0, 0, NULL );
	}
}
}//end of namespace	baseobject.
}//end of namespace	wiz.