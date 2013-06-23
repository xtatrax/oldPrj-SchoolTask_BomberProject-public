////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FObject.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		class Object ;
//		class Light  ;
//		class DirectionalLight : public Light , public Object ;
//
#include "StdAfx.h"
#include "Object.h"

namespace wiz{
namespace system{
/**************************************************************************
 Light ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �FLight()
//// �J�e�S��   �F���񂷂Ƃ炭��
//// �p�r       �F�v���e�N�g�R���X�g���N�^
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ� 
//// �S����     �F
//// ���l       �F���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
////            �F
////
Light::Light(wiz::OBJID id)
:Object(id)
{
    // D3DLIGHT9�\���̂�0�ŃN���A����
    ::ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}
/////////////////// ////////////////////
//// �p�r       �FLight()
//// �J�e�S��   �F�ł��Ƃ炭��
//// �p�r       �F�v���e�N�g�f�X�g���N�^�i���z�f�X�g���N�^�j
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ� 
//// �S����     �F
//// ���l       �F���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
////            �F
Light::~Light(){}
/**************************************************************************
 DirectionalLight ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �FDirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
////            �F    D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,
////            �F    D3DCOLORVALUE Ambient,D3DXVECTOR3 Direction)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F  LPDIRECT3DDEVICE9 pD3DDevice,   //�f�o�C�X
////            �F  D3DCOLORVALUE Diffuse,          //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE Specular,         //�X�y�L�����F
////            �F  D3DCOLORVALUE Ambient,          //�A���r�G���g�F
////            �F  D3DXVECTOR3 Direction           //���[���h��ԂŌ����w������
//// �S����     �F
//// ���l       �F�f�B���N�V���i�����C�g���\�z����
////            �F
////
DirectionalLight::DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
    D3DCOLORVALUE Diffuse,
    D3DCOLORVALUE Specular,
    D3DCOLORVALUE Ambient,
    D3DXVECTOR3 Direction,
	wiz::OBJID id)
    :Light(id)
{
    m_Light.Type		= D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse		= Diffuse;
    m_Light.Specular	= Specular;
    m_Light.Ambient		= Ambient;
    D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &Direction);
    // ���C�g�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetLight( 0, &m_Light );
    // ���C�g��L���ɂ���
    pD3DDevice->LightEnable( 0, TRUE );
}
/////////////////// ////////////////////
//// �p�r       �Fvirtual ~DirectionalLight()
//// �J�e�S��   �F�Z�X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F
//// ���l       �F
////            �F
////
DirectionalLight::~DirectionalLight(){}

/**************************************************************************
 Camera ��`��
****************************************************************************/
/**************************************************************************
 Camera::Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3& At,    //�����_
	FLOAT AbsPosZFromAt,//�����_���猩���A�J�����ʒu��Z�̈ʒu(��Βl�w��)
	FLOAT PosYFromAt,	//�����_���猩���A�J�����ʒu��Y�̈ʒu
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 ���J�����ʒu�̏����l�͒��ڂ͎w��ł��Ȃ��B
 �������_����݂āAZ�̎�O�Ɉ������Έʒu��Y�̑��Έʒu���w�肷��BX��0�ɌŒ�
 ��Z�̎�O�Ɉ������Έʒu�iAbsPosZFromAt�j�͐�Βl�������̂ŁA
	�}�C�i�X���w�肵�Ă��Ӗ����Ȃ��B
 �߂�l: �Ȃ�
***************************************************************************/
Camera::Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& At,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY)
:Object(OBJID_SYS_CAMERA),m_Eye(),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	try{
		//�J�����ʒu�̊m��
		m_Eye.x = m_At.x;
		m_Eye.y = m_At.y + PosYFromAt;
		m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
		//�J�����r���[�̍쐬
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		//�J�����ƒ����_�Ƃ̊ԁiArm�j���O�쐬
		m_Arm = m_At - m_Eye;
		D3DXVECTOR3 m;
		//���K��
		D3DXVec3Normalize(&m,&m_Arm);
		m_TotalAngleXZ = 0;
		//���K�����ꂽY�̒l���獂���̃��W�A���𓾂�
		FLOAT a_c,a_s;
		a_c = acos(m.z);
		a_s = asin(m.y);
		if(a_s < 0.0f){
			m_TotalAngleY = a_c;
		}
		else{
			m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
		}
		// �r���[�|�[�g�̎擾
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//���s���s
			//WinMain��Catch�܂Ŕ��
			throw BaseException(
				L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
				L"Camera::Draw()"
				);
		}
		m_Eye = m_At - m_Arm;
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// �A�X�y�N�g��̌v�Z
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// �ˉe�s��̏�����
		D3DXMatrixIdentity(&m_Proj);
		//D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		D3DXMatrixOrthoLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// �ˉe�s��̐ݒ�
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// �J�����̐ݒ�
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
Camera::Camera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3& Eye,	//�J�����̈ʒu
    D3DXVECTOR3& At,    //�����_
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: Fix�J�����̎��Ɏg�p����R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Camera::Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :Object(OBJID_SYS_CAMERA),m_View(),m_Proj(),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	try{
		m_Arm = m_At - m_Eye;
		//Fix�J�����̎��Ɏg�p����R���X�g���N�^�Ȃ̂�
		//�J�����ω��͂Ȃ��Ă��ǂ�
		m_TotalAngleXZ = 0;
		m_TotalAngleY = 0;
		// �r���[�|�[�g�̎擾
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//���s���s
			//WinMain��Catch�܂Ŕ��
			throw BaseException(
				L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
				L"Camera::Draw()"
				);
		}
		m_Eye = m_At - m_Arm;
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// �A�X�y�N�g��̌v�Z
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// �ˉe�s��̏�����
		D3DXMatrixIdentity(&m_Proj);
		//D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		D3DXMatrixOrthoLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// �ˉe�s��̐ݒ�
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// �J�����̐ݒ�
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
	}
	catch(...){
		throw;
	}
}


