////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Wall.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;

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
	PlayerCoil*		m_pCoil;
public:
	Continue(
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
};

}
}