#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Goal.h"
#include "Factory_Title.h"
#include "Factory_Result.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 6;
/**************************************************************************
 class Score : public Sprite;
 �p�r�@�F�����̕`��p�N���X
 �S���ҁF������
****************************************************************************/
class Score : public SpriteObject{
protected:
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iScore;
	int			m_DigitArr[MAX_DIGIT];
	bool		m_bFirst;
	bool		m_bTotal;
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect	= NULL,
				wiz::OBJID	id		= OBJID_UI_SCORE
	);
	virtual ~Score();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	update_Matrix( int i );

};

/**************************************************************************
 class DeadScore : public Score;
 �p�r�@�F���S�񐔕`��N���X
 �S���ҁF������
****************************************************************************/
class DeadScore : public Score{
public:
	DeadScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~DeadScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
 class ArrivalPos : public Score;
 �p�r�@�F���B�n�_�`��N���X
 �S���ҁF������
****************************************************************************/
class ArrivalPos : public Score{
	int		m_iMaxPosY;	//�ō����B�_
public:
	ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ArrivalPos();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	//�Q�b�^�[
	int	getMaxPosY(){
		return	m_iMaxPosY;
	}
};

/**************************************************************************
 class ScratchPoint : public Score;
 �p�r�@�F���B�n�_�`��N���X
 �S���ҁF������
****************************************************************************/
class ScratchPoint : public Score{
public:
	ScratchPoint(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ScratchPoint();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

};

/**************************************************************************
 class GoalPos : public Score;
 �p�r�@�F���B�n�_�`��N���X
 �S���ҁF������
****************************************************************************/
class GoalPos : public Score{
	GoalObject*	m_pGoalObject;
public:
	GoalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~GoalPos();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
 class TimeScore : public Score;
 �p�r�@�F���B�n�_�`��N���X
 �S���ҁF������
****************************************************************************/
class TimeScore : public Score{
	int		m_iTime;
	float	m_fElapsedTime;
public:
	TimeScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iTime,
				Rect*		Rect	= NULL );
	virtual ~TimeScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	setTime(){
		m_iTime	= LIMIT_TIME;
	}

};

/**************************************************************************
 class AnimationScore : public Score;
 �p�r�@�F�A�j���[�V�����X�R�A�`��N���X
 �S���ҁF������
****************************************************************************/
class AnimationScore : public Score{
	int		m_iDrawScore;		//�`�悷��X�R�A
	int		m_iResultScore;		//�ŏI�I�ȃX�R�A
	bool	m_bNext;			//�A�j���[�V��������X�R�A�����ɐi�߂�
	bool	m_bClickRock;		//
	float	m_fTransRate;
	float	m_fTime;
	int		m_iDight;
public:
	AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				int			iDight,
				bool		bTotal	= false,
				Rect*		Rect	= NULL);
	virtual ~AnimationScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);

	bool	getNext(){
		return	m_bNext;
	}
};

/**************************************************************************
 class ResultScore : public Score;
 �p�r�@�F���U���g�X�R�A�`��N���X
 �S���ҁF������
****************************************************************************/
class ResultScore : public Score{
	Rank*				m_pRank;
	AnimationScore*		m_pMaxPos;		//�ō��ʒu�p�A�j���[�V�����X�R�A�̃|�C���^
	AnimationScore*		m_pScratch;		//
	AnimationScore*		m_pDead;		//���S�񐔗p�A�j���[�V�����X�R�A�̃|�C���^
	AnimationScore*		m_pTotal;		//
	SpriteObject*		m_pRate_10;
	SpriteObject*		m_pRate_30;
	SpriteObject*		m_pRate_1;
	LPDIRECT3DTEXTURE9	m_pDeadTex;		//���S�񐔃X�R�A�̃e�N�X�`��
	LPDIRECT3DTEXTURE9	m_pMaxPosTex;	//�ō��ʒu�X�R�A�̃e�N�X�`��
	LPDIRECT3DTEXTURE9	m_pRate10Tex;	//
	LPDIRECT3DTEXTURE9	m_pRate30Tex;	//
	LPDIRECT3DTEXTURE9	m_pRate1Tex;	//
	int					m_iNowDraw;		//�A�j���[�V�������������X�R�A�̔ԍ�
	Result_Rank			m_ResultRank;
public:
	ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				LPDIRECT3DTEXTURE9	pRate10Tex,
				LPDIRECT3DTEXTURE9	pRate30Tex,
				LPDIRECT3DTEXTURE9	pRate1Tex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
				int			iScratchScore,
				Rect*		rect	= NULL);
	virtual ~ResultScore();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
};

/**************************************************************************
 class Factory_Score;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Score{
public:
/**************************************************************************
 Factory_Score(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Score( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~Factory_Score() ;
};

}
}
