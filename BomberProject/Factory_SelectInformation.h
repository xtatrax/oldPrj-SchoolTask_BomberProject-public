////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_SelectInformation.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�Z���N�g��ʂ̐����E�C���h�E
//					��
//	namespace wiz;
//
#pragma once

//////////
//	: �C���N���[�h
//	: �C���N���[�h
//////////

namespace wiz{
namespace bomberobject{
class CustomButtonA ;
class SelectInformation : public SpriteObject{
	SpriteObject		m_SpriteObject		;
	LPDIRECT3DTEXTURE9	m_pDescTex			;
	LPDIRECT3DTEXTURE9	m_pNomalTex			;
	LPDIRECT3DTEXTURE9	m_pHardTex			;
	LPDIRECT3DTEXTURE9	m_pExtraTex			;
	int					m_iPtn				;
	CustomButtonA*		m_pButtonNormal		;
	CustomButtonA*		m_pButtonHard		;
	CustomButtonA*		m_pButtonExtra		;
	CustomButtonA*		m_pButtonBack		;
	Color				m_DefaultFrameColor	;
	Color				m_NormalFrameColor	;
	Color				m_HardFrameColor	;
	Color				m_ExtraFrameColor	;

public:
	SelectInformation(
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
		const wiz::OBJID			id					= OBJID_UI_SELECTINFORMATION
	);

	~SelectInformation();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	void	setPtn( int i ){
		m_iPtn	= i;
	}
	int		getPtn(){
		return	m_iPtn;
	}
};


//**************************************************************************//
// class Factory_SelectInformation ;
//
// �S��  : ���� �O
// �p�r  : �`�F�b�N�|�C���g�ŃZ�[�u���s���@�\���쐬���܂�
//**************************************************************************//
class Factory_SelectInformation{
public:
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
	Factory_SelectInformation(FactoryPacket* fpac);
	~Factory_SelectInformation(){};
};

}
using namespace bomberobject ;
}