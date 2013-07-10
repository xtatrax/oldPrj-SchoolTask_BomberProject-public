////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���Α���
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#pragma once


namespace wiz{
namespace bomberobject{

//**************************************************************************//
// class MagneticObject : public PrimitiveCylinder ;
//
// �S����  : ���� �O
// �p�r    : ���E�I�u�W�F�N�g
//         : �R�C���I�u�W�F�N�g�⃆�[�U�[�ݒu���E�ɂ����p���Ă��܂��
//**************************************************************************//
extern class PlayerCoil ;
class MagneticObject {
//////////
//	: ����J
private:
	//	: ���Ƀt���O
	//	: S�� = POLE_S
	//	: N�� = POLE_N
	POLE			m_bMagnetPole		;
	float			m_fMagneticum		;
	D3DMATERIAL9	m_PoleMaterial		;
//////////
//	: �v���e�N�g
protected:
	void setPoleS(){ m_bMagnetPole = POLE_S  ; setColorS() ; }
	void setPoleN(){ m_bMagnetPole = POLE_N	 ; setColorN() ; }
	void setPole( POLE bPool ){
		     if( bPool == POLE_N ) setPoleN() ;
		else if( bPool == POLE_S ) setPoleS() ;
	}
	
	void setColorS(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 1.0f ; m_PoleMaterial.Ambient.g = 0.0f ; m_PoleMaterial.Ambient.r = 0.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ; 
	}
	void setColorN(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 0.0f ; m_PoleMaterial.Ambient.g = 0.0f ; m_PoleMaterial.Ambient.r = 1.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ;	
	}
	void setColorSuper(){
		m_PoleMaterial.Ambient.a = 1.0f ; m_PoleMaterial.Ambient.b = 0.0f ; m_PoleMaterial.Ambient.g = 1.0f ; m_PoleMaterial.Ambient.r = 1.0f ;
		m_PoleMaterial.Diffuse.a = 1.0f ; m_PoleMaterial.Diffuse.b = 1.0f ; m_PoleMaterial.Diffuse.g = 1.0f ; m_PoleMaterial.Diffuse.r = 1.0f ;			
	}

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
	/////////////////// ////////////////////
	//// �p�r       �FMagneticObject() ;
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �F
	//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
	////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
	//// �ߒl       �F�Ȃ�
	//// �S����     �F�g�n ��m
	//// ���l       �F
	////	
	MagneticObject() ;


	/////////////////// ////////////////////
	//// �p�r       �F  ~MagneticObject()
	//// �J�e�S��   �F�R���X�g���N�^
	//// �p�r       �FPlayer�p�̃R���X�g���N�^
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S����     �F���� �O
	//// ���l       �F
	////	
	~MagneticObject();

	/////////////////// ////////////////////
	//// �֐���     �Fvoid ChangePole()
	//// �J�e�S��   �F�Q�b�^�[
	//// �p�r       �F���ɂ��l��
	//// ����       �F�Ȃ�
	//// �ߒl       �F�Ȃ�
	//// �S��       �F�g�n��m
	//// ���l       �F S�� = POLE_S = false
	////			 �F N�� = POLE_N = true
	POLE  getMagnetPole() const { return m_bMagnetPole	;	}	;

	float getMagneticum() const { return m_fMagneticum*m_fMagneticum  ;	}	;
	D3DMATERIAL9 getMaterial(){
		return m_PoleMaterial ;
	}
};



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
//end of namespace bomberobject.
}
//end of namespace wiz.
