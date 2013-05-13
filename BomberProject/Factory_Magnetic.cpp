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
Camera*		MagneticumObject3D::m_pCamera = NULL;	

/**************************************************************************
 MagneticumObject ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
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
MagneticumObject::MagneticumObject(
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
,m_vPos( vPos )
,m_vScale( vScale )
,m_bMagnetPole( POLE_S )
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
void MagneticumObject::Update( UpdatePacket& i_UpdatePacket ){

};



//3D�ϊ��p
/**************************************************************************
 MagneticumObject3D ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagneticumObject3D( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F�g�n ��m
//// ���l       �F
////            �F
////
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
	wiz::OBJID id 								//	: ID
)
:PrimitiveCylinder(
				   pD3DDevice,
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   id,
				   pTexture)
,m_bMagnetPole( POLE_S )
,m_fMagneticum(MGPRM_MAGNETICUM_QUAD)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	m_pMagneticField	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 8.0f,8.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
	m_pMagneticField2	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 3.0f,3.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
	m_pMagneticField3	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 1.5f,1.5f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
}

/////////////////// ////////////////////
//// �p�r       �FMagneticumObject3D(
////									LPDIRECT3DDEVICE9 pD3DDevice,LPDIRECT3DTEXTURE9 pTexture,
////									float Radius1,float Radius2,float Lenght,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
////									D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
////									wiz::OBJID id = OBJID_3D_MAGNET) ;
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FPlayer�p�̃R���X�g���N�^
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
////			  :   LPDIRECT3DTEXTURE9 pTexture,  //�e�N�X�`��	
////		      :   Radius1						//�~�̒��a1
////		      :   Radius2						//�~�̒��a2
////			  :   Lenght						//����
////		      :   D3DXVECTOR3 &vRot				//��]�p
////		      :   D3DXVECTOR3 &vPos				//�ʒu
////              :   D3DCOLORVALUE& Diffuse,		//�f�B�t���[�Y�F
////              :   D3DCOLORVALUE& Specular,		//�X�y�L�����F
////              :   D3DCOLORVALUE& Ambient,		//�A���r�G���g�F
////              :   wiz::OBJID id = OBJID_3D_MAGNET //ID
//// �ߒl       �F����
//// �S����     �F�{�����V
//// ���l       �F
////	
MagneticumObject3D::MagneticumObject3D(
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPDIRECT3DTEXTURE9 pTexture,
	float Radius1,
	float Radius2,
	float Lenght,
	D3DXVECTOR3 &vRot,
	D3DXVECTOR3 &vPos,
	D3DCOLORVALUE& Diffuse,
	D3DCOLORVALUE& Specular,
	D3DCOLORVALUE& Ambient,
	wiz::OBJID id) 
:PrimitiveCylinder(
		   pD3DDevice,pTexture,
		   Radius1,Radius2,Lenght,
		   vRot,vPos,
		   Diffuse,Specular,Ambient,
		   id)
,m_bMagnetPole( POLE_N )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	m_pMagneticField	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( 4.0f,4.0f,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin);
}

/////////////////// ////////////////////
//// �p�r       �Fvoid Draw( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�I�u�W�F�N�g���f�B�X�v���C�ɕ\������
//// ����       �F  DrawPacket& i_DrawPacket             // ��ʕ`�掞�ɕK�v�ȃf�[�^�Q �����e���L
////			   �F  �� LPDIRECT3DDEVICE9   pD3DDevice              // IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
////			   �F  �� vector<Object*>&    Vec                     // �I�u�W�F�N�g�̔z��
////			   �F  �� Tempus2*            i_DrawPacket.pTime	   // ���Ԃ��Ǘ�����N���X�ւ̃|�C���^�[
////               �F  �� Command             i_DrawPacket.pCommand   // �R�}���h
//// �ߒl       �F����
//// �S����     �F�g�n ��m
//// ���l       �F
void MagneticumObject3D::Draw(DrawPacket& i_DrawPacket)
{
	multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_Target.begin();
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
		m_pMagneticField->Draw(i_DrawPacket);
		m_pMagneticField2->Draw(i_DrawPacket);
		m_pMagneticField3->Draw(i_DrawPacket);

		++it;
	}
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
void MagneticumObject3D::Update( UpdatePacket& i_UpdatePacket ){
	if(m_pCamera == NULL){
		m_pCamera = (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA);
	}
	m_ItemMap_Target.clear();
	multimap<float,Magnet3DItem*>::iterator it = m_ItemMap_All.begin();
	while(it != m_ItemMap_All.end()){
		if( ((it->first - m_pCamera->getEye().y) <= 13) && ((it->first - m_pCamera->getEye().y) >= -13) /*&&
			((it->first - m_pCamera->getEye().x) <= 15) && ((it->first - m_pCamera->getEye().x) >= -15)*/ ){
			m_ItemMap_Target.insert(multimap<float,Magnet3DItem*>::value_type(it->second->m_vPos.y,it->second));
		}
		++it;
	}
	multimap<float,Magnet3DItem*>::iterator it2 = m_ItemMap_Target.begin();
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

		//m_pMagneticField->Update(i_UpdatePacket);
		
		++it2;
	}
}

