////////////////////////////// //////////////////////////////
//	�v���W�F�N�g	�FBomberProject
//	�t�@�C����		�FFactory_Item.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�F�����@�� �{�����V
//	�����ް��Ɣ��l	�F�A�C�e���t�@�N�g���[
//					��
//	namespace wiz;
//		class Item ;
//		class Factory_Item ;
//
#include "StdAfx.h"
#include "Object.h"
#include "Scene.h"
#include "BassItems.h"
#include "Factory_Item.h"
//#include "Factory_Player.h"

namespace wiz{
namespace bomberobject{




/**************************************************************************
 Item ��`��
****************************************************************************/
/***************************************************************************
�֐����@�@�@�FItem( FactoryPacket* fpac,
                      LPDIRECT3DTEXTURE9 pTexture,
                      wiz::OBJID id )
�J�e�S���@�@�F�R���X�g���N�^
�p�r�@�@�@�@�F
�����@�@�@�@�FFactoryPacket* fpac           // : �f�o�C�X�Ȃ�
�@�@�@�@�@�@�FLPDIRECT3DTEXTURE9 pTexture   // : �e�N�X�`���\
�@�@�@�@�@�@�Fwiz::OBJID id                 // : ID
�߂�l�@�@�@�F
�S���ҁ@�@�@�F������
���l�@�@�@�@�F
****************************************************************************/
Item::Item(FactoryPacket* fpac,LPDIRECT3DTEXTURE9 pTexture, wiz::OBJID id)
	:PrimitiveSphere(fpac->pD3DDevice,
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						D3DCOLORVALUE(),
						pTexture,
						id
	)
	,m_pPlayerCoil(NULL)
	,m_pSuperGage(NULL)
	,m_pCamera(NULL)
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
/////////////////// ////////////////////
//// �֐���     �F~Item();
//// �J�e�S��   �F�f�X�g���N�^
//// �p�r       �F�j��
//// ����       �F�Ȃ�
//// �ߒl       �F�Ȃ�
//// �S����     �F���� �O
//// ���l       �F
////            �F
////
Item::~Item(){
	SafeDeletePointerMap( m_ItemMap_All );
	m_ItemMap_All.clear();
	m_ItemMap_Target.clear();
}

/**************************************************************
�֐����@�@�Fvoid Item::Draw(DrawPacket &i_DrawPacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�I�u�W�F�N�g�̕`��
�����@�@�@�FDrawPacket &i_DrawPacket          // �`��p�̂������
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************/
void	Item::Draw(DrawPacket &i_DrawPacket){
	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();
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
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
			i_DrawPacket.pD3DDevice->SetTexture(0,0);
			//�X�e�[�W�����ɖ߂�
			i_DrawPacket.pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
		}
		else{
		//�e�N�X�`�����Ȃ��ꍇ
			// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
			i_DrawPacket.pD3DDevice->SetTransform(D3DTS_WORLD, &(*it)->m_mMatrix);
			//�R�������b�V����Draw()���Ă�
			CommonMesh::Draw(i_DrawPacket);
		}
		++it;
	}
}


