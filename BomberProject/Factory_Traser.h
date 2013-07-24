////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Traser.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//
#pragma once

//////////
//	: �C���N���[�h
//	: �C���N���[�h
//////////

namespace wiz{
namespace bomberbehavior{

class PlayTraser : public Behavior{
public:
	PlayTraser(wiz::OBJID id);
	~PlayTraser();
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void PlayTraser::Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
	virtual void Update( UpdatePacket& i_UpdatePacket );
};

class TraserFactory{
public:
	TraserFactory(FactoryPacket* fpac);
};
}
using namespace bomberbehavior ;
}