/**************************************************************************
 Camera::~Camera();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Camera::~Camera(){
}
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
/**************************************************************************
 virtual void Camera::Draw(
	DrawPacket& i_DrawPacket
);
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Camera::Draw(DrawPacket& i_DrawPacket){

    // �r���[�|�[�g�̎擾
    D3DVIEWPORT9 vp;
    if(FAILED(i_DrawPacket.pD3DDevice->GetViewport(&vp))){
        //���s���s
		//WinMain��Catch�܂Ŕ��
        throw BaseException(
            L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
            L"Camera::Draw()"
            );
    }
	m_Eye = m_At - m_Arm;
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // �A�X�y�N�g��̌v�Z
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // �ˉe�s��̏�����
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // �ˉe�s��̐ݒ�
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // �J�����̐ݒ�
    i_DrawPacket.pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}


/**************************************************************************
 class LookAtCamera : public Object;
 �p�r: �I�u�W�F�N�g�𒍖ڂ���J�����N���X
****************************************************************************/
/**************************************************************************
 LookAtCamera::LookAtCamera(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    Object*	pObj,		//�����_�𓾂邽�߂̃I�u�W�F�N�g
	FLOAT LocalY,		//�����_���璲������Y�ʒu
	FLOAT AbsPosZFromAt,//�����_���猩���A�J�����ʒu��Z�̈ʒu(��Βl�w��)
	FLOAT PosYFromAt,	//�����_���猩���A�J�����ʒu��Y�̈ʒu
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 ���J�����ʒu�̏����l�͒��ڂ͎w��ł��Ȃ��B
 �������_����݂āAZ�̎�O�Ɉ������Έʒu��Y�̑��Έʒu���w�肷��BX��0�ɌŒ�
 ��Z�̎�O�Ɉ������Έʒu�iAbsPosZFromAt�j�͐�Βl�������̂ŁA
	�}�C�i�X���w�肵�Ă��Ӗ����Ȃ��B
 �߂�l: �Ȃ�
***************************************************************************/
LookAtCamera::LookAtCamera(LPDIRECT3DDEVICE9 pD3DDevice,
		Object* pObj,FLOAT LocalY,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
	    FLOAT Near,FLOAT Far,FLOAT FovY)
:

