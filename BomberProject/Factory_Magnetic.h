////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once

#include "StdAfx.h"
#include "Object.h"
#include "BassItems.h"

#define  POLE_S true		/* S�� */
#define  POLE_N false		/* N�� */


namespace wiz{

//**************************************************************************//
// class MagneticumObject : public SpriteObject ;
//
// �S����  : ���� �O
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
class MagneticumObject : public SpriteObject{

//////////
//	: ����J
private:
	//	: ���Ƀt���O
	//	: S�� = POLE_S
	//	: N�� = POLE_N
	bool m_bMagnetPole ;

//////////
//	: �v���e�N�g
protected:
	//	: ���W
	D3DXVECTOR3 m_vPos ;
	D3DXVECTOR3 m_vScale ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; m_Color = 0xFF0000FF	; } ;
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	; } ;
/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F����J�A�N�Z�b�T
//// �p�r       �F���ɂ𔽓]������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
////            �F
////
	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: ���J
public:
	MagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
		Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_MAGNET );
	//	: 
	void Update( UpdatePacket& i_UpdatePacket );
/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���ɂ��l��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F S�� = POLE_S = false
////            �F N�� = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
///////////////////// ////////////////////
//// �֐���     �FD3DXVECTOR3 getPos() const { return g_vZero; }
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �FDEAD OR ALIVE
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
	D3DXVECTOR3 getPos() const {
		return m_vPos; 
	}

};




//3D�ϊ��p
//**************************************************************************//
// class MagneticumObject3D : public PrimitiveCylinder ;
//
// �S����  : �g�n ��m
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
class MagneticumObject3D : public PrimitiveCylinder{
	static Camera*	   m_pCamera ;
//////////
//	: ����J
private:
	//	: ���Ƀt���O
	//	: S�� = POLE_S
	//	: N�� = POLE_N
	bool m_bMagnetPole ;
//////////
//	: �v���e�N�g
protected:
	struct Magnet3DItem{
		//	: ���W
		D3DMATERIAL9	m_Material ;
		D3DXMATRIX		m_Matrix ;
		D3DXVECTOR3		m_vScale ;
		D3DXVECTOR3		m_vPos ;
		D3DXQUATERNION	m_vRot ;
		//bool			m_bMagnetPole ;
		virtual ~Magnet3DItem(){}
	};

	//map<�I�u�W�F�N�g�̃|�W�V����, Magnet3DItem>
	multimap<float, Magnet3DItem*> m_ItemMap_All ;
	multimap<float, Magnet3DItem*> m_ItemMap_Target ;

	D3DXVECTOR3			m_vPos ;

	void setPoleS(){ m_bMagnetPole = POLE_S  ; 
	m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 0.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 1.0f ;
	m_Material.Ambient.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;} ;
	void setPoleN(){ m_bMagnetPole = POLE_N	 ;
	m_Material.Ambient.a = 1.0f ; m_Material.Ambient.b = 1.0f ; m_Material.Ambient.g = 0.0f ; m_Material.Ambient.r = 0.0f ;
	m_Material.Ambient.a = 1.0f ; m_Material.Diffuse.b = 1.0f ; m_Material.Ambient.g = 1.0f ; m_Material.Ambient.r = 1.0f ;} ;


/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F����J�A�N�Z�b�T
//// �p�r       �F���ɂ𔽓]������
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
////            �F
////

	bool ChangePole(){
		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
		else							{ setPoleS() ; }
		return true ;
	}

//////////
//	: ���J
public:
	MagneticumObject3D(
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPDIRECT3DTEXTURE9 pTexture,
		wiz::OBJID id = OBJID_3D_MAGNET
		) ;

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
	//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
	////			 �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////             �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
	////             �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////             �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////
	void Draw( DrawPacket& i_DrawPacket );

	/////////////////// ////////////////////
	//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
	//// �J�e�S��   �F�֐�
	//// �p�r       �F�I�u�W�F�N�g���X�V
	//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
	////			  �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	////              �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
	////              �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
	////              �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
	////              �F  ��       Command            pCommand        // �R�}���h
	//// �ߒl       �F����
	//// �S����     �F�g�n ��m
	//// ���l       �F
	void Update( UpdatePacket& i_UpdatePacket );


/////////////////// ////////////////////
//// �֐���     �FD3DXVECTOR3 getPos() const
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���S���W���l��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;

/////////////////// ////////////////////
//// �֐���     �Fvoid ChangePole()
//// �J�e�S��   �F�Q�b�^�[
//// �p�r       �F���ɂ��l��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S��       �F�g�n��m
//// ���l       �F S�� = POLE_S = false
////			 �F N�� = POLE_N = true
	bool getMagnetPole() const { return m_bMagnetPole	;	}	;

/////////////////// ////////////////////
//// �p�r       �Fvoid AddMagnetic( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�}�O�l�b�g�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F�g�n ��m
//// ���l       �F
////
	void AddMagnetic(
		D3DXVECTOR3 &vScale,
		D3DXVECTOR3 &vRot,
		D3DXVECTOR3 &vPos,
		D3DCOLORVALUE& Diffuse,
		D3DCOLORVALUE& Speular,
		D3DCOLORVALUE& Ambient
		) ;

};


