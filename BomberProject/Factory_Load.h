////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Load ;
//		class Factory_Load ;
//
#pragma once

#include "StdAfx.h"
#include "Factory_Load.h"
#include "Factory_Sound.h"


namespace wiz{
namespace bomberobject{

/*************************************************************************
class Load  public SpriteObject

�S���ҁF������
�p�r�@�F�^�C�g����ʂ̃{�^��
*************************************************************************/
class	Load	: public SpriteObject{
	Command			m_Com;
	D3DXVECTOR3		m_vPos;
	int				m_iTime;
	float			m_fRate;
	int				m_iPtn;
public:
	Load(
		const LPDIRECT3DDEVICE9		pD3DDevice	,
		const LPDIRECT3DTEXTURE9	pTexture	,
		const D3DXVECTOR3&			vScale		,
		const D3DXVECTOR3&			vRot		,
		const D3DXVECTOR3&			vPos		,
		const RECT*					pRect		,
		const D3DXVECTOR3&			vCenter		,
		const D3DXVECTOR3&			vOffsetPos	,
		const Command*				Com			,
		const Color					color		= 0xFFFFFFFF
	);
	~Load();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
class Factory_Load;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Load{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Load(FactoryPacket* fpac,Command* Com);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Load();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
