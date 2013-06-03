////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_CheckPoint ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"

namespace wiz{

/**************************************************************************
class CheckEffect;

�p�r�@�F�������̑}��
�S���ҁF������
**************************************************************************/
class CheckEffect : public PrimitiveBox{
	D3DXMATRIX		m_Matrix;
	D3DXVECTOR3		m_vPos ;
	int				m_Num;
	float			m_fWide;
	float			m_fHight;
	bool			m_bMark;
	PlayerCoil*		m_pCoil;
public:
	/////////////////// ////////////////////
	//// �p�r       �FDescription(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3		vPos,
				float			fLength,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

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
	//// �S����     �F������
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid update( int i )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	////            �F
	////
	void update( int i ,DrawPacket& i_DrawPacket);

/*************************************
�֐����@�F
�p�r�@�@�F�T�C�Y�k��
�J�e�S���F
�����@�@�F
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
	void	Reduction();

/*************************************
�֐����@�F
�p�r�@�@�F�T�C�Y�g��i�g�嗦�͏c�������j
�J�e�S���F
�����@�@�F
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
	void	Expansion();
};

/******************************************************:
******************************************************/
class CheckPoint : public Cylinder{
protected:
	struct ITEM{
		float	fPosY ;
		D3DXVECTOR3		vStartPos;
		ITEM(D3DXVECTOR3 i_vPos)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	typedef vector< ITEM* > ITEMCONTAINER ;
	ITEMCONTAINER			m_ItemContainer ;
	size_t					m_ActiveItem    ;
	PlayerCoil*				m_pCoil			;
	Camera*					m_pCamera		;
	D3DCOLORVALUE			m_Color;
	float					m_Thicken;
	float					m_Length;
	CheckEffect*			m_pEffect;
	Sound*					m_pSound;
	LPDIRECT3DTEXTURE9		m_pTexture;
/////////////////// ////////////////////
//// �֐���     �Fbool HitTestIntersect(OBB i_obb, D3DXVECTOR3 i_vMove, HITGROUNDVECTOR& o_HitListVec)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F
//// ����       �F
////            �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void SetTarget();
/////////////////// ////////////////////
//// �֐���     �Fbool HitTestIntersect(OBB i_obb, D3DXVECTOR3 i_vMove, HITGROUNDVECTOR& o_HitListVec)
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F
//// ����       �F
////            �F
//// �ߒl       �F
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void RemoveTarget();

public:
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id = OBJID_SYS_CHECKPOINT );
	~CheckPoint();
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
    virtual void Update( UpdatePacket& i_UpdatePacket );

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
//// �S����     �F���� �O
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////            �F
////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
/////////////////// ////////////////////
//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F
//// �p�r       �F�`�F�b�N�|�C���g��ǉ�
//// ����       �F
//// �ߒl       �F����
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	void add(D3DXVECTOR3 i_vPos){
		m_ItemContainer.push_back( new ITEM( i_vPos ) );
	}

/////////////////// ////////////////////
//// �p�r       �Fvoid Blink()
//// �J�e�S��   �F
//// �p�r       �F�I�u�W�F�N�g�𖾖ł�����
//// ����       �F
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
////            �F
////
	void	Blink();

};

/**************************************************************************
 class Factory_CheckPoint;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_CheckPoint{
public:
/**************************************************************************
 Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_CheckPoint();
};
}
//end of namespace wiz.
