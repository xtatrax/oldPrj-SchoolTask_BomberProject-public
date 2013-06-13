////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Enemy.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓��@����
//	�����p��		�F�{�����V
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Enemy ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Enemy.h"
#include "Factory_Player.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{

/**************************************************************************
 EnemySphere ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FEnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPDIRECT3DTEXTURE9 pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
////            �F  LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////

//CPP�ł̃R���X�g���N�^�̏������B
EnemySphere::EnemySphere(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
//�p����������Ȋ����ŏ����B�^�͕ϐ������B
	: PrimitiveSphere( pD3DDevice,
					   Diffuse,
					   Specular,
					   Ambient,
					   pTexture)
,m_pCamera( NULL )
,m_pPlayer( NULL )
,m_pCoil( NULL )
,m_pSound( NULL )
,m_bReset( false )

{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
}

/////////////////// ////////////////////
//// �֐���     �FEnemySphere::~EnemySphere();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F���̂�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
EnemySphere::~EnemySphere(){
	m_pCamera	= NULL ;
	m_pPlayer	= NULL ;
	m_pCoil		= NULL ;
	m_pSound	= NULL ;

	SafeDeletePointerMap( m_ItemMap_All );
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();

}

/////////////////// ////////////////////
//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�֐�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
void EnemySphere::UpdateTargetItem(){
	//////////
	//	�ΏۊO�̍폜
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin( ),
								TIMend = m_ItemMap_Target.end( );
	while( TIMit != TIMend ){
		if( (*TIMit)->m_fMapKey <= m_pCamera->getPosY()  -DRAWING_RANGE ||
			(*TIMit)->m_fMapKey >= m_pCamera->getPosY()  +DRAWING_RANGE ){
			(*TIMit)->m_bHidden = true ;
			TIMit = m_ItemMap_Target.erase( TIMit );
			continue;
		}
		TIMit++ ;
	}
	//
	//
	//////////
	if(m_bReset){
		ALLCONTAINER::iterator	it  = m_ItemMap_All.begin(),
								end = m_ItemMap_All.end();
		while(it != end){
			it->second->m_vPos = it->second->m_vStartPos;
			it->second->m_vIsAlive = true;
			it++;
		}
	}
	m_bReset = false;
	
	//////////
	//	�`��Ώۂ̒ǉ�
	//
	ALLCONTAINER::iterator	AIMit  = m_ItemMap_All.lower_bound( m_pCamera->getPosY()  -DRAWING_RANGE ),
							AIMend = m_ItemMap_All.upper_bound( m_pCamera->getPosY()  +DRAWING_RANGE );
	while( AIMit != AIMend ){
		if( AIMit->second->m_bHidden == true ){
			AIMit->second->m_bHidden = false ;
			m_ItemMap_Target.push_back( AIMit->second );
		}
		AIMit++ ;
	}
	//
	//
	//////////
	
}

/////////////////// ////////////////////
//// �֐���     �FvoidEnemySphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���̂�`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F�֓�����
//// �����p��   �F�{�����V
//// ���l       �F
////            �F
////
void EnemySphere::Draw(DrawPacket& i_DrawPacket)
{
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		//�}�e�B���A���ݒ�
		this->m_WorldMatrix = (*it)->m_Matrix   ;	
		this->SetMaterial((*it)->m_Material)	;
		if((*it)->m_vIsAlive){
			//�e�N�X�`��������ꍇ
			if(!m_pTexture){

				DWORD wkdword;
				//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
				i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);

				//�X�e�[�W�̐ݒ�
				i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);

				//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

				//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
				// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_Matrix);

				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
				i_DrawPacket.pD3DDevice->SetTexture(0,0);

				//�X�e�[�W�����ɖ߂�
				i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{

				//�e�N�X�`�����Ȃ��ꍇ
				// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_Matrix);

				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
			}
		}
		//���U
		if( (*it)->m_pDeadEffect[0] != NULL ){
			for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
				(*it)->m_pDeadEffect[i]->Draw( i_DrawPacket );
			}
		}

		++it;
	}
}



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
//// �S����     �F�֓�����
//// �����p��   �F�{�����V
//// ���l       
////            �F
////

void EnemySphere::Update( UpdatePacket& i_UpdatePacket){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);		
	}
	if( !m_pPlayer ){
		m_pPlayer = (ProvisionalPlayer3D*)SearchObjectFromID( i_UpdatePacket.pVec,OBJID_3D_USERMAGNET);
	}
	if( !m_pCoil ){
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID( i_UpdatePacket.pVec,typeid(PlayerCoil));
	}
	if(m_pSound == NULL){
		m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));
	}

	if(m_pCoil->getState() == COIL_STATE_CONTINUE)m_bReset = true;

	UpdateTargetItem();
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		if(m_pPlayer->getDrawing() && m_pCoil->getState() == COIL_STATE_MOVE){
			//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
			D3DXVECTOR3	vTargetDir	= m_pPlayer->getPos() - ((*it)->m_vPos) ;
			//	: �����ƑΏۂ܂ł̋��������߂�
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			float  fLng	= (float)sqrt(dirX + dirY);

			if(fLng <= (float)MGPRM_MAGNETICUM){
				if((*it)->m_bPole != m_pPlayer->getMagnetPole()){
					(*it)->m_vPos += vTargetDir * ENEMY_SPEED;
				}else{
					(*it)->m_vPos -= vTargetDir * ENEMY_SPEED;
				}
			}
		}

		float DeadLine  = (float)TwoPointToBassLength( (*it)->m_vPos, m_pCoil->getPos() ) ;
		if( m_pCoil->getState() == COIL_STATE_MOVE && DeadLine < ENEMY_RADIUS ){
			if(m_pCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE || m_pCoil->getSuperMode() == COIL_STATE_SUPER_READY){
				m_pCoil->setState(COIL_STATE_DEAD);
			}
			if((*it)->m_vIsAlive)m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			(*it)->m_vIsAlive = false;
		}
		
		if(!(*it)->m_vIsAlive && (*it)->m_pDeadEffect[0] == NULL )CreateEffect(i_UpdatePacket,it);
		//���U�G�t�F�N�g
		if( (*it)->m_pDeadEffect[0] != NULL ){
			for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
				(*it)->m_pDeadEffect[i]->Update( i_UpdatePacket );
			}
		}
		if( (*it)->m_pDeadEffect[0] != NULL ){
			if((*it)->m_vIsAlive){
				for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
					SafeDelete( (*it)->m_pDeadEffect[i] );
					continue;
				}
			}
		}

		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,(*it)->m_vScale.x,(*it)->m_vScale.y,(*it)->m_vScale.z);

		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&(*it)->m_vRot);

		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,(*it)->m_vPos.x,(*it)->m_vPos.y,(*it)->m_vPos.z);

		//�~�b�N�X�s��
		(*it)->m_Matrix = mScale * mRot * mMove;

		++it;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddEnemy( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FEnemy�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F�֓�����
//// �����p��   �F�{�����V
//// ���l       �F
//////////////////////////////////////////////////////////////////////////////////////////////////////
void EnemySphere::AddEnemy(
		const D3DXVECTOR3&		vScale		,
		const D3DXVECTOR3&		vRot		,
		const D3DXVECTOR3&		vPos		,
		const D3DCOLORVALUE&	Diffuse		,
		const D3DCOLORVALUE&	Specular	,
		const D3DCOLORVALUE&	Ambient
	)
{

	EnemyItem* pItem = new EnemyItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos = vPos;
	pItem->m_vStartPos = vPos;
	pItem->m_vIsAlive = true;
	//���U�G�t�F�N�g�̃|�C���^
	for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ )pItem->m_pDeadEffect[i] = NULL;
	::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	int	i	= rand()%10;
	if( i < 5 ){
		pItem->m_bPole	= POLE_N;
		pItem->m_Material.Ambient.a = 1.0f ; pItem->m_Material.Ambient.b = 0.0f ; pItem->m_Material.Ambient.g = 0.0f ; pItem->m_Material.Ambient.r = 1.0f ;
		pItem->m_Material.Specular.a = 0.0f ; pItem->m_Material.Specular.b = 0.0f ; pItem->m_Material.Specular.g = 0.0f ; pItem->m_Material.Specular.r = 0.0f ;
		pItem->m_Material.Diffuse.a = 1.0f ; pItem->m_Material.Diffuse.b = 1.0f ; pItem->m_Material.Diffuse.g = 1.0f ; pItem->m_Material.Diffuse.r = 1.0f ;	
	}else{
		pItem->m_bPole	= POLE_S;
		pItem->m_Material.Ambient.a = 1.0f ; pItem->m_Material.Ambient.b = 1.0f ; pItem->m_Material.Ambient.g = 0.0f ; pItem->m_Material.Ambient.r = 0.0f ;
		pItem->m_Material.Specular.a = 0.0f ; pItem->m_Material.Specular.b = 0.0f ; pItem->m_Material.Specular.g = 0.0f ; pItem->m_Material.Specular.r = 0.0f ;
		pItem->m_Material.Diffuse.a = 1.0f ; pItem->m_Material.Diffuse.b = 1.0f ; pItem->m_Material.Diffuse.g = 1.0f ; pItem->m_Material.Diffuse.r = 1.0f ;	
	}

	m_ItemMap_All.insert(ALLCONTAINER::value_type(vPos.y,pItem));	
}

/////////////////// ////////////////////
//// �֐���     �Fvoid	PlayerCoil::CreateEffect( UpdatePacket& i_UpdatePacket );
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S��       �F������
//// ���l       �F
////            �F
////
void	EnemySphere::CreateEffect( UpdatePacket& i_UpdatePacket, TARGETCONTAINER::iterator it ){
	//���U�G�t�F�N�g�̍쐬
	for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
		(*it)->m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.pD3DDevice, (*it)->m_vPos,
			float((360/PARTICLS_NUM_ENEMY) * i), m_pCoil->getDeadText() );
	}
};

/////////////////// ////////////////////
//// �p�r       �Fbool PlayerCoil::HitTestWall( OBB Obb )
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�ǂƂ̏Փ˔���
//// ����       �F  OBB Obb           //  : �����Ώۂ�OBB
//// �ߒl       �F�Փ˂��Ă����true
//// �S����     �F�g�n ��m
//// ���l       �F
void EnemySphere::HitTestWall( OBB Obb ){
	SPHERE sp;
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		sp.m_Center = (*it)->m_vPos;
		sp.m_Radius = ENEMY_RADIUS/2;
		//�ʏ�̏Փ˔���
		D3DXVECTOR3 Vec ;
		if(HitTest::SPHERE_OBB(sp,Obb,Vec)){
			//MessageBox( NULL, L"���������I�I", L"�����蔻��", NULL) ;
			if(m_pSound && (*it)->m_vIsAlive)m_pSound->SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			(*it)->m_vIsAlive = false;
		}
		it++;
	}
}

/**************************************************************************
 Factory_Enemy ��`��
****************************************************************************/
/**************************************************************************
 Factory_Enemy::Factory_Enemy(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Enemy::Factory_Enemy(FactoryPacket* fpac){
	try{
		//D3DCOLORVALUE EnemyDiffuse = {1.0f,1.0f,1.0f,1.0f};
		//D3DCOLORVALUE EnemySpecular = {1.0f,1.0f,1.0f,1.0f};
		//D3DCOLORVALUE EnemyAmbient = {1.0f,1.0f,1.0f,1.0f};
		//
		//			fpac->m_pVec->push_back(new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,NULL)));
		//EnemySphere* Enemy = new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Enemy.jpg"));
		//for(int i = 0; i < 3; i++){
		//	for(int j = 0; j < 3; j++){
		//		Enemy->AddEnemy(D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),     //�X�P�[��
		//						D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),     //�p�x
		//						D3DXVECTOR3((float(i)*5.0f+float(rand()%100*0.3f))+1.5f,
		//									(float(j)*2.75f+float(rand()%100*0.2f))+1.5f,0.0f),   //�|�W�V����
		//						EnemyDiffuse,
		//						EnemySpecular,
		//						EnemyAmbient
		//		);
		//	}
		//}
		//fpac->m_pVec->push_back(Enemy);

	}
	catch(...){
		//��throw
		throw;
	}
}

/**************************************************************************
 Factory_Enemy::~Factory_Enemy();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Factory_Enemy::~Factory_Enemy(){
//�Ȃɂ����Ȃ�
	}
}//end of namespace bomberobject.
}//end of namespace wiz.