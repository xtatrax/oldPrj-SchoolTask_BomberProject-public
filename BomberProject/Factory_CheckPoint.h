////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�� ���V
//	�ҏW			�F���� ��
//	�����ް��Ɣ��l	�F�`�F�b�N�|�C���g
//					��
//	namespace wiz;
//		namespace bomberobject;
//			class CheckEffect         : public PrimitiveBox	;
//			class CheckPoint          : public Cylinder		;
//			class Factory_CheckPoint  ;
//
#pragma once
//////////
//	: �C���N���[�h
#include "Factory_Coil.h"
#include "BassItems.h"
//	: �C���N���[�h
//////////
namespace wiz{
namespace bomberobject{

const	int	DRAWING_NUMBER	= 26;
/**************************************************************************
class CheckEffect;

�p�r�@�F�������̑}��
�S���ҁF������
**************************************************************************/
class CheckEffect : public PrimitiveBox{
	D3DXMATRIX		m_Matrix;
	D3DXVECTOR3		m_vPos ;
	int				m_Num;
	float			m_fWide;
	float			m_fHight;
	bool			m_bMark;
	bool			m_bStart;
	bool			m_bCreating;
	PlayerCoil*		m_pCoil;
	float			m_fPosXArr[DRAWING_NUMBER];
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
	CheckEffect(LPDIRECT3DDEVICE9 pD3DDevice,
				D3DXVECTOR3		vPos,
				float			fLength,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);

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
	void update( int i ,DrawPacket& i_DrawPacket);

/************************************
�֐����@�Fvoid Pos_Update( int i )
�p�r�@�@�F�`��ʒu�̍X�V
�J�e�S���F
�����@�@�Fint i     //�ύX�������G�t�F�N�g�̎w��
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
************************************/
	void Pos_Update( int i );
/*************************************
�֐����@�Fvoid	Reduction()
�p�r�@�@�F�T�C�Y�k��
�J�e�S���F
�����@�@�F
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
	void	Reduction();

/*************************************
�֐����@�Fvoid Expansion()
�p�r�@�@�F�T�C�Y�g��i�g�嗦�͏c�������j
�J�e�S���F
�����@�@�F
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
	void	Expansion();

/*************************************
�֐����@�Fvoid setPosY( float posY )
�p�r�@�@�FY���W�̂ݕύX
�J�e�S���F
�����@�@�Ffloat posY   //�ύX��Y���W
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
*************************************/
	void	setPosY( float posY ){
		m_vPos.y	= posY;
	}

/******************************************
�֐����@�Fvoid setStart( bool i_bStart )
�p�r�@�@�F�A�j���[�V����
�J�e�S���F
�����@�@�Fbool i_bStart    //�A�j���[�V�����J�n�t���O
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
******************************************/
	void	setStart(bool i_bStart){
		m_bStart	= i_bStart;
	}

/******************************************
�֐����@�Fbool setCreating(bool i_bCreating)
�p�r�@�@�F�G�t�F�N�g�̍쐬���ł��邩�ݒ�
�J�e�S���F
�����@�@�Fbool i_bCreating  //�G�t�F�N�g�̍쐬�ł��邩�t���O
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
******************************************/
	void	setCreating(bool i_bCreating){
		m_bCreating	= i_bCreating;
	}

/******************************************
�֐����@�Fbool getStart()
�p�r�@�@�F�A�j���[�V�������Ă��邩
�J�e�S���F
�����@�@�F
�߂�l�@�Fbool�l�@�A�j���[�V�������Ă��邩
�S���ҁ@�F������
���l�@�@�F
******************************************/
	bool	getStart(){
		return	m_bStart;
	}

/******************************************
�֐����@�Fbool getMark()
�p�r�@�@�F���r�J�n�n�_�̕`������Ă��邩
�J�e�S���F
�����@�@�F
�߂�l�@�Fbool�l�@���r�J�n�n�_�̕`������Ă��邩
�S���ҁ@�F������
���l�@�@�F
******************************************/
	bool	getMark(){
		return	m_bMark;
	}
/******************************************
�֐����@�Fbool getCreating()
�p�r�@�@�F�G�t�F�N�g�̍쐬���ł��邩
�J�e�S���F
�����@�@�F
�߂�l�@�Fbool�l�@�G�t�F�N�g�̍쐬���ł��邩
�S���ҁ@�F������
���l�@�@�F
******************************************/
	bool	getCreating(){
		return	m_bCreating;
	}

};

/******************************************************:
******************************************************/
class CheckPoint : public Cylinder{
protected:
	struct ITEM{
		float			fPosY		;
		DWORD			dwThisPoint	;
		D3DXVECTOR3		vStartPos	;
		ITEM(D3DXVECTOR3 i_vPos, DWORD dwPoint)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	typedef vector< ITEM* > ITEMCONTAINER	;
	PrimitiveBox			m_Box			;
	ITEMCONTAINER			m_ItemContainer ;
	size_t					m_ActiveItem    ;
	Camera*					m_pCamera		;
	PlayerCoil*				m_pCoil			;
	CheckEffect*			m_pEffect		;
	CheckEffect*			m_pEffect2		;
	Sound*					m_pSound		;
	D3DCOLORVALUE			m_Color			;
	float					m_Thicken		;
	float					m_Length		;
	LPDIRECT3DTEXTURE9		m_pTexture		;
	D3DXVECTOR3				m_vPos			;
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F
	//// ����       �F
	////            �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void SetTarget();
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F
	//// ����       �F
	////            �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void RemoveTarget();

public:
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice, float fLength,LPDIRECT3DTEXTURE9 pTexture,LPDIRECT3DTEXTURE9 pTexture2, wiz::OBJID id = OBJID_SYS_CHECKPOINT );
	~CheckPoint();
	/////////////////// ////////////////////
	//// �֐���     �Fvirtual void Update( UpdatePacket& i_UpdatePacket )
	//// �p�r       �F
	//// �J�e�S��   �F���z�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////            �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �p�r       �F
	//// �J�e�S��   �F�������z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
	////            �F
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;
	/////////////////// ////////////////////
	//// �֐���     �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F�`�F�b�N�|�C���g��ǉ�
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void add(D3DXVECTOR3 i_vPos){
		m_vPos	= i_vPos;
		m_ItemContainer.push_back( new ITEM( i_vPos , m_ItemContainer.size() +1) );
	}

	/////////////////// ////////////////////
	//// �֐���     �Fvoid Blink()
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F�I�u�W�F�N�g�𖾖ł�����
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F������
	//// ���l       �F
	////            �F
	////
	void	Blink();

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	D3DXVECTOR3 getThisPosition(DWORD Point){
		if( m_ItemContainer.size() < Point ) Point = m_ItemContainer.size() ;
		m_ActiveItem = Point ;
		return m_ItemContainer[Point]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	D3DXVECTOR3 getLastPosition(){
		//if( m_ItemContainer.size() < Point ) Point = m_ItemContainer.size() ;
		//m_ActiveItem = Point ;
		return m_ItemContainer[m_ItemContainer.size()-1]->vStartPos ;
	};
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	size_t getActiveItem(){
		return m_ActiveItem ;
	}
};

/**************************************************************************
 class Factory_CheckPoint;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_CheckPoint{
public:
/**************************************************************************
 Factory_CheckPoint(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_CheckPoint(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_CheckPoint();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
