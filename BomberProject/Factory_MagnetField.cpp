////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_MagnetField.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F���� �O
//	���p��			�F�g�n ��m
//	����			�F�{�� ���V
//	�����ް��Ɣ��l	�F���E�͈͂̉���Object
//					��
//	namespace wiz;
//		class Factory_MagnetField ;
//
#include "StdAfx.h"
#include "Factory_MagnetField.h"
#include "Factory_Player.h"
#include "Factory_Coil.h"

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

	m_dwVertexQty	= dwVertexQty +1 ;	//	: �p���@+�@���S���_
	float iRotSize	= 360.0f / ( dwVertexQty -1 ) ;
	Vertex* m_pVertex;

	pD3DDevice->CreateVertexBuffer( Vertex::getSize() * m_dwVertexQty , D3DUSAGE_WRITEONLY, Vertex::getFVF(), D3DPOOL_MANAGED, &m_pVertexBuffer, NULL );
	m_pVertexBuffer->Lock( 0, 0, (void**)&m_pVertex ,0 );	//	: ���_�f�[�^�̃A�h���X���擾����ƂƂ��ɁA�f�[�^�ւ̃A�N�Z�X���J�n����	

	m_pVertex[ 0 ]	= Vertex( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) , 0x3FFFFFFF );

	for ( DWORD i = 0 ; i < dwVertexQty  ; i++ ){
		m_pVertex[ i+1 ]	= Vertex(
			D3DXVECTOR3(  cosf( D3DXToRadian( iRotSize * i ) ) ,
			sinf(D3DXToRadian( iRotSize * i ) ) , 0.0f )	,
			0x3FFFFFFF
		);
	}
	m_pVertexBuffer->Unlock();
	//D3DXMatrixScaling( &m_mMatrix, 10.0f, 10.0f, 1.0f );

	m_dwColor_S	= 0x3F0000FF;
	m_dwColor_N	= 0x3FFF0000;
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
	if( !this ){
		Debugger::DBGWRITINGLOGTEXT::addStr(L"MagnetFieldCircle::Draw �� this �� NULL �Ȃ̂ł��E�E�E");
		return;
	}
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
	i_DrawPacket.pD3DDevice->DrawPrimitive( D3DPT_TRIANGLEFAN  , 0, m_dwVertexQty -1 );	//	: ���_�f�[�^�̕`��i�`��̎d���A�`��J�n�ʒu�A�v���~�e�B�u���j
	i_DrawPacket.pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    //i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_COLORVERTEX, FALSE); 
	i_DrawPacket.pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
}



