////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FBassMenuItems.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F
//	�����ް��Ɣ��l	�F���j���[�̕��i�Q
//					��
//	namespace wiz;
//		class Button;
//		class ButtonSprite : public SpriteObject;
//
#pragma once
#include "BassItems.h"

namespace wiz{

namespace menuobject{
/**************************************************************************
 class Button ;
 �p�r: �{�^������N���X
 �p�@: ����ButtonPlate����h�����Ȃ��N���X���{�^���ɂ��������͈ȉ��̂悤�ɂ�
	�邱�Ƃɂ���ă{�^�������邱�Ƃ��ł��܂�
	�܂����̃N���X���N���X���ɐ錾���Ă�������
		��)
		    class CLS{
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
	bool	m_IsPressed;			//����t���O
	DWORD	m_Command;				//�R�}���h
	
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
    Button(DWORD Cmd,DWORD Index);
/**************************************************************************
 virtual ~Button();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Button();
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
		Command Com;
		Com.m_Command = m_Command;
		Com.m_Param1  = 0;
		Com.m_Param2  = 0;
		return Com;
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

class ButtonSprite : public SpriteObject{
protected:
	Button m_ButtonState;
	Color  m_SelectColor;
	Color  m_UnSelectColor;
	
public:
	ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color dwSelectColor,
		Color dwUnSelectColor,DWORD dwCom,DWORD dwIndex);
	virtual ~ButtonSprite();
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���̃X�e�[�^�X
////            �F  Command Com                         // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
    virtual void Update(UpdatePacket& i_UpdatePacket);

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( LPDIRECT3DDEVICE9 pD3DDevice
////            �F  vector<Object*>& Vec)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command Com                         // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
    virtual void Draw(DrawPacket& i_DrawPacket) ;

	Button* getButtonP(){ return &m_ButtonState;}
} ;
}//end of namespace menuobject.
}//end of namespace wiz.
