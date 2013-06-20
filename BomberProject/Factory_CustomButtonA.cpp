////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CustomButtonA.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�FButtonSprite��Custom��
//					�F�^�C�g���Ƃ��Ŏg�p
//					��
//	namespace wiz;
//		class Factory_CustomButtonA ;
//
#include "StdAfx.h"
#include "Factory_CustomButtonA.h"


namespace wiz{
namespace bomberobject{
CustomButtonA::CustomButtonA(
	const LPDIRECT3DDEVICE9		pD3DDevice				,
	const LPDIRECT3DTEXTURE9	pFrameTexture			,
	const LPDIRECT3DTEXTURE9	pStringTexture			,
	const D3DXVECTOR3			vScalse					,
	const D3DXVECTOR3			vRot					,
	const D3DXVECTOR3			vPos					,
	const RECT*					pFrameRect				,
	const RECT*					pStringRect				,
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
	const DWORD					dwIndex					,
	const wiz::OBJID			id						,
	const bool					bApplyAspect	
)
:ButtonSprite(
		pD3DDevice				,
		pFrameTexture			,	//	��
		vScalse					,
		vRot					,
		vPos					,
		pFrameRect				,	//	��
		vCenter					,
		vOffset					,
		dwFrameSelectColor		,
		dwFrameUnSelectColor	,
		sSelectSound			,
		sDecisionSound			,
		fWaitTime				,
		Com						,
		dwIndex					,
		id						,
		bApplyAspect
	)
,m_dwStringSelectColor(dwStringSelectColor)
,m_dwStringUnSelectColor(dwStringUnSelectColor)
{
	m_pSprite = new PrimitiveSprite(
		pD3DDevice				,
		pStringTexture			,	//	��
		pStringRect				,
		vCenter					,
		vOffset					,
		dwStringSelectColor			//	��
	);
	m_pSprite->setMatrix(CustomButtonA::getMatrix());
}
CustomButtonA::~CustomButtonA()
{
	SafeDelete( m_pSprite );
}

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
void CustomButtonA::Update( UpdatePacket& i_UpdatePacket ){
	
	if( ButtonSprite::m_ButtonState.getMouseSelect() ){
		m_pSprite->setColor( m_dwStringSelectColor );
	}else{
		m_pSprite->setColor( m_dwStringUnSelectColor );	
	}

	ButtonSprite::Update(i_UpdatePacket);
};

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
//// �S����     �F
//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
////            �F
////
void CustomButtonA::Draw( DrawPacket& i_DrawPacket ){
	ButtonSprite::Draw(i_DrawPacket);
	m_pSprite->Draw(i_DrawPacket);
};

/**************************************************************************
 Factory_CustomButtonA ��`��
****************************************************************************/
/**************************************************************************
 Factory_CustomButtonA::Factory_CustomButtonA(
	FactoryPacket* fpac		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_CustomButtonA::Factory_CustomButtonA( FactoryPacket* fpac ){
	try{


	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_CustomButtonA::~Factory_CustomButtonA();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_CustomButtonA::~Factory_CustomButtonA(){
    //�Ȃɂ����Ȃ�
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
