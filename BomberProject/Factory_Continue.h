////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Continue.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� ��
//	�����p��		�F���� �O
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
#include "Factory_Coil.h"
#include "Factory_Score.h"
//	: �C���N���[�h
//////////

namespace wiz{
namespace bomberobject{
enum CONTINUEBEHAVIORPHASE{
	CONTINUEBEHAVIORPHASE_WAIT				,
	CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE	,
	CONTINUEBEHAVIORPHASE_CONTINUESELECTION	,
	CONTINUEBEHAVIORPHASE_CHECKSELECTION		,

};
///*************************************************************************
//class ContinueButton : public ButtonSprite
//
//�S���ҁF���� �O
//�p�r�@�F�R���e�j���[���̃{�^��
//*************************************************************************/
class ContinueButton : public ButtonSprite{
	Command			m_IssueCommand	;
	bool			m_bIsOperating	;
public:
	ContinueButton(
		const LPDIRECT3DDEVICE9		pD3DDevice			,
		const LPTATRATEXTURE	pTexture			,
		const D3DXVECTOR3			vScalse				,
		const D3DXVECTOR3			vPos				,
		const Rect*					pRect				,
		const float					fWaitTime			,
		const Command				Com					,
		const wiz::OBJID			id						
	);
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
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
	//// ���l       �F
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ) ;
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
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
	virtual void Draw( DrawPacket& i_DrawPacket );
	void getIssueCommand(Command& ret){
		if( m_IssueCommand.m_Command != GM_WITHOUT ){
			ret = m_IssueCommand ;
		}
	}
	void OperationStart(){
		m_bIsOperating = true ;
	}
	void OperationEnd(){
		m_bIsOperating = false ;
	}
};
///*************************************************************************
//class ContinueButton : public ButtonSprite
//
//�S���ҁF���� ��
//���p���F���� �O
//�p�r�@�F�R���e�B�j���[��ʂ̓�����`���Ă��܂�
//*************************************************************************/
class ContinueBehavior : public Behavior{
	LPTATRATEXTURE			m_pPTContinue		;
	LPTATRATEXTURE			m_pPTReally			;
	SpriteObject*			m_pPageTitle		;
	SpriteObject*			m_pDeadMessage		;
	ContinueButton*			m_pYesButton		;
	ContinueButton*			m_pNoButton			;
	Score*					m_pDeadScore		;
	SpriteObject*			m_pDeadCountChar	;
	PlayerCoil*				m_pCoil				;
	TimeScore*				m_pTime				;
	float					m_fDeadMessageTimeAccumulator	;
	float					m_fFadeOutTimeAccumulator		;
	const float				m_fMessageTime		;
	const float				m_fFadeOutTime		;
	float					m_fDeadMessageAlpha	;
	CONTINUEBEHAVIORPHASE	m_NowBehaviorFaze	;
public:
	ContinueBehavior( FactoryPacket& i_BassPacket);
	~ContinueBehavior();

	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
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
	//// ���l       �F
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket ) ;
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
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
	virtual void Draw( DrawPacket& i_DrawPacket );

	void OperationStart(){
		m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_DRAWDEADMESSAGE;
		m_fDeadMessageAlpha = 255.0f ;
		m_pDeadMessage->setAlpha(0xFF);
		m_fDeadMessageTimeAccumulator = 0.0f ;
		m_fFadeOutTimeAccumulator = 0.0f ;
		m_pDeadScore->setScore(m_pCoil->getDeadCount()+1);
		m_pDeadScore->setAlpha(0xFF);
		m_pDeadCountChar->setAlpha(0xFF);

	}
	void OperationStop(){
		m_NowBehaviorFaze = CONTINUEBEHAVIORPHASE_WAIT;
	}
};


