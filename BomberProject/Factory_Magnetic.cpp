////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Magnetic ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Magnetic.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
class Enemy : public SpriteObject{
	ProvisionalPlayer* pPlayer;
	D3DXVECTOR3 m_vPos ;
public:
	Enemy(
		LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
		D3DXVECTOR3 &vScale,						//	: �L�k
		D3DXVECTOR3 &vRot,							//	: ��]
		D3DXVECTOR3 &vPos,							//	: �ʒu
		RECT* pRect,						 		//	: �`��͈�
		Color color = 0xFFFFFFFF,					//	: �F
		wiz::OBJID id = OBJID_UI_SPRITE				//	: ID
	)
	:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
		pRect,g_vZero,g_vZero,color,id)
	,m_vPos(vPos)
	,pPlayer(NULL)
	{
	}
	void Update(UpdatePacket& i_UpdatePacket){

		if(pPlayer == NULL) pPlayer = (ProvisionalPlayer*)SearchObjectFromID(i_UpdatePacket.pVec , OBJID_3D_PLAYER);
		else{
			
			D3DXVECTOR3 vMove = g_vZero ;
			vMove.x = 1 ;
			D3DXVECTOR3 pPos = this->pPlayer->getPos();
			float degree = TwoPoint2Degree( m_vPos , pPos );	
			ArcMove( vMove, 10.0f, degree);
			//Debugger::DBGSTR::addStr(L"Degree : %f \n" , degree );
			vMove.y *= -1.0f ;
			this->m_vPos += vMove ;
			D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;
		}
	};
};
class EnemyManager : public Object{
	list< Enemy* > m_EnemyList ;
	float Delay ;
public:
	EnemyManager()
		:Object(OBJID_UI_SPRITE)
		,Delay(0)
	{}
	void Update(UpdatePacket& i_UpdatePacket){

		if( ( Delay += i_UpdatePacket.pTime->getElapsedTime() ) >= 0.8f){
			float x = rand() % 1024 ;
			float y = rand() % 800 ;
			m_EnemyList.push_back( 
				new Enemy(
					i_UpdatePacket.pD3DDevice,
					i_UpdatePacket.pTxMgr->addTexture(i_UpdatePacket.pD3DDevice,L"Circle.BMP"),
					g_vOne,
					g_vZero,
					D3DXVECTOR3( x , y ,0.0f),
					NULL,
					0xFFFF0000
				)
			);
			Delay = 0 ;
		}


		list< Enemy* >::iterator  it = m_EnemyList.begin() ;
		list< Enemy* >::iterator end = m_EnemyList.end()   ;

		for(  ; it != end ; it++ ){
			(*it)->Update( i_UpdatePacket );
		}


	}
	~EnemyManager(){
		SafeDeletePointerContainer(m_EnemyList);
	}
	virtual void Draw(DrawPacket& i_DrawPacket){
		list< Enemy* >::iterator  it = m_EnemyList.begin() ;
		list< Enemy* >::iterator end = m_EnemyList.end()   ;

		for(  ; it != end ; it++ ){
			(*it)->Draw( i_DrawPacket );
		}

	};


};


	
/**************************************************************************
 Factory_Magnetic ��`��
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Magnetic::Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 TextureManager& TexMgr){
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
//end of namespace wiz.
