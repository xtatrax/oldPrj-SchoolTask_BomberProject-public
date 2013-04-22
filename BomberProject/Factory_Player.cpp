////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Player.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Player ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{

/**************************************************************************
 ProvisionalPlayer ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FProvisionalPlayer( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
ProvisionalPlayer::ProvisionalPlayer(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
	D3DXVECTOR3 &vScale,						//	: �L�k
	D3DXVECTOR3 &vRot,							//	: ��]
	D3DXVECTOR3 &vPos,							//	: �ʒu
	RECT* pRect,								//	: �`��͈�
	Color color ,								//	: �F
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos(vPos)
{
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
void ProvisionalPlayer::Update( UpdatePacket& i_UpdatePacket ){
	wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
	D3DXVECTOR3 vMove = g_vZero ;
	vMove.x += Controller1P.Gamepad.fThumbLX;
	vMove.y -= Controller1P.Gamepad.fThumbLY;

	this->m_vPos += vMove * 15.0f ;
	
	D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;

};

/**************************************************************************
 PlayerCoil ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FPlayerCoil( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
PlayerCoil::PlayerCoil(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
	D3DXVECTOR3 &vScale,						//	: �L�k
	D3DXVECTOR3 &vRot,							//	: ��]
	D3DXVECTOR3 &vPos,							//	: �ʒu
	RECT* pRect,								//	: �`��͈�
	Color color ,								//	: �F
	wiz::OBJID id 								//	: ID
)
:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
	pRect,g_vZero,g_vZero,color,id)
,m_vPos(vPos)
,m_pPlayer(NULL)
{
}

/////////////////// ////////////////////
//// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
void PlayerCoil::Update( UpdatePacket& i_UpdatePacket ){
	if( m_pPlayer ){


		D3DXVECTOR3 vMove = g_vZero ;
		D3DXVECTOR3 pPos = this->m_pPlayer->getPos();

		float Lng  = TwoPointToBassLength( pPos, m_vPos ) ;
		float Lng2 = VectorLength( D3DXVECTOR3( pPos.x - m_vPos.x, pPos.y - m_vPos.y ,0) );
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", Lng2);
		Debugger::DBGSTR::addStr( L"Lng : %f\n", sqrt(Lng));
		Debugger::DBGSTR::addStr( L"Lng : %d\n", 100*100);
		if( Lng <= 100*100 ){
			vMove.x = 1 ;
			float degree = TwoPoint2Degree( m_vPos, pPos );	
			ArcMove( vMove , 10.0f, degree);

			//vMove.y *= -1.0f ;
			this->m_vPos += vMove ;
			D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
		}

		char atr[] = "������̂߂�ǂ�����";
		this->m_vPos += vMove * 1.0f ;

		D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
	} else {
		m_pPlayer = (ProvisionalPlayer*)SearchObjectFromTypeID( i_UpdatePacket.pVec , typeid(ProvisionalPlayer) );
	}
};

/**************************************************************************
 Factory_Player ��`��
****************************************************************************/
/**************************************************************************
 Factory_Player::Factory_Player(
	FactoryPacket* fpac		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Player::Factory_Player( FactoryPacket* fpac ){
	try{
		fpac->m_pVec->push_back(
			new ProvisionalPlayer(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Circle.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f,100.0f,0.0f),
				NULL,
				0xFFFF0000
			)
		);
		fpac->m_pVec->push_back(
			new PlayerCoil(
				fpac->pD3DDevice,
				fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"Circle.png" ),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f,300.0f,0.0f),
				NULL,
				0xFFFF00000
			)
		);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Player::~Factory_Player();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Player::~Factory_Player(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
