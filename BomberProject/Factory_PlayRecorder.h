////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_PlayRecorder.h
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
struct PlayData{
	float		fBeginTime		;
	enum {
		CT_L,
		CT_R,
		CT_M,
	}enumClickType				;
	D3DXVECTOR3 vClickPoint		;
	float		fEndTime		;
};
struct PDBHeader{
	DWORD m_dwBodyQty;
};
struct PDBBody{
	
};
struct PlayDataBIN : public BassSaveaPacketDat{
	BassSaveaPacketDat stIdentifier ;
	
	
};

class PlayRecorder : public Behavior{
	list<PlayData*> m_DataVec		;
	PlayData*		m_pLButtonBuf	;
	PlayData*		m_pMButtonBuf	;
	PlayData*		m_pRButtonBuf	;

	Camera*			m_pCamera		;
public:
	PlayRecorder(wiz::OBJID id);
	~PlayRecorder();
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Demo2Titre::Update( UpdatePacket& i_UpdatePacket )
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

class RecorderFactory{
public:
	RecorderFactory(FactoryPacket* fpac);
};
}
using namespace bomberbehavior ;
}