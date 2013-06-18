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

	extern class Object ;
	extern class Button ;

//**************************************************************************
// class Object;
//
// �S����  : ���� �O
// �p�r    : �V�[���z�u�I�u�W�F�N�g�̊��N���X�i���ۃN���X�j
//**************************************************************************
class Object{
private:
	bool	m_bAccessLock;
	bool	m_bDead;
	OBJID	m_dwID;

public:
	Object(OBJID id):m_bAccessLock(false),m_bDead(false),m_dwID(id){}
	virtual ~Object(){}

//////////
//	: �Q�b�^�[
public:
	virtual Button* getButtonP(){ return NULL; };
	/////////////////// ////////////////////
	//// �֐���     �Fvoid getID()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���̕��̂�ID���l�����܂�
	//// ����       �F�Ȃ�
	//// �ߒl       �F OBJID�ԍ�(DWORD)
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	DWORD getID() const { return m_dwID ; }

	/////////////////// ////////////////////
	//// �֐���     �Fbool getDead()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�폜�\��̏�Ԃ��l������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�폜�\��̏ꍇ true
	////            �F�����łȂ��ꍇ false
	////
	bool getDead() const { return m_bDead; }

//////////
//	: �Z�b�^�[
public:
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setDead()
	//// �J�e�S��   �F�Z�b�^�[
	//// �p�r       �F���S�t���O���Z�b�g����
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F���̊֐����ĂԂƃ���������폜����܂�
	////            �F
	////
	void setDead(){	m_bDead = true ; }




	///////////////////// ////////////////////
	//// �֐���     �FD3DXVECTOR3 getPos() const { return g_vZero; }
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���z�֐�
	//// ����       �F�Ȃ�
	//// �ߒl       �F���W
	//// �S����     �F���� �O
	//// ���l       �F�h����ŕK�v�Ȃ�Ώ���
	////            �F
	////
	virtual D3DXVECTOR3 getPos() const { return g_vZero; }

public:
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
	void AccessBegin(){	while(m_bAccessLock){ Sleep(1); } m_bAccessLock = true; }


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


	/**************************************************************************
		virtual void ChangeDevice(
		LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		);
	 �p�r: �f�o�C�X�r���ɂ��č\�z�i���z�֐��j
	 �߂�l: �Ȃ��B
	 ���f�o�C�X���r�������Ƃ��ɍō\�z���ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ChangeDevice(LPDIRECT3DDEVICE9 pD3DDevice){
		//���N���X�ł͉������Ȃ�
	}

public:
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ){};

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
	virtual void TargetRender( RenderPacket& i_RenderPacket ){};

	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�������z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F
	//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
	////            �F
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) = 0;
};


/**************************************************************************
 class Button ;
 �p�r: �{�^������N���X
 �p�@: ����ButtonPlate����h�����Ȃ��N���X���{�^���ɂ��������͈ȉ��̂悤�ɂ�
	�邱�Ƃɂ���ă{�^�������邱�Ƃ��ł��܂�
	�܂����̃N���X���N���X���ɐ錾���Ă�������
		��)
		    class foo{
		    private:
		       Button m_ButtonPrm;
		       �E
		       �E
		       �E
	���ɃI�u�W�F�N�g�z��ǉ�����ہAStage�N���X��Button�p�z��ɂ��̃N���X��
	�C���X�^���X�ւ̃|�C���^�[��ǉ����Ă�������
		��)	m_vec.push_back(pButtonPlate);
			m_ButtonVec.push_back(&pButtonPlate->m_ButtonPrm);
 ****************************************************************************/
class Button {
protected:
	DWORD	m_Index;				//���j���[��̃C���f�b�N�X
	bool	m_IsSelect;				//�I���t���O
	bool	m_IsMouseSelect;		//�}�E�X�ɂ���đI������Ă���
	bool	m_IsPressed;			//����t���O
	Command	m_Command;				//�R�}���h

