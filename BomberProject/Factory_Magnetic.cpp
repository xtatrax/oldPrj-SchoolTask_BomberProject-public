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
#include "Factory_Coil.h"
#include "BassItems.h"

namespace wiz{
namespace bomberobject{


///**************************************************************************
// MagneticumObject ��`��
//****************************************************************************/
///////////////////// ////////////////////
////// �֐���     �FMagneticumObject( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
//////            �F    D3DXVECTOR3 &vScale, D3DXVECTOR3 &vRot, D3DXVECTOR3 &vPos, RECT* pRect,
//////            �F    Color color = 0xFFFFFFFF, wiz::OBJID id = OBJID_3D_PLAYER )
////// �J�e�S��   �F�R���X�g���N�^
////// �p�r       �F
////// ����       �F
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F
//////            �F
//////
//MagneticumObject::MagneticumObject(
//	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
//	LPDIRECT3DTEXTURE9 pTexture,				//	: �e�N�X�`���[
//	D3DXVECTOR3 &vScale,						//	: �L�k
//	D3DXVECTOR3 &vRot,							//	: ��]
//	D3DXVECTOR3 &vPos,							//	: �ʒu
//	RECT* pRect,								//	: �`��͈�
//	Color color ,								//	: �F
//	wiz::OBJID id 								//	: ID
//)
//:SpriteObject(pD3DDevice,pTexture,vScale,vRot,vPos,
//	pRect,g_vZero,g_vZero,color,id)
//,m_vPos( vPos )
//,m_vScale( vScale )
//,m_bMagnetPole( POLE_S )
//{
//}
//
///////////////////// ////////////////////
////// �֐���     �Fvoid Update( UpdatePacket& i_UpdatePacket )
////// �J�e�S��   �F
////// �p�r       �F
////// ����       �F
////// �ߒl       �F�Ȃ�
////// �S��       �F���� �O
////// ���l       �F
//////            �F
//////
//void MagneticumObject::Update( UpdatePacket& i_UpdatePacket ){
//
//};
//


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
,m_fMagneticum((float)MGPRM_MAGNETICUM)
,m_pMagneticField( NULL )
,m_pMagneticField2( NULL )
,m_pMagneticField3( NULL )
,m_pMagneticField4( NULL )
,m_pCoil(	NULL )
,m_pCamera(	NULL )
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
	//���E�@�O��
	m_pMagneticField	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( m_fMagneticum,m_fMagneticum,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin,
									false);
	//���E�@�^��
	m_pMagneticField2	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( m_fMagneticum/3*2,m_fMagneticum/3*2,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin,
									false);
	//���E�@����
	m_pMagneticField3	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( m_fMagneticum/3,m_fMagneticum/3,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin,
									false);
	//�G�t�F�N�g�p
	m_pMagneticField4	= new	MagneticField(pD3DDevice,
									NULL,
									D3DXVECTOR3( m_fMagneticum,m_fMagneticum,0.0f ),
									D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 0.0f ),
									g_vMin,
									true);
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
,m_pMagneticField ( NULL )
,m_pMagneticField2( NULL )
,m_pMagneticField3( NULL )
,m_pMagneticField4( NULL )
,m_pCoil(NULL)
,m_pCamera(	NULL )

{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
}
/////////////////// ////////////////////
//// �p�r       �F  ~MagneticumObject3D()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �FPlayer�p�̃R���X�g���N�^
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////	
MagneticumObject3D::~MagneticumObject3D(){
	//���E�@�O��
	SafeDelete( m_pMagneticField  );
	SafeDelete( m_pMagneticField2 );
	SafeDelete( m_pMagneticField3 );
	SafeDelete( m_pMagneticField4 );
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();

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
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);
		//setPole( pNowItem->m_bMagnetPole );
		////�e�N�X�`��������ꍇ
		//if(m_pTexture){
		//	DWORD wkdword;
		//	//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
		//	i_DrawPacket.pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
		//	//�X�e�[�W�̐ݒ�
		//	i_DrawPacket.pD3DDevice->SetTexture(0,m_pTexture);
		//	//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		//	i_DrawPacket.pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		//	//i_DrawPacket.pD3DDevice->SetFVF(PlateFVF);
		//	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		//	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &pNowItem->m_Matrix);
		//	//�R�������b�V����Draw()���Ă�
		//	CommonMesh::Draw(i_DrawPacket);
		//	i_DrawPacket.pD3DDevice->SetTexture(0,0);
		//	//�X�e�[�W�����ɖ߂�
		//	i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		//}
		//else{
		////�e�N�X�`�����Ȃ��ꍇ
		//	// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		//	i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &pNowItem->m_Matrix);
		//	//�R�������b�V����Draw()���Ă�
		//	CommonMesh::Draw(i_DrawPacket);
		//}
		m_pMagneticField->SetPos(pNowItem->m_vPos);
		m_pMagneticField->setPole(pNowItem->m_bMagnetPole);
		m_pMagneticField->Update( UpdatePacket( i_DrawPacket ) );

		m_pMagneticField2->SetPos(pNowItem->m_vPos);
		m_pMagneticField2->setPole(pNowItem->m_bMagnetPole);
		m_pMagneticField2->Update( UpdatePacket( i_DrawPacket ) );

		m_pMagneticField3->SetPos(pNowItem->m_vPos);
		m_pMagneticField3->setPole(pNowItem->m_bMagnetPole);
		m_pMagneticField3->Update( UpdatePacket( i_DrawPacket ) );

