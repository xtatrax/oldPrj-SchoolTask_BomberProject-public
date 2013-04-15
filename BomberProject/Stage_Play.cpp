////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FStick Figures
//	�t�@�C����		�FStage_Pray.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	�����ް��Ɣ��l	�F�v���C�X�e�[�W
//					��
//	namespace wiz;
//		class PlayStage : public Stage ;
//
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stage_Play.h"
#include "stage.h"

namespace wiz{



class ProvisionalPlayer : public SpriteObject{
	D3DXVECTOR3 m_vPos ;
public:
	//	: 
	ProvisionalPlayer(
		LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
		LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
		D3DXVECTOR3 &vScale,						//	: �L�k
		D3DXVECTOR3 &vRot,							//	: ��]
		D3DXVECTOR3 &vPos,							//	: �ʒu
		RECT* pRect,								//	: �`��͈�
		Color color = 0xFFFFFFFF,					//	: �F
		wiz::OBJID id = OBJID_3D_PLAYER				//	: ID
	)
	:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
		pRect,g_vZero,g_vZero,color,id)
	,m_vPos(vPos)
	{
	}

	//	: 
	void Update(UpdatePacket& i_UpdatePacket){
		wiz::CONTROLER_STATE Controller1P = i_UpdatePacket.pCntlState[0] ;
		D3DXVECTOR3 vMove = g_vZero ;
		vMove.x += Controller1P.Gamepad.fThumbLX;
		vMove.y -= Controller1P.Gamepad.fThumbLY;

		this->m_vPos += vMove * 15.0f ;
		
		D3DXMatrixTranslation( &this->m_mMatrix , this->m_vPos.x , this->m_vPos.y , this->m_vPos.z ) ;

	};
	D3DXVECTOR3 getPos() const {return m_vPos;};

};
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
		RECT* pRect,								//	: �`��͈�
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
			float degree = TwoPoint2Degree( m_vPos.x, m_vPos.y, pPos.x, pPos.y );	
			ArcMove( vMove.x , vMove.y , 10.0f, degree);
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
 PlayStage ��`��
****************************************************************************/
/**************************************************************************
 PlayStage(
	LPDIRECT3DDEVICE9 pD3DDevice,		//�f�o�C�X
	const Script::MLPHeader& Header,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	const Script::SCORELEVEL Level		//	: �v���C���郌�x�����
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
PlayStage::PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* pStage)
	:Stage(pStage)

{
	try{

		this->m_Vec.push_back(
			new ProvisionalPlayer(
				pD3DDevice,
				this->m_TexMgr.addTexture(pD3DDevice,L"Circle.BMP"),
				g_vOne,
				g_vZero,
				D3DXVECTOR3(200.0f,100.0f,0.0f),
				NULL
			)
		);
		this->m_Vec.push_back(
			new EnemyManager()
		);
		//m_IsDialog = true;
		//MainFactory(pD3DDevice,m_Vec,m_TexMgr);
		////////////
		////	: �X�e�[�W�̍\�z
		//StageLoader(pD3DDevice, DEFAULT_STAGE_DATA_PATH, 1 , m_Vec, m_TexMgr);
		////m_pChildStage = new PauseMenu(pD3DDevice,this);
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
PlayStage::~PlayStage(){
	
}

}
//end of namespace wiz.
