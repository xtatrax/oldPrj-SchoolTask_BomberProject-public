////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Mouse.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�g�n ��m
//  ���p��			�F���� �O
//	�ҏW			�F���� ��
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class Factory_Mouse ;
//
#pragma once

//////////
//	: �C���N���[�h
#include "Line.h"
//	: �C���N���[�h
//////////
namespace wiz{
namespace bomberobject{
enum MOUSE_POSITION{
	RIGTH	,
	LEFT	,
};

//**************************************************************************//
// class MouseCursor : public PrimitiveBox
//
// �S����  : �g�n ��m
// ���p��  : ���� �O
// �p�r    : �}�E�X�J�[�\��
//**************************************************************************//
class MouseCursor : public Box , public  PrimitiveSprite{

	int					m_Ptn		;
	float				m_MovePosY	;
	Camera*				m_pCamera	;
	D3DXMATRIX			m_mScale	;
	D3DXVECTOR3			m_v3DPos	;
	D3DXVECTOR3			m_vScale	;
	Point				m_v2DPos	;
	Line*				m_pLine		;
	Line*				m_pLine2	;
	Torus*				m_pTorus	;
	SpriteObject*		m_pSelectPos;
	float				m_fTorusMagnification;
//protected:

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
	MouseCursor(LPDIRECT3DDEVICE9  pD3DDevice,TextureManager* m_TexMgr, float fLineLength, float fPointSize);

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
	Point		get2DPos(){ return m_v2DPos ; };
	D3DXVECTOR3	get3DPos(){ return m_v3DPos ; };

protected:

	//	: 
	void Update2DPos();
	//	: 
	void Update3DPos();
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
	Factory_Cursor(FactoryPacket* fpac, float fLineLength, float fPointSize );
/**************************************************************************
 ~Factory_Cursor();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Cursor();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.