void Item::setDrawTarget(){

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

/*******************************************************************
�֐����@�@�Fvoid Item::Update(UpdatePacket& i_UpdatePacket)
�J�e�S���@�F�֐�
�p�r�@�@�@�F�f�[�^�X�V
�����@�@�@�FUpdatePacket& i_UpdatePacket  // �X�V�p�f�[�^�������
�߂�l�@�@�F
�S���ҁ@�@�F������
�ҏW      �F���� �O
���l�@�@�@�F
********************************************************************/
void	Item::Update(UpdatePacket& i_UpdatePacket)
{

	vector<Object*>*	pVec	= i_UpdatePacket.pVec;

	if( !m_pPlayerCoil )	m_pPlayerCoil	= (PlayerCoil*)SearchObjectFromID(pVec, OBJID_3D_COIL       );
	if( !m_pSuperGage )		m_pSuperGage	=  (SuperGage*)SearchObjectFromID(pVec, OBJID_UI_SUPERGAUGE );
	if( !m_pCamera )		m_pCamera		=     (Camera*)SearchObjectFromID(pVec, OBJID_SYS_CAMERA    );

	//�R�C���̈ʒu�擾
	D3DXVECTOR3	cPos	= m_pPlayerCoil->getPos();

	setDrawTarget();

	TARGETCONTAINER::iterator it = m_ItemMap_Target.begin();

	while(it != m_ItemMap_Target.end()){

		if( (m_pPlayerCoil->getState() == COIL_STATE_MOVE		//	: �R�C�����ړ���
			|| m_pPlayerCoil->getState() == COIL_STATE_STICK )	//	: ���������E�ɋz����
			&& m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_CHARGE)					//	: �Ȃ�����	�X�[�p�[���[�h����Ȃ�������
		{
			//	: ��������Ώۂ܂ł̃x�N�g�����Z�o
			D3DXVECTOR3	vTargetDir	= cPos - ((*it)->m_Pos) ;

			//	: �����ƑΏۂ܂ł̋��������߂�
			double dirX = vTargetDir.x * vTargetDir.x;
			double dirY = vTargetDir.y * vTargetDir.y;
			(*it)->m_fDistance	 = (float)sqrt(dirX + dirY);

			//������5�ȓ��Ȃ����Ă���
			if( (*it)->m_fDistance < SuctionArea ){
				(*it)->m_Pos	+= vTargetDir/**SpeedRate*/ * m_pPlayerCoil->getSpeed();

				//�v���C���[�ƌ���Ȃ��߂��Ȃ�����A����
				if( (*it)->m_fDistance < VanishArea ){
					i_UpdatePacket.SearchWaveAndPlay( RCTEXT_SOUND_SE_ITEMS );
					//m_ItemMap_All.value_comp();
					ALLCONTAINER::size_type		count	= m_ItemMap_All.count((*it)->m_fMapKey) , 
												i		;
					ALLCONTAINER::iterator		ait		= m_ItemMap_All.find((*it)->m_fMapKey);
					//�G�l���M�[��
					m_pSuperGage->Recovery(-(*it)->m_fRecoveryPoint);
					if(!m_pSuperGage->getAcquired())m_pSuperGage->setAcquired(true);
					(*it)->m_bHidden = true ;
					// SafeDelete( (*it) );
					for( i = 0 ; i < count ; i++ ){
						if( ait->second == (*it) ){
							SafeDelete(ait->second);
							m_ItemMap_All.erase(ait);
							break ;
						}
						ait++ ;
					}
					it = m_ItemMap_Target.erase( it );
					continue;
				}
			}
			////�Q�[�W���ő�ɂȂ�����R�C���𖳓G��Ԃ�
			//if(m_pSuperGage->getRate() <= 0.0f){
			//	m_pPlayerCoil->setSuperMode(COIL_STATE_SUPER_READY);
			//}
		}
		if(m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_READY && !m_pSuperGage->getAcquired()){
				m_pSuperGage->setAcquired(true);
		}
		//�ړ��p
		D3DXMATRIX mMove, mScale;
		D3DXMatrixIdentity(&mMove);
		D3DXMatrixTranslation(&mMove,
			(*it)->m_Pos.x,(*it)->m_Pos.y,(*it)->m_Pos.z);
		D3DXMatrixScaling(&mScale,
			(*it)->m_Size.x,(*it)->m_Size.y,(*it)->m_Size.z);

		//�}�e�B���A���ݒ�
		m_Material = (*it)->m_Material;
		(*it)->m_mMatrix	= mScale * mMove;

		it++;
	}
//#if defined( ON_DEBUGGINGPROCESS ) | defined( PRESENTATION )
//	if( GetAsyncKeyState( MYVK_DEBUG_INVISIBLEGAUGE_MAX ) ){
//		m_pSuperGage->Recovery(-1) ;
//	}
//#endif
//	static float s_fTimeAccumulator = 0 ;
//	if(m_pPlayerCoil->getState() == COIL_STATE_MOVE && m_pPlayerCoil->getSuperMode() == COIL_STATE_SUPER_MOVE){
//		//	: ���[�σ��[�h�̎�
//		//static float s_fTimeTotal = 0.0f;
//		//s_fTimeTotal += (float)SUPER_GAGE_MAX / (float)COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime();
//		//if(s_fTimeTotal >= 1.0f){
//		//	m_pSuperGage->Consume( -(1.0f / COIL_SUPER_MODE_TIME * (float)i_UpdatePacket.pTime->getElapsedTime()) );
//		//	s_fTimeTotal -= (int)s_fTimeTotal;
//		//}
//		if( ( s_fTimeAccumulator += i_UpdatePacket.pTime->getElapsedTime()) < COIL_SUPER_MODE_TIME ){
//			float fOneSecondSub = (1.0f / (float)COIL_SUPER_MODE_TIME);
//			float fFrameSub     = fOneSecondSub * (float)i_UpdatePacket.pTime->getElapsedTime();
//			Debugger::DBGSTR::addStr(L"fOneSecondSub = %f\n",fOneSecondSub);
//			Debugger::DBGSTR::addStr(L"fFrameSub     = %f\n",fFrameSub);
//			m_pSuperGage->Consume( -fFrameSub );	
//		}
//	}else{
//		s_fTimeAccumulator = 0 ;	
//	}

}

/***********************************************
�֐����@�Fvoid Item::addItem(
                      D3DXVECTOR3 pos,
                      D3DXVECTOR3 size,
                      D3DCOLORVALUE Diffuse,
                      D3DCOLORVALUE Specular, 
                      D3DCOLORVALUE Ambient)
�J�e�S���F�֐�
�p�r�@�@�F�A�C�e���̒ǉ�
�����@�@�FD3DXVECTOR3 pos          //�`��ʒu
�@�@�@�@�FD3DXVECTOR3 size         //�傫��
�@�@�@�@�FD3DCOLORVALUE Diffuse    //
�@�@�@�@�FD3DCOLORVALUE Specular   //
�@�@�@�@�FD3DCOLORVALUE Ambient    //
�߂�l�@�F
�S���ҁ@�F������
���l�@�@�F
***********************************************/
void	Item::addItem(D3DXVECTOR3 pos, D3DXVECTOR3 size,
					  D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient, float fRecoveryPoint)
{
	try{
		fRecoveryPoint >= 1.0f && (fRecoveryPoint = 1.0f);
		float	sizeRate		= 1.0f;
		BallItem* bItem			= new BallItem;
		bItem->m_Pos			= pos;
		bItem->m_Size			= size * ( sizeRate );
		bItem->m_fMapKey		= pos.y ;
		bItem->m_bHidden		= true ;
		bItem->m_fDistance		= 6.0f;
		//bItem->m_fItemType	= itemType;
		bItem->m_fRecoveryPoint = fRecoveryPoint ;
		//if(itemType == ITEM_TYPE_RECOVETY)				bItem->m_fRecoveryPoint =
		RECOVERY_POINT;
		//if(itemType == ITEM_TYPE_RECOVETY_BIG)bItem->	m_fRecoveryPoint		= RECOVERY_POINT_L;
        // D3DMATERIAL9�\���̂�0�ŃN���A
        ::ZeroMemory(&bItem->m_Material,sizeof(D3DMATERIAL9));
		bItem->m_Material.Diffuse = Diffuse;
		bItem->m_Material.Specular = Specular;
		bItem->m_Material.Ambient = Ambient;

		m_ItemMap_All.insert(multimap<float,BallItem*>::value_type(bItem->m_Pos.y,bItem));
	}
	catch(...){
		throw;
	}
}

/**************************************************************************
 Factory_Item ��`��
****************************************************************************/
/**************************************************************************
�֐����@�@�FFactory_Item::Factory_Item( FactoryPacket* fpac );
�J�e�S���@�F�R���X�g���N�^
�p�r�@�@�@�F
�����@�@�@�FFactoryPacket* fpac     // �������̃f�[�^
�߂�l�@�@�F
�S���ҁ@�@�F������
���l�@�@�@�F
***************************************************************************/
Factory_Item::Factory_Item(FactoryPacket* fpac){
	try{
        D3DCOLORVALUE BallDiffuse = {0.0f,0.7f,0.7f,1.0f};
        D3DCOLORVALUE BallSpecular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE BallAmbient = {0.0f,0.7f,0.7f,1.0f};
		Item*	it	=	new	Item(fpac,NULL,OBJID_3D_ITEM);

		//�A�C�e��(��)
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 347*ItemDiffusionRate; j++){
				it->addItem(D3DXVECTOR3((float(i)*(ItemDiffusionRate/3.0f)+float(rand()%100*0.05f))+1.5f,
										(float(j)*(ItemDiffusionRate)+float(rand()%100*0.05f))+1.5f,0.0f),
							ITEM_SCALE,
							BallDiffuse,BallSpecular,BallAmbient);
			}
		}

		//�A�C�e��(��)
		it->addItem(D3DXVECTOR3(10.0f,10.0f,0.0f),
					ITEM_SCALE,
					BallDiffuse,BallSpecular,BallAmbient,
					RECOVERY_POINT_L);

		fpac->m_pVec->push_back(it);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 �֐����@�@�FFactory_Item::~Factory_Item();
 �J�e�S���@�F�f�X�g���N�^
 �p�r�@�@�@�F
 �����@�@�@�F
 �߂�l�@�@�F
 �S���ҁ@�@�F������
 ���l�@�@�@�F
***************************************************************************/
Factory_Item::~Factory_Item(){
    //�Ȃɂ����Ȃ�
}
}
//end of namespace bomberobject.

}
//end of namespace wiz.