Camera(
	pD3DDevice,			//�f�o�C�X
	D3DXVECTOR3(0,0,0),    //�J�����̈ʒu
	D3DXVECTOR3(0,0,0),    //�����_
	Near,         //�ˉe�̎�O���̋���
	Far,          //�ˉe�̉����̋���
	FovY          //Y���ˉe�p�x
	),
m_pObject(pObj),
m_LocalY(LocalY)
{
	try{
		D3DXVECTOR3 ObjPos(0,0,0);
		if(m_pObject){
			ObjPos = m_pObject->getPos();
		}
		//�����_���擾
		m_At = ObjPos;
		m_At.y += m_LocalY;

		//�J�����ʒu�̊m��
		m_Eye.x = m_At.x;
		m_Eye.y = m_At.y + PosYFromAt;
		m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
		//�J�����r���[�̍쐬
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		//�J�����ƒ����_�Ƃ̊ԁiArm�j���O�쐬
		m_Arm = m_At - m_Eye;
		D3DXVECTOR3 m;
		//���K��
		D3DXVec3Normalize(&m,&m_Arm);
		m_TotalAngleXZ = 0;
		//���K�����ꂽY�̒l���獂���̃��W�A���𓾂�
		FLOAT a_c,a_s;
		a_c = acos(m.z);
		a_s = asin(m.y);
		if(a_s < 0.0f){
			m_TotalAngleY = a_c;
		}
		else{
			m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
		}
		// �r���[�|�[�g�̎擾
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//���s���s
			//WinMain��Catch�܂Ŕ��
			throw BaseException(
				L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
				L"Camera::Draw()"
				);
		}
		D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
		// �A�X�y�N�g��̌v�Z
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// �ˉe�s��̏�����
		D3DXMatrixIdentity(&m_Proj);
		D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
		// �ˉe�s��̐ݒ�
		pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
		// �J�����̐ݒ�
		pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);

	}
	catch(...){
		//�ăX���[
		throw;
	}

}


