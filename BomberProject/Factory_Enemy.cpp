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
 EnemyModel ��`��
***************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FEnemyModel::EnemyModel(LPDIRECT3DDEVICE9 pD3DDevice,D3DCOLORVALUE& Diffuse,
////            �F  D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,LPTATRATEXTURE pTexture = 0);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F���̂��쐬
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  D3DCOLORVALUE& Diffuse,         //�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,            //�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,          //�A���r�G���g�F
////            �F  LPTATRATEXTURE pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
//// �ߒl       �F�Ȃ��i���s���͗�O��throw�j
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////

//CPP�ł̃R���X�g���N�^�̏������B
EnemyModel::EnemyModel(  BassPacket& Packet,const char *pFileName ,const wiz::OBJID id)
//�p����������Ȋ����ŏ����B�^�͕ϐ������B
//:SimpleCommonMesh(g_vZero,g_vZero,COLOR2D3DCOLORVALUE(-1),COLOR2D3DCOLORVALUE(-1),COLOR2D3DCOLORVALUE(-1),id )
:Object(id)
,m_pCamera( NULL )
,m_pPlayer( NULL )
,m_pCoil( NULL )
,m_pMesh( NULL )
,m_bReset( false )
{
	try{
		// X�t�@�C�����烁�b�V�������[�h���� 
		//LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
		//DWORD dwMQty;
		LPDIRECT3DDEVICE9 pDevice = Packet.GetDevice();
		if(FAILED(D3DXLoadMeshFromXA(pFileName,
								D3DXMESH_MANAGED,
								pDevice,
								NULL,
								NULL,
								NULL,
								NULL,
								&m_pMesh))){
			string	 buf1 = pFileName ;
			wstring  buf2 ;
			TLIB::widen(buf1,buf2);
			wstring msg  = wstring(L"���f���f�[�^\"") + buf2 + wstring(L"\"��ǂݍ��߂܂���ł���");
			// ���������s
            throw BaseException(
				msg.c_str(),
                L"LoadMeshFromX::LoadMeshFromX()"
            );
        }
		//
		//////////
		//	: �e�N�X�`���������C�h��
		//wstring wsTexName  ;
		//wchar_t* wpTexName = NULL;
		//if(pTexName){
		//	wpTexName = new wchar_t[ strlen(pTexName) +1 ];
		//	size_t ret;
		//	mbstowcs_s(&ret, wpTexName, strlen(pTexName) +1, pTexName, strlen(pTexName) +1);
		//}
		//
		//////////

		//TLIB::widen(sFileDir,wsFileDir);

		//m_pTex = Packet.AddTexture( L"DeadPerticul.png");
		m_pDeadEffect	= new DeadEffect( Packet.GetDevice(), Packet.AddTexture( L"DeadPerticul.png"), g_vOne ); 

		//D3DXMATERIAL d3dxMaterials = *(D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		//m_MaterialItems.init(pD3DDevice,pD3DXMtrlBuffer,dwMQty,TexMgr,g_sDefaultTexturePath.c_str(),wpTexName);
		//m_BassMesh.m_AABB = AABB(m_BassMesh.m_pMesh);
		//delete [] wpTexName;
		//CommonMesh::CreateMeshFormX( pD3DDevice, pFileName, pTexMgr);
		::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
		//ShaderChange( new CookTrance(pD3DDevice) );
	}
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pMesh);
        //�ăX���[
        throw;
    }

}

/////////////////// ////////////////////
//// �֐���     �FEnemyModel::~EnemyModel();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F���̂�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
EnemyModel::~EnemyModel(){
	m_pCamera	= NULL ;
	m_pPlayer	= NULL ;
	m_pCoil		= NULL ;
	SafeDelete( m_pDeadEffect );

	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
		
	m_ItemMap_Target.clear();
	
	SAFE_RELEASE( m_pMesh );
}

