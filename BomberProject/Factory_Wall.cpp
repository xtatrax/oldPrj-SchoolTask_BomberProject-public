////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Wall.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Wall ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Wall.h"
#include "BassItems.h"

namespace wiz{
PlayerCoil* WallObject::m_pPlayerCoil ;

WallObject::WallObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
	D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos,
	RECT *pRect, Color color , wiz::OBJID id)
	:SpriteObject(pD3DDevice ,pTexture ,vScale ,vRot, vPos, pRect, D3DXVECTOR3(70,180,0), g_vZero, color, id)
	,m_vPos( vPos )
{
}

bool WallObject::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
{
	float fTH = 150 ;
	float fTW =  20 ;
	if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
		abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
		return true ;
	}
	return false ;
}

/**************************************************************************
 Factory_Wall ��`��
****************************************************************************/
/**************************************************************************
 Factory_Wall::Factory_Wall(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Wall::Factory_Wall(FactoryPacket* fpac){
	try{
		fpac->m_pVec->push_back(
			new WallObject(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"biribiriWall.png"),
				D3DXVECTOR3(0.7f,0.7f,1.0f),
				D3DXVECTOR3(0.0f,0.0f,0.0f),
				D3DXVECTOR3(500.0f,300.0f,0.0f),
				NULL
			)
		);
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Wall::~Factory_Wall();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Wall::~Factory_Wall(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
