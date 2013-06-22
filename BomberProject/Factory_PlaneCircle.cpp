////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_PlaneCircle.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F
//					��
//	namespace wiz;
//		namespace bomberobject;
//

//////////
//	: ��{�̃C���N���[�h
#include "StdAfx.h"
#include "Factory_PlaneCircle.h"
//	: ��{�̃C���N���[�h
//////////

//////////
//	: �ǉ��̃C���N���[�h
//	: �ǉ��̃C���N���[�h
//////////



namespace wiz{
namespace bomberobject{


/**************************************************************************
 Factory_PlaneCircle ��`��
****************************************************************************/
/**************************************************************************
 Factory_PlaneCircle::Factory_PlaneCircle(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_PlaneCircle::Factory_PlaneCircle(FactoryPacket* fpac){
		try{

			D3DCOLORVALUE Diffuse = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Specular = {1.0f,0.0f,0.0f,1.0f};
			D3DCOLORVALUE Ambient = {1.0f,0.0f,0.0f,1.0f};
			
			//CheckPoint* pcp ;
			//fpac->m_pVec->push_back(
			//	pcp = new CheckPoint( fpac->pD3DDevice, 100.0f, fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"particle.png" ),)
			//);
			//pcp->add( D3DXVECTOR3(12.0f,45.0f,0.0f) );
			//pcp->add( D3DXVECTOR3(5.0f,120.0f,0.0f) );

		}
		
		catch(...){
			//��throw
			throw;
		}
	}

/**************************************************************************
 Factory_PlaneCircle::~Factory_PlaneCircle();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_PlaneCircle::~Factory_PlaneCircle(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace bomberobject.
}//end of namespace wiz.