////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_CheckPoint.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�� ���V
//	����            �F���� ��
//	����            �F���� �O
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
#include "Factory_Score.h"
//	: �C���N���[�h
//////////
namespace wiz{
namespace bomberobject{

const	int		DRAWING_NUMBER	= 26;
const	float	EFFECT_SIZE		= 5.0f;
//************************************************//
//class RestartPoint :public Box
//
// �S����  : ���� �O
// �ړI    : STL��O����h�������N���X
//************************************************//
class RestartPoint :public Box{
	float m_fSize ;
public:
	RestartPoint(
		const LPDIRECT3DDEVICE9	pD3DDevice	,
		const LPTATRATEXTURE	pPointTex
	);
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
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );
	/////////////////// ////////////////////
	//// �p�r       �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�������z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O �{�����V(�ҏW)
	//// ���l       �F
	////            �F
	////
	void Draw( DrawPacket& i_DrawPacket );


	void ChangePoint( D3DXVECTOR3& i_vNewPos ){
		m_BasePos	= i_vNewPos	;
		m_BasePos.z = 0.01f		;
		m_fSize		= 0.0f		;
	}
};

//************************************************//
//class CheckPoint : public Box
//
// �S����  : ���� �O
// ���p��  : �{�� ���V
// ����    : ���� ��
// ����    : ���� �O
// �ړI    : STL��O����h�������N���X
//************************************************//
class CheckPoint : public Box{
protected:
	//	: �U�镑���̏��
	enum BEHAVIORSTATE{
		BEHAVIORSTATE_WAIT		,
		BEHAVIORSTATE_REDUCTION	,
		BEHAVIORSTATE_LAST		,
	};
	//	: �d���̏��
	enum WORKSTATE{
		WORKSTATE_UNFINSHED		,
		WORKSTATE_COMPLETION	,
	};
	struct ITEM{
		float			fPosY		;
		DWORD			dwThisPoint	;
		D3DXVECTOR3		vStartPos	;
		ITEM(D3DXVECTOR3 i_vPos, DWORD dwPoint)
			:fPosY( i_vPos.y ),vStartPos(i_vPos)
		{}
	};
	D3DXVECTOR3				m_vLineScale		;
	D3DXVECTOR3				m_vStringScale		;
	typedef vector< ITEM* > ITEMCONTAINER		;
	LPTATRATEXTURE			m_pTxLine			;
	LPTATRATEXTURE			m_pTxCheckString	;
	LPTATRATEXTURE			m_pTxLastString		;
	ITEMCONTAINER			m_ItemContainer		;	//	: �`�F�b�N�|�C���g���i�[���Ă���z��
	size_t					m_ActiveItem		;	//	: ���̃`�F�b�N�|�C���g
	BEHAVIORSTATE			m_enumNowState		;	//	: ���݂̏��
	float					m_fBassLength		;	//	: �`�F�b�N�|�C���g�o�[�̌��̒���
	float					m_fReductionTime	;	//	: �k�����鑬��
	Camera*					m_pCamera			;	//	: 
	PlayerCoil*				m_pCoil				;	//	: �ʉ߂��m�F���邽�߂Ƀ|�C���^�[��ێ�
	TimeScore*				m_pTime				;	//	: ���Ԃ����Z�b�g���邽�߃|�C���^�[��ێ�
	RestartPoint*			m_pRestartPoint		;	//	: ���X�^�[�g�|�C���g

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
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F
	////            �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	CheckPoint( LPDIRECT3DDEVICE9 pD3DDevice,
				float			fLength,
				LPTATRATEXTURE	pLineTex				,
				LPTATRATEXTURE	pCheckPointStringTex	,
				LPTATRATEXTURE	pLastStingTex			,
				wiz::OBJID		id = OBJID_SYS_CHECKPOINT );
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F
	//// ����       �F
	////            �F
	//// �ߒl       �F
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
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
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�p���������̂ł��K���Ƃ���`�����Ȃ��Ă��ǂ�
	////            �F
	////
    virtual void Update( UpdatePacket& i_UpdatePacket );

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
	void PlayerPass(UpdatePacket& i_UpdatePacket);

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
	WORKSTATE Reduction(UpdatePacket& i_UpdatePacket);

	/////////////////// ////////////////////
	//// �֐���     �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �p�r       �F
	//// �J�e�S��   �F�������z�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket						// ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice				// IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////            �F  �� vector<Object*>&    Vec						// �I�u�W�F�N�g�̔z��
	////            �F  �� Tempus2*            i_DrawPacket.GetTime()	// ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////            �F  �� Command             i_DrawPacket.pCommand	// �R�}���h
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F�p��������͉̂��ꂩ�̃��x���ŕK����`�����邱�ơ
	////            �F
	////
    virtual void Draw( DrawPacket& i_DrawPacket ) ;

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
	void DrawLine( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �֐���     �Fvirtual void Draw( DrawPacket& i_DrawPacket )
	//// �p�r       �F
	//// �J�e�S��   �F�����o�֐�
	//// �p�r       �F�`�F�b�N�|�C���g��ǉ�
	//// ����       �F
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////            �F
	////
	void add(D3DXVECTOR3 i_vPos){
		//m_vPos	= i_vPos;
		m_ItemContainer.push_back( new ITEM( i_vPos , m_ItemContainer.size() +1) );
	}

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F�����o�֐�
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	D3DXVECTOR3 getThisPosition(DWORD Point){
		//	: 
		if( m_ItemContainer.size() < Point ) Point = m_ItemContainer.size()-1 ;
		//m_ActiveItem = Point ;
		return m_ItemContainer[Point]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F�����o�֐�
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	D3DXVECTOR3 getLastPosition(){
		return m_ItemContainer[m_ItemContainer.size()-1]->vStartPos ;
	};

	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F�����o�֐�
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
	/////////////////// ////////////////////
	//// �֐���     �F
	//// �p�r       �F�����o�֐�
	//// �J�e�S��   �F
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F
	//// �S����     �F
	//// ���l       �F
	////            �F
	////
	bool ActiveIsLast(){
		return m_ActiveItem >= m_ItemContainer.size()-1;
	}

	void	EffectCreate(LPDIRECT3DDEVICE9 pD3DDevice);
	void	setTexPos( size_t i_ActiveItem, float fTexPosY );
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
