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
	LPTATRATEXTURE	m_pRankTex;
	LPTATRATEXTURE	m_pFrameTex;
	Result_Rank			m_ResultRank;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vRot;
	D3DXVECTOR3			m_vScale;
public:
	Rank(	LPDIRECT3DDEVICE9	pD3DDevice,
			LPTATRATEXTURE	pRankTex,
			LPTATRATEXTURE	pFrameTex,
			D3DXVECTOR3	&vScale,
			D3DXVECTOR3	&vRot,
			D3DXVECTOR3	&vPos,
			Rect*		Rect	= NULL,
			wiz::OBJID	id		= OBJID_UI_RANK
	);
	~Rank();
	void	Draw(DrawPacket& i_DrawPacket);

	void	setDrawing( bool i_bDraw, Result_Rank i_iRank ){
		m_bDrawing		= i_bDraw;
		m_ResultRank	= i_iRank;

	}

	void setRect( Result_Rank i_iRank ){
		switch( i_iRank ){
			case	Rank_S:
				m_pRect->left	= 0;
				m_pRect->top	= 0;
				m_pRect->right	= 128;
				m_pRect->bottom	= 128;
				//m_pRect	= Rect( 0, 0, 128, 128 );
				break;
			case	Rank_A:
				m_pRect->left	= 128;
				m_pRect->top	= 0;
				m_pRect->right	= 256;
				m_pRect->bottom	= 128;
				//m_pRect	= Rect( 128, 0, 256, 128 );
				break;
			case	Rank_B:
				m_pRect->left	= 0;
				m_pRect->top	= 128;
				m_pRect->right	= 128;
				m_pRect->bottom	= 256;
				//m_pRect	= Rect( 0, 128, 128, 256 );
				break;
			case	Rank_C:
				m_pRect->left	= 128;
				m_pRect->top	= 128;
				m_pRect->right	= 256;
				m_pRect->bottom	= 256;
				//m_pRect	= Rect( 128, 128, 256, 256 );
				break;
			default	 :
				m_pRect->left	= 128;
				m_pRect->top	= 128;
				m_pRect->right	= 256;
				m_pRect->bottom	= 256;
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
