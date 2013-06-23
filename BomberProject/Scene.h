////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FScene.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�V�[��
//					�F�V�[���̓f�o�C�X����Ă΂�܂�
//					��
//	namespace wiz;
//		class Scene ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Stage.h"

namespace wiz{
namespace system{
//**************************************************************************
// class Scene;
//
// �S����  : ���� �O(�R�m��搶�̂ЂȌ`���)
// �p�r    : �V�[�����Ǘ�����N���X
//         : 
//**************************************************************************/
class Scene
{
	//////////
	//	: ���[�h��ʐ�p
	//LPDIRECT3DDEVICE9 m_pD3DDevice		;
	Command	m_LoadCommand				;
	static HANDLE	m_hLoadingThread	;	// ���[�h��ʗp�X���b�h�̃n���h��
	bool	m_bLoadingComplete			;
	Stage*	m_pStgBuf					;
	//
	//////////

	float	m_fStageNotFoundMessageTime		;

	Stage*	m_pRootStage					;
	bool	m_bUpdateThreadSuspendRequest	;	//	: �X���b�h��~�v���t���O(���C���X���b�h���s->�A�b�v�f�[�g�X���b�h����)
	bool	m_bUpdateThreadSuspend			;	//	: �X���b�h��~�����t���O(�A�b�v�f�[�g�X���b�h���s->���C���X���b�h����)
	bool	m_bUpdateThreadResumeRequest	;	//	: �X���b�h�ĊJ�v���t���O(�V�[�����s->�f�o�C�X����)


//	: ����J�֐�
private:

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Clear()
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g�̃N���A
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
    void Clear();
	
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setStages()
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�X�e�[�W���X�g���\�z
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
    void setStages();
public:
	/////////////////// ////////////////////
	//// �֐���     �FScene(LPDIRECT3DDEVICE9 pD3DDevice)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�V�[���𐶐�
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F���s�������O��throw
	////            �F
	////
	Scene(LPDIRECT3DDEVICE9 pD3DDevice,Command* pCommand );
	/////////////////// ////////////////////
	//// �֐���     �F~Scene()
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F�V�[����j��
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
    virtual ~Scene();
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Update(UpdatePacket& i_UpdatePacket)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�V�[�����X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket        // �A�b�v�f�[�g�����ɗ����f�[�^�̏W����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
    void Update(UpdatePacket& i_UpdatePacket);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Render(RenderPacket& i_RenderPacket);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�^�[�Q�b�g�����_�����O
	//// ����       �F  RenderPacket& i_RenderPacket        // �����_�[�����ɗ����f�[�^�̏W����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
	////            �F
	////
    void Render(RenderPacket& i_RenderPacket);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Draw(DrawPacket& i_DrawPacket);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�V�[����`��
	//// ����       �F  DrawPacket& i_DrawPacket            // �h���[�����ɗ����f�[�^�̏W����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
	////            �F
	////
	void Draw(DrawPacket& i_DrawPacket);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  Command& i_DrawPacket.pCommand      // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void CommandTranslator(DrawPacket& i_DrawPacket);
	/////////////////// ////////////////////
	//// �֐���     �Funsigned __stdcall LoadingThreadLauncher(void *args)
	//// �J�e�S��   �F�֐�
	//// �p�r       �F���[�h��p�̃X���b�h���N�����܂�
	//// ����       �Fvoid *args //
	//// �ߒl       �F0
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	static unsigned __stdcall LoadingThread(void* args);
	//static void LoadingThread(void* args);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommandTranslator(LPDIRECT3DDEVICE9 pD3DDevice,Command& i_DrawPacket.pCommand);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,       // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  Command& i_DrawPacket.pCommand						// �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void LoadingThreadStarter(LPDIRECT3DDEVICE9 pD3DDevice,const Command* pCommand);
	/////////////////// ////////////////////
	//// �֐���     �Fvoid SafeDeleteStage()
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�X�e�[�W�����S�ɍ폜����
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void SafeDeleteStage(Stage* &pStage);

//////////
//  : �Q�b�^�[
public:
	/////////////////// ////////////////////
	//// �֐���     �Fbool getUpdateThreadSuspendRequest()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̈ꎞ��~�v���̊m�F
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F���C���X���b�h->�A�b�v�f�[�g�X���b�h
	////            �F
	////
	bool getUpdateThreadSuspendRequest(){
		return m_bUpdateThreadSuspendRequest;
	};
	/////////////////// ////////////////////
	//// �֐���     �Fbool getUpdateThreadSuspend()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̈ꎞ��~�����̊m�F
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�A�b�v�f�[�g�X���b�h->���C���X���b�h
	////            �F
	////
	bool getUpdateThreadSuspend(){
		return m_bUpdateThreadSuspend;
	};
	/////////////////// ////////////////////
	//// �֐���     �Fbool getUpdateThreadSuspend()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̍ĊJ�v���̊m�F
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�V�[��->�f�o�C�X
	////            �F
	////
	bool getUpdateThreadResumeRequest(){
		return m_bUpdateThreadResumeRequest;
	};


//////////
//  : �Z�b�^�[
public:
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setUpdateThreadSuspendRequest()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̈ꎞ��~�v��
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F���C���X���b�h->�A�b�v�f�[�g�X���b�h
	////            �F
	////
	void setUpdateThreadSuspendRequest(){
		m_bUpdateThreadSuspendRequest = true ;
	};
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setUpdateThreadSuspend()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̈ꎞ��~�����m�F
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�A�b�v�f�[�g�X���b�h->���C���X���b�h
	////            �F
	////
	void setUpdateThreadSuspend(){
		m_bUpdateThreadSuspend        = true ;
	};
	/////////////////// ////////////////////
	//// �֐���     �Fvoid setUpdateThreadSuspend()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̍ĊJ�v��
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�A�b�v�f�[�g�X���b�h->�S��
	////            �F
	////
	void setUpdateThreadResumeRequest(){
		m_bUpdateThreadResumeRequest = true ;
	};

	/////////////////// ////////////////////
	//// �֐���     �Fvoid setUpdateThreadSuspend()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�A�b�v�f�[�g�X���b�h�̍ĊJ�ʒm
	//// ����       �F����
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�A�b�v�f�[�g�X���b�h->�S��
	////            �F
	////
	void setUpdateThreadResume(){
		m_bUpdateThreadSuspendRequest = false ;	//	: �X���b�h��~�v���t���O(���C���X���b�h->�A�b�v�f�[�g�X���b�h)
		m_bUpdateThreadSuspend        = false ;	//	: �X���b�h��~�����t���O(�A�b�v�f�[�g�X���b�h->���C���X���b�h)
		m_bUpdateThreadResumeRequest  = false ;	//	: �X���b�h�ĊJ�v���t���O(�V�[��->�f�o�C�X)
	};

};
}
//end of namespace system.
using namespace system ;
}
//end of namespace wiz.

