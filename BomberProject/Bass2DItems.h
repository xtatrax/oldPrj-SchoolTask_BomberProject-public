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
#include "TL-String.h"
namespace wiz {

namespace base2Dobject{

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
	void setMatrix( D3DXMATRIX i_mMatrix ){ m_mMatrix = i_mMatrix ; }

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

}//end of namespace base2Dobject.
using namespace base2Dobject;
}//end of namespace wiz.
