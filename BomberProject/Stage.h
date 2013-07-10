////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FDirectX Program Bass Project
//	�t�@�C����		�FStage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�X�e�[�W
//					�F�X�e�[�W�̓V�[������Ă΂�܂�
//					��
//	namespace wiz;
//		class StageLoader ;
//		class Stage ;
//		class MenuStage : public Stage ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassMenuItems.h"
#include "CSV.h"

namespace wiz{

// ���錾	
//class wiz::menuobject::Button;
using namespace menuobject ;
//class Button2;


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//**************************************************************************//
// class Stage;
//
// �S��  : ���� �O
// �p�r  : �Q�[�����X�e�[�W�P�ʂŊǗ�����N���X
//**************************************************************************//
class Stage{
protected:
	friend struct FactoryPacket		;
	friend struct BassPacket		;
	friend struct wiz::structs::UpdatePacket		;
	friend struct RenderPacket		;
	friend struct DrawPacket		;
	friend class  Button			;
	//	: ���j���[���̉�ʂւ̃|�C���^���Ƃ��Ă���
	Stage*						m_pParStage		;	//	: �e�X�e�[�W
	Stage*						m_pChildStage	;	//	: �q�X�e�[�W
	system::Sound*				m_pMySound		;
	system::Sound*				m_pSound		;
	bool						m_IsDialog		;	//	: �_�C�A���O�X�e�[�W���ǂ���
	bool						m_bUpdate		;	//	: ���̃t���O��true�ɂ���ƃX�e�[�W��update���~�܂�܂�
    vector<Object*>				m_Vec			;	//	: �z�u�I�u�W�F�N�g�̃|�C���^�̃x�N�g��
	TextureManager				m_TexMgr		;	//	: �e�N�X�`���̃|�C���^�̃x�N�g��
	vector<Button*>				m_ButtonVec		;	//	: �{�^���I�u�W�F�N�g�݂̂̔z��i�J�����Ȃǂ͓���Ȃ��j
	vector<Button*>::size_type	m_SelectIndex	;
	bool m_SelectLock;
	bool m_IsAnimetion;
	/**************************************************************************
	 void AddButton(
	 Button* pButton	//�{�^���̃|�C���^
	 );
	 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
	 �߂�l: �Ȃ�
	***************************************************************************/
	void AddButton(Object* pButton);
	/**************************************************************************
	 void AddButton(
	 Button* pButton	//�{�^���̃|�C���^
	 );
	 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
	 �߂�l: �Ȃ�
	***************************************************************************/
	void EraseButton(vector<Object*>::iterator ObjIt);
#if defined(ON_DEBUGGINGPROCESS)
	bool m_bSlow;
#endif
protected:
	/////////////////// ////////////////////
	//// �֐���     �Fvoid Stage::Clear()
	//// �J�e�S��   �F�֐�
	//// �p�r       �F����f�[�^��j������
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�f�X�g���N�^�Ő�ΌĂ΂�܂�
	////            �F
	////
	virtual void Clear();
public:
	/////////////////// ////////////////////
	//// �֐���     �FStage::Stage(Stage* Par = NULL)
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�f�t�H���g�̍\�z����
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	Stage(Stage* Par = NULL);

	/////////////////// ////////////////////
	//// �֐���     �Fvirtual Stage::~Stage()
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�f�t�H���g�̍\�z����
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	virtual ~Stage();

	/////////////////// ////////////////////
	//// �֐���     �Fconst Stage* Stage::getNextStage() 
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���̃X�e�[�W�ւ̃|�C���^��Ԃ�
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	const Stage* getNextStage() {
		return m_pParStage;
	}
	/////////////////// ////////////////////
	//// �֐���     �Fconst Stage* Stage::getPar() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�e�X�e�[�W�̃|�C���^��Ԃ�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�e�X�e�[�W�ւ̃|�C���^
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	const Stage* getPar() const{
		return m_pParStage;
	}
	/////////////////// ////////////////////
	//// �֐���     �Fconst Stage* Stage::geChild() const
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F�q�X�e�[�W�̃|�C���^��Ԃ�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�X�e�[�W�ւ̃|�C���^
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	const Stage* geChild() const{
		return m_pChildStage;
	}
	/////////////////// ////////////////////
	//// �֐���     �FStage* Stage::getLastStage()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F��ԍŌ���̎q�X�e�[�W�𓾂�
	//// ����       �F�Ȃ�
	//// �ߒl       �F��ԍŌ���̎q�X�e�[�W�̃|�C���^
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
	////            �F
	////
	Stage* getLastStage(){
		if(m_pChildStage){
			return m_pChildStage->getLastStage();
		}
		else{
			return this;
		}
	}
	/////////////////// ////////////////////
	//// �֐���     �FStage* Stage::getActiveStage()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���A�A�N�e�B�u�ȃX�e�[�W�𓾂�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�A�N�e�B�u�ȃX�e�[�W�̃|�C���^
	//// �S����     �F(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F���Ō���̎q���_�C�A���O�^�C�v�������ꍇ
	////            �F  ���̃_�C�A���O��ێ�����X�e�[�W�𓾂�
	////
	Stage* getActiveStage(){
		Stage* ret = getLastStage();
		while(	ret && ret->m_IsDialog){
			if( ret->m_pParStage )
				ret = ret->m_pParStage;
			else
				return ret;
		}
		return ret;
	}
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void ButtonUpdateUpdate( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�{�^�����X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	virtual void ButtonUpdate(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�X�e�[�W���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	virtual void Update(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Render(RenderPacket& i_RenderPacket);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�^�[�Q�b�g�����_�����O
	//// ����       �F  RenderPacket& i_RenderPacket        // �����_�[�����ɗ����f�[�^�̏W����
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F��ʈȊO�̃o�b�t�@�[�ɕ`�悷��
	////            �F
	////
    virtual void Render(RenderPacket& i_RenderPacket);
	
	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�V�[����`��
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O(�R�m��搶�̂ЂȌ`���)
	//// ���l       �F
    virtual void Draw(DrawPacket& i_DrawPacket) ;
	/////////////////// ////////////////////
	//// �p�r       �F
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	void TargetRender(BassPacket& BassPacket, Object* DrawObject, Object* RenderTarget);
	/////////////////// ////////////////////
	//// �p�r       �F
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	void DefaultRender();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid CommandTranslator(DrawPacket& i_DrawPacket);
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�R�}���h�����߂��ăX�e�[�W�̐؂�ւ��Ȃǂ��s��
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void CommandTranslator(DrawPacket& i_DrawPacket);

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class MenuStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class MenuStage : public Stage{
protected:
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MenuStage();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState	//�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,  //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class MenuStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class MenuStage2 : public Stage{
protected:
	vector<Button*> m_Button2Vec;
	//�{�^���I�u�W�F�N�g�݂̂̔z��i�J�����Ȃǂ͓���Ȃ��j
	vector<Button*>::size_type m_SelectIndex;
	bool m_SelectLock;
	bool m_IsAnimetion;
/**************************************************************************
 void AddButton2(
 Button2* pButton2	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����B����ȊO��m_Vec�ɂ��K�������
 �߂�l: �Ȃ�
***************************************************************************/
	void AddButton2(Object* pButton2);
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	MenuStage2(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~MenuStage2();
/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
	void Update(UpdatePacket& i_UpdatePacket);

/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,	//�R���g���[���[�̃X�e�[�^�X
	Command& i_DrawPacket.pCommand		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(DrawPacket& i_DrawPacket);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace wiz.
