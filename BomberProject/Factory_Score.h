#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"
#include "Factory_Goal.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 5;
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
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
				Rect*		Rect	= NULL );
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
 class AnimationScore : public Score;
 �p�r�@�F�A�j���[�V�����X�R�A�`��N���X
 �S���ҁF������
****************************************************************************/
class AnimationScore : public Score{
	int		m_iDrawScore;
	int		m_iResultScore;
	bool	m_bNext;
public:
	AnimationScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iScore,
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
	AnimationScore*		m_pDead;
	AnimationScore*		m_pMaxPos;
	LPDIRECT3DTEXTURE9	m_pDeadTex;
	LPDIRECT3DTEXTURE9	m_pMaxPosTex;
	int					m_iNowDraw;
public:
	ResultScore(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pDeadTex,
				LPDIRECT3DTEXTURE9	pMaxPosTex,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDeadScore,
				int			iMaxPosScore,
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