		m_pMagneticField4->setRadius( (*it)->m_fEffectSize );
		m_pMagneticField4->SetPos(pNowItem->m_vPos);
		m_pMagneticField4->setPole(pNowItem->m_bMagnetPole);
		m_pMagneticField4->Update( UpdatePacket( i_DrawPacket ) );
		(*it)->m_fEffectSize	= m_pMagneticField4->getRadius();
		
		m_pMagneticField->Draw(i_DrawPacket);
		m_pMagneticField2->Draw(i_DrawPacket);
		m_pMagneticField3->Draw(i_DrawPacket);
		m_pMagneticField4->Draw(i_DrawPacket);

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
	if( !m_pCoil ) 
		m_pCoil = (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL);

	setDrawTarget();
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);
		setPole( pNowItem->m_bMagnetPole );

		//�v�Z��Update��
		//�g��k��
		D3DXMATRIX mScale;
		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale,
			pNowItem->m_vScale.x,pNowItem->m_vScale.y,pNowItem->m_vScale.z);
		//��]
		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationQuaternion(&mRot,&pNowItem->m_vRot);
		//�ړ��p
		D3DXMATRIX mMove;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			pNowItem->m_vPos.x,pNowItem->m_vPos.y,pNowItem->m_vPos.z);
		//�~�b�N�X�s��
		pNowItem->m_Matrix = mScale * mRot * mMove;
		//�}�e�B���A���ݒ�
		m_Material = pNowItem->m_Material;

		//m_pMagneticField4->SetPos(pNowItem->m_vPos);
		//m_pMagneticField4->setPole(pNowItem->m_bMagnetPole);
		//m_pMagneticField4->Update( i_UpdatePacket );

		++it;
	}

}
void MagneticumObject3D::setDrawTarget(){

	//////////
	//	�`��ΏۊO�̍폜
	//
	TARGETCONTAINER::iterator	TIMit  = m_ItemMap_Target.begin(),
								TIMend = m_ItemMap_Target.end(  );
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
void MagneticumObject3D::AddMagnetic(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,POLE vPole,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem			= new Magnet3DItem	;
	pItem->m_bHidden			= true				;
	pItem->m_vScale				= vScale			;
	pItem->m_vPos				= vPos				;
	pItem->m_fMapKey			= vPos.y			;
	pItem->m_bMagnetPole		= vPole				;
	pItem->m_fEffectSize		= m_fMagneticum		;
    ::ZeroMemory(&pItem->m_Material,sizeof(D3DMATERIAL9)) ;
	pItem->m_Material.Diffuse	= Diffuse			;
	pItem->m_Material.Specular	= Specular			;
	pItem->m_Material.Ambient	= Ambient			;
	//��]�̏�����
	D3DXQuaternionRotationYawPitchRoll(&pItem->m_vRot,
			D3DXToRadian(vRot.y),D3DXToRadian(vRot.x),D3DXToRadian(vRot.z)) ;


	m_ItemMap_All.insert(multimap<float,Magnet3DItem*>::value_type(pItem->m_vPos.y,pItem));	
}
void MagneticumObject3D::HitTest(){
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);
		if(m_pCoil->CheckDistance(pNowItem->m_vPos ,(float)MGPRM_MAGNETICUM_QUAD, false))
			m_pCoil->m_fMoveDir = m_pCoil->MagneticDecision(m_pCoil->m_fMoveDir,pNowItem->m_vPos,pNowItem->m_bMagnetPole);
		it++;
	}
}
/////////////////// ////////////////////
//// �p�r       �Fbool MagneticumObject3D::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
//// �J�e�S��   �F�֐�
//// �p�r       �F�����𔻒�
//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
//// �ߒl       �Ftrue , false
//// �S����     �F�{�����V
//// ���l       �F
//bool MagneticumObject3D::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const{
//	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, i_vCoilPos ) ;
//	if( Lng <= i_iBorder ){
//		return true;
//	}
//	else{
//		return false;
//	}
//}

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
Factory_Magnetic::Factory_Magnetic(FactoryPacket *fpac){
	try{
		// �V�����_�[�I�u�W�F�N�g�̃}�e���A��
		D3DCOLORVALUE MagnetDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		D3DCOLORVALUE MagnetSpecular = { 0.0f, 0.0f, 0.0f, 0.0f } ;
		D3DCOLORVALUE MagnetAmbient  = { 1.0f, 1.0f, 1.0f, 1.0f } ;
		// ���E�̕\��
		//MagneticumObject3D* Magnet = new MagneticumObject3D(
		//	fpac->pD3DDevice,
		//	NULL,//fpac->m_pTexMgr->addTexture(fpac->pD3DDevice,L"ddn.jpg")
		//);
		//fpac->m_pVec->push_back(Magnet);

		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,10.0f,0.0f),
		//			  POLE_N,
		//			  MagnetDiffuse,
		//			  MagnetSpecular,
		//			  MagnetAmbient);

		//Magnet->AddMagnetic(D3DXVECTOR3(1.0f,1.0f,1.0f),
		//			  D3DXVECTOR3(0.0f,0.0f,0.0f),
		//			  D3DXVECTOR3(30.0f,30.0f,0.0f),
		//			  POLE_S,
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
//end of namespace bomberobject.
}
//end of namespace wiz.