///*************************************************************************
//class Reply  public SpriteObject
//
//�S���ҁF������
//�p�r�@�F�R���e�j���[���̃{�^��
//*************************************************************************/
//class	Reply	: public SpriteObject{
//	D3DXVECTOR3		m_vPos			;
//	bool			m_bMark			;
//	bool			m_bPushRock		;
//	bool			m_bWhichDraw	;
//	int				m_iTime			;
//	bool			m_bPush			;
//	bool			m_bSelect		;
//	DWORD			m_dNext			;
//	PlayerCoil*		m_pCoil			;
//
//public:
//	Reply(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const bool					mark		,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vRot		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const D3DXVECTOR3&			vCenter		,
//		const D3DXVECTOR3&			vOffsetPos	,
//		const Color					color		= 0xFFFFFFFF
//	);
//	~Reply();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//
//	bool	getWhichDraw(){
//		return	m_bWhichDraw;
//	}
//	void	setWhichDraw(bool b){
//		m_bWhichDraw	= b;
//	}
//};
//
///*************************************************************************
//class Continue  public SpriteObject
//
//�S���ҁF������
//�p�r�@�F�R���e�j���[���̃{�^��
//*************************************************************************/
//class	Continue	: public SpriteObject{
//	D3DXVECTOR3		m_vPos;
//	bool			m_bMark;
//	bool			m_bPushRock;
//	bool			m_bWhichDraw;
//
//	int				m_iTime			;
//	bool			m_bPush			;
//	bool			m_bSelect		;
//	DWORD			m_dNext			;
//	bool			m_bDrawing		;
//
//
//	PlayerCoil*		m_pCoil;
//	Reply*			m_pReply_Yes;
//	Reply*			m_pReply_No;
//	SpriteObject*	m_pRethinking;
//	SpriteObject*	m_pContinueChar				;	//	: �R���e�j���[���S�̃|�C���^
//	TimeScore*		m_pTime;
//
//	LPTATRATEXTURE	m_pRethinkingTex;	//Really?
//	LPTATRATEXTURE	m_pAnswerTex	;	//Yes : No
//	LPTATRATEXTURE	m_pContinueTex	;	//Yes : No
//public:
//	Continue(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const LPTATRATEXTURE	pTexture_Rethinking	,
//		const LPTATRATEXTURE	pTexture_Answer		,
//		const bool					mark		,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const wiz::OBJID			id			,
//		const Color					color		= 0xFFFFFFFF
//	);
//	~Continue();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//
//	bool	getWhichDraw(){
//		return	m_bWhichDraw;
//	}
//	void	setDrawing( bool i_bDrawing ){
//		m_bDrawing	= i_bDrawing;
//	}
//};
//
///*************************************************************************
//class Dead  public SpriteObject
//
//�S���ҁF������
//�p�r�@�F���S���ɏo������
//*************************************************************************/
//class	Dead	: public SpriteObject{
//	float			m_fTime;
//	int				m_iDeadCount;
//	bool			m_bDrawing;
//	Score*			m_pDeadScore;
//	SpriteObject*	m_pDeadCountChar;
//	Continue*		m_pSelect_Yes;
//	Continue*		m_pSelect_No;
//public:
//	Dead(
//		const LPDIRECT3DDEVICE9		pD3DDevice	,
//		const LPTATRATEXTURE	pTexture	,
//		const LPTATRATEXTURE	pDeadCountTex	,
//		const LPTATRATEXTURE	pCountCharTex	,
//		const int					iDeadCount	,
//		const D3DXVECTOR3&			vScale		,
//		const D3DXVECTOR3&			vPos		,
//		const Rect*					pRect		,
//		const Color					color		= 0xFFFFFFFF,
//		const wiz::OBJID			id			= OBJID_UI_DEAD_CHAR
//
//	);
//	~Dead();
//	void	Draw(DrawPacket& i_DrawPacket);
//	void	Update(UpdatePacket& i_UpdatePacket);
//	BYTE	getAlpha(){
//		return m_Color.byteColor.a;
//	}
//	void	setDrawing( bool i_bDraw ){
//		m_bDrawing	= i_bDraw;
//	}
//
//	void	setCount( int i_iCount ){
//		m_iDeadCount	= i_iCount;
//	}
//};

/**************************************************************************
class Factory_Continue;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Continue{
public:
/**************************************************************************
 Factory_Continue(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Continue(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Continue();
};

}
}