/////////////////// ////////////////////
//// �p�r       �FWallObject(	LPDIRECT3DDEVICE9 pD3DDevice,LPTATRATEXTURE pTexture,wiz::OBJID id = OBJID_3D_WALL);
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F�֐�
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
void EnemyModel::UpdateTargetItem(){
	//////////
	//	�ΏۊO�̍폜
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin( ),
								TIMend = m_ItemMap_Target.end( );
	while( TIMit != TIMend ){
		if( (*TIMit)->m_vPos.y <= m_pCamera->getPosY()  -DRAWING_RANGE ||
			(*TIMit)->m_vPos.y >= m_pCamera->getPosY()  +DRAWING_RANGE ){
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
			it->second->m_bIsAlive = true;
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
//// �p�r       �Fvoid Update( UpdatePacket& i_UpdatePacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���X�V
//// ����       �F  UpdatePacket& i_UpdatePacket     // �A�b�v�f�[�g���ɕK�v�ȃf�[�^�Q �����e���L
////            �F  ��       LPDIRECT3DDEVICE9  pD3DDevice      // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  ��       Tempus2*           pTime           // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  ��       vector<Object*>&   Vec,            // �I�u�W�F�N�g�̔z��
////            �F  �� const CONTROLER_STATE*   pCntlState      // �R���g���[���̃X�e�[�^�X
////            �F  ��       Command            pCommand        // �R�}���h
//// �ߒl       �F�Ȃ�
//// �S����     �F�֓�����
//// �����p��   �F�{�����V
//// ���l       
////            �F
////

void EnemyModel::Update( UpdatePacket& i_UpdatePacket){
	if( !m_pCamera )	m_pCamera	=              (Camera*)i_UpdatePacket.SearchObjectFromID(OBJID_SYS_CAMERA	) ;		
	if( !m_pPlayer )	m_pPlayer	= (ProvisionalPlayer3D*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_USERMAGNET	) ;
	if( !m_pCoil )		m_pCoil		=          (PlayerCoil*)i_UpdatePacket.SearchObjectFromID(OBJID_3D_COIL		) ;

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
				float  enemySpeed = 0.0f, SplitLng = MGPRM_MAGNETICUM/3.0f; 
				if(fLng <= SplitLng)			enemySpeed = ENEMY_SPEED_LV3;
				else if(fLng <= SplitLng*2.0f)	enemySpeed = ENEMY_SPEED_LV2;
				else							enemySpeed = ENEMY_SPEED_LV1;
				D3DXVec3Normalize(&vTargetDir,&vTargetDir);
				if((*it)->m_bPole != m_pPlayer->getMagnetPole()){
					(*it)->m_vPos += vTargetDir * enemySpeed;
				}else{
					(*it)->m_vPos -= vTargetDir * enemySpeed;
				}
			}
		}

		float DeadLine  = (float)TwoPointToBassLength( (*it)->m_vPos, m_pCoil->getPos() ) ;
		if( m_pCoil->getState() == COIL_STATE_MOVE && DeadLine < ENEMY_RADIUS && (*it)->m_bIsAlive ){
			if(m_pCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE || m_pCoil->getSuperMode() == COIL_STATE_SUPER_READY){
				m_pCoil->setState(COIL_STATE_DEAD);
			}
			if((*it)->m_bIsAlive)i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			m_pDeadEffect->setPos( (*it)->m_vPos );

			(*it)->m_bIsAlive = false;
		}


		if( !((*it)->m_bIsAlive) ){
	        m_pDeadEffect->Update( i_UpdatePacket );
		}

		//�g��k��
		//D3DXMATRIX mScale;
		//D3DXMatrixIdentity(&mScale);
		//D3DXMatrixScaling(&mScale,(*it)->m_vScale.x,(*it)->m_vScale.y,(*it)->m_vScale.z);

		//(*it)->m_vRot. += D3DXToRadian( 1.0f );
		
		//��]
		(*it)->m_fRotY += D3DXToRadian( 31.0f );
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationY(&mRot,(*it)->m_fRotY);

		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,(*it)->m_vPos.x,(*it)->m_vPos.y,(*it)->m_vPos.z);

		//�~�b�N�X�s��
		(*it)->m_Matrix = /*mScale * */mRot * mMove;

		++it;
	}
}

