////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Scroll.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓�����
//	�����ް��Ɣ��l	�F�X�N���[���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Scroll ;
//
#pragma once

#include "StdAfx.h"
namespace wiz{
namespace bomberobject{
//const static BYTE	g_csbySpriteQty  = 2 ;
//D3DXVECTOR3			g_vPos[2];
//SpriteObject*		g_pBGSpriteArr[g_csbySpriteQty];

class ScrollObject : public SpriteObject{
	D3DXMATRIX	m_Matrix1;
	D3DXMATRIX	m_Matrix2;
	D3DXVECTOR3 m_vPos1;
	D3DXVECTOR3 m_vPos2;
	D3DXVECTOR3 m_vScale;

public:
	ScrollObject(const LPDIRECT3DDEVICE9 pD3DDevice,const LPDIRECT3DTEXTURE9 pTexture,
					const D3DXVECTOR3& vScale, const D3DXVECTOR3& vPos, RECT pRect
);

/////////////////// ////////////////////
//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F���z�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////             �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////             �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////             �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////             �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////             �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
////             �F
////
	virtual void Update( UpdatePacket& i_UpdatePacket );


/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�������z�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////             �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////             �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////             �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////             �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////             �F
////
	virtual void Draw( DrawPacket& i_DrawPacket ) ;
/**************************************************************************
 ~ScrollObject();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~ScrollObject();
};

/**************************************************************************
class Factory_Scroll;

�p�r�@�F���C���H��N���X
�S���ҁF�֓� ����
****************************************************************************/
class Factory_Scroll{
public:
	Factory_Scroll(FactoryPacket* fpac);

	~Factory_Scroll();
};

}

}