//3D�ϊ��p
/**************************************************************************
 MagnetField ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �֐���     �FMagnetField( LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 pTexture,
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
MagnetField::MagnetField(
	LPDIRECT3DDEVICE9 pD3DDevice,				//	: �f�o�C�X
	wiz::OBJID id 								//	: ID
)
:Object(id)
,m_MagneticField( pD3DDevice, 64 )
,m_pCoil(	NULL )
,m_pCamera(	NULL )
,m_pPole_N(NULL)
,m_pPole_S(NULL)
,m_fEffectSizeRate( NULL )
,m_bPtn( true )
,m_iFlashingInterval( 0 )
{
}
/////////////////// ////////////////////
//// �p�r       �F~MagnetField()
//// �J�e�S��   �F
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////	
MagnetField::~MagnetField(){
	m_pCamera = NULL;
	m_pCoil	  = NULL;
	m_pPole_N = NULL;
	m_pPole_S = NULL;
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
void MagnetField::Update( UpdatePacket& i_UpdatePacket ){
	if( !m_pCamera )	m_pCamera	=     (Camera*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_SYS_CAMERA	) ;
	if( !m_pCoil )		m_pCoil		= (PlayerCoil*)SearchObjectFromID(i_UpdatePacket.pVec,OBJID_3D_COIL		) ;

	m_fEffectSizeRate += (float)i_UpdatePacket.pTime->getElapsedTime() / MGPRM_EFFECTINTERVAL ;
	Debugger::DBGSTR::addStr(L"m_fEffectSizeRate = %f\n",m_fEffectSizeRate);
	m_fEffectSizeRate >= 1.0f && ( m_fEffectSizeRate = 0 ) ;

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
//// �S����     �F�g�n ��m
//// �ҏW��     �F���� �O(�啝����)
//// ���l       �F
void MagnetField::Draw(DrawPacket& i_DrawPacket)
{

	//	: �F�̌���
	m_MagneticField.setPole(MagneticObject::getMagnetPole());

	//////////
	//	: ��{Matrix�̏���
	D3DXMATRIX mAll, mScale, mMove;

	D3DXMatrixTranslation(&mMove,
		m_vPos.x,
		m_vPos.y,
		m_vPos.z+0.2f
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
		D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.1f);
		mAll = mScale * mMove;
		m_MagneticField.setMatrix(mAll) ;
		m_MagneticField.Draw(i_DrawPacket);
	}
	//	: �͈͂̕`��
	//////////


	if( !m_pCoil ){
		OutputDebugString(L"MagnetField::Draw()�֐���[ m_pCoil ] ���u�ʂ��!�v���Ă����Ă�ł�� \n");
		return ;
	}
	//////////
	//	: �G�t�F�N�g�̕`��
	if( MagnetField::getMagnetPole() == m_pCoil->getMagnetPole() )
		fCircleSize =(float)MGPRM_MAGNETICUM * m_fEffectSizeRate;
	else
		fCircleSize =(float)MGPRM_MAGNETICUM * (1.0f-m_fEffectSizeRate);

	D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling(&mScale, fCircleSize, fCircleSize, 0.1f);
	mAll = mScale * mMove;
	m_MagneticField.setMatrix(mAll) ;
	m_MagneticField.Draw(i_DrawPacket);
	//	: �G�t�F�N�g�̕`��
	//////////

}

void MagnetField::HitTest(){
	if(m_pCoil->CheckDistance(m_vPos ,(float)MGPRM_MAGNETICUM_QUAD, false))
		m_pCoil->MagneticDecision(m_vPos,MagneticObject::getMagnetPole());
}

void	MagnetField::Flashing( UpdatePacket& i_UpdatePacket, POLE i_Pole ){
	if( i_Pole == POLE_S ){
		if( m_bPtn ){
			m_MagneticField.setColor( i_Pole, 0x000000FF );
		}
		else{
			m_MagneticField.setColor( i_Pole, 0x3F0000FF );
			m_iFlashingInterval++;
		}
	}
	else{
		if( m_bPtn ){
			m_MagneticField.setColor( i_Pole, 0x00FF0000 );
		}
		else{
			m_MagneticField.setColor( i_Pole, 0x3FFF0000 );
			m_iFlashingInterval++;
		}
	}

	if( m_bPtn ){
			m_bPtn	= false;
	}
	else{
		if( m_iFlashingInterval >= 5 ){
			m_bPtn	= true;
			m_iFlashingInterval	= 0;
		}
	}
}

/**************************************************************************
 StaticMagnetField ��`��
****************************************************************************/
/////////////////// ////////////////////
//// �p�r       �Fbool StaticMagnetField::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos ) const
//// �J�e�S��   �F�֐�
//// �p�r       �F�����𔻒�
//// ����       �FD3DXVECTOR3& i_vMagneticFieldPos //���E�̈ʒu 
////�@�@�@�@�@�@�FD3DXVECTOR3& i_vCoilPos          //�R�C���̈ʒu
////�@�@�@�@�@�@�Ffloat        i_iBorder           //���肷��l
//// �ߒl       �Ftrue , false
//// �S����     �F�{�����V
//// ���l       �F
//bool MagnetField::CheckDistance( D3DXVECTOR3& i_vMagneticFieldPos, D3DXVECTOR3& i_vCoilPos, float i_iBorder ) const{
//	float Lng  = (float)TwoPointToBassLength( i_vMagneticFieldPos, i_vCoilPos ) ;
//	if( Lng <= i_iBorder ){
//		return true;
//	}
//	else{
//		return false;
//	}
//}
StaticMagnetField::StaticMagnetField(LPDIRECT3DDEVICE9 pD3DDevice, wiz::OBJID id)
:MagnetField(pD3DDevice,id){

}
/////////////////// ////////////////////
//// �p�r       �F  ~StaticMagnetField()
//// �J�e�S��   �F�R���X�g���N�^
//// �p�r       �F
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////	
StaticMagnetField::~StaticMagnetField(){
	//���E�@�O��
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();

}

void StaticMagnetField::setDrawTarget(){

	if( !m_pCamera ) return;

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
void StaticMagnetField::Update( UpdatePacket& i_UpdatePacket ){

	MagnetField::Update(i_UpdatePacket);
	setDrawTarget();
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
//// �S����     �F�g�n ��m
//// �ҏW��     �F���� �O(�啝����)
//// ���l       �F
void StaticMagnetField::Draw(DrawPacket& i_DrawPacket){

	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);

		//	: �ɐ�
		MagneticObject::setPole(pNowItem->m_bMagnetPole);
		MagnetField::m_vPos = pNowItem->m_vPos;

		MagnetField::Draw(i_DrawPacket);
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
void StaticMagnetField::AddMagnetic(D3DXVECTOR3 &vPos,POLE vPole,
			D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient)
{
	Magnet3DItem* pItem			= new Magnet3DItem	;
	pItem->m_bHidden			= true				;
	pItem->m_vPos				= vPos				;
	pItem->m_fMapKey			= vPos.y			;
	pItem->m_bMagnetPole		= vPole				;


	m_ItemMap_All.insert(multimap<float,Magnet3DItem*>::value_type(pItem->m_vPos.y,pItem));	
}
void StaticMagnetField::HitTest(){
	TARGETCONTAINER::iterator	it  = m_ItemMap_Target.begin(),
								end = m_ItemMap_Target.end();
	while(it != end){
		Magnet3DItem* pNowItem  = (*it);
		if(m_pCoil->CheckDistance( pNowItem->m_vPos,(float)MGPRM_MAGNETICUM_QUAD, false))
			m_pCoil->MagneticDecision(pNowItem->m_vPos,pNowItem->m_bMagnetPole);
		it++;
	}

}

/**************************************************************************
 Factory_MagnetField ��`��
****************************************************************************/
/**************************************************************************
 Factory_MagnetField::Factory_MagnetField(
	Factory_MagnetField *fpac
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	TextureManager& TexMgr		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
Factory_MagnetField::Factory_MagnetField(FactoryPacket *fpac){
	try{
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 Factory_MagnetField::~Factory_MagnetField();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Factory_MagnetField::~Factory_MagnetField(){
    //�Ȃɂ����Ȃ�
}

}
//end of namespace bomberobject.
}
//end of namespace wiz.
