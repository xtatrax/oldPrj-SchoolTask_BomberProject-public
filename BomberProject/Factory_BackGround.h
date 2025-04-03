////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_BackGround.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F�R���e�j���[
//					��
//	namespace wiz;
//		class Reply ;
//		class Dead ;
//		class Continue ;
//
#pragma once

//////////
//	: �C���N���[�h
//	: �C���N���[�h
//////////

namespace wiz{
namespace bomberobject{


//**************************************************************************//
// class Factory_BG ;
//
// �S����  : ���� �O
// �p�r    : �ǎ�
//**************************************************************************//
class BackGround : public Box{
	Camera*		m_pCamera;
	UINT		m_uiYNum;
public:
	BackGround(LPDIRECT3DDEVICE9 pD3DDevice,D3DXVECTOR3 vScalse,LPTATRATEXTURE pTextuer);

	~BackGround();

	/////////////////// ////////////////////
	//// �p�r       �Fvoid update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );
};

//**************************************************************************//
// class Factory_BG ;
//
// �S����  : ���� �O
// �p�r    : �ǎ�
//**************************************************************************//
class Factory_BG{
public:
	/////////////////// ////////////////////
	//// �֐���     �FFactory_BG( FactoryPacket* fpac );
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FFactoryPacket* fpac
	//// �ߒl       �F�Ȃ�
	//// �S��       �F ���� �O
	//// ���l       �F
	////            �F
	////
	Factory_BG( FactoryPacket* fpac );
};
}
}