////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Continue.h
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
#include "Factory_Coil.h"
#include "Factory_Score.h"
//	: �C���N���[�h
//////////

namespace wiz{
namespace bomberobject{


class ContinueBehavior : public Behavior{
	PlayerCoil*			m_pCoil			;
	ButtonSprite		m_YesButton		;
	ButtonSprite		m_NoButton		;
	SpriteObject		m_PageName		;
	LPDIRECT3DTEXTURE9	m_pDeadTex		;
	LPDIRECT3DTEXTURE9	m_pContinueTex	;
	LPDIRECT3DTEXTURE9	m_pCheckTex		;
	bool				m_bIsCheck		;
public:
	ContinueBehavior(BassPacket& i_BassPacket);
	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O

	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

};










/*************************************************************************
class Reply  public SpriteObject

�S���ҁF������
�p�r�@�F�R���e�j���[���̃{�^��
*************************************************************************/
class	Reply	: public SpriteObject{
	D3DXVECTOR3		m_vPos			;
	bool			m_bMark			;
	bool			m_bPushRock		;
	bool			m_bWhichDraw	;
	int				m_iTime			;
	bool			m_bPush			;
	bool			m_bSelect		;
	DWORD			m_dNext			;
	PlayerCoil*		m_pCoil			;

public:
	Reply(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Reply();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
	void	setWhichDraw(bool b){
		m_bWhichDraw	= b;
	}
};

/*************************************************************************
class Dead  public SpriteObject

�S���ҁF������
�p�r�@�F���S���ɏo������
*************************************************************************/
class	Dead	: public SpriteObject{
	int				m_iTime;
	Score*			m_pDeadScore;
	SpriteObject*	m_pDeadCountChar;
public:
	Dead(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pDeadCountTex	,
		const LPDIRECT3DTEXTURE9	pCountCharTex	,
		const int					iDeadCount	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Dead();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	BYTE	getAlpha(){
		return m_Color.byteColor.a;
	}
};

/*************************************************************************
class Continue  public SpriteObject

�S���ҁF������
�p�r�@�F�R���e�j���[���̃{�^��
*************************************************************************/
class	Continue	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	bool			m_bPushRock;
	bool			m_bWhichDraw;

	int				m_iTime			;
	bool			m_bPush			;
	bool			m_bSelect		;
	DWORD			m_dNext			;


	PlayerCoil*		m_pCoil;
	Reply*			m_pReply_Yes;
	Reply*			m_pReply_No;
	SpriteObject*	m_pRethinking;
	SpriteObject*	m_pContinueChar				;	//	: �R���e�j���[���S�̃|�C���^
	TimeScore*		m_pTime;

	LPDIRECT3DTEXTURE9	m_pRethinkingTex;	//Really?
	LPDIRECT3DTEXTURE9	m_pAnswerTex	;	//Yes : No
	LPDIRECT3DTEXTURE9	m_pContinueTex	;	//Yes : No
public:
	Continue(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const LPDIRECT3DTEXTURE9	pTexture_Rethinking	,
		const LPDIRECT3DTEXTURE9	pTexture_Answer		,
		const bool					mark		,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
	~Continue();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getWhichDraw(){
		return	m_bWhichDraw;
	}
};

}
}