////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Goal.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject ;
//		class Factory_Goal ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Goal.h"
#include "BassItems.h"

namespace wiz{
/**************************************************************************
 GoalObject ��`��
****************************************************************************/
/***************************************************************************
�֐����@�@�FGoalObject(
                   FactoryPacket* fpac,
                   LPDIRECT3DTEXTURE9 pTexture,
                   wiz::OBJID id
              )
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac           //�f�o�C�X�Ȃ�
�@�@�@�@�@�FLPDIRECT3DTEXTURE9 pTexture   //�e�N�X�`���\
�@�@�@�@�@�Fwiz::OBJID id                 //ID
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
****************************************************************************/
GoalObject::GoalObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
,m_pCoil(NULL)
{
	try{
		//D3DXMatrixIdentity(&m_mMatrix);
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/**************************************************************
�֐����@�@�Fvoid GoalObject::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
<<<<<<< HEAD
�����@�@�@�FDrawPacket &i_DrawPacket   //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
=======
>>>>>>> workspace
***************************************************************/
void	GoalObject::Draw(DrawPacket &i_DrawPacket){
	multimap<float,GoalItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
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

/*******************************************************************
<<<<<<< HEAD
�֐����@�@�Fvoid GoalObject::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
=======
�֐���     �Fvoid	 GoalObject::Update(UpdatePacket& i_UpdatePacket)
�p�r       �F�f�[�^�X�V
>>>>>>> workspace
********************************************************************/
void	GoalObject::Update(UpdatePacket& i_UpdatePacket)
{
	multimap<float,GoalItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it->second->m_vScale.x,it->second->m_vScale.y,it->second->m_vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it->second->m_vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it->second->m_vPos.x,it->second->m_vPos.y,it->second->m_vPos.z);
		//�~�b�N�X�s��
		it->second->m_Matrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = it->second->m_Material;

		//�Փ˔���
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec, typeid(PlayerCoil) ) ;
		if( m_pCoil && m_pCoil->HitTestWall( it->second->m_Obb, 0) ){
			//it->second->m_vPos	= g_vMin;
		}

		++it;
	}
}

/*******************************************************************
<<<<<<< HEAD
�֐����@�@�Fvoid GoalObject::addGoal(
                     D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
                     D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
              )
�J�e�S���@�F�֐�
�p�r�@�@�@�F�S�[���̒ǉ�
�����@�@�@�FD3DXVECTOR3 &vScale
�@�@�@�@�@�FD3DXVECTOR3 &vRot
�@�@�@�@�@�FD3DXVECTOR3 &vPos
�@�@�@�@�@�FD3DCOLORVALUE& Diffuse
�@�@�@�@�@�FD3DCOLORVALUE& Specular
�@�@�@�@�@�FD3DCOLORVALUE& Ambient
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
=======
�֐���     �Fvoid	 GoalObject::addGoal(
						D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
						D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient
					)
�p�r       �F�S�[���̒ǉ�
>>>>>>> workspace
********************************************************************/
void GoalObject::addGoal(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	GoalItem* pItem = new GoalItem;
	pItem->m_vScale = vScale;
	pItem->m_vPos	= vPos;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9));
	pItem->m_Material.Diffuse = Diffuse;
	pItem->m_Material.Specular = Specular;
	pItem->m_Material.Ambient = Ambient;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	//�Փ˔���p��OBB�̏�����
	pItem->m_Obb.m_Center = vPos;
	pItem->m_Obb.m_Size = vScale * 0.5f;
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixRotationYawPitchRoll(&mRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));
	pItem->m_Obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
    pItem->m_Obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
    pItem->m_Obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);

	m_ItemMap_All.insert(multimap<float,GoalItem*>::value_type(pItem->m_vPos.y,pItem));	
}

<<<<<<< HEAD
=======
/*****************************************************************
�֐���	�Fvoid Will::GetOBB( size_t Index, OBB& obb )
�p�r	�F�w��̃C���f�b�N�X�̌��݂�OBB�𓾂�
******************************************************************/
void GoalObject::GetOBBList( float Index, list<OBB>& ObbList ){
    //�w��̔z�u�I�u�W�F�N�g������
	multimap<float,GoalItem*>::iterator itBegin = m_ItemMap_All.lower_bound( 20.0f ) ;
	multimap<float,GoalItem*>::iterator itEnd	= m_ItemMap_All.upper_bound( 20.0f ) ;
	OBB obb ; 
	for(multimap<float,GoalItem*>::iterator iter = itBegin; iter != itEnd; ++iter){
		obb.m_Center  = iter->second->m_vPos + iter->second->m_vPos;
		obb.m_Size	  = m_Size;
		obb.m_Size.x *= iter->second->m_vScale.x;
		obb.m_Size.y *= iter->second->m_vScale.y;
		obb.m_Size.z *= iter->second->m_vScale.z;
		obb.m_Size *= 0.5f;
		//�g�[�^���̉�]�𓾂�
		D3DXQUATERNION Qt = iter->second->m_vRot;
		Qt *= iter->second->m_vRot;
		//�N�I�[�^�j�I���𐳋K��
		D3DXQuaternionNormalize(&Qt,&Qt);
		//�N�I�[�^�j�I�������]�s����쐬
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&Qt);
		obb.m_Rot[0] = D3DXVECTOR3(mRot._11,mRot._12,mRot._13);
	    obb.m_Rot[1] = D3DXVECTOR3(mRot._21,mRot._22,mRot._23);
	    obb.m_Rot[2] = D3DXVECTOR3(mRot._31,mRot._32,mRot._33);
		ObbList.push_back( obb ) ;
	}
}

>>>>>>> workspace
/**************************************************************************
 Factory_Goal ��`��
****************************************************************************/
/**************************************************************************
 Factory_Goal::Factory_Goal(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Goal::Factory_Goal(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE GoalDiffuse = {0.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE GoalSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE GoalAmbient = {0.0f,1.0f,0.0f,1.0f};

		GoalObject* gl = new GoalObject(fpac->pD3DDevice,NULL);
<<<<<<< HEAD
		//gl->addGoal(	D3DXVECTOR3( 10.0f, 3.0f, 1.0f ),
		//				g_vZero,
		//				D3DXVECTOR3( 20.0f, 20.0f, 0.0f ),
		//				GoalDiffuse,
		//				GoalSpecular,
		//				GoalAmbient);
=======
		gl->addGoal(	D3DXVECTOR3( 3.0f, 1.0f, 1.0f ),
						g_vZero,
						D3DXVECTOR3( 35.0f, 20.0f, 0.0f ),
						GoalDiffuse,
						GoalSpecular,
						GoalAmbient);
>>>>>>> workspace

		fpac->m_pVec->push_back(gl);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_Goal::~Factory_Goal();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_Goal::~Factory_Goal(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace wiz.