	static DWORD MouseSelectIndex(bool Set = false ,DWORD index = 0){
		static DWORD	MouseSelectIndex	;
		if( Set )
			MouseSelectIndex	= index ;
		return			MouseSelectIndex	;
	}
public:
	/**************************************************************************
	 Button(
		LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		DWORD Cmd,						//�I�����s���ꂽ�Ƃ��̃R�}���h
		DWORD Index,					//���j���[�X�e�[�W��̃C���f�b�N�X
		);
	 �p�r: �R���X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
    Button(Command Cmd,DWORD Index)
		:m_Index(Index),m_IsPressed(false),m_IsSelect(false),m_Command(Cmd)
		,m_IsMouseSelect( false )
	{
		//�����C���f�b�N�X��0�ԂȂ�A������ԂőI������Ă���
		if(m_Index == 0){
			m_IsSelect = true;
		}
	};
	/**************************************************************************
	 virtual ~Button();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
	virtual ~Button(){};
	/**************************************************************************
	 void setSelect(
		bool select	//�I�����
	 );
	 �p�r: �I����Ԃ�ݒ�
	 �߂�l: �Ȃ��B
	***************************************************************************/
	void setSelect(bool select){
		m_IsSelect = select;
	}
	/**************************************************************************
	 void setSelect(
		bool select	//�I�����
	 );
	 �p�r: �I����Ԃ�ݒ�
	 �߂�l: �Ȃ��B
	***************************************************************************/
	void setMouseSelect(bool select){
		if(m_IsSelect = m_IsMouseSelect = select)
			Button::MouseSelectIndex( true , m_Index );
	}
	/**************************************************************************
	 void setPressed();
	 �p�r: ����t���O���Z�b�g����
	 �߂�l: �Ȃ��B
	***************************************************************************/
	void setPressed(){
		m_IsPressed = true;
	}
	/**************************************************************************
	 bool getSelect();
	 �p�r: �I������Ă邩�ǂ���
	 �߂�l: 0 ��I�� / 1 �I��
	***************************************************************************/
	bool getSelect(){
		return m_IsSelect;
	}
	
	/**************************************************************************
	 void setSelect(
		bool select	//�I�����
	 );
	 �p�r: �I����Ԃ�ݒ�
	 �߂�l: �Ȃ��B
	***************************************************************************/
	static DWORD getMouseSelectIndex(){
		DWORD ret = MouseSelectIndex();
		MouseSelectIndex(true, ULONG_MAX) ;
		return ret;
	}
	/**************************************************************************
	 bool getPressed();
	 �p�r: ���肳�ꂽ���ǂ���
	 �߂�l: 0 �񌈒� / 1 ����
	***************************************************************************/
	bool getPressed(){
		if( m_IsPressed ){
			m_IsPressed = false ;
			return true  ;
		}else{
			return false ;
		}
	}
	/**************************************************************************
	 void setSelect();
	 �p�r: �R�}���h�̔��s
	 �߂�l: ���s���ꂽ�R�}���h
	***************************************************************************/
	Command CommandIssue(){
		m_IsPressed		= false;
		return m_Command;
	}
	/**************************************************************************
	 void getIndex();
	 �p�r: ���������Ԗڂ̃{�^������Ԃ�
	 �߂�l: �����̔ԍ�
	***************************************************************************/
	DWORD getIndex(){
		return m_Index;
	}
};
//**************************************************************************
// class Behavior;
//
// �S����  : ���� �O
// �p�r    : �������`����I�u�W�F�N�g�̊�{�N���X
//**************************************************************************
class Behavior : public Object{
public:
	/////////////////// ////////////////////
	//// �p�r       �FBehavior(wiz::OBJID id)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	Behavior(wiz::OBJID id):Object(id){}
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ) = 0;
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�������z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F
	//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
	////            �F
	////
	virtual void Draw( DrawPacket& i_DrawPacket ){};
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

/**************************************************************************
 class Camera : public Object;
 �p�r: �J�����N���X
****************************************************************************/
class Camera : public Object{
protected:
    D3DXMATRIX  m_View;     // �J�����̔z�u
    D3DXMATRIX m_Proj;		// �ˉe�s��
    D3DXVECTOR3 m_Eye;      //�J�����̈ʒu
    D3DXVECTOR3 m_At;       //�����_
    FLOAT m_Near;           //�ˉe�̎�O���̋���
    FLOAT m_Far;            //�ˉe�̉����̋���
    FLOAT m_FovY;           //�ˉe�p�x

