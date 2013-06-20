////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_SelectInformation.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�Z���N�g��ʂ̐����E�C���h�E
//					��
//	namespace wiz;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_SelectInformation.h"
//	: ��{�̃C���N���[�h
//////////
//////////
//	: �ǉ��̃C���N���[�h
#include "Factory_CustomButtonA.h"
//	: �ǉ��̃C���N���[�h
//////////


namespace wiz{
namespace bomberobject{
/**************************************************************************
 SelectInformation ��`��
***************************************************************************/
SelectInformation::SelectInformation(
	const LPDIRECT3DDEVICE9		pD3DDevice	,
	const LPDIRECT3DTEXTURE9	pTexture	,
	const LPDIRECT3DTEXTURE9	pNomalTex	,
	const LPDIRECT3DTEXTURE9	pHardTexture	,
	const LPDIRECT3DTEXTURE9	pExtraTexture	,
	const D3DXVECTOR3&			vScale		,
	const D3DXVECTOR3&			vRot		,
	const D3DXVECTOR3&			vPos		,
	const RECT*					pRect		,
	const D3DXVECTOR3&			vCenter		,
	const D3DXVECTOR3&			vOffsetPos	,
	const Color					color		,
	const wiz::OBJID			id
)
:SpriteObject( pD3DDevice, pTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, color, id)
,m_pTex(		pTexture		)
,m_pNomalTex(	pNomalTex		)
,m_pHardTex(	pHardTexture	)
,m_pExtraTex(	pExtraTexture	)
,m_iPtn(		0				)
,m_pButtonNormal( NULL )
,m_pButtonHard(NULL)	
,m_pButtonExtra(NULL)
,m_pButtonBack(NULL)
{	
}

/**********************************************************
�f�X�g���N�^
**********************************************************/
SelectInformation::~SelectInformation()
{
}

/**********************************************************
�`��
**********************************************************/
void	SelectInformation::Draw(DrawPacket &i_DrawPacket)
{
	SpriteObject::Draw( i_DrawPacket );
}

/**********************************************************
�X�V
**********************************************************/
void	SelectInformation::Update(UpdatePacket &i_UpdatePacket)
{
	if( !m_pButtonNormal ) m_pButtonNormal  = (CustomButtonA*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_BUTTON_NORMAL);
	if( !m_pButtonHard   ) m_pButtonHard    = (CustomButtonA*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_BUTTON_HARD  );
	if( !m_pButtonExtra  ) m_pButtonExtra   = (CustomButtonA*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_BUTTON_EXTRA );
	if( !m_pButtonBack   ) m_pButtonBack    = (CustomButtonA*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_UI_BUTTON_BACK  );

	if( m_pButtonNormal && m_pButtonNormal->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pNomalTex;
	}
	else
	if( m_pButtonHard && m_pButtonHard->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pHardTex;
	}
	else
	if( m_pButtonExtra && m_pButtonExtra->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pExtraTex;
	}
	else
	if( m_pButtonBack && m_pButtonBack->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pNomalTex;
	}
	else{
			m_pTexture	= m_pTex;	
	}
}
/**************************************************************************
 Factory_SelectInformation ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FFactory_SelectInformation(FactoryPacket* fpac)
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�`�F�b�N�|�C���g�ŃZ�[�u����@�\���쐬���܂�
//// ����       �F  FactoryPacket* fpac
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
Factory_SelectInformation::Factory_SelectInformation(FactoryPacket* fpac){
	
};


}
}