//// 3D�ϊ��p
////**************************************************************************//
//// class MagneticumObject3D : public PrimitiveCylinder ;
////
//// �S����  : �g�n ��m
//// �p�r    : ���E�I�u�W�F�N�g
////         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
////**************************************************************************//
//class MagneticumObject3DverT : public PrimitiveCylinder{
////////////
////	: ����J
//private:
//	//	: ���Ƀt���O
//	//	: S�� = POLE_S
//	//	: N�� = POLE_N
//	bool m_bMagnetPole ;
//
////////////
////	: �v���e�N�g
//protected:
//	//	: ���W
//	D3DXVECTOR3 m_vPos ;
//	D3DXVECTOR3 m_vScale ;
//	//Color		m_Color;
//
//	void setPoleS(){ /*m_ = POLE_S  ; m_Color = 0xFF0000FF	;*/ } ;
//	void setPoleN(){ /*m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	;*/ } ;
///////////////////// ////////////////////
////// �֐���     �Fvoid ChangePole()
////// �J�e�S��   �F����J�A�N�Z�b�T
////// �p�r       �F���ɂ𔽓]������
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
//////            �F
//////
//	bool ChangePole(){
//		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
//		else							{ setPoleS() ; }
//		return true ;
//	}
//
////////////
////	: ���J
//public:
//	MagneticumObject3DverT( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
//		wiz::OBJID id = OBJID_2D_PLAYER );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
///////////////////// ////////////////////
////// �֐���     �FD3DXVECTOR3 getPos() const
////// �J�e�S��   �F�Q�b�^�[
////// �p�r       �F���S���W���l��
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F
//////            �F
//	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;
///////////////////// ////////////////////
////// �֐���     �Fvoid ChangePole()
////// �J�e�S��   �F�Q�b�^�[
////// �p�r       �F���ɂ��l��
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F S�� = POLE_S = false
//////            �F N�� = POLE_N = true
//	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
//	
//};


//	void setPoleS(){ /*m_ = POLE_S  ; m_Color = 0xFF0000FF	;*/ } ;
//	void setPoleN(){ /*m_bMagnetPole = POLE_N	 ; m_Color = 0xFFFF0000	;*/ } ;
///////////////////// ////////////////////
////// �֐���     �Fvoid ChangePole()
////// �J�e�S��   �F����J�A�N�Z�b�T
////// �p�r       �F���ɂ𔽓]������
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F ���Ƀt���O�ƃJ���[��ύX����
//////            �F
//////
//	bool ChangePole(){
//		if( m_bMagnetPole == POLE_S )	{ setPoleN() ; }
//		else							{ setPoleS() ; }
//		return true ;
//	}
//
////////////
////	: ���J
//public:
//	MagneticumObject3DverT( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//		D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
//		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
//		wiz::OBJID id = OBJID_3D_MAGNET );
//	//	: 
//	void Update( UpdatePacket& i_UpdatePacket );
///////////////////// ////////////////////
////// �֐���     �FD3DXVECTOR3 getPos() const
////// �J�e�S��   �F�Q�b�^�[
////// �p�r       �F���S���W���l��
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F
//////            �F
//	D3DXVECTOR3 getPos() const { return m_vPos			;	}	;
///////////////////// ////////////////////
////// �֐���     �Fvoid ChangePole()
////// �J�e�S��   �F�Q�b�^�[
////// �p�r       �F���ɂ��l��
////// ����       �F�Ȃ�
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F S�� = POLE_S = false
//////            �F N�� = POLE_N = true
//	bool getMagnetPole() const { return m_bMagnetPole	;	}	;
//	
//};
//

/**************************************************************************
 class Factory_Magnetic;
 �p�r: ���C���H��N���X
****************************************************************************/
class Factory_Magnetic{
public:
/**************************************************************************
 Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	//Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,TextureManager& TexMgr);
	Factory_Magnetic( FactoryPacket* fpac ) ;
/**************************************************************************
 ~MyFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
~Factory_Magnetic() ;
};
}
//end of namespace wiz.
