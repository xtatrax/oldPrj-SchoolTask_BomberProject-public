////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Gage.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V(�ҏW)
//	�����ް��Ɣ��l	�F�Q�[�W�t�@�N�g���[
//					��
//	namespace wiz;
//		class Gage;
//		class SuperGage;
//		class MagneticGage_N;
//		class MagneticGage_S;
//		class Factory_Item ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "Factory_Cursor.h"

const	int		SUPER_GAGE_MAX		= 512;
const	int		MAGNETIC_GAGE_MAX	= 256;

namespace wiz{
namespace bomberobject{

/************************************************
class Gage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������ �{�����V(�ҏW)
*************************************************/
class Gage : public SpriteObject{
protected:
	D3DXMATRIX m_mGaugeMatrix;
	Rect	m_BassRect;
	Rect	m_GaugeRect;
	Rect	m_FrameRect;
	float	m_fRate;
	
public:
	Gage(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex		,		//	: �R�A������Texture
		D3DXVECTOR3			&vScale		,		//	: �L�k
		D3DXVECTOR3			&vRot		,		//	: ��]
		D3DXVECTOR3			&vPos		,		//	: �ʒu
		D3DXVECTOR3			&vDirOffset	,		//	: �`��I�t�Z�b�g
		RECT				GaugeRect	,		//	: �`��͈�
		RECT				FrameRect	,		//	: �`��͈�
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);
	~Gage();
	void	Recovery( float fAddValue );	//	: �G�l���M�[�̉�
	void	Consume(  float fSubValue );	//	: �G�l���M�[�̏���
	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
	
	float getRate()const{
		return m_fRate;
	}

	void ResetGauge(){
		m_fRate = 1.0f ;
	}

	//void getGaugeRot_Right(int i_iValue){
	//	m_GaugeRect.right = i_iValue;
	//}
};

/************************************************
class SuperGage : public SpriteObject

�p�r�@�F�X�[�p�[���[�h�p�̃Q�[�W
�S���ҁF������ �{�����V(�ҏW)
*************************************************/
class SuperGage : public Gage{
	D3DXVECTOR3 m_vBassPos;
public:
	SuperGage(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex		,		//	: �R�A������Texture
		D3DXVECTOR3			&vScale		,		//	: �L�k
		D3DXVECTOR3			&vRot		,		//	: ��]
		D3DXVECTOR3			&vPos		,		//	: �ʒu
		RECT				GaugeRect	,		//	: �`��͈�
		RECT				FrameRect	,		//	: �`��͈�
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);

    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_N : public Gage

�p�r�@�FN���E�p�̃Q�[�W
�S���ҁF�{�����V
*************************************************/
class MagneticGage_N : public Gage{
	MouseCursor* m_pCursor ;
public:
	MagneticGage_N(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex		,		//	: �R�A������Texture
		D3DXVECTOR3			&vPos		,		//	: �ʒu
		RECT				GaugeRect	,		//	: �`��͈�
		RECT				FrameRect	,		//	: �`��͈�
		wiz::OBJID			id=OBJID_UI_GAUGE	//	: ID
	);

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
};

/************************************************
class MagneticGage_S : public Gage

�p�r�@�FS���E�p�̃Q�[�W
�S���ҁF�{�����V
*************************************************/
class MagneticGage_S : public Gage{
	MouseCursor*	m_pCursor	;
public:
	MagneticGage_S(
		LPDIRECT3DDEVICE9	pD3DDevice	,		//	: �f�o�C�X
		LPDIRECT3DTEXTURE9	pTex		,		//	: �R�A������Texture
		D3DXVECTOR3			&vPos		,		//	: �ʒu
		RECT				GaugeRect	,		//	: �`��͈�
		RECT				FrameRect	,		//	: �`��͈�
		wiz::OBJID			id = OBJID_UI_GAUGE	//	: ID
	);

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );
    void	Draw(DrawPacket& i_DrawPacket) ;
};

/**************************************************************************
 class Factory_Gage;

 �p�r�@�F���C���H��N���X
 �S���ҁF������ 
****************************************************************************/
class Factory_Gage{
	public:
	/**************************************************************************
	 Factory_Item(FactoryPacket* fpac);
	 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
	 �߂�l: �Ȃ�
	***************************************************************************/
		Factory_Gage(FactoryPacket* fpac);
	/**************************************************************************
	 ~MyFactory();
	 �p�r: �f�X�g���N�^
	 �߂�l: �Ȃ�
	***************************************************************************/
		~Factory_Gage();
	};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
