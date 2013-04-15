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
#pragma once

#include "StdAfx.h"
#include "TextureManager.h"
#include "Tempus/Tempus.h"
#include "Controller/Controller.h"

namespace wiz{

extern class Object;

struct UpdatePacket{
	const CONTROLER_STATE*	pCntlState	;
	LPDIRECT3DDEVICE9		pD3DDevice	;
	vector<Object*>*		pVec		;
	TextureManager*			pTxMgr		;
	TLIB::Tempus2*			pTime		;
	Command*				pCommand	;
	UpdatePacket()
		:pCntlState( NULL )
		,pD3DDevice( NULL )
		,pVec( NULL )
		,pTxMgr( NULL )
		,pTime( NULL )
		,pCommand( NULL )
	{
	}

};
struct RenderPacket{
	LPDIRECT3DDEVICE9	pD3DDevice	;
	vector<Object*>*	pVec		;
	Command*			pCommand	;
};
struct DrawPacket{
	LPDIRECT3DDEVICE9	pD3DDevice	;
	vector<Object*>*	pVec		;
	TLIB::Tempus2*		pTime		;
	Command*			pCommand	;
};



//**************************************************************************
// class Object;
//
// �S����  :
// �p�r    : �V�[���z�u�I�u�W�F�N�g�̊��N���X�i���ۃN���X�j
//**************************************************************************
class Object{
private:
	bool	m_bAccessLock;
	bool	m_bDead;
	OBJID	m_dwID;
public:
	Object(OBJID id):m_bAccessLock(false),m_dwID(id){}
    virtual ~Object(){}
/////////////////// ////////////////////
//// �֐���     �Fvoid getID()
//// �J�e�S��   �F�Z�b�^�[
//// �p�r       �F���S�t���O��ݒ�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	DWORD getID() const { return m_dwID ; }
/////////////////// ////////////////////
//// �֐���     �Fvoid setDead()
//// �J�e�S��   �F�Z�b�^�[
//// �p�r       �F���S�t���O��ݒ�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void setDead(){	m_bDead = true ; }
/////////////////// ////////////////////
//// �֐���     �Fbool getDead()
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �FDEAD OR ALIVE
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	bool getDead() const { return m_bDead; }
/////////////////// ////////////////////
//// �֐���     �Fvoid AccessBegin()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�f�[�^�ւ̃A�N�Z�X���J�n
//// ����       �F�Ȃ�
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�}���`�X���b�h�𗘗p����ۂɕ����̃X���b�h�������Ƀf�[�^������������̂�h��
////            �F���L�̊֐� ( void AccessEnd() ) �ƃZ�b�g
////
	void AccessBegin(){	while(m_bAccessLock){ Sleep(1); } m_bAccessLock = true; };
/////////////////// ////////////////////
//// �֐���     �Fvoid AccessEnd()
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�f�[�^�ւ̃A�N�Z�X���I��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F�}���`�X���b�h�𗘗p����ۂɕ����̃X���b�h�������Ƀf�[�^������������̂�h��
////            �F��L�̊֐� ( void AccessBegin() ) �ƃZ�b�g
////
	void AccessEnd(){ m_bAccessLock = false; }
/////////////////// ////////////////////
//// �֐���     �Fvirtual bool HitTest(D3DXVECTOR3 Pos)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  D3DXVECTOR3 Pos      //
//// �ߒl       �Ffalse
//// �S����     �F
//// ���l       �F�h����ŕK�v�Ȃ�Ώ���
////            �F  
////
    virtual bool HitTest(D3DXVECTOR3 Pos){ return false; }
/////////////////// ////////////////////
//// �p�r       �Fvirtual bool HitTest(Object* other)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �FObject* other      // ���̃I�u�W�F�̃|�C���^
//// �ߒl       �Ffalse 
//// �S����     �F
//// ���l       �F�h����ŕK�v�Ȃ�Ώ���
////            �F
////
    virtual bool HitTest(Object* other){ return false; }
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F      vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  Tempus2* i_DrawPacket.pTime                     // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���̃X�e�[�^�X
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
    virtual void Update(UpdatePacket& i_UpdatePacket){};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void TargetRender( LPDIRECT3DDEVICE9 pD3DDevice
////            �F      vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////            �F
////
	virtual void TargetRender(RenderPacket& i_RenderPacket){};

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec                // �I�u�W�F�N�g�̔z��
////            �F  Tempus2* i_DrawPacket.pTime                     // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) = 0;
};

//**************************************************************************
// class Light;
//
// �S����  : 
// �p�r    : ���C�g�N���X
//**************************************************************************
class Light{
protected:
    D3DLIGHT9   m_Light;
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
    Light();
/////////////////// ////////////////////
//// �p�r       �FLight()
//// �J�e�S��   �F�ł��Ƃ炭��
//// �p�r       �F�v���e�N�g�f�X�g���N�^�i���z�f�X�g���N�^�j
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ� 
//// �S����     �F
//// ���l       �F���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
////            �F
////
    virtual ~Light();
};

//**************************************************************************
// class DirectionalLight : public Light , public Object;
//
// �S����  : 
// �p�r    : �f�B���N�V���i�����C�g�N���X
//**************************************************************************
class DirectionalLight : public Light , public Object{
public:
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
    DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE Diffuse,
        D3DCOLORVALUE Specular,
        D3DCOLORVALUE Ambient,
        D3DXVECTOR3 Direction,
		wiz::OBJID id = OBJID_SYS_LIGHT);
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
    virtual ~DirectionalLight();
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////            �F
////
	virtual void Draw(DrawPacket& i_DrawPacket){};


};






}
//end of namespace wiz.

