////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Goal.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@��
//	�����ް��Ɣ��l	�F�S�[���t�@�N�g���[
//					��
//	namespace wiz;
//		class GoalObject ;
//		class Factory_Goal ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "Factory_Goal.h"
#include "Factory_Wall.h"
#include "BassItems.h"

namespace wiz{
/**************************************************************************
 FMemoryTex ��`��
****************************************************************************/
/**************************************************************************
 FMemoryTex::FMemoryTex(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F������
***************************************************************************/
FMemoryTex::FMemoryTex( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_pCamera	= NULL;
	m_pCoil		= NULL;
	m_iPtn		= 1;

	LPDIRECT3DVERTEXBUFFER9 pVB = 0;
	CommonMeshVertex* pVer = 0;
	m_pMesh->GetVertexBuffer(&pVB);
	pVB->Lock(0,0,(VOID**)&pVer,0);
	DWORD vsize = m_pMesh->GetNumVertices();
	for(DWORD n = 0;n < vsize;n++){ //���_�̐����擾����
		//�@���ƒ��_����uv�l�𓾂�
		BoxVecNomalUV(pVer[n].vec,pVer[n].normal,pVer[n].tu,pVer[n].tv);
	}
	pVB->Unlock();

}

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////            �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////            �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////            �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////            �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void FMemoryTex::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,mItem*>::iterator it = m_ItemMap_Target.begin();
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &it->second->mMatrix);
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
//// �S����     �F������
//// ���l       �F
////            �F
////
void FMemoryTex::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}

	m_ItemMap_Target.clear();
	multimap<float,mItem*>::iterator it = m_ItemMap_Memory.begin();
	while(it != m_ItemMap_Memory.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,mItem*>::value_type(it->second->vPos.y,it->second));
		}
		++it;
	}

	if( m_pCoil == NULL )
		m_pCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec, typeid(PlayerCoil) ) ;

	multimap<float,mItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){

		if( m_pCoil->getState() == COIL_STATE_CLEAR ){
			OrientGoal( i_UpdatePacket );
		}

		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->vScale.x,it2->second->vScale.y,it2->second->vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->vPos.x,it2->second->vPos.y,it2->second->vPos.z);
		//�~�b�N�X�s��
		it2->second->mMatrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = it2->second->mMaterial;

		++it2;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddDesc( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �FDesc�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F������
//// ���l       �F
void FMemoryTex::AddMemory(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	mItem* pItem = new mItem;
	pItem->vScale = vScale;
	pItem->vPos	= vPos;
    ::ZeroMemory(&pItem->mMaterial,sizeof(D3DMATERIAL9));
	pItem->mMaterial.Diffuse = Diffuse;
	pItem->mMaterial.Specular = Specular;
	pItem->mMaterial.Ambient = Ambient;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));

	m_ItemMap_Memory.insert(multimap<float,mItem*>::value_type(pItem->vPos.y,pItem));

	m_vPos		= vPos;
	m_vScale	= vScale;
}

