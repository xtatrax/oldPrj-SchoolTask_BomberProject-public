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

class SelectInformation : public SpriteObject{
public:
	SelectInformation(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		,
		const wiz::OBJID			id			= OBJID_UI_SELECTINFORMATION
	);
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