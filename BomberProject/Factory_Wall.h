////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Wall.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�{�� ���V
//	�ҏW			�F�g�n ��m
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class WallObject : public PrimitiveBox 
//		class Factory_Wall ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"
#include "Factory_Player.h"
#include "Factory_Enemy.h"
#include "Factory_Coil.h"
#include "Factory_Sound.h"
#include "Factory_CheckPoint.h"
#include "Factory_DeadEffect.h"
#include "Factory_Continue.h"

namespace wiz{
namespace bomberobject{

extern class PlayerCoil ;
extern class EnemyModel ;

/**************************************************************************
 Warning ��`��
****************************************************************************/
//**************************************************************************//
// class Warning
//
// �S����  : �{�����V
//     
// �p�r    : �G�t�F�N�g
//**************************************************************************//
class Warning : public PrimitiveBox{
	PrimitivePlate m_Plate;
	int	m_iPtn;
	LPDIRECT3DTEXTURE9	m_pTexture	;
	D3DMATERIAL9		m_Material	;
	D3DXMATRIX			m_Matrix	;
	D3DXVECTOR3			m_vPos		;	//	: ���W
	D3DXVECTOR3			m_vRot		;	//	: ��]
	D3DXVECTOR3			m_vScale	;	//	: �L�k
	bool				m_bToDraw	;
public:
	/////////////////// ////////////////////
	//// �p�r       �FWarning(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	Warning(LPDIRECT3DDEVICE9 pD3DDevice,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
			LPDIRECT3DTEXTURE9 pTexture,
			wiz::OBJID id = OBJID_3D_WARNING
			);
	/////////////////// ////////////////////
	//// �p�r       �F~Warning();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	~Warning();
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
	//// �S����     �F�{�����V
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );
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
	//// �S����     �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	void setMatrix(D3DXMATRIX& i_Matrix){
		m_Matrix = i_Matrix;
	}

	void setPos(D3DXVECTOR3& i_Pos){
		m_vPos = i_Pos;
	}
	void setRot(D3DXVECTOR3& i_Rot){
		m_vRot = i_Rot;
	}
	void setScale(D3DXVECTOR3& i_Scale){
		m_vScale = i_Scale;
	}

	void setToDraw(bool i_bFlg){
		m_bToDraw = i_bFlg;
	}
	bool getToDraw(){
		return m_bToDraw;
	}
};



/**************************************************************************
 WallObject ��`��
****************************************************************************/
//**************************************************************************//
// cclass WallObject : public PrimitiveBox
//
// �S����  : �{�����V
//         : �g�n ��m
// �ҏW    : ���� �O
// �p�r    : ��
//**************************************************************************//
class WallObject : public PrimitiveBox{
	int					m_Ptn			;
	PlayerCoil*			m_pPlayerCoil	;
	EnemyModel*			m_pEnemy		;
	Sound*				m_pSound		;
	Camera*				m_pCamera		;
	PrimitivePlate		m_Plate			;
	LPDIRECT3DTEXTURE9	m_pWallTex		;
	Warning*			m_pWarning		;
	struct WallItem{
		D3DMATERIAL9	m_Material	;
		D3DXMATRIX		m_Matrix	;
		OBB				m_Obb		;
		OBB				m_Obb_W		;
		float			m_fMapKey	;
		bool			m_bHidden	;
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		DrawOBB*       m_pDOB		;
		~WallItem(){SafeDelete(m_pDOB);}
#endif
		WallItem(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
		:m_bHidden(true)
		,m_fMapKey(vPos.y)
#if defined(ON_DEBUGGINGPROCESS) | defined( PRESENTATION )
		,m_pDOB()
#endif
		{
			::ZeroMemory(&m_Material,sizeof(D3DMATERIAL9));

			//�Փ˔���p��OBB�̏�����
			D3DXVECTOR3 vOBBScale	= D3DXVECTOR3(vScale.x/4,vScale.y*0.97f,vScale.z),
						vOBBScale_W	= D3DXVECTOR3(vScale.x,vScale.y,vScale.z),
						vOBBRot		= D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian( vRot.z ));
			m_Obb = OBB( vOBBScale, vOBBRot, vPos ) ;
			m_Obb_W = OBB( vOBBScale_W, vOBBRot, vPos ) ;
			D3DXMATRIX mScalse, mRot, mPos;
			D3DXMatrixIdentity(&mScalse);
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixIdentity(&mPos);
			D3DXMatrixScaling(&mScalse,vScale.x,vScale.y,vScale.z);
			D3DXMatrixRotationZ(&mRot,vOBBRot.z);
			D3DXMatrixTranslation(&mPos, vPos.x,vPos.y,vPos.z);
			m_Matrix = mScalse * mRot * mPos ;
			m_Material.Ambient = Ambient ;
			m_Material.Diffuse = Diffuse ;
			m_Material.Specular = Specular ;

		}

	};
	//map<�I�u�W�F�N�g�̃|�W�V����,WallItem>
	typedef multimap<float,WallItem*>	ALLCONTAINER		;
	typedef list<WallItem*>				TARGETCONTAINER		;
	ALLCONTAINER				m_ItemMap_All		;	//�S�Ă�WallItem
	TARGETCONTAINER				m_ItemMap_Target	;	//�`��Ώۂ�WallItem

protected:

