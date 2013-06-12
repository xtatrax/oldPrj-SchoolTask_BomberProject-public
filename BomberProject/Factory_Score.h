#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT_DEAD	= 4;
/**************************************************************************
 class Score : public Sprite;
 �p�r�@�F�����̕`��p�N���X
 �S���ҁF������
****************************************************************************/
class Score : public SpriteObject{
protected:
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iDigit;
	int			m_iScore;
	int			m_DigitArr[MAX_DIGIT_DEAD];
	bool		m_bFirst;
	PlayerCoil*	m_pCoil;
public:
	Score(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				int			iDigit,
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
public:
	ArrivalPos(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~ArrivalPos();

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
