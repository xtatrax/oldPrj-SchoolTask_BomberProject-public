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
#pragma once
#include "BassItems.h"
#include "Bass2DItems.h"

namespace wiz{

namespace menuobject{


class ButtonSprite : public SpriteObject{
protected:
	Button	m_ButtonState		;
	Color	m_SelectColor		;
	Color	m_UnSelectColor		;
public:
	ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 vScalse,D3DXVECTOR3 vRot,D3DXVECTOR3 vPos,RECT* pRect,
		D3DXVECTOR3 vCenter,D3DXVECTOR3 vOffset,Color dwSelectColor,
		Color dwUnSelectColor,Command Com,DWORD dwIndex);
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
using namespace menuobject ;
}//end of namespace wiz.
