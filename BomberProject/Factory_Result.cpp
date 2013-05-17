////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Result.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Result ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Result.h"
#include "BassItems.h"

namespace wiz{

/**************************************************************************
 Factory_Result ��`��
****************************************************************************/
/**************************************************************************
 Factory_Result::Factory_Result(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Result::Factory_Result(FactoryPacket* fpac){
	try{

		fpac->m_pVec->push_back(
			new SpriteObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"clear.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3( 200.0f, 200.0f, 0.0f ),
				NULL,
				g_vZero,
				g_vZero,
				0xFFFFFFFF
				)
		);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Result::~Factory_Result();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Result::~Factory_Result(){
    //�Ȃɂ����Ȃ�
}

}


//end of namespace wiz.