    D3DXVECTOR3 m_Arm;       //���_�ƒ����_�̊ԁi�r�j�̃x�N�g��
	FLOAT m_TotalAngleXZ;	//�J������XZ��]�̃��W�A���l
	FLOAT m_TotalAngleY;	//�J������Y��]�̃��W�A���l

	

public:
	/**************************************************************************
	 Camera(
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
	 Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& At,FLOAT PosZFromAt,FLOAT PosYFromAt,
		FLOAT Near,FLOAT Far,FLOAT FovY);
	/**************************************************************************
	Camera(
		LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
		D3DXVECTOR3& Eye,    //�J�����̈ʒu
		D3DXVECTOR3& At,    //�����_
		FLOAT Near,         //�ˉe�̎�O���̋���
		FLOAT Far,          //�ˉe�̉����̋���
		FLOAT FovY          //Y���ˉe�p�x
		);
	 �p�r: �R���X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
	Camera(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);

	/**************************************************************************
	 virtual ~Camera();
	 �p�r: ���z�f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
    virtual ~Camera();
	/**************************************************************************
	 virtual void Draw(
		DrawPacket& i_DrawPacket 
	 );
	 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
	 �߂�l: �Ȃ��B
	***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
	/**************************************************************************
	 void GetEyeAt(
	 D3DXVECTOR3& Eye,	//�J�����̈ʒu
	 D3DXVECTOR3& At	//�����_
	 );
	 �p�r: �J�����̌��݂̈ʒu�ƒ����_�𓾂�
	 �߂�l: �Ȃ��BEye��AT�ɒl����
	***************************************************************************/
	void GetEyeAt(D3DXVECTOR3& Eye,D3DXVECTOR3& At){
		Eye = m_Eye;
		At = m_At;
	}
	D3DXVECTOR3 getEye(){ return m_Eye ; }
	D3DXVECTOR3 getAt(){  return m_At ; }
	/**************************************************************************
	 void GetMatrix(
	 D3DXMATRIX& View,	//�r���[�s��
	 D3DXMATRIX& Proj	//�ˉe�s��
	 );
	 �p�r: �J�����̃r���[�s��Ǝˉe�s��𓾂�
	 �߂�l: �Ȃ��BView��Proj�ɒl����
	***************************************************************************/
	void GetMatrix(D3DXMATRIX& View,D3DXMATRIX& Proj){
		View = m_View;
		Proj = m_Proj;
	}
	/**************************************************************************
	 FLOAT GetFar();
	 �p�r: �J������Far�ʒu�𓾂�
	 �߂�l: Far�ʒu
	***************************************************************************/
	FLOAT GetFar(){
		return m_Far;
	}
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	float getPosY(){ return m_Eye.y ; };
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	void setPosY( float i_fYPos ){
		if( i_fYPos < 13.4f )
			i_fYPos = 13.4f ;
		//if( i_fYPos < 25.0f )
		m_Eye.y = m_At.y = i_fYPos ; 
	};
};

/**************************************************************************
 class LookAtCamera : public Camera;
 �p�r: �I�u�W�F�N�g�𒍖ڂ���J�����N���X
****************************************************************************/
class LookAtCamera : public Camera{
protected:
	Object* m_pObject;
	FLOAT m_LocalY;
public:
	/**************************************************************************
	 LookAtCamera(
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
	LookAtCamera(LPDIRECT3DDEVICE9 pD3DDevice,
		Object* pObj,FLOAT LocalY,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
	    FLOAT Near,FLOAT Far,FLOAT FovY);
	/**************************************************************************
	 virtual ~LookAtCamera();
	 �p�r: ���z�f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
    virtual ~LookAtCamera();
	/**************************************************************************
	 virtual void Transform(
		UpdatePacket& i_UpdatePacket
	 );
	 �p�r: �I�u�W�F�N�g��ω�������i���z�֐��j
	 �߂�l: �Ȃ��B
	***************************************************************************/
	virtual void Update( UpdatePacket& i_UpdatePacket );
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
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
		const CONTROLER_STATE* pCntlState,Context& Data);
};

/**************************************************************************
 class Guide : public Object;
 �p�r: �K�C�h�N���X�ix�Ay�Az�����ɐL�т�K�C�h���j
****************************************************************************/
class Guide : public Object{
protected:
    IDirect3DVertexBuffer9* m_pVB;
    //�N���X���\����
    //�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };
	/**************************************************************************
	 void CreateInctance(
	 LPDIRECT3DDEVICE9 pD3DDevice	//IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	 );
	 �p�r: �C���X�^���X�̍\�z
	 �߂�l: �Ȃ��B�i��O��throw�����j
	***************************************************************************/
	void CreateInctance(LPDIRECT3DDEVICE9 pD3DDevice);
public:
	/**************************************************************************
	 Guide(
		LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		);
	 �p�r: �R���X�g���N�^
	 �߂�l: �Ȃ��i���s���͗�O��throw�j
	***************************************************************************/
    Guide(LPDIRECT3DDEVICE9 pD3DDevice);
	/**************************************************************************
	 virtual ~Guide();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
    virtual ~Guide();
	/**************************************************************************
		virtual void ReleaseObj();
	 �p�r: �f�o�C�X�r���ɂ�郊�\�[�X�̊J���i���z�֐��j
	 �߂�l: �Ȃ��B
	 ���f�o�C�X���r�������Ƃ��ɌĂ΂��B���ׂĂ�Object�̔h���N���X�́A�ʂɑΉ����Ƃ�
	***************************************************************************/
	virtual void ReleaseObj();
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
	};


}
//end of namespace wiz.

