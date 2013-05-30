////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Mouse.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�g�n ��m
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Mouse ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"

namespace wiz{
//	: UI�̍���
#define UI_HEIGHT					( 88.0f )
//	: �\����ʂ̔{�� x=800, y=512 : x=40, y=25.6
#define DRAW_CLIENT_MAGNIFICATION	( 20.0f )
//	: ���E�̔��a
#define MAGNETIC_RADIUS				( 0.5f )

// �X�N���[�����W�����[���h���W�ɕϊ�
inline D3DXVECTOR3* CalcScreenToWorld(
   D3DXVECTOR3* pout,
   int Sx,  // �X�N���[��X���W
   int Sy,  // �X�N���[��Y���W
   float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   // �e�s��̋t�s����Z�o
   D3DXMATRIX InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}
//�X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o�i CalcScreenToXZ�֐� �j
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
inline D3DXVECTOR3* CalcScreenToXZ(
   D3DXVECTOR3* pout,
   int Sx,
   int Sy,
   int Screen_w,
   int Screen_h,
   D3DXMATRIX* View,
   D3DXMATRIX* Prj
) {
   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // ���Ƃ̌������N���Ă���ꍇ�͌�_��
   // �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
   if( ray.y <= 0 ) {
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}

/**************************************************************************
 MouseCursor ��`��
****************************************************************************/
//**************************************************************************//
// class MouseCursor : public PrimitiveBox
//
// �S����  : �g�n ��m
// �p�r    : �}�E�X�J�[�\��
//**************************************************************************//
class MouseCursor : public Box , public  PrimitiveSprite{
	int			m_Ptn;
	float		m_MovePosY;
	Camera*	    m_pCamera;
	D3DXMATRIX	m_mScale;

//protected:
	///////////////////// ////////////////////
	////// �p�r       �FMouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	////// �J�e�S��   �F�R���X�g���N�^
	////// �p�r       �F�֐�
	////// ����       �F�Ȃ�
	////// �ߒl       �F�Ȃ�
	////// �S����     �F���� �O
	////// ���l       �F
	//	void UpdateTargetItem();

public:
	/////////////////// ////////////////////
	//// �p�r       �FMouseCursor(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			�F LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////            �FpTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	MouseCursor(LPDIRECT3DDEVICE9  pD3DDevice,TextureManager* m_TexMgr);

	/////////////////// ////////////////////
	//// �p�r       �F~MouseCursor();
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	~MouseCursor();

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );
};

/**************************************************************************
 class Factory_Cursor;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Cursor{
public:
/**************************************************************************
 Factory_Cursor(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Cursor(FactoryPacket* fpac);
/**************************************************************************
 ~Factory_Cursor();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Cursor();
};
}
//end of namespace wiz.