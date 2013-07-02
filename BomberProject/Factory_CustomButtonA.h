////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CustomButtonA.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�FButtonSprite��Custom��
//					�F�^�C�g���Ƃ��Ŏg�p
//					��
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#pragma once

#include "StdAfx.h"


namespace wiz{
namespace bomberobject{

class CustomButtonA : public ButtonSprite{
	PrimitiveSprite*	m_pSprite				;
	Color				m_dwStringSelectColor	;
	Color				m_dwStringUnSelectColor	;
	int					m_iPtn					;
public:
	CustomButtonA(
		const LPDIRECT3DDEVICE9		pD3DDevice				,
		const LPTATRATEXTURE		pFrameTexture			,
		const LPTATRATEXTURE		pStringTexture			,
		const D3DXVECTOR3			vScalse					,
		const D3DXVECTOR3			vRot					,
		const D3DXVECTOR3			vPos					,
		const Rect*					pFrameRect				,
		const Rect*					pStringRect				,
		const D3DXVECTOR3			vCenter					,
		const D3DXVECTOR3			vOffset					,
		const Color					dwFrameSelectColor		,
		const Color					dwFrameUnSelectColor	,
		const Color					dwStringSelectColor		,
		const Color					dwStringUnSelectColor	,
		const char*					sSelectSound			,
		const char*					sDecisionSound			,
		const float					fWaitTime				,
		const Command				Com						,
		const wiz::OBJID			id						,
		const bool					bKillAfterIssuing		= false		,
		const bool					bApplyAspect			= true
	);


	~CustomButtonA();

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
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F
	//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
	////            �F
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
};


/**************************************************************************
 class Factory_CustomButtonA;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_CustomButtonA{
public:
	/**************************************************************************
	 Factory_CustomButtonA(
		FactoryPacket* fpac //�p�P�b�g�f�[�^
	);
	 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
	 �߂�l: �Ȃ�
	***************************************************************************/
	Factory_CustomButtonA( FactoryPacket* fpac );
	/**************************************************************************
	 ~MyFactory();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
	~Factory_CustomButtonA();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
