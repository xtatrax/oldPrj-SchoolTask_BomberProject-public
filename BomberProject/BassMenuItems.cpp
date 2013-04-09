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
#include "StdAfx.h"
#include "BassMenuItems.h"

namespace wiz{
namespace menuobject{

/**************************************************************************
 Button ��`��
****************************************************************************/
/**************************************************************************
 Button::Button(
	DWORD Cmd,						//�I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//���j���[�X�e�[�W��̃C���f�b�N�X
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Button::Button(DWORD Cmd,DWORD Index)
:m_Index(Index),m_IsPressed(false),m_IsSelect(false),m_Command(Cmd)
{
	//�����C���f�b�N�X��0�ԂȂ�A������ԂőI������Ă���
	if(m_Index == 0){
		m_IsSelect = true;
	}
}
/**************************************************************************
 virtual ~Button::Button();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Button::~Button(){

}





ButtonSprite::ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color SelectColor,
		Color UnSelectColor,DWORD dwCom,DWORD dwIndex)
:m_ButtonState(dwCom,dwIndex)
,SpriteObject(pD3DDevice,pTexture,vScalse,vRot,vPos,pRect,vCenter,vOffset,UnSelectColor)
,m_SelectColor(SelectColor)
,m_UnSelectColor(UnSelectColor)
{
	try{
	}
	catch(...){
		//�ăX���[
		throw;
	}


}
ButtonSprite::~ButtonSprite(){};
/////////////////// ////////////////////
//// �֐���     �Fvoid ButtonSprite::Update(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            �F      vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  const CONTROLER_STATE* pCntlState   // �R���g���[���̃X�e�[�^�X
////            �F  Command i_DrawPacket.pCommand       // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
void ButtonSprite::Update(UpdatePacket& i_UpdatePacket){

};


/////////////////// ////////////////////
//// �֐���     �Fvoid ButtonSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,Tempus2* i_DrawPacket.pTime,
////            �F      vector<Object*>& Vec,Command& i_DrawPacket.pCommand)
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g��`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice        // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,               // �I�u�W�F�N�g�̔z��
////            �F  Command i_DrawPacket.pCommand                         // �R�}���h
//// �ߒl       �F����
//// ���l       �F
////            �F
////
void ButtonSprite::Draw(DrawPacket& i_DrawPacket){
	if(m_ButtonState.getSelect()){
		m_Color = m_SelectColor;
		if(m_ButtonState.getPressed()){
			*i_DrawPacket.pCommand = m_ButtonState.CommandIssue();
		}
	}else{
		m_Color = m_UnSelectColor;
	}
	SpriteObject::Draw(i_DrawPacket);
};

}//end of namespace menuobject.
}//end of namespace wiz.
