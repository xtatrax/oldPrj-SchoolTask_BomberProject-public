#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

	const	int MAX_DIGIT	= 4;
/**************************************************************************
 class DeadCount : public Sprite;
****************************************************************************/
class DeadCount : public SpriteObject{
	D3DXVECTOR3	m_vPos;
	D3DXVECTOR3	m_vScale;
	int			m_iDeadScore;
	int			m_DigitArr[MAX_DIGIT];
	bool		m_bFirst;
	PlayerCoil*	m_pCoil;
public:
	DeadCount(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3	&vScale,
				D3DXVECTOR3	&vPos,
				Rect*		Rect	= NULL );
	virtual ~DeadCount();

	void	Draw(DrawPacket& i_DrawPacket);
	void	Update(UpdatePacket& i_UpdatePacket);
	void	update_Matrix( int i );
};

/**************************************************************************
 class Factory_DeadCount;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_DeadCount{
public:
/**************************************************************************
 Factory_DeadCount(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_DeadCount( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~Factory_DeadCount() ;
};

}
}
