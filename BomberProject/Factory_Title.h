////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Title.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�^�C�g���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Title ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Title.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{

/*************************************************************************
class Title_Select  public SpriteObject

�S���ҁF������
�p�r�@�F�^�C�g����ʂ̃{�^��
*************************************************************************/
class	Title_Select	: public SpriteObject{
	D3DXVECTOR3		m_vPos;
	DWORD			m_dNext;
	Sound*			m_pSound;
	bool			m_bPush;
public:
	Title_Select( LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,DWORD next,
			D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos, RECT* pRect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vOffsetPos,Color color = 0xFFFFFFFF);
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
class Factory_Title;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Title{
public:
/**************************************************************************
 Factory_Title(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Title(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Title();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
