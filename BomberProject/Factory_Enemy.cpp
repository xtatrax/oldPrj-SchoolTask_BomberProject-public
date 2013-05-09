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
	EnemySphere::~EnemySphere()
	{
		//��n��
		SafeRelease(m_pMesh);
	}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddWall( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FWall�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F�{�����V
//// ���l       �F
//////////////////////////////////////////////////////////////////////////////////////////////////////
	void EnemySphere::AddEnemy(D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, D3DCOLORVALUE &Diffuse,D3DCOLORVALUE &Specular, D3DCOLORVALUE &Ambient)
	{
		EnemyItem* pItem = new EnemyItem;
		pItem->m_vScale = vScale;
		pItem->m_vPos = vPos;
		::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
		pItem->m_Material.Diffuse = Diffuse;
		pItem->m_Material.Specular = Specular;
		pItem->m_Material.Ambient = Ambient;

	//��]�̏�����
		D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

		m_ItemMap_All.insert(multimap<float, EnemyItem*>::value_type(pItem->m_vPos.y,pItem));	
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
		D3DCOLORVALUE EnemySpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE EnemyAmbient = {1.0f,1.0f,1.0f,1.0f};
		
//		fpac->m_pVec->push_back(new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,NULL)));
		EnemySphere* Enemy = new EnemySphere(fpac->pD3DDevice, EnemyDiffuse, EnemySpecular, EnemyAmbient, fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"Enemy.jpg"));
		Enemy->AddEnemy(D3DXVECTOR3( 0.2f, 0.2f, 0.2f ),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXVECTOR3( 200.0f, 200.0f, 0.0f ),
					  EnemyDiffuse,
					  EnemySpecular,
					  EnemyAmbient);
	
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
}
//end of namespace wiz.