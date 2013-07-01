////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_DeadEffect.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F������
//	�����ް��Ɣ��l	�F���U�G�t�F�N�g
//					��
//	namespace wiz;
//		class DeadEffect ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Coil.h"

namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;
const int PARTICLS_NUM	= 50;
//const int PARTICLS_NUM_ENEMY = 20; 

/**************************************************************************
class DeadEffect;

�p�r�@�F�������̑}��
�S���ҁF������
**************************************************************************/
class DeadEffect : public PrimitiveBox{

	struct EffectItem{
		D3DXVECTOR3		m_vPos	;
		float			m_fDir	;

		EffectItem(){}
		virtual ~EffectItem(){}
	};

	multimap<float,EffectItem*>		m_ItemMap_Target	;	//�`��Ώۂ�WallItem

public:
	/////////////////// ////////////////////
	//// �p�r       �FDescription(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	DeadEffect(LPDIRECT3DDEVICE9	pD3DDevice,
				LPDIRECT3DTEXTURE9	pTexture,
				D3DXVECTOR3			vPos,
				wiz::OBJID id = OBJID_3D_DEADEFFECT
				);

	~DeadEffect();

	void	addEffect( D3DXVECTOR3 vPos,float fDir );
	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid update( int i )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	void	setMatrix(D3DXVECTOR3 vPos);
	void	setPos( D3DXVECTOR3 i_vPos );

	float	getColor(){
		return	m_Material.Ambient.r;
	}
};

/**************************************************************************
class Factory_DeadEffct;

�p�r�@�F���C���H��N���X
�S���ҁF������
****************************************************************************/
class Factory_DeadEffect{
public:
/**************************************************************************
 Factory_DeadEffct(FactoryPacket* fpac);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_DeadEffect(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_DeadEffect();
};

}
}