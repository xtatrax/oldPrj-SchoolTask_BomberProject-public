////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Continue.cpp
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

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
namespace wiz{
namespace bomberobject{

/*************************************************************************
class Reply  public SpriteObject

�S���ҁF������
�p�r�@�F�R���e�j���[���̃{�^��
*************************************************************************/
class	Reply	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	bool			m_bMark;
	bool			m_bPushRock;
	bool			m_bWhichDraw;
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
	int	m_iTime;
public:
	Dead(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Color					color		= 0xFFFFFFFF
	);
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

	PlayerCoil*		m_pCoil;
	Reply*			m_pReply_Yes;
	Reply*			m_pReply_No;
	SpriteObject*	m_pRethinking;
	SpriteObject*	m_pContinueChar				;	//	: �R���e�j���[���S�̃|�C���^

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