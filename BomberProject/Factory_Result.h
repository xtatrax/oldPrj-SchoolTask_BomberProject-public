////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Result.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject;
//		class Factory_Result ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Sound.h"

namespace wiz{
namespace bomberobject{

enum Result_Rank{
	Rank_S	= 1,
	Rank_A,
	Rank_B,
	Rank_C
};

/************************************************************
class  Rank  : public SpriteObject

�p�r�@�F�����N
�S���ҁF������
************************************************************/
class	Rank	: public	SpriteObject{
	bool				m_bDrawing;
	LPDIRECT3DTEXTURE9	m_pTex_S;
	LPDIRECT3DTEXTURE9	m_pTex_A;
	LPDIRECT3DTEXTURE9	m_pTex_B;
	LPDIRECT3DTEXTURE9	m_pTex_C;
public:
	Rank(	LPDIRECT3DDEVICE9	pD3DDevice,
			LPDIRECT3DTEXTURE9	pTex_S,
			LPDIRECT3DTEXTURE9	pTex_A,
			LPDIRECT3DTEXTURE9	pTex_B,
			LPDIRECT3DTEXTURE9	pTex_C,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect	= NULL,
			wiz::OBJID	id		= OBJID_UI_RANK
	);
	~Rank();
	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	setDrawing( bool i_bDraw, int i_iRank ){
		m_bDrawing	= i_bDraw;

		switch( i_iRank ){
			case	1:
				m_pTexture	= m_pTex_S;
				break;
			case	2:
				m_pTexture	= m_pTex_A;
				break;
			case	3:
				m_pTexture	= m_pTex_B;
				break;
			case	4:
				m_pTexture	= m_pTex_C;
				break;
			default	 :
				break;
		};
	}
};

/**************************************************************************
class Factory_Result;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_Result{
public:
/**************************************************************************
 Factory_Result(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Result( FactoryPacket* fpac, int iDeadCount, int iMaxPosY, int iScratchPoint );
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Result();
};

}
//end of namespace bomberobject.
}
//end of namespace wiz.
