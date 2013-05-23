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
//PlayerCoil* WallObject::m_pPlayerCoil = NULL ;
//Camera*		WallObject::m_pCamera = NULL;	

/**************************************************************************
 WallObject ��`��
****************************************************************************/
/**************************************************************************
 WallObject::WallObject(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,	//�e�N�X�`��
	wiz::OBJID id					//�I�u�W�F�N�g�̎��
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 �S���F�{�����V
***************************************************************************/
WallObject::WallObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,wiz::OBJID id)
	:PrimitiveBox(pD3DDevice,
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					D3DCOLORVALUE(),
					id,
					pTexture)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9));
	m_pPlayerCoil = NULL ;
	m_pCamera = NULL;	
}

bool WallObject::HitTest2DRectAndCircle(D3DXVECTOR3& i_vPos, float i_fRadius)
{
	//float fTH = 150 ;
	//float fTW =  20 ;
	//if( abs(m_vPos.x - i_vPos.x) < fTW + i_fRadius &&
	//	abs(m_vPos.y - i_vPos.y) < fTH + i_fRadius ){
	//	return true ;
	//}
	return false ;
}

/////////////////// ////////////////////
//// �p�r       �Fvoid Will::GetOBB( size_t Index, OBB& obb )
//// �J�e�S��   �F�֐�
//// �p�r       �F�w��̃C���f�b�N�X�̌��݂�OBB�𓾂�
//// ����       :		size_t Index,
////					OBB& obb	//�擾����OBB
//// �ߒl       �F�Ȃ��B�C���f�b�N�X���͈͊O�Ȃ��O
////				 �����݂�OBB��������
//// �S����     �F�g�n ��m
//// ���l       �F
void WallObject::GetOBBList( float Index, list<OBB>& ObbList ){
    //�w��̔z�u�I�u�W�F�N�g������
	multimap<float,WallItem*>::iterator itBegin = m_ItemMap_Target.lower_bound( 20.0f ) ;
	multimap<float,WallItem*>::iterator itEnd	= m_ItemMap_Target.upper_bound( 20.0f ) ;
	OBB obb ; 
	for(multimap<float,WallItem*>::iterator iter = itBegin; iter != itEnd; ++iter){
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
//// �S����     �F�{�����V
//// ���l       �F
void WallObject::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,WallItem*>::iterator it = m_ItemMap_Target.begin();
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
#if defined( ON_DEBUGGINGPROCESS )
		if( it->second->m_pDOB ){
			it->second->m_pDOB->Draw(i_DrawPacket);
		}else{
			it->second->m_pDOB = new DrawOBB(i_DrawPacket.pD3DDevice,it->second->m_Obb);
		}
#endif
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
//// �S����     �F�{�����V
//// ���l       �F
////            �F
////
void WallObject::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	if(m_pPlayerCoil == NULL){
		m_pPlayerCoil = (PlayerCoil*)SearchObjectFromTypeID(i_UpdatePacket.pVec,typeid(PlayerCoil));
	}

	m_ItemMap_Target.clear();
	multimap<float,WallItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		if( ( +(it->first - m_pCamera->getEye().y) <= DRAWING_RANGE) && ( +(it->first - m_pCamera->getEye().y) >= -DRAWING_RANGE ) ){
			m_ItemMap_Target.insert(multimap<float,WallItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}

	multimap<float,WallItem*>::iterator it2 = m_ItemMap_Target.begin();
	while(it2 != m_ItemMap_Target.end()){
		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			it2->second->m_vScale.x,it2->second->m_vScale.y,it2->second->m_vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&it2->second->m_vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			it2->second->m_vPos.x,it2->second->m_vPos.y,it2->second->m_vPos.z);
		//�~�b�N�X�s��
		it2->second->m_Matrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = it2->second->m_Material;

		//�Փ˔���
		//OBB obb	= OBB( it2->second->m_vScale, it2->second->m_vRot, it2->second->m_vPos ) ;
		//if( m_pPlayerCoil ){
		//	m_pPlayerCoil->HitTestWall( obb, 0 ) ;
		//}

		if( m_pPlayerCoil && m_pPlayerCoil->HitTestWall( it2->second->m_Obb, 0 ) ){
			switch(m_pPlayerCoil->getState()){
				case COIL_STATE_MOVE:
					m_pPlayerCoil->setState(COIL_STATE_DEAD);
					break;
				case COIL_STATE_SUPER:
					break;
				default:
					break;
			}
		}


		++it2;
	}
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
////				�g�n ��m
//// ���l       �F
void WallObject::AddWall(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	WallItem* pItem = new WallItem;
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
	pItem->m_Obb = OBB( vScale, pItem->m_vRot, vPos ) ;
	D3DXMATRIX mRot;
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixRotationYawPitchRoll(&mRot,
		D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z));


	m_ItemMap_All.insert(multimap<float,WallItem*>::value_type(pItem->m_vPos.y,pItem));	
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
 		D3DCOLORVALUE WallDiffuse = {0.7f,0.7f,0.7f,1.0f};
		D3DCOLORVALUE WallSpecular = {0.0f,0.0f,0.0f,0.0f};
		D3DCOLORVALUE WallAmbient = {0.5f,0.5f,0.5f,1.0f};




		WallObject* Wall = new WallObject(fpac->pD3DDevice,
			fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"biribiriWall.png"));
		//������
		//Wall->AddWall(D3DXVECTOR3(10.0f,25.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,20.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//�E��
		Wall->AddWall(D3DXVECTOR3(2.0f,26.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,0.0f),
					  D3DXVECTOR3(38.5f,12.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//����
		//Wall->AddWall(D3DXVECTOR3(2.0f,26.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(0.5f,12.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//��������
		//Wall->AddWall(D3DXVECTOR3(40.0f,2.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,24.0f,0.0f),
		//			  WallDiffuse,
		//			  WallSpecular,
		//			  WallAmbient);
		//��
		Wall->AddWall(D3DXVECTOR3(2.0f,40.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(20.0f,0.5f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//�^�񒆏c
		Wall->AddWall(D3DXVECTOR3(2.0f,10.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,0.0f),
					  D3DXVECTOR3(20.0f,6.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//������
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(20.0f,10.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//��
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,120.0f),
					  D3DXVECTOR3(20.0f,20.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		// ��������
		Wall->AddWall(D3DXVECTOR3(2.0f,11.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,90.0f),
					  D3DXVECTOR3(7.0f,14.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		//������
		Wall->AddWall(D3DXVECTOR3(2.0f,20.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,45.0f),
					  D3DXVECTOR3(20.0f,20.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		Wall->AddWall(D3DXVECTOR3(2.0f,5.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,45.0f),
					  D3DXVECTOR3(30.0f,15.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		Wall->AddWall(D3DXVECTOR3(2.0f,4.0f,0.5f),
					  D3DXVECTOR3(0.0f,0.0f,-45.0f),
					  D3DXVECTOR3(20.0f,17.0f,0.0f),
					  WallDiffuse,
					  WallSpecular,
					  WallAmbient);
		fpac->m_pVec->push_back(Wall);
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