/////////////////// ////////////////////
//// �֐���     �FvoidEnemyModel::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
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
void EnemyModel::Draw(DrawPacket& i_DrawPacket)
{
	TARGETCONTAINER::iterator it	= m_ItemMap_Target.begin();
	TARGETCONTAINER::iterator end	= m_ItemMap_Target.end();
	while(it != end){
		if((*it)->m_bIsAlive){
			//�}�e�B���A���ݒ�
			this->m_WorldMatrix = (*it)->m_Matrix   ;	
			this->m_Material = ((*it)->m_Material)	;
			//((CookTrance*)this->m_pShader)->Draw(i_DrawPacket,this);

			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.GetDevice()->SetTransform(D3DTS_WORLD, &m_WorldMatrix);


			//�����`�F�b�N
			if((!m_pMesh) || (!i_DrawPacket.GetDevice())){
				throw BaseException(L"�f�o�C�X�����b�V���������ł��B",
				L"CommonMesh::Draw()");
			}
			if(m_Material.Diffuse.a < 1.0f){
				//�����A�����x��1.0�����Ȃ�
				// �A���t�@�����̐ݒ�
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			}
			if(m_Material.Specular.r > 0.0f
				|| m_Material.Specular.g > 0.0f
				|| m_Material.Specular.b > 0.0f)
			{
				//�����A�X�y�L�����[���ݒ肵�Ă�����
				// �X�y�L�����[�L���̐ݒ�
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, 1);
			}

			//ChangeRenderStateArray(i_DrawPacket.GetDevice(),pParam);
			// �}�e���A���������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.GetDevice()->SetMaterial( &m_Material);
			//�`��
			m_pMesh->DrawSubset(0);
			//ChangeRenderStateArray(i_DrawPacket.GetDevice(),pParam);
			if(m_Material.Specular.r > 0.0f
				|| m_Material.Specular.g > 0.0f
				|| m_Material.Specular.b > 0.0f)
			{
				//�����A�X�y�L�����[���ݒ肵�Ă�����
				// �X�y�L�����[�����ɖ߂�
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, 0);
			}
			if(m_Material.Diffuse.a < 1.0f){
				//�����A�����x��1.0�����Ȃ�
				// �A���t�@���������ɖ߂�
				i_DrawPacket.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
			}
		}

		if( !((*it)->m_bIsAlive) )m_pDeadEffect->Draw( i_DrawPacket );
		//���U
		//if( (*it)->m_pDeadEffect[0] != NULL ){
		//	for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
		//		(*it)->m_pDeadEffect[i]->Draw( i_DrawPacket );
		//	}
		//}

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
//// �ߒl       �F�Ȃ�
//// �S����     �F�֓�����
//// �����p��   �F�{�����V
//// ���l       �F
////
void EnemyModel::AddEnemy(
		const D3DXVECTOR3&		vScale		,
		const D3DXVECTOR3&		vRot		,
		const D3DXVECTOR3&		vPos		,
		const D3DCOLORVALUE&	Diffuse		,
		const D3DCOLORVALUE&	Specular	,
		const D3DCOLORVALUE&	Ambient		,
		const POLE				Pole

	)
{

	EnemyItem* pItem = new EnemyItem;
	//pItem->m_vScale = vScale;
	pItem->m_fRotY =0;
	pItem->m_vPos = vPos;
	pItem->m_vStartPos = vPos;
	pItem->m_bIsAlive = true;
	//���U�G�t�F�N�g�̃|�C���^
	//0(m_pD3DDevice,L"DeadPerticul.png",&m_pTex);
	//for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ )pItem->m_pDeadEffect[i] = NULL;
	::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	//��]�̏�����
	//D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	int	i	= rand()%10;
	if( Pole == POLE_N ){
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
void	EnemyModel::CreateEffect( UpdatePacket& i_UpdatePacket, TARGETCONTAINER::iterator it ){
	//���U�G�t�F�N�g�̍쐬
	//for( int i = 0; i < PARTICLS_NUM_ENEMY; i++ ){
	//	(*it)->m_pDeadEffect[i]	= new DeadEffect( i_UpdatePacket.GetDevice(), (*it)->m_vPos,
	//		float((360/PARTICLS_NUM_ENEMY) * i), m_pCoil->getDeadText() );
	//}
};

/////////////////// ////////////////////
//// �p�r       �Fbool PlayerCoil::HitTestWall( OBB Obb )
//// �J�e�S��   �F�����o�֐�
//// �p�r       �F�ǂƂ̏Փ˔���
//// ����       �F  OBB Obb           //  : �����Ώۂ�OBB
//// �ߒl       �F�Փ˂��Ă����true
//// �S����     �F�g�n ��m
//// ���l       �F
void EnemyModel::HitTestWall( OBB Obb, UpdatePacket& i_UpdatePacket ){
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
			if( (*it)->m_bIsAlive){
    			m_pDeadEffect->setPos( (*it)->m_vPos );
			    i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_PLAYERBLOKEN );
			}
			    
			(*it)->m_bIsAlive = false;
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
		//EnemyModel* Enemy = new EnemyModel(
		//	fpac->GetDevice(),
		//	RCTEXT_MODEL_ENEMY,
		//	fpac->m_pTexMgr
		//);
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
		//fpac->AddObject(Enemy);

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