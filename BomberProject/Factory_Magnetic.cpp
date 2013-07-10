////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���Α���
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#include "StdAfx.h"
#include "Factory_Magnetic.h"

namespace wiz{
namespace bomberobject{


/**************************************************************************
 MagneticObject ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagneticObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�g�n ��m
//// ���l       �F
////            �F
////
MagneticObject::MagneticObject()
:m_bMagnetPole( POLE_S )
,m_fMagneticum((float)MGPRM_MAGNETICUM)
{
	::ZeroMemory( &m_PoleMaterial, sizeof(D3DMATERIAL9) ) ;
}
/////////////////// ////////////////////
//// �p�r       �F  ~MagneticObject()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FPlayer�p�̃R���X�g���N�^
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////	
MagneticObject::~MagneticObject(){
	//Debugger::DBGWRITINGLOGTEXT::addStr(L"MagneticObject::~MagneticObject()\n");
}


/**************************************************************************
 Factory_Magnetic ��`��
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	Factory_Magnetic *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Magnetic::~Factory_Magnetic();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Magnetic::~Factory_Magnetic(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
