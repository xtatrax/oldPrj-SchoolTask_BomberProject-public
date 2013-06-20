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
	const LPDIRECT3DDEVICE9		pD3DDevice			,
	const LPDIRECT3DTEXTURE9	pFrameTexture		,
	const LPDIRECT3DTEXTURE9	pDescTexture		,
	const LPDIRECT3DTEXTURE9	pNomalTex			,
	const LPDIRECT3DTEXTURE9	pHardTexture		,
	const LPDIRECT3DTEXTURE9	pExtraTexture		,
	const D3DXVECTOR3&			vScale				,
	const D3DXVECTOR3&			vRot				,
	const D3DXVECTOR3&			vPos				,
	const RECT*					pRect				,
	const D3DXVECTOR3&			vCenter				,
	const D3DXVECTOR3&			vOffsetPos			,
	const Color					DefaultFrameColor	,
	const Color					NormalFrameColor	,
	const Color					HardFrameColor		,
	const Color					ExtraFrameColor		,
	const wiz::OBJID			id
)
:SpriteObject( pD3DDevice, pDescTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, 0xFFFFFFFF, id)
,m_SpriteObject(pD3DDevice, pFrameTexture, vScale, vRot, vPos, pRect, vCenter, vOffsetPos, 0xFFFFFFFF, id)
,m_pDescTex(		pDescTexture	)
,m_pNomalTex(	pNomalTex		)
,m_pHardTex(	pHardTexture	)
,m_pExtraTex(	pExtraTexture	)
,m_iPtn(		0				)
,m_pButtonNormal( NULL )
,m_pButtonHard(NULL)	
,m_pButtonExtra(NULL)
,m_pButtonBack(NULL)
,m_DefaultFrameColor(DefaultFrameColor)
,m_NormalFrameColor(NormalFrameColor)
,m_HardFrameColor(HardFrameColor)
,m_ExtraFrameColor(ExtraFrameColor)

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
	m_SpriteObject.Draw( i_DrawPacket );
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
			m_SpriteObject.setColor( m_NormalFrameColor );
	}
	else
	if( m_pButtonHard && m_pButtonHard->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pHardTex;
			m_SpriteObject.setColor( m_HardFrameColor );
	}
	else
	if( m_pButtonExtra && m_pButtonExtra->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pExtraTex;
			m_SpriteObject.setColor( m_ExtraFrameColor );
			////	: �Ή��Z
			//if( m_ExtraFrameColor.byteColor.r >= 0xFF && m_ExtraFrameColor.byteColor.b == 0 ){
			//	m_ExtraFrameColor.byteColor.g++;
			//}
			////	: �Ԍ��Z
			//if( m_ExtraFrameColor.byteColor.r > 0 && m_ExtraFrameColor.byteColor.g == 0xFF && m_ExtraFrameColor.byteColor.b == 0){
			//	m_ExtraFrameColor.byteColor.r--;
			//}
			////	: ���Z
			//if( m_ExtraFrameColor.byteColor.r == 0 && m_ExtraFrameColor.byteColor.g >= 0xFF ){
			//	m_ExtraFrameColor.byteColor.b++;
			//}
			////	: �Ό��Z
			//if( m_ExtraFrameColor.byteColor.r == 0 && m_ExtraFrameColor.byteColor.g > 0 && m_ExtraFrameColor.byteColor.b == 0xFF){
			//	m_ExtraFrameColor.byteColor.g--;
			//}
			////	: �ԉ��Z
			//if( m_ExtraFrameColor.byteColor.g == 0 && m_ExtraFrameColor.byteColor.b >= 0xFF ){
			//	m_ExtraFrameColor.byteColor.r++;
			//}
			////	: �Ό��Z
			//if( m_ExtraFrameColo.r == 0 && m_ExtraFrameColo.g > 0 && m_ExtraFrameColo.b == 0xFF){
			//	m_ExtraFrameColo.g--;
			//}

	}
	else
	if( m_pButtonBack && m_pButtonBack->getButtonP()->getMouseSelect() ){
			m_pTexture	= m_pNomalTex;
	}
	else{
		//	: �ʏ펞
			m_pTexture	= m_pDescTex;	
			m_SpriteObject.setColor( m_DefaultFrameColor );
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