/****************************************************
�֐����@�Fvoid	OrientGoal(UpdatePacket& i_UpdatePacket)
�J�e�S���F�֐�
�p�r�@�@�F�N���A��v���[���[�𓮂���
�����@�@�F�Ȃ�
�߂�l�@�F�Ȃ�
�S���ҁ@�F������
���l�@�@�F
****************************************************/
void FMemoryTex::OrientGoal(UpdatePacket& i_UpdatePacket){
	//�R�C���̌��݂̏��𓾂�
	D3DXVECTOR3	move		= m_pCoil->getPos();	//�ʒu
	D3DXVECTOR3	scale		= m_pCoil->getScale();	//�傫��
	float		dir			= m_pCoil->getDir();	//�i�s����

	const float	rate		= 0.1f;			//�ړ����鑬��
	const float	ScaleRate	= rate*rate;	//�傫���̕ω���
	const float DirRate		= rate*60;		//�p�x�̕ω���
	const float	OrientPos	= m_vPos.x + (m_vScale.x / 2 - 4);	//�������ׂ��ʒu

	int			dirPtn		= 1;		//�����ׂ��p�x������
	const float	TopDir		= 90.0f;	//������������̂̊p�x
	const float	RightDir	= 0.0f;		//�E�����������̂̊p�x
	const float	LeftDir		= 180.0f;	//�������������̂̊p�x

	const float LeastScale	= 0.3f;	//�ł��k���������̑傫��

	//****************************
	//�傫���̕ύX
	if( scale.x > LeastScale ){
		scale.x	-= ScaleRate;
		scale.z	-= ScaleRate;
	}
	else{
		scale.x	= LeastScale;
		scale.y	= LeastScale;
	}
	//****************************
	//�ʒu�̕ύX
	switch( m_iPtn ){
		case 1:	if( m_vPos.y >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 2;
				break;
		case 2:	if( OrientPos > move.x ){
					move.x	+= rate;
					dirPtn	= 2;	//�E
					if( OrientPos < move.x )
						move.x	= OrientPos;
				}
				else if( OrientPos < move.x ){
					move.x	-= rate;
					dirPtn	= 3;	//��
					if( OrientPos > move.x )
						move.x	= OrientPos;
				}
				else	m_iPtn	= 3;
				break;
		case 3:	if( m_vPos.y + 1.4 >= move.y )
					move.y	+= rate;
				else	m_iPtn	= 4;
				dirPtn	= 1;
				break;
		case 4:	if( m_vPos.x <= move.x ){
					move.x	-= rate;
					dirPtn	 = 3;
				}
				else{
					i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_RESULT;
				}
				break;
	}
	//****************************
	//�p�x�̕ύX
	switch( dirPtn ){
		case 1:	//��
			if( dir > TopDir )
				dir	-= DirRate;
			else if( dir < TopDir )
				dir	+= DirRate;
			break;

		case 2:	//�E
			if( dir > RightDir )
				dir	-= DirRate;
			else if( dir < RightDir )
				dir	+= DirRate;
			break;

		case 3:	//��
			if( dir > LeftDir )
				dir	-= DirRate;
			else if( dir < LeftDir )
				dir	+= DirRate;
			break;
	}
	//**************************************************

	m_pCoil->setPos(move);
	m_pCoil->setScale(scale);
	m_pCoil->setDir(dir);
}

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
,m_pSound( NULL )
,m_bPlaySound( true )
{
	try{
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
GoalObject::~GoalObject(){
	
	m_pCoil = NULL ;
	SafeDeletePointerMap( m_ItemMap_All ) ;


}
/**************************************************************
�֐����@�@�Fvoid GoalObject::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket   //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
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
�֐����@�@�Fvoid GoalObject::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  //�������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
�֐���     �Fvoid	 GoalObject::Update(UpdatePacket& i_UpdatePacket)
�p�r       �F�f�[�^�X�V
********************************************************************/
void	GoalObject::Update(UpdatePacket& i_UpdatePacket)
{
	if( m_pSound == NULL )
		m_pSound = (Sound*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(Sound));

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
			m_pCoil->setState( COIL_STATE_CLEAR );
			if( m_bPlaySound ){
				m_pSound->SearchSoundAndPlay( RCTEXT_SOUND_SE_GOAL );
				m_bPlaySound	= false;
			}
			//i_UpdatePacket.pCommand->m_Command	= GM_OPENSTAGE_RESULT;
		}

		++it;
	}
}

/*******************************************************************
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
        D3DCOLORVALUE MemoryDiffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE MemorySpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MemoryAmbient = {1.0f,1.0f,1.0f,0.0f};

        D3DCOLORVALUE GoalDiffuse = {0.0f,1.0f,1.0f,0.3f};
        D3DCOLORVALUE GoalSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE GoalAmbient = {0.0f,1.0f,1.0f,0.3f};

		FMemoryTex* mt = new FMemoryTex(fpac->pD3DDevice,fpac->m_pTexMgr->addTexture( fpac->pD3DDevice, L"memory.png" ));
		GoalObject* gl = new GoalObject(fpac->pD3DDevice,NULL);
		////������
		//gl->addGoal(	D3DXVECTOR3( 10.0f, 3.0f, 1.0f ),
		//				D3DXVECTOR3( 0.0f, 0.0f, 90.0f ),
		//				D3DXVECTOR3( 20.0f, 20.0f, 0.0f ),
		//				GoalDiffuse,
		//				GoalSpecular,
		//				GoalAmbient);

		mt->AddMemory(	D3DXVECTOR3(20.0f,5.0f,0.0f),
						g_vZero,
						D3DXVECTOR3(20.0f,20.0f * 8.0f-8.0f ,0.0f),
						MemoryDiffuse,
						MemorySpecular,
						MemoryAmbient	);

		fpac->m_pVec->push_back( mt );

		gl->addGoal(	D3DXVECTOR3( 40.0f, 2.0f, 0.0f ),
						g_vZero,
						//D3DXVECTOR3( 20.0f, 20.0f, 0.0f ),
						D3DXVECTOR3( 20.0f, 20.0f * 8.0f-10.0f, 0.0f ),
						GoalDiffuse,
						GoalSpecular,
						GoalAmbient);
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
