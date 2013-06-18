////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
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




ButtonSprite::ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color SelectColor,
		Color UnSelectColor,Command Com,DWORD dwIndex)
:m_ButtonState(Com,dwIndex)
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
	if( Cursor2D::isHitSprite(this) )
		m_ButtonState.setMouseSelect(true);
	else
		m_ButtonState.setMouseSelect(false);
		//Debugger::DBGSTR::addStr(L"Button::getMouseSelectIndex() %d\n",Button::getMouseSelectIndex());
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