/////////////////// ////////////////////
//// �p�r       �Fvoid AddMagnetic( DrawPacket& i_DrawPacket )
//// �J�e�S��   �F�֐�
//// �p�r       �F�}�O�l�b�g�̒ǉ�
//// ����       �F  LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
////		    �F  D3DXVECTOR3 &vScale				//�g��k��
////		    �F  D3DXVECTOR3 &vRot				//��]�p
////		    �F  D3DXVECTOR3 &vPos				//�ʒu
////            �F  D3DCOLORVALUE& Diffuse,			//�f�B�t���[�Y�F
////            �F  D3DCOLORVALUE& Specular,		//�X�y�L�����F
////            �F  D3DCOLORVALUE& Ambient,			//�A���r�G���g�F
//// �ߒl       �F����
//// �S����     �F�g�n ��m
//// ���l       �F
void MagneticumObject3D::AddMagnetic(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem = new Magnet3DItem ;
	pItem->m_vScale = vScale ;
	pItem->m_vPos	= vPos ;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9)) ;
	pItem->m_Material.Diffuse  = Diffuse ;
	pItem->m_Material.Specular = Specular ;
	pItem->m_Material.Ambient  = Ambient ;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z)) ;

	m_ItemMap_All.insert(multimap<float,Magnet3DItem*>::value_type(pItem->m_vPos.y,pItem));	
}


/**************************************************************************
 Factory_Magnetic ��`��
****************************************************************************/
/**************************************************************************
 Factory_Magnetic::Factory_Magnetic(
	Factory_Magnetic *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
//Factory_Magnetic::Factory_Magnetic(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
//					 TextureManager& TexMgr){
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
		// �V�����_�[�I�u�W�F�N�g�̃}�e���A��
		D3DCOLORVALUE MagnetDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		D3DCOLORVALUE MagnetSpecular = { 0.0f, 0.0f, 0.0f, 0.0f } ;
		D3DCOLORVALUE MagnetAmbient  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		// ���E�̕\��
		MagneticumObject3D* Magnet = new MagneticumObject3D(
			fpac->pD3DDevice,
			NULL//fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"ddn.jpg")
		);
		fpac->m_pVec->push_back(Magnet);

		//Magnet->AddMagnetic(D3DXVECTOR3(10.0f,10.0f,0.5f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(10.0f,10.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(1.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(2.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(3.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(4.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(5.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(6.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(7.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(8.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(9.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(10.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(11.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(12.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(13.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(14.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(15.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(16.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(17.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(18.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(19.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(20.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(21.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(22.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(23.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(24.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(25.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(26.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(27.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(28.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(29.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(31.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(32.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(33.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(34.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(35.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(36.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(37.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(38.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(39.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);
		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(40.0f,0.0f,0.0f),
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);

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
