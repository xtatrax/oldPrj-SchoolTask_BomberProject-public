////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPointSave.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�`�F�b�N�|�C���g�ʉ݂ŃZ�[�u����@�\
//					��
//	namespace wiz;
//
#pragma once

//////////
//	: �C���N���[�h
#include "Factory_CheckPoint.h"
//	: �C���N���[�h
//////////

namespace wiz{
using namespace bomberobject ;
namespace bomberbehavior{
class CheckPointSave : public Behavior{
	static CheckPointSave*	m_pMyInstance	;
	       CheckPoint*		m_pCheckPoint	;
		   PlayerCoil*		m_pCoil			;
		   SaveData			m_Data			;
	/////////////////// ////////////////////
	//// �p�r       �FCheckPointSave::CheckPointSave();
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	CheckPointSave(DWORD dwStageNum);
public:
	static CheckPointSave* getInstance(DWORD dwStageNum){
		if( m_pMyInstance )return m_pMyInstance;
		return new CheckPointSave(dwStageNum);
	}
	/////////////////// ////////////////////
	//// �p�r       �Fvoid CheckPointSave::Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

};

//**************************************************************************//
// class Factory_CheckPointSave ;
//
// �S��  : ���� �O
// �p�r  : �`�F�b�N�|�C���g�ŃZ�[�u���s���@�\���쐬���܂�
//**************************************************************************//
class Factory_CheckPointSave{
public:
	/////////////////// ////////////////////
	//// �֐���     �FFactory_CheckPointSave(FactoryPacket* fpac)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�`�F�b�N�|�C���g�ŃZ�[�u����@�\���쐬���܂�
	//// ����       �F  FactoryPacket* fpac
	//// �ߒl       �F�Ȃ�
	//// �S��       �F���� �O
	//// ���l       �F
	////            �F
	////
	Factory_CheckPointSave(FactoryPacket* fpac,DWORD dwStageNum);
	~Factory_CheckPointSave(){};
};

}
using namespace bomberbehavior ;
}