	/////////////////// ////////////////////
	//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F�֐�
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	void UpdateTargetItem();

public:
	/////////////////// ////////////////////
	//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �FLPDIRECT3DDEVICE9 pD3DDevice //�f�o�C�X
	////			  : LPDIRECT3DTEXTURE9 pTexture  //�e�N�X�`��
	////			  : pTexture,wiz::OBJID id = OBJID_3D_WALL //ID
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	WallObject(	LPDIRECT3DDEVICE9 pD3DDevice,
				LPDIRECT3DTEXTURE9 pTexture,
				wiz::OBJID id = OBJID_3D_WALL
				);
	/////////////////// ////////////////////
	//// �p�r       �F~WallObject();
	//// �J�e�S��   �F�f�X�g���N�^
	//// �p�r       �F
	//// ����       �F
	//// �ߒl       �F����
	//// �S����     �F���� �O
	//// ���l       �F
	~WallObject();

	bool HitTest2DRectAndCircle( D3DXVECTOR3& i_vPos, float i_fRadius );

	

	///////////////////// ////////////////////
	////// �p�r       �Fvoid GetOBB( size_t Index, OBB& obb )
	////// �J�e�S��   �F�֐�
	////// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	////// ����       �F float Index,
	//////				 OBB& obb			//�擾����OBB
	////// �ߒl       �F�Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
	//////				�����݂�OBB��������
	////// �S����     �F�g�n ��m
	////// ���l       �F
	void GetOBBList( float Index, list<OBB>& ObbList );


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
	//// �S����     �F�{�����V
	//// ���l       �F
	void Draw( DrawPacket& i_DrawPacket );

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
	//// �S����     �F�{�����V
	//// ���l       �F
	////            �F
	////
	void Update( UpdatePacket& i_UpdatePacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid AddWall( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �FWall�̒ǉ�
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	////		    �F  D3DXVECTOR3 &vScale				//�g��k��
	////		    �F  D3DXVECTOR3 &vRot				//��]�p
	////		    �F  D3DXVECTOR3 &vPos				//�ʒu
	////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
	////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
	////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
	//// �ߒl       �F����
	//// �S����     �F�{�����V
	//// ���l       �F
	void AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);


	bool HitTest3DAddWall( MultiBox* pBox, size_t& Index, D3DXVECTOR3& Vec, D3DXVECTOR3& ElsePos );


};

//class WallManager {
//	typedef multimap< float, Wall > WALLCONTAINER ;
//	WALLCONTAINER m_Walls ;
//
//public:
//	WallManager();
//
//};
//

/**************************************************************************
 class Factory_Wall;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Wall{
public:
/**************************************************************************
 Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr			//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Wall(FactoryPacket* fpac);
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~Factory_Wall();
};
}
//end of namespace bomberobject.
}
//end of namespace wiz.
