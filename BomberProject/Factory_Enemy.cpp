////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Enemy.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�֓��@����
//	�����ް��Ɣ��l	�F���C���t�@�N�g���[
//					��
//	namespace wiz;
//		class Factory_Enemy ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Enemy.h"

#include "BassItems.h"

namespace wiz
{
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
	{
		
		::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
		
	}

/////////////////// ////////////////////
//// �֐���     �FvoidEnemySphere::Draw( LPDIRECT3DDEVICE9 pD3DDevice , vector<Object*>& Vec)
//// �J�e�S��   �F���z�֐�
//// �p�r       �F���̂�`��
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
//// �ߒl       �F�Ȃ�
//// �S����     �F (�R�m��搶�̂ЂȌ`���)
//// ���l       �F
////            �F
////
	void EnemySphere::Draw(DrawPacket& i_DrawPacket)
	{
		multimap<float,EnemyItem*>::iterator it = m_ItemMap_Target.begin();
		while(it != m_ItemMap_Target.end()){
//�e�N�X�`��������ꍇ
			if(m_pTexture){
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
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
				i_DrawPacket.pD3DDevice->SetTexture(0,0);
//�X�e�[�W�����ɖ߂�
				i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}

			else{
//�e�N�X�`�����Ȃ��ꍇ
// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->m_Matrix);
//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(i_DrawPacket);
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
//// ���l       �F
////            �F
////

	void EnemySphere::Update( UpdatePacket& i_UpdatePacket){
		if(m_pCamera == NULL){
			m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
		}

		m_ItemMap_Target.clear();
		multimap<float,EnemyItem*>::iterator it = m_ItemMap_All.begin();
		while(it != m_ItemMap_All.end()){
			if( ( +(it->first - m_pCamera->getEye().y) <= 3000) && ( +(it->first - m_pCamera->getEye().y) >= -3000 ) ){
				
				m_ItemMap_Target.insert(multimap<float,EnemyItem*>::value_type(it->second->m_vPos.y,it->second));
			}

			++it;
		}

		multimap<float,EnemyItem*>::iterator it2 = m_ItemMap_Target.begin();
		while(it2 != m_ItemMap_Target.end()){
//�v�Z��Update��





//�g��k��
			D3DXMATRIX mScale;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale,it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
//��]
			D3DXMATRIX mRot;
			D3DXMatrixIdentity(&mRot);
			D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
//�ړ��p
			D3DXMATRIX mMove;
			D3DXMatrixIdentity(&mMove);
			D3DXMatrixTranslation(&mMove,it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
//�~�b�N�X�s��
			it2->second->m_Matrix = mScale * mRot * mMove;
//�}�e�B���A���ݒ�
			m_Material = it2->second->m_Material;

			++it2;
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
//// ���l       �F
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void EnemySphere::AddEnemy(D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, D3DCOLORVALUE &Diffuse,D3DCOLORVALUE &Specular, D3DCOLORVALUE &Ambient){
		EnemyItem* pItem = new EnemyItem;
		pItem->m_vScale = vScale;
		pItem->m_vPos = vPos;
		::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
		pItem->m_Material.Diffuse = Diffuse;
		pItem->m_Material.Specular = Specular;
		pItem->m_Material.Ambient = Ambient;
//��]�̏�����
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
		m_ItemMap_All.insert(multimap<float, EnemyItem*>::value_type(pItem->m_vPos.y,pItem));	
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
//��n��
		SafeRelease(m_pMesh);
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
			D3DCOLORVALUE EnemyDiffuse = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE EnemySpecular = {1.0f,1.0f,1.0f,1.0f};
			D3DCOLORVALUE EnemyAmbient = {1.0f,1.0f,1.0f,1.0f};
			
//			fpac->m_pVec->push_back(new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,NULL)));
			EnemySphere* Enemy = new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Enemy.jpg"));
			Enemy->AddEnemy(D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),     //�X�P�[��
							D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),     //���N�g
							D3DXVECTOR3( 20.0f, 20.0f, 0.0f ),   //�|�W�V����
							EnemyDiffuse,
							EnemySpecular,
							EnemyAmbient
			);
			fpac->m_pVec->push_back(Enemy);

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
}//end of namespace wiz.