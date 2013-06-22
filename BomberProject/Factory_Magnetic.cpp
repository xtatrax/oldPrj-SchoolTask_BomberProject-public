////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Magnetic.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�g�n ��m
//	����			�F�{�� ���V
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
// PlaneCircle ��`��
//****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
MagnetFieldCircle::MagnetFieldCircle(LPDIRECT3DDEVICE9 pD3DDevice,DWORD dwVertexQty){

	m_dwVertexQty	= dwVertexQty  +1 ;
	float iRotSize	= 360.0f / (dwVertexQty -1) ;
	Vertex* m_pVertex;

	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * m_dwVertexQty , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	

	m_pVertex[ 0 ]	= Vertex( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) , 0x3FFFFFFF );

	for ( DWORD i = 1 ; i < m_dwVertexQty  ; i++ ){
		m_pVertex[ i ]	= Vertex( D3DXVECTOR3(  cosf( D3DXToRadian( iRotSize * i ) ) , sinf(D3DXToRadian( iRotSize * i ) ) , 0.0f )	, 0x3FFFFFFF );
	}
	m_pVertexBuffer->Unlock();
	D3DXMatrixScaling( &m_mMatrix, 10.0f, 10.0f, 1.0f );
}

/////////////////// ////////////////////
//// �֐���     �F
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F
//// �ߒl       �F�Ȃ�
//// �S��       �F���� �O
//// ���l       �F
////            �F
////
void MagnetFieldCircle::Draw(DrawPacket& i_DrawPacket){
	 //���[���h�ϊ��s���ݒ�
	i_DrawPacket.pD3DDevice->SetTransform( D3DTS_WORLD , &m_mMatrix );								//�ϊ��ςݒ��_�̏ꍇ�͖��������

	i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
    i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	////���_�A���t�@���g����悤�ɂ���f�t�H���g�ł����̂悤�ɐݒ肳��Ă���
 //   i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);
 //   //��̐ݒ��L���ɂ���
 //   i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_COLORVERTEX, TRUE); 

	//	: ���_�o�b�t�@��p���ă��f����`�悷��
	i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	i_DrawPacket.pD3DDevice->SetStreamSource( 0, m_pVertexBuffer , 0 , Vertex::getSize() );		//	: �`��ΏۂƂȂ钸�_�o�b�t�@��ݒ�
	i_DrawPacket.pD3DDevice->SetFVF( Vertex::getFVF() );											//	: ���_�f�[�^�̌`����ݒ�
	i_DrawPacket.pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN  , 0, m_dwVertexQty  );	//	: ���_�f�[�^�̕`��i�`��̎d���A�`��J�n�ʒu�A�v���~�e�B�u���j
	i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    //i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_COLORVERTEX, FALSE); 
	i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
}



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
	wiz::OBJID id 								//	: ID
)
:PrimitiveCylinder(
				   pD3DDevice,
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   D3DCOLORVALUE(),
				   id,
				   NULL)
,m_bMagnetPole( POLE_S )
,m_fMagneticum((float)MGPRM_MAGNETICUM)
,m_MagneticField( pD3DDevice, 32 )
,m_pCoil(	NULL )
,m_pCamera(	NULL )
,m_fEffectSizeRate(0)
{
	::ZeroMemory( &m_Material, sizeof(D3DMATERIAL9) ) ;
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
,m_MagneticField( pD3DDevice, 32 )
,m_pCoil(NULL)
,m_pCamera(	NULL )
,m_fEffectSizeRate(0)

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
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();

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
	if( !m_pCamera )	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA	) ;
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;

	setDrawTarget();

	m_fEffectSizeRate += i_UpdatePacket.pTime->getElapsedTime() / MGPRM_EFFECTINTERVAL ;
	Debugger::DBGSTR::addStr(L"m_fEffectSizeRate = %f\n",m_fEffectSizeRate);
	m_fEffectSizeRate >= 1.0f && ( m_fEffectSizeRate = 0 ) ;

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

		//	: �F�̌���
		m_MagneticField.setPole(pNowItem->m_bMagnetPole);

		//////////
		//	: ��{Matrix�̏���
		D3DXMATRIX mAll, mScale, mMove;

		D3DXMatrixTranslation(&mMove,
			pNowItem->m_vPos.x,
			pNowItem->m_vPos.y,
			pNowItem->m_vPos.z-0.2f
		);
		//	: ��{Matrix�̏���
		//////////

		//////////
		//	: �͈͂̕`��

		//	: ������
		BYTE byPartitionQty = 3 ;

		float fCircleSize ;
		for( BYTE i = byPartitionQty ; i >= 1 ; i-- ){
			fCircleSize = (float)MGPRM_MAGNETICUM * ( (float)i/(float)byPartitionQty ) ;
			D3DXMatrixIdentity(&mScale);
			D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.0f);
			mAll = mScale * mMove;
			m_MagneticField.setMatrix(mAll) ;
			m_MagneticField.Draw(i_DrawPacket);
		}
		//	: �͈͂̕`��
		//////////


		//////////
		//	: �G�t�F�N�g�̕`��
		if( pNowItem->m_bMagnetPole == m_pCoil->getMagnetPole() )
			fCircleSize =(float)MGPRM_MAGNETICUM * m_fEffectSizeRate;
		else
			fCircleSize =(float)MGPRM_MAGNETICUM * (1.0f-m_fEffectSizeRate);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.0f);
		mAll = mScale * mMove;
		m_MagneticField.setMatrix(mAll) ;
		m_MagneticField.Draw(i_DrawPacket);
		//	: �G�t�F�N�g�̕`��
		//////////

		++it;
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
void MagneticumObject3D::AddMagnetic(D3DXVECTOR3 &vScale,D3DXVECTOR3 &vRot,D3DXVECTOR3 &vPos,POLE vPole,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem			= new Magnet3DItem	;
	pItem->m_bHidden			= true				;
	pItem->m_vPos				= vPos				;
	pItem->m_fMapKey			= vPos.y			;
	pItem->m_bMagnetPole		= vPole				;


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