/**************************************************************************
 LookAtCamera::~LookAtCamera();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
LookAtCamera::~LookAtCamera(){
}

/**************************************************************************
 virtual void LookAtCamera::Transform(
 vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
 const CONTROLER_STATE* pCntlState,	//�R���g���[���̏��
 Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��ω�������i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void LookAtCamera::Update( UpdatePacket& i_UpdatePacket ){


    if(i_UpdatePacket.pCntlState[0].bConnected){
		BoxCon wButtons = i_UpdatePacket.pCntlState[0].Gamepad.wButtons.XConState;
		Point  sThumbR  = Point( i_UpdatePacket.pCntlState[0].Gamepad.sThumbRX, i_UpdatePacket.pCntlState[0].Gamepad.sThumbRY);

		D3DXVECTOR3 ObjPos(0,0,0);
		if(m_pObject){
			ObjPos = m_pObject->getPos();
		}
		//���݂̒����_�𓾂�
		m_At.x = ObjPos.x;
		m_At.z = ObjPos.z;
		//m_Eye�ʒu�̕ύX�P
		if(wButtons.RIGHT_SHOULDER){
			//���S����
			m_At.y = ObjPos.y;
			m_At.y += m_LocalY;
		}

		//�J�����ʒu�ƒ����_�̊Ԃ̃x�N�g�����Z�o
		D3DXVECTOR3 span = m_Eye - m_At;
		//���K��
		D3DXVec3Normalize(&span,&span);
		//����
		span = span * 0.2f;
		//D�p�b�h��
		//�J����������
        if(wButtons.DOWN){
			//�J�����ʒu������
			m_Eye = m_Eye + span;
		    m_Arm = m_At - m_Eye;
			if(D3DXVec3Length(&m_Arm) > (m_Far * 0.5f)){
				m_Eye = m_Eye - span;
			    m_Arm = m_At - m_Eye;
			}
        }
		//D�p�b�h��
		//�J���������
        if(wButtons.UP){
			//�J�����ʒu�����
			m_Eye = m_Eye - span;
		    m_Arm = m_At - m_Eye;
			if(D3DXVec3Length(&m_Arm) < 2.0f){
				m_Eye = m_Eye + span;
			    m_Arm = m_At - m_Eye;
			}
        }
		//m_Eye�ʒu�̕ύX�Q
		FLOAT AngleX = 0;
		//�E�X�e�B�b�NX����
        if(sThumbR.x != 0){
            AngleX = sThumbR.x / 1000000.0f;
        }
		//�E�X�e�B�b�NY����
		FLOAT AngleY = 0;
        if(sThumbR.y != 0){
            AngleY = sThumbR.y / 1000000.0f;
        }
		m_TotalAngleXZ += AngleX;
		if(m_TotalAngleXZ > (D3DX_PI * 2)){
			m_TotalAngleXZ -= (D3DX_PI * 2);
		}
		if(m_TotalAngleXZ < -(D3DX_PI * 2)){
			m_TotalAngleXZ += (D3DX_PI * 2);
		}
		m_TotalAngleY += AngleY;
		if(m_TotalAngleY < -(D3DX_PI / 180)){
			m_TotalAngleY = -(D3DX_PI / 180);
		}
		if(m_TotalAngleY > (D3DX_PI / 4)){
			m_TotalAngleY = (D3DX_PI / 4);
		}
		FLOAT xArm = D3DXVec3Length(&m_Arm) * cos(m_TotalAngleY);
		FLOAT yArm = D3DXVec3Length(&m_Arm) * sin(m_TotalAngleY);
		m_Eye.x = xArm * sin(m_TotalAngleXZ) + m_At.x;
		m_Eye.y = yArm + m_At.y;
		m_Eye.z = xArm * -cos(m_TotalAngleXZ) + m_At.z;
	    m_Arm = m_At - m_Eye;
	}
}



/**************************************************************************
 virtual void LookAtCamera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void LookAtCamera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
	const CONTROLER_STATE* pCntlState,Context& Data){
    // �r���[�|�[�g�̎擾
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //���s���s
		//WinMain��Catch�܂Ŕ��
        throw BaseException(
            L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
            L"Camera::Draw()"
            );
    }
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // �A�X�y�N�g��̌v�Z
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // �ˉe�s��̏�����
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // �ˉe�s��̐ݒ�
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // �J�����̐ݒ�
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
}


/**************************************************************************
 class Guide ��`��
****************************************************************************/
/**************************************************************************
 void Guide::CreateInctance(
 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �C���X�^���X�̍\�z
 �߂�l: �Ȃ��B�i��O��throw�����j
***************************************************************************/
void Guide::CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice){
	ReleaseObj();
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
            throw BaseException(
                L"���_�o�b�t�@�̍쐬�Ɏ��s���܂����B",
                L"Guide::Guide()"
                );
        }
        //�o�b�t�@�����b�N
        VOID* pVertices;
        if(FAILED( m_pVB->Lock( 0, sizeof(Vertices),( void** )&pVertices, 0 ))){
            // ���������s
            throw BaseException(
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
		ReleaseObj();
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 Guide::Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
:Object(OBJID_SYS_GUIDELINE),m_pVB(0)
{
	CreateInctance(pD3DDevice);
}
/**************************************************************************
 Guide::~Guide();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Guide::~Guide(){
	ReleaseObj();
}
/**************************************************************************
	virtual void Guide::ReleaseObj();
 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Guide::ReleaseObj(){
    SafeRelease(m_pVB);
}

/**************************************************************************
	virtual void Guide::ChangeDevice(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	);
 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
 �߂�l: �Ȃ��B
 ���f�o�C�X���r�������Ƃ��ɍō\�z���ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
***************************************************************************/
void Guide::ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
	//���N���X�ł͉������Ȃ�
	CreateInctance(pD3DDevice);
}


/**************************************************************************
 virtual void Guide::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Context& Data					//���[�U�[�f�[�^
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Guide::Draw(DrawPacket& i_DrawPacket){
	LPDIRECT3DDEVICE9 pD3DDevice = i_DrawPacket.pD3DDevice ;
	if(!m_pVB){
		//�o�b�t�@�������Ȃ牽�����Ȃ�
		return;
	}
    D3DXMATRIX  wm;
    //���W�ϊ�����
    D3DXMatrixIdentity(&wm);
    // �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    pD3DDevice->LightEnable( 0, FALSE );
    pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    pD3DDevice->LightEnable( 0, TRUE );
}




}
//end of namespace system.

}
//end of namespace wiz.

